#ifndef LPAIR_H
#define LPAIR_H
#include "ldefines.h"

LNAMESPACE_BEGIN

//! this class using to define a pair .
//! element access names
//! T1      | T2
//! first   | second
//!
//! LPair<int,LString> a;
//! a.first = 12;
//! a.second = "Hello World";
template<typename T1,typename T2>
struct LAPI LPair
{
    LPair(){}
    LPair(const T1& _1,const T2& _2):first(_1),second(_2){}
    LPair(const LPair<T1,T2>& _other)
    {
        first=_other.first;
        second=_other.second;
    }
    LPair(LPair<T1,T2>&& _other)
    {
        first=lMove(_other.first);
        second=lMove(_other.second);
    }
    LPair& operator=(const LPair<T1,T2>& _other)
    {
        first=_other.first;
        second=_other.second;
        return *this;
    }
    LPair& operator=(LPair<T1,T2>&& _other)
    {
        first=lMove(_other.first);
        second=lMove(_other.second);
        return *this;
    }

    T1 first;
    T2 second;
};

LNAMESPACE_END

#endif // LPAIR_H
