// cat_function.c
#include "cat_functions.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для просчета отступов
int autoTab(char *lineNumberBuffer) {
  // Вычисляем количество пробелов для выравнивания
  int spacesNeeded = 6 - strlen(lineNumberBuffer);
  if (spacesNeeded < 0) {
    spacesNeeded = 0;
  }
  return spacesNeeded;
}

// Функция для нумерации только заполненных строк (-b)
void numberNonblankLines(char **line, int lineNumberGlobal, int flag_t) {
  char *original = *line;
  static int lineNumber = 0;  // Статическая переменная для учета номеров
  // строк
  if (lineNumberGlobal == 1) {
    lineNumber = 0;
  }

  // Если строка не пуста, то нумеруем ее
  if (strlen(original) > 0 && original[0] != '\n') {
    char lineNumberBuffer[32];
    snprintf(lineNumberBuffer, sizeof(lineNumberBuffer), "%d", ++lineNumber);

    // Создаем строку с номером строки и выравниваем его
    char formattedLineNumber[32];
    snprintf(formattedLineNumber, sizeof(formattedLineNumber), "%*s%d",
             autoTab(lineNumberBuffer), "", lineNumber);
    char *spase = "  ";
    char *resultLine =
        (char *)malloc(strlen(original) + strlen(formattedLineNumber) + 3);
    if (flag_t) {
      snprintf(resultLine, strlen(original) + strlen(formattedLineNumber) + 3,
               "%s%s%s", formattedLineNumber, spase, original);
    } else {
      snprintf(resultLine, strlen(original) + strlen(formattedLineNumber) + 3,
               "%s\t%s", formattedLineNumber, original);
    }

    free(*line);
    *line = resultLine;
  }
}

// Функция для замены(добавления) символа конца строки на "$" в каждой строке
// (-e)
void replaceEndOfLineWithDollarSigns(char **line) {
  char *original = *line;
  size_t original_length = strlen(original);

  // Буфер для новой строки с дополнительным местом на символ "$" и
  // нулевой символ
  char *result = (char *)malloc(original_length * 2 + 1);
  result[0] = '\0';

  for (size_t i = 0; i < original_length; i++) {
    if (original[i] == '\n') {
      strcat(result, "$\n");

    } else {
      strncat(result, &original[i], 1);
    }
  }

  // Освобождаем старую строку
  free(*line);

  // Обновляем указатель на новую строку
  *line = result;
}

// Функция для нумерации всех строк в файле (-n)
void numberAllLines(char **line, int lineNumber, int flag_t) {
  char lineNumberStr[16];  // Максимальное количество цифр в номере строки (для
                           // больших файлов)
  snprintf(lineNumberStr, sizeof(lineNumberStr), "%d", lineNumber);

  // Создаем строку с номером строки и выравниваем его
  char lineNumberBuffer[32];  // Максимальная длина строки с номером строки
  snprintf(lineNumberBuffer, sizeof(lineNumberBuffer), "%*s%d",
           autoTab(lineNumberStr), "", lineNumber);

  // Создаем новую строку с номером и текстом строки
  char *resultLine =
      (char *)malloc(strlen(*line) + strlen(lineNumberBuffer) +
                     2);  // 2 - на символы табуляции и нулевой символ

  char *spase = "  ";
  if (flag_t) {
    snprintf(resultLine, strlen(*line) + strlen(lineNumberBuffer) + 3, "%s%s%s",
             lineNumberBuffer, spase, *line);
  } else {
    snprintf(resultLine, strlen(*line) + strlen(lineNumberBuffer) + 2, "%s\t%s",
             lineNumberBuffer, *line);
  }

  // Освобождаем старую строку и обновляем указатель
  free(*line);
  *line = resultLine;
}

// Функция для сжатия смежных пустых строк, оставляя одну пустую строку (-s)
void squeezeAdjacentBlankLines(char **line, int *display) {
  char *original = *line;
  static int previousLineWasBlank = 0;  // Переменная для отслеживания
  // предыдущей пустой строки

  // Если строка не пуста, то выводим ее
  if (original[0] != '\n' || strlen(original) <= 0) {
    previousLineWasBlank = 0;
    *display = 1;
  } else {
    previousLineWasBlank++;
  }

  if (previousLineWasBlank > 1) {
    *display = 0;
  }
}

// Функция для отображения табуляции как "^I" (-t)
void displayTabsAsCaretI(char **buffer) {
  char *original = *buffer;
  char *result = (char *)malloc(strlen(original) * 2 +
                                1);  // Дополнительное место для символа '\0'
  char *resultPtr = result;

  // int previousWasDigit = 0; // Флаг для отслеживания, была ли предыдущая
  // цифра

  while (*original != '\0') {
    if (*original == '\t') {
      *resultPtr++ = '^';
      *resultPtr++ = 'I';

    } else {
      *resultPtr++ = *original;
    }
    original++;
  }

  *resultPtr = '\0';  // Завершаем строку нулевым символом

  // Освобождаем старый буфер
  free(*buffer);

  // Обновляем указатель на новый буфер
  *buffer = result;
}

// Функция для отображения непечатаемых знаков (-v)
void displayNonPrintableCharacters(char *buffer) {
  char *original = buffer;
  char *result = (char *)malloc(strlen(original) * 4 +
                                1);  // Дополнительное место для символа '\0'
  char *resultPtr = result;

  while (*original != '\0') {
    if ((*original < ' ' || *original >= 127) && *original != '\t' &&
        *original != '\n') {
      if (*original == 127) {
        *resultPtr++ = '^';
        *resultPtr++ = '?';
      } else if (*original < 32) {
        *resultPtr++ = '^';
        *resultPtr++ = *original + '@';  // Исправленное представление
      } else {
        *resultPtr++ = 'M';
        *resultPtr++ = '-';
        *resultPtr++ = *original - 128;
      }
    } else {
      *resultPtr++ = *original;
    }
    original++;
  }

  *resultPtr = '\0';
  strcpy(buffer, result);  // Копирование результата обратно в исходную строку
  free(result);            // Освобождение памяти
}
