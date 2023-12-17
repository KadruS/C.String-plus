#include "test_me.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {test_strrchr(), test_strstr(), test_strpbrk(),
                              // test_memchr(),
                              // test_strncpy(),
                              // test_memcpy(),
                              // test_memset(),
                              // test_strcspn(),
                              test_strlen(),
                              // test_strncmp(),
                              // test_memcmp(),
                              // test_strtok(),
                              test_strncat(),
                              // test_strerror(),
                              // test_to_lower(),
                              // test_to_upper(),
                              // test_trim(),
                              // test_insert(),
                              // test_sprintf(),
                              // test_sprintf_d(),
                              // test_sprintf_f(),
                              test_sprintf_e(),
                               NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}