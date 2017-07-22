#ifndef LVECTOR3_H
#define LVECTOR3_H
#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lmatrix.h"
LNAMESPACE_BEGIN

// forward declartion
class LVector4;

class LAPI LVector3
{
public:
    //! Default constructor
    linline                 LVector3();

    //! constructor will set all parameter to _scaler
    linline                 LVector3(const f32& _scaler);

    //! constructor with  3 first values
    linline                 LVector3(const f32& _x,const f32& _y,const f32& _z);

    //! constructor with pointer (to 3D array)
    linline                 LVector3(const f32* _a);

    //! Copy Constructor
    linline                 LVector3(const LVector3& _a);

    //! Get Angel Between two axis
    static linline  f32     angle(const LVector3& _a, const LVector3& _b);

    //! Access to vector parameter  0=x , 1=y , 2=z
    linline f32&            at(u32 _i);
    linline f32             at(u32 _i)const;

    //! Get _a (cross) _b
    static linline LVector3 crossProduct(const LVector3& _a,const LVector3& _b);

    //! Get Distance Between two point
    static linline  f32     distance(const LVector3& _a, const LVector3& _b);

    //! Get _a (dot) _b
    static linline f32      dotProduct(const LVector3& _a,const LVector3& _b);

    //! Get Angel of this to _other
    linline f32             getAngelFrom(const LVector3& _other)const;

    //! Get this (cross) _other
    linline LVector3        getCrossProduct(const LVector3& _other)const;

    //! Get Distance of this to _other
    linline f32             getDistanceFrom(const LVector3& _other)const;

    //! Get this (dot) _other
    linline f32             getDotProduct(const LVector3& _other)const;

    //! Get Length of Vector
    linline f32             getLength()const;

    //! Get Normalized Copy of this. if Vector isn't normalizable , returns LVector3::zero
    linline LVector3        getNormalized()const;

    //! Get Orthogonal Vector of this vector
    linline LVector3        getOrthogonal()const;

    //! Get Refelcted Copy of this
    linline LVector3        getReflected(const LVector3& _n)const;

    //! Get Squared Length
    linline f32             getSqauredLength()const;

    //! Get Sqaured Distance of this to _other
    linline f32             getSqauredDistanceFrom(const LVector3& _other)const;

    //! Checkout this vector is able to normalize
    linline bool            isNormalizable()const;

    //! Checkout is this a unit vector
    linline bool            isNormalized()const;

    //! Lerp Between two point
    static linline LVector3 lerp(const LVector3& _a,const LVector3& _b,const f64& _p);

    //! Normalize Vector
    linline bool            normalize();

    //! Get orthogonal vector
    static linline LVector3 orthogonal(const LVector3& _a);

    //! Reflect the vector
    linline void            reflect(const LVector3& _n);

    //! Rotate A around B using theta and phi
    //! theta angel between +X axis and rotation axis
    //! phi   angel between +Y axis and rotation axis
    static linline LVector3 rotateAround(const LVector3 &a, const LVector3 &b, const f32 &yaw, const f32 &pitch, const f32 &roll);


    //! set functions just like constructors
    linline void            set(const f32& _scaler);

    linline void            set(const f32& _x,const f32& _y,const f32& _z);

    linline void            set(const f32* _a);

    //! Change Length of this
    linline void            setLength(const f32& _l);

    //! Get Squared Distance Between two point
    static linline  f32     squaredDistance(const LVector3& _a, const LVector3& _b);

    //! Convert this to translation Matrix
    linline LMatrix         toTranslationMatrix()const;


    //! Access to vector parameter just like at
    linline f32&            operator[](u32 _i);
    linline f32&            operator()(u32 _i);
    linline f32             operator[](u32 _i)const;
    linline f32             operator()(u32 _i)const;

    //! Copy
    linline LVector3&       operator=(const LVector3& _a);
    linline LVector3&       operator=(const f32& _a);

    //! Multiply . IMPORTANT NOTE : this IS NOT crossproduct or dotproduct
    linline LVector3        operator*(const LVector3& _other)const;
    linline LVector3&       operator*=(const LVector3& _other);
    linline LVector3        operator*(const f32& _scaler)const;
    linline LVector3&       operator*=(const f32& _scaler);
    friend linline LVector3 operator*(const f32 &_a, const LVector3 &_b);
    linline LVector3        operator*(const LMatrix& _other)const;
    linline LVector3&       operator*=(const LMatrix& _other);

    //! Division
    linline LVector3        operator/(const LVector3& _other)const;
    linline LVector3&       operator/=(const LVector3& _other);
    linline LVector3        operator/(const f32& _scaler)const;
    linline LVector3&       operator/=(const f32& _scaler);
    friend linline LVector3 operator/(const f32 &_a, const LVector3 &_b);

    //! Negetive and Positive sign
    linline LVector3        operator+()const;
    linline LVector3        operator-()const;

    //! Addition
    linline LVector3        operator+(const LVector3& _other)const;
    linline LVector3&       operator+=(const LVector3& _other);
    friend linline LVector3 operator+(const f32 &_a, const LVector3 &_b);

    //! Sub
    linline LVector3        operator-(const LVector3& _other)const;
    linline LVector3&       operator-=(const LVector3& _other);
    friend linline LVector3 operator-(const f32 &_a, const LVector3 &_b);

    //! Compare
    linline bool            operator==(const LVector3& _other)const;
    linline bool            operator!=(const LVector3& _other)const;

    //! Casting operator
    operator                LVector4()const;

    const static LVector3   up;
    const static LVector3   down;
    const static LVector3   left;
    const static LVector3   right;
    const static LVector3   forward;
    const static LVector3   back;
    const static LVector3   zero;
    const static LVector3   one;

public:
    union
    {
        struct
        {
            f32 x,y,z;
        };
        f32 m[3];
    };
};


LVector3::LVector3():
    x(0.0f),
    y(0.0f),
    z(0.0f)
{

}

LVector3::LVector3(const f32 &_scaler):
    x(_scaler),
    y(_scaler),
    z(_scaler)
{

}

LVector3::LVector3(const f32 &_x, const f32 &_y, const f32 &_z):
    x(_x),
    y(_y),
    z(_z)
{

}

LVector3::LVector3(const f32 *_a):
    x(_a[0]),
    y(_a[1]),
    z(_a[2])
{

}

LVector3::LVector3(const LVector3 &_a)
{
    x=_a.x;
    y=_a.y;
    z=_a.z;
}

f32 LVector3::angle(const LVector3 &_a, const LVector3 &_b)
{
    return lACos(dotProduct(_a.getNormalized(),_b.getNormalized()));
}

f32& LVector3::at(u32 _i)
{
    lError(_i>2,"f32& LVector3::at(u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector3::at(u32 _i) const
{
    lError(_i>2,"f32 LVector3::at(u32 _i)const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

LVector3 LVector3::crossProduct(const LVector3 &_a, const LVector3 &_b)
{
    return _a.getCrossProduct(_b);
}

f32 LVector3::distance(const LVector3 &_a, const LVector3 &_b)
{
    f32 dx=_b.x-_a.x;
    f32 dy=_b.y-_a.y;
    f32 dz=_b.z-_a.z;
    return lSqrt(dx*dx+dy*dy+dz*dz);
}

f32 LVector3::dotProduct(const LVector3 &_a, const LVector3 &_b)
{
    return _a.getDotProduct(_b);
}

f32 LVector3::getAngelFrom(const LVector3 &_other) const
{
    return angle(*this,_other);
}

LVector3 LVector3::getCrossProduct(const LVector3 &_other) const
{
    return LVector3((y*_other.z-z*_other.y),
                    -(x*_other.z-z*_other.x),
                    (x*_other.y-y*_other.x));
}

f32 LVector3::getDistanceFrom(const LVector3 &_other) const
{
    return distance(*this,_other);
}

f32 LVector3::getDotProduct(const LVector3 &_other) const
{
    return x*_other.x+y*_other.y+z*_other.z;
}

f32 LVector3::getLength() const
{
    return lSqrt(x*x+y*y+z*z);
}

LVector3 LVector3::getNormalized() const
{
    LVector3 o=(*this);
    if(!o.normalize())
        return LVector3::zero;
    return o;
}

LVector3 LVector3::getOrthogonal() const
{
    LVector3 ot=(x<y)?(x<z?right:forward):(y<z?up:forward);
    return getCrossProduct(ot);
}

LVector3 LVector3::getReflected(const LVector3 &_n) const
{
    LVector3 out=(*this);
    out.reflect(_n);
    return out;
}

f32 LVector3::getSqauredLength() const
{
    return (x*x+y*y+z*z);
}

f32 LVector3::getSqauredDistanceFrom(const LVector3 &_other) const
{
    return squaredDistance(*this,_other);
}

bool LVector3::isNormalizable() const
{
    return (*this!=LVector3::zero);
}

bool LVector3::isNormalized() const
{
    return lCompareFloat(getSqauredLength(),1.0);
}

LVector3 LVector3::lerp(const LVector3 &_a, const LVector3 &_b, const f64 &_p)
{
    return LVector3(
                lLerp(_a.x,_b.x,_p),
                lLerp(_a.y,_b.y,_p),
                lLerp(_a.z,_b.z,_p)
                );
}

bool LVector3::normalize()
{
    f32 l=lSqrt(x*x+y*y+z*z);
    if(l<=0.0f)
        return false;
    x/=l;
    y/=l;
    z/=l;
    return true;
}

LVector3 LVector3::orthogonal(const LVector3 &_a)
{
    return _a.getOrthogonal();
}

void LVector3::reflect(const LVector3 &_n)
{
    (*this)=(*this)-(2.0f*dotProduct(*this,_n)*_n);
}

LVector3 LVector3::rotateAround(const LVector3 &a, const LVector3 &b, const f32 &yaw, const f32 &pitch, const f32 &roll)
{
    //! ToDo : Get Better algorithm
    LVector3 out=a-b;
    out*=LMatrix::createRotationMatrix(yaw,pitch,roll);
    out+=b;
    return out;
}

void LVector3::set(const f32 &_scaler)
{
    x=_scaler;
    y=_scaler;
    z=_scaler;
}

void LVector3::set(const f32 &_x, const f32 &_y, const f32 &_z)
{
    x=_x;
    y=_y;
    z=_z;
}

void LVector3::set(const f32 *_a)
{
    x=_a[0];
    y=_a[1];
    z=_a[2];
}

void LVector3::setLength(const f32 &_l)
{
    normalize();
    (*this)*=_l;
}

f32 LVector3::squaredDistance(const LVector3 &_a, const LVector3 &_b)
{
    f32 dx=_b.x-_a.x;
    f32 dy=_b.y-_a.y;
    f32 dz=_b.z-_a.z;
    return dx*dx+dy*dy+dz*dz;
}

LMatrix LVector3::toTranslationMatrix() const
{
    return LMatrix::createTranslationMatrix((*this));
}

f32& LVector3::operator[](u32 _i)
{
    lError(_i>2,"f32& LVector3::operator[](u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32& LVector3::operator()(u32 _i)
{
    lError(_i>2,"f32& LVector3::operator()(u32 _i): big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector3::operator[](u32 _i) const
{
    lError(_i>2,"f32 LVector3::operator[](u32 _i) const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

f32 LVector3::operator()(u32 _i) const
{
    lError(_i>2,"f32 LVector3::operator()(u32 _i) const: big value for _i ; must be between [0-2]",m[0]);
    return m[_i];
}

LVector3 &LVector3::operator*=(const LVector3 &_other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector3 &LVector3::operator*=(const LMatrix &_other)
{
    (*this)= (*this)*_other;
    return (*this);
}

LVector3 &LVector3::operator*=(const f32 &_scaler)
{
    (*this)= (*this)*_scaler;
    return (*this);
}

LVector3 &LVector3::operator/=(const LVector3 &_other)
{
    (*this)= (*this)/_other;
    return (*this);
}

LVector3 &LVector3::operator/=(const f32 &_scaler)
{
    (*this)= (*this)/_scaler;
    return (*this);
}

LVector3 &LVector3::operator+=(const LVector3 &_other)
{
    (*this)= (*this)+_other;
    return (*this);
}

LVector3 &LVector3::operator-=(const LVector3 &_other)
{
    (*this)= (*this)-_other;
    return (*this);
}

bool LVector3::operator!=(const LVector3 &_other) const
{
    return !(*this==_other);
}



LVector3 operator*(const f32 &_a, const LVector3 &_b)
{
    LVector3 out=_b;
    out*=_a;
    return out;
}

LVector3 operator/(const f32 &_a, const LVector3 &_b)
{
    LVector3 out=_b;
    out/=_a;
    return out;
}

LVector3 operator+(const f32 &_a, const LVector3 &_b)
{
    LVector3 out=_b;
    out+=_a;
    return out;
}

LVector3 operator-(const f32 &_a, const LVector3 &_b)
{
    LVector3 out=_b;
    out-=_a;
    return out;
}

LVector3 &LVector3::operator=(const LVector3 &_a)
{
    x=_a.x;
    y=_a.y;
    z=_a.z;
    return (*this);
}

LVector3 &LVector3::operator=(const f32 &_a)
{
    x=y=z=_a;
    return (*this);
}

LVector3 LVector3::operator*(const LVector3 &_other) const
{
    LVector3 out=(*this);
    out.x*=_other.x;
    out.y*=_other.y;
    out.z*=_other.z;
    return out;
}

LVector3 LVector3::operator*(const LMatrix &_other) const
{
    LVector3 out;
    out.x=x*_other.m11+y*_other.m21+z*_other.m31+_other.m41;
    out.y=x*_other.m12+y*_other.m22+z*_other.m32+_other.m42;
    out.z=x*_other.m13+y*_other.m23+z*_other.m33+_other.m43;
    return out;
}

LVector3 LVector3::operator*(const f32 &_scaler) const
{
    LVector3 out=(*this);
    out.x*=_scaler;
    out.y*=_scaler;
    out.z*=_scaler;
    return out;
}

LVector3 LVector3::operator/(const LVector3 &_other) const
{
    LVector3 out=(*this);
    out.x/=_other.x;
    out.y/=_other.y;
    out.z/=_other.z;
    return out;
}

LVector3 LVector3::operator/(const f32 &_scaler) const
{
    LVector3 out=(*this);
    out.x/=_scaler;
    out.y/=_scaler;
    out.z/=_scaler;
    return out;
}

LVector3 LVector3::operator+() const
{
    return (*this);
}

LVector3 LVector3::operator-() const
{
    return LVector3(-x,-y,-z);
}

LVector3 LVector3::operator+(const LVector3 &_other)const
{
    return LVector3(x+_other.x,
                    y+_other.y,
                    z+_other.z);
}

LVector3 LVector3::operator-(const LVector3 &_other)const
{
    return LVector3(x-_other.x,
                    y-_other.y,
                    z-_other.z);
}

bool LVector3::operator==(const LVector3 &_other) const
{
    return(
               lCompareFloat(x,_other.x)&&
               lCompareFloat(y,_other.y)&&
               lCompareFloat(z,_other.z)
           );
}

LNAMESPACE_END
#endif // LVECTOR3_H
