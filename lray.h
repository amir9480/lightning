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

class LAPI LRay
{
public:
    linline             LRay();

    linline             LRay(const LVector3& _pos,const LVector3& _dir);

    linline             LRay(const LRay& _other);

    //! Get Ray Start Position
    linline LVector3    getPos() const;

    //! Get Ray Direction
    linline LVector3    getDir() const;

    //! Get Normalized Copy of this
    linline LRay        getNormalized()const;

    //! Get Point Along Ray
    linline LVector3    getPoint(const f32& _dis)const;

    //! is Intersect with another plane. if there is no intersection returns NaN . other wise returns d
    //! that is distance between start point and intersection point. to check you can use \fn isnan
    linline f32         isIntersect(const LPlane& _other)const;

    //! is Intersect with another Sphere. if there is no intersection returns NaN . other wise returns d
    //! that is distance between start point and intersection point. to check you can use \fn isnan
    linline f32         isIntersect(const LBoundingSphere& _other)const;

    //! is Intersect with another Triangle. if there is no intersection returns NaN . other wise returns d
    //! that is distance between start point and intersection point. to check you can use \fn isnan
    linline f32         isIntersect(const LTriangle& _other)const;

    //! Normalize Ray Direction
    linline void        normalize();

    //! Set Function
    linline void        set(const LVector3& _pos,const LVector3& _dir);

    //! Set Ray Direction
    linline void        setDir(const LVector3 &dir);

    //! Set Ray Start Position
    linline void        setPos(const LVector3 &pos);


    //! Copy
    linline LRay&       operator=(const LRay& _other);

    //! Compare
    linline bool        operator==(const LRay& _other)const;
    linline bool        operator!=(const LRay& _other)const;

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

LRay::LRay(const LRay &_other)
{
    (*this)=_other;
}

LVector3 LRay::getPos() const
{
    return mPos;
}

void LRay::setPos(const LVector3 &pos)
{
    mPos = pos;
}

LRay &LRay::operator=(const LRay &_other)
{
    mDir=_other.mDir;
    mPos=_other.mPos;
    return (*this);
}

bool LRay::operator==(const LRay &_other) const
{
    return (
                mDir==_other.mDir&&
                mPos==_other.mPos
           );
}

bool LRay::operator!=(const LRay &_other) const
{
    return !((*this)==_other);
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

f32 LRay::isIntersect(const LPlane& _other) const
{
    // Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    f32 dir_dot_norm=mDir.getDotProduct(_other.mNormal);
    if(dir_dot_norm==0.0f)
        return lNaN;// there are no intersection
    return (_other.d-mPos.getDotProduct(_other.mNormal))/dir_dot_norm;
}

f32 LRay::isIntersect(const LBoundingSphere &_other) const
{
    // Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    LVector3 e=_other.getPos()-mPos;
    f32 a = e.getDotProduct(mDir);
    f32 f = _other.getRadius()*_other.getRadius()-e.getDotProduct(e)+a*a;
    if(f<0.0f)
        return lNaN;
    return a-lSqrt(f);
}

f32 LRay::isIntersect(const LTriangle &_other) const
{
    // Adapted from http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
    LVector3 h,s,q;
    f32 a,f,u,v,t;
    h=mDir.getCrossProduct(-_other.e2);
    a=_other.e3.getDotProduct(h);
    if(lCompareFloat(a,0.0f))
        return lNaN;
    f=1.0f/a;
    s=mPos-_other.v1;
    u=f*s.getDotProduct(h);
    if(u>1.0f||u<0.0f)
        return lNaN;
    q=s.getCrossProduct(_other.e3);
    v=f*q.getDotProduct(mDir);
    if(v<0.0f||u+v>1.0f)
        return lNaN;
    t=f*q.getDotProduct(-_other.e2);
    if(t<0.0001f)
        return lNaN;
    return t;
}

void LRay::normalize()
{
    mDir.normalize();
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
