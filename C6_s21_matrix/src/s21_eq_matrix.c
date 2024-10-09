#include "s21_matrix.h"

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;

  if (IS_NOT_VALID_MATRIX(A) || IS_NOT_VALID_MATRIX(B) ||
      A->columns != B->columns || A->rows != B->rows) {
    return FAILURE;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (!IS_EQUAL(A->matrix[i][j], B->matrix[i][j])) {
        result = FAILURE;
        return result;
      }
    }
  }
  return result;
}