#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cat_functions.h"

void errorFunc(void) { printf("Usage: ./s21_cat [-benstv] [file ...]\n"); }

int main(int argc, char *argv[]) {
  int flag_b = 0;
  int flag_e = 0;
  int flag_n = 0;
  int flag_s = 0;
  int flag_t = 0;
  int flag_v = 0;
  int display = 1;
  int opt;
  int option_index = 0;

  // Структура для getopt_long
  struct option long_options[] = {
      {"number", no_argument, 0, 'n'},
      {"number-nonblank", no_argument, 0, 'b'},
      {"squeeze-blank", no_argument, 0, 's'},
  };

  if (argc < 2) {
    errorFunc();
    return 1;
  }

  while ((opt = getopt_long(argc, argv, "sbentvET::", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 's':
        flag_s = 1;
        break;
      case 'b':
        flag_b = 1;
        break;
      case 'e':
        flag_e = 1;
        flag_v = 1;
        break;
      case 'E':
        flag_e = 1;
        break;
      case 'n':
        flag_n = 1;
        break;
      case 'T':
        flag_t = 1;
        break;
      case 't':
        flag_t = 1;
        flag_v = 1;
        break;
      case 'v':
        flag_v = 1;
        break;

      default:
        errorFunc();
        exit(EXIT_FAILURE);
    }
  }

  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, "Cannot open file: %s\n", argv[i]);
      continue;  // Продолжить обработку следующего файла
    }

    char line[1024] = "\n";
    int lineNumber = 1;

    while (fgets(line, sizeof(line), file)) {
      char *buffer = strdup(line);
      // strcpy(buffer, line);

      if (flag_b) {
        numberNonblankLines(&buffer, lineNumber, flag_t);
      }

      if (flag_s) {
        squeezeAdjacentBlankLines(&buffer, &display);
      }

      if (flag_n && !flag_b) {
        numberAllLines(&buffer, lineNumber, flag_t);
      }

      if (flag_e) {
        flag_v = 1;
        replaceEndOfLineWithDollarSigns(&buffer);
      }

      if (flag_t) {
        flag_v = 1;
        displayTabsAsCaretI(&buffer);
      }

      if (flag_v) {
        displayNonPrintableCharacters(buffer);
      }

      if (display) {
        printf("%s", buffer);
      }

      free(buffer);
      lineNumber++;
    }
    if (flag_b && !EOF) {
      printf("\t\t");
    }

    fclose(file);
  }

  return 0;
}
