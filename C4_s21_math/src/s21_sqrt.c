//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

// long double s21_pow_int(double x, int n) {
//     if (n == 0) {
//         return 1.0L;  // Любое число в степени 0 равно 1
//     } else if (n > 0) {
//         long double result = 1.0L;
//         for (int i = 0; i < n; i++) {
//             result *= x;
//         }
//         return result;
//     } else {
//         return 1.0L / s21_pow_int(x, -n);
//     }
// }

long double s21_sqrt(double x) {
  ld result = 0;
  if (x < 0)
    result = S21_NAN;
  else
    result = s21_pow(x, 0.5);
  return result;
}