//
// Created by Тихон Чабусов on 09.02.2024.
//

#include "s21_other_features.h"

// Возвращает результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = generalized_check(value);
  s21_long_decimal result_buff = {0};
  if (flag == 0) {
    convert_decimal_to_long_decimal(value, &result_buff);
    for (int i = 0; i <= 3; i++) {
      result->bits[i] = MASK_0;
    }
    duplicate_decimal(result, value);
    int sign = bit(result_buff.bits[7], 31);
    if (sign == 0) {
      int mask = MASK_0;
      mask = (1U << 31);
      result->bits[3] |= mask;
    } else {
      int mask = MASK_0;
      mask = ~(1U << 31);
      result->bits[3] &= mask;
    }
  }
  return flag;
}

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = generalized_check(value);
  s21_long_decimal buff = {0};
  if (flag == 0) {
    for (int i = 0; i <= 3; i++) {
      result->bits[i] = MASK_0;
    }
    convert_decimal_to_long_decimal(value, &buff);
    while (compute_ten_scale_value(buff) > 0) {
      subtract_ten_from_long_decimal(&buff);
    }
  }
  convert_long_decimal_to_decimal_arifmetic(buff, result);
  return flag;
}

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = generalized_check(value);
  s21_long_decimal result_long = {0};
  if (flag == 0) {
    int flag_floor = 0;
    s21_long_decimal buff = {0};
    s21_long_decimal buff_of_buff = {0};
    convert_decimal_to_long_decimal(value, &buff);
    convert_decimal_to_long_decimal(value, &buff_of_buff);
    while (compute_ten_scale_value(buff) > 0) {
      reset_long_decimal(&result_long);
      subtract_ten_from_long_decimal(&buff_of_buff);
      add_ten_to_long_decimal(&buff_of_buff);
      long_integer_subtraction(buff, buff_of_buff, &result_long);
      if (is_long_decimal_zero(result_long)) {
        flag_floor = 1;
      }
      subtract_ten_from_long_decimal(&buff);
    }
    reset_long_decimal(&result_long);
    if (flag_floor == 1 && bit(buff.bits[7], 31) == 1) {
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      binary_addition_with_carry(buff, one, &result_long);
      result_long.bits[7] = buff.bits[7];
    } else

      duplicate_long_decimal(&result_long, buff);
    for (int i = 0; i <= 3; i++) {
      result->bits[i] = MASK_0;
    }
  }
  convert_long_decimal_to_decimal_with_error_handling(&result_long, result,
                                                      &flag);
  return flag;
}

// Округляет Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = generalized_check(value);
  s21_long_decimal result_long = {0};
  if (flag == 0) {
    s21_long_decimal buff = {0};
    s21_long_decimal buff_of_buff = {0};
    convert_decimal_to_long_decimal(value, &buff);
    convert_decimal_to_long_decimal(value, &buff_of_buff);
    while (compute_ten_scale_value(buff) > 0) {
      reset_long_decimal(&result_long);
      subtract_ten_from_long_decimal(&buff_of_buff);
      add_ten_to_long_decimal(&buff_of_buff);
      long_integer_subtraction(buff, buff_of_buff, &result_long);
      subtract_ten_from_long_decimal(&buff);
      subtract_ten_from_long_decimal(&buff_of_buff);
    }
    int sub_value = result_long.bits[0];
    reset_long_decimal(&result_long);
    if ((sub_value == 5 && bit(buff.bits[0], 0) == 1) || sub_value > 5) {
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      binary_addition_with_carry(buff, one, &result_long);
      result_long.bits[7] = buff.bits[7];
    } else

      duplicate_long_decimal(&result_long, buff);
    for (int i = 0; i <= 3; i++) {
      result->bits[i] = MASK_0;
    }
  }
  convert_long_decimal_to_decimal_with_error_handling(&result_long, result,
                                                      &flag);
  return flag;
}