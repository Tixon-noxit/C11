# C11

Проекты на языке C11


## 1. [Simple Bash Utilse](https://github.com/Tixon-noxit/C11/tree/main/C3_SimpleBashUtils)
### Описание
Разработка утилит командной строки на языке C с использованием стандартов POSIX и Google Style. Проект реализует утилиты cat и grep в рамках Simple Bash Utils, предоставляя функциональность, аналогичную стандартным UNIX-утилитам, с поддержкой различных флагов и режимов работы.

#### Ключевые особенности
  - Архитектура:
    - Реализация двух утилит (s21_cat и s21_grep), каждая из которых находится в отдельных директориях (src/cat/ и src/grep/), с разделением на исходные файлы, заголовочные файлы и файлы сборки.
  - Поддержка нескольких флагов, обеспечивающих гибкость и возможность расширенной фильтрации данных для grep и cat.
  
#### Функциональность
Утилита s21_cat:
  - Полная поддержка флагов, включая все GNU-версии, что позволяет гибко работать с файлами и их содержимым.
    
#### Утилита s21_grep:
  - Поддержка базовых флагов -e, -i, -v, -c, -l, -n для расширенного поиска в файлах.
  - Использование библиотек pcre или regex для обработки регулярных выражений.
  - Реализация бонусных флагов -h, -s, -f, -o для расширенной фильтрации данных (бонусная часть).
  - Поддержка комбинаций флагов, таких как -iv и -in, что позволяет гибко настраивать поиск (бонусная часть).
#### Подготовка и тестирование
  - Полное покрытие кода тестами, проверяющими все возможные флаги и их комбинации, с использованием фреймворка GTest для обеспечения стабильности и корректности работы.
  - Написание Makefile для сборки отдельных утилит (s21_cat и s21_grep), создания статических библиотек и запуска тестов, включая цели all, clean, test.
    
#### Инструменты и технологии
  - C, POSIX
  - GTest — для тестирования корректности и покрытия кода.
  - Google Style Guide — соблюдение стандартов кодирования.

### Результаты и достижения
Данный проект реализует основные функции утилит `cat` и `grep`, часто используемых в UNIX-подобных системах, предоставляя аналоги этих утилит с поддержкой разнообразных флагов и совместимостью с различными требованиями пользователей. В процессе разработки ты освоил работу с `POSIX` и регулярными выражениями, создание Makefile, написание тестов с `GTest` и соблюдение стандартов Google Style, что укрепило навыки разработки CLI-утилит и работы с текстовыми данными.

***

## 2. [s21_string+](https://github.com/Tixon-noxit/C11/tree/main/C2_s21_stringplus)
### Описание

Разработка библиотеки для работы со строками на языке C с использованием стандарта C11. Библиотека реализует основные функции стандартной библиотеки string.h и дополнительные функции форматирования, предоставляя аналоги этих функций с поддержкой гибкого форматирования и пользовательских спецификаций.

#### Ключевые особенности

##### Архитектура
  - Реализация библиотеки s21_string, включающей функции для работы с строками, такие как копирование, сравнение, вычисление длины строки и другие базовые функции string.h.
  - Поддержка собственных массивов ошибок для платформ, без использования системных массивов ошибок.
  - Создание статической библиотеки s21_string.a с заголовочным файлом s21_string.h.
    
#### Функциональность
  - Реализация функций библиотеки string.h, включая основные операции со строками.
  - Частичная реализация функции sprintf, поддерживающая базовые спецификаторы (c, d, f, s, u, %), флаги (-, +, пробел), ширину, точность и длину.
  - Реализация расширенной функциональности sprintf с дополнительными модификаторами форматирования, а также функции sscanf и дополнительных функций обработки строк (бонусные задания).
    
#### Тестирование
  - Полное покрытие функций библиотеки модульными тестами с использованием библиотеки Check.
  - Сравнение результатов тестов с результатами стандартной библиотеки string.h для проверки корректности.
  - Обеспечение покрытия кода на уровне не менее 80% с помощью инструмента gcov.
    
#### Инструменты:
  - Написание Makefile для сборки библиотеки и тестов с целями all, clean, test, s21_string.a, gcov_report.
  - Генерация отчета покрытия кода в формате HTML при помощи цели gcov_report.
    
#### Технологии:
  - C11
  - Check
  - Google Style Guide
  - POSIX.1-2017
    
### Результаты и достижения 
Данный проект предоставляет реализацию функций библиотеки string.h и частичную поддержку форматирования sprintf, предлагая аналоги функций стандартной библиотеки и позволяя гибкую работу со строками. В процессе разработки я освоил работу с C11 и POSIX, написание тестов с Check, создание статической библиотеки и тестирование покрытия кода с gcov, что повысило мои навыки работы с языком C и разработкой высококачественных библиотек.

***

## 3. [s21_decimal](https://github.com/Tixon-noxit/C11/tree/main/C5_s21_decimal)
### Описание

Разработка библиотеки для работы с десятичными числами (decimal.h) на языке C, поддерживающей операции с числами большого диапазона и предоставляющей статическую библиотеку для работы с десятичными значениями. Библиотека реализует функции для манипуляции с десятичными числами с использованием битовых операций.

#### Ключевые особенности

#### Архитектура
  - Реализация статической библиотеки s21_decimal с заголовочным файлом s21_decimal.h, обеспечивающей работу с десятичными числами в бинарном представлении.
  - Хранение десятичных значений в виде массивов битов для оптимальной производительности.
  - Запрещено использование типа __int128 для поддержки совместимости с платформами.

#### Функциональность
  - Реализация функций для работы с десятичными числами в диапазоне от -79,228,162,514,264,337,593,543,950,335 до +79,228,162,514,264,337,593,543,950,335.
  - Поддержка работы с битовыми представлениями чисел, соблюдая расположение разрядов числа в массиве битов.
  - Возможность сохранения или удаления незначащих нулей, за исключением функции s21_truncate.

#### Тестирование
  - Полное покрытие функций библиотеки модульными тестами с использованием библиотеки Check.
  - Проверка корректности всех функций с достижением покрытия кода на уровне не менее 80% с помощью инструмента gcov.

#### Инструменты
  - Написание Makefile для сборки библиотеки и тестов с целями all, clean, test, s21_decimal.a, gcov_report.
  - Генерация отчета покрытия кода в формате HTML с помощью цели gcov_report.

#### Технологии
  - C11
  - Check
  - Google Style Guide
  - POSIX.1-2017

### Результаты и достижения 
Данный проект реализует библиотеку для работы с десятичными числами, предоставляя аналог функций для операций с числами в большом диапазоне значений с использованием битовых операций. В процессе разработки я освоил битовые операции, разработку модульных тестов с Check и анализ покрытия кода с gcov, что укрепило мои навыки разработки высокопроизводительных библиотек и работы с числовыми данными в C.

***

## 4. [s21_matrix](https://github.com/Tixon-noxit/C11/tree/main/C6_s21_matrix)
### Описание

Разработка библиотеки для выполнения базовых операций с матрицами на языке C, предоставляющей возможность работы с матрицами в различных математических задачах. Библиотека реализована в виде статической библиотеки и предоставляет функции для создания, удаления, сравнения матриц, выполнения арифметических операций, а также операций транспонирования и нахождения обратной матрицы.

#### Ключевые особенности

#### Архитектура
  - Реализация статической библиотеки s21_matrix.a с заголовочным файлом s21_matrix.h, поддерживающей основные операции с матрицами, включая сложение, вычитание, умножение, транспонирование и нахождение обратной матрицы.
  - Использование структурного программирования для обеспечения удобочитаемости и модульности кода.

#### Функциональность
  - Реализованы основные операции, такие как:
      - create_matrix — создание матрицы;
      - remove_matrix — очистка и уничтожение матрицы;
      - eq_matrix — сравнение матриц;
      - sum_matrix и sub_matrix — сложение и вычитание матриц;
      - mult_matrix — умножение матриц;
      - mult_number — умножение матрицы на число;
      - transpose — транспонирование;
      - determinant — нахождение определителя;
      - calc_complements — расчет матрицы алгебраических дополнений;
      - inverse_matrix — нахождение обратной матрицы.
      - Поддержка точности дробной части до 6 знаков после запятой.
        
#### Тестирование
  - Полное покрытие функций библиотеки модульными тестами с использованием библиотеки Check.
  - Достижение покрытия кода на уровне не менее 80% для всех функций, проверенное с помощью инструмента gcov.
    
#### Инструменты
  - Подготовка Makefile для сборки библиотеки и тестов с целями all, clean, test, s21_matrix.a, gcov_report.
  - Генерация отчета покрытия кода в формате HTML с использованием цели gcov_report.

#### Технологии
  - C11
  - Check
  - Google Style Guide
  - POSIX.1-2017

### Результаты и достижения 
Этот проект реализует библиотеку для работы с матрицами, предоставляя базовые матричные операции, такие как сложение, вычитание, умножение, нахождение обратной матрицы и транспонирование. В процессе работы я освоил написание и тестирование математических операций на языке C, а также научился обеспечивать высокий уровень покрытия кода тестами, что позволило улучшить мои навыки структурированного программирования и работы с математическими структурами данных.

***

## 5. [BrickGame Tetris](https://github.com/Tixon-noxit/C11/tree/main/C7_BrickGame_v1.0)
### Описание
Разработка классической игры Tetris под названием BrickGame v1.0 с использованием языка C и библиотеки ncurses для интерфейса терминала. Этот проект реализует все базовые механики игры, используя конечный автомат для управления логикой игры, а также поддерживает расширенные возможности, такие как уровни, рекорды и система очков с сохранением результатов между запусками.

#### Ключевые особенности

#### Архитектура

##### Программа состоит из двух основных частей:
  - Логическая библиотека игры, реализующая основные механики Tetris, и обеспечивающая взаимодействие с пользовательским интерфейсом.
  - Терминальный интерфейс с использованием библиотеки ncurses для визуализации игрового процесса и отображения дополнительной информации.
  - Реализация конечного автомата для формализации логики игры и управления её состояниями.
    
#### Функциональность

  ##### Основные игровые механики:
  - Поворот фигур, горизонтальное перемещение, ускоренное падение при нажатии клавиши.
  - Предварительный просмотр следующей фигуры.
  - Разрушение заполненных строк и завершение игры при достижении верхней границы.
  - Поддержка управления с помощью физических кнопок на консоли, включая:
  - Начало и конец игры, пауза, стрелки для перемещения и поворота фигуры.
  - Поле 10x20 для размещения игровых фигур.
  - Автоматическое фиксирование фигуры при достижении нижней границы или столкновении с другой фигурой.

Дополнительные возможности

##### Система очков и рекордов:
- Начисление очков за разрушенные строки (100 за 1 строку, 300 за 2 строки, 700 за 3 строки и 1500 за 4 строки).
- Хранение рекордов в файле или встраиваемой СУБД, позволяющее сохранить данные между запусками игры.
  
##### Механика уровней:
- Повышение уровня каждые 600 очков с увеличением скорости падения фигур. Максимальный уровень — 10.

#### Тестирование
- Полное покрытие логики игры модульными тестами с использованием библиотеки Check.
- Обеспечение покрытия тестами на уровне не менее 80% для всех функций логики игры, проверенное с помощью gcov.

#### Инструменты
- Подготовка Makefile с целями: all, install, uninstall, clean, dvi, dist, test, gcov_report.
- Генерация HTML отчета покрытия кода при помощи цели gcov_report.

#### Технологии
- C11
- Ncurses
- Check
- Google Style Guide
- POSIX.1-2017
- 
### Результаты и достижения 
Этот проект представляет реализацию классической игры Tetris для терминала, охватывающей как основные, так и расширенные игровые механики, такие как уровни и рекорды. Работа над проектом позволила мне углубить знания о создании конечных автоматов, программировании на C, работе с терминальными интерфейсами и написании тестов для сложной игровой логики, что значительно улучшило мои навыки структурированного программирования и понимание игровых алгоритмов.

***

## 6. [s21_math](https://github.com/Tixon-noxit/C11/tree/main/C4_s21_math)
### Описание
Разработка библиотеки s21_math на языке C для выполнения основных математических операций, аналогичных функциям из стандартной библиотеки math.h. Цель проекта — создать набор математических функций, включающих тригонометрические вычисления, логарифмы, корни и возведение в степень, с соблюдением стандартов структурного программирования и требований к стилю кода.

#### Ключевые особенности

#### Архитектура
  - Библиотека разработана на языке C стандарта C11 с использованием компилятора gcc.
  - Код библиотеки структурирован и размещён в папке src ветки develop.
  - Каждая функция имеет префикс s21_ для избежания конфликтов с аналогами из стандартной библиотеки math.h.
  - Реализован набор математических операций, включая вычисления тригонометрических функций, логарифмов, корней и возведение в степень.

#### Функциональность
  - Основные функции библиотеки math.h, такие как:
  - Тригонометрические функции (синус, косинус и т.д.).
  - Логарифмические функции (логарифм, экспоненциальные вычисления и т.д.).
  - Функции для работы с корнями и степенями.
  - Дополнительные функции для округления, нахождения абсолютного значения и другие.
  - Реализация без использования устаревших конструкций и библиотек, с соблюдением стандарта POSIX.1-2017.

#### Тестирование
  - Полное покрытие всех функций библиотеки модульными тестами с использованием библиотеки Check.
  - Тесты сравнивают результаты функций s21_math с результатами стандартной библиотеки math.h, что гарантирует корректность расчетов.
  - Покрытие тестами на уровне не менее 80% для каждой функции, проверенное с помощью gcov.
  - Точность вычислений проверяется до 16 значащих цифр, а точность дробной части — до 6 знаков.

#### Инструменты
  - Makefile с целями для сборки и очистки проекта: all, clean, test, s21_math.a, gcov_report.
  - Генерация HTML-отчёта покрытия кода с использованием цели gcov_report.

#### Технологии
  - C11
  - Check
  - Google Style Guide
  - POSIX.1-2017

### Результаты и достижения 
Проект s21_math продемонстрировал навыки в реализации математических функций, структурном программировании и написании модульных тестов для их проверки. Этот проект помог мне укрепить понимание работы с числами с плавающей точкой, оптимизации кода, тестирования точности вычислений и соблюдения код-стиля.
