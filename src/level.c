#include "assets.h"
#include "level.h"
#include "transform.h"
#include "utils.h"
#include <string.h>

extern CountTime;

Vector level_p[8][7] = {
    P(0, 0),           P(2.828, -2.828), P(1.242, -6.07),   P(-2.828, 5.656), P(1.414, 8.484),   P(-1.879, -6.363),
    P(-2.121, -0.707), P(-4, 0.586),     P(2.828, -0.586),  P(0, 0),          P(-4, 4.586),      P(7.828, -1.586),
    P(-5, 6.586),      P(-3, 6.586),     P(0, 0),           P(1.7, 2.3),      P(3, -3),          P(3.4, 6.3),
    P(-4, -3.414),     P(3.293, -6.707), P(-7.535, -4.121), P(1, 1),          P(1.586, -3.242),  P(-2.414, -0.172),
    P(-3, 5),          P(6, -2.828),     P(-2, 7),          P(-4, 7),         P(-1.414, -4.242), P(-4, -2),
    P(1.414, -2.828),  P(0.828, 1.172),  P(-0.172, 4.172),  P(1.828, -0.828), P(1.535, 5.051),   P(2, 0),
    P(0, -2),          P(-4, 4),         P(0, 2),           P(-3, -1),        P(-1, 0),          P(2, 3),
};
double level_a[8][7] = {-45, 135, -45, 45, 180, -45, 45,  180, 180, 0,   0, 135, 90,  -90,
                        180, 0,   135, 0,  180, -45, 225, 90,  45,  -90, 0, -45, -90, 90,
                        45,  0,   90,  0,  45,  -90, -45, -90, 180, -45, 0, 45,  90,  0};

Level *Load_Level_1()
{
    Level *level;
    level->board_level[0] = Make_Level(P(0, 2), 0, P(1, 1));
    level->board_level[1] = Make_Level(P(2, 0), -90, P(1, 1));
    level->board_level[2] = Make_Level(P(-3, -3), -45, P(1, 1));
    level->board_level[3] = Make_Level(P(-2, 0), 0, P(1, 1));
    level->board_level[4] = Make_Level(P(1, -3), -45, P(1, 1));
    level->board_level[5] = Make_Level(P(0, -1), 180, P(1, 1));
    level->board_level[6] = Make_Level(P(-3, 2), 90, P(1, 1));
    return level;
}

Transform *Make_Level(Vector position, double rotation, Vector scale)
{
    Transform *Temp;
    Temp->position = position;
    Temp->rotation = rotation;
    Temp->scale = scale;
    return Temp;
}

void ShowTime()
{
    char str[10];
    const int Limit = 60;

    sprintf(str, "%d/%d", CountTime, Limit);

    char str1[40] = "Time/Limit(s): ";
    strcat(str1, str);

    textbox(1, 26, 2, 4, 2, str1, 40);
}

