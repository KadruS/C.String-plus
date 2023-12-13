#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;

  while (*str != '\0') {
    str++;
    length++;
  }

  return length;
}