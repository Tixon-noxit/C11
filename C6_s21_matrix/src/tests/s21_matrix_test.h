//
// Created by Тихон Чабусов on 06.04.2024.
//

#ifndef C6_S21_MATRIX_1_S21_MATRIX_TEST_H
#define C6_S21_MATRIX_1_S21_MATRIX_TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

#define PRINT_IF_ERR_CREATE_MATRIX(res) \
  if (res != RES_OK) printf("error while create_matrix, possibly malloc\n");
#define GET_RAND(min, max) (min + ((double)rand() / RAND_MAX) * (max - min))

int init_matrixes_3x3(matrix_t *A, matrix_t *B);

#endif  // C6_S21_MATRIX_1_S21_MATRIX_TEST_H
