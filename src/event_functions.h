/*
 * event_functions.h
 * 存放事件函数。
 */

#ifndef BOARDGAME_EVENT_FUNCTIONS_H
#define BOARDGAME_EVENT_FUNCTIONS_H

// 对所有在屏幕上的物体及背景进行更新操作，即全部重绘。
void UpdateAll();

// 鼠标事件回调函数。
void MyMouseEvent(int x, int y, int button, int event);

void TimerEventProcess();

void UpdateAll_LevelSelect();

static void ShowGUI();

void ShowGUI_LevelSelect();
void ShowGUI_LevelSelect_Plus();

void UpdateAll_Cr();

void ShowGUI_Plus();

#endif // BOARDGAME_EVENT_FUNCTIONS_H
