#ifndef LRAY_H
#define LRAY_H
#include "ldefines.h"
#include "lmathutility.h"
#include "lvector3.h"

#include "lboundingbox.h"
#include "lboundingsphere.h"
#include "lplane.h"
#include "ltriangle.h"

LNAMESPACE_BEGIN

class LRay
{
public:
    linline             LRay();

    linline             LRay(const LVector3& _pos,const LVector3& _dir);

    //! Get Ray Start Position
    linline LVector3    getPos() const;

    //! Get Ray Direction
    linline LVector3    getDir() const;

    //! Get Normalized Copy of this
    linline LRay        getNormalized()const;

    //! Get Point Along Ray
    linline LVector3    getPoint(const f32& _dis)const;

    //! Normalize Ray Direction
    linline void        normalize();

    //! Set Function
    linline void        set(const LVector3& _pos,const LVector3& _dir);

    //! Set Ray Direction
    linline void        setDir(const LVector3 &dir);

    //! Set Ray Start Position
    linline void        setPos(const LVector3 &pos);

protected:
    LVector3 mPos;// Ray Start Position
    LVector3 mDir;// Ray Direction
};

LRay::LRay()
{
    set(LVector3::zero,LVector3::forward);
}

LRay::LRay(const LVector3 &_pos, const LVector3 &_dir)
{
    set(_pos,_dir);
}

LVector3 LRay::getPos() const
{
    return mPos;
}

void LRay::setPos(const LVector3 &pos)
{
    mPos = pos;
}

LVector3 LRay::getDir() const
{
    return mDir;
}

LRay LRay::getNormalized() const
{
    LRay o=*this;
    o.normalize();
    return o;
}

LVector3 LRay::getPoint(const f32 &_dis) const
{
    return mPos+(mDir*_dis);
}

void LRay::normalize()
{
    return mDir.normalize();
}

void LRay::set(const LVector3 &_pos, const LVector3 &_dir)
{
    mPos=_pos;
    mDir=_dir;
}

void LRay::setDir(const LVector3 &dir)
{
    mDir = dir;
}


LNAMESPACE_END

#endif // LRAY_H
