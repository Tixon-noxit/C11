//
// Created by Тихон Чабусов on 24.04.2024.
//

#ifndef C7_BRICKGAME_V1_0_1_BACKEND_H
#define C7_BRICKGAME_V1_0_1_BACKEND_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/inc/defines.h"
#include "../../../common/inc/objects.h"
#include "../inc/matrix.h"

TetFigure* createTetFigure(void);

void score_add(int count_line);

int readMaxScore(const char* filename);

void updateMaxScore(const char* filename, int new_score);

TetFigure* createNewTetFigure(GameInfo_t* tetg);

void moveFigureDown(void);

void moveFigureUp(void);

void moveFigureLeft(void);

void moveFigureRight(void);

void calculateTet(void);

void createGameInfo_t(int field_width, int field_height, int figures_size,
                      int count, TetBlock* figures_template);

void freeGameInfo_t(void);

GameInfo_t updateCurrentState(void);

void userInput(UserAction_t action, bool hold);

#endif  // C7_BRICKGAME_V1_0_1_BACKEND_H
