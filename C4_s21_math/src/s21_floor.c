//
// Created by adis on 06.01.2024.
//

#include "s21_math.h"

long double s21_floor(double x) { return -s21_ceil(-x); }