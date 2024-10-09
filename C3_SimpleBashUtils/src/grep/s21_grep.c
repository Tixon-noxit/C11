#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flags flags = {0};
  check_flag(argc, argv, &flags);
  searchAndPrintResults(&flags);
}
