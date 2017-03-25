#ifndef LBOUNDINGSPHERE_H
#define LBOUNDINGSPHERE_H
#include "ldefines.h"
#include "lmatrix.h"
#include "lvector3.h"

LNAMESPACE_BEGIN

class LBoundingSphere
{
public:
    linline                     LBoundingSphere();

    linline                     LBoundingSphere(const LVector3& _pos,const f32& _radius);

    linline                     LBoundingSphere(const LBoundingSphere& _other);

    //! Add an Internal Point in this Bounding Sphere
    linline void                add(const LVector3& _p);

    //! Get Merged copy of this with another
    linline LBoundingSphere     getMerged(const LBoundingSphere& _other)const;

    //! get Position
    linline LVector3            getPos() const;

    //! get Radius
    linline f32                 getRadius() const;

    //! Get Volume of this Sphere
    linline f32                 getVolume()const;

    //! Check is point inside sphere or not. if was returns true. otherwise returns false
    linline bool                isContain(const LVector3& _p)const;

    //! Check is all part of another sphere is inside or not. if was returns true otherwise returns false;
    linline bool                isContain(const LBoundingSphere& _b)const;

    //! Merge this with another Sphere
    linline void                merge(const LBoundingSphere& _other);

    //! set Function
    linline void                set(const LVector3& _pos,const f32& _radius);

    //! Set Position
    linline void                setPos(const LVector3 &pos);

    //! Set Radius
    linline void                setRadius(const f32 &radius);

    //! Copy Assign
    linline LBoundingSphere&    operator =(const LBoundingSphere& _other);

    //! Compare
    linline bool                operator==(const LBoundingSphere& _other)const;
    linline bool                operator!=(const LBoundingSphere& _other)const;
protected:
    LVector3 mPos;
    f32      mRadius;
};

f32 LBoundingSphere::getRadius() const
{
    return mRadius;
}

f32 LBoundingSphere::getVolume() const
{
    return mRadius*mRadius*mRadius*lPi*4.0f/3.0f;
}

bool LBoundingSphere::isContain(const LVector3 &_p) const
{
    return (mPos.getDistanceFrom(_p)<=mRadius);
}

bool LBoundingSphere::isContain(const LBoundingSphere &_b) const
{
    return (mPos.getDistanceFrom(_b.mPos)+_b.mRadius<=mRadius);
}

void LBoundingSphere::merge(const LBoundingSphere &_other)
{
    //TODO: Get Better Algorithm
    f32 dis=mPos.getDistanceFrom(_other.mPos)/2.0f;
    mPos=(mPos+_other.mPos)/2.0f;
    mRadius=dis+lMax(mRadius,_other.mRadius);
}

void LBoundingSphere::set(const LVector3 &_pos, const f32 &_radius)
{
    mPos=_pos;
    mRadius=_radius;
}

void LBoundingSphere::setRadius(const f32 &radius)
{
    mRadius = radius;
}

LBoundingSphere &LBoundingSphere::operator =(const LBoundingSphere &_other)
{
    mPos=_other.mPos;
    mRadius=_other.mRadius;
    return (*this);
}

bool LBoundingSphere::operator==(const LBoundingSphere &_other) const
{
    return(
                mPos==_other.mPos&&
                mRadius==_other.mRadius
          );
}

bool LBoundingSphere::operator!=(const LBoundingSphere &_other) const
{
    return !(*this==_other);
}

LBoundingSphere::LBoundingSphere()
{
    set(LVector3::zero,lInfinity);
}

LBoundingSphere::LBoundingSphere(const LVector3 &_pos, const f32 &_radius)
{
    set(_pos,_radius);
}

LBoundingSphere::LBoundingSphere(const LBoundingSphere &_other)
{
    (*this)=_other;
}

void LBoundingSphere::add(const LVector3 &_p)
{
    f32 _dis=mPos.getDistanceFrom(_p);
    if(_dis>mRadius)
        mRadius=_dis;
}

LBoundingSphere LBoundingSphere::getMerged(const LBoundingSphere &_other) const
{
    LBoundingSphere o=(*this);
    o.merge(_other);
    return o;
}

LVector3 LBoundingSphere::getPos() const
{
    return mPos;
}

void LBoundingSphere::setPos(const LVector3 &pos)
{
    mPos = pos;
}


LNAMESPACE_END

#endif // LBOUNDINGSPHERE_H
