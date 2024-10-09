#include "s21_matrix.h"

double **s21_create_matrix_array(int rows, int columns) {
  double **matrix = malloc(sizeof(double *) * rows);
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      matrix[i] = calloc(columns, sizeof(double));
      if (!matrix[i]) {
        s21_free_matrix_array(matrix, i);
        break;
      }
    }
  }
  return matrix;
}

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *m) {
  int result_code = RES_OK;

  if (rows < 1 || columns < 1 || !m) {
    result_code = RES_INCORRECT;
  } else {
    m->rows = rows;
    m->columns = columns;
    m->matrix = s21_create_matrix_array(rows, columns);
    if (!m->matrix) {
      result_code = RES_INCORRECT;
    }
  }
  return result_code;
}