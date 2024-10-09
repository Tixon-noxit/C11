CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Werror -g
LDFLAGS = -lm

SRCDIR = .
BUILDDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.c) $(SRCDIR)/s21_grep.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

EXECUTABLE = $(BUILDDIR)/s21_grep

.PHONY: all

all: $(EXECUTABLE) clean style

rebuild: clean_rebuild all

clean_rebuild:
	rm -f s21_grep test/s21_grep_test

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o s21_grep

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests:
	./tests.sh

style:
	clang-format -i *.c *.h
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem *.c
	clang-format -n *.c *.h

clean:
	rm -f $(OBJECTS)


