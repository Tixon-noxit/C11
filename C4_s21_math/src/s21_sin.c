//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"
long double s21_sin(double x) {
  ld sin;
  if (s21_fabs(x) == S21_POS_INF || x == S21_NAN)
    sin = S21_NAN;
  else
    sin = s21_cos(x - S21_PI_2);
  return sin;
}