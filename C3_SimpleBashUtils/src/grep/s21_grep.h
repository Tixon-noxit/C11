#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10000

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int count_n;
  int count_l;
  int count_c;
  int count;  // кол-во файлов
  char arg_rex[BUF];
  char *file[BUF];
  char file_f[BUF];
  char str[BUF];
} Flags;

void check_flag(int argc, char *argv[], Flags *flags);
void readRegexFromFile(Flags *flags);
void searchAndPrintResults(Flags *flags);
void flag_prod(int i, Flags *flags);
void errorFunc(void);
void printResult(FILE *file, Flags *flags, regmatch_t star, regex_t reg, int i);
void setupSearchParameters(Flags *flags, int argc, int optind, char *argv[]);

#endif
