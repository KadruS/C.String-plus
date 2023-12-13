#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "s21_string.h"

void spec_s(const char* str, char* mini, int accuracy);
void spec_c(int symbol, char* buff);

char* set_buf_and_width(char* buffer, char* mini_start, int width, spec* spec) {
  char* mini_current = mini_start;
  s21_size_t count_width = width;

  if (!spec->minus) {
    for (s21_size_t i = 0; i < s21_strlen(mini_start) || (int)i < width;
         i++) {  // s21_strlen
      if (count_width > s21_strlen(mini_start)) {
        if (spec->plus == 1) {
          spec->plus++;
          count_width--;
          continue;
        }
        if (spec->zero)  // flag ZERO
          *buffer = '0';
        else
          *buffer = ' ';
        count_width--;
      } else {
        if (spec->plus == 2) {  // flag PLUS
          *buffer = '+';
          buffer++;
          spec->plus++;
        }
        *buffer = *mini_current;
        mini_current++;
      }
      buffer++;
    }
  } else {
    for (s21_size_t i = 0; i < s21_strlen(mini_start) || (int)i < width; i++) {
      if (i < s21_strlen(mini_start)) {
        *buffer = *mini_current;
        mini_current++;
      } else if (spec->zero)  // flag ZERO
        *buffer = '0';
      else
        *buffer = ' ';
      buffer++;
    }
  }
  return buffer;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      spec spec = {0};

      if (*format == '-') {
        spec.minus = 1;
        format++;
      } else if (*format == '+') {
        spec.plus = 1;
        format++;
      } else if (*format == ' ') {
        spec.space = 1;
        format++;
      }

      while (*format >= '0' && *format <= '9') {
        spec.width = spec.width * 10 + (*format - '0');
        format++;
      }

      if (*format == '.') {
        format++;
        // if (!(*format >= '0' && *format <= '9')) checkout
        while (*format >= '0' && *format <= '9') {
          spec.accuracy = spec.accuracy * 10 + (*format - '0');
          format++;
        }
        spec.accuracy_defined = 1;
      }

      if (*format == 'h') {
        format++;
        spec.length = 'h';
      }

      if (*format == 'l') {
        format++;
        spec.length = 'l';
      }

      if (*format == 'L') {
        format++;
        spec.length = 'L';
      }

      // accuracy default
      switch (*format) {
        case 'u':
        case 'd': {
          // default accuracy 0 или 1 ??
          if (!spec.accuracy_defined) {
            spec.accuracy = 1;
          }
          long int int_arg;
          if (spec.length == 'l') {
            int_arg = va_arg(args, long int);
          } else if (spec.length == 'h') {
            int_arg = (short) va_arg(args, int);
          } else {
            int_arg = (int) va_arg(args, int);
          }

          char stringified_number[50] = {0};  //={0}
          spec_d(int_arg, stringified_number, spec);

          str = set_buf_and_width(str, stringified_number, spec.width, &spec);

          format++;
          break;
        }
        case 'f': {
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }

          char stringified_number[10000] = {0};
          spec_f(double_arg, stringified_number, &spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);

          format++;
          break;
        }
        case 's': {
          char mini[100] = {0};
          char* string_arg = va_arg(args, char*);
          spec_s(string_arg, mini, spec.accuracy);
          str = set_buf_and_width(str, mini, spec.width, &spec);

          format++;
          break;
        }
        case 'c': {
          int char_arg = va_arg(args, int);
          char mini[1] = {0};
          spec_c(char_arg, mini);
          str = set_buf_and_width(str, mini, spec.width, &spec);
          format++;
          break;
        }
        case '%': {
          char mini[1] = {0};
          mini[0] = '%';
          str = set_buf_and_width(str, mini, spec.width, &spec);
          format++;
          break;
        }
        case 'X': {
          spec.specifier = 'X';
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);

          format++;
          break;
        }
        case 'x': {
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);

          format++;
          break;
        }
        case 'o': {
          spec.specifier = 'o';
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);

          format++;
          break;
        }
        case 'g': {
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }

          char stringified_number[1000] = {0};
          spec_g(double_arg, stringified_number, &spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);
          // result += result_count(stringified_number);
          format++;
          break;
        }
        case 'E': {  // dobavil
          spec.specifier = 'E';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }
          char stringified_number[100] = {0};
          spec_e(double_arg, stringified_number, &spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);
          // result += result_count(stringified_number);
          format++;
          break;
        }
        case 'e': {
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }
          char stringified_number[100] = {0};
          spec_e(double_arg, stringified_number, &spec);
          str = set_buf_and_width(str, stringified_number, spec.width, &spec);
          // result += result_count(stringified_number);
          format++;
          break;
        }
      }
    } else {
      *str = *format;
      str++;
      format++;
    }
  }
  *str = '\0';
  va_end(args);
  return 0;
}

void spec_c(int symbol, char* buff) {
  *buff = symbol;
  buff++;
}

void spec_s(const char* str, char* mini, int accuracy) {
  int i = 0;
  if (accuracy > 0) {
    while (str[i] != '\0' && 0 < accuracy) {
      *mini = str[i];
      mini++;
      i++;
      accuracy--;
    }
  }
}

void spec_d(long int number, char* stringified_number,
            spec spec) {
  int i = 0;
  int length = 0;

  if (number < 0) {
    number *= -1;
    stringified_number[i] = '-';
    i++;
    length++;
  }

  long int temp = number;
  while (temp != 0) {
    temp /= 10;
    length++;
  }

  // Accuracy
  for (int flag_minus = i; length < spec.accuracy + flag_minus; i++) {
    stringified_number[i] = '0';
    length++;
  }
  // Strnum
  stringified_number[length] = '\0';
  for (int str_end = length - 1; str_end >= i; str_end--) {
    stringified_number[str_end] = number % 10 + '0';
    number /= 10;
  }
}

void spec_f(long double number, char* stringified_number, spec* spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 6;
  }
  long double int_part = 0;
  long double decimal_part = modfl(number, &int_part);
  decimal_part = round(decimal_part * pow(10, spec->accuracy));

  if (decimal_part < 0) {
    decimal_part *= -1;
  }

  if (decimal_part == 1 && spec->accuracy == 0) {
    if (int_part >= 0) {
      int_part += 1;
    } else {
      int_part -= 1;
    }

  }

  char s[1000] = {0};

  spec_d((long int)decimal_part, s, *spec);

  int decimal_accuracy = spec->accuracy;
  spec->accuracy = 0;

  spec_d((long int)int_part, stringified_number, *spec);

  if (decimal_accuracy != 0) {
    s21_strcat(stringified_number, ".");
    s21_strcat(stringified_number, s);
  }
}

void spec_x(long int decimalValue, char hexString[], spec spec) {
  long int number;
  if (spec.length == 'l') {
    number = decimalValue;
  } else if (spec.length == 'h') {
    number = (short)decimalValue;
  } else {
    number = (int)decimalValue;
  }
  int remainder;
  int index = 0;

  char letter = 'a';
  int hex_or_oct = 16;
  if (spec.specifier == 'X') {
    letter = 'A';
  }
  if (spec.specifier == 'o') {
    hex_or_oct = 8;
  }

  while (number != 0) {
    remainder = number % hex_or_oct;

    if (spec.specifier == 'o') {
      hexString[index] = remainder + '0';
    } else {
      if (remainder < 10) {
        hexString[index] = remainder + '0';
      } else {
        hexString[index] = remainder - 10 + letter;
      }
    }

    number = number / hex_or_oct;
    index++;
  }

  // Accuracy
  for (; index < spec.accuracy; index++) {
    hexString[index] = '0';
  }

  hexString[index] = '\0';

  int i, j;
  char temp;
  for (i = 0, j = index - 1; i < j; i++, j--) {
    temp = hexString[i];
    hexString[i] = hexString[j];
    hexString[j] = temp;
  }
}

void spec_g(long double number, char* mini, spec* spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 6;
  }
  // char inim[10000] = {0};
  int len_int = 0;
  int len_dec = 0;
  long double integer_part = 0;
  long double decimal_part = modfl(number, &integer_part);
  long int decimal_part_int = (long int)(round(decimal_part * pow(10, spec->accuracy)));

  // Два цикла чтобы посчитать количество знаков в числах
  while (integer_part >= 1) {
    integer_part /= 10;
    len_int++;
  }
  int flag = 0;
  while (decimal_part_int > 1) {
    if (decimal_part_int % 10 == 0 && !flag) { //добавил эту штуку |
      spec->accuracy -= 1;
    }
    if (decimal_part_int % 10 != 0) {
      len_dec++;
      flag = 1;
    }
    if (flag && decimal_part_int % 10 == 0) {
      len_dec++;
    }
    decimal_part_int /= 10;
  }
  // printf("%ld %d\n", decimal_part_int, spec->accuracy);


  // Переделываем точность с учетом значащих знаков
  // spec->accuracy -= len_int;                  ВМЕСТО ЭТОЙ ШТУКИ |
  if (spec->accuracy < 0) {
    spec->accuracy = 0;
  }
  spec->accuracy_defined = 1;

  if (len_int + len_dec > 6) {
    spec_e(number, mini, spec);
  } else {
    spec_f(number, mini, spec);
  }
}

void spec_e(long double number, char* mini, spec *spec) {
  int accuracy = spec->accuracy;
  int accuracy_defined = spec->accuracy_defined;
  int zero_accuracy = accuracy;
  if (!accuracy_defined) {
    accuracy = 6;
  }

  int exponent = 0;

  if (number != 0.0) {
    while (fabsl(number) < 1.0) {
      number *= 10.0;
      exponent--;
    }
    while (fabsl(number) >= 10.0) {
      number /= 10.0;
      exponent++;
    }
    long double integer_part = 0;
    long double decimal_part = modfl(number, &integer_part);
    if (decimal_part < 0) {
      decimal_part *= -1;
    }
    spec_d((long int)integer_part, mini, *spec);
    if (zero_accuracy != 0) {
      mini += s21_strlen(mini);
      *mini = '.';
      mini += 1;

      long int decimal_part_int =
          (long int)(decimal_part * pow(10, accuracy + 1));
      spec_d(decimal_part_int, mini, *spec);
    } else {
      int count = 0;
      int len = s21_strlen(mini);
      char last_char = mini[len - 1];
      if (last_char >= '5') {
        for (int i = len - 1 - count; i >= 0 && mini[i] == '9'; i--) {
          mini[i] = '0';
          count++;
        }
        mini[len - count - 1] += 1;
      }
      mini[len] = '\0';
      mini += s21_strlen(mini);
      if (spec->specifier == 'E') {
        *mini = 'E';
      } else
        *mini = 'e';
      mini += 1;
      if (exponent >= 0) {
        *mini = '+';
        mini += 1;
      }
      spec_d(exponent, mini,  *spec);
    }
  }

}

void test_spec_s() {
  char str[500] = {
      0};  // НАДО БЫЛО ЗАНУЛИТb! Было куча мусора в буффере см скрин до и
           // после. Цикл шёл(или принтфы отрабатывали) до РАНДОМНОГО НУЛЬ
           // терминатора!! иначе всё было свдинуто

  char* pow = "qwrt";
  s21_sprintf(str, ">%10.3s", pow);  //  ширина ломается при фиксе участии
  // точности, строка меньше плюс нет обработки когда просто точка
  printf("s21_: %s|\n", str);

  sprintf(str, ">%10.3s", pow);
  printf("orig: %s|", str);
}

  // if (!spec->accuracy_defined) {
  //   spec->accuracy = 6;
  // }
  // spec->length = 'l';
  // double int_part = 0;
  // double decimal_part = modf(number, &int_part);
  // decimal_part = round(decimal_part * pow(10, spec->accuracy));

  // if (decimal_part < 0) {
  //   decimal_part *= -1;
  // }

  // if (decimal_part == 1 && spec->accuracy == 0) {
  //   int_part += 1;
  // }

  // char s[1000] = {0};

  // spec_d((long int)decimal_part, s, *spec);

  // int decimal_accuracy = spec->accuracy;
  // spec->accuracy = 0;

  // spec_d((long int)int_part, stringified_number, *spec);

  // if (decimal_accuracy != 0) {
  //   s21_strcat(stringified_number, ".");
  //   s21_strcat(stringified_number, s);
  // }