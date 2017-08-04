#include "lfunction.h"

LNAMESPACE_BEGIN

LFunction::LFunction(LString _argtypes):
    mArgTypes(_argtypes)
{

}

LFunction::~LFunction()
{

}

const LString LFunction::getArgTypes() const
{
    return mArgTypes;
}

LNAMESPACE_END
