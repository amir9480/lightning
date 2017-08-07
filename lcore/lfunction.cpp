#include "lfunction.h"

LNAMESPACE_BEGIN

LFunctionPtr::LFunctionPtr(LString _argtypes):
    mArgTypes(_argtypes)
{

}

LFunctionPtr::~LFunctionPtr()
{

}

const LString LFunctionPtr::getArgTypes() const
{
    return mArgTypes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LFunction::LFunction()
{
    mFptr=nullptr;
}

LFunction::LFunction(const LFunction &_other):
    LFunction()
{
    *this = _other;
}

LFunction::LFunction(LFunction &&_other):
    LFunction()
{
    *this = lMove(_other);
}

LFunction::~LFunction()
{
    if(mFptr)
        delete mFptr;
}

LVariant LFunction::call() const
{
   LVariant o;
   if(mFptr)
       o = (*mFptr)();
   return o;
}

LVariant LFunction::operator()() const
{
   LVariant o;
   if(mFptr)
       o = (*mFptr)();
   return o;
}

LFunction &LFunction::operator=(const LFunction &_other)
{
    if(mFptr)
        delete mFptr;
    if(_other.mFptr)
        mFptr = _other.mFptr->clone();
    return *this;
}

LFunction &LFunction::operator=(LFunction &&_other)
{
    if(mFptr)
        delete mFptr;
    mFptr = _other.mFptr;
    _other.mFptr=nullptr;
    return *this;
}

LNAMESPACE_END
