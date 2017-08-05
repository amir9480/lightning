#include "lmathutility.h"
#include <math.h>
LNAMESPACE_BEGIN

const f32 lPi               =3.1415926535897932384626433f;
const f32 lOneByPi          =0.31830988618379067153776753518301f;
const f32 lTwoPi            =6.2831853071795864769252866f;
const f32 lPiOverTwo        =1.57079632679489661923132165f;
const f32 lPiPowTwo         =9.8696044010893586188344904766156f;
const f32 lRadianPerDegree  =0.01745329251994329576923690722222f;
const f32 lDegreePerRadian  =57.295779513082320876798156332941f;

/*!
 * \fa
 * lNaN means Not a Number
 * \endfa
 */
const int& _lnan(){static int o=0x7F800001;return o;}
const f32 lNaN       = *((float*)(&(_lnan())));
/*!
 * \fa
 * lInfinity value
 * \endfa
 */
const int& _linf(){static int o=0x7F800000;return o;}
const f32 lInfinity  = *((float*)(&(_linf())));

f32 LAPI lACos(const f32& _in)
{
    return lRound(acosf(_in)*lDegreePerRadian,6);
}

f64 LAPI lACosD(const f64& _in)
{
    //! ToDo: Get Better Algorith
    return lRoundD(acos(_in)*lDegreePerRadian,6);
}

f32 LAPI lACotan(const f32& _in)
{
    //! ToDo: Get Better Algorith
    return lRound(atanf(1.0f/_in)*lDegreePerRadian,6);
}

f64 LAPI lACotanD(const f64& _in)
{
    return lRoundD(atanf(1.0/_in)*lDegreePerRadian,6);
}

f32 LAPI lASin(const f32& _in)
{
    return lRound(asinf(_in)*lDegreePerRadian,6);
}

f64 LAPI lASinD(const f64& _in)
{
    return lRound(asin(_in)*lDegreePerRadian,6);
}

f32 LAPI lATan(const f32& _in)
{
    return lRound(atanf(_in)*lDegreePerRadian,6);
}

f64 LAPI lATanD(const f64& _in)
{
    return lRound(atan(_in)*lDegreePerRadian,6);
}


f32 lATan2(const f32 &_a, const f32 &_b)
{
    return lRound(atan2f(_a,_b)*lDegreePerRadian,6);
}

f64 lATan2D(const f64 &_a, const f64 &_b)
{
    return lRoundD(atan2(_a,_b)*lDegreePerRadian,6);
}

f32 LAPI lCos(const f32& _in)
{
    return lRound(cosf(_in*lRadianPerDegree),6);
}

f64 LAPI lCosD(const f64& _in)
{
    return lRoundD(cos(_in*lRadianPerDegree),6);
}

f32 lExp(const f32& _in)
{
    return expf(_in);
}

f64 lExpD(const f64& _in)
{
    return exp(_in);
}

f32 lFMod(const f32 &_a, const f32 &_b)
{
    return fmodf(_a,_b);
}

f64 lFModD(const f64 &_a, const f64 &_b)
{
    return fmod(_a,_b);
}

f96 lFModLD(const f64 &_a, const f64 &_b)
{
    return fmodl(_a,_b);
}

f32 lLog(const f32 &_in)
{
    return logf(_in);
}

f64 lLogD(const f64 &_in)
{
    return log(_in);
}

f32 lLog10(const f32 &_in)
{
    return log10f(_in);
}

f64 lLog10D(const f64 &_in)
{
    return log10(_in);
}

f32 LAPI lPow(const f32& _a,const f32& _b)
{
    return powf(_a,_b);
}

f64 LAPI lPowD(const f64& _a,const f64& _b)
{
    return pow(_a,_b);
}

f32 LAPI lSin(const f32& _in)
{
    return lRound(sinf(_in*lRadianPerDegree),6);
}

f64 LAPI lSinD(const f64& _in)
{
    return lRoundD(sin(_in*lRadianPerDegree),6);
}

f32 LAPI lSqrt(const f32& _in,f32 _base)
{
    return powf(_in,1.0f/_base);
}

f64 LAPI lSqrtD(const f64& _in,f64 _base)
{
    return pow(_in,1.0/_base);
}

LNAMESPACE_END

