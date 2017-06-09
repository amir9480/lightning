#ifndef LVECTOR4_H
#define LVECTOR4_H

#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

/*!
 * \ingroup Math
 *
 * \en
 * \brief Vector 4D class
 * \details This class using to define 4D vectors instead of 3D vectors and recommended for Multiply with matrix
 * \note To convert to 3D vector , all parameter must division on W
 * \enden
 *
 * \fa
 * \brief  کلاس بردار چهاربعدی
 * \details این کلاس برای تعریف بردارهای چهار بعدی به جای سه بعدی استفاده میشود و برای ضرب با ماتریس پیشنهاد میشود
 * \note تقسیم خواهد شد w در پایان تمام مقادیر برای تبدیل به بردار سه بعدی بر مقدار
 * \endfa
 *
 * LVector3(x,y,z) = LVector4(x/w,y/w,z/w,w/w) -> w=1
 *
 * \code{.cpp}
 * LVector4 a(1.0f,2.0f,3.0f);
 * a=a*LMatrix::createTranslationMatrix(LVector3(5.0f,0.0f,0.0f));
 * \endcode
 *
 */
class LAPI LVector4
{
public:
    //! LVector4  Default constructor
    linline                 LVector4();

    //! LVector4 Constructor with scaler value
    linline                 LVector4(const f32& _s);

    //! LVector4 Constructor with 3D vector and \a _w parameter
    linline                 LVector4(const LVector3& p,const f32& _w=1.0f);

    //! \overload
    linline                 LVector4(const f32& _x,const f32& _y,const f32& _z,const f32& _w=1.0f);

    // Copy Constructor
    linline                 LVector4(const LVector4& _other);

    //! Access to vector parameter by index
    linline f32&            at(u32 _i);
    //! \copydoc LVector4::at(u32 _i)
    linline f32             at(u32 _i)const;

    //! set function with 3D vector and \a _w parameter
    linline void            set(const LVector3& p,const f32& _w=1.0f);

    //! \overload
    linline void            set(const f32& _x,const f32& _y,const f32& _z,const f32& _w=1.0f);

    //! set function with scaler value. x=y=z=w= \a _s
    linline void            set(const f32& _s);

    //! Assign Operator
    linline LVector4&       operator=(const LVector4& _other);

    //! Access to vector parameter by index
    linline f32&            operator[](u32 _i);
    //! \copydoc operator[](u32 _i)
    linline f32&            operator()(u32 _i);
    //! \copydoc operator[](u32 _i)
    linline f32             operator[](u32 _i)const;
    //! \copydoc operator[](u32 _i)
    linline f32             operator()(u32 _i)const;

    //! Compare Operator
    linline bool            operator==(const LVector4& _other)const;
    //! Compare Operator
    linline bool            operator!=(const LVector4& _other)const;

    //! Multiply two vecotr
    linline LVector4        operator*(const LVector4& _other)const;
    //! \ref operator*(const LVector4& _other)const
    linline LVector4&       operator*=(const LVector4& _other);

    //! Multiply with scaler
    linline LVector4        operator*(const f32& _scaler)const;
    //! \ref operator*(const f32& _scaler)const
    linline LVector4&       operator*=(const f32& _scaler);
    //! \ref operator*(const f32& _scaler)const
    friend linline LVector4 operator*(const f32 &_a, const LVector4 &_b);

    //! Multiply with matrix
    linline LVector4        operator*(const LMatrix& _other)const;
    //! \ref operator*(const LMatrix& _other)const
    linline LVector4&       operator*=(const LMatrix& _other);

    //! Division operator
    linline LVector4        operator/(const LVector4& _other)const;
    //! \ref operator/(const LVector4& _other)const
    linline LVector4&       operator/=(const LVector4& _other);

    //! scaler Division
    linline LVector4        operator/(const f32& _scaler)const;
    //! \ref operator/(const f32& _scaler)const
    linline LVector4&       operator/=(const f32& _scaler);
    //! \ref operator/(const f32& _scaler)const
    friend linline LVector4 operator/(const f32 &_a, const LVector4 &_b);

    //! Positive Sign
    linline LVector4        operator+()const;
    //! Negetive Sign
    linline LVector4        operator-()const;

    //! Addition
    linline LVector4        operator+(const LVector4& _other)const;
    //! \ref operator+(const LVector4& _other)const
    linline LVector4&       operator+=(const LVector4& _other);
    //! \ref operator+(const LVector4& _other)const
    friend linline LVector4 operator+(const f32 &_a, const LVector4 &_b);

    //! Subtract
    linline LVector4        operator-(const LVector4& _other)const;
    //! \ref operator-(const LVector4& _other)const
    linline LVector4&       operator-=(const LVector4& _other);
    //! \ref operator-(const LVector4& _other)const
    friend linline LVector4 operator-(const f32 &_a, const LVector4 &_b);

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


/*!
 * \en
 * \brief LVector4  Default constructor . x=0,y=0,z=0 and w=1
 * \enden
 *
 * \fa
 * \brief x=0,y=0,z=0,w=1 سازنده پیش فرض با مقدار های
 * \endfa
 */
LVector4::LVector4():
    x(0.0f),
    y(0.0f),
    z(0.0f),
    w(1.0f)
{

}

/*!
 * \en
 * \brief LVector4 Constructor with 3D vector and \a _w parameter
 * \param p  : 3D position
 * \param _w : w parameter .default is 1
 * \enden
 *
 * \fa
 * \brief  \a w سازنده با استفاده از بردار سه بعدی و مقدار
 * \param p  : مکان سه بعدی
 * \param _w : با مقدار پیش فرض 1 w مقدار
 * \endfa
 */
LVector4::LVector4(const LVector3 &p, const f32 &_w):
    x(p.x),
    y(p.y),
    z(p.z),
    w(_w)
{

}

/*!
 * \en
 * \brief LVector4 Constructor with scaler value. x=y=z=w= \a _s
 * \param _s scaler value
 * \enden
 *
 * \fa
 * \brief x=y=z=w= \a _s سازنده با مقدار اسکالر.
 * \param _s مقدار اسکالر
 * \endfa
 */
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

/*!
 * \en
 * \brief Copy Constructor
 * \enden
 *
 * \fa
 * \brief سازنده کپی
 * \endfa
 */
LVector4::LVector4(const LVector4 &_other)
{
    (*this)=_other;
}

/*!
 * \en
 * \brief Access to vector parameter by index
 * \param _i value index and ( 0 <= _i <= 1 )
 * \return will returns when _i (0=x , 1=y , 2=z , w=3)
 * \enden
 *
 * \fa
 * \brief دسترسی به پارامتر بردار با استفاده از نمایه
 * \param _i   ( 0 <= _i <= 1 )   مقدار نمایه که
 * \return (0=x , 1=y , 2=z , w=3) مقدار رو وقتی که ورودی به این ترتیب باشه
 * \endfa
 */
f32& LVector4::at(u32 _i)
{
    lError(_i>3,"f32& LVector4::at(u32 _i): big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

f32 LVector4::at(u32 _i) const
{
    lError(_i>3,"f32& LVector4::at(u32 _i)const: big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

/*!
 * \en
 * \brief set function with 3D vector and \a _w parameter
 * \param p  : 3D position
 * \param _w : w parameter .default is 1
 * \enden
 *
 * \fa
 * \brief \a w تابع ست با استفاده از بردار سه بعدی و مقدار
 * \param p  : مکان سه بعدی
 * \param _w : با مقدار پیش فرض 1 w مقدار
 * \endfa
 */
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

/*!
 * \en
 * \brief set function with scaler value. x=y=z=w= \a _s
 * \param _s scaler value
 * \enden
 *
 * \fa
 * \brief x=y=z=w= \a _s تابع ست با مقدار اسکالر.
 * \param _s مقدار اسکالر
 * \endfa
 */
void LVector4::set(const f32 &_s)
{
    x=y=z=w=_s;
}

/*!
 * \en
 * \brief Assign Operator
 * \enden
 *
 * \fa
 * \brief عملگر کپی
 * \endfa
 */
LVector4 &LVector4::operator=(const LVector4 &_other)
{
    x=_other.x;
    y=_other.y;
    z=_other.z;
    w=_other.w;
    return (*this);
}

/*!
 * \en
 * \brief Access to vector parameter by index
 * \enden
 *
 * \fa
 * \brief دسترسی به پارامتر بردار به کمک نمایه
 * \endfa
 * \sa \ref at
 */
f32& LVector4::operator[](u32 _i)
{
    lError(_i>3,"f32& LVector4::operator[](u32 _i): big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

f32& LVector4::operator()(u32 _i)
{
    lError(_i>3,"f32& LVector4::operator()(u32 _i): big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

f32 LVector4::operator[](u32 _i) const
{
    lError(_i>3,"f32& LVector4::operator[](u32 _i)const: big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

f32 LVector4::operator()(u32 _i) const
{
    lError(_i>3,"f32& LVector4::operator()(u32 _i)const: big value for _i ; must be between [0-3]",m[0]);
    return m[_i];
}

/*!
 * \en
 * \brief Compare Operator
 * \enden
 *
 * \fa
 * \brief عملگر مقایسه
 * \endfa
 */
bool LVector4::operator==(const LVector4 &_other) const
{
    return(
               lCompareFloat(x,_other.x)&&
               lCompareFloat(y,_other.y)&&
               lCompareFloat(z,_other.z)&&
               lCompareFloat(w,_other.w)
           );
}

/*!
 * \en
 * \brief Compare Operator
 * \enden
 *
 * \fa
 * \brief عملگر مقایسه
 * \endfa
 */
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

/*!
 * \en
 * \brief Multiply two vecotr.
 * \note : this IS NOT crossproduct or dotproduct
 * \enden
 *
 * \fa
 * \brief ضرب دو بردار
 * \note : این ضرب خارجی یا ضرب داخلی نمی باشد
 * \endfa
 */
LVector4 LVector4::operator*(const LVector4 &_other) const
{
    LVector4 out=(*this);
    out.x*=_other.x;
    out.y*=_other.y;
    out.z*=_other.z;
    out.w*=_other.w;
    return out;
}

/*!
 * \en
 * \brief Multiply with matrix
 * \enden
 *
 * \fa
 * \brief ضرب در ماتریس
 * \endfa
 */
LVector4 LVector4::operator*(const LMatrix &_other) const
{
    LVector4 out;
    out.x=x*_other.m11+y*_other.m21+z*_other.m31+w*_other.m41;
    out.y=x*_other.m12+y*_other.m22+z*_other.m32+w*_other.m42;
    out.z=x*_other.m13+y*_other.m23+z*_other.m33+w*_other.m43;
    out.w=x*_other.m14+y*_other.m24+z*_other.m34+w*_other.m44;
    return out;
}

/*!
 * \en
 * \brief Multiply with scaler
 * \enden
 *
 * \fa
 * \brief ضرب اسکالر
 * \endfa
 */
LVector4 LVector4::operator*(const f32 &_scaler) const
{
    LVector4 out=(*this);
    out.x*=_scaler;
    out.y*=_scaler;
    out.z*=_scaler;
    out.w*=_scaler;
    return out;
}

/*!
 * \en
 * \brief Division operator
 * \enden
 *
 * \fa
 * \brief تقسیم دو بردار
 * \endfa
 */
LVector4 LVector4::operator/(const LVector4 &_other) const
{
    LVector4 out=(*this);
    out.x/=_other.x;
    out.y/=_other.y;
    out.z/=_other.z;
    out.w/=_other.w;
    return out;
}

/*!
 * \en
 * \brief scaler Division
 * \enden
 *
 * \fa
 * \brief تقسیم اسکالر
 * \endfa
 */
LVector4 LVector4::operator/(const f32 &_scaler) const
{
    LVector4 out=(*this);
    out.x/=_scaler;
    out.y/=_scaler;
    out.z/=_scaler;
    out.w/=_scaler;
    return out;
}

/*!
 * \en
 * \brief Positive Sign
 * \enden
 *
 * \fa
 * \brief علامت مثبت
 * \endfa
 * \return LVecotr4(x,y,z,w)
 */
LVector4 LVector4::operator+() const
{
    return (*this);
}

/*!
 * \en
 * \brief Negetive Sign
 * \enden
 *
 * \fa
 * \brief علامت منفی
 * \endfa
 * \return LVecotr4(-x,-y,-z,-w)
 */
LVector4 LVector4::operator-() const
{
    return LVector4(-x,-y,-z,-w);
}

LVector4::operator LVector3() const
{
    return LVector3(x/w,y/w,z/w);
}

/*!
 * \en
 * \brief Addition
 * \enden
 *
 * \fa
 * \brief جمع
 * \endfa
 */
LVector4 LVector4::operator+(const LVector4 &_other)const
{
    return LVector4(x+_other.x,
                    y+_other.y,
                    z+_other.z,
                    w+_other.w);
}

/*!
 * \en
 * \brief Subtract
 * \enden
 *
 * \fa
 * \brief تفریق
 * \endfa
 */
LVector4 LVector4::operator-(const LVector4 &_other)const
{
    return LVector4(x-_other.x,
                    y-_other.y,
                    z-_other.z,
                    w-_other.w);
}

LNAMESPACE_END

#endif // LVECTOR4_H
