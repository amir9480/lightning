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

/*!
how to create and call non member function:

void sayHello()
{
    cout<<"Hello WOrld "<<endl;
}

LFunctionPtr* a = new LNonMemberFunction<decltype(&sayHello)>(&sayHello);
(*a)();


how to pass arguments to function

void sayHello(LString _name)
{
    cout<<"Hello "<<_name.toUTF8().getData()<<endl;
}


how to use with member functions

struct A
{
    void sayHello()
    {
        cout<<"Hello World"<<endl;
    }
};

LFunctionPtr* a = new LMemberFunction<decltype(&A::sayHello)>(&A::sayHello);
A obj;
(*a)(LVariant::create(obj));// pass Class Object as first parameter

how to get returned value

int sum(int a,int b)
{
   return a+b;
}

LFunctionPtr* a = new LNonMemberFunction<decltype(&sum)>(&sum);
LVariant r = (*a)(4,7);
cout<<r.toInt()<<endl;


 */
class LFunctionPtr
{
public:
    LFunctionPtr(LString _argtypes);
    virtual ~LFunctionPtr();

    const LString           getArgTypes() const;

    virtual LFunctionPtr*   clone()=0;// get a copy

    virtual LVariant        operator()()                                                                                                   {return LVariant();}
    virtual LVariant        operator()(LVariant)                                                                                           {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant)                                                                                  {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant)                                                                         {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant)                                                                {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant)                                                       {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                                              {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                                     {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                            {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)                   {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant)          {return LVariant();}
    virtual LVariant        operator()(LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant,LVariant) {return LVariant();}
protected:
    const LString   mArgTypes;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... FT>
class LNonMemberFunction:public LFunctionPtr
{
};

template<typename RT> // Return Type
class LNonMemberFunction<RT(*)()>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)()):
        LFunctionPtr(__lGetFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
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

template<typename RT,typename A1>
class LNonMemberFunction<RT(*)(A1)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1)):
        LFunctionPtr(__lGetFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1)>(mPtrF);
    }
    LVariant call(A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1>::get())
            o=(*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _a1)
    {
        LVariant o;
        if(_a1.isConverible<A1>())
             o=(*this).call(_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1);
};

template<typename RT,typename A1,typename A2>
class LNonMemberFunction<RT(*)(A1,A2)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2>::get())
            o=(*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2);
};

template<typename RT,typename A1,typename A2,typename A3>
class LNonMemberFunction<RT(*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3>::get())
            o=(*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    LNonMemberFunction(RT(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<RT(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
             o=(*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<> // Return Type
class LNonMemberFunction<void(*)()>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)()):
        LFunctionPtr(__lGetFTypesAsString<void>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
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
class LNonMemberFunction<void(*)(A1)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1)):
        LFunctionPtr(__lGetFTypesAsString<A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1)>(mPtrF);
    }
    LVariant call(A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1>::get())
            (*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _a1)
    {
        LVariant o;
        if(_a1.isConverible<A1>())
             (*this).call(_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1);
};

template<typename A1,typename A2>
class LNonMemberFunction<void(*)(A1,A2)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2>::get())
            (*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2);
};

template<typename A1,typename A2,typename A3>
class LNonMemberFunction<void(*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3>::get())
            (*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3);
};

template<typename A1,typename A2,typename A3,typename A4>
class LNonMemberFunction<void(*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    LNonMemberFunction(void(*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LNonMemberFunction<void(*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant call(A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetFTypesAsString<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
             (*this).call(_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... FT>
class LMemberFunction:public LFunctionPtr
{
};

template<typename CT,typename RT> // Class type,Return Type
class LMemberFunction<RT(CT::*)()>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)()):
        LFunctionPtr(__lGetMFTypesAsString<CT>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
    {
        return new LMemberFunction<RT(CT::*)()>(mPtrF);
    }
    LVariant call(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT>::get())
            o=(_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        LVariant o;
        if(_o.isConverible<CT>())
            o=(*this).call(_o.to<CT&>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)();
};

template<typename CT,typename RT,typename A1>
class LMemberFunction<RT(CT::*)(A1)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1>::get())
            o=(_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1);
};

template<typename CT,typename RT,typename A1,typename A2>
class LMemberFunction<RT(CT::*)(A1,A2)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2>::get())
            o=(_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3>
class LMemberFunction<RT(CT::*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename CT> // Class type,Return Type
class LMemberFunction<void(CT::*)()>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)()):
        LFunctionPtr(__lGetMFTypesAsString<CT>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
    {
        return new LMemberFunction<void(CT::*)()>(mPtrF);
    }
    LVariant call(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT>::get())
            (_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        LVariant o;
        if(_o.isConverible<CT>())
            (*this).call(_o.to<CT&>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)();
};

template<typename CT,typename A1>
class LMemberFunction<void(CT::*)(A1)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1>::get())
            (_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1);
};

template<typename CT,typename A1,typename A2>
class LMemberFunction<void(CT::*)(A1,A2)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2);
};

template<typename CT,typename A1,typename A2,typename A3>
class LMemberFunction<void(CT::*)(A1,A2,A3)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9);
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
};

////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename CT,typename RT> // Class type,Return Type
class LMemberFunction<RT(CT::*)()const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)()const):
        LFunctionPtr(__lGetMFTypesAsString<CT>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
    {
        return new LMemberFunction<RT(CT::*)()const>(mPtrF);
    }
    LVariant call(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT>::get())
            o=(_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        LVariant o;
        if(_o.isConverible<CT>())
            o=(*this).call(_o.to<CT&>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)()const;
};

template<typename CT,typename RT,typename A1>
class LMemberFunction<RT(CT::*)(A1)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1>::get())
            o=(_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1)const;
};

template<typename CT,typename RT,typename A1,typename A2>
class LMemberFunction<RT(CT::*)(A1,A2)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2>::get())
            o=(_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3>
class LMemberFunction<RT(CT::*)(A1,A2,A3)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const;
};

template<typename CT,typename RT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>:public LFunctionPtr
{
public:
    LMemberFunction(RT(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<RT(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            o=(_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
            o=(*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    RT(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename CT> // Class type
class LMemberFunction<void(CT::*)()const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)()const):
        LFunctionPtr(__lGetMFTypesAsString<CT>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr*  clone()
    {
        return new LMemberFunction<void(CT::*)()const>(mPtrF);
    }
    LVariant call(CT& _o)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT>::get())
            (_o.*mPtrF)();
        return o;
    }
    virtual LVariant operator()(LVariant _o)
    {
        LVariant o;
        if(_o.isConverible<CT>())
            (*this).call(_o.to<CT&>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)()const;
};

template<typename CT,typename A1>
class LMemberFunction<void(CT::*)(A1)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1>::get())
            (_o.*mPtrF)(_a1);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1)const;
};

template<typename CT,typename A1,typename A2>
class LMemberFunction<void(CT::*)(A1,A2)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2>::get())
            (_o.*mPtrF)(_a1,_a2);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2)const;
};

template<typename CT,typename A1,typename A2,typename A3>
class LMemberFunction<void(CT::*)(A1,A2,A3)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3>::get())
            (_o.*mPtrF)(_a1,_a2,_a3);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const;
};

template<typename CT,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
class LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>:public LFunctionPtr
{
public:
    LMemberFunction(void(CT::*_Fptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const):
        LFunctionPtr(__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get()),
        mPtrF(_Fptr)
    {
    }
    virtual LFunctionPtr* clone()
    {
        return new LMemberFunction<void(CT::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(mPtrF);
    }
    LVariant call(CT& _o,A1 _a1,A2 _a2,A3 _a3,A4 _a4,A5 _a5,A6 _a6,A7 _a7,A8 _a8,A9 _a9,A10 _a10)
    {
        LVariant o;
        if(mArgTypes==__lGetMFTypesAsString<CT,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10>::get())
            (_o.*mPtrF)(_a1,_a2,_a3,_a4,_a5,_a6,_a7,_a8,_a9,_a10);
        return o;
    }
    virtual LVariant operator()(LVariant _o,LVariant _a1,LVariant _a2,LVariant _a3,LVariant _a4,LVariant _a5,LVariant _a6,LVariant _a7,LVariant _a8,LVariant _a9,LVariant _a10)
    {
        LVariant o;
        if(_o.isConverible<CT>()&&_a1.isConverible<A1>()&&_a2.isConverible<A2>()&&_a3.isConverible<A3>()&&_a4.isConverible<A4>()&&_a5.isConverible<A5>()&&_a6.isConverible<A6>()&&_a7.isConverible<A7>()&&_a8.isConverible<A8>()&&_a9.isConverible<A9>()&&_a10.isConverible<A10>())
            (*this).call(_o.to<CT&>(),_a1.to<A1>(),_a2.to<A2>(),_a3.to<A3>(),_a4.to<A4>(),_a5.to<A5>(),_a6.to<A6>(),_a7.to<A7>(),_a8.to<A8>(),_a9.to<A9>(),_a10.to<A10>());
        else
            lError2(1,"Can not call function because of function argument types mismatch");
        return o;
    }
private:
    void(CT::*mPtrF)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const;
};








////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*!

this class using to hold functions

how to create and call non member function?
void sayHello()
{
   cout<<"Hello World"<<endl;
}

LFunction a=LFunction::create(&sayHello);
a();

or

LFunction a;
a=&sayHello;
a();

how to pass parameter to function

void sayHello(LString _name)
{
   cout<<"Hello "<<_name.toUTF8().getData()<<endl;
}

LFunction a=LFunction::create(&sayHello);
a("Lightning");

how to get what returns

int sum(int a,int b)
{
   return a+b;
}

LFunction a=LFunction::create(&sum);
LVariant v = a(4,5);
cout<<v.toInt()<<endl;

how to create and call member functions?
struct A
{
    void sayHello()
    {
        cout<<"Hello World"<<endl;
    }
};

LFunction a=LFunction::create(&A::sayHello);
A obj;
a(obj);// pass class/struct object as first parameter

*/
class LFunction
{
public:
    LFunction();
    LFunction(const LFunction& _other);
    LFunction(LFunction&& _other);
    virtual ~LFunction();

    LVariant        call()const;
    template<typename... Args>
    LVariant        call(Args... _args)const;

    template<typename FT>
    static LFunction   create(FT _in);

    LFunction&      operator=(const LFunction& _other);
    LFunction&      operator=(LFunction&& _other);

    template<typename RT>
    LFunction&      operator=(RT(*_fptr)());
    template<typename RT,typename... Args>
    LFunction&      operator=(RT(*_fptr)(Args...));
    template<typename RT,typename CT>
    LFunction&      operator=(RT(CT::*_fptr)());
    template<typename RT,typename CT,typename... Args>
    LFunction&      operator=(RT(CT::*_fptr)(Args...));
    template<typename RT,typename CT>
    LFunction&      operator=(RT(CT::*_fptr)()const);
    template<typename RT,typename CT,typename... Args>
    LFunction&      operator=(RT(CT::*_fptr)(Args...)const);


    LVariant        operator()()const;
    template<typename... Args>
    LVariant        operator()(Args... _args)const;


private:
    LFunctionPtr* mFptr;
};

template<typename... Args>
LVariant LFunction::call(Args... _args)const
{
    LVariant o;
    o = (*mFptr)({LVariant::create(_args)...});
    return o;
}

template<typename FT>
LFunction LFunction::create(FT _in)
{
    LFunction o;
    o = _in;
    return o;
}


template<typename RT>
LFunction &LFunction::operator=(RT(*_fptr)())
{
    if(mFptr)
        delete mFptr;
    mFptr = new LNonMemberFunction<RT(*)()>(_fptr);
    return *this;
}

template<typename RT,typename... Args>
LFunction &LFunction::operator=(RT(*_fptr)(Args...))
{
    if(mFptr)
        delete mFptr;
    mFptr = new LNonMemberFunction<RT(*)(Args...)>(_fptr);
    return *this;
}

template<typename RT,typename CT>
LFunction &LFunction::operator=(RT(CT::*_fptr)())
{
    if(mFptr)
        delete mFptr;
    mFptr = new LMemberFunction<RT(CT::*)()>(_fptr);
    return *this;
}

template<typename RT,typename CT,typename... Args>
LFunction &LFunction::operator=(RT(CT::*_fptr)(Args...))
{
    if(mFptr)
        delete mFptr;
    mFptr = new LMemberFunction<RT(CT::*)(Args...)>(_fptr);
    return *this;
}

template<typename RT,typename CT>
LFunction &LFunction::operator=(RT(CT::*_fptr)()const)
{
    if(mFptr)
        delete mFptr;
    mFptr = new LMemberFunction<RT(CT::*)()const>(_fptr);
    return *this;
}

template<typename RT,typename CT,typename... Args>
LFunction &LFunction::operator=(RT(CT::*_fptr)(Args...)const)
{
    if(mFptr)
        delete mFptr;
    mFptr = new LMemberFunction<RT(CT::*)(Args...)const>(_fptr);
    return *this;
}




template<typename... Args>
LVariant LFunction::operator()(Args... _args)const
{
    LVariant o;
    if(mFptr)
        o = (*mFptr)(LVariant::create(_args)...);
    return o;
}


LNAMESPACE_END

#endif // LFunction_H
