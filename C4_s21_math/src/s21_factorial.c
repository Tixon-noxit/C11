//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_factorial(long i) {
  ld result = 1.0L;
  if (i > 0) {
    for (long d = i; d >= 1; d--) {
      result *= d;
    }
  }
  return result;
}
