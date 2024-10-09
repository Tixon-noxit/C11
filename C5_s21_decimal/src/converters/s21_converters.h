//
// Created by Тихон Чабусов on 09.02.2024.
//

#ifndef MY_DECIMAL_S21_CONVERTERS_H
#define MY_DECIMAL_S21_CONVERTERS_H

#include "../common/common.h"
#include "../other_features/s21_other_features.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

#endif  // MY_DECIMAL_S21_CONVERTERS_H
