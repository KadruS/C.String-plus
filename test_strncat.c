#include "test_me.h"

START_TEST(strncat_1) {
  char str[20] = "Hello";
  char *substr = "world!";
  char str2[20] = "Hello";
  char *substr2 = "world!";
  ck_assert_str_eq(s21_strncat(str, substr, 3), strncat(str2, substr2, 3));
}
END_TEST

Suite *test_strncat(void) {
  Suite *s = suite_create("\033[45m-=S21_STRNCAT=-\033[0m");
  TCase *tc = tcase_create("strncat_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strncat_1);

  return s;
}
