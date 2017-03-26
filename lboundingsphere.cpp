#include "lboundingsphere.h"
#include "lboundingbox.h"
#include "lplane.h"
LNAMESPACE_BEGIN

bool LBoundingSphere::isIntersect(const LPlane &_other) const
{
    if(lAbs(_other.getDistanceFrom(mPos))<=mRadius)
        return true;
    return false;
}

bool LBoundingSphere::isIntersect(const LBoundingBox &_other) const
{
    return _other.isIntersect(*this);
}

LNAMESPACE_END

