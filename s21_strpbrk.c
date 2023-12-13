#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  const char *start = str1;
  while (*str2 != '\0') {
    while (*str1 != '\0') {
      if (*str1 == *str2) {
        result = (char *)str1;
        return result;
      }
      str1++;
    }
    str1 = start;
    str2++;
  }
  return result;
}