//
// Created by Тихон Чабусов on 09.02.2024.
//

#ifndef MY_DECIMAL_S21_OPERATORS_COMPARISON_H
#define MY_DECIMAL_S21_OPERATORS_COMPARISON_H

#include "../common//common.h"

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

#endif  // MY_DECIMAL_S21_OPERATORS_COMPARISON_H
