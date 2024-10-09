CC=gcc
CFLAGS=-Wall -Wextra -std=c11 --coverage -fprofile-arcs -ftest-coverage
OUTPUT_DIR = .
WORKING_FILES := $(filter-out s21_decimal_test.c, *.c)
LIBNAME = s21_decimal
UNAME := $(shell uname)
SRCDIR = ..
TESTDIR = .
GCOVDIR = gcov_report
LIBRARY = $(SRCDIR)/$(LIBNAME).a
TESTS = $(TESTDIR)/$(LIBNAME).a



all: s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar rcs $(LIBNAME).a *.o

s21_decimal.o: s21_decimal.h
	find .. -type f -name '*.c' ! -name "s21_decimal_test.c" -exec $(CC) -c -g2 -Wall -Wextra -Werror {} \;

clean:
	find ./../ -type f -name '*.gch'  			-delete
	find ./../ -type f -name '*.o'    			-delete
	find ./../ -type f -name '*.a'      			-delete
	find ./../ -type f -name '*.gcda'      			-delete
	find ./../ -type f -name '*.gcov'      			-delete
	find ./../ -type f -name '*.gcno'      			-delete
	find ./../ -name '*.dSYM'      				-exec rm -rv {} +
	find ./../ -type f -name '*.out'  			-delete
	find ./../ -type f -name 'vgcore*'  			-delete
	rm -rf $(GCOVDIR)
	rm -rf s21_decimal_test


style:
	find ../ -iname '*.c' | xargs clang-format -i
	find ../ -iname '*.h' | xargs clang-format -i
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem ../

retest: retest_no_start
	./s21_decimal_test

#CLion debug only
retest_no_start: clean all test

test:
ifeq ($(UNAME),  Darwin)
	find .. -type f -name '*.c' -exec $(CC) --coverage -fprofile-arcs -ftest-coverage -c -g2 -Wall -Wextra -Werror  {} \;
	ar rcs $(LIBNAME).a *.o
	$(CC) $(CFLAGS) -o ./s21_decimal_test  tests/s21_decimal_test.c s21_decimal.a -lcheck -lpthread
else
	find .. -type f -name '*.c' ! -name "s21_decimal_test.c" -exec $(CC) --coverage -fprofile-arcs -ftest-coverage -c -g2 -Wall -Wextra -Werror {} \;
	ar rcs $(LIBNAME).a *.o
	$(CC) $(CCFLAGS) -o $(OUTPUT_DIR)/s21_decimal_test  tests/s21_decimal_test.c -l:$(LIBNAME).a -lcheck -lm -lpthread -lsubunit -lgcov -L.
endif


gcov_report: retest
	mkdir -p $(GCOVDIR)
	mv *.gcda $(GCOVDIR) #2>/dev/null; true
	mv *.gcno $(GCOVDIR) #2>/dev/null; true
	lcov --capture --directory $(GCOVDIR) --output-file $(GCOVDIR)/coverage.info
	genhtml $(GCOVDIR)/coverage.info --output-directory $(GCOVDIR)/html


format_project:
	find ../ -iname '*.c' | xargs clang-format -i
	find ../ -iname '*.h' | xargs clang-format -i
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem ../



.PHONY: all clean test gcov_report

