//
// Created by Тихон Чабусов on 24.04.2024.
//

#ifndef C7_BRICKGAME_V1_0_1_TETRIS_H
#define C7_BRICKGAME_V1_0_1_TETRIS_H

#include <stdbool.h>

#define _GNU_SOURCE
#include <time.h>  // для struct timespec и функций clock_gettime, nanosleep
#include <unistd.h>  // для usleep

#include "../../../common/inc/objects.h"
#include "../../../gui/cli/inc/frontend.h"
#include "backend.h"

#define TEST_MAX_SCORE_FILE "max_score_test.txt"

// Фигурки :)
TetBlock tet_templates[] = {
    {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0},
    {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {1}, {0}, {0}, {0}, {1}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0},
    {0}, {0}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {1}, {0}, {0},
    {0}, {0}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {1}, {1}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0},
    {0}, {0}, {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {1}, {1}, {0}, {0}, {0}, {1}, {1}, {0}, {0},
    {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

#endif  // C7_BRICKGAME_V1_0_1_TETRIS_H
