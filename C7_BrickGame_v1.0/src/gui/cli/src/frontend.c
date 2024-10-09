//
// Created by Тихон Чабусов on 24.04.2024.
//

/**
 * @file frontend.c
 * @brief Функции для отрисовки игрового интерфейса.
 *
 * Этот файл содержит функции для отрисовки различных элементов игрового
 * интерфейса Tetris.
 */

#include "../inc/frontend.h"

/**
 * @brief Функция для отрисовки текста по центру заданной области.
 *
 * @param top_y Верхняя граница области.
 * @param bottom_y Нижняя граница области.
 * @param left_x Левая граница области.
 * @param right_x Правая граница области.
 * @param text Текст для отображения.
 */
void draw_centered_text(int top_y, int bottom_y, int left_x, int right_x,
                        const char* text) {
  int text_length = strlen(text);
  int center_y = (top_y + bottom_y) / 2;
  int center_x = (left_x + right_x - text_length) / 2;

  mvprintw(center_y, center_x, "%s", text);
}

/**
 * @brief Отрисовка прямоугольника вокруг игровой области.
 *
 * @param top_y Координата Y верхней границы.
 * @param bottom_y Координата Y нижней границы.
 * @param left_x Координата X левой границы.
 * @param right_x Координата X правой границы.
 */
void draw_game_area_border(int top_y, int bottom_y, int left_x, int right_x) {
  // Верхняя и нижняя линии
  mvhline(top_y, left_x, ACS_HLINE, right_x - left_x + 1);
  mvhline(bottom_y, left_x, ACS_HLINE, right_x - left_x + 1);
  // Левая и правая линии
  mvvline(top_y + 1, left_x, ACS_VLINE, bottom_y - top_y - 1);
  mvvline(top_y + 1, right_x, ACS_VLINE, bottom_y - top_y - 1);
  // Угловые символы
  mvaddch(top_y, left_x, ACS_ULCORNER);   // Верхний левый угол
  mvaddch(top_y, right_x, ACS_URCORNER);  // Верхний правый угол
  mvaddch(bottom_y, left_x, ACS_LLCORNER);  // Нижний левый угол
  mvaddch(bottom_y, right_x, ACS_LRCORNER);  // Нижний правый угол
}

/**
 * @brief Отрисовка следующей фигуры, счета, рекорда и уровня.
 */
void printNextFigure(void) {
  GameInfo_t* tetg = get_current_game_info();
  TetField* field = tetg->field;
  TetFigure* next_figure = tetg->next_figure;

  // Отрисовка прямоугольника вокруг следующей фигуры
  draw_game_area_border(2, next_figure->size + 4, (field->width) * 2 + 5,
                        (field->width) * 2 + 3 + next_figure->size * 2 + 1);

  // Вывод блока следующей фигуры
  mvprintw(2, (FIELD_WIDTH * 2) + 5, "NEXT");
  // Отображение следующей фигуры в правой части экрана
  for (int i = 0; i < next_figure->size; i++) {
    for (int j = 0; j < next_figure->size; j++) {
      mvprintw(
          i + 3, (field->width) * 2 + 4 + j * 2, "%c",
          next_figure->blocks[i * next_figure->size + j].b == 0 ? ' ' : '#');
    }
  }

  // Отрисовка прямоугольника вокруг счета игрока
  draw_game_area_border(10, 12, (field->width) * 2 + 5,
                        (field->width) * 2 + 3 + 11);
  // Вывод счета игрока
  mvprintw(10, (FIELD_WIDTH * 2) + 5, "SCORE");
  mvprintw(11, (FIELD_WIDTH * 2) + 6, "%d", tetg->score);

  // Отрисовка прямоугольника вокруг рекорда игрока
  draw_game_area_border(13, 15, (field->width) * 2 + 5,
                        (field->width) * 2 + 3 + 11);
  // Вывод рекорда игрока
  mvprintw(13, (FIELD_WIDTH * 2) + 5, "Hi-SCORE");
  mvprintw(14, (FIELD_WIDTH * 2) + 6, "%d", tetg->max_score);

  // Отрисовка прямоугольника вокруг уровня игрока
  draw_game_area_border(16, 18, (field->width) * 2 + 5,
                        (field->width) * 2 + 3 + 11);
  // Вывод уровня
  mvprintw(16, (FIELD_WIDTH * 2) + 5, "LEVEL");
  mvprintw(17, (FIELD_WIDTH * 2) + 6, "%d", tetg->level);
}

/**
 * @brief Вывод игровой ситуации на экран с выделением игровой зоны белой
 * линией.
 */
void printGameInfo_t(void) {
  GameInfo_t currentState = updateCurrentState();
  GameInfo_t* tetg = &currentState;
  TetField* tf = tetg->field;
  TetFigure* t = tetg->figure;

  curs_set(0);  // Скрыть курсор

  int offsetX = 2;  // Смещение игрового поля вправо
  int offsetY = 0;  // Если нужно сместить вниз, измените значение

  // Отрисовка игровой области без границ
  for (int i = 0; i < tf->height; i++) {
    for (int j = 0; j < tf->width; j++) {
      int sum = 0;
      if (tf->blocks[i * tf->width + j].b != 0) {
        sum = 1;
      } else {
        int x =
            (j - t->x) * 2;  // Учитываем, что каждый блок занимает две позиции
        int y = i - t->y;
        if (x >= 0 && x < t->size * 2 && y >= 0 && y < t->size) {
          if (t->blocks[y * t->size + x / 2].b != 0) {
            sum = 1;
          };
        };
      };
      if (sum > 0) {
        // Проверяем, что x не выходит за границы игровой области
        if (j * 2 >= 0 && j * 2 < tf->width * 2) {
          // Отрисовка сегмента фигуры как '[ ]' (два символа)
          mvprintw(i + offsetY, j * 2 + offsetX, "[]");
        }
      } else {
        // Отрисовка пустого места (два пробела)
        mvprintw(i + offsetY, j * 2 + offsetX, "  ");
      }
    }
  }

  // Отрисовка границ игровой области
  draw_game_area_border(offsetY, tf->height + offsetY, offsetX - 1,
                        offsetX + (tf->width) * 2);

  // Отрисовка границ области статистики
  draw_game_area_border(offsetY, tf->height + offsetY,
                        offsetX + (tf->width) * 2,
                        offsetX + (tf->width) * 2 + 14);

  printNextFigure();

  refresh();  // Обновление экрана
}

void showStartScreen(void) {
  initscr();  // Инициализация экрана
  noecho();  // Отключение отображения вводимых символов
  curs_set(0);  // Скрыть курсор

  int top_y = 0;
  int bottom_y = 20;
  int left_x = 1;
  int right_x = 22;

  draw_game_area_border(top_y, bottom_y, left_x, right_x);
  draw_game_area_border(top_y, bottom_y, left_x + 21, right_x + 14);
  draw_centered_text(top_y, bottom_y, left_x, right_x, "Press S to start");

  int ch;
  while ((ch = getch()) != 's' && ch != 'S') {
    // Ожидание нажатия клавиши 'S' или 's'
  }

  clear();  // Очистка экрана перед началом игры
  refresh();
  endwin();  // Завершение работы с ncurses
}
