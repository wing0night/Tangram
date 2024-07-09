#include "transform.h"

void MoveObjectTo(Transform *t, Vector position)
{
    t->position.x = position.x;
    t->position.y = position.y;
}
void RotateObjectTo(Transform *t, double degree)
{
    t->rotation = degree;
}
void ScaleObjectTo(Transform *t, Vector scale)
{
    t->scale = scale;
}
Transform *MakeZeroTransform()
{
    return MakeTransform(P(0.0, 0.0), 0.0, P(1.0, 1.0));
}
Transform *MakeTransform(Vector position, double rotation, Vector scale)
{
    Transform *newTransform = MemAlloc(sizeof(Transform));
    newTransform->position = position;
    newTransform->rotation = rotation;
    newTransform->scale = scale;
    return newTransform;
}

void FreeTransform(Transform *t)
{
    MemFree(t);
}
