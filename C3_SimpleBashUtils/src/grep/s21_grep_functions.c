#include "s21_grep.h"

void check_flag(int argc, char *argv[], Flags *flags) {
  int rez = 0;
  while ((rez = getopt(argc, argv, "ivclnhsf:e:o")) != -1) {
    switch (rez) {
      case 'e':
        flags->e = 1;
        strcat(flags->arg_rex, optarg);
        strcat(flags->arg_rex, "|");
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        strcpy(flags->file_f, optarg);
        readRegexFromFile(flags);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        errorFunc();
        exit(EXIT_FAILURE);  // Программа завершилась с ошибкой EXIT_FAILURE = 1
    }
  }
  setupSearchParameters(flags, argc, optind, argv);
}

void setupSearchParameters(Flags *flags, int argc, int optind, char *argv[]) {
  // Если не установлены флаги -e и -f
  if (!flags->e && !flags->f) {
    // Если есть дополнительные аргументы командной строки - это паттерны
    if (argc > optind) {
      strcat(flags->arg_rex, argv[optind]);
      optind++;
    }
  }

  // Сбросить счетчик
  flags->count = 0;

  // Если установлен флаг -e, удалить лишний символ '|' в конце регулярного
  // выражения
  if (flags->e == 1) {
    flags->arg_rex[strlen(flags->arg_rex) - 1] = '\0';
  }

  // Сбор файлов в
  while (argc > optind) {
    flags->file[flags->count] = argv[optind];
    flags->count++;
    optind++;
  }
}

void readRegexFromFile(Flags *flags) {
  FILE *file;

  // Открыть файл для чтения
  file = fopen(flags->file_f, "r");
  if (file != NULL) {
    while (!feof(file)) {
      if (fgets(flags->str, BUF, file) != NULL) {
        // Удалить символ новой строки, если он присутствует в конце строки
        if (flags->str[strlen(flags->str) - 1] == '\n' &&
            strlen(flags->str) - 1 != 0)
          flags->str[strlen(flags->str) - 1] = '\0';

        // Добавить строку к регулярному выражению с символом '|'
        strcat(flags->arg_rex, flags->str);
        strcat(flags->arg_rex, "|");
      }
    }
    fclose(file);
  }
  // Удалить последний символ '|' из регулярного выражения
  flags->arg_rex[strlen(flags->arg_rex) - 1] = '\0';
}

void printResult(FILE *file, Flags *flags, regmatch_t star, regex_t reg,
                 int i) {
  while (fgets(flags->str, BUF, file) != NULL) {
    if (flags->str[strlen(flags->str) - 1] != '\n') {
      strcat(flags->str, "\n");
    }
    flags->count_n += 1;
    int regul = regexec(&reg, flags->str, 1, &star, 0);
    if (flags->v == 1) regul = !regul;
    if (regul == 0) {
      flags->count_c += 1;
      flags->count_l += 1;
    }
    if ((flags->n && flags->o) || (flags->v && flags->o)) {
      flags->o = 0;
    }

    if (flags->o == 0 && regul == 0 && flags->c == 0 && flags->count > 1 &&
        flags->l == 0 && flags->n == 0 && flags->h == 0)
      printf("%s:%s", flags->file[i], flags->str);

    if (flags->o == 0 && regul == 0 && flags->c == 0 && flags->count > 1 &&
        flags->l == 0 && flags->n == 0 && flags->h == 1)
      printf("%s", flags->str);

    if (flags->count > 1 && flags->o == 0 && regul == 0 && flags->c == 0 &&
        flags->n == 1 && flags->h == 0)
      printf("%s:%d:%s", flags->file[i], flags->count_n, flags->str);

    if ((flags->o == 0 && regul == 0 && flags->c == 0 && flags->n == 1 &&
         flags->h == 1) ||
        (flags->o == 0 && regul == 0 && flags->count == 1 && flags->l == 0 &&
         flags->n == 1 && flags->c == 0))
      printf("%d:%s", flags->count_n, flags->str);

    if (flags->o == 0 && regul == 0 && flags->count == 1 && flags->l == 0 &&
        flags->n == 0 && flags->c == 0)
      printf("%s", flags->str);

    if (flags->o == 1 && flags->n == 1 && regul == 0)
      printf("%d:", flags->count_n);

    if (regul == 0 && flags->o == 1 && flags->l == 0 && flags->c == 0) {
      char *pointer = flags->str;
      while ((regexec(&reg, pointer, 1, &star, 0) == 0)) {
        if (flags->count == 1) {
          printf("%.*s\n", (int)(star.rm_eo - star.rm_so),
                 pointer + star.rm_so);
        } else {
          printf("%s:%.*s\n", flags->file[i], (int)(star.rm_eo - star.rm_so),
                 pointer + star.rm_so);
        }
        pointer += star.rm_eo;
      }
    }
  }
}

void searchAndPrintResults(Flags *flags) {
  regex_t reg;
  // regmatch_t star;
  regmatch_t star = {0};
  for (int i = 0; i < flags->count; i++) {
    FILE *file = fopen(flags->file[i], "rb");
    if (flags->i == 1) {
      regcomp(&reg, flags->arg_rex, REG_ICASE | REG_EXTENDED);
    } else {
      regcomp(&reg, flags->arg_rex, REG_EXTENDED);
    }
    if (file != NULL) {
      printResult(file, flags, star, reg, i);
      regfree(&reg);
      flag_prod(i, flags);
      fclose(file);
    } else {
      if (flags->s == 0)
        printf("\ngrep: %s: No such file or directory", flags->file[i]);
    }
    flags->count_c = 0;
    flags->count_l = 0;
    flags->count_n = 0;
  }
}

void flag_prod(int i, Flags *flags) {
  if (flags->c == 1 && flags->l == 0 && flags->count > 1 && flags->h == 0)
    printf("%s:%d\n", flags->file[i], flags->count_c);
  if (flags->c == 1 && flags->l == 0 && flags->count > 1 && flags->h == 1)
    printf("%d\n", flags->count_c);
  if (flags->c == 1 && flags->l == 0 && flags->count == 1)
    printf("%d\n", flags->count_c);
  if (flags->c == 0 && flags->l == 1 && flags->count_l > 0)
    printf("%s\n", flags->file[i]);
  if (flags->c == 1 && flags->l == 1 && flags->count > 1 && flags->count_c == 0)
    printf("%s:0\n", flags->file[i]);
  if (flags->c == 1 && flags->l == 1 && flags->count > 1 && flags->count_c >= 1)
    printf("%s:1\n%s\n", flags->file[i], flags->file[i]);
  if (flags->c == 1 && flags->l == 1 && flags->count == 1 &&
      flags->count_c == 0)
    printf("0\n");
  if (flags->c == 1 && flags->l == 1 && flags->count == 1 &&
      flags->count_c >= 1)
    printf("1\n%s\n", flags->file[i]);
}

void errorFunc(void) {
  printf("Usage: ./s21_grep [options] template [file_name]\n");
}
