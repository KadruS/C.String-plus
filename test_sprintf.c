#include "test_me.h"

// WITHOUT ARGS
START_TEST(sprintf_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World");
  sprintf(str1, "Hello World");
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH C
START_TEST(sprintf_c_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %c", 'w');
  sprintf(str1, "Hello World %c", 'w');
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_c_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %c sdfdsaf", 'w');
  sprintf(str1, "Hello World %c sdfdsaf", 'w');
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH D
START_TEST(sprintf_d_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %.5d", -1234);
  sprintf(str1, "Hello World %.5d", -1234);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_d_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %.d sdfdsaf", 1);
  sprintf(str1, "Hello World %.d sdfdsaf", 1);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_d_3) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %.6d sdfdsaf", -12);
  sprintf(str1, "Hello World %.6d sdfdsaf", -12);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_d_4) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %.2d sdfdsaf", 0);
  sprintf(str1, "Hello World %.2d sdfdsaf", 0);
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH F
START_TEST(sprintf_f_1) {
  char str[50];
  char str1[50];
  double dd = 0.0055;
  s21_sprintf(str, "Hello Worldd %.3f", dd);
  sprintf(str1, "Hello World %.3f", dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %f sdfdsaf", 1.);
  sprintf(str1, "Hello World %f sdfdsaf", 1.);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_3) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %f sdfdsaf", -123.2302);
  sprintf(str1, "Hello World %f sdfdsaf", -123.2302);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_4) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "Hello World %13.8f sdfdsaf", -123.230223423423);
  sprintf(str1, "Hello World %13.8f sdfdsaf", -123.230223423423);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_5) {
  char str[10000];
  char str1[10000];
  double chislo = 14.1;
  chislo++;
  s21_sprintf(str, "Hello World %f sdfdsadf", chislo);
  sprintf(str1, "Hello World %f sdfdsadf", chislo);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_6) {
  char str[10000];
  char str1[10000];
  double chislo = 0.00324;
  s21_sprintf(str, "Hello World %f sdfdsadf", chislo);
  sprintf(str1, "Hello World %f sdfdsadf", chislo);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_7) {
  char str[50];
  char str1[50];
  double dd = 998.888888;
  s21_sprintf(str, "Hello World %.10f", dd);
  sprintf(str1, "Hello World %.10f", dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_8) {
  char str[10000];
  char str1[10000];
  double chislo = 123.0000001;
  s21_sprintf(str, "Hello World %.22f sdfd %f sadf", chislo, chislo);
  sprintf(str1, "Hello World %.22f sdfd %f sadf", chislo, chislo);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_f_9) {
  char str[500];
  char str1[500];
  double dd = 12345.1231;
  s21_sprintf(str, "Hello %f World %.f", dd, dd);
  sprintf(str1, "Hello %f World %.f", dd, dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH Xx
START_TEST(sprintf_x_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %x asdfasdf", 266);
  sprintf(str1, "asdfasdf %x asdfasdf", 266);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_x_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %12.12x asdfasdf", 266);
  sprintf(str1, "asdfasdf %12.12x asdfasdf", 266);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_X_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %X asdfasdf", 266);
  sprintf(str1, "asdfasdf %X asdfasdf", 266);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_X_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %14.14X asdfasdf", 266);
  sprintf(str1, "asdfasdf %14.14X asdfasdf", 266);
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH o
START_TEST(sprintf_o_1) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %o asdfasdf %o", 266, 33);
  sprintf(str1, "asdfasdf %o asdfasdf %o", 266, 33);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_o_2) {
  char str[50];
  char str1[50];
  s21_sprintf(str, "asdfasdf %o asdfasdf", 266);
  sprintf(str1, "asdfasdf %o asdfasdf", 266);
  ck_assert_str_eq(str, str1);
}
END_TEST

// WITH g,G
START_TEST(sprintf_g_1) {
  char str[50];
  char str1[50];
  double dd = 266.100;
  s21_sprintf(str, "asdfasdf %g asdfasdf %o", dd, 33);
  sprintf(str1, "asdfasdf %.6g asdfasdf %o", dd, 33);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_g_2) {
  char str[50];
  char str1[50];
  double dd = 10000000000.438954354534;
  double d = 9993212.9993;
  s21_sprintf(str, "asdfasdf %g asdfasdf%g", dd, d);
  sprintf(str1, "asdfasdf %g asdfasdf%g", dd, d);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_g_3) {
  char str[50];
  char str1[50];
  long double dd = 10000000000.438954354534;
  s21_sprintf(str, "asdfasdf %Lg asdfasdf", dd);
  sprintf(str1, "asdfasdf %Lg asdfasdf", dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_g_4) {
  char str[50];
  char str1[50];
  double dd = 266.12000;
  s21_sprintf(str, "asdfasdf %.7g asdfasdf %o", dd, 33);
  sprintf(str1, "asdfasdf %.7g asdfasdf %o", dd, 33);
  ck_assert_str_eq(str, str1);
}
END_TEST

// With E,e
START_TEST(sprintf_e_1) {
  char str[50];
  char str1[50];
  double dd = 1.5435e+300;
  s21_sprintf(str, "\n%.3e\n%.6e\n%e\n%.e\n", dd, dd, dd, dd);
  sprintf(str1, "\n%.3e\n%.6e\n%e\n%.e\n", dd, dd, dd, dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_e_2) {
  char str[50];
  char str1[50];
  double dd = -0.00000438546;
  double minus = -123534.2309489;
  s21_sprintf(str, "\npow minus: %.e \nchislo minus: %e", dd, minus);
  sprintf(str1, "\npow minus: %.e \nchislo minus: %e", dd, minus);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_e_3) {
  char str[50];
  char str1[50];
  long double dd = 12400000000.438954354534;
  s21_sprintf(str, "asdfasdf %Le asdfasdf", dd);
  sprintf(str1, "asdfasdf %Le asdfasdf", dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_e_4) {
  char str[50];
  char str1[50];
  double dd = 8.24;
  s21_sprintf(str, "asdfasdf %e asdfasdf %.2e", dd, dd);
  sprintf(str1, "asdfasdf %e asdfasdf %.2e", dd, dd);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(sprintf_e_5) {
  char str[50];
  char str1[50];
  long double dd = 10000000000.438954354534;
  double d = 10000000000.438954354534;
  s21_sprintf(str, "asdfasdf %Le asdfasdfd %e", dd, d);
  sprintf(str1, "asdfasdf %Le asdfasdf %e", dd, d);
  ck_assert_str_eq(str, str1);
}
END_TEST

Suite *test_sprintf(void) {
  Suite *s = suite_create("\033[45m-=S21_SPRINTF=-\033[0m");
  TCase *tc = tcase_create("sprintf_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_1);
  tcase_add_test(tc, sprintf_c_1);
  tcase_add_test(tc, sprintf_c_2);
  tcase_add_test(tc, sprintf_d_1);
  tcase_add_test(tc, sprintf_d_2);
  tcase_add_test(tc, sprintf_d_3);
  tcase_add_test(tc, sprintf_d_4);
  tcase_add_test(tc, sprintf_f_1);
  tcase_add_test(tc, sprintf_f_2);
  tcase_add_test(tc, sprintf_f_3);
  tcase_add_test(tc, sprintf_f_4);
  tcase_add_test(tc, sprintf_f_5);
  tcase_add_test(tc, sprintf_f_6);
  tcase_add_test(tc, sprintf_f_7);
  tcase_add_test(tc, sprintf_f_8);
  tcase_add_test(tc, sprintf_f_9);
  tcase_add_test(tc, sprintf_x_1);
  tcase_add_test(tc, sprintf_x_2);
  tcase_add_test(tc, sprintf_X_1);
  tcase_add_test(tc, sprintf_X_2);
  tcase_add_test(tc, sprintf_o_1);
  tcase_add_test(tc, sprintf_o_2);
  tcase_add_test(tc, sprintf_g_1);
  tcase_add_test(tc, sprintf_g_2);
  tcase_add_test(tc, sprintf_g_3);
  tcase_add_test(tc, sprintf_g_4);
  tcase_add_test(tc, sprintf_e_1);
  tcase_add_test(tc, sprintf_e_2);
  tcase_add_test(tc, sprintf_e_3);
  tcase_add_test(tc, sprintf_e_4);
  tcase_add_test(tc, sprintf_e_5);

  return s;
}