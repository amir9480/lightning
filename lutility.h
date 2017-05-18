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

////////////////////////////////////////////////////////////////////////////////////////////////////







template<typename T>
struct ___fake_return{static T call(){T o;return o;}};
template<>
struct ___fake_return<void>{static void call(){}};

/*!
* how use call if exist.
* first define lConfigCallIfExist( checkID,Function_Return_Type,Function_Name, ARGUMENT_TYPES )
*
* then you can use it like this
* checkID<YourType>::value ; // if YourType has Function_Name with Function_Return_Type return type and ARGUMENT_TYPES argument types . then this will be true
* checkID<YourType>::call(your_object,arguments...);// this will call your_object.Function_Name(arguments...) if exist
*
* note : use lConfigCallIfExistConst instead for const functions
* sample:
*
* struct A
* {
*     void foo(int g)const{cout<<"FOO"<<endl;}
* };
* struct B
* {
*     void foo(int g)const{cout<<"FOO CONST"<<endl;}
* };
* struct C
* {
* };
*
* lConfigCallIfExist(has_foo,void,foo,int)
* lConfigCallIfExistConst(has_foo_const,void,foo,int)
*
* int main()
* {
*     A a;
*     B b;
*     C c;
*     int d;
*     has_foo<A>::call(a,3);// output FOO
*     has_foo<B>::call(b,4);
*     has_foo<C>::call(c,5);
*     has_foo<int>::call(d,6);

*     has_foo_const<A>::call(a,3);
*     has_foo_const<B>::call(b,4);// output FOOCONST
*     has_foo_const<C>::call(c,5);
*     has_foo_const<int>::call(d,6);
*
* }
*/
#define lConfigCallIfExist(...) LOVERLOADED_MACRO(__lConfigCallIfExist,__VA_ARGS__)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist13(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist12(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist11(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist10(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist9(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return __call(CT(),_in,a1,a2,a3,a4,a5,a6);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist8(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return _in.FUNCNAME(a1,a2,a3,a4,a5);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return __call(CT(),_in,a1,a2,a3,a4,a5);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist7(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4){return _in.FUNCNAME(a1,a2,a3,a4);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4){return __call(CT(),_in,a1,a2,a3,a4);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist6(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3){return _in.FUNCNAME(a1,a2,a3);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3){return __call(CT(),_in,a1,a2,a3);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist5(NAME,RETURNTYPE,FUNCNAME,A1,A2)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2){return _in.FUNCNAME(a1,a2);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2){return __call(CT(),_in,a1,a2);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist4(NAME,RETURNTYPE,FUNCNAME,A1)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1){return _in.FUNCNAME(a1);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1){return __call(CT(),_in,a1);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist3(NAME,RETURNTYPE,FUNCNAME)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)()>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in){return _in.FUNCNAME();}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in){return __call(CT(),_in);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define lConfigCallIfExistConst(...) LOVERLOADED_MACRO(__lConfigCallIfExistConst,__VA_ARGS__)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst13(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst12(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst11(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst10(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst9(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return __call(CT(),_in,a1,a2,a3,a4,a5,a6);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst8(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return _in.FUNCNAME(a1,a2,a3,a4,a5);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return __call(CT(),_in,a1,a2,a3,a4,a5);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst7(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4){return _in.FUNCNAME(a1,a2,a3,a4);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4){return __call(CT(),_in,a1,a2,a3,a4);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst6(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3){return _in.FUNCNAME(a1,a2,a3);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3){return __call(CT(),_in,a1,a2,a3);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst5(NAME,RETURNTYPE,FUNCNAME,A1,A2)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2){return _in.FUNCNAME(a1,a2);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2){return __call(CT(),_in,a1,a2);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst4(NAME,RETURNTYPE,FUNCNAME,A1)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1){return _in.FUNCNAME(a1);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1){return __call(CT(),_in,a1);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst3(NAME,RETURNTYPE,FUNCNAME)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)()const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=is_same<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in){return _in.FUNCNAME();}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in){return __call(CT(),_in);}\
};

#endif // LUTILITY_H
