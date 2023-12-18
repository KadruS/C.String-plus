#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  const char *start = str2;
  while (*str1 != '\0') {
    while (*str2 != '\0') {
      if (*str2 == *str1) {
        result = (char *)str2;
        return result;
      }
      str2++;
    }
    str2 = start;
    str1++;
  }
  return result;
}