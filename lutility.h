#ifndef LUTILITY_H
#define LUTILITY_H
#include "lcore.h"

#if LTARGET==LTARGET_DEBUG
//! Disable Unused parameter warning
#define         LUNUSED(IN) (void)IN
#else
#define         LUNUSED(IN)
#endif

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
