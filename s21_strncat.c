#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *start = dest;
  s21_size_t counter = 0;

  while (*dest != '\0') dest++;
  while (*src != '\0' && counter++ != n) {
    *dest++ = *src++;
  }
  *dest = '\0';

  return start;
}