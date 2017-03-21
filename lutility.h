#ifndef LUTILITY_H
#define LUTILITY_H
#include "ldefines.h"

#if LTARGET==LTARGET_DEBUG
//! Disable Unused parameter warning
#define L_UNUSED(IN) (void)IN
#else
#define L_UNUSED(IN)
#endif

LNAMESPACE_BEGIN

//! Swap two value
template<typename T>
linline void lSwap(T& _a,T& b);



template<typename T>
linline void lSwap(T& _a,T& _b)
{
    T temp=_a;
    _a=_b;
    _b=temp;
}

LNAMESPACE_END
#endif // LUTILITY_H
