/*
 * board.h
 * ���ɰ�İ塣
 */

#ifndef BOARDGAME_BOARD_H
#define BOARDGAME_BOARD_H

#include "libgraphics.h"
#include "transform.h"
#include "utils.h"

/*ÿ������ı�����*/
#define BOARD_MAX_EDGE 4

/*
 * struct Board
 * ���ɰ�İ壬�ṹ�塣
 * ��Ա��
 * - order�����ȼ����ڰ��ص�������£�order��İ���Ⱦ���Ϸ���
 *          �����ȱ������
 * - points�����������������꣬����˾Ͳ��ö��ˡ�
 * - point_cnt��һ���м������㡣
 * - transform����Ÿð�ı��Ρ����μ������Σ�struct Transform��
 * - fill_color��������ɫ��
 * - outline_color���߿���ɫ��
 * - pen_size���߿��ϸ��
 * - _global_points_buffer�������㺯���õģ������������굽���������ֵ��
 * ��Ҫ�Լ��������������
 */
typedef struct Board
{
    int order;
    Vector points[BOARD_MAX_EDGE]; // relevant position
    int point_cnt;
    Transform *transform;
    Transform *transform_l; // level�ĸð�����λ����Ϣ
    string fill_color;
    string outline_color;
    string fill_color_l;
    string outline_color_l;
    int pen_size;
    Vector _global_points_buffer[BOARD_MAX_EDGE]; // global position
    Vector _global_points_buffer_l[BOARD_MAX_EDGE];
} Board;

/*
 * ����һ���µ�Board����
 */
Board *MakeBoard(int order, const Vector points[], int point_cnt, string fill_color, string outline_color,
                 string fill_color_l, string outline_color_l, int pen_size, Transform *init_transform,
                 Transform *transform_l);
/*
 * ����Ļ�ϻ������Board��
 */
void DrawBoard(Board *b);
/*
 * ����Ļ�ϲ������Board��
 */
void EraseBoard(Board *b);
/*
 * �жϵ�p�Ƿ���b�ڲ���
 */
bool IsPointInBoard(Board *b, Vector p);
/*
 * �ͷŸ�Board�ڴ档
 */
void FreeBoard(Board *b);
/*
 * ��תBoard��������������(0,y)
 */
void FlipBoard(Board *b);

void DrawBoard_Cr();

#endif // BOARDGAME_BOARD_H
