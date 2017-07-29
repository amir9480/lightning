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

bool LRect::operator==(const LRect &_other)
{
    return ( x==_other.x&&y==_other.y&&
             width==_other.width&&height==_other.height );
}

bool LRect::operator!=(const LRect &_other)
{
    return !(*this==_other);
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

bool LRectF::operator==(const LRectF &_other)
{
    return ( x==_other.x&&y==_other.y&&
          width==_other.width&&height==_other.height );
}

bool LRectF::operator!=(const LRectF &_other)
{
    return !(*this==_other);
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

bool LPoint::operator==(const LPoint &_other)
{
    return ( x==_other.x&&y==_other.y );
}

bool LPoint::operator!=(const LPoint &_other)
{
    return !(*this==_other);
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

bool LPointF::operator==(const LPointF &_other)
{
    return ( x==_other.x&&y==_other.y );
}

bool LPointF::operator!=(const LPointF &_other)
{
    return !(*this==_other);
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

bool LSize::operator==(const LSize &_other)
{
    return ( width==_other.width&&height==_other.height );
}

bool LSize::operator!=(const LSize &_other)
{
    return !(*this==_other);
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

bool LSizeF::operator==(const LSizeF &_other)
{
    return ( width==_other.width&&height==_other.height );
}

bool LSizeF::operator!=(const LSizeF &_other)
{
    return !(*this==_other);
}

LNAMESPACE_END
