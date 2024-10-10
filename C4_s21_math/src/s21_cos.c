//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_cos(double x) {
  ld result = 0;
  if (s21_fabs(x) == S21_POS_INF || x == S21_NAN) {
    result = S21_NAN;
  } else {
    x = s21_fmod(x, 2 * S21_PI);
    int i = 0;
    long double term = 1;
    while (s21_fabs((double)term) > S21_EPS) {
      term = s21_pow(-1, i) / s21_factorial(2 * i) * s21_pow(x, 2 * i);
      result += term;
      i++;
    }
  }
  return result;
}