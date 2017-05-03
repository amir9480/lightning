#ifndef LMATHUTILITY_H
#define LMATHUTILITY_H
#include "lcore.h"
LNAMESPACE_BEGIN

/*!
 * \file*/
/*!
 * \page lmathutilitynotes
 * \ingroup Math
 * \en
 * All functions in lmathutility like sin and... is based on degree not Radian <br>
 * All function name that ended with D is for working with double prections <br>
 * \enden
 *
 * \fa
 * <br> تمام توابع موجود در این فایل مثل سینوس بر اساس درجه کار میکند نه رادیان
 * <br> ها میباشد double ختم میشود جهت کار با  D تمام توابعی که نامشان به
 * \endfa
 *
 * \code{.cpp}
 * float a=lSin(90.0f);//=1.0f
 * double b=lTanD(45.0f);//=45.0f
 * \endcode
 */

//! Value of PI ~= 3.14
extern const f32 lPi;

//! Value of 1/PI
extern const f32 lOneByPi;

//! Value of 2*PI
extern const f32 lTwoPi;

//! Value of PI/2
extern const f32 lPiOverTwo;

//! Value of Pow(PI,2)
extern const f32 lPiPowTwo;

//! Value of PI/180.0
extern const f32 lRadianPerDegree;

//! Value of 180.0/PI
extern const f32 lDegreePerRadian;


//! Value of Not A Number (NAN)
extern const f32 lNaN;

//! value of +infinity
extern const f32 lInfinity;


//! Compute Absolute of a number
template <typename T>
linline T       lAbs(const T& _in);

//! Compute acos by degree
f32 LAPI        lACos(const f32& _in);
f64 LAPI        lACosD(const f64& _in);

//! Compute acotan by degree
f32 LAPI        lACotan(const f32& _in);
f64 LAPI        lACotanD(const f64& _in);

//! Compute asin by degree
f32 LAPI        lASin(const f32& _in);
f64 LAPI        lASinD(const f64& _in);

//! Compute aTan by degree
f32 LAPI        lATan(const f32& _in);
f64 LAPI        lATanD(const f64& _in);

//! Compute aTan by degree _y/_x
f32 LAPI        lATan2(const f32& _y,const f32& _x);
f64 LAPI        lATan2D(const f64& _y,const f64& _x);

//! Get Up Rounding of value
linline f32     lCeil(const f32& _in);
linline f64     lCeilD(const f64& _in);

//! Compare two float point number with precition limit
linline bool    lCompareFloat(const f32& _a, const f32& _b, const u8& _precision=4);
linline bool    lCompareDouble(const f64& _a, const f64& _b, const u8& _precision=4);

//! Compute cos by degree
f32 LAPI        lCos(const f32& _in);
f64 LAPI        lCosD(const f64& _in);

//! Compute cotan by degree
linline f32     lCotan(const f32& _in);
linline f64     lCotanD(const f64& _in);

//! Get Exp of a value
f32             lExp(const f32& _in);
f64             lExpD(const f64& _in);

//! Compute floor of a float point number
linline f32     lFloor(const f32& _in);
linline f64     lFloorD(const f64& _in);

//! Get Mod of float points
f32             lFMod(const f32& _a,const f32& _b);
f64             lFModD(const f64& _a,const f64& _b);

//! CheckOut FloatPoint is NaN
linline bool    lIsNaN(const f32& _in);
linline bool    lIsNaND(const f64& _in);

//! Get Lerp betweem two float point number .
linline f32     lLerp(const f32& _a,const f32& _b,const f64& _p);
linline f32     lLerpD(const f64& _a,const f64& _b,const f64& _p);

//! Get Limited Angle between -90 and 90
linline f32     lLimitedAngle90(const f32& _angle);

//! Get Limited Angle between -180 and 180
linline f32     lLimitedAngle180(const f32& _angle);

//! Get Logarithm (Naturnal)
f32             lLog(const f32& _in);
f64             lLogD(const f64& _in);

//! Get Logarithm (10)
f32             lLog10(const f32& _in);
f64             lLog10D(const f64& _in);

//! Get Minimum one
template<typename T>
linline T       lMin(const T& _a,const T& _b);

//! Get Maximum one
template<typename T>
linline T       lMax(const T& _a,const T& _b);

//! Get Interger Power
linline i32     lPower(const i32& _a,const u32& _b);

//! Get Float Point Power
f32 LAPI        lPow(const f32& _a,const f32& _b);
f64 LAPI        lPowD(const f64& _a,const f64& _b);

//! Compute round of a float point number
linline f32     lRound(const f32& _in, const u32& _precision=0);
linline f64     lRoundD(const f64& _in,const u32 &_precision=0);

//! Get Sign Value . if x<0 will returns -1 otherwise returns 1
template<typename T>
linline i8      lSign(const T& _x);

//! Compute sin by degree
f32 LAPI        lSin(const f32& _in);
f64 LAPI        lSinD(const f64& _in);

//! Set FloatPoint to NaN
linline void    lSetNaN(f32 &_in);
//! \copydoc lSetNaN
linline void    lSetNaND(f64& _in);

//! sqrt
f32 LAPI        lSqrt(const f32& _in,f32 _base=2);
f64 LAPI        lSqrtD(const f64& _in,f64 _base=2);

//! Compute tan by degree
linline f32     lTan(const f32& _in);
linline f64     lTanD(const f64& _in);

//! Convert radian to degree
linline f32     lToDegree(const f32& _in);

//! Convert degree to radian
linline f32     lToRadian(const f32& _in);

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T lAbs(const T& _in)
{
    if(_in<(T)0)
        return -_in;
    return _in;
}

f32 lCeil(const f32& _in)
{
    return -lFloor(-_in);
}

f64 lCeilD(const f64& _in)
{
    return -lFloorD(-_in);
}

/*!
 * \en
 * \brief Compare two float point number with precition limit
 * \enden
 *
 * \fa
 * \brief مقایسه دو شناور که با محدود کردن تعداد ارقام اعشار
 * \endfa
 * *Example usage of this*
 * \code{.cpp}
 * float p= 31.4f/10.0f;
 * if(p==3.14f)// will be false
 *    ....
 * if(lCompareFloat(p,3.14f,2))// will be true
 *    ....
 * \endcode
 */
bool lCompareFloat(const f32& _a, const f32& _b, const u8& _precision)
{
    return (lAbs(_a-_b)<1.0f/lPower(10,_precision));
}

//! \copydoc lCompareFloat
bool lCompareDouble(const f64& _a, const f64& _b, const u8& _precision)
{
    return (lAbs(_a-_b)<1.0/lPower(10,_precision));
}

f32 lCotan(const f32& _in)
{
    return lCos(_in)/lSin(_in);
}

f64 lCotanD(const f64& _in)
{
    return lCosD(_in)/lSinD(_in);
}

f32 lFloor(const f32& _in)
{
    if(_in>=0.0f)
        return static_cast<f32>(static_cast<i32>(_in));
    return -static_cast<f32>(static_cast<i32>(-_in));
}

f64 lFloorD(const f64& _in)
{
    if(_in>=0.0)
        return static_cast<f32>(static_cast<i32>(_in));
    return -static_cast<f32>(static_cast<i32>(-_in));
}

f32 lLerp(const f32 &_a, const f32 &_b, const f64 &_p)
{
    if(_p>1.0)
        return _b;
    else if(_p<0.0)
        return _a;
    return ((_b-_a)*_p)+_a;
}

f32 lLerpD(const f64 &_a, const f64 &_b, const f64 &_p)
{
    if(_p>1.0)
        return _b;
    else if(_p<0.0)
        return _a;
    return ((_b-_a)*_p)+_a;
}

/*!
 * \en
 * when you send degree angle values to function this will convert it to a value between -90 and 90
 * \enden
 * \fa
 * وقتی که یک زاویه بر حسب درجه به این تابع بفرستید براتون تبدیلش میکنه به یک زاویه بین نود و منفی نود
 * \endfa
 */
f32 lLimitedAngle90(const f32& _angle)
{
    f32 out=_angle;
    while(out<-90.0f)
        out+=180.0f;
    while(out>90.0f)
        out-=180.0f;
    return out;
}

/*!
 * \en
 * when you send degree angle values to function this will convert it to a value between -180 and 180
 * \enden
 * \fa
 * وقتی که یک زاویه بر حسب درجه به این تابع بفرستید براتون تبدیلش میکنه به یک زاویه بین صد و هشتاد  و منفی صد هشتاد
 * \endfa
 * \code
 * float a= lLimitedAngle180(210);// a=-150
 * \endcode
 */
f32 lLimitedAngle180(const f32& _angle)
{
    f32 out=_angle;
    while(out<-180.0f)
        out+=360.0f;
    while(out>180.0f)
        out-=360.0f;
    return out;
}

template<typename T>
T lMin(const T& _a,const T& _b)
{
    return ((_a<_b)? _a:_b);
}

template<typename T>
T lMax(const T& _a,const T& _b)
{
    return ((_a>_b)? _a:_b);
}

bool lIsNaN(const f32& _in)
{
    return !(_in==_in);
}

bool lIsNaND(const f64& _in)
{
    return !(_in==_in);
}

i32 lPower(const i32& _a,const u32& _b)
{
    i32 out=1;
    for(u32 i=0;i<_b;i++)
        out*=_a;
    return out;
}

/*!
 * \en
 * \return rounded float value
 * \enden
 *
 * \fa
 * \return عدد ممیز شناور گرد شده
 * \endfa
 * float p=3.1415;
 * float a=lRound(p);//a=3
 * float b=lRound(p,2);//b=3.14
 */
f32 lRound(const f32& _in, const u32& _precision)
{
    if(_in>=0.0f)
        return (lFloor((_in*lPower(10,_precision))+0.5f)/lPower(10,_precision));
    f32 o=-(lFloor((-_in*lPower(10,_precision))+0.5f)/lPower(10,_precision));
    // Prevent from -0.0f
    if(lCompareFloat(lAbs(o),0.0f,_precision))
        o=0.0f;
    return o;
}

//! \copydoc lRound
f64 lRoundD(const f64& _in, const u32& _precision)
{
    if(_in>=0.0)
        return (lFloorD((_in*lPower(10,_precision))+0.5)/lPower(10,_precision));
    f64 o= -(lFloorD((-_in*lPower(10,_precision))+0.5)/lPower(10,_precision));
    // Prevent from -0.0f
    if(lCompareDouble(lAbs(o),0.0f,_precision))
        o=0.0;
    return o;
}

void lSetNaN(f32& _in)
{
    _in=0.0f/0.0f;
}

void lSetNaND(f64 &_in)
{
    _in=0.0/0.0;
}

template<typename T>
i8 lSign(const T& _x)
{
    return ((_x>0)?1:-1);
}

f32 lTan(const f32& _in)
{
    return lSin(_in)/lCos(_in);
}

f64 lTanD(const f64& _in)
{
    return lSinD(_in)/lCosD(_in);
}

f32 lToDegree(const f32& _in)
{
    return _in*lDegreePerRadian;
}

f32 lToRadian(const f32& _in)
{
    return _in*lRadianPerDegree;
}

LNAMESPACE_END
#endif // LMATHUTILITY_H
