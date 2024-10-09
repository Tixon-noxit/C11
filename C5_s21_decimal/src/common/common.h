//
// Created by Тихон Чабусов on 09.02.2024.
//

#ifndef MY_DECIMAL_COMMON_H
#define MY_DECIMAL_COMMON_H

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NORMAL_POINT_MAX 28

#define WORD_BITS 32
#define WORD_SIZE 4

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK_0 0b00000000000000000000000000000000
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define SCALE 0x00ff0000
#define MINUS 0x80000000

#define ZERO_DECIMAL 0b00000000000000000000000000000000

#define OK 0         // - OK
#define TOO_LARGE 1  // - число слишком велико или равно бесконечности
#define TOO_SMALL \
  2  // - число слишком мало или равно отрицательной бесконечности
#define DIVIDE_BY_ZERO 3  // - деление на 0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_long_decimal;

void s21_decimal_zero(s21_decimal *result);

int is_decimal_zero(s21_decimal val);

void printBits(s21_decimal s);

int is_integer_s21_decimal(s21_decimal num);

int get_diff_sign(s21_decimal value_1, s21_decimal value_2);

// unsigned int get_scale(s21_decimal val); // +
void set_scale(s21_decimal *val, unsigned int scale);  // +

unsigned int get_sign(s21_decimal val);

void set_sign(s21_decimal *number, int sign);

void copy_s21_decimal(const s21_decimal *source, s21_decimal *destination);

int count_decimal_places(float floatValue);

int is_normal_point(s21_decimal p);

void long_integer_subtraction(s21_long_decimal value_1,
                              s21_long_decimal value_2,
                              s21_long_decimal *result);

void change_sign_after_multiplication(s21_long_decimal *result,
                                      s21_long_decimal num1,
                                      s21_long_decimal num2);

int binary_addition_with_carry(s21_long_decimal value_1,
                               s21_long_decimal value_2,
                               s21_long_decimal *result);

int bit(int binary_num, int digit);

int copy_decimal_to_long_decimal(int a, int b);

void convert_decimal_to_long_decimal(s21_decimal num,
                                     s21_long_decimal *new_num);

void shift_left_with_carry(s21_long_decimal *num, int move);

int find_first_set_bit(s21_long_decimal num, int *index, int *bits_index);

void subtract_ten_from_long_decimal(s21_long_decimal *num);

void add_ten_to_long_decimal(s21_long_decimal *num);

void duplicate_long_decimal(s21_long_decimal *destination,
                            s21_long_decimal source);

void duplicate_decimal(s21_decimal *destination, s21_decimal source);

void reset_long_decimal(s21_long_decimal *val);

int compute_ten_scale_value(s21_long_decimal val);

void standardize_long_decimals(s21_long_decimal *val, s21_long_decimal *val2);

void modify_decimal_scale(s21_long_decimal *number, char operation,
                          int scale_change_amount, int current_scale);

void convert_long_decimal_to_decimal_arifmetic(s21_long_decimal source,
                                               s21_decimal * false);

int is_long_decimal_zero(s21_long_decimal num);

int generalized_check(s21_decimal num);

void convert_long_decimal_to_decimal(s21_long_decimal *source,
                                     s21_decimal *destination, int *error_flag);

void convert_long_decimal_to_decimal_with_error_handling(
    s21_long_decimal *source, s21_decimal *destination, int *error_flag);

int set_decimal_scale(s21_decimal *value, int scale);

int determine_bank_rounding(s21_long_decimal num);

#endif  // MY_DECIMAL_COMMON_H
