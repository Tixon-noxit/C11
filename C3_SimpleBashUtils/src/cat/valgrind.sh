#!/bin/bash

# Скрипт для запуска проверок с использованием Valgrind

# Сборка программы
make

# Где ищем - файл
readonly FILE_CONSTANT="Makefile"

# Функция для выполнения тестов
run_valgrind_test() {
    echo "Running valgrind with flags: $@"
    valgrind --leak-check=full ./s21_cat "$@"
}

# Запуск тестов с разными флагами
run_valgrind_test "-b" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-b" "$FILE_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-e" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-e" "$FILE_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-n" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-n" "$FILE_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-s" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-s" "$FILE_CONSTANT" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-t" "$FILE_CONSTANT"
echo
echo
run_valgrind_test "-t" "$FILE_CONSTANT" "$FILE_CONSTANT"
echo
echo

# Очистка после выполнения тестов
make clean

