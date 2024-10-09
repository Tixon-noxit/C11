#include "s21_matrix.h"

// Освобождения памяти, выделенной под каждую строку матрицы
void s21_free_matrix(matrix_t *matrix, int i) {
  if (matrix) {
    s21_free_matrix_array(matrix->matrix, i);
    matrix->matrix = NULL;
  }
}

// Освобождения памяти, выделенной под строки матрицы
void s21_free_matrix_array(double **matrix, int i) {
  while (--i > -1) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
}