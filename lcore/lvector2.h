#ifndef LVECTOR2_H
#define LVECTOR2_H

#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

class LAPI LVector2
{
public:
    //! Default constructor
    linline                 LVector2();

    //! constructor will set all parameter to _scaler
    linline                 LVector2(const f32& _scaler);

    //! constructor with  3 first values
    linline                 LVector2(const f32& _x,const f32& _y);

    //! constructor with pointer (to 3D array)
    linline                 LVector2(const f32* _a);

    //! Copy Constructor
    linline                 LVector2(const LVector2& _a);

    //! Get Angel Between two axis
    static linline  f32     angle(const LVector2& _a, const LVector2& _b);

    //! Access to vector parameter  0=x , 1=y , 2=z
    linline f32&            at(u32 _i);
    linline f32             at(u32 _i)const;

    //! Get Distance Between two point
    static linline  f32     distance(const LVector2& _a, const LVector2& _b);

    //! Get _a (dot) _b
    static linline f32      dotProduct(const LVector2& _a,const LVector2& _b);

    //! Get Angel of this to _other
    linline f32             getAngelFrom(const LVector2& _other)const;

    //! Get Distance of this to _other
    linline f32             getDistanceFrom(const LVector2& _other)const;

    //! Get this (dot) _other
    linline f32             getDotProduct(const LVector2& _other)const;

    //! Get Length of Vector
    linline f32             getLength()const;

    //! Get Normalized Copy of this. if Vector isn't normalizable , returns LVector2::zero
    linline LVector2        getNormalized()const;

    //! Get Refelcted Copy of this
    linline LVector2        getReflected(const LVector2& _n)const;

    //! Get Squared Length
    linline f32             getSqauredLength()const;

    //! Get Sqaured Distance of this to _other
    linline f32             getSqauredDistanceFrom(const LVector2& _other)const;

    //! Checkout this vector is able to normalize
    linline bool            isNormalizable()const;

    //! Checkout is this a unit vector
    linline bool            isNormalized()const;

    //! Lerp Between two point
    static linline LVector2 lerp(const LVector2& _a,const LVector2& _b,const f64& _p);

    //! Normalize Vector
    linline bool            normalize();

    //! Reflect the vector
    linline void            reflect(const LVector2& _n);

    //! set functions just like constructors
    linline void            set(const f32& _scaler);

    linline void            set(const f32& _x,const f32& _y);

    linline void            set(const f32* _a);

    //! Change Length of this
    linline void            setLength(const f32& _l);

    //! Get Squared Distance Between two point
    static linline  f32     squaredDistance(const LVector2& _a, const LVector2& _b);

    //! Convert this to translation Matrix
    linline LMatrix         toTranslationMatrix()const;


    //! Access to vector parameter just like at
    linline f32&            operator[](u32 _i);
    linline f32&            operator()(u32 _i);
    linline f32             operator[](u32 _i)const;
    linline f32             operator()(u32 _i)const;

    //! Copy
    linline LVector2&       operator=(const LVector2& _a);
    linline LVector2&       operator=(const f32& _a);

    //! Multiply . IMPORTANT NOTE : this IS NOT crossproduct or dotproduct
    linline LVector2        operator*(const LVector2& _other)const;
    linline LVector2&       operator*=(const LVector2& _other);
    linline LVector2        operator*(const f32& _scaler)const;
    linline LVector2&       operator*=(const f32& _scaler);
    friend linline LVector2 operator*(const f32 &_a, const LVector2 &_b);
    linline LVector2        operator*(const LMatrix& _other)const;
    linline LVector2&       operator*=(const LMatrix& _other);

    //! Division
    linline LVector2        operator/(const LVector2& _other)const;
    linline LVector2&       operator/=(const LVector2& _other);
    linline LVector2        operator/(const f32& _scaler)const;
    linline LVector2&       operator/=(const f32& _scaler);
    friend linline LVector2 operator/(const f32 &_a, const LVector2 &_b);

    //! Negetive and Positive sign
    linline LVector2        operator+()const;
    linline LVector2        operator-()const;

    //! Addition
    linline LVector2        operator+(const LVector2& _other)const;
    linline LVector2&       operator+=(const LVector2& _other);
    friend linline LVector2 operator+(const f32 &_a, const LVector2 &_b);

    //! Sub
    linline LVector2        operator-(const LVector2& _other)const;
    linline LVector2&       operator-=(const LVector2& _other);
    friend linline LVector2 operator-(const f32 &_a, const LVector2 &_b);

    //! Compare
    linline bool            operator==(const LVector2& _other)const;
    linline bool            operator!=(const LVector2& _other)const;

    const static LVector2   up;
    const static LVector2   down;
    const static LVector2   left;
    const static LVector2   right;
    const static LVector2   zero;
    const static LVector2   one;

public:
    union
    {
        struct
        {
            f32 x,y;
        };
        f32 m[2];
    };
};


LVector2::LVector2():
    x(0.0f),
    y(0.0f)
{

}

LVector2::LVector2(const f32 &_scaler):
    x(_scaler),
    y(_scaler)
{

}

LVector2::LVector2(const f32 &_x, const f32 &_y):
    x(_x),
    y(_y)
{

}

LVector2::LVector2(const f32 *_a):
    x(_a[0]),
    y(_a[1])
{

}

LVector2::LVector2(const LVector2 &_a)
{
    x=_a.x;
    y=_a.y;
}

f32 LVector2::angle(const LVector2 &_a, const LVector2 &_b)
{
    return lACos(dotProduct(_a.getNormalized(),_b.getNormalized()));
}

f32& LVector2::at(u32 _i)
{
    lError(_i>2,"f32& LVector2::at(u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector2::at(u32 _i) const
{
    lError(_i>2,"f32 LVector2::at(u32 _i)const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector2::distance(const LVector2 &_a, const LVector2 &_b)
{
    f32 dx=_b.x-_a.x;
    f32 dy=_b.y-_a.y;
    return lSqrt(dx*dx+dy*dy);
}

f32 LVector2::dotProduct(const LVector2 &_a, const LVector2 &_b)
{
    return _a.getDotProduct(_b);
}

f32 LVector2::getAngelFrom(const LVector2 &_other) const
{
    return angle(*this,_other);
}

f32 LVector2::getDistanceFrom(const LVector2 &_other) const
{
    return distance(*this,_other);
}

f32 LVector2::getDotProduct(const LVector2 &_other) const
{
    return x*_other.x+y*_other.y;
}

f32 LVector2::getLength() const
{
    return lSqrt(x*x+y*y);
}

LVector2 LVector2::getNormalized() const
{
    LVector2 o=(*this);
    if(!o.normalize())
        return LVector2::zero;
    return o;
}

LVector2 LVector2::getReflected(const LVector2 &_n) const
{
    LVector2 out=(*this);
    out.reflect(_n);
    return out;
}

f32 LVector2::getSqauredLength() const
{
    return (x*x+y*y);
}

f32 LVector2::getSqauredDistanceFrom(const LVector2 &_other) const
{
    return squaredDistance(*this,_other);
}

bool LVector2::isNormalizable() const
{
    return (*this!=LVector2::zero);
}

bool LVector2::isNormalized() const
{
    return lCompareFloat(getSqauredLength(),1.0);
}

LVector2 LVector2::lerp(const LVector2 &_a, const LVector2 &_b, const f64 &_p)
{
    return LVector2(
                lLerp(_a.x,_b.x,_p),
                lLerp(_a.y,_b.y,_p)
                );
}

bool LVector2::normalize()
{
    f32 l=lSqrt(x*x+y*y);
    if(l<=0.0f)
        return false;
    x/=l;
    y/=l;
    return true;
}

void LVector2::reflect(const LVector2 &_n)
{
    (*this)=(*this)-(2.0f*dotProduct(*this,_n)*_n);
}

void LVector2::set(const f32 &_scaler)
{
    x=_scaler;
    y=_scaler;
}

void LVector2::set(const f32 &_x, const f32 &_y)
{
    x=_x;
    y=_y;
}

void LVector2::set(const f32 *_a)
{
    x=_a[0];
    y=_a[1];
}

void LVector2::setLength(const f32 &_l)
{
    normalize();
    (*this)*=_l;
}

f32 LVector2::squaredDistance(const LVector2 &_a, const LVector2 &_b)
{
    f32 dx=_b.x-_a.x;
    f32 dy=_b.y-_a.y;
    return dx*dx+dy*dy;
}

f32& LVector2::operator[](u32 _i)
{
    lError(_i>2,"f32& LVector2::operator[](u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32& LVector2::operator()(u32 _i)
{
    lError(_i>2,"f32& LVector2::operator()(u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector2::operator[](u32 _i) const
{
    lError(_i>2,"f32 LVector2::operator[](u32 _i) const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector2::operator()(u32 _i) const
{
    lError(_i>2,"f32 LVector2::operator()(u32 _i) const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

LVector2 &LVector2::operator*=(const LVector2 &_other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector2 &LVector2::operator*=(const LMatrix &_other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector2 &LVector2::operator*=(const f32 &_scaler)
{
    (*this)= (*this)*_scaler;
    return (*this);
}

LVector2 &LVector2::operator/=(const LVector2 &_other)
{
    (*this)= (*this)/_other;
    return (*this);
}

LVector2 &LVector2::operator/=(const f32 &_scaler)
{
    (*this)= (*this)/_scaler;
    return (*this);
}

LVector2 &LVector2::operator+=(const LVector2 &_other)
{
    (*this)= (*this)+_other;
    return (*this);
}

LVector2 &LVector2::operator-=(const LVector2 &_other)
{
    (*this)= (*this)-_other;
    return (*this);
}

bool LVector2::operator!=(const LVector2 &_other) const
{
    return !(*this==_other);
}



LVector2 operator*(const f32 &_a, const LVector2 &_b)
{
    LVector2 out=_b;
    out*=_a;
    return out;
}

LVector2 operator/(const f32 &_a, const LVector2 &_b)
{
    LVector2 out=_b;
    out/=_a;
    return out;
}

LVector2 operator+(const f32 &_a, const LVector2 &_b)
{
    LVector2 out=_b;
    out+=_a;
    return out;
}

LVector2 operator-(const f32 &_a, const LVector2 &_b)
{
    LVector2 out=_b;
    out-=_a;
    return out;
}

LVector2 &LVector2::operator=(const LVector2 &_a)
{
    x=_a.x;
    y=_a.y;
    return (*this);
}

LVector2 &LVector2::operator=(const f32 &_a)
{
    x=y=_a;
    return (*this);
}

LVector2 LVector2::operator*(const LVector2 &_other) const
{
    LVector2 out=(*this);
    out.x*=_other.x;
    out.y*=_other.y;
    return out;
}

LVector2 LVector2::operator*(const LMatrix &_other) const
{
    LVector2 out;
    out.x=x*_other.m11+y*_other.m21+_other.m31;
    out.y=x*_other.m12+y*_other.m22+_other.m32;
    return out;
}

LVector2 LVector2::operator*(const f32 &_scaler) const
{
    LVector2 out=(*this);
    out.x*=_scaler;
    out.y*=_scaler;
    return out;
}

LVector2 LVector2::operator/(const LVector2 &_other) const
{
    LVector2 out=(*this);
    out.x/=_other.x;
    out.y/=_other.y;
    return out;
}

LVector2 LVector2::operator/(const f32 &_scaler) const
{
    LVector2 out=(*this);
    out.x/=_scaler;
    out.y/=_scaler;
    return out;
}

LVector2 LVector2::operator+() const
{
    return (*this);
}

LVector2 LVector2::operator-() const
{
    return LVector2(-x,-y);
}

LVector2 LVector2::operator+(const LVector2 &_other)const
{
    return LVector2(x+_other.x,
                    y+_other.y);
}

LVector2 LVector2::operator-(const LVector2 &_other)const
{
    return LVector2(x-_other.x,
                    y-_other.y);
}

bool LVector2::operator==(const LVector2 &_other) const
{
    return(
               lCompareFloat(x,_other.x)&&
               lCompareFloat(y,_other.y)
           );
}

LNAMESPACE_END

#endif // LVECTOR2_H
