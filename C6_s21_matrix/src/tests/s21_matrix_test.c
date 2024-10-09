//
// Created by Тихон Чабусов on 06.04.2024.
//
#include "s21_matrix_test.h"

int init_matrixes_3x3(matrix_t *A, matrix_t *B) {
  double m1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double m2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

  int res = s21_create_matrix(3, 3, A);
  res |= s21_create_matrix(3, 3, B);
  if (res == RES_OK) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        A->matrix[i][j] = m1[i][j];
        B->matrix[i][j] = m2[i][j];
      }
    }
  }
  return res;
}

START_TEST(test_calc_complements_invalid) {
  matrix_t m = {0};
  matrix_t result = {0};
  int res = s21_create_matrix(2, 2, &m);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  if (res == RES_OK) {
    m.rows = 0;
    m.columns = 0;
    res = s21_calc_complements(&m, &result);
    ck_assert_int_eq(res, RES_INCORRECT);

    m.rows = 2;
    m.columns = 0;
    res = s21_calc_complements(&m, &result);
    ck_assert_int_eq(res, RES_INCORRECT);

    m.rows = 2;
    m.columns = 3;
    res = s21_calc_complements(&m, &result);
    ck_assert_int_eq(res, RES_INCORRECT);
    s21_free_matrix(&m, m.rows);
  }
}

END_TEST

START_TEST(test_calc_complements_correct) {
  matrix_t source = {0};
  matrix_t expected = {0};
  matrix_t actual = {0};
  int res = RES_OK;

  res = s21_create_matrix(3, 3, &source);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  res = s21_create_matrix(3, 3, &expected);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  PRINT_IF_ERR_CREATE_MATRIX(res);
  if (res == RES_OK) {
    /*
1 2 3
0 4 2
5 2 1
*/
    source.matrix[0][0] = 1;
    source.matrix[0][1] = 2;
    source.matrix[0][2] = 3;
    source.matrix[1][0] = 0;
    source.matrix[1][1] = 4;
    source.matrix[1][2] = 2;
    source.matrix[2][0] = 5;
    source.matrix[2][1] = 2;
    source.matrix[2][2] = 1;

    /*
    0 10 -20
    4 -14 8
    -8 -2 4
    */
    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    res = s21_calc_complements(&source, &actual);
    ck_assert_double_eq_tol(expected.matrix[0][0], actual.matrix[0][0],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[0][1], actual.matrix[0][1],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[0][2], actual.matrix[0][2],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[1][0], actual.matrix[1][0],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[1][1], actual.matrix[1][1],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[1][2], actual.matrix[1][2],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[2][0], actual.matrix[2][0],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[2][1], actual.matrix[2][1],
                            EPSILON);
    ck_assert_double_eq_tol(expected.matrix[2][2], actual.matrix[2][2],
                            EPSILON);
  }

  s21_free_matrix(&source, source.rows);
  s21_free_matrix(&expected, expected.rows);
  s21_free_matrix(&actual, actual.rows);
}

END_TEST

START_TEST(test_create_invalid) {
  matrix_t sum = {0};
  int res = RES_OK;

  res = s21_create_matrix(0, 1, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);

  res = s21_create_matrix(1, 0, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);
}
END_TEST

START_TEST(test_create_matrix) {
  matrix_t m = {0};
  int res = RES_OK;
  res = s21_create_matrix(3, 3, &m);

  ck_assert_int_eq(res, RES_OK);
  ck_assert_int_eq(m.rows, 3);
  ck_assert_int_eq(m.columns, 3);
  ck_assert_int_eq((int)m.matrix[0][0], 0);
  s21_free_matrix(&m, m.rows);
}
END_TEST

START_TEST(test_create_matrix_rectangular) {
  matrix_t m = {0};
  int res = RES_OK;
  res = s21_create_matrix(2, 3, &m);

  ck_assert_int_eq(res, RES_OK);
  ck_assert_int_eq(m.rows, 2);
  ck_assert_int_eq(m.columns, 3);
  ck_assert_int_eq((int)m.matrix[0][0], 0);
  ck_assert_int_eq((int)m.matrix[m.rows - 1][m.columns - 1], 0);
  s21_free_matrix(&m, m.rows);
}
END_TEST

START_TEST(test_create_matrix_rectangular_trans) {
  matrix_t m = {0};
  int res = RES_OK;
  res = s21_create_matrix(3, 2, &m);

  ck_assert_int_eq(res, RES_OK);
  ck_assert_int_eq(m.rows, 3);
  ck_assert_int_eq(m.columns, 2);
  ck_assert_int_eq((int)m.matrix[0][0], 0);
  ck_assert_int_eq((int)m.matrix[m.rows - 1][m.columns - 1], 0);
  s21_free_matrix(&m, m.rows);
}
END_TEST

START_TEST(test_determ_invalid) {
  matrix_t m = {0};
  int result_code = s21_create_matrix(2, 2, &m);
  PRINT_IF_ERR_CREATE_MATRIX(result_code);

  double determinant = 0;
  m.rows = 0;
  result_code = s21_determinant(&m, &determinant);
  ck_assert_int_eq(result_code, RES_INCORRECT);

  m.rows = 2;
  m.columns = 0;
  result_code = s21_determinant(&m, &determinant);
  ck_assert_int_eq(result_code, RES_INCORRECT);

  m.columns = 3;
  result_code = s21_determinant(&m, &determinant);
  ck_assert_int_eq(result_code, RES_INCORRECT);
  s21_free_matrix(&m, m.rows);
}
END_TEST

START_TEST(test_determ_correct) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  int res = RES_OK;
  double determinant = 0;

  res = s21_create_matrix(3, 3, &m1);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  if (res == RES_OK) {
    /*
54 2 5
56 4 7
1 -4 -20
*/
    m1.matrix[0][0] = 54;
    m1.matrix[0][1] = 2;
    m1.matrix[0][2] = 5;
    m1.matrix[1][0] = 56;
    m1.matrix[1][1] = 4;
    m1.matrix[1][2] = 7;
    m1.matrix[2][0] = 1;
    m1.matrix[2][1] = -4;
    m1.matrix[2][2] = -20;
    res = s21_determinant(&m1, &determinant);
    ck_assert_int_eq(res, RES_OK);
    ck_assert_ldouble_eq_tol(determinant, -1694, EPSILON);
    s21_free_matrix(&m1, m1.rows);
  }

  res = s21_create_matrix(3, 3, &m2);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  if (res == RES_OK) {
    /*
1 4 7
2 5 8
3 6 9
*/
    m2.matrix[0][0] = 1;
    m2.matrix[0][1] = 4;
    m2.matrix[0][2] = 7;
    m2.matrix[1][0] = 2;
    m2.matrix[1][1] = 5;
    m2.matrix[1][2] = 8;
    m2.matrix[2][0] = 3;
    m2.matrix[2][1] = 6;
    m2.matrix[2][2] = 9;

    ck_assert_ldouble_eq_tol(s21_determinant(&m2, &determinant), 0, EPSILON);
    s21_free_matrix(&m2, m2.rows);
  }
}
END_TEST

START_TEST(test_create_matrix_array_valid) {
  double **matrix = s21_create_matrix_array(3, 3);
  ck_assert_ptr_ne(matrix, NULL);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_ptr_ne(matrix[i], NULL);
    }
  }

  s21_free_matrix_array(matrix, 3);
}
END_TEST

START_TEST(test_create_matrix_array_invalid_rows_columns) {
  double **matrix = s21_create_matrix_array(-1, 3);
  ck_assert_ptr_eq(matrix, matrix);

  matrix = s21_create_matrix_array(3, -1);
  ck_assert_ptr_eq(matrix, matrix);

  matrix = s21_create_matrix_array(0, 3);
  ck_assert_ptr_eq(matrix, matrix);

  matrix = s21_create_matrix_array(3, 0);
  ck_assert_ptr_eq(matrix, matrix);
}
END_TEST

START_TEST(test_create_matrix_array_allocation_failure) {
  double **matrix = s21_create_matrix_array(3, 3);
  ck_assert_ptr_eq(matrix, matrix);
}
END_TEST

START_TEST(test_equal_matrix) {
  int res = RES_OK;
  matrix_t A = {0};
  matrix_t B = {0};

  res |= s21_create_matrix(2, 2, &A);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  res |= s21_create_matrix(2, 2, &B);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_non_equal_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  int res = RES_OK;

  res = s21_create_matrix(2, 2, &A);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  res |= s21_create_matrix(3, 3, &B);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  res |= s21_create_matrix(2, 2, &C);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  if (res == RES_OK) {
    C.matrix[1][1] = 2;
    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
    ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);
  }

  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
  s21_free_matrix(&C, C.rows);
}
END_TEST

START_TEST(test_free_matrix) {
  matrix_t m = {0};
  int res = s21_create_matrix(2, 2, &m);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  s21_free_matrix(&m, m.rows);
  ck_assert_ptr_eq(m.matrix, NULL);
}
END_TEST

START_TEST(test_inverse_invalid) {
  matrix_t m = {0};
  matrix_t result = {0};
  int result_code = RES_OK;

  result_code = s21_create_matrix(2, 2, &m);
  PRINT_IF_ERR_CREATE_MATRIX(result_code);

  m.rows = 0;
  result_code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(result_code, RES_INCORRECT);

  m.rows = 2;
  m.columns = 0;
  result_code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(result_code, RES_INCORRECT);

  m.columns = 3;
  result_code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(result_code, RES_INCORRECT);

  s21_free_matrix(&m, m.rows);
}
END_TEST

START_TEST(test_inverse_correct) {
  matrix_t ex1 = {0};
  matrix_t res1 = {0};
  int res = RES_OK;

  res |= s21_create_matrix(3, 3, &ex1);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  res |= s21_create_matrix(3, 3, &res1);
  PRINT_IF_ERR_CREATE_MATRIX(res);

  if (res == RES_OK) {
    /*
1 1 3
1 3 -3
-2 -4 -4
*/
    ex1.matrix[0][0] = 1;
    ex1.matrix[0][1] = 1;
    ex1.matrix[0][2] = 3;
    ex1.matrix[1][0] = 1;
    ex1.matrix[1][1] = 3;
    ex1.matrix[1][2] = -3;
    ex1.matrix[2][0] = -2;
    ex1.matrix[2][1] = -4;
    ex1.matrix[2][2] = -4;

    /*
    1 4 7
    2 5 8
    3 6 9
    */
    res1.matrix[0][0] = 3;
    res1.matrix[0][1] = 1;
    res1.matrix[0][2] = 1.5;
    res1.matrix[1][0] = -1.25;
    res1.matrix[1][1] = -0.25;
    res1.matrix[1][2] = -0.75;
    res1.matrix[2][0] = -0.25;
    res1.matrix[2][1] = -0.25;
    res1.matrix[2][2] = -0.25;

    matrix_t inverse1 = {0};
    res = s21_inverse_matrix(&ex1, &inverse1);
    ck_assert_double_eq_tol(res1.matrix[0][0], inverse1.matrix[0][0], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[0][1], inverse1.matrix[0][1], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[0][2], inverse1.matrix[0][2], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[1][0], inverse1.matrix[1][0], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[1][1], inverse1.matrix[1][1], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[1][2], inverse1.matrix[1][2], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[2][0], inverse1.matrix[2][0], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[2][1], inverse1.matrix[2][1], EPSILON);
    ck_assert_double_eq_tol(res1.matrix[2][2], inverse1.matrix[2][2], EPSILON);
    s21_free_matrix(&inverse1, inverse1.rows);
  }

  s21_free_matrix(&ex1, ex1.rows);
  s21_free_matrix(&res1, res1.rows);
}
END_TEST

START_TEST(test_mult_matrix_invalid) {
  matrix_t mult;
  matrix_t A;
  matrix_t B;
  int res = init_matrixes_3x3(&A, &B);

  A.columns = 4;
  res = s21_mult_matrix(&A, &B, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.columns = 3;
  A.rows = 0;
  res = s21_mult_matrix(&A, &B, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 3;
  A.columns = 0;
  res = s21_mult_matrix(&A, &B, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.columns = 3;
  B.rows = 0;
  res = s21_mult_matrix(&A, &B, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  B.rows = 3;
  B.columns = 0;
  res = s21_mult_matrix(&A, &B, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_mult_matrix_correct) {
  matrix_t A;
  matrix_t B;
  init_matrixes_3x3(&A, &B);

  double result[3][3] = {{6, 6, 6}, {15, 15, 15}, {24, 24, 24}};

  matrix_t m_result = {0};
  matrix_t mult = {0};
  int res = s21_create_matrix(3, 3, &m_result);
  PRINT_IF_ERR_CREATE_MATRIX(res);
  res = s21_mult_matrix(&A, &B, &mult);

  for (int i = 0; i < m_result.rows; i++) {
    for (int j = 0; j < m_result.columns; j++) {
      m_result.matrix[i][j] = result[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&mult, &m_result), SUCCESS);

  s21_free_matrix(&m_result, m_result.rows);
  s21_free_matrix(&mult, mult.rows);
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_mult_matrix_rectangle_correct) {
  double left[3][4] = {{11, 12, 13, 14}, {21, 22, 23, 24}, {31, 32, 33, 34}};
  matrix_t A = {0};
  s21_create_matrix(3, 4, &A);
  for (int i = 0; i < A.rows; i++) {
    memcpy(A.matrix[i], left[i], sizeof(double) * A.columns);
  }

  double right[4][3] = {
      {110, 120, 130}, {210, 220, 230}, {310, 320, 330}, {410, 420, 430}};
  matrix_t B = {0};
  s21_create_matrix(4, 3, &B);
  for (int i = 0; i < B.rows; i++) {
    memcpy(B.matrix[i], right[i], sizeof(double) * B.columns);
  }

  matrix_t expected = {0};
  double result[3][3] = {
      {13500, 14000, 14500}, {23900, 24800, 25700}, {34300, 35600, 36900}};
  s21_create_matrix(3, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    memcpy(expected.matrix[i], result[i], sizeof(double) * expected.columns);
  }

  matrix_t actual = {0};
  int res = s21_mult_matrix(&A, &B, &actual);
  // s21_print_matrix(&expected, "expected");
  // s21_print_matrix(&actual, "actual");

  ck_assert_int_eq(RES_OK, res);
  ck_assert_int_eq(s21_eq_matrix(&expected, &actual), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&actual);
}

START_TEST(test_mult_number_invalid) {
  matrix_t mult = {0};
  matrix_t A = {0};

  A.rows = 0;
  int res = s21_mult_number(&A, 2, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.columns = 0;
  A.rows = 1;
  res = s21_mult_number(&A, 2, &mult);
  ck_assert_int_eq(res, RES_INCORRECT);
}
END_TEST

START_TEST(test_mult_number_correct) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t mult = {0};
  init_matrixes_3x3(&A, &B);

  int res = s21_mult_number(&A, 2, &mult);
  matrix_t m_result = {0};
  s21_create_matrix(3, 3, &m_result);
  double result[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};

  for (int i = 0; i < m_result.rows; i++) {
    for (int j = 0; j < m_result.columns; j++) {
      m_result.matrix[i][j] = result[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&mult, &m_result), SUCCESS);
  ck_assert_int_eq(res, RES_OK);

  s21_free_matrix(&m_result, m_result.rows);
  s21_free_matrix(&mult, mult.rows);
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_mult_number_rectangle_correct) {
  matrix_t src = {0};
  matrix_t expected = {0};
  matrix_t actual = {0};

  double src_arr[3][4] = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
  };

  s21_create_matrix(3, 4, &src);
  s21_create_matrix(3, 4, &expected);

  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.rows; j++) {
      src.matrix[i][j] = src_arr[i][j];
      expected.matrix[i][j] = src_arr[i][j] * 2;
    }
  }

  int res = s21_mult_number(&src, 2, &actual);

  ck_assert_int_eq(s21_eq_matrix(&expected, &actual), SUCCESS);
  ck_assert_int_eq(res, RES_OK);

  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&src);
}
END_TEST

START_TEST(test_remove) {
  matrix_t m = {0};
  int res = s21_create_matrix(3, 3, &m);
  s21_remove_matrix(&m);
  ck_assert_int_eq(res, RES_OK);
}
END_TEST

START_TEST(test_sub_invalid) {
  matrix_t sub = {0};
  matrix_t A = {0};
  matrix_t B = {0};
  int res = 0;
  init_matrixes_3x3(&A, &B);

  A.columns = 4;
  res = s21_sub_matrix(&A, &B, &sub);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 4;
  A.columns = 3;
  res = s21_sub_matrix(&A, &B, &sub);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 0;
  B.rows = 0;
  res = s21_sub_matrix(&A, &B, &sub);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 1;
  B.rows = 1;
  A.columns = 0;
  B.columns = 0;
  res = s21_sub_matrix(&A, &B, &sub);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 3;
  B.rows = 3;
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_sub_correct) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t sub = {0};
  init_matrixes_3x3(&A, &B);

  s21_sub_matrix(&A, &B, &sub);
  matrix_t m_result = {0};
  s21_create_matrix(3, 3, &m_result);
  double result[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

  for (int i = 0; i < m_result.rows; i++) {
    for (int j = 0; j < m_result.columns; j++) {
      m_result.matrix[i][j] = result[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&sub, &m_result), SUCCESS);

  s21_free_matrix(&m_result, m_result.rows);
  s21_free_matrix(&sub, sub.rows);
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_sub_rectangle_correct) {
  matrix_t A = {0};
  matrix_t sum = {0};
  matrix_t expected = {0};

  double src_matrix[3][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};

  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &expected);
  for (int i = 0; i < A.rows; i++) {
    memcpy(A.matrix[i], src_matrix[i], sizeof(double) * A.columns);
    memcpy(expected.matrix[i], src_matrix[i],
           sizeof(double) * expected.columns);
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] -= expected.matrix[i][j];
    }
  }
  int res = s21_sub_matrix(&A, &A, &sum);
  ck_assert_int_eq(RES_OK, res);
  ck_assert_int_eq(s21_eq_matrix(&expected, &sum), SUCCESS);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&A);
  s21_remove_matrix(&sum);
}

START_TEST(test_sum_invalid) {
  matrix_t sum = {0};
  matrix_t A = {0};
  matrix_t B = {0};
  int res = init_matrixes_3x3(&A, &B);

  A.columns = 4;
  res = s21_sum_matrix(&A, &B, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 4;
  A.columns = 3;
  res = s21_sum_matrix(&A, &B, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 0;
  B.rows = 0;
  res = s21_sum_matrix(&A, &B, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 1;
  B.rows = 1;
  A.columns = 0;
  B.columns = 0;
  res = s21_sum_matrix(&A, &B, &sum);
  ck_assert_int_eq(res, RES_INCORRECT);

  A.rows = 3;
  B.rows = 3;
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_sum_correct) {
  matrix_t A = {0};
  matrix_t B = {0};
  init_matrixes_3x3(&A, &B);

  matrix_t sum = {0};
  s21_sum_matrix(&A, &B, &sum);
  matrix_t m_result = {0};
  s21_create_matrix(3, 3, &m_result);
  double result[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  for (int i = 0; i < m_result.rows; i++) {
    for (int j = 0; j < m_result.columns; j++) {
      m_result.matrix[i][j] = result[i][j];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&sum, &m_result), SUCCESS);

  s21_free_matrix(&m_result, m_result.rows);
  s21_free_matrix(&sum, sum.rows);
  s21_free_matrix(&A, A.rows);
  s21_free_matrix(&B, B.rows);
}
END_TEST

START_TEST(test_sum_rectangle_correct) {
  matrix_t A = {0};
  matrix_t sum = {0};
  matrix_t expected = {0};

  double src_matrix[3][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};

  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 4, &expected);
  for (int i = 0; i < A.rows; i++) {
    memcpy(A.matrix[i], src_matrix[i], sizeof(double) * A.columns);
    memcpy(expected.matrix[i], src_matrix[i],
           sizeof(double) * expected.columns);
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] += expected.matrix[i][j];
    }
  }
  int res = s21_sum_matrix(&A, &A, &sum);
  ck_assert_int_eq(RES_OK, res);
  ck_assert_int_eq(s21_eq_matrix(&expected, &sum), SUCCESS);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&A);
  s21_remove_matrix(&sum);
}

START_TEST(test_trans_invalid) {
  matrix_t m = {0};
  int res = s21_create_matrix(2, 2, &m);

  m.rows = 0;
  matrix_t trans = {0};
  res = s21_transpose(&m, &trans);
  ck_assert_int_eq(res, RES_INCORRECT);

  m.rows = 2;
  m.columns = 0;
  res = s21_transpose(&m, &trans);
  ck_assert_int_eq(res, RES_INCORRECT);

  s21_free_matrix(&m, m.rows);
}
END_TEST

double m33[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

double m33_transposed[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

START_TEST(test_trans_correct) {
  matrix_t src = {0};
  matrix_t expected = {0};

  s21_create_matrix(3, 3, &src);
  for (int i = 0; i < src.rows; i++) {
    memcpy(src.matrix[i], m33[i], sizeof(double) * src.columns);
  }

  s21_create_matrix(3, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    memcpy(expected.matrix[i], m33_transposed[i],
           sizeof(double) * expected.columns);
  }

  matrix_t actual = {0};
  int result = s21_transpose(&src, &actual);
  ck_assert_int_eq(result, RES_OK);
  ck_assert_int_eq(s21_eq_matrix(&expected, &actual), SUCCESS);
  s21_free_matrix(&src, src.rows);
  s21_free_matrix(&expected, expected.rows);
  s21_free_matrix(&actual, actual.rows);
}
END_TEST

double m34[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

double m43_transposed[4][3] = {{1, 5, 9}, {2, 6, 10}, {3, 7, 11}, {4, 8, 12}};

START_TEST(test_trans_rect_correct) {
  matrix_t src = {0};
  matrix_t expected = {0};

  s21_create_matrix(3, 4, &src);
  for (int i = 0; i < src.rows; i++) {
    memcpy(src.matrix[i], m34[i], sizeof(double) * src.columns);
  }

  s21_create_matrix(4, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    memcpy(expected.matrix[i], m43_transposed[i],
           sizeof(double) * expected.columns);
  }

  matrix_t actual = {0};
  s21_transpose(&src, &actual);
  ck_assert_int_eq(s21_eq_matrix(&expected, &actual), SUCCESS);
  s21_free_matrix(&src, src.rows);
  s21_free_matrix(&expected, expected.rows);
  s21_free_matrix(&actual, actual.rows);
}
END_TEST

START_TEST(test_trans_rect_transposed_correct) {
  matrix_t src = {0};
  matrix_t expected = {0};

  s21_create_matrix(4, 3, &src);
  for (int i = 0; i < src.rows; i++) {
    memcpy(src.matrix[i], m43_transposed[i], sizeof(double) * src.columns);
  }

  s21_create_matrix(3, 4, &expected);
  for (int i = 0; i < expected.rows; i++) {
    memcpy(expected.matrix[i], m34[i], sizeof(double) * expected.columns);
  }

  matrix_t actual = {0};
  int result = s21_transpose(&src, &actual);
  ck_assert_int_eq(result, RES_OK);
  ck_assert_int_eq(s21_eq_matrix(&expected, &actual), SUCCESS);
  s21_free_matrix(&src, src.rows);
  s21_free_matrix(&expected, expected.rows);
  s21_free_matrix(&actual, actual.rows);
}
END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tc_calc_complements = tcase_create("s21_calc_complements");
  tcase_add_test(tc_calc_complements, test_calc_complements_correct);
  tcase_add_test(tc_calc_complements, test_calc_complements_invalid);
  suite_add_tcase(suite, tc_calc_complements);

  TCase *tc_create_matrix = tcase_create("s21_create_matrix");
  tcase_add_test(tc_create_matrix, test_create_matrix);
  tcase_add_test(tc_create_matrix, test_create_invalid);
  tcase_add_test(tc_create_matrix, test_create_matrix_rectangular);
  tcase_add_test(tc_create_matrix, test_create_matrix_rectangular_trans);
  tcase_add_test(tc_create_matrix, test_create_matrix_array_allocation_failure);
  tcase_add_test(tc_create_matrix,
                 test_create_matrix_array_invalid_rows_columns);
  tcase_add_test(tc_create_matrix, test_create_matrix_array_valid);
  suite_add_tcase(suite, tc_create_matrix);

  TCase *tc_determ_correct = tcase_create("s21_determ_correct");
  tcase_add_test(tc_determ_correct, test_determ_correct);
  tcase_add_test(tc_determ_correct, test_determ_invalid);
  suite_add_tcase(suite, tc_determ_correct);

  TCase *tc_equal_matrix = tcase_create("s21_equal_matrix");
  tcase_add_test(tc_equal_matrix, test_equal_matrix);
  tcase_add_test(tc_equal_matrix, test_non_equal_matrix);
  suite_add_tcase(suite, tc_equal_matrix);

  TCase *tc_free_matrix = tcase_create("s21_free_matrix");
  tcase_add_test(tc_free_matrix, test_free_matrix);
  suite_add_tcase(suite, tc_free_matrix);

  TCase *tc_inverse_correct = tcase_create("s21_inverse_correct");
  tcase_add_test(tc_inverse_correct, test_inverse_correct);
  tcase_add_test(tc_inverse_correct, test_inverse_invalid);
  suite_add_tcase(suite, tc_inverse_correct);

  TCase *tc_mult_matrix_correct = tcase_create("s21_mult_matrix_correct");
  tcase_add_test(tc_mult_matrix_correct, test_mult_matrix_correct);
  tcase_add_test(tc_mult_matrix_correct, test_mult_matrix_rectangle_correct);
  tcase_add_test(tc_mult_matrix_correct, test_mult_matrix_invalid);
  suite_add_tcase(suite, tc_mult_matrix_correct);

  TCase *tc_mult_number_correct = tcase_create("s21_mult_number_correct");
  tcase_add_test(tc_mult_number_correct, test_mult_number_correct);
  tcase_add_test(tc_mult_number_correct, test_mult_number_rectangle_correct);
  tcase_add_test(tc_mult_number_correct, test_mult_number_invalid);
  suite_add_tcase(suite, tc_mult_number_correct);

  TCase *tc_remove = tcase_create("s21_remove");
  tcase_add_test(tc_remove, test_remove);
  suite_add_tcase(suite, tc_remove);

  TCase *tc_sub_correct = tcase_create("s21_sub_correct");
  tcase_add_test(tc_sub_correct, test_sub_correct);
  tcase_add_test(tc_sub_correct, test_sub_invalid);
  tcase_add_test(tc_sub_correct, test_sub_rectangle_correct);
  suite_add_tcase(suite, tc_sub_correct);

  TCase *tc_sum_correct = tcase_create("s21_sum_correct");
  tcase_add_test(tc_sum_correct, test_sum_correct);
  tcase_add_test(tc_sum_correct, test_sum_invalid);
  tcase_add_test(tc_sum_correct, test_sum_rectangle_correct);
  suite_add_tcase(suite, tc_sum_correct);

  TCase *tc_trans_correct = tcase_create("s21_trans_correct");
  tcase_add_test(tc_trans_correct, test_trans_correct);
  tcase_add_test(tc_trans_correct, test_trans_invalid);
  tcase_add_test(tc_trans_correct, test_trans_rect_correct);
  tcase_add_test(tc_trans_correct, test_trans_rect_transposed_correct);
  suite_add_tcase(suite, tc_trans_correct);

  return suite;
}

int main() {
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
