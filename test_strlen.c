#include "test_me.h"

START_TEST(strlen_1) {
  const char *str = "privetMir";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  const char *str = "privet\0ir";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  const char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  const char str[30] = {'a', 'b', 'o', 'b', 'a'};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  const char *str = " ";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_6) {
  const char *str = "\n";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_7) {
  const char *str = "\0";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *test_strlen(void) {
  Suite *s = suite_create("\033[45m-=S21_STRLEN=-\033[0m");
  TCase *tc = tcase_create("strlen_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_5);
  tcase_add_test(tc, strlen_6);
  tcase_add_test(tc, strlen_7);

  return s;
}