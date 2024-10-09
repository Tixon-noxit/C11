#include "s21_matrix.h"

static inline double s21_sub_doubles(double a, double b) { return a - b; }

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return perform_matrix_arithmetic(A, B, result, s21_sub_doubles);
}