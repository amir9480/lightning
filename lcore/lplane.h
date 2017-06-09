#ifndef LPLANE_H
#define LPLANE_H
#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lmatrix.h"
#include "lvector3.h"
#include "lvector4.h"
LNAMESPACE_BEGIN

//forward declartion
class LBoundingBox;
class LBoundingSphere;

class LAPI LPlane
{
public:
    //! Create Default
    linline             LPlane();

    //! Create from a point and normal
    linline             LPlane(const LVector3& _point,const LVector3& _normal);

    //! Create from a normal and custom d
    linline             LPlane(const LVector3& _normal,const f32& _d);

    //! Create from three points . _point1 is same _point
    linline             LPlane(const LVector3& _point1,const LVector3& _point2,const LVector3& _point3);

    //! Create from a b c d
    linline             LPlane(const f32& _a,const f32& _b,const f32& _c,const f32& _d);

    //! Copy Constructor
    linline             LPlane(const LPlane& _other);


    //! Calculate D parameter of plane
    linline void        calcD(const LVector3& _point);

    //! Get Distance Between Vector3 and plane if was Negetive it's Means the point is in the back side of plane
    linline f32         getDistanceFrom(const LVector3& _point)const;

    //! Get Dot Product of Plane And another vector3
    linline f32         getDotProduct(const LVector3& _other)const;

    //! Get Dot Coord of Plane And another vector3
    linline f32         getDotCoord(const LVector3& _other)const;

    //! Get Normalized of this plane
    linline LPlane      getNormalized()const;

    //! Get Projected Point on Plane
    linline LVector3    getProjectedPoint(const LVector3& _point)const;

    //! Get Reflected Point based on Plane
    linline LVector3    getReflectedPoint(const LVector3& _point)const;

    //! Get Reflection Matrix from Plane
    linline LMatrix     getReflectionMatrix()const;

    //! returns true when point is in the back of plane . otherwise returns false
    linline bool        isBackSide(const LVector3& _point)const;

    //! returns true when point is in the front of plane . otherwise returns false
    linline bool        isFrontSide(const LVector3& _point)const;

    //! if plane intersects other AABB will returns true . other wise returns false
    bool                isIntersect(const LBoundingBox& _other)const;

    //! if plane intersects other Sphere will returns true . other wise returns false
    bool                isIntersect(const LBoundingSphere& _other)const;

    //! returns true when two point is in the same side of plane
    linline bool        isSameSide(const LVector3& _a,const LVector3& _b)const;

    //! normalize plane
    linline void        normalize();

    //! Set from a point and normal
    linline void        set(const LVector3& _point,const LVector3& _normal);

    //! Set from a normal and custom d
    linline void        set(const LVector3& _normal,const f32& _d);

    //! Set from three points . _point1 is same _point
    linline void        set(const LVector3& _point1,const LVector3& _point2,const LVector3& _point3);

    //! Set from a b c d
    linline void        set(const f32& _a,const f32& _b,const f32& _c,const f32& _d);

    //! Transform Plane Using Matrices
    linline void        transform(const LMatrix& _t);


    //! Compare Operators
    linline bool        operator==(const LPlane& _other)const;
    linline bool        operator!=(const LPlane& _other)const;

    //! Equale operator
    linline LPlane& operator =(const LPlane& _other);
public:
    union
    {
        struct
        {
            f32 a,b,c;
        };
        LVector3 mNormal;
    };
    f32 d;// a+b+c=d
};

LPlane::LPlane()
{
    mNormal=0.0f;
    d=0.0f;
}

LPlane::LPlane(const LVector3 &_point, const LVector3 &_normal)
{
    set(_point,_normal);
}

LPlane::LPlane(const LVector3 &_normal, const f32 &_d)
{
    set(_normal,_d);
}

LPlane::LPlane(const LVector3 &_point1, const LVector3 &_point2, const LVector3 &_point3)
{
    set(_point1,_point2,_point3);
}

LPlane::LPlane(const LPlane &_other)
{
    (*this)=(_other);
}

void LPlane::calcD(const LVector3 &_point)
{
    d= (mNormal.getDotProduct(_point));
}

f32 LPlane::getDistanceFrom(const LVector3 &_point) const
{
    return (mNormal.getDotProduct(_point))-d;
}

f32 LPlane::getDotProduct(const LVector3 &_other) const
{
    return mNormal.getDotProduct(_other);
}

f32 LPlane::getDotCoord(const LVector3 &_other) const
{
    return mNormal.getDotProduct(_other)-d;
}

LPlane LPlane::getNormalized() const
{
    LPlane out=(*this);
    out.normalize();
    return out;
}

LVector3 LPlane::getProjectedPoint(const LVector3 &_point) const
{
    LVector3 out=_point;
    out-=mNormal*getDistanceFrom(_point);
    return out;
}

LVector3 LPlane::getReflectedPoint(const LVector3 &_point) const
{
    LVector3 out=_point;
    out-=(mNormal*getDistanceFrom(_point)*2.0f);
    return out;
}

LMatrix LPlane::getReflectionMatrix() const
{
    // Adapted from DirectX documents
    LMatrix out;
    LPlane p=this->getNormalized();

    out.m11=-2.0f*p.a*p.a+1.0f;
    out.m12=-2.0f*p.b*p.a;
    out.m13=-2.0f*p.c*p.a;

    out.m21=-2.0f*p.a*p.b;
    out.m22=-2.0f*p.b*p.b+1.0f;
    out.m23=-2.0f*p.c*p.b;

    out.m31=-2.0f*p.a*p.c;
    out.m32=-2.0f*p.b*p.c;
    out.m33=-2.0f*p.c*p.c+1.0f;

    out.m41=-2.0f*p.a*p.d;
    out.m42=-2.0f*p.b*p.d;
    out.m43=-2.0f*p.c*p.d;

    return out;
}

bool LPlane::isFrontSide(const LVector3 &_point) const
{
    return (getDistanceFrom(_point)>=0.0f);
}



bool LPlane::isSameSide(const LVector3 &_a, const LVector3 &_b) const
{
    return (isFrontSide(_a)==isFrontSide(_b));
}

void LPlane::normalize()
{
    d/=mNormal.getLength();
    mNormal.normalize();
}

bool LPlane::isBackSide(const LVector3 &_point) const
{
    return (getDistanceFrom(_point)<0.0f);
}

void LPlane::set(const LVector3 &_point, const LVector3 &_normal)
{
    mNormal=_normal.getNormalized();
    calcD(_point);
}

void LPlane::set(const LVector3 &_normal, const f32 &_d)
{
    mNormal=_normal.getNormalized();
    d=_d;
}

void LPlane::set(const LVector3 &_point1, const LVector3 &_point2, const LVector3 &_point3)
{
    LVector3 m=_point1-_point2;
    LVector3 n=_point3-_point2;
    mNormal=(m.getCrossProduct(n)).getNormalized();
    calcD(_point2);
}

void LPlane::set(const f32 &_a, const f32 &_b, const f32 &_c, const f32 &_d)
{
    a=_a;
    b=_b;
    c=_c;
    d=_d;
}

void LPlane::transform(const LMatrix &_t)
{
    mNormal*=_t.getInverseTransposed();
}

bool LPlane::operator==(const LPlane& _other)const
{
    return (lCompareFloat(d,_other.d)&&mNormal==_other.mNormal);
}

bool LPlane::operator!=(const LPlane& _other)const
{
    return !((*this)==_other);
}

LPlane &LPlane::operator =(const LPlane &_other)
{
    a=_other.a;
    b=_other.b;
    c=_other.c;
    d=_other.d;
    return (*this);
}

LNAMESPACE_END
#endif // LPLANE_H
