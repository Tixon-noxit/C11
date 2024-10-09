#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int result_code = RES_OK;
  double res_A = 0;

  if (!result || IS_NOT_VALID_MATRIX(A) || A->rows != A->columns) {
    result_code |= RES_INCORRECT;
  } else {
    result_code |= s21_determinant(A, &res_A);
  }

  if (result_code == RES_OK && res_A != 0) {
    matrix_t buf_1 = {NULL, 0, 0};
    matrix_t buf_2 = {NULL, 0, 0};

    result_code |= s21_calc_complements(A, &buf_1);
    result_code |= s21_transpose(&buf_1, &buf_2);
    result_code |= s21_mult_number(&buf_2, 1.0 / res_A, result);

    s21_remove_matrix(&buf_1);
    s21_remove_matrix(&buf_2);
  }
  return result_code;
}