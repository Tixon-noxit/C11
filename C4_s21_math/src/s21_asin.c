//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"
long double s21_asin(double x) {
  long double asin;
  if (x >= -1 && x <= 1) {
    asin = s21_atan(x / s21_pow(1 - x * x, 0.5));
  } else {
    asin = S21_NAN;
  }
  return asin;
}
