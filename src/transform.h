/*
 * transform.h
 * ��¼�����λ����Ϣ������λ�á���ת�����š� 
 */

#ifndef BOARDGAME_TRANSFORM_H
#define BOARDGAME_TRANSFORM_H

#include "utils.h"

/*
 * struct Transform
 * ��¼�����λ����Ϣ������λ�á���ת�����š� 
 * - position �����ȫ������λ�á� 
 * - rotation ������ʱ����ת�ĽǶȡ���λΪ�ȡ� 
 * - scale ������x��y�᷽������š� 
 */
typedef struct Transform
{
    Vector position;
    double rotation; // in degree
    Vector scale;
} Transform;

// �������㡱���Ρ���������Ϊ(0,0)����תΪ0�ȣ�����Ϊ(1,1)������ 
Transform *MakeZeroTransform();
// �����µı���ʾ���� 
Transform *MakeTransform(Vector position, double rotation, Vector scale);
// �ͷű��ζ��� 
void FreeTransform(Transform *t);

// �����б��ε������Ƶ��µ�λ�á� 
// ʾ���� 
// MoveObjectTo(obj->transform, P(3, 3));
void MoveObjectTo(Transform *t, Vector position);
// �����б��ε�������ת���µĽǶȡ� 
void RotateObjectTo(Transform *t, double degree);
// �����б��ε��������ŵ��µı����� 
void ScaleObjectTo(Transform *t, Vector scale);

#endif // BOARDGAME_TRANSFORM_H
