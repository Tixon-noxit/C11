//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_ceil(double x) {
  ld result;
  if ((x == S21_POS_INF || x == S21_NEG_INF)) {
    result = x;
  } else {
    result = (long long int)x;
    if (s21_fabs(x) > 0 && x != result) {
      if (x != S21_DBL_MAX) {
        if (x > 0) result++;
      } else {
        result = S21_DBL_MAX;
      }
    }
  }

  if (x != x) result = S21_NAN;

  return result;
}