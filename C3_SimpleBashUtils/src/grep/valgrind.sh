#!/bin/bash

# Скрипт для запуска проверок с использованием Valgrind

# Сборка программы
make


# Что ищем - паттерн
readonly SEARCH_CONSTANT="clear"

# Где ищем - файл
readonly FILE_CONSTANT="Makefile"

# Файл с паттернами для поиска (флаг -f)
readonly PATTERNS_CONSTANT="patterns.txt"


# Функция для выполнения тестов
run_valgrind_test() {
    echo "Running valgrind with flags: $@"
    valgrind --leak-check=full ./s21_grep "$@"
}

# Запуск тестов с разными флагами
run_valgrind_test "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-e" "$SEARCH_CONSTANT" "-e" "all" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-i" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-v" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-c" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-l" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-n" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-h" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-s" "$SEARCH_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-f" "$PATTERNS_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-o" "$SEARCH_CONSTANT" "$FILE_CONSTANT"

# Очистка после выполнения тестов
make clean

