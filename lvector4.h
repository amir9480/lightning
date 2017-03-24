#ifndef LVECTOR4_H
#define LVECTOR4_H

#include "ldefines.h"
#include "lmathutility.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

class LAPI LVector4
{
public:
    //! Constructor
    linline                 LVector4();
    //! Constructor
    linline                 LVector4(const LVector3& p,const f32& _w=1.0f);
    //! Constructor
    linline                 LVector4(const f32& _s);
    //! Constructor
    linline                 LVector4(const f32& _x,const f32& _y,const f32& _z,const f32& _w=1.0f);
    //! Constructor
    linline                 LVector4(const LVector4& _other);

    //! Access to vector parameter  0=x , 1=y , 2=z , w=3
    linline f32&            at(u32 _i);
    linline f32             at(u32 _i)const;

    //! set function
    linline void            set(const LVector3& p,const f32& _w=1.0f);
    //! set function
    linline void            set(const f32& _x,const f32& _y,const f32& _z,const f32& _w=1.0f);
    //! set function
    linline void            set(const f32& _s);

    //! Copy Assign
    linline LVector4&       operator=(const LVector4& _other);

    //! Access to vector parameter just like at
    linline f32&            operator[](u32 _i);
    linline f32&            operator()(u32 _i);
    linline f32             operator[](u32 _i)const;
    linline f32             operator()(u32 _i)const;

    //! Compare
    linline bool            operator==(const LVector4& _other)const;
    linline bool            operator!=(const LVector4& _other)const;

    //! Multiply . IMPORTANT NOTE : this IS NOT crossproduct or dotproduct
    linline LVector4        operator*(const LVector4& _other)const;
    linline LVector4&       operator*=(const LVector4& _other);
    linline LVector4        operator*(const f32& _scaler)const;
    linline LVector4&       operator*=(const f32& _scaler);
    friend linline LVector4 operator*(const f32 &_a, const LVector4 &_b);
    linline LVector4        operator*(const LMatrix& _other)const;
    linline LVector4&       operator*=(const LMatrix& _other);

    //! Division
    linline LVector4        operator/(const LVector4& _other)const;
    linline LVector4&       operator/=(const LVector4& _other);
    linline LVector4        operator/(const f32& _scaler)const;
    linline LVector4&       operator/=(const f32& _scaler);
    friend linline LVector4 operator/(const f32 &_a, const LVector4 &_b);

    //! Negetive and Positive sign
    linline LVector4        operator+()const;
    linline LVector4        operator-()const;

    //! Addition
    linline LVector4        operator+(const LVector4& _other)const;
    linline LVector4&       operator+=(const LVector4& _other);
    friend linline LVector4 operator+(const f32 &_a, const LVector4 &_b);

    //! Sub
    linline LVector4        operator-(const LVector4& _other)const;
    linline LVector4&       operator-=(const LVector4& _other);
    friend linline LVector4 operator-(const f32 &_a, const LVector4 &_b);

    //! Casting operator
    linline operator        LVector3()const;
public:
    union
    {
        struct
        {
            f32 x,y,z,w;
        };
        f32 m[4];
    };
};

LVector4::LVector4():
    x(0.0f),
    y(0.0f),
    z(0.0f),
    w(1.0f)
{

}

LVector4::LVector4(const LVector3 &p, const f32 &_w):
    x(p.x),
    y(p.y),
    z(p.z),
    w(_w)
{

}

LVector4::LVector4(const f32 &_s)
{
    set(_s);
}

LVector4::LVector4(const f32 &_x, const f32 &_y, const f32 &_z, const f32 &_w):
    x(_x),
    y(_y),
    z(_z),
    w(_w)
{

}

LVector4::LVector4(const LVector4 &_other)
{
    (*this)=_other;
}

f32& LVector4::at(u32 _i)
{
    //! ToDo: Add exception to i
    return m[_i];
}

f32 LVector4::at(u32 _i) const
{
    //! ToDo: Add exception to i
    return m[_i];
}

void LVector4::set(const LVector3 &p, const f32 &_w)
{
    x=(p.x);
    y=(p.y);
    z=(p.z);
    w=(_w);
}

void LVector4::set(const f32 &_x, const f32 &_y, const f32 &_z, const f32 &_w)
{
    x=(_x);
    y=(_y);
    z=(_z);
    w=(_w);
}

void LVector4::set(const f32 &_s)
{
    x=y=z=w=_s;
}

LVector4 &LVector4::operator=(const LVector4 &_other)
{
    x=_other.x;
    y=_other.y;
    z=_other.z;
    w=_other.w;
    return (*this);
}

f32& LVector4::operator[](u32 _i)
{
    //! ToDo: Add exception to i
    return m[_i];
}

f32& LVector4::operator()(u32 _i)
{
    //! ToDo: Add exception to i
    return m[_i];
}

f32 LVector4::operator[](u32 _i) const
{
    //! ToDo: Add exception to i
    return m[_i];
}

f32 LVector4::operator()(u32 _i) const
{
    //! ToDo: Add exception to i
    return m[_i];
}

bool LVector4::operator==(const LVector4 &_other) const
{
    return(
               lCompareFloat(x,_other.x)&&
               lCompareFloat(y,_other.y)&&
               lCompareFloat(z,_other.z)&&
               lCompareFloat(w,_other.w)
           );
}

bool LVector4::operator!=(const LVector4 &_other) const
{
    return !((*this)==_other);
}


LVector4 &LVector4::operator*=(const LVector4 &_other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector4 &LVector4::operator*=(const f32 &_scaler)
{
    (*this)= (*this)*_scaler;
    return (*this);
}

LVector4& LVector4::operator*=(const LMatrix& _other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector4 &LVector4::operator/=(const LVector4 &_other)
{
    (*this)= (*this)/_other;
    return (*this);
}

LVector4 &LVector4::operator/=(const f32 &_scaler)
{
    (*this)= (*this)/_scaler;
    return (*this);
}

LVector4 &LVector4::operator+=(const LVector4 &_other)
{
    (*this)= (*this)+_other;
    return (*this);
}

LVector4 &LVector4::operator-=(const LVector4 &_other)
{
    (*this)= (*this)-_other;
    return (*this);
}


LVector4 operator*(const f32 &_a, const LVector4 &_b)
{
    LVector4 out=_b;
    out*=_a;
    return out;
}

LVector4 operator/(const f32 &_a, const LVector4 &_b)
{
    LVector4 out=_b;
    out/=_a;
    return out;
}

LVector4 operator+(const f32 &_a, const LVector4 &_b)
{
    LVector4 out=_b;
    out+=_a;
    return out;
}

LVector4 operator-(const f32 &_a, const LVector4 &_b)
{
    LVector4 out=_b;
    out-=_a;
    return out;
}

LVector4 LVector4::operator*(const LVector4 &_other) const
{
    LVector4 out=(*this);
    out.x*=_other.x;
    out.y*=_other.y;
    out.z*=_other.z;
    out.w*=_other.w;
    return out;
}

LVector4 LVector4::operator*(const LMatrix &_other) const
{
    LVector4 out;
    out.x=x*_other.m11+y*_other.m21+z*_other.m31+w*_other.m41;
    out.y=x*_other.m12+y*_other.m22+z*_other.m32+w*_other.m42;
    out.z=x*_other.m13+y*_other.m23+z*_other.m33+w*_other.m43;
    out.w=x*_other.m14+y*_other.m24+z*_other.m34+w*_other.m44;
    return out;
}

LVector4 LVector4::operator*(const f32 &_scaler) const
{
    LVector4 out=(*this);
    out.x*=_scaler;
    out.y*=_scaler;
    out.z*=_scaler;
    out.w*=_scaler;
    return out;
}

LVector4 LVector4::operator/(const LVector4 &_other) const
{
    LVector4 out=(*this);
    out.x/=_other.x;
    out.y/=_other.y;
    out.z/=_other.z;
    out.w/=_other.w;
    return out;
}

LVector4 LVector4::operator/(const f32 &_scaler) const
{
    LVector4 out=(*this);
    out.x/=_scaler;
    out.y/=_scaler;
    out.z/=_scaler;
    out.w/=_scaler;
    return out;
}

LVector4 LVector4::operator+() const
{
    return (*this);
}

LVector4 LVector4::operator-() const
{
    return LVector4(-x,-y,-z,-w);
}

LVector4::operator LVector3() const
{
    return LVector3(x/w,y/w,z/w);
}

LVector4 LVector4::operator+(const LVector4 &_other)const
{
    return LVector4(x+_other.x,
                    y+_other.y,
                    z+_other.z,
                    w+_other.w);
}

LVector4 LVector4::operator-(const LVector4 &_other)const
{
    return LVector4(x-_other.x,
                    y-_other.y,
                    z-_other.z,
                    w-_other.w);
}

LNAMESPACE_END

#endif // LVECTOR4_H
