#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "s21_string.h"

void spec_s(const char* str, char* mini, int accuracy);
void spec_c(int symbol, char* buff);

char* begin_buf(char* buffer, char* mini, int width, spec* spec) {
  char* mini_current = NULL;
  mini_current = mini;

  s21_size_t count_width = width;
  if (count_width == 0 || (s21_strlen(mini) >= count_width)) {
    spec->plus++;
    spec->space++;

    if ((spec->specifier == 's' || spec->specifier == 'p') &&
        (spec->plus || spec->space)) {
      if (count_width != 0) count_width--;
      spec->plus = 0;   // обработка при плюсе
      spec->space = 0;  // обработка при пробеле
    }
  } else if ((spec->specifier == 's' || spec->specifier == 'p') &&
             (spec->plus || spec->space)) {
    spec->plus = 0;
    spec->space = 0;
  }
  //  краевой случай при отсутсвии ширины
  for (s21_size_t i = 0; i < s21_strlen(mini) || (int)i < width; i++) {
    if (count_width > s21_strlen(mini)) {
      if (spec->plus == 1) {
        spec->plus++;
        count_width--;
        continue;
      } else if (spec->space == 1) {
        spec->space++;
        count_width--;
        continue;
      }

      if (spec->zero && count_width > s21_strlen(mini))  // flag ZERO
        *buffer = '0';
      else
        *buffer = ' ';

      count_width--;
    } else {
      if (spec->plus == 2) {  // flag PLUS
        *buffer = '+';
        buffer++;
        spec->plus++;
      } else if (spec->space == 2) {  // flag SPACE
        *buffer = ' ';
        buffer++;
        spec->space++;
      }
      if (spec->hash == 1) {
        buffer = spec_hash(buffer, mini, &width,
                           spec);  // не работает без знака минус, но  если
                                   // возвращать функцию все работает, а тут нет
        spec->hash += 1;
      }
      *buffer = *mini_current;
      mini_current++;
    }
    buffer++;
  }
  return buffer;
}

char* end_buf(char* buffer, char* mini, int width, spec* spec) {
  char* mini_current = mini;
  int width_current = width;
  for (s21_size_t i = 0; i < s21_strlen(mini) || (int)i < width_current; i++) {
    if (i < s21_strlen(mini)) {
      if (spec->hash == 1) {
        buffer = spec_hash(buffer, mini, &width_current, spec);
        spec->hash += 1;
        width_current--;
      }
      *buffer = *mini_current;
      mini_current++;
    } else if (spec->zero)  // flag ZERO
      *buffer = '0';
    else
      *buffer = ' ';
    buffer++;
  }
  return buffer;
}

char* set_buf(char* buffer, char* mini, spec* spec) {
  int width = spec->width;
  if (!spec->minus) {
    buffer = begin_buf(buffer, mini, width, spec);
  } else {
    buffer = end_buf(buffer, mini, width, spec);
  }
  return buffer;
}

char* spec_hash(char* buffer, char* mini, int* width, spec* spec) {
  if (spec->specifier == 'o') {
    if (*width > 0 && !spec->minus) {
      buffer--;
    } else
      *width += 1;
    if (*mini != '0')
      *buffer = '0';
    else if (spec->minus && *mini == '0') {
      buffer--;
    }
    buffer++;
  } else if (spec->specifier == 'x') {
    if (*width > 1 && !spec->minus)
      buffer -= 2;
    else
      *width -= 2;
    *buffer = '0';
    buffer++;
    *buffer = 'x';
    buffer++;
  } else if (spec->specifier == 'X') {
    if (*width > 1 && !spec->minus)
      buffer -= 2;
    else
      *width -= 2;
    *buffer = '0';
    buffer++;
    *buffer = 'X';
    buffer++;
  } else if (spec->specifier == 'g') {
    spec->accuracy = 3;
  }
  // }
  if (spec->accuracy == 0) {
    spec->accuracy = 6;
  }
  return buffer;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* str_start = str;

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      spec spec = {0};
      while(*format == '+' || *format == '-' || *format == ' ' || *format == '#' || *format == '0') {
        if (*format == '+') {
          spec.plus = 1;
          format++;
        }
        if (*format == '-') {
          spec.minus = 1;
          format++;
        }
        if (*format == ' ') {
          spec.space = 1;
          format++;
        }
        if (*format == '#') {
          spec.hash = 1;
          format++;
        }
        if (*format == '0') {
          spec.zero = 1;
          format++;
        }
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
          spec.specifier = 'd';
          if (!spec.accuracy_defined) {
            spec.accuracy = 1;
          }
          long int int_arg;
          if (spec.length == 'l') {
            int_arg = va_arg(args, long int);
          } else if (spec.length == 'h') {
            int_arg = (short)va_arg(args, int);
          } else {
            int_arg = (int)va_arg(args, int);
          }

          char stringified_number[50] = {0};
          char* p = &stringified_number[0];
          spec_d(int_arg, stringified_number, spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'f': {
          spec.specifier = 'f';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }

          char stringified_number[10000] = {0};
          spec_f(double_arg, stringified_number, &spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 's': {
          spec.specifier = 's';
          char mini[100] = {0};
          char* string_arg = va_arg(args, char*);
          spec_s(string_arg, mini, spec.accuracy);
          str = set_buf(str, mini, &spec);

          format++;
          break;
        }
        case 'c': {
          spec.specifier = 'c';
          int char_arg = va_arg(args, int);
          char mini[1] = {0};
          spec_c(char_arg, mini);
          str = set_buf(str, mini, &spec);
          format++;
          break;
        }
        case '%': {
          char mini[1] = {0};
          mini[0] = '%';
          str = set_buf(str, mini, &spec);
          format++;
          break;
        }
        case 'X': {
          spec.specifier = 'X';
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'x': {
          spec.specifier = 'x';
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'o': {
          spec.specifier = 'o';
          long int int_arg = va_arg(args, long int);

          char stringified_number[100] = {0};

          spec_x(int_arg, stringified_number, spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'g': {
          spec.specifier = 'g';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }

          char stringified_number[1000] = {0};
          spec_g(double_arg, stringified_number, &spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
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
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          // result += result_count(stringified_number);
          format++;
          break;
        }
        case 'e': {
          spec.specifier = 'e';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }
          char stringified_number[100] = {0};
          spec_e(double_arg, stringified_number, &spec);
          // str = set_buf(str, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
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
  return s21_strlen(str_start);
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

void spec_d(long int number, char* stringified_number, spec spec) {
  int i = 0;
  int length = 0;
  int flag_minus = 0;

  if (number < 0) {
    number *= -1;
    stringified_number[i] = '-';
    i++;
    length++;
    flag_minus++;
  } else if (number == 0) {  //под вопросом
    length++;
    stringified_number[0] =
        (spec.accuracy == 0 && spec.specifier == 'd') ? '\0' : '0';
    i = 1;  // tut hzz
  }

  long int temp = number;
  while (temp != 0) {
    temp /= 10;
    length++;
  }

  // Accuracy
  for (; length < spec.accuracy + flag_minus; i++) {
    stringified_number[i] = '0';
    length++;
  }
  // Strnum
  stringified_number[length] = '\0';
  if (number != 0) {
    for (int str_end = length - 1; str_end >= i; str_end--) {
      stringified_number[str_end] = number % 10 + '0';
      number /= 10;
    }
  }
}

void spec_f(long double number, char* stringified_number, spec* spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 6;
  }
  long double int_part = 0;
  long double decimal_part = modfl(number, &int_part);
  decimal_part = round(decimal_part * pow(10, spec->accuracy));
  // long long int_part_int = (long long)llround(int_part);
  // printf("%Lf %Lf %lld\n", int_part, number, int_part_int);

  if (labs((long int)decimal_part) / (int)(pow(10, spec->accuracy)) % 10 ==
      1) {
    if (decimal_part >= 0) {
      int_part += 1;
    } else if (decimal_part < 0){
      int_part -= 1;
    }
    decimal_part = 0;
  }

  if (decimal_part < 0) {
    decimal_part *= -1;
  }

  char s[1000] = {0};

  spec_d((long int)decimal_part, s, *spec);

  int decimal_accuracy = spec->accuracy;
  spec->accuracy = 0;

  spec_d((long int)int_part, stringified_number, *spec);  // insert lower

  if (decimal_accuracy != 0) {
    s21_strcat(stringified_number, ".");
    // here
    s21_strcat(stringified_number, s);
  }
}

void spec_x(long int decimalValue, char hexString[], spec spec) {
  if (!spec.accuracy_defined) {
    spec.accuracy = 1;
  }
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

  if (number == 0) {
    hexString[0] = spec.accuracy == 0 ? '\0' : '0';
    index++; 
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

void spec_g(long double number, char* stringified_number, spec* spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 6;
  }
  int copy_accuracy = spec->accuracy;
  // char inim[10000] = {0};
  int len_int = 0;
  int len_dec = 0;
  long double integer_part = 0;
  long double decimal_part = modfl(number, &integer_part);
  long int decimal_part_int =
      (long int)(round(decimal_part * pow(10, spec->accuracy)));
  // decimal_part == 0.0000756589 when making int zeros is gone and result is 75
  if (integer_part < 0) {
    integer_part *= -1;
  } else if (integer_part == 0) {
    len_int++;
  }

  // Два цикла чтобы посчитать количество знаков в числах
  while (integer_part >= 1) {
    integer_part /= 10;
    len_int++;
  }

  while (decimal_part_int >= 1) {
    decimal_part_int /= 10;
    len_dec = spec->accuracy;
  }
  // if (len_dec < spec->accuracy) {
  //   len_dec
  // }

  spec->accuracy_defined = 1;

  if (len_int + len_dec > spec->accuracy || number < 0.0001) {
    spec->accuracy = spec->accuracy == 0 ? 0 : spec->accuracy - 1;
    spec_e(number, stringified_number, spec);
  } else {
    spec->accuracy -= len_int;
    spec_f(number, stringified_number, spec);
  }
}

void spec_e(long double number, char* stringified_number, spec* spec) {
  // Is negative
  char sign = '+';
  if (number < 0) {
    number *= -1;
    stringified_number[0] = '-';
    stringified_number++;
  }

  // Making float and checking if power minus or not
  int pow = 0;
  while (number >= 10 ||
         number <
             1) {  //уточнить условие // отрицательные степени чекнуть //1-9 ??
    if (number >= 10) {
      number /= 10;
    } else {
      number *= 10;
      sign = '-';
    }
    pow++;
  }

  char pow_string[4];
  pow_calc(pow, pow_string);

  char e = spec->specifier == 'E' ? 'E' : 'e';
  char notation[3] = {e, sign, '\0'};

  spec_f(number, stringified_number, spec);
  // printf("%s\n", stringified_number);
  s21_strcat(stringified_number, notation);
  s21_strcat(stringified_number, pow_string);
  // stringified_number[s21_strlen(stringified_number)] = '\0';
}

void pow_calc(int pow, char* pow_string) {
  int i = 2;
  // 0
  if (pow == 0) {
    pow_string[0] = '0';
    pow_string[1] = '0';
    pow_string[2] = '\0';
  } else if (pow < 10) {
    pow_string[0] = '0';
    pow_string[2] = '\0';
  } else if (pow >= 100) {
    i = 3;
    pow_string[3] = '\0';
  }
  // pow_string[ ]
  // 10-100
  while (i >= 0) {
    pow_string[i - 1] = pow % 10 + '0';
    pow /= 10;
    i--;
  }
}

s21_size_t add_width_and_flags(char* stringified_number, char* str, spec spec) {
  char s = spec.specifier;
  int xXo = (s == 'x' || s == 'X' || s == 'o') ? 1 : 0;
  int is_plus_added = (spec.plus && *stringified_number != '-') ? 1 : 0;
  int is_space_added = (spec.space && *stringified_number != '-' && !is_plus_added) ? 1 : 0;
  if (xXo) {
    is_plus_added = 0;
    is_space_added = 0;
  }
  s21_size_t shift = s21_strlen(stringified_number) + is_plus_added + is_space_added;
  //Flag 0
  if (spec.zero && (is_plus_added || is_space_added)) {
    *str++ = is_plus_added ? '+' : ' ';
    is_plus_added = 0;
    is_space_added = 0;
  } else if (spec.zero && *stringified_number == '-') {
    *str++ = *stringified_number++;
  }

  //Width and flag 0
  while (shift < spec.width && !spec.minus) {
    *str++ = spec.zero ? '0' : ' ';
    shift++;
  }

  //Flag plus
  if (is_plus_added) {
    *str++ = '+';
  }

  //Space
  if (is_space_added) {
    *str++ = ' ';
  }

  //Main algo
  while (*stringified_number != '\0') {
    *str++ = *stringified_number++;
  }

  //Flag minus
  while (shift < spec.width && spec.minus) {
    *str++ = ' ';
    shift++;
  }

  return shift;
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