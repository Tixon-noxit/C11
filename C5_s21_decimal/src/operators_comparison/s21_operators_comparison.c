//
// Created by Тихон Чабусов on 09.02.2024.
//

#include "s21_operators_comparison.h"

// Меньше
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int error_flag = OK;  // 1 - первое меньше, 0 - не меньше))
  int flag_equel = OK;
  s21_long_decimal res = {0};
  s21_long_decimal new_num = {0};
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  standardize_long_decimals(&new_num, &res);
  int bits_index = 6;
  int index = 31;
  if (bit(res.bits[7], 31) < bit(new_num.bits[7], 31))
    error_flag = TOO_LARGE;
  else if (bit(res.bits[7], 31) == bit(new_num.bits[7], 31)) {
    while (!(bits_index == 0 && index == 0) && (flag_equel == OK)) {
      if (index <= 0) {
        index = 31;
        bits_index--;
      } else {
        index--;
      }
      if (bit(res.bits[bits_index], index) !=
          bit(new_num.bits[bits_index], index)) {
        flag_equel = TOO_LARGE;
        if (bit(res.bits[bits_index], index) >
            bit(new_num.bits[bits_index], index)) {
          error_flag = TOO_LARGE;
        }
      }
    }
    if (bit(res.bits[7], 31) == bit(new_num.bits[7], 31) &&
        bit(new_num.bits[7], 31) == 1 && flag_equel != OK) {
      error_flag = !error_flag;
    }
  }
  return error_flag;
}

// Меньше или равно
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int error_flag = OK;
  if (s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2))
    error_flag = TOO_LARGE;
  return error_flag;
}

// Больше
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int error_flag = OK;
  if (!s21_is_less_or_equal(value_1, value_2)) error_flag = TOO_LARGE;
  return error_flag;
}

// Больше или равно
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int error_flag = OK;
  if (!s21_is_less(value_1, value_2)) error_flag = TOO_LARGE;
  return error_flag;
}

// Равно
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal res = {0};
  s21_long_decimal new_num = {0};
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  standardize_long_decimals(&new_num, &res);
  int bits_index = 6;
  int index = 31;
  int error_flag = TOO_LARGE;
  if (!is_long_decimal_zero(new_num) && !is_long_decimal_zero(res))
    error_flag = TOO_LARGE;
  else if ((bit(res.bits[7], 31) != bit(new_num.bits[7], 31)))
    error_flag = OK;  // проверка на знак
  while (!(bits_index == 0 && index == 0) && (error_flag == TOO_LARGE)) {
    if (index <= 0) {
      index = 31;
      bits_index--;
    } else {
      index--;
    }
    if (bit(res.bits[bits_index], index) !=
        bit(new_num.bits[bits_index], index))
      error_flag = OK;
  }
  return error_flag;
}

// Не равно
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) ? OK : TOO_LARGE;
}