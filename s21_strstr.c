#include "s21_string.h"

char *s21_strstr(const char *heystack, const char *needle) {
  int i = 0;
  int j = 0;
  int result = 0;
  if (heystack == needle || *needle == '\0') return 0;
  while (needle[i] != '\0') {
    if (heystack[j] == '\0') {
      result = -1;
      break;
    }
    if (heystack[j + i] == needle[i]) {
      i++;
      result = j;
    } else {
      j++;
      i = 0;
    }
  }
  char *copy = (char *)heystack;
  char *res = &copy[result];
  return res;
}