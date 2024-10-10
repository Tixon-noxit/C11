//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_exp(double x) {
  ld result = 1;
  int negative = 0;
  if (s21_fabs(x) < S21_EPS)
    result = 1;
  else if (x == S21_NEG_INF)
    result = 0;
  else if (x < -38)
    result = 0;
  else if (x > 308)
    result = S21_POS_INF;
  else {
    if (x < 0) {
      negative = 1;
      x = -x;
    }
    long long int x_int = (ld)(x / S21_LN2);
    if (x_int > 63) x_int = 63;
    ld x_rest = x - x_int * S21_LN2;

    long long int exp = 1;
    ld term = 1;
    int i = 1;

    while (s21_fabs(term) > S21_EPS) {
      term *= x_rest / i;
      result += term;
      i++;
    }
    exp = ((exp) << x_int);

    result *= exp;
    if (negative == 1) result = 1. / result;
  }
  return result;
}