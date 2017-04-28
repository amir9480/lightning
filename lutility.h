#ifndef LUTILITY_H
#define LUTILITY_H
#include "ldefines.h"

#if LTARGET==LTARGET_DEBUG
//! Disable Unused parameter warning
#define         LUNUSED(IN) (void)IN
#else
#define         LUNUSED(IN)
#endif

#define LOVERLOADED_MACRO( _MACRONAME_ ,...) __MACRO( _MACRONAME_ , _COUNTARGS(__VA_ARGS__))(__VA_ARGS__)
#define _COUNTARGS(...) __COUNTARGS((__VA_ARGS__,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __COUNTARGS(ARG) ___COUNTARGS ARG
#define ___COUNTARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,N,...) N
#define __MACRO( name , number) __MACRO2( name , number )
#define __MACRO2( name , number ) __MACRO3( name , number )
#define __MACRO3( name , number ) name##number

#define LTOSTRING(X) ______TOSTRING1(#X)
#define ______TOSTRING1(X) X

LNAMESPACE_BEGIN

//! remove reference & from type
template <typename T>
struct LRemoveReference
{
    typedef T type;
};
template <typename T>
struct LRemoveReference<T&>
{
    typedef T type;
};
template <typename T>
struct LRemoveReference<T&&>
{
    typedef T type;
};

//! remove pointer * from type
template <typename T>
struct LRemovePointer
{
    typedef T type;
};
template <typename T>
struct LRemovePointer<T*>
{
    typedef T type;
};
template <typename T>
struct LRemovePointer<T**>
{
    typedef T type;
};

//! Swap two value
template<typename T>
linline void    lSwap(T& _a,T& b);


template<typename T>
linline void lSwap(T& _a,T& _b)
{
    T temp=_a;
    _a=_b;
    _b=temp;
}

//! force to use move operator instead of copy operator
template<typename T>
linline typename LRemoveReference<T>::type&& lMove(T&& _in)
{
    return static_cast<typename LRemoveReference<T>::type&&>(_in);
}

LNAMESPACE_END
#endif // LUTILITY_H
