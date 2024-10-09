//
// Created by Тихон Чабусов on 09.02.2024.
//

#include "common.h"

// вычитания между двумя s21_long_decimal (длинными целыми числами)
void long_integer_subtraction(s21_long_decimal value_1,
                              s21_long_decimal value_2,
                              s21_long_decimal *result) {
  s21_long_decimal value_1_buff = {0};
  duplicate_long_decimal(&value_1_buff, value_1);
  s21_long_decimal value_2_buff = {0};
  duplicate_long_decimal(&value_2_buff, value_2);
  for (int bits_index = 0; bits_index < 7; bits_index++) {
    for (int index = 0; index < 32; index++) {
      int value_1_bit = bit(value_1_buff.bits[bits_index], index);
      int value_2_bit = bit(value_2_buff.bits[bits_index], index);
      if (value_1_bit >= value_2_bit) {
        result->bits[bits_index] |= (value_1_bit - value_2_bit) << index;
      } else {
        int buff_index = index;
        int buff_bits_index = bits_index;
        int one_was_found = 0;
        while (one_was_found == 0) {  // добавить индекс меньше 7
          if (buff_index >= 31) {
            buff_index = 0;
            buff_bits_index++;
          } else {
            buff_index++;
          }
          if (bit(value_1_buff.bits[buff_bits_index], buff_index) == 1) {
            int mask = MASK_0;
            one_was_found = 1;
            mask |= ~(1U << buff_index);
            value_1_buff.bits[buff_bits_index] &= mask;

            while (!((buff_bits_index == bits_index) &&
                     (buff_index == index))) {  //  в обратную сторону
              if (buff_index <= 0) {
                buff_index = 31;
                buff_bits_index--;
              } else {
                buff_index--;
              }
              mask &= MASK_0;
              mask |= (1U << buff_index);
              value_1_buff.bits[buff_bits_index] |= mask;
            }
            result->bits[bits_index] |= 1U << index;
          }
        }
      }
    }
  }
}

// умножение s21_long_decimal
void change_sign_after_multiplication(s21_long_decimal *result,
                                      s21_long_decimal num1,
                                      s21_long_decimal num2) {
  int sign_bit_num1 = bit(num1.bits[7], 31);
  int sign_bit_num2 = bit(num2.bits[7], 31);
  if (sign_bit_num1 != sign_bit_num2) {
    unsigned int mask = MASK_0;
    mask |= (1U << 31);
    result->bits[7] |= mask;
  } else {
    unsigned int mask = MASK_0;
    mask |= ~(1U << 31);
    result->bits[7] &= mask;
  }
}

// сложение
int binary_addition_with_carry(s21_long_decimal value_1,
                               s21_long_decimal value_2,
                               s21_long_decimal *result) {
  int digit_buff = 0;  // запоминаем в след разряд
  for (int bits_index = 0; bits_index < 7; bits_index++) {
    result->bits[bits_index] = MASK_0;
    for (int index = 0; index < 32; index++) {
      int value_1_bit =
          bit(value_1.bits[bits_index], index);  // находим соот разряду биты
      int value_2_bit =
          bit(value_2.bits[bits_index], index);  // спасибо за апдейт
      result->bits[bits_index] +=
          (digit_buff ? !copy_decimal_to_long_decimal(value_1_bit, value_2_bit)
                      : copy_decimal_to_long_decimal(value_1_bit, value_2_bit))
          << index;

      if (value_1_bit + value_2_bit + digit_buff >= 2) {
        digit_buff = 1;
      } else {
        digit_buff = 0;
      }
    }
  }
  return TOO_LARGE;
}

// извлекает бит из числа binary_num extract_bit
int bit(int binary_num, int digit) {  // bit(1000100, 2) == 1
  int result = 1 & (binary_num >> (digit % 32));
  return (result);
}

// исключающее ИЛИ между двумя битами
int copy_decimal_to_long_decimal(int a, int b) {
  int result = (a | b) & (!(a & b));
  return (result);
}

// копирует s21_decimal в s21_long_decimal
void convert_decimal_to_long_decimal(s21_decimal num,
                                     s21_long_decimal *new_num) {
  new_num->bits[0] = num.bits[0];
  new_num->bits[1] = num.bits[1];
  new_num->bits[2] = num.bits[2];
  for (int i = 3; i < 7; i++) {
    new_num->bits[i] = MASK_0;
  }
  new_num->bits[7] = num.bits[3];
}

// сдвига влево на n bit
void shift_left_with_carry(s21_long_decimal *num, int move) {
  for (int bits_index = 6; bits_index >= 0; bits_index--) {
    for (int index = 31; index >= 0; index--) {
      if ((bits_index + (index + move) / 32) <= 6) {
        int from = bit(num->bits[bits_index], index);  // otkuda
        int to = bit(num->bits[bits_index + (index + move) / 32],
                     (index + move) % 32);  // kuda
        if (from != to) {
          unsigned int mask = MASK_0;
          if (to == 0) {
            mask |= (1U << (index + move) % 32);
            num->bits[bits_index + (index + move) / 32] |= mask;
          } else {
            mask |= ~(1U << (index + move) % 32);
            num->bits[bits_index + (index + move) / 32] &= mask;
          }
        }
      }
      int null_mask = MASK_0;
      null_mask |= ~(1 << index);
      num->bits[bits_index] &= null_mask;
    }
  }
}
//

// обновление значения index
int find_first_set_bit(s21_long_decimal num, int *index, int *bits_index) {
  int flag = OK;
  if (is_long_decimal_zero(num)) {
    flag = TOO_LARGE;
    while (bit(num.bits[*bits_index], *index) != 1) {
      if ((*index) <= 0) {
        (*index) = 31;
        (*bits_index)--;
      } else {
        (*index)--;
      }
    }
  }
  return (flag);
}

// вычитания десяти из числа типа s21_long_decimal
void subtract_ten_from_long_decimal(s21_long_decimal *num) {  //  / 1010
  int index = 31, bits_index = 6;
  s21_long_decimal result = {0};
  // int buff = 0;  // число из которого мы вычитали
  modify_decimal_scale(num, '-', 1, compute_ten_scale_value(*num));
  if (find_first_set_bit(*num, &index, &bits_index)) {  // находим единицу
    int buff = 0;  // число из которого мы вычитали
    result.bits[7] = num->bits[7];
    while (bits_index >= 0) {  // пока не дошли до конца
      buff *= 2;  // еще один бит для записи 1 или 0
      buff += bit(num->bits[bits_index], index);  // записываем
      if (buff < 10) {
        shift_left_with_carry(
            &result,
            1);  // сдвиг, а, свдиг если числа не хватает для вычитания походу
      } else {
        shift_left_with_carry(&result, 1);
        result.bits[0] += 1;
        buff -= 10;
      }
      if (index <= 0) {
        index = 31;
        bits_index--;
      } else {
        index--;
      }
    }
    reset_long_decimal(num);
    duplicate_long_decimal(num, result);
  }
}

// увеличивает число типа s21_long_decimal на десять
void add_ten_to_long_decimal(s21_long_decimal *num) {
  s21_long_decimal ten = {0};
  s21_long_decimal thousand = {0};
  int seven_bit = num->bits[7];
  duplicate_long_decimal(&ten, *num);
  duplicate_long_decimal(&thousand, *num);
  shift_left_with_carry(&ten, 1);
  shift_left_with_carry(&thousand, 3);
  binary_addition_with_carry(ten, thousand, num);
  num->bits[7] = seven_bit;
  modify_decimal_scale(num, '+', 1, compute_ten_scale_value(*num));
}

// копирует содержимое одного длинного десятичного числа (source) в другое
// (destination)
void duplicate_long_decimal(s21_long_decimal *destination,
                            s21_long_decimal source) {
  reset_long_decimal(destination);
  for (int i = 0; i <= 7; i++) {
    destination->bits[i] |= source.bits[i];
  }
}

// копирует содержимое одного десятичного числа (source) в другое (destination)
void duplicate_decimal(s21_decimal *destination, s21_decimal source) {
  for (int i = 0; i <= 3; i++) {
    destination->bits[i] |= source.bits[i];
  }
}

// зануление s21_long_decimal
void reset_long_decimal(s21_long_decimal *val) {
  for (int i = 0; i <= 7; i++) {
    val->bits[i] = MASK_0;
  }
}

// выявление показателя степени s21_long_decimal
int compute_ten_scale_value(s21_long_decimal val) {
  int buff = 0;
  for (int i = 23; i >= 16; i--) {
    buff *= 2;
    buff += bit(val.bits[7], i);
  }
  return (buff);
}

// нормализация s21_long_decimal
void standardize_long_decimals(s21_long_decimal *val, s21_long_decimal *val2) {
  int val_1 = compute_ten_scale_value(*val);
  int val_2 = compute_ten_scale_value(*val2);
  if (val_1 > 28) {
    for (int i = 0; i < val_1 - 28; i++) {
      subtract_ten_from_long_decimal(val);
    }
    val_1 = 28;
  }
  if (val_2 > 28) {
    for (int i = 0; i < val_2 - 28; i++) {
      subtract_ten_from_long_decimal(val2);
    }
    val_2 = 28;
  }
  while (val_1 != val_2) {
    if (val_1 > val_2) {
      add_ten_to_long_decimal(val2);
      val_2++;
    } else {
      add_ten_to_long_decimal(val);
      val_1++;
    }
  }
}

// изменение степени s21_long_decimal
void modify_decimal_scale(s21_long_decimal *number, char operation,
                          int scale_change_amount, int current_scale) {
  if (operation == '+') current_scale += scale_change_amount;
  if (operation == '-') current_scale -= scale_change_amount;
  for (int i = 16; i <= 23; i++) {
    unsigned int mask = MASK_0;
    mask |= ~(1U << i);
    number->bits[7] &= mask;
    number->bits[7] |= (bit(current_scale, i - 16) << i);
  }
}

// преобразование s21_long_decimal в s21_decimal
void convert_long_decimal_to_decimal_arifmetic(s21_long_decimal source,
                                               s21_decimal * false) {
  false->bits[0] = source.bits[0];
  false->bits[1] = source.bits[1];
  false->bits[2] = source.bits[2];
  false->bits[3] = source.bits[7];
}

// проверка что s21_long_decimal пустое
int is_long_decimal_zero(s21_long_decimal num) {
  int is_null = TOO_LARGE;
  if (num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0 &&
      num.bits[3] == 0 && num.bits[4] == 0 && num.bits[5] == 0 &&
      num.bits[6] == 0) {
    is_null = OK;
  }
  return (is_null);
}

// Проверки по основным критериям
int generalized_check(s21_decimal num) {
  int flag = OK;
  s21_long_decimal buff = {0};
  convert_decimal_to_long_decimal(num, &buff);
  if (compute_ten_scale_value(buff) > 28)
    flag = TOO_LARGE;  // проверка на корректную степень
  for (int i = 0; i < 16; i++) {  // проверка на младшее слово
    if (bit(buff.bits[7], i) == 1) {
      flag = TOO_LARGE;
    }
  }
  for (int i = 24; i < 31; i++) {  // проверка на младшее слово
    if (bit(buff.bits[7], i) == 1) {
      flag = TOO_LARGE;
    }
  }
  return flag;
}

// преобразует s21_long_decimal в s21_decimal
void convert_long_decimal_to_decimal(
    s21_long_decimal *source, s21_decimal *destination,
    int *error_flag) {  // cделать compute_ten_scale_value >28
  int flag_null = is_long_decimal_zero(*source);  // изначально не ноль?
  while (compute_ten_scale_value(*source) > 28)  // проверка на малое
  {
    if (determine_bank_rounding(*source) == 1) {
      subtract_ten_from_long_decimal(source);
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_long_decimal result_long = {0};
      result_long.bits[7] = source->bits[7];
      binary_addition_with_carry(*source, one, &result_long);
      reset_long_decimal(source);
      duplicate_long_decimal(source, result_long);
    } else
      subtract_ten_from_long_decimal(source);
  }
  if (is_long_decimal_zero(*source) != flag_null)
    *error_flag = TOO_SMALL;  // число обратилось в ноль
  while ((source->bits[3] > 0 ||  // 32-ой бит может быть знаком, так что можно
                                  // нарваться на исключение
          source->bits[4] > 0 || source->bits[5] > 0 || source->bits[6] > 0) &&
         compute_ten_scale_value(*source) > 0) {
    if (determine_bank_rounding(*source) == 1) {
      subtract_ten_from_long_decimal(source);
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_long_decimal result_long = {0};
      result_long.bits[7] = source->bits[7];
      binary_addition_with_carry(*source, one, &result_long);
      reset_long_decimal(source);
      duplicate_long_decimal(source, result_long);
    } else
      subtract_ten_from_long_decimal(source);
  }

  if ((source->bits[3] > 0 || source->bits[4] > 0 || source->bits[5] > 0 ||
       source->bits[6] > 0) &&
      compute_ten_scale_value(*source) == 0) {
    if (bit(source->bits[7], 31) == 0) {
      *error_flag = TOO_LARGE;  // число слишком большое
    } else {
      *error_flag = TOO_SMALL;
    }
  }
  if (*error_flag > OK) {  // если код ошибки
    destination->bits[0] = 0;
    destination->bits[1] = 0;
    destination->bits[2] = 0;
    destination->bits[3] = 0;
  } else {
    destination->bits[0] = source->bits[0];
    destination->bits[1] = source->bits[1];
    destination->bits[2] = source->bits[2];
    destination->bits[3] = source->bits[7];
  }
}

// преобразование s21_decimal в int
void convert_long_decimal_to_decimal_with_error_handling(
    s21_long_decimal *source, s21_decimal *destination,
    int *error_flag) {  // cделать compute_ten_scale_value >28
  int flag_null = is_long_decimal_zero(*source);
  while (compute_ten_scale_value(*source) > 28) {
    subtract_ten_from_long_decimal(source);
  }
  if (is_long_decimal_zero(*source) != flag_null)
    *error_flag = TOO_LARGE;  // число обратилось в ноль
  while ((source->bits[3] > 0 ||  // 32-ой бит может быть знаком, так что можно
                                  // нарваться на исключение
          source->bits[4] > 0 || source->bits[5] > 0 || source->bits[6] > 0) &&
         compute_ten_scale_value(*source) > 0) {
    subtract_ten_from_long_decimal(
        source);  // уменьшаем, пока есть степень 10 и число не
    // помещается в 3 32-битных
  }
  if ((source->bits[3] > 0 || source->bits[4] > 0 || source->bits[5] > 0 ||
       source->bits[6] > 0) &&
      compute_ten_scale_value(*source) == 0) {
    *error_flag = TOO_LARGE;
  }
  if (*error_flag > OK) {  // если код ошибки
    destination->bits[0] = 0;
    destination->bits[1] = 0;
    destination->bits[2] = 0;
    destination->bits[3] = 0;
  } else {
    destination->bits[0] = source->bits[0];
    destination->bits[1] = source->bits[1];
    destination->bits[2] = source->bits[2];
    destination->bits[3] = source->bits[7];
  }
}

// устанавливает показатель степени
int set_decimal_scale(s21_decimal *value, int scale) {
  int res = TOO_LARGE;
  if (scale <= 28 && scale >= 0) {
    res = OK;
    value->bits[3] &= MINUS;
    value->bits[3] |= (scale << 16) & SCALE;
  }
  return res;
}

// определяет, требуется ли банковское округление для s21_long_decimal
int determine_bank_rounding(s21_long_decimal num) {
  int flag = OK;  // флаг 1 - надо округлять, флаг 0 - не надо
  s21_long_decimal buff = {0};
  s21_long_decimal buff_of_buff = {0};
  s21_long_decimal result_long = {0};
  duplicate_long_decimal(&buff, num);
  duplicate_long_decimal(&buff_of_buff, num);
  subtract_ten_from_long_decimal(&buff_of_buff);
  add_ten_to_long_decimal(&buff_of_buff);
  long_integer_subtraction(buff, buff_of_buff, &result_long);
  subtract_ten_from_long_decimal(&buff);
  int sub_value = result_long.bits[0];
  if (sub_value > 5) {
    flag = TOO_LARGE;
  }
  if (sub_value == 5 && bit(buff.bits[0], 0) == 1) {
    flag = TOO_LARGE;
  }
  return flag;
}
