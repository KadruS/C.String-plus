#include "test_me.h"

START_TEST(strstr_1) {
  char *str = "Hello world!";
  char *substr = "world";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

Suite *test_strstr(void) {
  Suite *s = suite_create("\033[45m-=S21_STRSTR=-\033[0m");
  TCase *tc = tcase_create("strstr_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strstr_1);

  return s;
}
