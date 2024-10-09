#pragma once

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 0.00000001
#define IS_NOT_VALID_MATRIX(m) (m == NULL || m->rows <= 0 || m->columns <= 0)
#define IS_EQUAL(a, b) (fabs(a - b) <= EPSILON)

typedef enum { RES_OK = 0, RES_INCORRECT, RES_CALC_ERROR } result_t;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

double **s21_create_matrix_array(int rows, int columns);
int perform_matrix_arithmetic(matrix_t *A, matrix_t *B, matrix_t *result,
                              double (*f)(double, double));
void s21_free_matrix(matrix_t *matrix, int i);
void s21_free_matrix_array(double **matrix, int i);
int s21_determinant_array(double **B, int m, int n, double *result);