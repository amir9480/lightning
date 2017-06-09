#include "lboundingbox.h"
#include "lplane.h"
#include "lboundingsphere.h"

LNAMESPACE_BEGIN

bool LBoundingBox::isIntersect(const LPlane &_other) const
{
    const LVector3* corners=getCorners();
    bool a=_other.isFrontSide(corners[0]);
    return !(
                _other.isFrontSide(corners[1])==a&&
                _other.isFrontSide(corners[2])==a&&
                _other.isFrontSide(corners[3])==a&&
                _other.isFrontSide(corners[4])==a&&
                _other.isFrontSide(corners[5])==a&&
                _other.isFrontSide(corners[6])==a&&
                _other.isFrontSide(corners[7])==a
            );
}

bool LBoundingBox::isIntersect(const LBoundingSphere &_other) const
{
    LVector3 spos=_other.getPos();
    LVector3 cp;// closest point to sphere
    LVector3 _max = mMax+mPos;
    LVector3 _min = mMin+mPos;
    if(spos.x>=_max.x)
        cp.x=_max.x;
    else if(spos.x<=_min.x)
        cp.x=_min.x;

    if(spos.y>=_max.y)
        cp.y=_max.y;
    else if(spos.y<=_min.y)
        cp.y=_min.y;

    if(spos.z>=_max.z)
        cp.z=_max.z;
    else if(spos.z<=_min.z)
        cp.z=_min.z;

    return (cp.getDistanceFrom(spos)<=_other.getRadius());
}


LNAMESPACE_END


