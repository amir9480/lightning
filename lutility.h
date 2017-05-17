#ifndef LUTILITY_H
#define LUTILITY_H
#include "ldefines.h"
#include "typeinfo.h"

#if LTARGET==LTARGET_DEBUG
template <typename... A> linline void _lunused(A&&...) {}
//! Disable Unused parameter warning
#define         LUNUSED(IN) _lunused(IN)
#else
#define         LUNUSED(IN)
#endif

/*!
 * \def LOVERLOADED_MACRO : using to overload macros by argument count. max allowed argumentst is 30
 *
 * #define TEST1(A1)
 * #define TEST2(A1,A2)
 * #define TEST3(A1,A2,A3)
 *
 * and now you can easily overload this
 * #define TEST(...) LOVERLOADED_MACRO(TEST,__VA_ARGS__)
 */
#define LOVERLOADED_MACRO( _MACRONAME_ ,...) __MACRO( _MACRONAME_ , _COUNTARGS(__VA_ARGS__))(__VA_ARGS__)
#define _COUNTARGS(...) __COUNTARGS((__VA_ARGS__,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __COUNTARGS(ARG) ___COUNTARGS ARG
#define ___COUNTARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,N,...) N
#define __MACRO( name , number) __MACRO2( name , number )
#define __MACRO2( name , number ) __MACRO3( name , number )
#define __MACRO3( name , number ) name##number

#define LCAT( _FIRST , _SECOND ) __MACRO(_FIRST,_SECOND)

#define LVAARGS(...) _COUNTARGS(__VA_ARGS__), __VA_ARGS__

#define LTO_STRING(X) ______TOSTRING1(#X)
#define ______TOSTRING1(X) X

#define LPAR_OPEN (
#define LPAR_CLOSE )
#define LCOMMA ,

////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 *
 * lCallOnStart use this for function that need to be called right on program start before every thing
 *
 * sample:
 *
 * void lCallOnStart()
 * {
 *     cout<<"Hello World"<<endl;
 * }
 *
 * note: function type can not be changed
 * note: function is not a real function ! so you can NOT call it (but there is secret way to do that :D)
 * note: you can define this function multiple times inside a file !
 *
 */
#define lCallOnStart \
static  LCAT(____lcall__,__LINE__)();\
namespace {\
    struct LCAT(_____fake_type_,__LINE__)\
    {\
        LCAT(_____fake_type_,__LINE__)()\
        {\
            LCAT(____lcall__,__LINE__)();\
        }\
    };\
}\
static const LCAT(_____fake_type_,__LINE__) LCAT(____fake_obj,__LINE__);\
static void LCAT(____lcall__,__LINE__)


/*!
 *
 * lCallOnEnd use this for function that need to be called right on program exit.
 *
 * sample:
 *
 * void lCallOnEnd()
 * {
 *     cout<<"Good Bye World"<<endl;
 * }
 *
 * note: if program crash this function will not be called
 * note: function type can not be changed
 * note: function is not a real function ! so you can NOT call it (but there is secret way to do that :D)
 * note: you can define this function multiple times inside a file !
 *
 */
#define lCallOnEnd \
static LCAT(____lcall2__,__LINE__)();\
namespace {\
    struct LCAT(_____fake_type2_,__LINE__)\
    {\
        LCAT(_____fake_type2_,__LINE__)(){}\
        ~ LCAT(_____fake_type2_,__LINE__)()\
        {\
            LCAT(____lcall2__,__LINE__)();\
        }\
    };\
}\
static const LCAT(_____fake_type2_,__LINE__) LCAT(____fake_obj,__LINE__);\
static void LCAT(____lcall2__,__LINE__)

////////////////////////////////////////////////////////////////////////////////////////////////////

#define lHasMember(NAME,FUNCNAME)\
template<typename ____Th,typename __Sign>\
struct NAME\
{\
   template <typename U,U> struct AAA;\
   template <typename A> linline static char Check(AAA<__Sign,&A::FUNCNAME >* in);\
   template <typename A> linline static int Check(...);\
   const static bool value = sizeof(Check<____Th>(0))==sizeof(char);\
};

#define lCallIf(NAME,FUNCNAME)\
template<typename ____Th,typename RT,bool __value>\
struct NAME{\
    template<typename ...ARGS>\
    linline static RT call(____Th in,ARGS... args){return in.FUNCNAME(args...);}\
};\
template<typename ____Th,typename RT>\
struct NAME <____Th,RT,false>{\
    template<typename ...ARGS>\
    linline static RT call(____Th in,ARGS... args){LUNUSED(in);LUNUSED(args...);static RT o;return o;}\
};\
template<typename ____Th,typename RT>\
struct NAME<____Th,RT&,true>{\
    template<typename ...ARGS>\
    linline static RT& call(____Th in,ARGS... args){return in.FUNCNAME(args...);}\
};\
template<typename ____Th,typename RT>\
struct NAME <____Th,RT&,false>{\
    template<typename ...ARGS>\
    linline static RT& call(____Th in,ARGS... args){LUNUSED(in);LUNUSED(args...);static RT o;return o;}\
};\
template<typename ____Th>\
struct NAME<____Th,void,true>{\
    template<typename ...ARGS>\
    linline static void call(____Th in,ARGS... args){in.FUNCNAME(args...);}\
};\
template<typename ____Th>\
struct NAME <____Th,void,false>{\
    template<typename ...ARGS>\
    linline static void call(____Th in,ARGS... args){LUNUSED(in);LUNUSED(args...);}\
};

#define lCaller(NAME,CHECKERNAME,RETURNTYPE,FUNCNAME)\
template<typename ____Th>\
RETURNTYPE NAME(____Th in)\
{\
    return l_call_if_##CHECKERNAME <____Th,RETURNTYPE,l_has_##CHECKERNAME<____Th,RETURNTYPE(____Th::*)()>::value>::call(in);\
}
#define lCallerA(NAME,CHECKERNAME,RETURNTYPE,FUNCNAME,ARGS)\
template<typename ____Th , typename... __args>\
RETURNTYPE NAME(____Th in,__args... ___args)\
{\
    return l_call_if_##CHECKERNAME <____Th,RETURNTYPE,l_has_##CHECKERNAME<____Th,RETURNTYPE(____Th::*) ARGS >::value>::call(in,___args...);\
}



#define lConfigCallIfExist(...) LOVERLOADED_MACRO(_lConfigCallIfExist,__VA_ARGS__)

#define _lConfigCallIfExist3(CHECKNAME,RETURNTYPE,FUNCNAME)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCaller(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME)

#define _lConfigCallIfExist4(CHECKNAME,RETURNTYPE,FUNCNAME,A1)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LPAR_CLOSE)

#define _lConfigCallIfExist5(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LPAR_CLOSE)

#define _lConfigCallIfExist6(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LPAR_CLOSE)

#define _lConfigCallIfExist7(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LPAR_CLOSE)

#define _lConfigCallIfExist8(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LPAR_CLOSE)

#define _lConfigCallIfExist9(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LPAR_CLOSE)

#define _lConfigCallIfExist10(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7 LPAR_CLOSE)

#define _lConfigCallIfExist11(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LPAR_CLOSE)

#define _lConfigCallIfExist12(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LCOMMA A9 LPAR_CLOSE)

#define _lConfigCallIfExist13(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LCOMMA A9 LCOMMA A10 LPAR_CLOSE)

////////////////////////////////////////////////////////////////////////////////////////////////////

#define lCallerConst(NAME,CHECKERNAME,RETURNTYPE,FUNCNAME)\
template<typename ____Th>\
RETURNTYPE NAME(____Th in)\
{\
    return l_call_if_##CHECKERNAME <____Th,RETURNTYPE,l_has_##CHECKERNAME<____Th,RETURNTYPE(____Th::*)()const>::value>::call(in);\
}
#define lCallerAConst(NAME,CHECKERNAME,RETURNTYPE,FUNCNAME,ARGS)\
template<typename ____Th , typename... __args>\
RETURNTYPE NAME(____Th in,__args... ___args)\
{\
    return l_call_if_##CHECKERNAME <____Th,RETURNTYPE,l_has_##CHECKERNAME<____Th,RETURNTYPE(____Th::*) ARGS const>::value>::call(in,___args...);\
}

#define lConfigCallIfExistConst(...) LOVERLOADED_MACRO(_lConfigCallIfExistConst,__VA_ARGS__)

#define _lConfigCallIfExistConst3(CHECKNAME,RETURNTYPE,FUNCNAME)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME)

#define _lConfigCallIfExistConst4(CHECKNAME,RETURNTYPE,FUNCNAME,A1)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerA(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LPAR_CLOSE)

#define _lConfigCallIfExistConst5(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LPAR_CLOSE)

#define _lConfigCallIfExistConst6(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LPAR_CLOSE)

#define _lConfigCallIfExistConst7(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LPAR_CLOSE)

#define _lConfigCallIfExistConst8(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LPAR_CLOSE)

#define _lConfigCallIfExistConst9(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LPAR_CLOSE)

#define _lConfigCallIfExistConst10(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7 LPAR_CLOSE)

#define _lConfigCallIfExistConst11(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LPAR_CLOSE)

#define _lConfigCallIfExistConst12(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LCOMMA A9 LPAR_CLOSE)

#define _lConfigCallIfExistConst13(CHECKNAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCallerAConst(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,LPAR_OPEN A1 LCOMMA A2 LCOMMA A3 LCOMMA A4 LCOMMA A5 LCOMMA A6 LCOMMA A7  LCOMMA A8 LCOMMA A9 LCOMMA A10 LPAR_CLOSE)


#define lCallIfExist(OBJ,CHECKNAME)\
l_caller_##CHECKNAME(OBJ);

#define lCallIfExistA(OBJ,CHECKNAME,...)\
l_caller_##CHECKNAME(OBJ, __VA_ARGS__ );

/*!
 * \def lCallIfExist using to calling an object's method if and only if it was exist .
 * before you call this Macro you need to declare \def lConfigCallIfExist
 *
 * \def lConfigCallIfExist(what you want call it (I thing ID is good so it's "ID"),member function return type , member function name , member fucntion argument types)
 * \def lCallIfExist(Object,ID)
 * \def lCallIfExistA(Object,ID,function arguments)
 *
 * sample:
 * \code{.cpp}
 *
struct A
{
    A& call0(){cout<<"Call0"<<endl;return *this;}
    void call1(int _in){cout<<"Call1 "<<_in<<endl;}
    A& operator +(int _in){cout<<"operator"<<_in<<endl;return *this;}
};

struct B
{

};

//! ( ID , Return Type,Function name , Argument Types...)
lConfigCallIfExist(test1,A&,call0)
lConfigCallIfExist(test2,void,call1,int)
lConfigCallIfExist(test3,A&,operator+ ,int)


int main()
{
    A a;
    B b;
    // (obj,ID)
    lCallIfExist(a,test1);// will call a.call0()
    lCallIfExist(b,test1);// there is not any thing to call

    // (obj,ID,arguments)
    lCallIfExistA(a,test2,12);// will call a.call1(12)
    lCallIfExistA(b,test2,12);// there is not any thing to call

    lCallIfExistA(a,test3,80);// will call a.operator+(80)
    lCallIfExistA(b,test3,80);// there is not any thing to call

    return 0;
}
 *
 * \endcode
 *
 * Additional Options Available with this macro
 * this macro will generate following macros
 *
#define lConfigCallIfExist(CHECKNAME,RETURNTYPE,FUNCNAME,...)\
lHasMember(l_has_##CHECKNAME,FUNCNAME)\
lCallIf(l_call_if_##CHECKNAME,FUNCNAME)\
lCaller(l_caller_##CHECKNAME,CHECKNAME,RETURNTYPE,FUNCNAME,...)
 *
 *
 * this is an example
 *
struct A
{
    void call1(int _in){cout<<"Call1 "<<_in<<endl;}
};

struct B
{

};

lConfigCallIfExist(test1,void,call1,int)


option to check function is exist or not
    l_has_ID<classtype,function pointer type>::value

    ID is same first argument you passed for lConfigCallIfExist

    cout<<l_has_test1<A,void(A::*)(int)>::value<<endl;// will be 1
    cout<<l_has_test1<B,void(B::*)(int)>::value<<endl;// will be 0

option to call a function or not at compile time (NOT runtime check)

l_call_if_ID<Object type,Compile time condition>::call(obj,arguments...)
    ID is same first argument you passed for lConfigCallIfExist

l_call_if_test1<A,1>::call(a,15);// will call  call1(15)
l_call_if_test1<A,0>::call(a,25);// there is nothing to call

and last option is availble is  same call if exist
l_caller_ID(OBJ,ARGS...);

#define lCallIfExist(OBJ,CHECKNAME)\
l_caller_##CHECKNAME(OBJ);

#define lCallIfExistA(OBJ,CHECKNAME,...)\
l_caller_##CHECKNAME(OBJ, __VA_ARGS__ );


NOTE : use lConfigCallIfExistConst instead of lConfigCallIfExist for const functions
sample:
struct A
{
    void test()const{}
};

lConfigCallIfExistConst(has_a,void,test)
 */


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

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

template<typename T1,typename T2>
struct LIsSameType
{
    static const bool value=false;
};

template<typename T1>
struct LIsSameType<T1,T1>
{
    static const bool value=true;
};

//! check is A Derived from B .
//!
//!struct A
//!{
//!};
//!struct B:A
//!{
//!};
//!
//! cout<<lIsDerivedFrom<B,A>::value<<endl; // is true
//!
template <typename A, typename B>
struct lIsDerivedFrom
{
    template <typename _B, typename _A>
    struct ___ltest__
    {
        operator _B*() const;
        operator _A*();
    };
    struct yes{bool a[2];};
    struct no{bool a[1];};
    template <typename T>
    static yes check(A*,T);
    static no check(B*, int);
    static const bool value = LIsSameType<decltype(check(___ltest__<B,A>(), int())),yes>::value;
};

//! type is availble if first parameter was true
template<bool _con,typename T=void>
struct LEnable_If
{
};
template<typename T>
struct LEnable_If<true,T>
{
    typedef T type;
};

//! will returns a unique string for each value type
template<typename __T>
const char* lGetTypeName()
{
    return typeid(__T).name();
}

//! will returns a unique string for each value type
template<typename __T>
const char* lGetTypeName(__T in)
{
    LUNUSED(in);
    return typeid(__T).name();
}

template<typename T>
struct LIsPointer
{
    const static bool value=false;
};

template<typename T>
struct LIsPointer<T*>
{
    const static bool value=true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////


//! force to use move operator instead of copy operator
template<typename T>
linline typename LRemoveReference<T>::type&& lMove(T&& _in)
{
    return static_cast<typename LRemoveReference<T>::type&&>(_in);
}

//! Swap two value
template<typename T>
linline void    lSwap(T& _a,T& _b)
{
    T temp=lMove(_a);
    _a=lMove(_b);
    _b=lMove(temp);
}


//! to check some operators is availabe
//! example lHasOperator::Equal<int>::value is 1 because operator== is available for int
namespace LHasOperator
{
struct _No{bool _m[2];};
template<typename _T1, typename _T2>
inline _No operator== (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator!= (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator> (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator< (const _T1&, const _T2&);

template<typename T1, typename T2=T1>
struct Equal{ const static bool value = !LIsSameType<decltype( *(T1*)(0) == *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct NotEqual{ const static bool value = !LIsSameType<decltype( *(T1*)(0) != *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct Greater{ const static bool value = !LIsSameType<decltype( *(T1*)(0) > *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct Less{ const static bool value = !LIsSameType<decltype( *(T1*)(0) < *(T2*)(0) ),_No>::value;};
}

//! Checkout default constructor is availble or not
template <typename T>
struct LHasDefaultConstructor
{
    struct _No{bool _m[2];};

    template<typename U>
    static decltype(U(),bool()) is(u8);


    template<typename U>
    static _No is(...);

    const static bool value = !LIsSameType<decltype( is<T>(0) ),_No>::value;

};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum LSortType
{
    LSortTypeAscending,
    LSortTypeDescending
};

template<typename T,typename ET>
linline u32 _qs_partitioninc(T& _arr,u32 left,u32 right)
{
    u32 l=left;
    u32 r=right-1;
    ET p=_arr[right];
    while(1)
    {
        while(_arr[l]<p)
            l++;
        while(r>0&&_arr[r]>p)
            r--;
        if(l>=r)
            break;
        else
            lSwap(_arr[l],_arr[r]);
    }
    lSwap(_arr[l],_arr[right]);
    return l;
}

template<typename T>
void lQuickSortInc(T& _arr,u32 _size,u32 left=0)
{
    if(left>=_size||_size<=1)
        return;
    int p=_qs_partitioninc<T,decltype(_arr[0])>(_arr,left,_size-1);
    lQuickSortInc(_arr,p,left);
    lQuickSortInc(_arr,_size,p+1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T,typename ET>
linline u32 _qs_partitiondec(T& _arr,u32 left,u32 right)
{
    u32 l=left;
    u32 r=right-1;
    ET p=_arr[right];
    while(1)
    {
        while(_arr[l]>p)
            l++;
        while(r>0&&_arr[r]<p)
            r--;
        if(l>=r)
            break;
        else
            lSwap(_arr[l],_arr[r]);
    }
    lSwap(_arr[l],_arr[right]);
    return l;
}

template<typename T>
void lQuickSortDec(T& _arr,u32 _size,u32 left=0)
{
    if(left>=_size||_size<=1)
        return;
    int p=_qs_partitiondec<T,decltype(_arr[0])>(_arr,left,_size-1);
    lQuickSortDec(_arr,p,left);
    lQuickSortDec(_arr,_size,p+1);
}



//! function to sort arrays
template<typename T>
void lSort(T& _arr,u32 _size,LSortType _type=LSortType::LSortTypeAscending)
{
    if(_type==LSortTypeAscending)
        lQuickSortInc(_arr,_size);
    else if(LSortTypeDescending)
        lQuickSortDec(_arr,_size);

}

LNAMESPACE_END

#endif // LUTILITY_H
