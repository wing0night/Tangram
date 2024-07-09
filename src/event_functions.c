#include "assets.h"
#include "event_functions.h"
#include "level.h"
#include "libgraphics.h"
#include <math.h>
#define TIMER_BLINK500 1

const int mseconds500 = 500;

int Level_Num = 0;

int Judge = 0;

int isInLevel = 0;

int Instruction = 0;

int CountTime = 0;

int HalfSecond = 0;

int TimeUp = 0;

int i;

int flag[8] = {0};

int flag_Cr = 0;

int Created = 0;
int Created_Pre = 0;

int Level_Sum = 3;

int In_Cr = 0;

int Show = 0;

static string gBackgroundColor = "White";

// 引用一下在main.c中的窗口宽高。
extern double WINDOW_WIDTH;
extern double WINDOW_HEIGHT;

// extern Asset *gAssets_Cr;

extern Vector level_p[6][7];
extern double level_a[6][7];

extern Asset *gAssets;
// 绘制背景。目前使用纯色。
static void draw_background();

static void draw_background_LevelSelect();

// 显示GUI控件。
static void ShowGUI();

// 上一个选中的板，相比movingBoard他不会被重置为NULL。
static Board *gLastSelectedBoard = NULL;

bool Is_Rotation_Match(Board *board)
{

    return ((int)(board->transform->rotation - board->transform_l->rotation) % 360 == 0);
}

void MyMouseEvent(int x, int y, int button, int event)
{
    DisplayClear();
    uiGetMouse(x, y, button, event);
    if (Level_Num != 0)
    {
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
    }

    else if (flag_Cr != 0)
    {

        UpdateAll_Cr();
        ShowGUI();
        isInLevel = 0;
    }

    else
    {
        UpdateAll_LevelSelect();
        if (Created == 1)
        {
            ShowGUI_LevelSelect_Plus();
        }
        else
        {
            ShowGUI_LevelSelect();
        }
    }

    static bool isMouseDown = FALSE;
    static Board *movingBoard = NULL;
    static Board *Parallel_Board = NULL;
    static Vector delta = ZERO_VECTOR;
    double px = ScaleXInches(x);
    double py = ScaleYInches(y);

    switch (event)
    {
    case MOUSEMOVE:
        if (isMouseDown)
        {
            if (movingBoard != NULL)
            {
                MoveObjectTo(movingBoard->transform, VectorAdd(P(px, py), delta));
                if (movingBoard->order == 1)
                {
                    Parallel_Board = Get_Board_i(2);
                }

                else if (movingBoard->order == 2)
                {
                    Parallel_Board = Get_Board_i(1);
                }

                else if (movingBoard->order == 6)
                {
                    Parallel_Board = Get_Board_i(7);
                }

                else if (movingBoard->order == 7)
                {
                    Parallel_Board = Get_Board_i(6);
                }

                else
                {
                    Parallel_Board = Get_Board_i(1);
                }

                if (movingBoard->order == 4)
                {
                    if ((int)(movingBoard->transform->rotation - movingBoard->transform_l->rotation) % 90 == 0)
                    {
                        if ((movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) > -0.05 &&
                            (movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) < 0.05)
                        {
                            movingBoard->transform->position.x = movingBoard->transform_l->position.x;
                            movingBoard->transform->position.y = movingBoard->transform_l->position.y;

                            if (flag[movingBoard->order] == 0)
                            {
                                Judge++;
                            }
                            flag[movingBoard->order]++;
                        }
                    }
                }

                if (movingBoard->order == 5)
                {
                    if ((int)(movingBoard->transform->rotation - movingBoard->transform_l->rotation) % 180 == 0)
                    {
                        if ((movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) > -0.05 &&
                            (movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) < 0.05)
                        {
                            movingBoard->transform->position.x = movingBoard->transform_l->position.x;
                            movingBoard->transform->position.y = movingBoard->transform_l->position.y;

                            if (flag[movingBoard->order] == 0)
                            {
                                Judge++;
                            }
                            flag[movingBoard->order]++;
                        }
                    }
                }

                if (Is_Rotation_Match(movingBoard))
                {
                    if ((movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) > -0.05 &&
                        (movingBoard->transform->position.x) - (movingBoard->transform_l->position.x) < 0.05)
                    {
                        movingBoard->transform->position.x = movingBoard->transform_l->position.x;
                        movingBoard->transform->position.y = movingBoard->transform_l->position.y;

                        if (flag[movingBoard->order] == 0)
                        {
                            Judge++;
                        }
                        flag[movingBoard->order]++;
                    }
                }

                if ((int)(movingBoard->transform->rotation - Parallel_Board->transform_l->rotation) % 360 == 0)
                {

                    if ((movingBoard->transform->position.x) - (Parallel_Board->transform_l->position.x) > -0.05 &&
                        (movingBoard->transform->position.x) - (Parallel_Board->transform_l->position.x) < 0.05)
                    {
                        movingBoard->transform->position.x = Parallel_Board->transform_l->position.x;
                        movingBoard->transform->position.y = Parallel_Board->transform_l->position.y;

                        if (flag[movingBoard->order] == 0)
                        {
                            Judge++;
                        }
                        flag[movingBoard->order]++;
                    }
                }
            }
        }
        break;
    case BUTTON_UP:

        isMouseDown = FALSE;
        if (movingBoard != NULL)
        {
            movingBoard = NULL;
        }
        break;
    case BUTTON_DOWN:
        if (button == LEFT_BUTTON)
        {
            // puts("Down");
            isMouseDown = TRUE;
            movingBoard = GetSelectedBoard(P(px, py));
            if (movingBoard != NULL)
            {
                delta = VectorSub(movingBoard->transform->position, P(px, py));
                gLastSelectedBoard = movingBoard;
            }
        }
        break;
    default:
        break;
    }
}

void UpdateAll()
{
    int i;
    draw_background();

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard_l(GetAssets()->boards[i]);
    }

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard(GetAssets()->boards[i]);
    }
    if (flag_Cr == 0)
    {
        ShowTime();
    }

    // UpdateDisplay();
}

void UpdateAll_LevelSelect()
{
    int i;
    draw_background_LevelSelect();

    // UpdateDisplay();
}

void UpdateAll_Cr()
{

    int i;
    draw_background();

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard(GetAssets()->boards[i]);
    }
    DrawBoard_Cr();
    textbox(1, 21, 18, 4.5, 1, "<Create you level here>", 100);
    textbox(1, 19, 17, 8.5, 1, "<Make sure that every board is in this blue area>", 100);

    // UpdateDisplay();
    if (Created_Pre == 1)
    {
        textbox(1, 21, 1.5, 5, 1, "Level Created~", 20);
    }
}

void Load_SelectedLevel(int i)
{
    LoadAllAssets(i);
}

void myKeyboardEvent(int key, int event)
{
    uiGetKeyboard(key, event); // needed for using simpleGUI
    ShowGUI();
}

static void ShowGUI()
{
    // 旋转按钮，将板逆时针旋转45度。

    if (button(GenUIID(0), 1, 11.3, 2, 1, "<Turn"))
    {
        if (gLastSelectedBoard != NULL)
        {
            double rotation = gLastSelectedBoard->transform->rotation;
            if (rotation + 45 > 360)
            {
                rotation -= 360;
            }
            rotation += 45;
            RotateObjectTo(gLastSelectedBoard->transform, rotation);
            if (flag_Cr == 1)
            {
                UpdateAll_Cr();
            }
            else
            {
                UpdateAll();
            }

            button(GenUIID(0), 1, 11.3, 2, 1, "<Turn");
        }
    }
    if (button(GenUIID(0), 7, 11.3, 2, 1, "Turn>"))
    {
        if (gLastSelectedBoard != NULL)
        {
            double rotation = gLastSelectedBoard->transform->rotation;
            if (rotation + 45 > 360)
            {
                rotation -= 360;
            }
            else if (rotation - 45 < 0)
            {
                rotation += 360;
            }
            rotation -= 45;
            RotateObjectTo(gLastSelectedBoard->transform, rotation);
            if (flag_Cr == 1)
            {
                UpdateAll_Cr();
            }
            else
            {
                UpdateAll();
            }

            button(GenUIID(0), 1, 11.3, 2, 1, "<Turn");
            button(GenUIID(0), 7, 11.3, 2, 1, "Turn>");
        }
    }
    // 翻转按钮。将板沿相对坐标系y轴翻转。
    if (button(GenUIID(0), 4, 11.3, 2, 1, "Flip"))
    {
        if (gLastSelectedBoard != NULL)
        {
            double rotation = gLastSelectedBoard->transform->rotation;
            if (rotation + 180 > 360)
            {
                rotation -= 360;
            }

            rotation += 180;
            RotateObjectTo(gLastSelectedBoard->transform, rotation);
            if (flag_Cr == 1)
            {
                UpdateAll_Cr();
            }
            else
            {
                UpdateAll();
            }

            button(GenUIID(0), 1, 11.3, 2, 1, "<Turn");
            button(GenUIID(0), 7, 11.3, 2, 1, "Turn>");
            button(GenUIID(0), 4, 11.3, 2, 1, "Flip");
        }
    }
    if (button(GenUIID(0), 4, 10, 2, 1, "ReLoad"))
    {

        if (flag_Cr == 1)
        {
            LoadAllAssets_Cr();
            UpdateAll_Cr();
        }
        else
        {
            for (i = 0; i <= 8; i++)
            {
                flag[i] = 0;
            }
            if (Judge >= 7)
            {
                Judge = 0;
            }
            LoadAllAssets(Level_Num);
            if (flag_Cr == 1)
            {
                UpdateAll_Cr();
            }
            else
            {
                UpdateAll();
            }
        }

        button(GenUIID(0), 1, 11.3, 2, 1, "<Turn");
        button(GenUIID(0), 7, 11.3, 2, 1, "Turn>");
        button(GenUIID(0), 4, 11.3, 2, 1, "Flip");
        button(GenUIID(0), 4, 10, 2, 1, "ReLoad");
    }

    if (button(GenUIID(0), 1, 14.5, 4, 2, "Instruction"))
    {

        Instruction = 1;

        if (flag_Cr == 1)
        {
            UpdateAll_Cr();
        }
        else
        {
            UpdateAll();
        }
        button(GenUIID(0), 1, 11.3, 2, 1, "<Turn");
        button(GenUIID(0), 7, 11.3, 2, 1, "Turn>");
        button(GenUIID(0), 4, 11.3, 2, 1, "Flip");
        button(GenUIID(0), 4, 10, 2, 1, "ReLoad");
        button(GenUIID(0), 1, 14.5, 4, 2, "Instruction");
    }

    if (button(GenUIID(0), 1, 17, 4, 2, "Return"))
    {

        Level_Num = 0;
        isInLevel = 0;
        flag_Cr = 0;
        In_Cr = 0;
        Created_Pre = 0;
        SetPenSize(10);

        CountTime = 0;
        Instruction = 0;
        Judge = 0;
        Show = 0;
        for (i = 0; i <= 8; i++)
        {
            flag[i] = 0;
        }
        cancelTimer(TIMER_BLINK500);
        UpdateAll_LevelSelect();
        if (Created == 1)
        {
            ShowGUI_LevelSelect_Plus();
        }
        else
        {
            ShowGUI_LevelSelect();
        }
    }

    if (flag_Cr == 1)
    {
        if (button(GenUIID(0), 26.5, 1.5, 4, 2, "Create->"))
        {

            for (i = 1; i <= 7; i++)
            {
                level_p[6][i - 1] = gAssets->boards[i - 1]->transform->position;

                level_a[6][i - 1] = gAssets->boards[i - 1]->transform->rotation;
            }

            Created = 1;
            Created_Pre = 1;
            textbox(1, 21, 1.5, 5, 1, "Level Created~", 20);
        }
    }

    if (Judge >= 7)
    {

        textbox(1, 10, 10, 4, 2, "Success!", 20);
    }

    if (Level_Num != 0)
    {
        ShowTitle(Level_Num);
    }

    if (Instruction == 1 && flag_Cr == 0)
    {
        textbox(1, 5.8, 14.8, 8, 1, "Try to find the right way to place the board!", 100);
    }
    else if (Instruction == 1 && flag_Cr == 1)
    {
        textbox(1, 5.8, 14.8, 8, 1, "Create your own level within this blue area!", 100);
    }
}

void ShowGUI_LevelSelect()
{
    SetPenSize(10);
    if (button(GenUIID(1), 18.5, 10, 4, 4, "Create My Own Level"))
    {
        flag_Cr = 1;
        Created_Pre = 0;
        Show = 0;
        LoadAllAssets_Cr();

        UpdateAll_Cr();
        ShowGUI();

        Level_Num = 0;
        isInLevel = 0;
        TimeUp = 0;
        // Created = 0;
    }

    else if (button(GenUIID(1), 3.5, 10, 3, 3, "Level1"))
    {
        Level_Num = 1;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 8.5, 10, 3, 3, "Level2"))
    {
        Level_Num = 2;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 13.5, 10, 3, 3, "Level3"))
    {
        Level_Num = 3;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 3.5, 5, 3, 3, "Level4"))
    {
        Level_Num = 4;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 8.5, 5, 3, 3, "Level5"))
    {
        Level_Num = 5;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 13.5, 5, 3, 3, "Level6"))
    {
        Level_Num = 6;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }

    else if (button(GenUIID(1), 13, 16, 4, 2, "Tangram"))
    {
        SetPenSize(5);
        Show = 1;
        textbox(1, 14, 14.5, 2, 1, "Welcome!", 10);
        SetPenSize(10);
    };
    /*else if(Created && isInLevel == 0){
        ShowGUI_Plus();

    }*/

    if (TimeUp == 1)
    {
        SetPenSize(10);
        textbox(1, 15, 2, 8, 2, "You've run out of time!", 50);
    }
    if (Show == 1)
    {
        SetPenSize(5);
        textbox(1, 14, 14.5, 2, 1, "Welcome!", 10);
        SetPenSize(10);
    }
}

void ShowGUI_LevelSelect_Plus()
{

    if (button(GenUIID(1), 18.5, 10, 4, 4, "Create My Own Level"))
    {
        Show = 0;
        flag_Cr = 1;
        Created_Pre = 0;
        LoadAllAssets_Cr();

        UpdateAll_Cr();
        ShowGUI();

        Level_Num = 0;
        isInLevel = 0;
        TimeUp = 0;
        // Created = 0;
    }

    else if (button(GenUIID(1), 3.5, 10, 3, 3, "Level1"))
    {
        Level_Num = 1;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 8.5, 10, 3, 3, "Level2"))
    {
        Level_Num = 2;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 13.5, 10, 3, 3, "Level3"))
    {
        Level_Num = 3;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 3.5, 5, 3, 3, "Level4"))
    {
        Level_Num = 4;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
    else if (button(GenUIID(1), 8.5, 5, 3, 3, "Level5"))
    {
        Level_Num = 5;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }

    else if (button(GenUIID(1), 13.5, 5, 3, 3, "Level6"))
    {
        Level_Num = 6;
        Show = 0;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }

    else if (button(GenUIID(1), 24.5, 10, 3, 3, "My Level"))
    {

        Show = 0;
        In_Cr = 1;
        Level_Num = 7;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }

    else if (button(GenUIID(1), 13, 16, 4, 2, "Tangram"))
    {
        SetPenSize(5);
        Show = 1;
        textbox(1, 14, 14.5, 2, 1, "Welcome!", 10);
        SetPenSize(10);
    };

    if (TimeUp == 1)
    {
        SetPenSize(10);
        textbox(1, 15, 2, 8, 2, "You've run out of time!", 50);
    }

    if (Show == 1)
    {
        SetPenSize(5);
        textbox(1, 14, 14.5, 2, 1, "Welcome!", 10);
        SetPenSize(10);
    }
}

static void draw_background()
{
    StartFilledRegion(1.0);
    MovePen(0, 0);
    SetPenColor(gBackgroundColor);
    DrawLine(0, WINDOW_HEIGHT);
    DrawLine(WINDOW_WIDTH, 0);
    DrawLine(0, -WINDOW_HEIGHT);
    DrawLine(-WINDOW_WIDTH, 0);
    EndFilledRegion();
}

static void draw_background_LevelSelect()
{
    StartFilledRegion(1.0);
    MovePen(0, 0);
    SetPenColor("Yellow");
    DrawLine(0, WINDOW_HEIGHT);
    DrawLine(WINDOW_WIDTH, 0);
    DrawLine(0, -WINDOW_HEIGHT);
    DrawLine(-WINDOW_WIDTH, 0);
    EndFilledRegion();
}

void TimerEventProcess()
{
    /*UpdateAll();
    ShowGUI();*/
    if (TIMER_BLINK500)
    {
        if (isInLevel)
        {
            HalfSecond++;
            UpdateAll();
            ShowGUI();
            ShowTitle(Level_Num);
            if (HalfSecond % 2 == 0)
            {
                CountTime++;
            }
        }

        else if (flag_Cr == 0)
        {
            if (Created == 1)
            {
                ShowGUI_LevelSelect_Plus();
            }
            else
            {
                ShowGUI_LevelSelect();
            }
        }
    }
    if (CountTime == 60)
    {
        UpdateAll_LevelSelect();
        ShowGUI_LevelSelect();
        Level_Num = 0;
        isInLevel = 0;

        Instruction = 0;
        Judge = 0;
        TimeUp = 1;
        CountTime = 0;
        SetPenSize(10);
        textbox(1, 15, 2, 8, 2, "You've run out of time!", 50);
    }
}

void ShowGUI_Plus()
{

    if (button(GenUIID(1), 25, 10, 3, 3, "My Level"))
    {

        In_Cr = 1;
        Level_Num = 6;
        LoadAllAssets(Level_Num);
        UpdateAll();
        ShowGUI();
        isInLevel = 1;
        startTimer(TIMER_BLINK500, mseconds500);
        TimeUp = 0;
    }
}
