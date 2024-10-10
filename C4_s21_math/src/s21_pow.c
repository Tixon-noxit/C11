//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_pow(double base, double exp) {
  ld result = 0;
  if (s21_fabs(exp) < S21_EPS) {
    result = 1;
  } else if (s21_fabs(base - 1) < S21_EPS) {
    result = 1;
  } else if (s21_fabs(base + 1) < S21_EPS && s21_fabs(exp) == S21_POS_INF) {
    result = 1;
  } else if (base < 0 && base > S21_NEG_INF && exp != s21_ceil(exp)) {
    result = S21_NAN;
  } else if (base < 0) {
    base = -base;
    if (exp * s21_log(base) < -16)
      result = 0;
    else {
      result = s21_exp(exp * s21_log(base));
      if (s21_fmod(exp, 2.) != 0) result = -result;
    }
  } else {
    if (exp * s21_log(base) < -16)
      result = 0;
    else
      result = s21_exp(exp * s21_log(base));
  }
  if (result == S21_NEG_INF) result = -result;
  return result;
}
