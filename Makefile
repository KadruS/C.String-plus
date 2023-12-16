TARGETS=*.c
CFLAGS=-std=c11 #-Wall -Werror -Wextra 
TESTS=test*.c
FLAG_TEST=-lcheck
FUNCTIONS=s21_strstr.c s21_strncat.c s21_strcat.c s21_strrchr.c s21_strpbrk.c s21_strlen.c s21_sprintf.c 
# SRCS=$(wildcard s21_math.c)
OBJS=$(SRCS:.c=.o)
ifeq ($(shell uname), Linux)
	FLAG_TEST +=-lsubunit -lm
endif

all: test

test: clean $(FUNCTIONS)
	gcc --coverage $(CFLAGS) $(TESTS) $(FUNCTIONS) $(FLAG_TEST) -o test -g
	./test


clean:
	-rm -rf *.o *.gcno *.gcda *.info  test s21_math.a gcov_report report greport a.out *.txt *.dSYM

style:
	clang-format -n --style=google *.c *.h