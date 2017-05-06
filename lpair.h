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
struct LPair
{
    T1 first;
    T2 second;

};

LNAMESPACE_END

#endif // LPAIR_H
