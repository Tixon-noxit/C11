//
// Created by Тихон Чабусов on 09.02.2024.
//

#ifndef MY_DECIMAL_S21_ARITHMETIC_OPERATORS_H
#define MY_DECIMAL_S21_ARITHMETIC_OPERATORS_H

#include <assert.h>

#include "../common/common.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void long_decimal_divide_with_remainder(s21_long_decimal value_1,
                                        s21_long_decimal value_2,
                                        s21_long_decimal *result,
                                        s21_long_decimal *buff);

#endif  // MY_DECIMAL_S21_ARITHMETIC_OPERATORS_H
