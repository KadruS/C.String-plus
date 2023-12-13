#include "test_me.h"

START_TEST(strpbrk_1) {
  const char str1[] = "Hello, world!";
  const char str2[] = "aeiou";
  ck_assert_pstr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

Suite *test_strpbrk(void) {
  Suite *s = suite_create("\033[45m-=S21_STRPBRK=-\033[0m");
  TCase *tc = tcase_create("strpbrk_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strpbrk_1);

  return s;
}