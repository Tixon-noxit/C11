//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_fmod(double x, double y) {
  int mod = (int)(x / y);
  long double res = (long double)x - mod * (long double)y;
  return res;
}