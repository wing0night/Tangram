#include "board.h"
#include "libgraphics.h"
#include "utils.h"

// 绘制板的外轮廓。
static void DrawBoardOutline(Board *b);
static void DrawBoardOutline_l(Board *b);
// 计算从相对坐标到绝对坐标的值。
static void CalcGlobalPoints(Board *b);

void FlipBoard(Board *b)
{
    int i;
    for (i = 0; i < b->point_cnt; i++)
    {
        b->points[i].y *= -1;
    }
}

void EraseBoard(Board *b)
{
    SetEraseMode(TRUE);
    DrawBoard(b);
    SetEraseMode(FALSE);
}

void DrawBoard(Board *b)
{
    // Fill the shape
    SetPenColor(b->fill_color);
    StartFilledRegion(1);
    DrawBoardOutline(b);
    EndFilledRegion();

    // Draw outline
    SetPenColor(b->outline_color);
    SetPenSize(b->pen_size);
    DrawBoardOutline(b);
}

void DrawBoard_l(Board *b)
{
    // Fill the shape
    SetPenColor(b->fill_color_l);
    StartFilledRegion(1);
    DrawBoardOutline_l(b);
    EndFilledRegion();

    SetPenColor(b->outline_color_l);
    SetPenSize(b->pen_size);
    DrawBoardOutline_l(b);
}

void DrawBoard_Cr()
{
    SetPenColor("Blue");
    SetPenSize(2);
    MovePen(15, 19);
    DrawLine(16, 0);
    DrawLine(0, -18);
    DrawLine(-16, 0);
    DrawLine(0, 18);
}

static void CalcGlobalPoints(Board *b)
{
    int i;
    for (i = 0; i < b->point_cnt; i++)
    {
        Vector tv = b->points[i];
        tv = VectorRotate(tv, b->transform->rotation);
        tv.x *= b->transform->scale.x;
        tv.y *= b->transform->scale.y;
        tv = VectorAdd(tv, b->transform->position);
        b->_global_points_buffer[i] = tv;
    }
}

static void CalcGlobalPoints_l(Board *b)
{
    int i;
    for (i = 0; i < b->point_cnt; i++)
    {
        Vector tv = b->points[i];
        tv = VectorRotate(tv, b->transform_l->rotation);
        tv.x *= b->transform_l->scale.x;
        tv.y *= b->transform_l->scale.y;
        tv = VectorAdd(tv, b->transform_l->position);
        b->_global_points_buffer_l[i] = tv;
    }
}

bool IsPointInBoard(Board *b, Vector p)
{
    // 使用几何定理：过一个点作射线，若射线与多边形交点个数为偶数，
	// 则它在多边形外；如果交点个数为奇数，则它在多边形内。
    int cross = 0, i;
    Vector cv, nv;
    CalcGlobalPoints(b);
    for (i = 0; i < b->point_cnt; i++)
    {
        cv = b->_global_points_buffer[i];
        nv = b->_global_points_buffer[(i + 1) % b->point_cnt];

        if (cv.y == nv.y)
        {
            continue;
        }
        if (p.y < Min(cv.y, nv.y))
        {
            continue;
        }
        if (p.y > Max(cv.y, nv.y))
        {
            continue;
        }

        double x = (p.y - cv.y) * (nv.x - cv.x) / (nv.y - cv.y) + cv.x;
        if (x > p.x)
        {
            cross++;
        }
    }

    if ((cross % 2) == 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Board *MakeBoard(int order, const Vector points[], int point_cnt, string fill_color, string outline_color,
                 string fill_color_l, string outline_color_l, int pen_size, Transform *init_transform,
                 Transform *transform_l)
{
    Board *newBoard = MemAlloc(sizeof(Board));
    int i;
    for (i = 0; i < point_cnt; i++)
    {
        newBoard->points[i] = points[i];
    }

    newBoard->point_cnt = point_cnt;
    newBoard->transform = init_transform;
    newBoard->fill_color = fill_color;
    newBoard->outline_color = outline_color;
    newBoard->fill_color_l = fill_color_l;
    newBoard->outline_color_l = outline_color_l;
    newBoard->pen_size = pen_size;
    newBoard->order = order;
    newBoard->transform_l = transform_l;
    return newBoard;
}

void FreeBoard(Board *b)
{
    FreeTransform(b->transform);
    MemFree(b);
}

static void DrawBoardOutline(Board *b)
{
    int i;

    CalcGlobalPoints(b);

    // current x, y
    double cx = b->_global_points_buffer[0].x, cy = b->_global_points_buffer[0].y;

    // next x, y
    double nx, ny;

    MovePen(cx, cy);
    // Draw each line
    for (i = 0; i < b->point_cnt; i++)
    {
        nx = b->_global_points_buffer[(i + 1) % b->point_cnt].x;
        ny = b->_global_points_buffer[(i + 1) % b->point_cnt].y;
        DrawLine(nx - cx, ny - cy);
        cx = nx;
        cy = ny;
    }
}

static void DrawBoardOutline_l(Board *b)
{
    int i;

    CalcGlobalPoints_l(b);
    // current x, y

    double cx_l = b->_global_points_buffer_l[0].x, cy_l = b->_global_points_buffer_l[0].y;
    // next x, y

    double nx_l, ny_l;

    MovePen(cx_l, cy_l);
    // Draw each line（关卡）
    for (i = 0; i < b->point_cnt; i++)
    {
        nx_l = b->_global_points_buffer_l[(i + 1) % b->point_cnt].x;
        ny_l = b->_global_points_buffer_l[(i + 1) % b->point_cnt].y;
        DrawLine(nx_l - cx_l, ny_l - cy_l);
        cx_l = nx_l;
        cy_l = ny_l;
    }
}
