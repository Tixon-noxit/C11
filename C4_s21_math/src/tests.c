#include "tests.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int failed = 0;

  failed += test_abs();
  failed += test_log();
  failed += test_exp();
  failed += test_floor();
  failed += test_ceil();
  failed += test_sqrt();
  failed += test_pow();
  failed += test_cos();
  failed += test_sin();
  failed += test_tan();
  failed += test_fabs();
  failed += test_acos();
  failed += test_asin();
  failed += test_atan();
  return (failed == 0) ? 0 : CK_FAILURE;
}

START_TEST(test_abs_loop) { ck_assert(abs(_i) == s21_abs(_i)); }
END_TEST

int test_abs() {
  Suite *suite = suite_create("s21_math");
  TCase *tc_core = tcase_create("Core");
  tcase_add_loop_test(tc_core, test_abs_loop, -50, 50);
  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_exp_loop) {
  ck_assert_ldouble_eq_tol(exp(_i), s21_exp(_i), 0.001);
}
START_TEST(test_exp_double) {
  for (double i = 0; i < 10.;) {
    ck_assert_ldouble_eq_tol(exp(i), s21_exp(i), 0.001);
    i += 0.1;
  }
}
END_TEST
int test_exp() {
  Suite *suite = suite_create("s21_exp");
  TCase *tc_core = tcase_create("Core");
  tcase_add_loop_test(tc_core, test_exp_loop, 0, 28);
  tcase_add_test(tc_core, test_exp_double);
  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_log_loop_1) {
  double d = (double)_i / 100;
  ck_assert_ldouble_eq_tol(log(d), s21_log(d), 0.00001);
}
END_TEST

START_TEST(test_log_loop_2) {
  double d = (double)_i / 10;
  ck_assert_ldouble_eq_tol(log(d), s21_log(d), 0.00001);
}
END_TEST

START_TEST(test_log_loop_3) {
  double d = (double)_i / 1000;
  ck_assert_ldouble_eq_tol(log(d), s21_log(d), 0.00001);
}
END_TEST

int test_log() {
  Suite *suite = suite_create("s21_log");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_log_loop_1, 1, 10);
  tcase_add_loop_test(tc_core, test_log_loop_2, 1, 10);
  tcase_add_loop_test(tc_core, test_log_loop_3, 1, 10);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_floor_loop_1) {
  double x = (double)_i + 0.0000000193;
  ck_assert_ldouble_eq_tol(floor(x), s21_floor(x), 0.00001);
}
END_TEST

START_TEST(test_floor_loop_2) {
  double x = (double)_i + 0.999;
  ck_assert_ldouble_eq_tol(floor(x), s21_floor(x), 0.00001);
}
END_TEST

START_TEST(test_floor_loop_3) {
  double x = (double)_i;
  ck_assert_ldouble_eq_tol(floor(x), s21_floor(x), 0.00001);
}
END_TEST

int test_floor() {
  Suite *suite = suite_create("s21_floor");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_floor_loop_1, -10, 10);
  tcase_add_loop_test(tc_core, test_floor_loop_2, -10, 10);
  tcase_add_loop_test(tc_core, test_floor_loop_3, -10, 10);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_ceil_loop_1) {
  double x = (double)_i + 0.193;
  ck_assert_ldouble_eq_tol(ceil(x), s21_ceil(x), 0.00001);
}
END_TEST

START_TEST(test_ceil_loop_2) {
  double x = (double)_i + 0.999;
  ck_assert_ldouble_eq_tol(ceil(x), s21_ceil(x), 0.00001);
}
END_TEST

START_TEST(test_ceil_loop_3) {
  double x = (double)_i;
  ck_assert_ldouble_eq_tol(ceil(x), s21_ceil(x), 0.00001);
}
END_TEST

START_TEST(ceil_test_4) {
  ck_assert_ldouble_infinite(s21_ceil(INFINITY));
  ck_assert_ldouble_infinite(ceil(INFINITY));
  ck_assert_ldouble_eq(s21_ceil(S21_DBL_MAX), ceil(S21_DBL_MAX));
}
END_TEST

int test_ceil() {
  Suite *suite = suite_create("s21_ceil");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_ceil_loop_1, -10, 10);
  tcase_add_loop_test(tc_core, test_ceil_loop_2, -10, 10);
  tcase_add_loop_test(tc_core, test_ceil_loop_3, -10, 10);
  tcase_add_test(tc_core, ceil_test_4);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_sqrt_loop) {
  if (_i < 0) {
    ck_assert_double_nan(s21_sqrt(_i));
  } else {
    ck_assert_double_eq_tol(sqrt(_i), s21_sqrt(_i), 0.00001);
  }
}
END_TEST

int test_sqrt() {
  Suite *suite = suite_create("s21_sqrt");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_sqrt_loop, -10, 10);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_pow_loop_1) {
  ck_assert_double_eq_tol(pow(2, _i), s21_pow(2, _i), 0.000001);
}
END_TEST

START_TEST(test_pow_zero) {
  ck_assert_double_eq_tol(pow(0, 2), s21_pow(0, 2), 0.000001);
}
END_TEST

START_TEST(pow_test_3) {
  long double base = -10.1261;
  long double exp = -0.72;
  ck_assert_double_nan(s21_pow(base, exp));
  ck_assert_double_nan(pow(base, exp));
}
END_TEST

START_TEST(pow_test_4) {
  long double base = -1;
  long double exp = S21_POS_INF;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

int test_pow() {
  Suite *suite = suite_create("s21_pow");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_pow_loop_1, -10, 10);
  tcase_add_test(tc_core, test_pow_zero);
  tcase_add_test(tc_core, pow_test_3);
  tcase_add_test(tc_core, pow_test_4);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_cos_loop) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(cos(x), s21_cos(x), 0.000001);
}

START_TEST(cos_2) {
  ck_assert_ldouble_nan(s21_cos(INFINITY));
  ck_assert_ldouble_nan(cos(INFINITY));
}
END_TEST

int test_cos() {
  Suite *suite = suite_create("s21_cos");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_cos_loop, -30, 30);
  tcase_add_test(tc_core, cos_2);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_sin_loop) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(sin(x), s21_sin(x), 0.000001);
}

START_TEST(sin_test_2) {
  ck_assert_ldouble_nan(s21_sin(INFINITY));
  ck_assert_ldouble_nan(sin(INFINITY));
}
END_TEST

int test_sin() {
  Suite *suite = suite_create("s21_sin");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_sin_loop, -30, 30);
  tcase_add_test(tc_core, sin_test_2);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_tan_loop) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(tan(x), s21_tan(x), 0.0001);
}

START_TEST(test_tan_loop_2) {
  double x = (double)_i;
  ck_assert_double_eq_tol(tan(x), s21_tan(x), 0.0001);
}

int test_tan() {
  Suite *suite = suite_create("s21_tan");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_tan_loop, -10, 10);
  tcase_add_loop_test(tc_core, test_tan_loop_2, -30, 30);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_fabs_loop) {
  double x = (double)_i;
  ck_assert(fabs(x) == s21_fabs(x));
}
END_TEST

int test_fabs() {
  Suite *suite = suite_create("s21_fabs");
  TCase *tc_core = tcase_create("Core");
  tcase_add_loop_test(tc_core, test_fabs_loop, -50, 50);
  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_acos_loop) {
  double x = (double)_i / 100;
  ck_assert_double_eq_tol(acos(x), s21_acos(x), 0.0001);
}

START_TEST(test_acos_loop_2) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(acos(x), s21_acos(x), 0.0001);
}

START_TEST(acos_test_3) {
  ck_assert_ldouble_nan(s21_acos(NAN));
  ck_assert_ldouble_nan(acos(NAN));
}
END_TEST

int test_acos() {
  Suite *suite = suite_create("s21_acos");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_acos_loop, -10, 10);
  tcase_add_loop_test(tc_core, test_acos_loop_2, -10, 10);
  tcase_add_test(tc_core, acos_test_3);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_asin_loop) {
  double x = (double)_i / 100;
  ck_assert_double_eq_tol(asin(x), s21_asin(x), 0.0001);
}

START_TEST(test_asin_loop_2) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(asin(x), s21_asin(x), 0.0001);
}

START_TEST(test_asin_nan) { ck_assert_ldouble_nan(s21_asin(2)); }

int test_asin() {
  Suite *suite = suite_create("s21_asin");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_asin_loop, -10, 10);
  tcase_add_loop_test(tc_core, test_asin_loop_2, -10, 10);
  tcase_add_test(tc_core, test_asin_nan);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}

START_TEST(test_atan_loop) {
  double x = (double)_i / 100;
  ck_assert_double_eq_tol(atan(x), s21_atan(x), 0.0001);
}

START_TEST(test_atan_loop_2) {
  double x = (double)_i / 10;
  ck_assert_double_eq_tol(atan(x), s21_atan(x), 0.0001);
}

START_TEST(atan_test_3) {
  ck_assert_ldouble_eq(s21_atan(INFINITY), atan(INFINITY));
  ck_assert_ldouble_eq(s21_atan(-INFINITY), atan(-INFINITY));
  ck_assert_ldouble_eq_tol(s21_atan(1.0), atan(1.0), S21_EPS_TEST);
  ck_assert_ldouble_eq_tol(s21_atan(1.1), atan(1.1), S21_EPS_TEST);
  ck_assert_ldouble_eq_tol(s21_atan(-1.0), atan(-1.0), S21_EPS_TEST);
  ck_assert_ldouble_eq_tol(s21_atan(-1.1), atan(-1.1), S21_EPS_TEST);
}
END_TEST

int test_atan() {
  Suite *suite = suite_create("s21_atan");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(suite, tc_core);
  tcase_add_loop_test(tc_core, test_atan_loop, -10, 10);
  tcase_add_loop_test(tc_core, test_atan_loop_2, -10, 10);
  tcase_add_test(tc_core, atan_test_3);
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}