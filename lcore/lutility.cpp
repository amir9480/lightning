#include "lutility.h"

LNAMESPACE_BEGIN

LRect::LRect()
{
    x=0;
    y=0;
    width=0;
    height=0;
}

LRect::LRect(int _x, int _y, int _width, int _height)
{
    x=_x;
    y=_y;
    width=_width;
    height=_height;
}

LRectF::LRectF()
{
    x=0;
    y=0;
    width=0;
    height=0;
}

LRectF::LRectF(float _x, float _y, float _width, float _height)
{
    x=_x;
    y=_y;
    width=_width;
    height=_height;
}

LPoint::LPoint()
{
    x=0;
    y=0;
}

LPoint::LPoint(int _x, int _y)
{
    x=_x;
    y=_y;
}


LPointF::LPointF()
{
    x=0;
    y=0;
}

LPointF::LPointF(float _x, float _y)
{
    x=_x;
    y=_y;
}

LSize::LSize()
{
    width=0;
    height=0;
}

LSize::LSize(int _width, int _height)
{
    width=_width;
    height=_height;
}

LSizeF::LSizeF()
{
    width=0;
    height=0;
}

LSizeF::LSizeF(float _width, float _height)
{
    width=_width;
    height=_height;
}

LNAMESPACE_END
