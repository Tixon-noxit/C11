//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_log(double x) {
  ld result = 0;
  if (x < 0)
    result = S21_NAN;
  else if (x == 0)
    result = S21_NEG_INF;
  else if (x > S21_DBL_MAX)
    result = S21_POS_INF;
  else {
    int r = 0;
    for (; x >= S21_E; r++) x /= S21_E;
    for (int i = 0; i < 1 << 7; i++) {
      result = result + 2 * (x - s21_exp((double)result)) /
                            (x + s21_exp((double)result));
    }
    result += r;
  }
  return result;
}
