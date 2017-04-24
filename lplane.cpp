#include "lplane.h"
#include "lboundingbox.h"
#include "lboundingsphere.h"
LNAMESPACE_BEGIN

bool LPlane::isIntersect(const LBoundingBox &_other) const
{
    return _other.isIntersect(*this);
}

bool LPlane::isIntersect(const LBoundingSphere &_other) const
{
    return _other.isIntersect(*this);
}

LNAMESPACE_END



