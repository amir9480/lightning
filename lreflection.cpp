#include "lreflection.h"

LNAMESPACE_BEGIN

LFunctionPtr::LFunctionPtr(LString argtypes, LString fullname, void *_pointer):
    mArgtypes(argtypes),
    mFullname(fullname),
    mPointer(_pointer)
{

}

LFunctionPtr::~LFunctionPtr()
{

}

LString _l_get_args_names(u32 _count)
{
    LUNUSED(_count);
    return LString::empty;
}

LString _l_get_args_names(u32 _count,const char* _b,...)
{
    va_list args;
    LString o;
    va_start(args,_b);
    o+=_b;
    for(u32 i=1;i<_count;i++)
    {
        const char* ar=va_arg(args,const char*);
        o+=",";
        o+=ar;
    }
    va_end(args);
    return o;
}




LNAMESPACE_END

