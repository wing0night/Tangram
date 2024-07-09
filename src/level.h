#ifndef LEVEL_H
#define LEVEL_H

#include "assets.h"
#include "transform.h"
#include "utils.h"

typedef struct Level
{
    Transform *board_level[BOARD_LIST_CNT];
} Level;

Level *Load_Level_1();

Transform *Make_Level(Vector position, double rotation, Vector scale);

void ShowTime();

// void Load_level();

#endif
