#include "s21_matrix.h"
// Это простая функция, которая принимает два значения типа double и возвращает
// их сумму.
// Она определена как inline, что позволяет компилятору вставлять её код прямо в
// место вызова,
// что может улучшить производительность в некоторых случаях.
static inline double s21_sum_doubles(double a, double b) { return a + b; }

int perform_matrix_arithmetic(matrix_t *A, matrix_t *B, matrix_t *result,
                              double (*f)(double, double)) {
  int result_code = RES_OK;

  if (IS_NOT_VALID_MATRIX(A) || IS_NOT_VALID_MATRIX(B) || !result ||
      A->columns != B->columns || A->rows != B->rows) {
    result_code = RES_INCORRECT;
  } else {
    result_code = s21_create_matrix(A->rows, A->columns, result);
  }

  if (result_code == RES_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = f(A->matrix[i][j], B->matrix[i][j]);
      }
    }
  }
  return result_code;
}

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return perform_matrix_arithmetic(A, B, result, s21_sum_doubles);
}