//
// Created by Тихон Чабусов on 24.04.2024.
//

#ifndef C7_BRICKGAME_V1_0_1_MATRIX_H
#define C7_BRICKGAME_V1_0_1_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "../../../common/inc/defines.h"
#include "../../../common/inc/objects.h"

GameInfo_t *get_current_game_info(void);
TetField *createTetField(int width, int height);
void freeTetField(TetField *tetf);
int collisionTet(void);
TetFigure *rotTetFigure(void);
void freeTetFigure(TetFigure *tf);
void plantFigure(void);
int eraseLinesTet(void);
void dropNewFigure(void);
int lineFieldTet(int i, TetField *tfl);
TetFigure *createNewTetFigure(GameInfo_t *tetg);
void dropLineTet(int i, TetField *tfl);
#endif  // C7_BRICKGAME_V1_0_1_MATRIX_H
