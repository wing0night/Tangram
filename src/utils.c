#include "utils.h"
#include <math.h>
#include <stdlib.h>

// 内存分配函数。 
void *MemAlloc(size_t bytes)
{
    return malloc(bytes);
}

// 内存释放函数。 
void MemFree(void *object)
{
    free(object);
}

// 向量旋转一定的角度。 
Vector VectorRotate(Vector v, double degree)
{
    double t = Deg2Rad(degree);
    double sin_t = sin(t);
    double cos_t = cos(t);
    Vector r;
    r.x = v.x * cos_t - v.y * sin_t;
    r.y = v.x * sin_t + v.y * cos_t;
    return r;
}

// 向量加法。 
Vector VectorAdd(Vector a, Vector b)
{
    Vector r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

// 向量减法。 
Vector VectorSub(Vector a, Vector b)
{
    Vector r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

// 向量缩放。 
Vector VectorScale(Vector v, double scale)
{
    Vector r;
    r = v;
    r.x *= scale;
    r.y *= scale;
    return r;
}

// 角度转成弧度。 
double Deg2Rad(double degree)
{
    return degree * M_PI / 180.0;
}

// 最小值。 
double Min(double x, double y)
{
    if (x < y)
        return x;
    else
        return y;
}

// 最大值。 
double Max(double x, double y)
{
    if (x > y)
        return x;
    else
        return y;
}
