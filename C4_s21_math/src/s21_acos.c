//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_acos(double x) {
  long double acos = 10;
  if (x >= -1 && x <= 1)
    acos = S21_PI_2 - s21_asin(x);
  else
    acos = S21_NAN;
  return acos;
}