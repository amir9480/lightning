#ifndef LBOUNDINGSPHERE_H
#define LBOUNDINGSPHERE_H
#include "lcore.h"
#include "lmatrix.h"
#include "lvector3.h"

LNAMESPACE_BEGIN

// forward declartion
class LBoundingBox;
class LPlane;

class LAPI LBoundingSphere
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

    //! Get Transformed Copy of this
    linline LBoundingSphere     getTransformed(const LMatrix& _m)const;

    //! Get Volume of this Sphere
    linline f32                 getVolume()const;

    //! Check is point inside sphere or not. if was returns true. otherwise returns false
    linline bool                isContain(const LVector3& _p)const;

    //! Check is all part of another sphere is inside or not. if was returns true otherwise returns false;
    linline bool                isContain(const LBoundingSphere& _b)const;

    //! if Sphere intersects other plane will returns true . other wise returns false
    bool                        isIntersect(const LPlane& _other)const;

    //! if Sphere intersects other Box will returns true . other wise returns false
    bool                        isIntersect(const LBoundingBox& _other)const;

    //! if Sphere intersects other Box will returns true . other wise returns false
    linline bool                isIntersect(const LBoundingSphere& _other)const;

    //! Merge this with another Sphere
    linline void                merge(const LBoundingSphere& _other);

    //! set Function
    linline void                set(const LVector3& _pos,const f32& _radius);

    //! Set Position
    linline void                setPos(const LVector3 &pos);

    //! Set Radius
    linline void                setRadius(const f32 &radius);

    //! Transform this sphere using Transformatrion Matrix
    linline void                transform(const LMatrix& _m);


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

LBoundingSphere LBoundingSphere::getTransformed(const LMatrix &_m) const
{
    LBoundingSphere o=*this;
    o.transform(_m);
    return o;
}

f32 LBoundingSphere::getVolume() const
{
    return mRadius*mRadius*mRadius*lPi*(1.333333333333333f/* 4/3 */);
}

bool LBoundingSphere::isContain(const LVector3 &_p) const
{
    return (mPos.getDistanceFrom(_p)<=mRadius);
}

bool LBoundingSphere::isContain(const LBoundingSphere &_b) const
{
    return (mPos.getDistanceFrom(_b.mPos)+_b.mRadius<=mRadius);
}

bool LBoundingSphere::isIntersect(const LBoundingSphere &_other) const
{
    return (mPos.getDistanceFrom(_other.mPos)<=mRadius+_other.mRadius);
}

void LBoundingSphere::merge(const LBoundingSphere &_other)
{
    //TODO: Get Better Algorithm
    f32 dis=mPos.getDistanceFrom(_other.mPos)*0.5f;
    mPos=(mPos+_other.mPos)*0.5f;
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

void LBoundingSphere::transform(const LMatrix &_m)
{
    mPos*=_m;
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
