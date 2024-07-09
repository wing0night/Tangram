/*
 * assets.h
 * 负责资源管理的类型和函数
 * 资源管理采用单例模式，只有一个资源对象被实例化。 
 */

#ifndef BOARDGAME_ASSETS_H
#define BOARDGAME_ASSETS_H

#include "board.h"
#include "libgraphics.h"

// 板的数组大小，一共有七块板。 
#define BOARD_LIST_CNT 7

/*
 * struct Asset
 * 负责资源管理。 
 */
typedef struct Asset
{
    // 板的数组。 
    Board *boards[BOARD_LIST_CNT];
} Asset;

typedef struct Asset_Level
{
	// 关卡数组。
    Transform *boards[BOARD_LIST_CNT];
} Asset_Level;

Board *Get_Board_i(int i);

// 判断资产是否加载。 
bool IsAssetsLoaded();
// 加载第i关的资源。 
void LoadAllAssets(int i);
// 获取当前资源（单例）。 
Asset *GetAssets();
// 获取坐标p下的板。如果没有，返回空指针。 
Board *GetSelectedBoard(Vector p);
// 释放资源。 
void FreeAllAssets();
// 展示标题。 
void ShowTitle(int i);

void LoadAllAssets_Cr();

static Asset *MakeAssets_Cr();

void LoadInitBoards(Asset *asset, int i);

#endif // BOARDGAME_ASSETS_H
