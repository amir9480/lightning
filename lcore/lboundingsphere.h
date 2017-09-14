#ifndef LBOUNDINGSPHERE_H
#define LBOUNDINGSPHERE_H
#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmatrix.h"
#include "lvector3.h"

LNAMESPACE_BEGIN

// forward declartion
class LBoundingBox;
class LPlane;

/*!
 * \ingroup Math
 *
 * \en
 * \brief Bounding Sphere
 * \details This class is for Bounding Sphere and using for intersections and visability determinate
 * \enden
 *
 */
class LAPI LBoundingSphere
{
public:
    //! Default constructor
    linline                     LBoundingSphere();

    //! Constructor with center point and radius
    linline                     LBoundingSphere(const LVector3& _pos, const f32& _radius);
    // Copy constructor
    linline                     LBoundingSphere(const LBoundingSphere& _other);

    //! Add an internal point in this bounding sphere
    linline void                add(const LVector3& _p);

    //! Get merged copy of this with another sphere
    linline LBoundingSphere     getMerged(const LBoundingSphere& _other)const;

    //! Get center position
    linline LVector3            getPos() const;

    //! Get sphere radius
    linline f32                 getRadius() const;

    //! Get transformed copy of this
    linline LBoundingSphere     getTransformed(const LMatrix& _m)const;

    //! Get volume of sphere
    linline f32                 getVolume()const;

    //! Check is point inside sphere or not, if was returns true.
    linline bool                isContain(const LVector3& _p)const;

    //! Check is all part of another sphere is inside or not. if was returns true
    linline bool                isContain(const LBoundingSphere& _b)const;

    //! if Sphere intersects other plane will returns true . other wise returns false
    bool                        isIntersect(const LPlane& _other)const;

    //! if Sphere intersects other Box will returns true . other wise returns false
    bool                        isIntersect(const LBoundingBox& _other)const;

    //! BoundingSphere-BoundingSphere Intersection Check
    linline bool                isIntersect(const LBoundingSphere& _other)const;

    //! Merge this with another sphere
    linline void                merge(const LBoundingSphere& _other);

    //! Set function
    linline void                set(const LVector3& _pos,const f32& _radius);

    //! Set center position
    linline void                setPos(const LVector3 &pos);

    //! Set radius function
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

/*!
 * \en
 * \brief Get sphere radius
 * \enden
 *
 */
f32 LBoundingSphere::getRadius() const
{
    return mRadius;
}

/*!
 * \en
 * \brief Get transformed copy of this
 * \enden
 *
 * \sa transform
 */
LBoundingSphere LBoundingSphere::getTransformed(const LMatrix &_m) const
{
    LBoundingSphere o=*this;
    o.transform(_m);
    return o;
}

/*!
 * \en
 * \brief Get volume of sphere
 * \enden
 *
 */
f32 LBoundingSphere::getVolume() const
{
    return mRadius*mRadius*mRadius*lPi*(1.333333333333333f/* 4/3 */);
}

/*!
 * \en
 * \brief Check is point inside sphere or not, if was returns true.
 * \enden
 *
 */
bool LBoundingSphere::isContain(const LVector3 &_p) const
{
    return (mPos.getDistanceFrom(_p)<=mRadius);
}

/*!
 * \en
 * \brief Check is all part of another sphere is inside or not. if was returns true
 * \enden
 *
 */
bool LBoundingSphere::isContain(const LBoundingSphere &_b) const
{
    return (mPos.getDistanceFrom(_b.mPos)+_b.mRadius<=mRadius);
}

/*!
 * \en
 * \brief  BoundingSphere-BoundingSphere Intersection Check
 * \enden
 *
 */
bool LBoundingSphere::isIntersect(const LBoundingSphere &_other) const
{
    return (mPos.getDistanceFrom(_other.mPos)<=mRadius+_other.mRadius);
}

/*!
 * \en
 * \brief  Merge this with another sphere
 * \enden
 *
 * \sa getMerged
 */
void LBoundingSphere::merge(const LBoundingSphere &_other)
{
    //TODO: Get Better Algorithm
    f32 dis=mPos.getDistanceFrom(_other.mPos)*0.5f;
    mPos=(mPos+_other.mPos)*0.5f;
    mRadius=dis+lMax(mRadius,_other.mRadius);
}

/*!
 * \en
 * \brief  Set function
 * \param _pos  Sphere center point
 * \param _radius Sphere radius
 * \enden
 *
 * \sa getMerged
 */
void LBoundingSphere::set(const LVector3 &_pos, const f32 &_radius)
{
    mPos=_pos;
    mRadius=_radius;
}

/*!
 * \en
 * \brief  Set radius function
 * \enden
 *
 */
void LBoundingSphere::setRadius(const f32 &radius)
{
    mRadius = radius;
}

/*!
 * \en
 * \brief  transform this sphere
 * \enden
 *
 * \sa getTransformed
 */
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

/*!
 * \en
 * \brief Default constructor with infinity radius
 * \enden
 *
 */
LBoundingSphere::LBoundingSphere()
{
    set(LVector3::zero,lInfinity);
}

/*!
 * \en
 * \brief Constructor with center point and radius
 * \param _pos Center point
 * \param _radius Radius of sphere
 * \enden
 *
 * \sa set(const LVector3& _pos,const f32& _radius)
 */
LBoundingSphere::LBoundingSphere(const LVector3 &_pos, const f32 &_radius)
{
    set(_pos,_radius);
}

LBoundingSphere::LBoundingSphere(const LBoundingSphere &_other)
{
    (*this)=_other;
}

/*!
 * \en
 * \brief Add an internal point in this bounding sphere
 * \enden
 *
 */
void LBoundingSphere::add(const LVector3 &_p)
{
    f32 _dis=mPos.getDistanceFrom(_p);
    if(_dis>mRadius)
        mRadius=_dis;
}

/*!
 * \en
 * \brief Get merged copy of this with another sphere
 * \enden
 *
 * \sa merge
 */
LBoundingSphere LBoundingSphere::getMerged(const LBoundingSphere &_other) const
{
    LBoundingSphere o=(*this);
    o.merge(_other);
    return o;
}

/*!
 * \en
 * \brief Get center position
 * \enden
 *
 * \sa setPos
 */
LVector3 LBoundingSphere::getPos() const
{
    return mPos;
}

/*!
 * \en
 * \brief Set center position
 * \enden
 *
 * \sa getPos
 */
void LBoundingSphere::setPos(const LVector3 &pos)
{
    mPos = pos;
}


LNAMESPACE_END

#endif // LBOUNDINGSPHERE_H
