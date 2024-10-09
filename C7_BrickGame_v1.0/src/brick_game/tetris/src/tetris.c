/**
 * @file tetris.c
 * @brief Функции для управления игровым процессом Tetris.
 *
 * Этот файл содержит функции для управления игровым процессом, обработки ввода
 * пользователя, приостановки и возобновления игры, а также основной игровой
 * цикл.
 */

#include "../inc/tetris.h"

/**
 * @brief Функция для приостановки и возобновления игры.
 */
void pauseGame(void) {
  GameInfo_t *tetg = get_current_game_info();
  tetg->pause = (tetg->pause == Pause) ? Start : Pause;
}

/**
 * @brief Обработка нажатий клавиш пользователем.
 *
 * Функция обрабатывает нажатия клавиш и выполняет соответствующие действия,
 * такие как перемещение фигуры, поворот, приостановка игры и выход.
 */
void keystrokes(void) {
  GameInfo_t *tetg = get_current_game_info();
  int ch = getch();
  switch (ch) {
    case 'S':
    case 's':
      tetg->player->action = Start;
      break;
    case KEY_DOWN:
      tetg->player->action = Down;
      break;
    case KEY_LEFT:
      tetg->player->action = Left;
      break;
    case KEY_RIGHT:
      tetg->player->action = Right;
      break;
    case ' ':
      tetg->player->action = Action;
      break;
    case 'P':
    case 'p':
      pauseGame();
      break;
    case ESCAPE:
      tetg->player->action = ESCAPE_BTN;
      break;
    case ERR:
    default:
      tetg->player->action = TET_PLAYER_NOP;
      break;
  }
}

/**
 * @brief Проверка состояния паузы и выполнение соответствующих действий.
 *
 * Если игра не находится на паузе, функция продолжает обычное выполнение
 * игрового цикла, включая обработку ускоренного падения фигуры при нажатии на
 * нижнюю стрелку.
 */
void check_pause(void) {
  GameInfo_t *tetg = get_current_game_info();
  // Если игра не находится на паузе, продолжить обычное выполнение
  if (tetg->pause != Pause) {
    if (tetg->player->action == Down) {
      // Ускоренное падение фигуры при нажатии на нижнюю стрелку
      while (!collisionTet()) {
        moveFigureDown();
        printGameInfo_t();  // Обновление отображения поля после каждого шага
        // вниз
        usleep(FALL_DELAY_US);
      }
      moveFigureUp();
    } else {
      calculateTet();  // Просчет игрового цикла
    }
  }
}

/**
 * @brief Главная функция, управляющая игровым циклом.
 *
 * Функция инициализирует игру, запускает основной игровой цикл, обрабатывает
 * ввод пользователя, проверяет состояние паузы и обновляет отображение игры.
 * Завершает игру при достижении условия окончания.
 *
 * @return int Статус завершения программы.
 */
int main(void) {
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};  // Фиксация времени

  showStartScreen();  // Показ экрана с сообщением перед началом игры

  WIN_INIT;

  createGameInfo_t(FIELD_WIDTH, FIELD_HEIGHT, 5, 7, tet_templates);
  GameInfo_t *tetg = get_current_game_info();
  dropNewFigure();

  while (tetg->playing != Terminate && tetg->level < 11) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    keystrokes();
    check_pause();
    printGameInfo_t();

    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec == 33000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
      nanosleep(&ts2, &ts1);
    };
  };

  freeGameInfo_t();
  endwin();
  return 0;
}
