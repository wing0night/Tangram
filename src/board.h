/*
 * board.h
 * 七巧板的板。
 */

#ifndef BOARDGAME_BOARD_H
#define BOARDGAME_BOARD_H

#include "libgraphics.h"
#include "transform.h"
#include "utils.h"

/*每块板最多的边数。*/
#define BOARD_MAX_EDGE 4

/*
 * struct Board
 * 七巧板的板，结构体。
 * 成员：
 * - order：优先级，在板重叠的情况下，order大的板渲染在上方，
 *          且优先被点击。
 * - points：各个顶点的相对坐标，存好了就不用动了。
 * - point_cnt：一共有几个顶点。
 * - transform：存放该板的变形。（参见：变形，struct Transform）
 * - fill_color：板的填充色。
 * - outline_color：边框颜色。
 * - pen_size：边框粗细。
 * - _global_points_buffer：给计算函数用的，计算从相对坐标到绝对坐标的值。
 * 不要自己用上面这个！！
 */
typedef struct Board
{
    int order;
    Vector points[BOARD_MAX_EDGE]; // relevant position
    int point_cnt;
    Transform *transform;
    Transform *transform_l; // level的该板块相对位置信息
    string fill_color;
    string outline_color;
    string fill_color_l;
    string outline_color_l;
    int pen_size;
    Vector _global_points_buffer[BOARD_MAX_EDGE]; // global position
    Vector _global_points_buffer_l[BOARD_MAX_EDGE];
} Board;

/*
 * 创建一个新的Board对象。
 */
Board *MakeBoard(int order, const Vector points[], int point_cnt, string fill_color, string outline_color,
                 string fill_color_l, string outline_color_l, int pen_size, Transform *init_transform,
                 Transform *transform_l);
/*
 * 在屏幕上画出这个Board。
 */
void DrawBoard(Board *b);
/*
 * 在屏幕上擦除这个Board。
 */
void EraseBoard(Board *b);
/*
 * 判断点p是否在b内部。
 */
bool IsPointInBoard(Board *b, Vector p);
/*
 * 释放该Board内存。
 */
void FreeBoard(Board *b);
/*
 * 翻转Board，相对于相对坐标(0,y)
 */
void FlipBoard(Board *b);

void DrawBoard_Cr();

#endif // BOARDGAME_BOARD_H
