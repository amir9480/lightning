#include "lboundingbox.h"
#include "lplane.h"
#include "lboundingsphere.h"

LNAMESPACE_BEGIN

bool LBoundingBox::isIntersect(const LPlane &_other) const
{
    bool a=_other.isFrontSide(mCorners[0]);
    return !(
                _other.isFrontSide(mCorners[1])==a&&
                _other.isFrontSide(mCorners[2])==a&&
                _other.isFrontSide(mCorners[3])==a&&
                _other.isFrontSide(mCorners[4])==a&&
                _other.isFrontSide(mCorners[5])==a&&
                _other.isFrontSide(mCorners[6])==a&&
                _other.isFrontSide(mCorners[7])==a
            );
}

bool LBoundingBox::isIntersect(const LBoundingSphere &_other) const
{
    LVector3 spos=_other.getPos();
    LVector3 cp;// closest point to sphere

    if(spos.x>=mMax.x)
        cp.x=mMax.x;
    else if(spos.x<=mMin.x)
        cp.x=mMin.x;

    if(spos.y>=mMax.y)
        cp.y=mMax.y;
    else if(spos.y<=mMin.y)
        cp.y=mMin.y;

    if(spos.z>=mMax.z)
        cp.z=mMax.z;
    else if(spos.z<=mMin.z)
        cp.z=mMin.z;

    return (cp.getDistanceFrom(spos)<=_other.getRadius());
}


LNAMESPACE_END


