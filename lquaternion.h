#ifndef LQUATERNION_H
#define LQUATERNION_H

#include "lcore.h"
#include "lmathutility.h"
#include "lutility.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

// forward declartion
class LVector3;


// this class is based on '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
class LAPI LQuaternion
{
public:
    linline                     LQuaternion();

    linline                     LQuaternion(const f32& _x,const f32& _y,const f32& _z,const f32& _w);

    //! Constructor Quaternion From Axes
                                LQuaternion(const LVector3& _right,const LVector3& _up,const LVector3& _forward);

    //! Constructor Quaternion from an Axis and an Angle
                                LQuaternion(const LVector3& _axis,const f32& _angle);

    //! Constructor Quaternion from euler angles
    linline                     LQuaternion(const f32& _x, const f32& _y, const f32& _z);
                                LQuaternion(const LVector3& _euler);

    //! Constructor From Rotation Matrix
    linline                     LQuaternion(const LMatrix& _rotation_matrix);

    //! Constructor  from to rotation
                                LQuaternion(const LVector3& _from,const LVector3& _to);

    //! Copy Constructor
    linline                     LQuaternion(const LQuaternion& _other);

    //! at function
    //! x=0 , y=1 , z=2 , w=3
    linline f32&                at(u32 i);
    linline f32                 at(u32 i)const;

    //! Conjugate the Quaternion -> means (-x,-y,-z,w)
    linline void                conjugate();

    //! Get CrossProduct Between Two Quaternion
    static linline LQuaternion  crossProduct(const LQuaternion& _a,const LQuaternion& _b);

    //! Get DotProduct Between Two Quaternion
    static linline f32          dotProduct(const LQuaternion& _a,const LQuaternion& _b);

    //! Get Conjugated copy of this -> means (-x,-y,-z,w)
    linline LQuaternion         getConjugated()const;

    //! Get Cross Product of this and other
    linline LQuaternion         getCrossProduct(const LQuaternion& _other)const;

    //! Get dot product of this and other
    linline f32                 getDotProduct(const LQuaternion& _other)const;

    //! Get Exp of this
    linline LQuaternion         getExp()const;

    //! Get forward Axis of this
    LVector3                    getForward()const;

    //! Get Inversed Copy of this
    linline LQuaternion         getInversed()const;

    //! is same getMagnitude
    linline f32                 getLength()const;

    //! Get Logarithm of this
    linline LQuaternion         getLog()const;

    //! Get Magnitude of Quaternion
    linline f32                 getMagnitude()const;

    //! Get Normalized Copy of this
    linline LQuaternion         getNormalized()const;

    //! Get right Axis of this
    LVector3                    getRight()const;

    //! Get Rotated Vector by this Quaternion
    LVector3                    getRotated(const LVector3& _in)const;

    //! is same getSqauredMagnitude
    linline f32                 getSqauredLength()const;

    //! Get Sqaured Magnitude of Quaternion
    linline f32                 getSqauredMagnitude()const;

    //! Get forward Axis of this
    LVector3                    getUp()const;

    //! Inverse the Quaternion. if Quaternion can not inverse return false
    linline bool                inverse();

    //! is Quaternion able to inverse?
    linline bool                isInversable()const;

    //! Get Linear Quaternion Interpolation
    linline static LQuaternion  lerp(const LQuaternion& _a1,const LQuaternion& _a2,const f32& _t);

    //! Normalize Quaternion
    linline void                normalize();

    //! set functions
    linline void                set(const f32& _x,const f32& _y,const f32& _z,const f32& _w);

    //! set Quaternion From Axes
    void                        set(const LVector3& _right,const LVector3& _up,const LVector3& _forward);

    //! set Quaternion from an Axis and an Angle
    void                        set(const LVector3& _axis,const f32& _angle);

    //! set Quaternion from euler angles
    linline void                set(const f32& _x, const f32& _y, const f32& _z);
    void                        set(const LVector3& _euler);

    //! set From Rotation Matrix
    linline void                set(const LMatrix& _rotation_matrix);

    //! set  from to rotation
    void                        set(const LVector3& _from,const LVector3& _to);

    //! Get Spherical Linear Quaternion Interpolation
    linline static LQuaternion  slerp(const LQuaternion& _a1,const LQuaternion& _a2,const f32& _t);

    //! Convert to an Axes
    void                        toAxes(LVector3& _right, LVector3& _up, LVector3& _forward)const;

    //! Convert to an Axis and an Angle
    void                        toAxisAngle(LVector3& _axis_,f32& _angle_)const;

    //! Convert To Euler Angel
    LVector3                    toEulerAngel()const;

    //! Convert to RotationMatrix
    linline LMatrix             toRotationMatrix()const;

    //! Just like at
    linline f32&                operator[](u32 i);
    linline f32                 operator[](u32 i)const;

    //! Positive/Negetive signs
    linline LQuaternion         operator+ ()const;
    linline LQuaternion         operator- ()const;

    //! Copy
    linline LQuaternion&        operator= (const LQuaternion& _other);

    //! Compare
    linline bool                operator== (const LQuaternion& _other)const;
    linline bool                operator!= (const LQuaternion& _other)const;

    //! Cross Product
    linline LQuaternion         operator* (const LQuaternion& _other)const;
    linline LQuaternion&        operator*= (const LQuaternion& _other);

    //! Scaler Product
    linline LQuaternion         operator* (const f32& _scaler)const;
    linline LQuaternion&        operator*= (const f32& _scaler);

    //! Divid
    linline LQuaternion         operator/ (const LQuaternion& _other)const;
    linline LQuaternion&        operator/= (const LQuaternion& _other);

    //! Scaler div
    linline LQuaternion         operator/ (const f32& _scaler)const;
    linline LQuaternion&        operator/= (const f32& _scaler);

    //! Add
    linline LQuaternion         operator+ (const LQuaternion& _other)const;
    linline LQuaternion&        operator+= (const LQuaternion& _other);

    //! Sub
    linline LQuaternion         operator- (const LQuaternion& _other)const;
    linline LQuaternion&        operator-= (const LQuaternion& _other);


    static const LQuaternion identity;
    static const LQuaternion zero;
public:
    union
    {
        struct
        {
            f32 x,y,z,w;
        };
        //! X Y Z W
        f32 m[4];
    };
};

LQuaternion::LQuaternion():x(0.0f),y(0.0f),z(0.0f),w(1.0f)
{

}

LQuaternion::LQuaternion(const f32 &_x, const f32 &_y, const f32 &_z)
{
    set(_x,_y,_z);
}

LQuaternion::LQuaternion(const f32 &_x, const f32 &_y, const f32 &_z, const f32 &_w)
{
    set(_x,_y,_z,_w);
}

LQuaternion::LQuaternion(const LMatrix &_in)
{
    set(_in);
}

LQuaternion::LQuaternion(const LQuaternion &_other)
{
    (*this)=_other;
}


f32 &LQuaternion::at(u32 i)
{
    //! TO DO : Add assert to i
    return m[i];
}

f32 LQuaternion::at(u32 i) const
{
    //! TO DO : Add assert to i
    return m[i];
}

void LQuaternion::conjugate()
{
    x=-x;
    y=-y;
    z=-z;
    normalize();
}

LQuaternion LQuaternion::crossProduct(const LQuaternion &_a, const LQuaternion &_b)
{
    return _a.getCrossProduct(_b);
}

f32 LQuaternion::dotProduct(const LQuaternion &_a, const LQuaternion &_b)
{
    return _a.getDotProduct(_b);
}

LQuaternion LQuaternion::getExp() const
{
    LQuaternion out;
    f32 m;
    f32 l = lSqrt(x*x+y*y+z*z);
    if(lCompareFloat(l,0.0f,4))
        m=1.0f;
    else
        m=lSin(l)/l;
    out.w=lCos(l);
    out.x=x*m;
    out.y=y*m;
    out.z=z*m;
    return out;
}

f32 LQuaternion::getLength() const
{
    return lSqrt(x*x+y*y+z*z+w*w);
}

LQuaternion LQuaternion::getLog() const
{
    LQuaternion out;
    float l=lATan2((x*x+y*y+z*z),w);
    out.w=0.0f;
    out.x=x*l;
    out.y=y*l;
    out.z=z*l;
    return out;
}

f32 LQuaternion::getMagnitude() const
{
    return lSqrt(x*x+y*y+z*z+w*w);
}

LQuaternion LQuaternion::getConjugated() const
{
    LQuaternion out=(*this);
    out.conjugate();
    return out;
}

LQuaternion LQuaternion::getCrossProduct(const LQuaternion &_other) const
{
    return LQuaternion(
                w*_other.x + x*_other.w + y*_other.z - z*_other.y,
                w*_other.y + y*_other.w + z*_other.x - x*_other.z,
                w*_other.z + z*_other.w + x*_other.y - y*_other.x,
                w*_other.w - x*_other.x - y*_other.y - z*_other.z
                );
}

f32 LQuaternion::getDotProduct(const LQuaternion &_other) const
{
    return x*_other.x + y*_other.y + z*_other.z + w*_other.w;
}

LQuaternion LQuaternion::getInversed() const
{
    LQuaternion out=(*this);
    out.inverse();
    return out;
}

LQuaternion LQuaternion::getNormalized() const
{
    LQuaternion out=(*this);
    out.normalize();
    return out;
}

f32 LQuaternion::getSqauredLength() const
{
    return x*x+y*y+z*z+w*w;
}

f32 LQuaternion::getSqauredMagnitude() const
{
    return x*x+y*y+z*z+w*w;
}

bool LQuaternion::inverse()
{
    f32 mag=lSqrt(x*x+y*y+z*z+w*w);
    if(mag>0.0)
    {
        mag=1.0f/mag;
        x*= -mag;
        y*= -mag;
        z*= -mag;
        w*= +mag;
        return true;
    }
    return false;
}

bool LQuaternion::isInversable() const
{
    // No Need to sqrt
    return (x*x+y*y+z*z+w*w>0.0f);
}

LQuaternion LQuaternion::lerp(const LQuaternion &_a1, const LQuaternion &_a2, const f32 &_t)
{
    return (((_a2-_a1)*_t)+_a1);
}

void LQuaternion::normalize()
{
    f32 len=getMagnitude();
    if((!lCompareFloat(1.0f,len))&&(!lCompareFloat(0.0f,len)))
    {
        len=1.0f/len;
        x*= len;
        y*= len;
        z*= len;
        w*= len;
    }
}


void LQuaternion::set(const f32 &_x, const f32 &_y, const f32 &_z, const f32 &_w)
{
    x=_x;
    y=_y;
    z=_z;
    w=_w;
}

void LQuaternion::set(const f32 &_x, const f32 &_y, const f32 &_z)
{
    f32 sinx=lSin(_x*0.5f);
    f32 siny=lSin(_y*0.5f);
    f32 sinz=lSin(_z*0.5f);
    f32 cosx=lCos(_x*0.5f);
    f32 cosy=lCos(_y*0.5f);
    f32 cosz=lCos(_z*0.5f);

    x=-(cosx*siny*sinz)+(sinx*cosy*cosz);
    y= (cosx*siny*cosz)+(sinx*cosy*sinz);
    z=-(sinx*siny*cosz)+(cosx*cosy*sinz);
    w= (cosx*cosy*cosz)+(sinx*siny*sinz);
}

void LQuaternion::set(const LMatrix &_in)
{
    // Adapted from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

    f32 t=_in.m11+_in.m22+_in.m33;
    if(t>0.0f)
    {
        f32 s=lSqrt(t+1.0f)*2.0f;
        w=0.25f*s;
        s=1.0f/s;
        x=(_in.m32-_in.m23)*s;
        y=(_in.m13-_in.m31)*s;
        z=(_in.m12-_in.m21)*s;
    }
    else if((_in.m11>_in.m22)&&(_in.m11>_in.m33))
    {
        f32 s=lSqrt(1.0f+_in.m11-_in.m22-_in.m33)*2.0f;
        x=0.25f*s;
        s=1.0f/s;
        w=(_in.m32-_in.m23)*s;
        y=(_in.m12+_in.m21)*s;
        z=(_in.m13+_in.m31)*s;
    }
    else if(_in.m22>_in.m33)
    {
        f32 s=lSqrt(1.0f+_in.m22-_in.m11-_in.m33)*2.0f;
        y=0.25f*s;
        s=1.0f/s;
        w=(_in.m13-_in.m31)*s;
        x=(_in.m12+_in.m21)*s;
        z=(_in.m23+_in.m32)*s;
    }
    else
    {
        f32 s= lSqrt(1.0f+_in.m33-_in.m11-_in.m22)*2.0f;
        z=0.25f*s;
        s=1.0f/s;
        w=(_in.m21-_in.m12)*s;
        x=(_in.m13+_in.m31)*s;
        y=(_in.m23+_in.m32)*s;
    }
}

LQuaternion LQuaternion::slerp(const LQuaternion &_a1, const LQuaternion &_a2, const f32 &_t)
{
    LQuaternion out;
    LQuaternion a1=_a1;
    LQuaternion a2=_a2;

    f32 cosang = a1.getDotProduct(_a2);
    if(cosang<0.0f)
    {
        a1.x=-a1.x;
        a1.y=-a1.y;
        a1.z=-a1.z;
        a1.w=-a1.w;
        cosang=-cosang;
    }
    float key1,key2;
    if(_t>0.9999f)
    {
        key1=1.0f-_t;
        key2=0.0f;
    }
    else
    {
        f32 sinang=1.0f-cosang*cosang;
        f32 ang=lATan2(sinang,cosang);
        f32 oneOverSinAng=1.0f/sinang;

        key1= lSin((1.0f-_t)*ang)*oneOverSinAng;
        key2= lSin(_t*ang)       *oneOverSinAng;
    }

    out.x= a1.x*key1 + a2.x*key2;
    out.y= a1.y*key1 + a2.y*key2;
    out.z= a1.z*key1 + a2.z*key2;
    out.w= a1.w*key1 + a2.w*key2;
    return out;
}

LMatrix LQuaternion::toRotationMatrix() const
{
    f32 x2=2.0f*x*x;
    f32 y2=2.0f*y*y;
    f32 z2=2.0f*z*z;
    f32 xy=2.0f*x*y;
    f32 xz=2.0f*x*z;
    f32 yz=2.0f*y*z;
    f32 wx=2.0f*w*x;
    f32 wy=2.0f*w*y;
    f32 wz=2.0f*w*z;
    LMatrix o;
    o.m11=lRound(1.0f-y2-z2,6);
    o.m12=lRound(xy-wz,6);
    o.m13=lRound(xz+wy,6);
    o.m21=lRound(xy+wz,6);
    o.m22=lRound(1.0f-x2-z2,6);
    o.m23=lRound(yz-wx,6);
    o.m31=lRound(xz-wy,6);
    o.m32=lRound(yz+wx,6);
    o.m33=lRound(1.0f-x2-y2,6);
    return o;
}

f32 &LQuaternion::operator[](u32 i)
{
    //! TO DO : Add assert to i
    return m[i];
}

f32 LQuaternion::operator [](u32 i) const
{
    //! TO DO : Add assert to i
    return m[i];
}

LQuaternion LQuaternion::operator+() const
{
    return (*this);
}

LQuaternion LQuaternion::operator-() const
{
    return LQuaternion(-x,-y,-z,-w);
}

LQuaternion& LQuaternion::operator=(const LQuaternion& _other)
{
    x=_other.x;
    y=_other.y;
    z=_other.z;
    w=_other.w;
    return (*this);
}

bool LQuaternion::operator==(const LQuaternion &_other) const
{
    return (
                lCompareFloat(x,_other.x)&&
                lCompareFloat(y,_other.y)&&
                lCompareFloat(z,_other.z)&&
                lCompareFloat(w,_other.w)
                );
}

bool LQuaternion::operator!=(const LQuaternion &_other) const
{
    return !((*this)==_other);
}

LQuaternion LQuaternion::operator*(const LQuaternion &_other) const
{
    return getCrossProduct(_other);
}

LQuaternion &LQuaternion::operator*=(const LQuaternion &_other)
{
    (*this)=(*this)*_other;
    return (*this);
}

LQuaternion LQuaternion::operator*(const f32 &_scaler) const
{
    return LQuaternion(
                x * _scaler,
                y * _scaler,
                z * _scaler,
                w * _scaler
                );
}

LQuaternion &LQuaternion::operator*=(const f32 &_scaler)
{
    (*this)=(*this)*_scaler;
    return (*this);
}

LQuaternion LQuaternion::operator/(const LQuaternion &_other) const
{
    LQuaternion out=(*this);
    out*=_other.getInversed();
    return out;
}

LQuaternion &LQuaternion::operator/=(const LQuaternion &_other)
{
    (*this)=(*this)/_other;
    return (*this);
}

LQuaternion LQuaternion::operator/(const f32 &_scaler) const
{
    return LQuaternion(
                x / _scaler,
                y / _scaler,
                z / _scaler,
                w / _scaler
                );
}

LQuaternion &LQuaternion::operator/=(const f32 &_scaler)
{
    (*this)=(*this)/_scaler;
    return (*this);
}

LQuaternion LQuaternion::operator+(const LQuaternion &_other) const
{
    return LQuaternion(
                x + _other.x,
                y + _other.y,
                z + _other.z,
                w + _other.w
                );
}

LQuaternion &LQuaternion::operator+=(const LQuaternion &_other)
{
    (*this)=(*this)+_other;
    return (*this);
}

LQuaternion LQuaternion::operator-(const LQuaternion &_other) const
{
    return LQuaternion(
                x - _other.x,
                y - _other.y,
                z - _other.z,
                w - _other.w
                );
}

LQuaternion &LQuaternion::operator-=(const LQuaternion &_other)
{
    (*this)=(*this)-_other;
    return (*this);
}

LNAMESPACE_END
#endif // LQUATERNION_H
