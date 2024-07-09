#include "utils.h"
#include <math.h>
#include <stdlib.h>

// �ڴ���亯���� 
void *MemAlloc(size_t bytes)
{
    return malloc(bytes);
}

// �ڴ��ͷź����� 
void MemFree(void *object)
{
    free(object);
}

// ������תһ���ĽǶȡ� 
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

// �����ӷ��� 
Vector VectorAdd(Vector a, Vector b)
{
    Vector r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

// ���������� 
Vector VectorSub(Vector a, Vector b)
{
    Vector r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

// �������š� 
Vector VectorScale(Vector v, double scale)
{
    Vector r;
    r = v;
    r.x *= scale;
    r.y *= scale;
    return r;
}

// �Ƕ�ת�ɻ��ȡ� 
double Deg2Rad(double degree)
{
    return degree * M_PI / 180.0;
}

// ��Сֵ�� 
double Min(double x, double y)
{
    if (x < y)
        return x;
    else
        return y;
}

// ���ֵ�� 
double Max(double x, double y)
{
    if (x > y)
        return x;
    else
        return y;
}
