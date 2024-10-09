//
// Created by Тихон Чабусов on 09.02.2024.
//

#include "./s21_converters.h"

// Из int в s21_decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i <= 3; i++) {
    dst->bits[i] = MASK_0;
  }

  if (src < 0) {
    dst->bits[3] = (1U << 31);  // Установка знака на 1
    dst->bits[0] = -src;  // Присвоение абсолютного значения src
  } else {
    dst->bits[0] = src;
  }

  return OK;
}

// Из s21_decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_long_decimal buff = {0};
  convert_decimal_to_long_decimal(src, &buff);
  while (compute_ten_scale_value(buff) > 0) {
    subtract_ten_from_long_decimal(&buff);
  }
  int flag = OK;
  for (int i = 6; i > 0; i--) {
    if (buff.bits[i] != 0) {
      flag = TOO_LARGE;
    }
  }
  if (flag == OK) {
    *dst = buff.bits[0];
    if (bit(buff.bits[7], 31) == 1) {
      *dst = (*dst) * (-1);
    }
  }
  return flag;
}

// Из float в s21_decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = OK;
  if (isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL) error = TOO_LARGE;
  if (dst && !error) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = fabs(src);
    }
    int temp = (int)src;
    int scale = 0;
    while (src - ((float)temp / (int)(pow(10, scale))) != 0) {
      scale++;
      temp = src * (int)(pow(10, scale));
    }
    s21_from_int_to_decimal(temp, dst);
    if (sign) s21_negate(*dst, dst);  // *-1
    set_decimal_scale(dst, scale);
  } else {
    error = TOO_LARGE;
  }
  return error;
}

// Из s21_decimal в float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_flag = OK;
  s21_long_decimal buff = {0};
  convert_decimal_to_long_decimal(src, &buff);
  float num_0 = (float)src.bits[0];
  float num_1 = (float)src.bits[1] * pow(2.0, 32.0);
  float num_2 = (float)src.bits[2] * pow(2.0, 64.0);
  float sign = 1.0;
  if (bit(src.bits[3], 31)) {
    sign *= -1.0;
  }
  int compute_ten_scale_value_buff = compute_ten_scale_value(buff);
  if (compute_ten_scale_value_buff >
      28) {  // проверка корректного ввода степени
    error_flag = TOO_LARGE;
  } else {
    *dst = sign * (num_0 + num_1 + num_2) *
           powf(10, -compute_ten_scale_value_buff);
  }
  return (error_flag);
}
