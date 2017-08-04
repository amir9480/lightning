#ifndef LFUNCTION_H
#define LFUNCTION_H

#include "ldefines.h"
#include "lmemory.h"
#include "lstring.h"
#include "lutility.h"
#include "llog.h"
#include "lvariant.h"

LNAMESPACE_BEGIN

template<typename T1,typename... T2>
struct __lGetFTypesAsString // Get Function Argument Types as string
{
    static LString get()
    {
        return lGetTypeName<T1>()+LSTR(",")+__lGetFTypesAsString<T2...>::get();
    }
};
template<typename T1>
struct __lGetFTypesAsString<T1>
{
    static LString get()
    {
        return lGetTypeName<T1>();
    }
};

template<typename T1,typename... T2>
struct __lGetMFTypesAsString// Get Member Function Argument Types as string
{
    static LString get()
    {
        return lGetTypeName<T1>()+LSTR(",")+__lGetMFTypesAsString<T2...>::get();
    }
};
template<typename T1>
struct __lGetMFTypesAsString<T1>
{
    static LString get()
    {
        return lGetTypeName<T1>()+LSTR(",_M");
    }
};


class LFunction
{
public:
    LFunction(LString _argtypes);
    virtual ~LFunction();

    const LString       getArgTypes() const;

    virtual LFunction*  clone()=0;// get a copy

    virtual LVariant    operator()()                                                                                                   {return LVariant();}
    virtual LVariant    operator()(LVariant)                                                                                           {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant)                                                                                  {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant)                                                                         {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant)                                                                {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant)                                                       {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                                              {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                                     {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                            {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                   {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)          {return LVariant();}
    virtual LVariant    operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant) {return LVariant();}
protected:
    const LString   mArgTypes;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... FT>
class LNonMemberFunction:public LFunction
{
};

template<typename RT> // Return Type
class LNonMemberFunction<RT(*)()>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)()):
        LFunction(__lGetFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LNonMemberFunction<RT(*)()>(mPtrF);
    }
    virtual LVariant operator()()
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<void>::get())
            o=(*mPtrF)();
        return o;
    }
private:
    RT(*mPtrF)();
};

template<typename RT,typename A1> // Return Type, ArgType1
class LNonMemberFunction<RT(*)(A1)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1)):
        LFunction(__lGetFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1)>(mPtrF);
    }
    LVariant operator()(A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1>::get())
            o=(*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _a1)
    {
        return (*this)(_a1.to<A1>());
    }
private:
    RT(*mPtrF)(A1);
};

template<typename RT,typename A1,typename A2>
class LNonMemberFunction<RT(*)(A1,A2)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2)):
        LFunction(__lGetFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2>::get())
            o=(*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>());
    }
private:
    RT(*mPtrF)(A1,A2);
};

template<typename RT,typename A1,typename A2,typename A3>
class LNonMemberFunction<RT(*)(A1,A2,A3)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3)):
        LFunction(__lGetFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3>::get())
            o=(*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    RT(*mPtrF)(A1,A2,A3);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunction
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
class LNonMemberFunction<void(*)()>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)()):
        LFunction(__lGetFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LNonMemberFunction<void(*)()>(mPtrF);
    }
    virtual LVariant operator()()
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<void>::get())
            (*mPtrF)();
        return o;
    }
private:
    void(*mPtrF)();
};

template<typename A1>
class LNonMemberFunction<void(*)(A1)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1)):
        LFunction(__lGetFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1)>(mPtrF);
    }
    LVariant operator()(A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1>::get())
            (*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _a1)
    {
        return (*this)(_a1.to<A1>());
    }
private:
    void(*mPtrF)(A1);
};

template<typename A1,typename A2>
class LNonMemberFunction<void(*)(A1,A2)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2)):
        LFunction(__lGetFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2>::get())
            (*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>());
    }
private:
    void(*mPtrF)(A1,A2);
};

template<typename A1,typename A2,typename A3>
class LNonMemberFunction<void(*)(A1,A2,A3)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3)):
        LFunction(__lGetFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3>::get())
            (*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    void(*mPtrF)(A1,A2,A3);
};

template<typename A1,typename A2,typename A3,typename A4>
class LNonMemberFunction<void(*)(A1,A2,A3,A4)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunction
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunction(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant operator()(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... FT>
class LMemberFunction:public LFunction
{
};

template<typename CT,typename RT> // Class type,Return Type
class LMemberFunction<RT(CT::*)()>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)()):
        LFunction(__lGetMFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LMemberFunction<RT(CT::*)()>(mPtrF);
    }
    LVariant operator()(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<void>::get())
            o=(_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        return (*this)(_o.to<CT&>());
    }
private:
    RT(CT::*mPtrF)();
};

template<typename CT,typename RT,typename A1> // Class type, Return Type, ArgType1
class LMemberFunction<RT(CT::*)(A1)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1)):
        LFunction(__lGetMFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1>::get())
            o=(_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>());
    }
private:
    RT(CT::*mPtrF)(A1);
};

template<typename CT,typename RT,typename A1,typename A2>
class LMemberFunction<RT(CT::*)(A1,A2)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2)):
        LFunction(__lGetMFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2>::get())
            o=(_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
    }
private:
    RT(CT::*mPtrF)(A1,A2);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3>
class LMemberFunction<RT(CT::*)(A1,A2,A3)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename CT,typename RT> // Class type,Return Type
class LMemberFunction<RT(CT::*)()const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)()const):
        LFunction(__lGetMFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LMemberFunction<RT(CT::*)()const>(mPtrF);
    }
    LVariant operator()(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<void>::get())
            (_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        return (*this)(_o.to<CT&>());
    }
private:
    RT(CT::*mPtrF)()const;
};

template<typename CT,typename RT,typename A1> // Class type, Return Type, ArgType1
class LMemberFunction<RT(CT::*)(A1)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1)const):
        LFunction(__lGetMFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1>::get())
            (_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>());
    }
private:
    RT(CT::*mPtrF)(A1)const;
};

template<typename CT,typename RT,typename A1,typename A2>
class LMemberFunction<RT(CT::*)(A1,A2)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2)const):
        LFunction(__lGetMFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2>::get())
            o=(_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
    }
private:
    RT(CT::*mPtrF)(A1,A2)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3>
class LMemberFunction<RT(CT::*)(A1,A2,A3)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>:public LFunction
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename CT> // Class type
class LMemberFunction<void(CT::*)()>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)()):
        LFunction(__lGetMFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LMemberFunction<void(CT::*)()>(mPtrF);
    }
    LVariant operator()(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<void>::get())
            (_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        return (*this)(_o.to<CT&>());
    }
private:
    void(CT::*mPtrF)();
};

template<typename CT,typename A1> // Class type, ArgType1
class LMemberFunction<void(CT::*)(A1)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1)):
        LFunction(__lGetMFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1>::get())
            (_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>());
    }
private:
    void(CT::*mPtrF)(A1);
};

template<typename CT,typename A1,typename A2>
class LMemberFunction<void(CT::*)(A1,A2)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2)):
        LFunction(__lGetMFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2>::get())
            o=(_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
    }
private:
    void(CT::*mPtrF)(A1,A2);
};

template<typename CT,typename A1,typename A2,typename A3>
class LMemberFunction<void(CT::*)(A1,A2,A3)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename CT> // Class type
class LMemberFunction<void(CT::*)()const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)()const):
        LFunction(__lGetMFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction*  clone()
    {
        return new LMemberFunction<void(CT::*)()const>(mPtrF);
    }
    LVariant operator()(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<void>::get())
            (_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        return (*this)(_o.to<CT&>());
    }
private:
    void(CT::*mPtrF)()const;
};template<typename CT,typename A1>
class LMemberFunction<void(CT::*)(A1)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1)const):
        LFunction(__lGetMFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1>::get())
            (_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>());
    }
private:
    void(CT::*mPtrF)(A1)const;
};

template<typename CT,typename A1,typename A2>
class LMemberFunction<void(CT::*)(A1,A2)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2)const):
        LFunction(__lGetMFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
    }
private:
    void(CT::*mPtrF)(A1,A2)const;
};

template<typename CT,typename A1,typename A2,typename A3>
class LMemberFunction<void(CT::*)(A1,A2,A3)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>:public LFunction
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const):
        LFunction(__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunction* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(mPtrF);
    }
    LVariant operator()(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        return (*this)(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const;
};








LNAMESPACE_END

#endif // LFUNCTION_H
