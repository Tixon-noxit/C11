#include "s21_matrix.h"

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int result_code = RES_OK;

  if (!result || IS_NOT_VALID_MATRIX(A)) {
    result_code = RES_INCORRECT;
  } else {
    result_code = s21_create_matrix(A->columns, A->rows, result);
  }

  if (result_code == RES_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return result_code;
}