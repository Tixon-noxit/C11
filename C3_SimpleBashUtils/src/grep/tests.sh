#!/bin/bash
# chmod +x s21_grep - на всякий случай
# на linux ./tests.sh
# Путь к исполняемым файлам grep и s21_grep
GREP_CMD="grep"
S21_GREP_CMD="./s21_grep"

# Массив с флагами и их комбинациями для тестирования
FLAGS=("i" "v" "c" "l" "n" "h" "s" "o")
COMBO_FLAGS=("iv" "ic" "il" "in" "ih" "is" "io" "vc" "vl" "vn" "vh" "vs" "vo" "cl" "cn" "ch" "cs" "co" "ln" "lh" "ls" "lo" "nh" "ns" "no" "hs" "ho" "so")

# no !!!

# Функция для проведения теста с определенными флагами
run_test() {
    local flags="$1"
    local test_name="$2"
    
    # Файл с регулярным выражением
    regex_file="./test/pattern.txt"
    
    # Файл для поиска
    search_file="./test/test_1_grep.txt"
    
    # Оригинальный grep
    original_output="$("$GREP_CMD" -$flags -f "$regex_file" "$search_file")"
    
    # Мой s21_grep
    custom_output="$("$S21_GREP_CMD" -$flags -f "$regex_file" "$search_file")"
    
    # Запись результатов во временные файлы
    echo "$original_output" > "original_result.txt"
    echo "$custom_output" > "custom_result.txt"
    
    # Сравнение результатов с diff
    diff_output="$(diff "original_result.txt" "custom_result.txt")"
    
    if [ -z "$diff_output" ]; then
        echo "Test '$test_name' OK"
    else
        echo "Test '$test_name' FAIL"
        echo "Diff output:"
        echo "$diff_output"
    fi
    
    # Удаление временных файлов
    rm -f "original_result.txt" "custom_result.txt"
}

# Функция для проведения теста с определенными флагами
run_test_2_file() {
    local flags="$1"
    local test_name="$2"
    
    # Файл с регулярным выражением
    regex_file="./test/pattern.txt"
    
    # Файл для поиска
    search_file="./test/test_1_grep.txt"
    
    # Оригинальный grep
    original_output="$("$GREP_CMD" -$flags -f "$regex_file" "$search_file" "$search_file")"
    
    # Мой s21_grep
    custom_output="$("$S21_GREP_CMD" -$flags -f "$regex_file" "$search_file" "$search_file")"
    
    # Запись результатов во временные файлы
    echo "$original_output" > "original_result.txt"
    echo "$custom_output" > "custom_result.txt"
    
    # Сравнение результатов с diff
    diff_output="$(diff "original_result.txt" "custom_result.txt")"
    
    if [ -z "$diff_output" ]; then
        echo "Test '$test_name' OK"
    else
        echo "Test '$test_name' FAIL"
        echo "Diff output:"
        echo "$diff_output"
    fi
    
    # Удаление временных файлов
    rm -f "original_result.txt" "custom_result.txt"
}

# Функция для проведения теста с определенными флагами
run_test_combo() {
    local flags="$1"
    local test_name="$2"
    
    # Файл с регулярным выражением
    regex_file="./test/pattern.txt"
    
    # Файл для поиска
    search_file="./test/test_1_grep.txt"
    
    # Оригинальный grep
    original_output="$("$GREP_CMD" -$flags -f "$regex_file" "$search_file")"
    
    # Мой s21_grep
    custom_output="$("$S21_GREP_CMD" -$flags -f "$regex_file" "$search_file")"
    
    # Запись результатов во временные файлы
    echo "$original_output" > "original_result.txt"
    echo "$custom_output" > "custom_result.txt"
    
    # Сравнение результатов с diff
    diff_output="$(diff "original_result.txt" "custom_result.txt")"
    
    if [ -z "$diff_output" ]; then
        echo "Test '$test_name' OK"
    else
        echo "Test '$test_name' FAIL"
        echo "Diff output:"
        echo "$diff_output"
    fi
    
    # Удаление временных файлов
    rm -f "original_result.txt" "custom_result.txt"
}

# Функция для проведения теста с определенными флагами
run_test_combo_2_files() {
    local flags="$1"
    local test_name="$2"
    
    # Файл с регулярным выражением
    regex_file="./test/pattern.txt"
    
    # Файл для поиска
    search_file="./test/test_1_grep.txt"
    
    # Оригинальный grep
    original_output="$("$GREP_CMD" -$flags -f "$regex_file" "$search_file" "$search_file")"
    
    # Мой s21_grep
    custom_output="$("$S21_GREP_CMD" -$flags -f "$regex_file" "$search_file" "$search_file")"
    
    # Запись результатов во временные файлы
    echo "$original_output" > "original_result.txt"
    echo "$custom_output" > "custom_result.txt"
    
    # Сравнение результатов с diff
    diff_output="$(diff "original_result.txt" "custom_result.txt")"
    
    if [ -z "$diff_output" ]; then
        echo "Test '$test_name' OK"
    else
        echo "Test '$test_name' FAIL"
        echo "Diff output:"
        echo "$diff_output"
    fi
    
    # Удаление временных файлов
    rm -f "original_result.txt" "custom_result.txt"
}

# Запуск тестов с 1 флагом
for flag_combination in "${FLAGS[@]}"; do
    run_test "$flag_combination" "Flags: -$flag_combination"
done
echo

# Запуск тестов с 1 флагом и 2 файлами
for flag_combination in "${FLAGS[@]}"; do
    run_test_2_file "$flag_combination" "Flags: -$flag_combination 2 file"
done

echo

# # Запуск тестов для каждой комбинации флагов
# for flag_combination in "${COMBO_FLAGS[@]}"; do
#     run_test "$flag_combination" "Combo flags: -$flag_combination"
# done

# echo

# # Запуск тестов для каждой комбинации флагов и 2 файлами
# for flag_combination in "${COMBO_FLAGS[@]}"; do
#     run_test_combo_2_files "$flag_combination" "Combo flags: -$flag_combination"
# done






