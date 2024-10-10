//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_atan(double x) {
  int n = 0;
  long double atan = 0.0;
  if (x < -S21_DBL_MAX) {
    atan = -S21_PI_2;
  } else if (x > S21_DBL_MAX) {
    atan = S21_PI_2;
  } else if (s21_fabs(x - 1) < S21_EPS) {
    atan = 0.7853982;
  } else if (s21_fabs(x + 1) < S21_EPS) {
    atan = -0.7853982;
  } else {
    if (x > -1 && x < 1) atan = 0;
    if (x > 1) atan = S21_PI_2;
    if (x < -1) atan = -S21_PI_2;
    long double term = 1;
    while (s21_fabs(term) > S21_EPS) {
      if ((x > -1 && x < 1)) {
        term = s21_pow(-1, n) / (2 * n + 1) * s21_pow(x, 2 * n + 1);
        atan += term;
      } else {
        term = s21_pow(-1, n) / (2 * n + 1) * s21_pow(x, -2 * n - 1);
        atan -= term;
      }
      n++;
    }
  }
  return atan;
}