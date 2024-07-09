/*
 * transform.h
 * 记录物体的位置信息，包括位置、旋转和缩放。 
 */

#ifndef BOARDGAME_TRANSFORM_H
#define BOARDGAME_TRANSFORM_H

#include "utils.h"

/*
 * struct Transform
 * 记录物体的位置信息，包括位置、旋转和缩放。 
 * - position 物体的全局坐标位置。 
 * - rotation 物体逆时针旋转的角度。单位为度。 
 * - scale 物体沿x，y轴方向的缩放。 
 */
typedef struct Transform
{
    Vector position;
    double rotation; // in degree
    Vector scale;
} Transform;

// 创建“零”变形。其中坐标为(0,0)，旋转为0度，缩放为(1,1)（倍） 
Transform *MakeZeroTransform();
// 创建新的变形示例。 
Transform *MakeTransform(Vector position, double rotation, Vector scale);
// 释放变形对象。 
void FreeTransform(Transform *t);

// 将含有变形的物体移到新的位置。 
// 示例： 
// MoveObjectTo(obj->transform, P(3, 3));
void MoveObjectTo(Transform *t, Vector position);
// 将含有变形的物体旋转到新的角度。 
void RotateObjectTo(Transform *t, double degree);
// 将含有变形的物体缩放的新的倍数。 
void ScaleObjectTo(Transform *t, Vector scale);

#endif // BOARDGAME_TRANSFORM_H
