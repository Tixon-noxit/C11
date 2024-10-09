#!/bin/bash
# chmod +x s21_cat - на всякий случай

# Путь к исполняемым файлам cat и s21_cat
CAT_CMD="cat"
S21_CAT_CMD="./s21_cat"

# Массив с флагами и их комбинациями для тестирования
FLAGS=("b" "e" "n" "s" "t")

# Функция для проведения теста с определенными флагами
run_test() {
    local flags="$1"
    local test_name="$2"
    
    
    # Файл для поиска
    open_file="./test/testfile.txt"
    
    # Оригинальный grep
    original_output="$("$CAT_CMD" -$flags "$open_file")"
    
    # Мой s21_grep
    custom_output="$("$S21_CAT_CMD" -$flags "$open_file")"
    
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
run_test_two_files() {
    local flags="$1"
    local test_name="$2"
    
    
    # Файл для поиска
    open_file="./test/testfile.txt"
    
    # Оригинальный cat
    original_output="$("$CAT_CMD" -$flags "$open_file" "$open_file")"
    
    # Мой s21_cat
    custom_output="$("$S21_CAT_CMD" -$flags "$open_file" "$open_file")"
    
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
run_test_tree_files() {
    local flags="$1"
    local test_name="$2"
    
    
    # Файл для поиска
    open_file="./test/testfile.txt"
    
    # Оригинальный cat
    original_output="$("$CAT_CMD" -$flags "$open_file" "$open_file" "$open_file")"
    
    # Мой s21_cat
    custom_output="$("$S21_CAT_CMD" -$flags "$open_file" "$open_file" "$open_file")"
    
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


# Запуск тестов для каждой комбинации флагов
for flag_combination in "${FLAGS[@]}"; do
    run_test "$flag_combination" "Flag: -$flag_combination"
done
echo
# Запуск тестов для каждого флага с 2 файлами
for flag_combination in "${FLAGS[@]}"; do
    run_test_two_files "$flag_combination" "Flag: -$flag_combination 2 file"
done
echo
# Запуск тестов для каждого флага с 3 файлами
for flag_combination in "${FLAGS[@]}"; do
    run_test_tree_files "$flag_combination" "Flag: -$flag_combination 3 file"
done


