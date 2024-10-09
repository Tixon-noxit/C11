//
// Created by Тихон Чабусов on 09.02.2024.
//

#include "s21_arithmetic_operators.h"

#include "../operators_comparison/s21_operators_comparison.h"

// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_flag = OK, flag_not_null = 0;
  s21_long_decimal res = {0}, new_num = {0}, new_num_2 = {0};
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  int flag_sign = OK;
  if (is_long_decimal_zero(res) || is_long_decimal_zero(new_num)) {
    flag_not_null = 1;
  }

  standardize_long_decimals(&new_num, &res);
  if (bit(res.bits[7], 31) == bit(new_num.bits[7], 31)) {  // знаки равны
    binary_addition_with_carry(new_num, res, &new_num_2);
    new_num_2.bits[7] = res.bits[7];

  } else {
    int mask = MASK_0;
    s21_decimal value_1_copy = {0}, value_2_copy = {0};
    convert_long_decimal_to_decimal_arifmetic(new_num, &value_1_copy);
    convert_long_decimal_to_decimal_arifmetic(res, &value_2_copy);
    mask |= ~(1U << 31);
    value_1_copy.bits[3] &= mask;
    value_2_copy.bits[3] &= mask;
    mask = 0;

    if (bit(new_num.bits[7], 31) == 1) {  // у первого минус
      mask |= ~(1U << 31);
      new_num.bits[7] &= mask;
      flag_sign = TOO_LARGE;
    } else if (bit(res.bits[7], 31) == 1) {  // у второго минус
      mask |= ~(1U << 31);
      res.bits[7] &= mask;
      flag_sign = TOO_SMALL;
    }
    new_num_2.bits[7] = new_num.bits[7];
    if (s21_is_greater(value_1_copy, value_2_copy)) {
      long_integer_subtraction(new_num, res, &new_num_2);
      if (flag_sign == TOO_LARGE) {
        mask = 0;
        mask |= (1U << 31);
        new_num_2.bits[7] |= mask;
      }
    } else if (s21_is_greater(value_2_copy, value_1_copy)) {
      long_integer_subtraction(res, new_num, &new_num_2);
      if (flag_sign == TOO_SMALL) {
        mask = 0;
        mask |= (1U << 31);
        new_num_2.bits[7] |= mask;
      }
    } else if (s21_is_equal(value_1_copy, value_2_copy)) {
      reset_long_decimal(&new_num_2);
      flag_sign = DIVIDE_BY_ZERO;
    }
  }

  if (flag_not_null == 1 && is_long_decimal_zero(new_num_2) == 0 &&
      flag_sign != DIVIDE_BY_ZERO) {
    error_flag = TOO_SMALL;
  }
  convert_long_decimal_to_decimal(&new_num_2, result, &error_flag);
  return (error_flag);
}

// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_flag = OK;
  int flag_not_null = 0;
  s21_long_decimal new_num_2 = {0};
  s21_long_decimal res = {0};
  s21_long_decimal new_num = {0};
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  if (s21_is_not_equal(value_1, value_2)) {
    // int flag_not_null = 0;
    int mask = MASK_0;

    if (is_long_decimal_zero(res) || is_long_decimal_zero(new_num)) {
      flag_not_null = 1;
    }
    standardize_long_decimals(&new_num, &res);
    s21_decimal value_1_false = {0};
    s21_decimal value_2_false = {0};
    convert_long_decimal_to_decimal_arifmetic(new_num, &value_1_false);
    convert_long_decimal_to_decimal_arifmetic(res, &value_2_false);
    if (bit(res.bits[7], 31) != bit(new_num.bits[7], 31)) {  // если не равны
      binary_addition_with_carry(new_num, res, &new_num_2);
      new_num_2.bits[7] =
          new_num.bits[7];  // копируем у вайта, потому что у него нужный знак
    } else {
      if (bit(new_num.bits[7], 31) == 1) {
        if (s21_is_greater_or_equal(value_1_false, value_2_false)) {  // -3 -30
          long_integer_subtraction(res, new_num, &new_num_2);
          new_num_2.bits[7] = new_num.bits[7];
          mask |= ~(1U << 31);
          new_num_2.bits[7] &= mask;
        } else {  // -30 -3
          long_integer_subtraction(new_num, res, &new_num_2);
          new_num_2.bits[7] = new_num.bits[7];
        }
      } else {
        if (s21_is_greater_or_equal(value_1_false, value_2_false)) {  // 30 3
          long_integer_subtraction(new_num, res, &new_num_2);
          new_num_2.bits[7] = new_num.bits[7];
        } else if (is_long_decimal_zero(new_num) &&
                   is_long_decimal_zero(res)) {  // 3 30
          long_integer_subtraction(res, new_num, &new_num_2);
          new_num_2.bits[7] = new_num.bits[7];
          mask |= (1U << 31);
          new_num_2.bits[7] |= mask;
        }
      }
    }
  }
  if ((flag_not_null == 1 && is_long_decimal_zero(new_num_2) == 0) ||
      (compute_ten_scale_value(new_num) > 28) ||
      compute_ten_scale_value(res) > 28) {
    error_flag = TOO_SMALL;
  }

  convert_long_decimal_to_decimal(&new_num_2, result, &error_flag);
  return error_flag;
}

// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result) {  // cделать нормализацию, сокращение степени
  int error_flag = OK;
  s21_long_decimal res = {0};
  s21_long_decimal new_num = {0};
  s21_long_decimal new_num_2 = {0};
  s21_long_decimal buffer_num = {
      0};  // нужен тк в функции суммы невозможно сделать +=
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  if (is_long_decimal_zero(res) && is_long_decimal_zero(new_num)) {
    int one_index = 31, start_index = 0;
    int one_bits = 6, start_bits = 0;
    find_first_set_bit(new_num, &one_index,
                       &one_bits);  // находим старшую единицу
    int iteartions = (one_bits * 32 + one_index + 1);
    for (int i = 0; i < iteartions; i++)
    // one_num2_bits*32 + one_num2_index + 1) -- количество разрядов в числе,
    // на которое мы умножаем
    {
      if (bit(new_num.bits[start_bits], start_index) == 1) {
        binary_addition_with_carry(
            res, new_num_2,
            &buffer_num);  // результат + число нового разряда записываем
        // в буффер
        duplicate_long_decimal(
            &new_num_2,
            buffer_num);  // перезаписываем из буфера в результат
                          // т.е. результат += число
      }
      shift_left_with_carry(&res, 1);  // сдвиг как в умножении в столбик

      if (start_index >= 31) {  // двигаем индекс
        start_index = 0;
        start_bits++;
      } else {
        start_index++;
      }
    }
    int new_scale =
        compute_ten_scale_value(new_num) + compute_ten_scale_value(res);

    modify_decimal_scale(&new_num_2, '+', new_scale, 0);
  }
  change_sign_after_multiplication(&new_num_2, res,
                                   new_num);  // - * - == +; + * - == -
  convert_long_decimal_to_decimal(&new_num_2, result, &error_flag);
  return (error_flag);
}

// Деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_flag = OK;
  s21_long_decimal res = {0};
  s21_long_decimal new_num = {0};
  s21_long_decimal new_num_2 = {0};
  convert_decimal_to_long_decimal(value_1, &new_num);
  convert_decimal_to_long_decimal(value_2, &res);
  if (!is_long_decimal_zero(res))
    error_flag = DIVIDE_BY_ZERO;
  else {
    s21_long_decimal buff = {0};
    s21_long_decimal buff_one = {0};
    s21_long_decimal buff_two = {0};
    s21_long_decimal buff_result = {0};  // буферная для сложения деления
                                         // остатка
    int new_scale = 0;
    if (compute_ten_scale_value(new_num) >= compute_ten_scale_value(res))
      new_scale =
          compute_ten_scale_value(new_num) - compute_ten_scale_value(res);
    else {
      while (compute_ten_scale_value(new_num) != compute_ten_scale_value(res)) {
        add_ten_to_long_decimal(&new_num);
      }
    }
    modify_decimal_scale(&new_num_2, '+', new_scale, 0);
    long_decimal_divide_with_remainder(new_num, res, &new_num_2, &buff);

    while (is_long_decimal_zero(buff) && new_scale < 28 && buff.bits[3] == 0) {
      reset_long_decimal(&buff_two);
      add_ten_to_long_decimal(&buff);
      duplicate_long_decimal(&buff_two, buff);
      reset_long_decimal(&buff);
      reset_long_decimal(&buff_one);
      long_decimal_divide_with_remainder(buff_two, res, &buff_one, &buff);
      add_ten_to_long_decimal(&new_num_2);
      binary_addition_with_carry(new_num_2, buff_one, &buff_result);
      reset_long_decimal(&new_num_2);
      duplicate_long_decimal(&new_num_2, buff_result);
      new_scale += 1;
      modify_decimal_scale(&new_num_2, '+', new_scale, 0);
    }

    if (bit(new_num.bits[7], 31) != bit(res.bits[7], 31)) {
      int mask = MASK_0;
      mask |= 1U << 31;
      new_num_2.bits[7] |= mask;
    }
  }
  convert_long_decimal_to_decimal(&new_num_2, result, &error_flag);

  return (error_flag);
}

void long_decimal_divide_with_remainder(
    s21_long_decimal value_1, s21_long_decimal value_2,
    s21_long_decimal *result,
    s21_long_decimal *buff) {  // записывает целое в result, остаток в buff
  s21_long_decimal buff_sub = {0};
  s21_decimal buff_false = {0};
  s21_decimal value_2_false = {0};
  convert_long_decimal_to_decimal_arifmetic(
      value_2, &value_2_false);  // для сравнения в нормальный децимал
  value_2_false.bits[3] &= 0;
  int index = 31, bits_index = 6;
  if (find_first_set_bit(value_1, &index, &bits_index)) {
    while (bits_index >= 0) {
      shift_left_with_carry(buff, 1);
      buff->bits[0] += bit(value_1.bits[bits_index], index);
      convert_long_decimal_to_decimal_arifmetic(*buff, &buff_false);
      if (s21_is_less(buff_false, value_2_false)) {
        shift_left_with_carry(result, 1);
      } else {
        shift_left_with_carry(result, 1);
        result->bits[0] += 1;
        reset_long_decimal(&buff_sub);
        long_integer_subtraction(
            *buff, value_2,
            &buff_sub);  // записываем буферный результат вычитания
        reset_long_decimal(buff);
        duplicate_long_decimal(buff, buff_sub);
      }
      if (index <= 0) {
        index = 31;
        bits_index--;
      } else {
        index--;
      }
    }
  }
}
