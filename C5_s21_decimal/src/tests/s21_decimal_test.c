#include "s21_decimal_test.h"

/* ADD */
START_TEST(add_test_1) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000000000;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000000;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_2) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // 28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  // 642834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00010100100001000001100110011000;  // 670957983144090008
  result.bits[1] = 0b00001001010011111011100010111011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_3) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // 2812345678.9876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000001110000000000000000;  // 7

  num2.bits[0] = 0b10001000101100110000101001011001;  // 64.2834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000100000000000000000000;  // 16

  result.bits[0] =
      0b00101111101000001100000001011001;  // 2812345743.2711069354213465
  result.bits[1] = 0b10101110101011000101101100110010;
  result.bits[2] = 0b00000000000101110100001101011111;
  result.bits[3] = 0b00000000000100000000000000000000;  // 16
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_4) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  //  -28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  //  +642834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b11111100111000011111101100011010;  // +614711069564336922
  result.bits[1] = 0b00001000100001111110010001110101;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_5) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // + 28123456789876.543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000110000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  //  - 6428345263542134.65
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000100000000000000000;

  result.bits[0] = 0b11001011001011010101100000111011;  // -6400221806752258.107
  result.bits[1] = 0b01011000110100100010011111010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000110000000000000000;
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_6) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // - 28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  // - 642834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] = 0b00010100100001000001100110011000;  // - 670957983144090008
  result.bits[1] = 0b00001001010011111011100010111011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_add(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_7) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] =
      0b11111111111111111111111111111111;  // + 79228162514264337593543950335
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000001;  // + 1
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] =
      0b00000000000000000000000000000000;  // пойман на ошибке дешевка
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_add(num1, num2, &result2);  // 1
  ck_assert_int_eq(flag, 1);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_8) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000000001;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000111110000000000000000;  // 1 * 10 ^(-31)

  num2.bits[0] = 0b00000000000000000000000000000000;  // 0
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_add(num1, num2, &result2);  // 2
  ck_assert_int_eq(flag, 2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_9) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] =
      0b11111111111111111111111111111111;  // - 79228162514264337593543950335
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000001;  // - 1
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] =
      0b00000000000000000000000000000000;  // пойман на ошибке дешевка
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_add(num1, num2, &result2);  // 2
  ck_assert_int_eq(flag, 2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(add_test_10) {
  s21_decimal val1 = {{100, 0, 0, 0x00000000}};
  s21_decimal val2 = {{200, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 300);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(add_test_11) {
  s21_decimal val1 = {{100, 200, 300, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 99);
  ck_assert_int_eq(res.bits[1], 201);
  ck_assert_int_eq(res.bits[2], 300);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(add_test_12) {
  s21_decimal val1 = {{100, 200, 300, 0x00020000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 9999);
  ck_assert_int_eq(res.bits[1], 20001);
  ck_assert_int_eq(res.bits[2], 30000);
  ck_assert_int_eq(res.bits[3], 262144);
}

END_TEST

START_TEST(add_test_13) {
  s21_decimal val1 = {{100, 200, 300, 0x00050000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x80060000}};
  s21_decimal res = {0};

  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1001);
  ck_assert_int_eq(res.bits[1], 1999);
  ck_assert_int_eq(res.bits[2], 3000);
  ck_assert_int_eq(res.bits[3], 393216);
}

END_TEST
// 100 = 0b01100100
// 200 = 0b11001000
// 300 = 0b100101100
// 0x00050000 = 0b00000000000001010000000000000000

// Для val2:

// 0xFFFFFFFF = 0b11111111111111111111111111111111
// 0 = 0b00000000
// 0 = 0b00000000
// 0x80060000 = 0b10000000000001100000000000000000

START_TEST(add_test_14) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}

END_TEST

START_TEST(add_test_15) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(add_test_16) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}

END_TEST

START_TEST(add_test_17) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000D0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3264175145);
  ck_assert_int_eq(res.bits[1], 2405181685);
  ck_assert_int_eq(res.bits[2], 472446402);
  ck_assert_int_eq(res.bits[3], 720896);
}

END_TEST

START_TEST(add_test_18) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1305451419);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 458752);
}

END_TEST

START_TEST(add_test_19) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x80050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1911069901);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 2147942400);
}

END_TEST

START_TEST(add_test_20) {
  s21_decimal val1 = {{1, 2, 3, 0x801C0000}};
  s21_decimal val2 = {{11111111, 22222222, 33333333, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1111116634);
  ck_assert_int_eq(res.bits[1], 2222222200);
  ck_assert_int_eq(res.bits[2], 3333333300);
  ck_assert_int_eq(res.bits[3], 2148270080);
}

END_TEST

START_TEST(add_test_21) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{5, 0, 0, 0x00010000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}

END_TEST

START_TEST(add_test_22) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  s21_add(val1, val2, &res);
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(add_test_23) {
  s21_decimal val1 = {{60, 0, 0, 0x80000000}};
  s21_decimal val2 = {{40, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}

END_TEST

START_TEST(add_test_24) {
  s21_decimal val1 = {{123, 456, 789, 0x800D0000}};
  s21_decimal val2 = {{111, 222, 333, 0x00100000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 122889);
  ck_assert_int_eq(res.bits[1], 455778);
  ck_assert_int_eq(res.bits[2], 788667);
  ck_assert_int_eq(res.bits[3], 2148532224);
}

END_TEST

/* SUB */
START_TEST(sub_test_1) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000000000;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000000;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_2) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // 28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b01010111011101110000101001111100;  //  42834526354213500
  num2.bits[1] = 0b00000000100110000010110111000110;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b11001011101001011111101100111101;  //-14711069564336957
  result.bits[1] = 0b00000000001101000100001110100011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_3) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // -2812345678.9876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000001110000000000000000;  // 7

  num2.bits[0] = 0b10001000101100110000101001011001;  // 64.2834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000100000000000000000000;  // 16

  result.bits[0] =
      0b00101111101000001100000001011001;  // -2812345743.2711069354213465
  result.bits[1] = 0b10101110101011000101101100110010;
  result.bits[2] = 0b00000000000101110100001101011111;
  result.bits[3] = 0b10000000000100000000000000000000;  // 16
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_4) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  //  28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  //  -642834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] = 0b11111100111000011111101100011010;  // 614711069564336922
  result.bits[1] = 0b00001000100001111110010001110101;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_5) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // - 28123456789876.543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000110000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  //  - 6428345263542134.65
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000100000000000000000;

  result.bits[0] = 0b11001011001011010101100000111011;  // +6400221806752258.107
  result.bits[1] = 0b01011000110100100010011111010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000110000000000000000;
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_6) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10001011110100010000111100111111;  // - 28123456789876543
  num1.bits[1] = 0b00000000011000111110101000100010;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b10001000101100110000101001011001;  //  642834526354213465
  num2.bits[1] = 0b00001000111010111100111010011000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00010100100001000001100110011000;  // - 670957983144090008
  result.bits[1] = 0b00001001010011111011100010111011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_sub(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_7) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] =
      0b11111111111111111111111111111111;  // - 79228162514264337593543950335
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000001;  //  1
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] =
      0b00000000000000000000000000000000;  // пойман на ошибке дешевка
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_sub(num1, num2, &result2);  // 1
  ck_assert_int_eq(flag, 2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_8) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000000001;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000111110000000000000000;  // 1 * 10 ^(-31)

  num2.bits[0] = 0b00000000000000000000000000000000;  // 0
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_sub(num1, num2, &result2);  // 2
  ck_assert_int_eq(flag, 2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_9) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] =
      0b11111111111111111111111111111111;  //  79228162514264337593543950335
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000001;  // - 1
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] =
      0b00000000000000000000000000000000;  // пойман на ошибке дешевка
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_sub(num1, num2, &result2);  // 2
  ck_assert_int_eq(flag, 1);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(sub_test_10) {
  s21_decimal val1 = {{1000, 0, 0, 0x00000000}};
  s21_decimal val2 = {{500, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 500);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(sub_test_11) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(sub_test_12) {
  s21_decimal val1 = {{100, 200, 300, 0x00020000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 10001);
  ck_assert_int_eq(res.bits[1], 19999);
  ck_assert_int_eq(res.bits[2], 30000);
  ck_assert_int_eq(res.bits[3], 262144);
}

END_TEST

START_TEST(sub_test_13) {
  s21_decimal val1 = {{100, 200, 300, 0x00050000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x80060000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 999);
  ck_assert_int_eq(res.bits[1], 2001);
  ck_assert_int_eq(res.bits[2], 3000);
  ck_assert_int_eq(res.bits[3], 393216);
}

END_TEST

START_TEST(sub_test_14) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}

END_TEST

START_TEST(sub_test_15) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}

END_TEST

START_TEST(sub_test_16) {
  s21_decimal val1 = {{0, 0, 1, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0XFFFFFFFF);
  ck_assert_int_eq(res.bits[1], 0XFFFFFFFF);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(sub_test_17) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1911069901);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 2147942400);
}

END_TEST

START_TEST(sub_test_18) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x80050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1305451419);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 458752);
}

END_TEST

START_TEST(sub_test_19) {
  s21_decimal val1 = {{1, 2, 3, 0x801C0000}};
  s21_decimal val2 = {{11111111, 22222222, 33333333, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1111105566);
  ck_assert_int_eq(res.bits[1], 2222222200);
  ck_assert_int_eq(res.bits[2], 3333333300);
  ck_assert_int_eq(res.bits[3], 786432);
}

END_TEST

START_TEST(sub_test_20) {
  s21_decimal val1 = {{123, 321, 0, 0x00020000}};
  s21_decimal val2 = {{0, 0, 1, 0x00030000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 4294966066);
  ck_assert_int_eq(res.bits[1], 4294964085);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147680256);
}

END_TEST

START_TEST(sub_test_21) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1470944564);
  ck_assert_int_eq(res.bits[1], 1791840269);
  ck_assert_int_eq(res.bits[2], 1234567892);
  ck_assert_int_eq(res.bits[3], 983040);
}

END_TEST

START_TEST(sub_test_22) {
  s21_decimal val1 = {{123, 456, 789, 0x000D0000}};
  s21_decimal val2 = {{111, 222, 333, 0x80100000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 123111);
  ck_assert_int_eq(res.bits[1], 456222);
  ck_assert_int_eq(res.bits[2], 789333);
  ck_assert_int_eq(res.bits[3], 1048576);
}

END_TEST

/* DIV */
START_TEST(div_test_1) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000101010;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000011;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000001110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_div(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(div_test_2) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11101011000111110000101011010010;  // 12345678901234567890
  num1.bits[1] = 0b10101011010101001010100110001100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b11101011000111110000101011010010;  // 12345678901234567890
  num2.bits[1] = 0b10101011010101001010100110001100;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000001;  // 1
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_div(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(div_test_3) {
  s21_decimal num1, num2, result2 = {0};
  num1.bits[0] = 0b11101011000111110000101011010011;  // 12345678901234567891
  num1.bits[1] = 0b10101011010101001010100110001100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000000;  // 3
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  int flag = s21_div(num1, num2, &result2);
  ck_assert_int_eq(3, flag);
}

END_TEST

START_TEST(div_test_4) {
  s21_decimal num1, num2, result2 = {0};
  num1.bits[0] = 0b00000000000000000000000000001010;  // 10
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000011;  // 3
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  s21_div(num1, num2, &result2);
  float res = 3.333333;
  float dev_res = 0;
  s21_from_decimal_to_float(result2, &dev_res);
  ck_assert_float_eq_tol(res, dev_res, 0.000001);
}

END_TEST

START_TEST(div_test_5) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b10111011111100101110000111110010;  // 123412341234
  num1.bits[1] = 0b00000000000000000000000000011100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000101;  // 5
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] =
      0b01110111111001011100001111100100;  // 4115226300411522630.333333333
  result.bits[1] = 0b00000000000000000000000000111001;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000010000000000000000;
  //               0b00000000000000010000000000000000; с
  s21_div(num1, num2, &result2);

  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(div_test_6) {
  s21_decimal number1 = {{864192, 0, 0, 0x00030000}};
  s21_decimal number2 = {{7, 0, 0, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_div(number1, number2, &res));
  ck_assert_int_eq(res.bits[0], 123456);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 196608);
}

END_TEST

START_TEST(div_test_7) {
  s21_decimal val1 = {{15, 15, 15, 0x000F0000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 15);
  ck_assert_int_eq(res.bits[1], 15);
  ck_assert_int_eq(res.bits[2], 15);
  ck_assert_int_eq(res.bits[3], 1048576);
}

END_TEST

START_TEST(div_test_8) {
  s21_decimal val1 = {{123, 456, 789, 0x00040000}};
  s21_decimal val2 = {{1, 1, 1, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 405681253);
  ck_assert_int_eq(res.bits[1], 150366383);
  ck_assert_int_eq(res.bits[2], 4277177570);
  ck_assert_int_eq(res.bits[3], 1638400);
}

END_TEST

START_TEST(div_test_9) {
  s21_decimal val1 = {{2, 0, 0, 0x00000000}};
  s21_decimal val2 = {{5, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2684354560);
  ck_assert_int_eq(res.bits[1], 2135032051);
  ck_assert_int_eq(res.bits[2], 216840434);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

// START_TEST(div_4) {
//   s21_decimal val1 = {{123456789, 900009, 1337, 0x00100000}};
//   s21_decimal val2 = {{1, 1, 1111111, 0x80070000}};
//   s21_decimal res;
//   ck_assert_int_eq(0, s21_div(val1, val2, &res));
//   ck_assert_int_eq(res.bits[0], 796440904);
//   ck_assert_int_eq(res.bits[1], 280165);
//   ck_assert_int_eq(res.bits[2], 0);
//   ck_assert_int_eq(res.bits[3], 2149253120);
// }
// END_TEST

START_TEST(div_test_10) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}

END_TEST

// START_TEST(div_test_11) {
//   s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
//   s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
//   s21_decimal res;
//   ck_assert_int_eq(0, s21_div(val1, val2, &res));
//   ck_assert_int_eq(res.bits[0], 0);
//   ck_assert_int_eq(res.bits[1], 0);
//   ck_assert_int_eq(res.bits[2], 0);
//   ck_assert_int_eq(res.bits[3], 0);
// }
// END_TEST

START_TEST(div_test_12) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_div(val1, val2, &res));
}

END_TEST

START_TEST(div_test_13) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1639353344);
  ck_assert_int_eq(res.bits[1], 286);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(div_test_14) {
  s21_decimal val1 = {{123, 123, 123, 0x00050000}};
  s21_decimal val2 = {{1, 2, 3, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3942814950);
  ck_assert_int_eq(res.bits[1], 3297597181);
  ck_assert_int_eq(res.bits[2], 2222614453);
  ck_assert_int_eq(res.bits[3], 1441792);
}

END_TEST

START_TEST(div_test_15) {
  s21_decimal val1 = {{1234567890, 0, 0, 0x00050000}};
  s21_decimal val2 = {{0, 0, 0, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}

END_TEST

START_TEST(div_test_16) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2966737934);
  ck_assert_int_eq(res.bits[1], 2263411014);
  ck_assert_int_eq(res.bits[2], 752918170);
  ck_assert_int_eq(res.bits[3], 2148663296);
}

END_TEST

START_TEST(div_test_17) {
  s21_decimal val1 = {{123456, 0, 0, 0x00040000}};
  s21_decimal val2 = {{123, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1964161873);
  ck_assert_int_eq(res.bits[1], 2944270678);
  ck_assert_int_eq(res.bits[2], 54411082);
  ck_assert_int_eq(res.bits[3], 1835008);
}

END_TEST

START_TEST(div_test_18) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};
  s21_decimal val2 = {{3, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 89478485);
  ck_assert_int_eq(res.bits[1], 347537611);
  ck_assert_int_eq(res.bits[2], 180700362);
  ck_assert_int_eq(res.bits[3], 1835008);
}

END_TEST

/* MUL */

START_TEST(mul_test_1) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11101011000111110000101011010010;  // 12345678901234567890
  num1.bits[1] = 0b10101011010101001010100110001100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000010100111001;  // 1337
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] =
      0b11110101000111111000001011000010;  // 16506172690950617268930
  result.bits[1] = 0b11001101001010011000000011110111;
  result.bits[2] = 0b00000000000000000000001101111110;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_mul(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_2) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11101011000111110000101011010010;  // -12345678901234567890
  num1.bits[1] = 0b10101011010101001010100110001100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000010100111001;  // 1337
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] =
      0b11110101000111111000001011000010;  // -16506172690950617268930
  result.bits[1] = 0b11001101001010011000000011110111;
  result.bits[2] = 0b00000000000000000000001101111110;
  result.bits[3] = 0b10000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_mul(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_3) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11101011000111110000101011010010;  // -12345.678901234567890
  num1.bits[1] = 0b10101011010101001010100110001100;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000011110000000000000000;  // 15

  num2.bits[0] = 0b00000000000000000000010100111001;  // - 1337
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000010000000000000000;  // 1

  result.bits[0] =
      0b11110101000111111000001011000010;  // 1650617.2690950617268930
  result.bits[1] = 0b11001101001010011000000011110111;
  result.bits[2] = 0b00000000000000000000001101111110;
  result.bits[3] = 0b00000000000100000000000000000000;  // 16

  s21_mul(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_4) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11111111111111111111111111111111;
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000011110000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000000;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  //               0b00000000000000010000000000000000; степень 1 - 16 разряд
  s21_mul(num1, num2, &result2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_5) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11111111111111111111111111111111;
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000010;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_mul(num1, num2, &result2);  // 1
  ck_assert_int_eq(flag, 1);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_6) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11111111111111111111111111111111;
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000010;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b00000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_mul(num1, num2, &result2);  // 1
  ck_assert_int_eq(flag, 1);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

// START_TEST(mul_test_7) {
//   s21_decimal num1, num2, result, result2 = {0};
//   num1.bits[0] =
//       0b11111111111111111111111111111111;  // max =
//                                            // 79228162514264.337593543950335
//   num1.bits[1] = 0b11111111111111111111111111111111;
//   num1.bits[2] = 0b11111111111111111111111111111111;
//   num1.bits[3] = 0b00000000000011110000000000000000;  // 15

//   num2.bits[0] = 0b00000000000000000000000000000010;  // 2
//   num2.bits[1] = 0b00000000000000000000000000000000;
//   num2.bits[2] = 0b00000000000000000000000000000000;
//   num2.bits[3] = 0b00000000000000000000000000000000;

//   result.bits[0] =
//       0b00110011001100110011001100110100;  // 158456325028528.67518708790068
//                                            // (без бансковского на конце 7)
//   result.bits[1] = 0b00110011001100110011001100110011;
//   result.bits[2] = 0b00110011001100110011001100110011;
//   result.bits[3] = 0b00000000000011100000000000000000;  //  14

//   s21_mul(num1, num2, &result2);
//   ck_assert_int_eq(result.bits[0], result2.bits[0]);
//   ck_assert_int_eq(result.bits[1], result2.bits[1]);
//   ck_assert_int_eq(result.bits[2], result2.bits[2]);
//   ck_assert_int_eq(result.bits[3], result2.bits[3]);
// }
// END_TEST

START_TEST(mul_test_8) {
  s21_decimal num1, num2, result, result2 = {0};
  num1.bits[0] = 0b11111111111111111111111111111111;
  num1.bits[1] = 0b11111111111111111111111111111111;
  num1.bits[2] = 0b11111111111111111111111111111111;
  num1.bits[3] = 0b00000000000000000000000000000000;

  num2.bits[0] = 0b00000000000000000000000000000010;
  num2.bits[1] = 0b00000000000000000000000000000000;
  num2.bits[2] = 0b00000000000000000000000000000000;
  num2.bits[3] = 0b10000000000000000000000000000000;

  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  int flag = s21_mul(num1, num2, &result2);  // 2
  ck_assert_int_eq(flag, 2);
  ck_assert_int_eq(result.bits[0], result2.bits[0]);
  ck_assert_int_eq(result.bits[1], result2.bits[1]);
  ck_assert_int_eq(result.bits[2], result2.bits[2]);
  ck_assert_int_eq(result.bits[3], result2.bits[3]);
}

END_TEST

START_TEST(mul_test_9) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{4, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 492);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(mul_test_10) {
  s21_decimal val1 = {{15, 15, 15, 0x000F0000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 150);
  ck_assert_int_eq(res.bits[1], 150);
  ck_assert_int_eq(res.bits[2], 150);
  ck_assert_int_eq(res.bits[3], 983040);
}

END_TEST

START_TEST(mul_test_11) {
  s21_decimal val1 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 4294967294);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 720896);
}

END_TEST

START_TEST(mul_test_12) {
  s21_decimal val1 = {{127, 0, 0, 0x00000000}};
  s21_decimal val2 = {{229, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 29083);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(mul_test_13) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}

END_TEST

START_TEST(mul_test_14) {
  s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
  s21_decimal val2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(mul_test_15) {
  s21_decimal val1 = {{123456789, 900009, 1337, 0x00100000}};
  s21_decimal val2 = {{1, 1, 1111111, 0x80070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3773028595);
  ck_assert_int_eq(res.bits[1], 2256743337);
  ck_assert_int_eq(res.bits[2], 2740366469);
  ck_assert_int_eq(res.bits[3], 2147745792);
}

END_TEST

START_TEST(mul_test_16) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}

END_TEST

START_TEST(mul_test_17) {
  s21_decimal val1 = {{0XFFFFFFFF, 100, 0, 0}};
  s21_decimal val2 = {{0XFFFFFFFF, 100, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 4294967094);
  ck_assert_int_eq(res.bits[2], 10200);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(mul_test_18) {
  s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 4294967295);
  ck_assert_int_eq(res.bits[1], 4294967295);
  ck_assert_int_eq(res.bits[2], 4294967295);
  ck_assert_int_eq(res.bits[3], 1835008);
}

END_TEST

START_TEST(mul_test_19) {
  s21_decimal val1 = {{1241434324, 223, 64654654, 0x00060000}};
  s21_decimal val2 = {{7676767, 7465478, 12, 0x80070000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}

END_TEST

START_TEST(mul_test_20) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1797304573);
  ck_assert_int_eq(res.bits[1], 1947946003);
  ck_assert_int_eq(res.bits[2], 2024334038);
  ck_assert_int_eq(res.bits[3], 2148270080);
}

END_TEST

/* EQUAL */
START_TEST(s21_is_equal_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_equal_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_equal_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_equal_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_equal_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_equal_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_equal_test_7) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_equal_test_8) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_equal_test_9) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_equal_test_10) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_equal_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_equal_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_equal_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_equal_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_equal_test_15) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_16) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_equal_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_equal(dec_1, dec_2), 1);
}

END_TEST

/* GREATER OR EQUAL */
START_TEST(s21_is_greater_or_equal_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_7) {
  int num_1 = -4;
  int num_2 = 6;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_8) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_9) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_10) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_15) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_16) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_or_equal_test_22) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater_or_equal(dec_1, dec_2), 1);
}

END_TEST

/* GREATER */

START_TEST(s21_is_greater_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_7) {
  int num_1 = -4;
  int num_2 = 6;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_8) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_greater_test_9) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_10) {
  float num_1 = -42.46565725766751567;
  float num_2 = -42.465;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_greater(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_greater_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}

END_TEST

START_TEST(s21_is_greater_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}

END_TEST

START_TEST(s21_is_greater_test_15) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}

END_TEST

START_TEST(s21_is_greater_test_16) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}

END_TEST

START_TEST(s21_is_greater_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_greater_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_greater_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_test_22) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_greater_test_23) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_greater(dec_1, dec_2), 0);
}

END_TEST

/* LESS OR EQUAL */
START_TEST(s21_is_less_or_equal_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_7) {
  int num_1 = -4;
  int num_2 = 6;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_8) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_9) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_10) {
  float num_1 = -42.46565725766751567;
  float num_2 = -42.465;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less_or_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_15) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_16) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_22) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_or_equal_test_23) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less_or_equal(dec_1, dec_2), 1);
}

END_TEST

/* LESS */
START_TEST(s21_is_less_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_7) {
  int num_1 = -4;
  int num_2 = 6;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_less_test_8) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_9) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_less(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_less_test_10) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_15) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test_16) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_less_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 0);
}

END_TEST

START_TEST(s21_is_less_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_less_test_22) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(dec_1, dec_2), 0);
}

END_TEST

/* NOT EQUAL */
START_TEST(s21_is_not_equal_test_1) {
  float num_1 = 1.375342323523;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_2) {
  float num_1 = 1.39;
  float num_2 = 1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_3) {
  float num_1 = 1.39;
  float num_2 = -1.39;
  s21_decimal dec_1, dec_2;
  s21_from_float_to_decimal(num_1, &dec_1);
  s21_from_float_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_4) {
  int num_1 = 0;
  int num_2 = 0;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_5) {
  int num_1 = 9;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_6) {
  int num_1 = 4;
  int num_2 = 4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_7) {
  int num_1 = -4;
  int num_2 = -7;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_8) {
  int num_1 = -4;
  int num_2 = -4;
  s21_decimal dec_1, dec_2;
  s21_from_int_to_decimal(num_1, &dec_1);
  s21_from_int_to_decimal(num_2, &dec_2);
  int res = s21_is_not_equal(dec_1, dec_2);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_9) {
  s21_decimal a = {0};
  a.bits[0] = 2;
  s21_decimal b = {0};
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_10) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  s21_decimal b = {0};
  b.bits[0] = 13;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_11) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 1;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_12) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 2;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 2;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_13) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 12;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_14) {
  s21_decimal a = {0};
  a.bits[0] = 13;
  a.bits[1] = 32;
  a.bits[2] = 21;
  s21_decimal b = {0};
  b.bits[0] = 13;
  b.bits[1] = 32;
  b.bits[2] = 21;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}

END_TEST

START_TEST(s21_is_not_equal_test_15) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_16) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_17) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000000;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_18) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000011;
  dec_2.bits[1] = 0b00000000000000000000000011111111;
  dec_2.bits[2] = 0b00000000000000000000000000000000;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_19) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_20) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b10000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 1);
}

END_TEST

START_TEST(s21_is_not_equal_test_21) {
  s21_decimal dec_1;
  s21_decimal dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000001;
  dec_1.bits[2] = 0b00000000000000000000000000000001;
  dec_1.bits[3] = 0b00000000000000000000000000000000;
  dec_2.bits[0] = 0b00000000000000000000000000000001;
  dec_2.bits[1] = 0b00000000000000000000000000000001;
  dec_2.bits[2] = 0b00000000000000000000000000000001;
  dec_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(s21_is_not_equal(dec_1, dec_2), 0);
}

END_TEST

/* FROM DECIMAL TO FLOAT */
START_TEST(s21_from_decimal_to_float_test_1) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000010000110000110010001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", -5.49265);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_2) {
  s21_decimal dec;
  int res = 0;
  float number = 0.0;
  long int c = 2147483648;
  dec.bits[0] = 1812;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;
  res = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_3) {
  s21_decimal dec;
  int res = 0;
  float number = 0.0;
  dec.bits[0] = 0XFFFFFF;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  res = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_4) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000000000110001101111001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", 2546.5);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_5) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000000001011010101110101;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", -0.46453);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_6) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000100011;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", 3.5);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_7) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000101101;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", 4.5);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_8) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000000000000000000101101;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", -4.5);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

START_TEST(s21_from_decimal_to_float_test_9) {
  s21_decimal dec_1;
  float dec_2;
  float *dec = &dec_2;
  dec_1.bits[0] = 0b00000000000010000110000110010001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(dec_1, dec);
  char var3dec[1000];
  char result[1000];
  snprintf(var3dec, sizeof(var3dec), "%.6f", -5.49265);
  snprintf(result, sizeof(result), "%f", dec_2);
  ck_assert_str_eq(result, var3dec);
}

END_TEST

/* FROM DECIMAL TO INT */
START_TEST(s21_from_decimal_to_int_test_1) {
  s21_decimal dec;
  int res = 0;
  int number = 0;
  dec.bits[0] = 133151;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, 133151);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  s21_decimal dec;
  int res = 0;
  int number = 0;
  dec.bits[0] = 2147483647;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  s21_decimal dec;
  int res = 0;
  int number = 0;
  dec.bits[0] = 133151;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -133151);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  s21_decimal dec;
  int res = 0;
  int number = 0;
  dec.bits[0] = 18;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
  s21_decimal dec;
  int res = 0;
  int number = 0;
  dec.bits[0] = 18;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, 18);
  ck_assert_int_eq(res, 0);
}

END_TEST

START_TEST(s21_from_decimal_to_int_test_6) {
  s21_decimal dec = {0};
  dec.bits[0] = 100;
  int check = 100;
  int result;
  int res = s21_from_decimal_to_int(dec, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(res, 0);
}

END_TEST

/* FROM FLOAT TO DECIMAL */

START_TEST(s21_from_float_to_decimal_test_1) {
  s21_decimal dec, result;
  s21_decimal *res = &result;
  float num = 1.0;
  s21_from_float_to_decimal(num, res);
  dec.bits[0] = 0b00000000000000000000000000000001;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(dec.bits[3], result.bits[3]);
  ck_assert_float_eq(dec.bits[2], result.bits[2]);
  ck_assert_float_eq(dec.bits[1], result.bits[1]);
  ck_assert_float_eq(dec.bits[0], result.bits[0]);
}

END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  s21_decimal dec, result;
  s21_decimal *res = &result;
  float num = -1.0;
  s21_from_float_to_decimal(num, res);
  dec.bits[0] = 0b00000000000000000000000000000001;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(dec.bits[3], result.bits[3]);
  ck_assert_float_eq(dec.bits[2], result.bits[2]);
  ck_assert_float_eq(dec.bits[1], result.bits[1]);
  ck_assert_float_eq(dec.bits[0], result.bits[0]);
}

END_TEST

/* FROM INT TO DECIMAL */
START_TEST(s21_from_int_to_decimal_test_1) {
  int num = 1;
  s21_decimal dec, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(num, res);
  dec.bits[0] = 0b00000000000000000000000000000001;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(dec.bits[3], result.bits[3]);
  ck_assert_int_eq(dec.bits[2], result.bits[2]);
  ck_assert_int_eq(dec.bits[1], result.bits[1]);
  ck_assert_int_eq(dec.bits[0], result.bits[0]);
}

END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  int num = -1;
  s21_decimal dec, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(num, res);
  dec.bits[0] = 0b00000000000000000000000000000001;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(dec.bits[3], result.bits[3]);
  ck_assert_int_eq(dec.bits[2], result.bits[2]);
  ck_assert_int_eq(dec.bits[1], result.bits[1]);
  ck_assert_int_eq(dec.bits[0], result.bits[0]);
}

END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  int num = -987879878;
  s21_decimal dec, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(num, res);
  dec.bits[0] = 0b00111010111000011101100111000110;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(dec.bits[3], result.bits[3]);
  ck_assert_int_eq(dec.bits[2], result.bits[2]);
  ck_assert_int_eq(dec.bits[1], result.bits[1]);
  ck_assert_int_eq(dec.bits[0], result.bits[0]);
}

END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  int num = -2147483646;
  s21_decimal dec, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(num, res);
  dec.bits[0] = 0b01111111111111111111111111111110;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(dec.bits[3], result.bits[3]);
  ck_assert_int_eq(dec.bits[2], result.bits[2]);
  ck_assert_int_eq(dec.bits[1], result.bits[1]);
  ck_assert_int_eq(dec.bits[0], result.bits[0]);
}

END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
  int num = 2147483646;
  s21_decimal dec, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(num, res);
  dec.bits[0] = 0b01111111111111111111111111111110;
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(dec.bits[3], result.bits[3]);
  ck_assert_int_eq(dec.bits[2], result.bits[2]);
  ck_assert_int_eq(dec.bits[1], result.bits[1]);
  ck_assert_int_eq(dec.bits[0], result.bits[0]);
}

END_TEST

/* FLOOR */
START_TEST(s21_floor_test_1) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000011010011;  // 21.1
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000010101;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000000010100101;  // 214.7483813
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000011010110;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_3) {
  s21_decimal dec;
  dec.bits[0] =
      0b11111111111111111111111111111111;  // 7922816251426433759354395033.5
  dec.bits[1] = 0b11111111111111111111111111111111;
  dec.bits[2] = 0b11111111111111111111111111111111;
  dec.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10011001100110011001100110011001;
  res.bits[1] = 0b10011001100110011001100110011001;
  res.bits[2] = 0b00011001100110011001100110011001;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_4) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
  dec.bits[1] = 0b00000000000001000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000110101101011111110101111101;  // 112590205
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_5) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_6) {
  s21_decimal dec;
  dec.bits[0] = 2;  // 2
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 2;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_7) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // 3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_8) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // -3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_9) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000000000;  // 0
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000000;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_10) {
  s21_decimal dec;
  dec.bits[0] = 0b01001100110100101000000111000101;  // 9878798789
  dec.bits[1] = 0b00000000000000000000000000000010;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b01001100110100101000000111000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_11) {
  s21_decimal dec;
  dec.bits[0] =
      0b00000111100110110001111110011000;  // -5.492654545456454545645464
  dec.bits[1] = 0b01100110010010001001000110100011;
  dec.bits[2] = 0b00000000000001001000101100011101;
  dec.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_12) {
  s21_decimal dec;
  dec.bits[0] =
      0b01001110111001000011100101110110;  // 7961327845421.879754123131254
  dec.bits[1] = 0b01001011001101011010000111011001;
  dec.bits[2] = 0b00011001101110010111010010111111;
  dec.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10100100000111100100000000101110;
  res.bits[1] = 0b00000000000000000000011100111101;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_13) {
  s21_decimal dec;
  dec.bits[0] =
      0b01111000100010101111010011001010;  // -12345677.187654345678987654346
  dec.bits[1] = 0b01100010000010101110010010000111;
  dec.bits[2] = 0b00100111111001000001101011010101;
  dec.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000101111000110000101001101;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_14) {
  s21_decimal dec;
  dec.bits[0] = 0b10101111110010001101100101011111;  // 2.5986531268974139743
  dec.bits[1] = 0b01101000101000101011010010000001;
  dec.bits[2] = 0b00000000000000000000000000000001;
  dec.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000010;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_floor_test_15) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 2576980378);
  ck_assert_int_eq(res.bits[1], 2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_floor_test_16) {
  s21_decimal number = {{1234567890, 0, 0, 0x00020000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 12345678);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_floor_test_17) {
  s21_decimal number = {{123, 123, 123, 0x000F0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 2268949);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_floor_test_18) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 4294967295);
  ck_assert_int_eq(res.bits[1], 4294967295);
  ck_assert_int_eq(res.bits[2], 4294967295);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_floor_test_19) {
  s21_decimal number = {{1234567890, 987654321, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_floor_test_20) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_floor_test_21) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1841348007);
  ck_assert_int_eq(res.bits[1], 5302);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_floor_test_22) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

/* NEGATE */
START_TEST(s21_negate_test_1) {
  int num = 15;
  int res_num = 0;
  s21_decimal dec;
  s21_decimal res;
  s21_from_int_to_decimal(num, &dec);
  s21_negate(dec, &res);
  s21_from_decimal_to_int(res, &res_num);
  ck_assert_int_eq(-15, res_num);
}

END_TEST

START_TEST(s21_negate_test_2) {
  float num = 10.1243;
  float res_num = 0;
  s21_decimal dec;
  s21_decimal res;
  s21_from_float_to_decimal(num, &dec);
  s21_negate(dec, &res);
  s21_from_decimal_to_float(res, &res_num);
  ck_assert_float_eq(-10.1243, res_num);
}

END_TEST

START_TEST(s21_negate_test_3) {
  float num = 10.1243e5;
  float res_num = 0;
  s21_decimal dec;
  s21_decimal res;
  s21_from_float_to_decimal(num, &dec);
  s21_negate(dec, &res);
  s21_from_decimal_to_float(res, &res_num);
  ck_assert_float_eq(-10.1243e5, res_num);
}

END_TEST

START_TEST(s21_negate_test_4) {
  float num = -10.1243;
  float res_num = 0;
  s21_decimal dec;
  s21_decimal res;
  s21_from_float_to_decimal(num, &dec);
  s21_negate(dec, &res);
  s21_from_decimal_to_float(res, &res_num);
  ck_assert_float_eq(10.1243, res_num);
}

END_TEST

START_TEST(s21_negate_test_5) {
  float num = 578326783;
  float res_num = 0;
  s21_decimal dec;
  s21_decimal res;
  s21_from_float_to_decimal(num, &dec);
  s21_negate(dec, &res);
  s21_from_decimal_to_float(res, &res_num);
  ck_assert_float_eq(-578326783, res_num);
}

END_TEST

/* ROUND */
START_TEST(s21_round_test_1) {
  s21_decimal dec;
  dec.bits[0] = 0b10010011111100000001110001010010;
  dec.bits[1] = 0b00000000000000000000000100100000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000001111100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000010100101;  // -16.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000010000;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal dec;
  dec.bits[0] = 0b11111111111111111111111111111111;  // 18014398509481.983
  dec.bits[1] = 0b00000000001111111111111111111111;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b01001101110100101111000110101001;  // 18014398509481
  res.bits[1] = 0b00000000000000000001000001100010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_4) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000011110111001001110100;  // -10123.40
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000001111110100;  // -1012
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_5) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
  dec.bits[1] = 0b00000000000001000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000110101101011111110101111101;  // 112590205
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_6) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_7) {
  s21_decimal dec;
  dec.bits[0] = 2;  // 2
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 2;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_8) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // 3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_9) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // -3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_10) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000000000;  // 0
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000000;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_11) {
  s21_decimal dec;
  dec.bits[0] = 0b01001100110100101000000111000101;  // 9878798789
  dec.bits[1] = 0b00000000000000000000000000000010;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b01001100110100101000000111000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_12) {
  s21_decimal dec;
  dec.bits[0] =
      0b00000111100110110001111110011000;  // -5.492654545456454545645464
  dec.bits[1] = 0b01100110010010001001000110100011;
  dec.bits[2] = 0b00000000000001001000101100011101;
  dec.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_13) {
  s21_decimal dec;
  dec.bits[0] =
      0b01001110111001000011100101110110;  // 7961327845421.879754123131254
  dec.bits[1] = 0b01001011001101011010000111011001;
  dec.bits[2] = 0b00011001101110010111010010111111;
  dec.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10100100000111100100000000101110;
  res.bits[1] = 0b00000000000000000000011100111101;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_14) {
  s21_decimal dec;
  dec.bits[0] =
      0b01111000100010101111010011001010;  // -12345677.187654345678987654346
  dec.bits[1] = 0b01100010000010101110010010000111;
  dec.bits[2] = 0b00100111111001000001101011010101;
  dec.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000101111000110000101001101;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_15) {
  s21_decimal dec;
  dec.bits[0] = 0b10101111110010001101100101011111;  // 2.5986531268974139743
  dec.bits[1] = 0b01101000101000101011010010000001;
  dec.bits[2] = 0b00000000000000000000000000000001;
  dec.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000010;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_round(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_round_test_16) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 2576980378);
  ck_assert_int_eq(res.bits[1], 2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_round_test_17) {
  s21_decimal number = {{1234567890, 0, 0, 0x00020000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 12345679);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_round_test_18) {
  s21_decimal number = {{123, 123, 123, 0x000F0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 2268950);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_round_test_19) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 4294967295);
  ck_assert_int_eq(res.bits[1], 4294967295);
  ck_assert_int_eq(res.bits[2], 4294967295);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_round_test_20) {
  s21_decimal number = {{1234567890, 987654321, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_round_test_21) {
  s21_decimal number = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 2576980376);
  ck_assert_int_eq(res.bits[1], 2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_round_test_22) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

START_TEST(s21_round_test_23) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 1841348007);
  ck_assert_int_eq(res.bits[1], 5302);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}

END_TEST

START_TEST(s21_round_test_24) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_round(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}

END_TEST

/* TRUNCATE */
START_TEST(s21_truncate_test_1) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000011010011;  // 21.1
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000010101;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000000010100101;  // 214.7483813
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000011010110;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal dec;
  dec.bits[0] =
      0b11111111111111111111111111111111;  // 7922816251426433759354395033.5
  dec.bits[1] = 0b11111111111111111111111111111111;
  dec.bits[2] = 0b11111111111111111111111111111111;
  dec.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10011001100110011001100110011001;
  res.bits[1] = 0b10011001100110011001100110011001;
  res.bits[2] = 0b00011001100110011001100110011001;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_4) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
  dec.bits[1] = 0b00000000000001000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000110101101011111110101111101;  // 112590205
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_5) {
  s21_decimal dec;
  dec.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_6) {
  s21_decimal dec;
  dec.bits[0] = 2;  // 2
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 2;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_7) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // 3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_8) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000100011;  // -3.5
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000100;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_9) {
  s21_decimal dec;
  dec.bits[0] = 0b00000000000000000000000000000000;  // 0
  dec.bits[1] = 0b00000000000000000000000000000000;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000000;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_10) {
  s21_decimal dec;
  dec.bits[0] = 0b01001100110100101000000111000101;  // 9878798789
  dec.bits[1] = 0b00000000000000000000000000000010;
  dec.bits[2] = 0b00000000000000000000000000000000;
  dec.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b01001100110100101000000111000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_11) {
  s21_decimal dec;
  dec.bits[0] =
      0b00000111100110110001111110011000;  // -5.492654545456454545645464
  dec.bits[1] = 0b01100110010010001001000110100011;
  dec.bits[2] = 0b00000000000001001000101100011101;
  dec.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000101;
  res.bits[1] = 0b00000000000000000000000000000010;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_12) {
  s21_decimal dec;
  dec.bits[0] =
      0b01001110111001000011100101110110;  // 7961327845421.879754123131254
  dec.bits[1] = 0b01001011001101011010000111011001;
  dec.bits[2] = 0b00011001101110010111010010111111;
  dec.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b10100100000111100100000000101110;
  res.bits[1] = 0b00000000000000000000011100111101;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_13) {
  s21_decimal dec;
  dec.bits[0] =
      0b01111000100010101111010011001010;  // -12345677.187654345678987654346
  dec.bits[1] = 0b01100010000010101110010010000111;
  dec.bits[2] = 0b00100111111001000001101011010101;
  dec.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000101111000110000101001101;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b10000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test_14) {
  s21_decimal dec;
  dec.bits[0] = 0b10101111110010001101100101011111;  // 2.5986531268974139743
  dec.bits[1] = 0b01101000101000101011010010000001;
  dec.bits[2] = 0b00000000000000000000000000000001;
  dec.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal res;
  res.bits[0] = 0b00000000000000000000000000000010;
  res.bits[1] = 0b00000000000000000000000000000000;
  res.bits[2] = 0b00000000000000000000000000000000;
  res.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(dec, &res);
  ck_assert_float_eq(res.bits[0], res.bits[0]);
  ck_assert_float_eq(res.bits[1], res.bits[1]);
  ck_assert_float_eq(res.bits[2], res.bits[2]);
  ck_assert_float_eq(res.bits[3], res.bits[3]);
}

END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tc_add = tcase_create("s21_add_test_case");
  tcase_add_test(tc_add, add_test_1);
  tcase_add_test(tc_add, add_test_2);
  tcase_add_test(tc_add, add_test_3);
  tcase_add_test(tc_add, add_test_4);
  tcase_add_test(tc_add, add_test_5);
  tcase_add_test(tc_add, add_test_6);
  tcase_add_test(tc_add, add_test_7);
  tcase_add_test(tc_add, add_test_8);
  tcase_add_test(tc_add, add_test_9);
  tcase_add_test(tc_add, add_test_10);
  tcase_add_test(tc_add, add_test_11);
  tcase_add_test(tc_add, add_test_12);
  tcase_add_test(tc_add, add_test_13);
  tcase_add_test(tc_add, add_test_14);
  tcase_add_test(tc_add, add_test_15);
  tcase_add_test(tc_add, add_test_16);
  tcase_add_test(tc_add, add_test_17);
  tcase_add_test(tc_add, add_test_18);
  tcase_add_test(tc_add, add_test_19);
  tcase_add_test(tc_add, add_test_20);
  tcase_add_test(tc_add, add_test_21);
  tcase_add_test(tc_add, add_test_22);
  tcase_add_test(tc_add, add_test_23);
  tcase_add_test(tc_add, add_test_24);
  suite_add_tcase(suite, tc_add);

  TCase *tc_div = tcase_create("s21_div_test_case");
  tcase_add_test(tc_div, div_test_1);
  tcase_add_test(tc_div, div_test_2);
  tcase_add_test(tc_div, div_test_3);
  tcase_add_test(tc_div, div_test_4);
  tcase_add_test(tc_div, div_test_5);
  tcase_add_test(tc_div, div_test_6);
  tcase_add_test(tc_div, div_test_7);
  tcase_add_test(tc_div, div_test_8);
  tcase_add_test(tc_div, div_test_9);
  tcase_add_test(tc_div, div_test_10);
  // tcase_add_test(tc, div_test_11);
  tcase_add_test(tc_div, div_test_12);
  tcase_add_test(tc_div, div_test_13);
  tcase_add_test(tc_div, div_test_14);
  tcase_add_test(tc_div, div_test_15);
  tcase_add_test(tc_div, div_test_16);
  tcase_add_test(tc_div, div_test_17);
  tcase_add_test(tc_div, div_test_18);
  suite_add_tcase(suite, tc_div);

  TCase *tc_sub = tcase_create("s21_sub_test_case");
  tcase_add_test(tc_sub, sub_test_1);
  tcase_add_test(tc_sub, sub_test_2);
  tcase_add_test(tc_sub, sub_test_3);
  tcase_add_test(tc_sub, sub_test_4);
  tcase_add_test(tc_sub, sub_test_5);
  tcase_add_test(tc_sub, sub_test_6);
  tcase_add_test(tc_sub, sub_test_7);
  tcase_add_test(tc_sub, sub_test_8);
  tcase_add_test(tc_sub, sub_test_9);
  tcase_add_test(tc_sub, sub_test_10);
  tcase_add_test(tc_sub, sub_test_11);
  tcase_add_test(tc_sub, sub_test_12);
  tcase_add_test(tc_sub, sub_test_13);
  tcase_add_test(tc_sub, sub_test_14);
  tcase_add_test(tc_sub, sub_test_15);
  tcase_add_test(tc_sub, sub_test_16);
  tcase_add_test(tc_sub, sub_test_17);
  tcase_add_test(tc_sub, sub_test_18);
  tcase_add_test(tc_sub, sub_test_19);
  tcase_add_test(tc_sub, sub_test_20);
  tcase_add_test(tc_sub, sub_test_21);
  tcase_add_test(tc_sub, sub_test_22);
  suite_add_tcase(suite, tc_sub);

  TCase *tc_mul = tcase_create("s21_mul_test_case");
  tcase_add_test(tc_mul, mul_test_1);
  tcase_add_test(tc_mul, mul_test_2);
  tcase_add_test(tc_mul, mul_test_3);
  tcase_add_test(tc_mul, mul_test_4);
  tcase_add_test(tc_mul, mul_test_5);
  tcase_add_test(tc_mul, mul_test_6);
  // tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc_mul, mul_test_8);
  tcase_add_test(tc_mul, mul_test_9);
  tcase_add_test(tc_mul, mul_test_10);
  tcase_add_test(tc_mul, mul_test_11);
  tcase_add_test(tc_mul, mul_test_12);
  tcase_add_test(tc_mul, mul_test_13);
  tcase_add_test(tc_mul, mul_test_14);
  tcase_add_test(tc_mul, mul_test_15);
  tcase_add_test(tc_mul, mul_test_16);
  tcase_add_test(tc_mul, mul_test_17);
  tcase_add_test(tc_mul, mul_test_18);
  tcase_add_test(tc_mul, mul_test_19);
  tcase_add_test(tc_mul, mul_test_20);
  suite_add_tcase(suite, tc_mul);

  TCase *tc_from_int_to_decimal = tcase_create("s21_from_int_to_decimal_tc");
  tcase_add_test(tc_from_int_to_decimal, s21_from_int_to_decimal_test_1);
  tcase_add_test(tc_from_int_to_decimal, s21_from_int_to_decimal_test_2);
  tcase_add_test(tc_from_int_to_decimal, s21_from_int_to_decimal_test_3);
  tcase_add_test(tc_from_int_to_decimal, s21_from_int_to_decimal_test_4);
  tcase_add_test(tc_from_int_to_decimal, s21_from_int_to_decimal_test_5);
  suite_add_tcase(suite, tc_from_int_to_decimal);

  TCase *tc_from_decimal_to_int = tcase_create("s21_from_decimal_to_int_tc");
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_1);
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_2);
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_3);
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_4);
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_5);
  tcase_add_test(tc_from_decimal_to_int, s21_from_decimal_to_int_test_6);
  suite_add_tcase(suite, tc_from_decimal_to_int);

  TCase *tc_from_decimal_to_float =
      tcase_create("s21_from_decimal_to_float_tc");
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_1);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_2);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_3);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_4);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_5);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_6);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_7);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_8);
  tcase_add_test(tc_from_decimal_to_float, s21_from_decimal_to_float_test_9);
  suite_add_tcase(suite, tc_from_decimal_to_float);

  TCase *tc_from_float_to_decimal =
      tcase_create("s21_from_float_to_decimal_tc");
  tcase_add_test(tc_from_float_to_decimal, s21_from_float_to_decimal_test_1);
  tcase_add_test(tc_from_float_to_decimal, s21_from_float_to_decimal_test_2);
  suite_add_tcase(suite, tc_from_float_to_decimal);

  TCase *tc_is_less = tcase_create("s21_is_less_tc");
  tcase_add_test(tc_is_less, s21_is_less_test_1);
  tcase_add_test(tc_is_less, s21_is_less_test_2);
  tcase_add_test(tc_is_less, s21_is_less_test_3);
  tcase_add_test(tc_is_less, s21_is_less_test_4);
  tcase_add_test(tc_is_less, s21_is_less_test_5);
  tcase_add_test(tc_is_less, s21_is_less_test_6);
  tcase_add_test(tc_is_less, s21_is_less_test_7);
  tcase_add_test(tc_is_less, s21_is_less_test_8);
  tcase_add_test(tc_is_less, s21_is_less_test_9);
  tcase_add_test(tc_is_less, s21_is_less_test_10);
  tcase_add_test(tc_is_less, s21_is_less_test_11);
  tcase_add_test(tc_is_less, s21_is_less_test_12);
  tcase_add_test(tc_is_less, s21_is_less_test_13);
  tcase_add_test(tc_is_less, s21_is_less_test_14);
  tcase_add_test(tc_is_less, s21_is_less_test_15);
  tcase_add_test(tc_is_less, s21_is_less_test_16);
  tcase_add_test(tc_is_less, s21_is_less_test_17);
  tcase_add_test(tc_is_less, s21_is_less_test_18);
  tcase_add_test(tc_is_less, s21_is_less_test_19);
  tcase_add_test(tc_is_less, s21_is_less_test_20);
  tcase_add_test(tc_is_less, s21_is_less_test_21);
  tcase_add_test(tc_is_less, s21_is_less_test_22);
  suite_add_tcase(suite, tc_is_less);

  TCase *tc_is_less_or_equal = tcase_create("s21_is_less_or_equal_tc");
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_1);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_2);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_3);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_4);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_5);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_6);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_7);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_8);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_9);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_10);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_11);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_12);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_13);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_14);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_15);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_16);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_17);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_18);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_19);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_20);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_21);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_22);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_test_23);
  suite_add_tcase(suite, tc_is_less_or_equal);

  TCase *tc_is_greater = tcase_create("s21_is_greater_tc");
  tcase_add_test(tc_is_greater, s21_is_greater_test_1);
  tcase_add_test(tc_is_greater, s21_is_greater_test_2);
  tcase_add_test(tc_is_greater, s21_is_greater_test_3);
  tcase_add_test(tc_is_greater, s21_is_greater_test_4);
  tcase_add_test(tc_is_greater, s21_is_greater_test_5);
  tcase_add_test(tc_is_greater, s21_is_greater_test_6);
  tcase_add_test(tc_is_greater, s21_is_greater_test_7);
  tcase_add_test(tc_is_greater, s21_is_greater_test_8);
  tcase_add_test(tc_is_greater, s21_is_greater_test_9);
  tcase_add_test(tc_is_greater, s21_is_greater_test_10);
  tcase_add_test(tc_is_greater, s21_is_greater_test_11);
  tcase_add_test(tc_is_greater, s21_is_greater_test_12);
  tcase_add_test(tc_is_greater, s21_is_greater_test_13);
  tcase_add_test(tc_is_greater, s21_is_greater_test_14);
  tcase_add_test(tc_is_greater, s21_is_greater_test_15);
  tcase_add_test(tc_is_greater, s21_is_greater_test_16);
  tcase_add_test(tc_is_greater, s21_is_greater_test_17);
  tcase_add_test(tc_is_greater, s21_is_greater_test_18);
  tcase_add_test(tc_is_greater, s21_is_greater_test_19);
  tcase_add_test(tc_is_greater, s21_is_greater_test_20);
  tcase_add_test(tc_is_greater, s21_is_greater_test_21);
  tcase_add_test(tc_is_greater, s21_is_greater_test_22);
  tcase_add_test(tc_is_greater, s21_is_greater_test_23);
  suite_add_tcase(suite, tc_is_greater);

  TCase *tc_is_greater_or_equal = tcase_create("s21_is_greater_or_equal_tc");
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_1);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_2);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_3);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_4);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_5);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_6);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_7);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_8);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_9);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_10);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_11);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_12);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_13);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_14);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_15);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_16);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_17);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_18);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_19);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_20);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_21);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_test_22);
  suite_add_tcase(suite, tc_is_greater_or_equal);

  TCase *tc_is_equal = tcase_create("s21_is_equal_tc");
  tcase_add_test(tc_is_equal, s21_is_equal_test_1);
  tcase_add_test(tc_is_equal, s21_is_equal_test_2);
  tcase_add_test(tc_is_equal, s21_is_equal_test_3);
  tcase_add_test(tc_is_equal, s21_is_equal_test_4);
  tcase_add_test(tc_is_equal, s21_is_equal_test_5);
  tcase_add_test(tc_is_equal, s21_is_equal_test_6);
  tcase_add_test(tc_is_equal, s21_is_equal_test_7);
  tcase_add_test(tc_is_equal, s21_is_equal_test_8);
  tcase_add_test(tc_is_equal, s21_is_equal_test_9);
  tcase_add_test(tc_is_equal, s21_is_equal_test_10);
  tcase_add_test(tc_is_equal, s21_is_equal_test_11);
  tcase_add_test(tc_is_equal, s21_is_equal_test_12);
  tcase_add_test(tc_is_equal, s21_is_equal_test_13);
  tcase_add_test(tc_is_equal, s21_is_equal_test_14);
  tcase_add_test(tc_is_equal, s21_is_equal_test_15);
  tcase_add_test(tc_is_equal, s21_is_equal_test_16);
  tcase_add_test(tc_is_equal, s21_is_equal_test_17);
  tcase_add_test(tc_is_equal, s21_is_equal_test_18);
  tcase_add_test(tc_is_equal, s21_is_equal_test_19);
  tcase_add_test(tc_is_equal, s21_is_equal_test_20);
  tcase_add_test(tc_is_equal, s21_is_equal_test_21);
  suite_add_tcase(suite, tc_is_equal);

  TCase *tc_is_not_equal = tcase_create("s21_is_not_equal_tc");
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_1);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_2);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_3);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_4);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_5);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_6);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_7);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_8);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_9);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_10);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_11);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_12);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_13);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_14);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_15);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_16);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_17);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_18);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_19);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_20);
  tcase_add_test(tc_is_not_equal, s21_is_not_equal_test_21);
  suite_add_tcase(suite, tc_is_not_equal);

  TCase *tc_negate = tcase_create("s21_negate_tc");
  tcase_add_test(tc_negate, s21_negate_test_1);
  tcase_add_test(tc_negate, s21_negate_test_2);
  tcase_add_test(tc_negate, s21_negate_test_3);
  tcase_add_test(tc_negate, s21_negate_test_4);
  tcase_add_test(tc_negate, s21_negate_test_5);
  suite_add_tcase(suite, tc_negate);

  TCase *tc_floor = tcase_create("s21_floor_tc");
  tcase_add_test(tc_floor, s21_floor_test_1);
  tcase_add_test(tc_floor, s21_floor_test_2);
  tcase_add_test(tc_floor, s21_floor_test_3);
  tcase_add_test(tc_floor, s21_floor_test_4);
  tcase_add_test(tc_floor, s21_floor_test_5);
  tcase_add_test(tc_floor, s21_floor_test_6);
  tcase_add_test(tc_floor, s21_floor_test_7);
  tcase_add_test(tc_floor, s21_floor_test_8);
  tcase_add_test(tc_floor, s21_floor_test_9);
  tcase_add_test(tc_floor, s21_floor_test_10);
  tcase_add_test(tc_floor, s21_floor_test_11);
  tcase_add_test(tc_floor, s21_floor_test_12);
  tcase_add_test(tc_floor, s21_floor_test_13);
  tcase_add_test(tc_floor, s21_floor_test_14);
  tcase_add_test(tc_floor, s21_floor_test_15);
  tcase_add_test(tc_floor, s21_floor_test_16);
  tcase_add_test(tc_floor, s21_floor_test_17);
  tcase_add_test(tc_floor, s21_floor_test_18);
  tcase_add_test(tc_floor, s21_floor_test_19);
  tcase_add_test(tc_floor, s21_floor_test_20);
  tcase_add_test(tc_floor, s21_floor_test_21);
  tcase_add_test(tc_floor, s21_floor_test_22);
  suite_add_tcase(suite, tc_floor);

  TCase *tc_round = tcase_create("s21_round_tc");
  tcase_add_test(tc_round, s21_round_test_1);
  tcase_add_test(tc_round, s21_round_test_2);
  tcase_add_test(tc_round, s21_round_test_3);
  tcase_add_test(tc_round, s21_round_test_4);
  tcase_add_test(tc_round, s21_round_test_5);
  tcase_add_test(tc_round, s21_round_test_6);
  tcase_add_test(tc_round, s21_round_test_7);
  tcase_add_test(tc_round, s21_round_test_8);
  tcase_add_test(tc_round, s21_round_test_9);
  tcase_add_test(tc_round, s21_round_test_10);
  tcase_add_test(tc_round, s21_round_test_11);
  tcase_add_test(tc_round, s21_round_test_12);
  tcase_add_test(tc_round, s21_round_test_13);
  tcase_add_test(tc_round, s21_round_test_14);
  tcase_add_test(tc_round, s21_round_test_15);
  tcase_add_test(tc_round, s21_round_test_16);
  tcase_add_test(tc_round, s21_round_test_17);
  tcase_add_test(tc_round, s21_round_test_18);
  tcase_add_test(tc_round, s21_round_test_19);
  tcase_add_test(tc_round, s21_round_test_20);
  tcase_add_test(tc_round, s21_round_test_21);
  tcase_add_test(tc_round, s21_round_test_22);
  tcase_add_test(tc_round, s21_round_test_23);
  tcase_add_test(tc_round, s21_round_test_24);
  suite_add_tcase(suite, tc_round);

  TCase *tc_truncate = tcase_create("s21_truncate_tc");
  tcase_add_test(tc_truncate, s21_truncate_test_1);
  tcase_add_test(tc_truncate, s21_truncate_test_2);
  tcase_add_test(tc_truncate, s21_truncate_test_3);
  tcase_add_test(tc_truncate, s21_truncate_test_4);
  tcase_add_test(tc_truncate, s21_truncate_test_5);
  tcase_add_test(tc_truncate, s21_truncate_test_6);
  tcase_add_test(tc_truncate, s21_truncate_test_7);
  tcase_add_test(tc_truncate, s21_truncate_test_8);
  tcase_add_test(tc_truncate, s21_truncate_test_9);
  tcase_add_test(tc_truncate, s21_truncate_test_10);
  tcase_add_test(tc_truncate, s21_truncate_test_11);
  tcase_add_test(tc_truncate, s21_truncate_test_12);
  tcase_add_test(tc_truncate, s21_truncate_test_13);
  tcase_add_test(tc_truncate, s21_truncate_test_14);
  suite_add_tcase(suite, tc_truncate);

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
