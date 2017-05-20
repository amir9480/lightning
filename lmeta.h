#ifndef LMETA_H
#define LMETA_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"
#include "lstring.h"
#include "lpair.h"
#include "lvariant.h"
#include "lmemorymanager.h"
#include "lmap.h"

#include "stdarg.h"

LNAMESPACE_BEGIN

//! get function argument types as string for validation
template<typename T1,typename... T2>
struct _l_get_types_as_string
{
    static LString get()
    {
        return LSTR(lGetTypeName<T1>())+LSTR(",")+_l_get_types_as_string<T2...>::get();
    }
};

template<typename T1>
struct _l_get_types_as_string<T1>
{
    static LString get()
    {
        return lGetTypeName<T1>();
    }
};

//! get member function argument types as string for validation
template<typename T1,typename... T2>
struct _lm_get_types_as_string
{
    static LString get()
    {
        return LSTR(lGetTypeName<T1>())+LSTR(" , ")+_lm_get_types_as_string<T2...>::get();
    }
};

template<typename T1>
struct _lm_get_types_as_string<T1>
{
    static LString get()
    {
        return lGetTypeName<T1>()+LSTR(",_M_");
    }
};
LString LAPI _l_get_args_names(u32 _count);
LString LAPI _l_get_args_names(u32 _count,const char* _b,...);

//! get function name as string for validation
template<typename... _args_>
linline LString _l_get_func_name(const char* fname,const char* _returntype,_args_... args)
{
    LString o=_returntype;
    o+=LSTR(" ")+fname+"(";
    o+=_l_get_args_names(sizeof...(_args_),args...);
    o+=")";
    o.removeWhiteSpaces();
    return o;
}

//! get member function name as string for validation
template<typename... _args_>
linline LString _l_get_mfunc_name(const char* _classname,const char* fname,const char* _returntype,_args_... args)
{
    LString o=_returntype;
    o+=LSTR(" ")+_classname+"::"+fname+"(";
    o+=_l_get_args_names(sizeof...(_args_),args...);
    o+=")";
    o.removeWhiteSpaces();
    return o;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//! base class for functions pointers
//! how work with LFunctionPointer?
//!
//! how create common function pointer?
//! void testfoo(int _in)
//! {
//!     cout<<"Hello "<<_in<<endl;
//! }
//!
//! //to create function pointer for test foo
//! LFunctionPointer* a=new LFunction<void(*)(int)>("testfoo(int)",&testfoo);
//! // "testfoo(int)" is unique name for your function . you can access it with 'mFullname' field
//! // void(*)(int) is type of pointer to testfoo like   RETURNTYPE(*)(ARGUMENTTYPES...)
//! // max arguments allowed is 10
//!
//! how to call pointer to function?
//! (*a)(12);
//!
//! please make sure your argument values ( types ) is OK and same thing
//!
//!
//! how to call fucntion in native way and safe way
//! (*dynamic_cast<LFunction<void(*)(int)>*>(a))(14);
//!
//! how create pointer to member function?
//!
//! struct A
//! {
//!     void testfoo(int _in)
//!     {
//!         cout<<"Hello "<<mVal<<" "<<_in<<endl;
//!     }
//!     int mVal;
//! };
//!
//! LFunctionPointer* a=new LMemberFunction<void(A::*)(int)>("A::testfoo(int)",&A::testfoo);
//!
//! how to call?
//! A obj;
//! obj.mVal=444;
//! (*a)(obj,123);
//!
//! how call in native way and safe way?
//! (*dynamic_cast<LMemberFunction<void(A::*)(int)>*>(a))(obj,123);
//!
//!
class LAPI LFunctionPointer
{
public:
    LFunctionPointer(LString argtypes, LString fullname,void* _pointer);
    virtual ~LFunctionPointer();
    const LString mArgtypes;
    const LString mFullname;
    const void*   mPointer;


    virtual void operator()(){}
    virtual void operator()(LVariant){}
    virtual void operator()(LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
    virtual void operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////

//! create a pointer to function
template<typename... FT>// FT = Function Type
class LFunction:public LFunctionPointer
{
};

template<typename RT>// RT = Return Type
class LFunction<RT(*)()>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)()):
        LFunctionPointer(LString::empty,_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
    virtual void operator()()
    {
       if(mArgtypes==LString::empty)
          (*mPtrF)();
    }
protected:
    RT(*mPtrF)();
};

template<typename RT,typename A1>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1)):
        LFunctionPointer(_l_get_types_as_string<A1>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
    void operator()(A1 _a1)
    {
        if(mArgtypes==_l_get_types_as_string<A1>::get())
            (*mPtrF)(_a1);
    }
    virtual void operator()(LVariant a1)
    {
        (*mPtrF)(a1.to<A1>());
    }
protected:
    RT(*mPtrF)(A1);
};

template<typename RT,typename A1,typename A2>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2)):
        LFunctionPointer(_l_get_types_as_string<A1,A2>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2>::get())
            (*mPtrF)(_a1,_a2);
    }
    virtual void operator()(LVariant a1,LVariant a2)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>());
    }
protected:
    RT(*mPtrF)(A1,A2);
};

template<typename RT,typename A1,typename A2,typename A3>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3>::get())
            (*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3);

};

template<typename RT,typename A1,typename A2,typename A3,typename A4>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4>::get())
            (*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5,A6>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPointer
{
public:
     LFunction(LString _fullname,RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPointer(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
    }
    virtual void operator()(LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9,LVariant a10)
    {
        (*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>(),a10.to<A10>());
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

//! create pointer to member function
template<typename... FT>// FT = Function Type
class LMemberFunction:public LFunctionPointer
{
};

template<typename OT,typename RT>// RT = Return Type
class LMemberFunction<RT(OT::*)()>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)()):
        LFunctionPointer(LString::empty,_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o)
    {
       if(mArgtypes==LString::empty)
          (_o.*mPtrF)();
    }
    virtual void operator()(LVariant o)
    {
        (o.to<OT>().*mPtrF)();
    }
protected:
    RT(OT::*mPtrF)();
};

template<typename OT,typename RT,typename A1>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1)):
        LFunctionPointer(_lm_get_types_as_string<A1>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1)
    {
        if(mArgtypes==_lm_get_types_as_string<A1>::get())
            (_o.*mPtrF)(_a1);
    }
    virtual void operator()(LVariant o,LVariant a1)
    {
         (o.to<OT>().*mPtrF)(a1.to<A1>());
    }
protected:
    RT(OT::*mPtrF)(A1);
};

template<typename OT,typename RT,typename A1,typename A2>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3);

};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9,LVariant a10)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>(),a10.to<A10>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename OT,typename RT>// RT = Return Type
class LMemberFunction<RT(OT::*)()const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)()const):
        LFunctionPointer(LString::empty,_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o)
    {
       if(mArgtypes==LString::empty)
          (_o.*mPtrF)();
    }
    virtual void operator()(LVariant o)
    {
       (o.to<OT>().*mPtrF)();
    }
protected:
    RT(OT::*mPtrF)()const;
};

template<typename OT,typename RT,typename A1>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1)const):
        LFunctionPointer(_lm_get_types_as_string<A1>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1)
    {
        if(mArgtypes==_lm_get_types_as_string<A1>::get())
            (_o.*mPtrF)(_a1);
    }
    virtual void operator()(LVariant o,LVariant a1)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>());
    }
protected:
    RT(OT::*mPtrF)(A1)const;
};

template<typename OT,typename RT,typename A1,typename A2>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3)const;

};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const;
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>:public LFunctionPointer
{
public:
     LMemberFunction(LString _fullname,RT(OT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const):
        LFunctionPointer(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get(),_fullname,(void*)_Fptr),
        mPtrF(_Fptr)
    {
    }
     void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
    }
    virtual void operator()(LVariant o,LVariant a1,LVariant a2,LVariant a3,LVariant a4,LVariant a5,LVariant a6,LVariant a7,LVariant a8,LVariant a9,LVariant a10)
    {
        (o.to<OT>().*mPtrF)(a1.to<A1>(),a2.to<A2>(),a3.to<A3>(),a4.to<A4>(),a5.to<A5>(),a6.to<A6>(),a7.to<A7>(),a8.to<A8>(),a9.to<A9>(),a10.to<A10>());
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class LAPI LMetaEnumElement
{
    friend class LMetaEnum;
    template<typename U>
    friend class LEnum;
public:
    LMetaEnumElement(const LString& _name,const u64& _value,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        mName(_name),
        mValue(_value),
        mAttributes(_attrs)
    {}
    virtual ~LMetaEnumElement(){}

    LString                         getName()const;

    u64                             getValue()const;

    const LMap<LString,LString>&    getAttributes()const;

    LString                         getAttribute(const LString& _key)const;

    LMetaEnumElement& operator=(const LMetaEnumElement& _other);
protected:
    LString mName;
    u64 mValue;
    LMap<LString,LString> mAttributes;
};

class LAPI LMetaEnum
{
public:
    LMetaEnum(const LString& _name,const LString& _typename,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        mName(_name),
        mTypeName(_typename),
        mAttributes(_attrs)
    {
    }
    virtual ~LMetaEnum()
    {
    }
    //! Add a new element to Meta
    virtual void                    addElement(const LMetaEnumElement& _ni)=0;

    //! Get element struct
    virtual const LMetaEnumElement& getElement(const LString& _other)const=0;

    //! Get element value by name
    virtual u64                     getElementByName(const LString& _other)const=0;

    //! Get element name by value
    virtual LString                 getElementName(const u64& _in)const=0;

    //! Type name of enum
    const LString mName;
    const LString mTypeName;
protected:
    LVector<LMetaEnumElement>   mData;
    const LMap<LString,LString> mAttributes;
};

template<typename T>
class LAPI LEnum:public LMetaEnum
{
public:
    LEnum(const LString& _name,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        LMetaEnum(_name,lGetTypeName<T>(),_attrs)
    {}
    ~LEnum(){}

    void                    addElement(const LMetaEnumElement& _ni);
    const LMetaEnumElement& getElement(const LString& _other)const;
    u64                     getElementByName(const LString &_in) const;
    LString                 getElementName(const u64 &_in) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LMetaProperty
{
    template<typename ClassType,typename VarType>
    friend class LProperty;
public:
    LMetaProperty(const LString& _name,const LString& _type):
        mName(_name),
        mTypeName(_type),
        mObj(nullptr)
    {}
    virtual ~LMetaProperty(){}



    virtual LMetaProperty*  clone()const=0;

    virtual LVariant        get()=0;

    virtual LVariant        getProperty(const LString &_property_name)=0;

    void                    setObject(void* _obj)
    {
        mObj=_obj;
    }

    virtual void            setProperty(const LString& _property_name,const LVariant& _newVal)=0;

    const LString mName;
    const LString mTypeName;
protected:
    void* mObj;
};



template<typename ClassType,typename VarType>
class LProperty:public LMetaProperty
{
public:
    LProperty(const LString& _name,VarType ClassType::*_data,void* _obj=nullptr):
            LMetaProperty(_name,lGetTypeName<ClassType>()),
            mData(_data)
    {
        mObj=_obj;
    }
    virtual ~LProperty(){}

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:
    VarType ClassType::*mData;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void LEnum<T>::addElement(const LMetaEnumElement& _ni)
{
    mData.pushBack(_ni);
}

template<typename T>
const LMetaEnumElement& LEnum<T>::getElement(const LString &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mName==_in)
            return mData[i];
    lError2(1,LSTR("Enum Element ")+_in+" not found");
    return mData[0];
}

template<typename T>
u64 LEnum<T>::getElementByName(const LString &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mName==_in)
            return mData[i].mValue;
    return 0;
}

template<typename T>
LString LEnum<T>::getElementName(const u64 &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mValue==_in)
            return mData[i].mName;
    return LString::empty;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename ClassType,typename VarType>
LMetaProperty* LProperty<ClassType,VarType>::clone() const
{
    LMetaProperty* o = new LProperty<ClassType,VarType>(mName,mData);
    o->mObj=mObj;
    return o;
}

template<typename ClassType,typename VarType>
LVariant LProperty<ClassType,VarType>::get()
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        return o;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType>
LVariant LProperty<ClassType,VarType>::getProperty(const LString &_property_name)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        return o.getProperty(_property_name);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType>
void LProperty<ClassType,VarType>::setProperty(const LString &_property_name, const LVariant &_newVal)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        o.setProperty(_property_name,_newVal);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}



LNAMESPACE_END

#endif // LMETA_H
