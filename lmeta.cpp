#include "lmeta.h"

LNAMESPACE_BEGIN



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

