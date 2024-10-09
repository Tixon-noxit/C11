//
// Created by Тихон Чабусов on 24.04.2024.
//

#include "../inc/backend.h"

/**
 * @brief Получает указатель на текущее состояние игры.
 *
 * @return Указатель на структуру GameInfo_t, представляющую текущее состояние
 * игры.
 */
GameInfo_t *get_current_game_info(void) {
  static GameInfo_t state_t;
  return &state_t;
}

/**
 * @brief Возвращает структуру, содержащую информацию о текущем состоянии игры.
 *
 * Эта функция должна вызываться из интерфейса с некоторой периодичностью для
 * поддержания интерфейса в актуальном состоянии.
 *
 * @return Текущая структура состояния игры.
 */
GameInfo_t updateCurrentState(void) {
  GameInfo_t *tetg = get_current_game_info();
  return *tetg;
}

/**
 * @brief Создает и инициализирует набор шаблонов фигур Tetris.
 *
 * @param count Количество шаблонов.
 * @param figures_size Размер области фигуры.
 * @param figures_template Массив блоков для серии шаблонов фигур.
 * @return Указатель на структуру TetFiguresT.
 */
TetFiguresT *createTetFiguresT(int count, int figures_size,
                               TetBlock *figures_template) {
  TetFiguresT *tetft = (TetFiguresT *)malloc(sizeof(TetFiguresT));
  tetft->count = count;        // Количество шаблонов
  tetft->size = figures_size;  // Размер области фигуры
  tetft->blocks = figures_template;  // Массив блоков для серии шаблонов фигур
                                     // (определен заранее)

  return tetft;
}

/**
 * @brief Освобождает память, выделенную под структуру TetFiguresT.
 *
 * @param tetft Указатель на структуру TetFiguresT для освобождения.
 */
void freeTetFiguresT(TetFiguresT *tetft) {
  if (tetft) free(tetft);
}

/**
 * @brief Инициализирует игровые параметры.
 *
 * @param field_width Ширина игрового поля.
 * @param field_height Высота игрового поля.
 * @param figures_size Размер области фигуры.
 * @param count Количество шаблонов фигур.
 * @param figures_template Массив блоков для шаблонов фигур.
 */
void createGameInfo_t(int field_width, int field_height, int figures_size,
                      int count, TetBlock *figures_template) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->field = createTetField(field_width, field_height);
  tetg->figurest = createTetFiguresT(count, figures_size, figures_template);
  tetg->ticks = 70;
  tetg->ticks_left = TET_TICK_START;
  tetg->score = 0;
  tetg->max_score = readMaxScore(MAX_SCORE_FILE);
  TetFigure *next_t = createNewTetFigure(tetg);
  tetg->next_figure = next_t;
  tetg->level = 0;
  tetg->player = (TetPlayer *)malloc(sizeof(TetPlayer));
  tetg->player->action = TET_PLAYER_NOP;
  tetg->playing = Start;
}

/**
 * @brief Освобождает память, выделенную под структуру GameInfo_t.
 */
void freeGameInfo_t(void) {
  GameInfo_t *tetg = get_current_game_info();
  if (tetg) {
    if (tetg->field) {
      freeTetField(tetg->field);
      tetg->field = NULL;  // Обнуляем указатель после освобождения памяти
    }
    if (tetg->figurest) {
      freeTetFiguresT(tetg->figurest);
      tetg->figurest = NULL;  // Обнуляем указатель после освобождения памяти
    }
    // Освобождение игрока
    if (tetg->player) {
      free(tetg->player);
      tetg->player = NULL;
    }
  }
}

/**
 * @brief Обрабатывает действия пользователя.
 *
 * @param action Действие пользователя.
 * @param hold Флаг, указывающий на зажатие клавиши.
 */
void userInput(UserAction_t action, bool hold) {
  GameInfo_t *tetg = get_current_game_info();
  (void)hold;
  // обработка действий игрока
  switch (action) {
    case Right:
      moveFigureRight();
      if (collisionTet()) moveFigureLeft();
      break;
    case Left:
      moveFigureLeft();
      if (collisionTet()) moveFigureRight();
      break;
    case Down:
      moveFigureDown();
      if (collisionTet()) moveFigureUp();
      break;
    case Action: {
      TetFigure *t = rotTetFigure();
      TetFigure *told = tetg->figure;
      tetg->figure = t;
      if (collisionTet()) {
        tetg->figure = told;
        freeTetFigure(t);
      } else {
        freeTetFigure(told);
      }
      break;
    }
    case ESCAPE_BTN:
      tetg->playing = Terminate;
      break;
    case TET_PLAYER_NOP:
    default:
      break;
  }
}

/**
 * @brief Добавляет очки за удаленные линии.
 *
 * @param count_line Количество удаленных линий.
 */
void score_add(int count_line) {
  GameInfo_t *tetg = get_current_game_info();

  if (count_line == 1) {
    tetg->score += 100;
  } else if (count_line == 2) {
    tetg->score += 300;
  } else if (count_line == 3) {
    tetg->score += 700;
  } else if (count_line == 4) {
    tetg->score += 1500;
  }

  // обновление рекорда
  if (tetg->score > readMaxScore(MAX_SCORE_FILE)) {
    updateMaxScore(MAX_SCORE_FILE, tetg->score);
    tetg->max_score = tetg->score;
  }

  int proper_level = floor(tetg->score / 600);

  if (tetg->score > 0) {
    if (proper_level > tetg->level && tetg->level < 10) {
      tetg->level = proper_level;
      tetg->ticks -= 10;  // Увеличить скорость
    }
  }
}

/**
 * @brief Просчитывает один такт игрового цикла.
 */
void calculateTet(void) {
  GameInfo_t *tetg = get_current_game_info();
  if (tetg->ticks_left <= 0 &&
      tetg->playing == Start) {  // Такты перемещения фигур
    tetg->ticks_left = (tetg->ticks * 100);
    moveFigureDown();  // Движение фигуры вниз
    if (collisionTet()) {
      moveFigureUp();  // Вернуть в исходное положение
      plantFigure();   // Перенести блоки на поле
      score_add(eraseLinesTet());  // Посчитать строки, заполненные блоками,
                                   // удалить их и добавить результат в очки
      dropNewFigure();       // Выбросить новую фигуру
      if (collisionTet()) {  // Если при выбросе фигуры происходит столкновение
                             // - игра окончена - на поле нет места
        tetg->playing = Terminate;
        return;
      }
    }
  }
  userInput(tetg->player->action, false);
  tetg->ticks_left--;
}

/**
 * @brief Читает максимальный счет из файла.
 *
 * @param filename Имя файла для чтения.
 * @return Максимальный счет.
 */
int readMaxScore(const char *filename) {
  int max_score = 0;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fscanf(file, "%d", &max_score);
    fclose(file);
  }
  return max_score;
}

/**
 * @brief Обновляет максимальный счет и записывает его в файл.
 *
 * @param filename Имя файла для записи.
 * @param new_score Новый максимальный счет.
 */
void updateMaxScore(const char *filename, int new_score) {
  int max_score = readMaxScore(filename);
  if (new_score > max_score) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
      fprintf(file, "%d", new_score);
      fclose(file);
    }
  }
}
