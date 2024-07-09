/*
 * utils.h
 * 存放一些工具和数学函数。
 */

#ifndef BOARDGAME_UTILS_H
#define BOARDGAME_UTILS_H

#include <stddef.h>

/*内存分配函数。暂时使用malloc。*/
void *MemAlloc(size_t bytes);
/*内存释放函数。暂时使用free。*/
void MemFree(void *object);

/*
 * 二维向量，用来表示坐标。
 * 不要用MemAlloc给Vector分配堆内存！！
 * 不要用指针操作Vector！！
 * Vector要当值类型使用！！
 */
typedef struct Vector
{
    double x, y;
} Vector;

/*
 * 创建一个Vector来表示一个点的简便方法。
 * 例：Vector p = P(2, 3);
 */
#define P(x, y)                                                                                                        \
    (Vector)                                                                                                           \
    {                                                                                                                  \
        (x), (y)                                                                                                       \
    }
/*零坐标/零向量*/
#define ZERO_VECTOR (P(0.00, 0.00))

// Math functions

/*返回将v逆时针旋转degree度后的向量。*/
Vector VectorRotate(Vector v, double degree);
/*度数转化为弧度的函数。*/
double Deg2Rad(double degree);
/*返回a和b相加的结果。*/
Vector VectorAdd(Vector a, Vector b);
/*返回a和b相减的结果。*/
Vector VectorSub(Vector a, Vector b);
/*返回向量数乘结果。*/
Vector VectorScale(Vector v, double scale);
/*浮点数最小值*/
double Min(double x, double y);
/*浮点数最大值*/
double Max(double x, double y);

#endif // BOARDGAME_UTILS_H
