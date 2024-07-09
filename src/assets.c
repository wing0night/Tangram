#include "assets.h"
#include "event_functions.h"
#include "level.h"
#include "utils.h"
#include <math.h>
#include <string.h>

// asset�ĵ�����ֻ�ܱ���ʼ��һ�Ρ�
static bool bAssetsLoaded = FALSE;
static bool bAssetsLoaded_Level = FALSE;
Asset *gAssets;
const double s = 1.414;

// Asset *gAssets_Cr;

extern int Level_Num;

extern Instruction;

extern int flag_Cr;

extern int Created;

extern int In_Cr;

// �����߿�岢�����Ƿŵ���ʼλ�á�
void LoadInitBoards(Asset *asset, int i);

//���˳�򣺺졢�ơ������̡���ɫ��Ʒ�졢��ɫ
extern Vector level_p[8][7];
extern double level_a[8][7];

// ���ʲ������߼�д�����
static Asset *MakeAssets(int p)
{
    // �߿��ȫ���ʼ����λ�á����ü����ġ�
    const Vector initPosition = P(5, 5);
    const Vector initPosition_l_1 = P(0, 0);
    const Vector initPosition_l_2 = P(20, 9);
    Vector initPosition_l;
    if (In_Cr == 1)
    {
        initPosition_l = initPosition_l_1;
    }
    else
    {
        initPosition_l = initPosition_l_2;
    }

    int i;
    Asset *asset = MemAlloc(sizeof(Asset));

    // Make boards
    // boards Ӧ����order��С��������
    LoadInitBoards(asset, p);
    // ����LoadInitBoards���߿�����ڡ�����ġ���������У������Ҫ������ȫ�����λ�ơ�
    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        asset->boards[i]->transform->position = VectorAdd(initPosition, asset->boards[i]->transform->position);
        asset->boards[i]->transform_l->position = VectorAdd(initPosition_l, asset->boards[i]->transform_l->position);
    }

    return asset;
}

// ���������ؿ����ء�
static Asset *MakeAssets_Cr()
{
    // �߿��ȫ���ʼ����λ�á����ü����ġ�
    const Vector initPosition = P(5, 5);
    const Vector initPosition_l = P(20, 9);

    int i;
    Asset *asset = MemAlloc(sizeof(Asset));
    // Load Levels
    // ...

    // Make boards
    // boards Ӧ����order��С��������
    LoadInitBoards(asset, 1);
    // ����LoadInitBoards���߿�����ڡ�����ġ���������У������Ҫ������ȫ�����λ�ơ�
    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        asset->boards[i]->transform->position = VectorAdd(initPosition, asset->boards[i]->transform->position);
        asset->boards[i]->transform_l->position = VectorAdd(initPosition_l, asset->boards[i]->transform_l->position);
    }

    return asset;
}

void ShowTitle(Level_Num)
{

    if (flag_Cr == 1)
    {
        textbox(1, 9, 17, 4, 2, "Create My Level!", 20);
        return;
    }
    else if (Created == 1)
    {
        textbox(1, 9, 17, 4, 2, "My Level", 20);
        return;
    }

    char str[5];
    char str1[10] = "Level";

    sprintf(str, "%d", Level_Num);

    strcat(str1, str);

    textbox(1, 9, 17, 4, 2, str1, 20);
}

// �����x,y�����µ�order���İ壻
// ���û�У�����NULL��
Board *GetSelectedBoard(Vector p)
{
    Asset *asset = GetAssets();
    Board *res = NULL;
    int i;
    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        if (IsPointInBoard(asset->boards[i], p))
        {
            // boardsӦ����order��С��������
            res = asset->boards[i];
        }
    }
    return res;
}

Board *Get_Board_i(int i)
{
    Asset *asset = GetAssets();
    Board *res = NULL;

    res = asset->boards[i - 1];

    return res;
}

// ��ʼ����ɺ�Ҫ�Ȱ����ǻ�һ�顣
static void DrawInitAssets(Asset *asset)
{
    int i;

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard_l(asset->boards[i]);
    }

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard(asset->boards[i]);
    }
}

static void DrawInitAssets_Cr(Asset *asset)
{
    int i;

    for (i = 0; i < BOARD_LIST_CNT; i++)
    {
        DrawBoard(asset->boards[i]);
    }
    DrawBoard_Cr();
}

static void ReleaseAssets(Asset *asset)
{
    MemFree(asset);
}

bool IsAssetsLoaded()
{
    return bAssetsLoaded;
}
void LoadAllAssets(int i)
{
    gAssets = MakeAssets(i);
    bAssetsLoaded = TRUE;
    DrawInitAssets(gAssets);
}

void LoadAllAssets_Cr()
{
    gAssets = MakeAssets_Cr();
    bAssetsLoaded = TRUE;
    if (Created)
    {
        DrawInitAssets(gAssets);
    }
    else
    {
        DrawInitAssets_Cr(gAssets);
    }
}

Asset *GetAssets()
{
    if (IsAssetsLoaded())
    {
        return gAssets;
    }
    else
    {
        return NULL;
    }
}

Asset *GetAssets_Cr()
{
    if (IsAssetsLoaded())
    {
        return gAssets;
    }
    else
    {
        return NULL;
    }
}

void FreeAllAssets()
{
    if (IsAssetsLoaded())
    {
        ReleaseAssets(gAssets);
        bAssetsLoaded = FALSE;
    }
}

void LoadInitBoards(Asset *asset, int i)
{
    // ��������������ĵ���
    // Load_level();
    const Vector bp1_2[] = {P(-4, 2), P(4, 2), P(0, -2)};
    asset->boards[0] =
        MakeBoard(1, bp1_2, 3, "Red", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(0, 2), 0, P(1, 1)),
                  MakeTransform(level_p[i - 1][0], level_a[i - 1][0], P(1, 1)));
    //�������MakeTransform�м�¼�˹ؿ��иð���λ����Ϣ
    // level_p[0][0]�ǵ�һ�ص�һ������λ��
    asset->boards[1] =
        MakeBoard(2, bp1_2, 3, "Yellow", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(2, 0), -90, P(1, 1)),
                  MakeTransform(level_p[i - 1][1], level_a[i - 1][1], P(1, 1)));

    const Vector bp3[] = {P(-2 * M_SQRT2, M_SQRT2), P(2 * M_SQRT2, M_SQRT2), P(0, -1 * M_SQRT2)};
    asset->boards[2] =
        MakeBoard(3, bp3, 3, "Blue", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(-3, -3), -45, P(1, 1)),
                  MakeTransform(level_p[i - 1][2], level_a[i - 1][2], P(1, 1)));

    const Vector bp4[] = {P(-2, 0), P(0, 2), P(2, 0), P(0, -2)};
    asset->boards[3] =
        MakeBoard(4, bp4, 4, "Green", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(-2, 0), 0, P(1, 1)),
                  MakeTransform(level_p[i - 1][3], level_a[i - 1][3], P(1, 1)));

    const Vector bp5[] = {P(0, M_SQRT2), P(2 * M_SQRT2, M_SQRT2), P(0, -1 * M_SQRT2), P(-2 * M_SQRT2, -1 * M_SQRT2)};
    asset->boards[4] =
        MakeBoard(5, bp5, 4, "Cyan", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(1, -3), -45, P(1, 1)),
                  MakeTransform(level_p[i - 1][4], level_a[i - 1][4], P(1, 1)));

    const Vector bp6_7[] = {P(-2, 1), P(2, 1), P(0, -1)};
    asset->boards[5] =
        MakeBoard(6, bp6_7, 3, "Magenta", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(0, -1), 180, P(1, 1)),
                  MakeTransform(level_p[i - 1][5], level_a[i - 1][5], P(1, 1)));
    asset->boards[6] =
        MakeBoard(7, bp6_7, 3, "Orange", "Black", "Light Gray", "Light Gray", 2, MakeTransform(P(-3, 2), 90, P(1, 1)),
                  MakeTransform(level_p[i - 1][6], level_a[i - 1][6], P(1, 1)));
}
