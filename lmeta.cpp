#include "lmeta.h"

LNAMESPACE_BEGIN


LFunctionPointer::LFunctionPointer(LString argtypes, LString fullname, void *_pointer):
    mArgtypes(argtypes),
    mFullname(fullname.getWithoutWhiteSpaces()),
    mPointer(_pointer)
{

}

LFunctionPointer::~LFunctionPointer()
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

////////////////////////////////////////////////////////////////////////////////////////////////////


LString LMetaEnumElement::getName() const
{
    return mName;
}

u64 LMetaEnumElement::getValue() const
{
    return mValue;
}

const LMap<LString, LString> &LMetaEnumElement::getAttributes() const
{
    return mAttributes;
}

LString LMetaEnumElement::getAttribute(const LString &_key) const
{
    return mAttributes[_key];
}

LMetaEnumElement &LMetaEnumElement::operator=(const LMetaEnumElement &_other)
{
    mName=_other.mName;
    mValue=_other.mValue;
    mAttributes=_other.mAttributes;
    return *this;
}





LNAMESPACE_END

