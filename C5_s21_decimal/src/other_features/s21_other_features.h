//
// Created by Тихон Чабусов on 09.02.2024.
//

#ifndef MY_DECIMAL_S21_OTHER_FEATURES_H
#define MY_DECIMAL_S21_OTHER_FEATURES_H

#include "../arithmetic_operators/s21_arithmetic_operators.h"
#include "../common/common.h"
#include "../converters/s21_converters.h"

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

#endif  // MY_DECIMAL_S21_OTHER_FEATURES_H
