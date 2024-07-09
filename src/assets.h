/*
 * assets.h
 * ������Դ��������ͺͺ���
 * ��Դ������õ���ģʽ��ֻ��һ����Դ����ʵ������ 
 */

#ifndef BOARDGAME_ASSETS_H
#define BOARDGAME_ASSETS_H

#include "board.h"
#include "libgraphics.h"

// ��������С��һ�����߿�塣 
#define BOARD_LIST_CNT 7

/*
 * struct Asset
 * ������Դ���� 
 */
typedef struct Asset
{
    // ������顣 
    Board *boards[BOARD_LIST_CNT];
} Asset;

typedef struct Asset_Level
{
	// �ؿ����顣
    Transform *boards[BOARD_LIST_CNT];
} Asset_Level;

Board *Get_Board_i(int i);

// �ж��ʲ��Ƿ���ء� 
bool IsAssetsLoaded();
// ���ص�i�ص���Դ�� 
void LoadAllAssets(int i);
// ��ȡ��ǰ��Դ���������� 
Asset *GetAssets();
// ��ȡ����p�µİ塣���û�У����ؿ�ָ�롣 
Board *GetSelectedBoard(Vector p);
// �ͷ���Դ�� 
void FreeAllAssets();
// չʾ���⡣ 
void ShowTitle(int i);

void LoadAllAssets_Cr();

static Asset *MakeAssets_Cr();

void LoadInitBoards(Asset *asset, int i);

#endif // BOARDGAME_ASSETS_H
