#ifndef LREFLECTION_H
#define LREFLECTION_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"

#include "stdarg.h"

LNAMESPACE_BEGIN

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
LString _l_get_args_names(u32 _count);
LString _l_get_args_names(u32 _count,const char* _b,...);

template<typename... _args_>
linline LString _l_get_func_name(const char* fname,const char* _returntype,_args_... args)
{
    LString o=_returntype;
    o+=LSTR(" ")+fname+"(";
    o+=_l_get_args_names(sizeof...(_args_),args...);
    o+=")";
    return o;
}

template<typename... _args_>
linline LString _l_get_mfunc_name(const char* _classname,const char* fname,const char* _returntype,_args_... args)
{
    LString o=_returntype;
    o+=LSTR(" ")+_classname+"::"+fname+"(";
    o+=_l_get_args_names(sizeof...(_args_),args...);
    o+=")";
    return o;
}

class LFunctionPtr
{
public:
    LFunctionPtr(LString argtypes, LString fullname);
    virtual ~LFunctionPtr();
    const LString mArgtypes;
    const LString mFullname;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename... FT>// FT = Function Type
class LFunction:public LFunctionPtr
{
};

template<typename RT>// RT = Return Type
class LFunction<RT(*)()>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)()):
        LFunctionPtr(LString::empty,_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()()
    {
       if(mArgtypes==LString::empty)
          (*mPtrF)();
    }
protected:
    RT(*mPtrF)();
};

template<typename RT,typename A1>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1)):
        LFunctionPtr(_l_get_types_as_string<A1>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1)
    {
        if(mArgtypes==_l_get_types_as_string<A1>::get())
            (*mPtrF)(_a1);
    }
protected:
    RT(*mPtrF)(A1);
};

template<typename RT,typename A1,typename A2>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2)):
        LFunctionPtr(_l_get_types_as_string<A1,A2>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2>::get())
            (*mPtrF)(_a1,_a2);
    }
protected:
    RT(*mPtrF)(A1,A2);
};

template<typename RT,typename A1,typename A2,typename A3>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3>::get())
            (*mPtrF)(_a1,_a2,_a3);
    }
protected:
    RT(*mPtrF)(A1,A2,A3);

};

template<typename RT,typename A1,typename A2,typename A3,typename A4>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4>::get())
            (*mPtrF)(_a1,_a2,_a3);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5,A6>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>// RT = Return Type , A1 = argument type 1 and ...
class LFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    linline LFunction(LString _fullname,RT(*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        if(mArgtypes==_l_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
    }
protected:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename... FT>// FT = Function Type
class LMemberFunction:public LFunctionPtr
{
};

template<typename OT,typename RT>// RT = Return Type
class LMemberFunction<RT(OT::*)()>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)()):
        LFunctionPtr(LString::empty,_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o)
    {
       if(mArgtypes==LString::empty)
          (_o.*mPtrF)();
    }
protected:
    RT(OT::*mPtrF)();
};

template<typename OT,typename RT,typename A1>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1)):
        LFunctionPtr(_lm_get_types_as_string<A1>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1)
    {
        if(mArgtypes==_lm_get_types_as_string<A1>::get())
            (_o.*mPtrF)(_a1);
    }
protected:
    RT(OT::*mPtrF)(A1);
};

template<typename OT,typename RT,typename A1,typename A2>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
    }
protected:
    RT(OT::*mPtrF)(A1,A2);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3);

};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename OT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>// RT = Return Type , A1 = argument type 1 and ...
class LMemberFunction<RT(OT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    linline LMemberFunction(LString _fullname,RT(OT::*Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get(),_fullname),
        mPtrF(Fptr)
    {
    }
    linline void operator()(OT &_o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        if(mArgtypes==_lm_get_types_as_string<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
    }
protected:
    RT(OT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename ClassType>
struct LPropertyBase
{
    LPropertyBase(LString _name,LString _type):
        mName(_name),
        mType(_type)
    {
    }
    virtual ~LPropertyBase(){}

    virtual void    fromString(ClassType& _o,const LString _in)=0;
    virtual LString toString(ClassType& _o)const=0;

    const LString mName;
    const LString mType;
};

template<typename ClassType,typename T>
struct LProperty:LPropertyBase<ClassType>
{
    LProperty(LString _name,T ClassType::*_data):
        LPropertyBase<ClassType>(_name,lGetTypeName<T>()),
        mData(_data)
    {
    }
    T& get(ClassType& _o)
    {
        if(dynamic_cast<LPropertyBase<ClassType>*>(this)->mType==lGetTypeName<T>())
            return _o.*mData;
        static T o;
        lWarning(1,"LProperty::get() , type is not correct");
        return o;
    }

    virtual void fromString(ClassType& _o,const LString _in)
    {
        LUNUSED(_in);
        LUNUSED(_o);
        lWarning(1,"LProperty::fromString() , from string is not supported by this type");
    }
    virtual LString toString(ClassType& _o)const
    {
        LUNUSED(_o);
        lWarning(1,"LProperty::toString() , to string is not supported by this type");
        return LString::empty;
    }
protected:
    T ClassType::*mData;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class LMetaObject
{
public:
    LMetaObject(LString _metatype):
        mMetaType(_metatype)
    {
    }
    ~LMetaObject()
    {
        for(u32 i=0;i<mFunctions.getSize();i++)
            delete mFunctions[i];
        for(u32 i=0;i<mProperties.getSize();i++)
            delete mProperties[i];
    }

    LMetaObject& addFunction(LFunctionPtr* _f)
    {
        mFunctions.pushBack(_f);
        return *this;
    }

    LMetaObject& addProperty(LPropertyBase<T>* _f)
    {
        mProperties.pushBack(_f);
        return *this;
    }

    LFunctionPtr* getFunction(LString fullname)
    {
        for(u32 i=0;i<mFunctions.getSize();i++)
            if(fullname==mFunctions[i]->mFullname)
                return mFunctions[i];
        lError(1,LSTR("Function \"")+fullname+"\" Not found , please be carefull about function name",nullptr);
    }

    LPropertyBase<T>* getProperty(LString name)
    {
        for(u32 i=0;i<mProperties.getSize();i++)
            if(name==mProperties[i]->mName)
                return mProperties[i];
        lError(1,LSTR("Property \"")+name+"\" Not found , please be carefull about property name",nullptr);
    }

    const LString mMetaType;
private:
    LVector<LFunctionPtr*>      mFunctions;
    LVector<LPropertyBase<T>*>  mProperties;
};

template<typename T>
struct LMetaObjectManager
{
    static LMetaObject<T>* get()
    {
        lError(1,LSTR("MetaObjectManager is undefined for ")+lGetTypeName<T>(),nullptr);
    }
};


LNAMESPACE_END

#endif // LREFLECTION_H
