//
// Created by adis on 06.01.2024.
//
#include "s21_math.h"

long double s21_tan(double x) {
  ld tan;
  if (s21_fabs(s21_cos(x)) < S21_EPS && s21_sin(x) > 0)
    tan = S21_POS_INF;
  else if (s21_fabs(s21_cos(x)) < S21_EPS && s21_sin(x) < 0)
    tan = S21_NEG_INF;
  else
    tan = s21_sin(x) / s21_cos(x);
  return tan;
}