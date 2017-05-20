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
    u32 _i;
    if((_i=mAttributes.findKey(_key))!=LMap<LString,LString>::nothing)
        return mAttributes.at(_i);
    return LString::empty;
}

LMetaEnumElement &LMetaEnumElement::operator=(const LMetaEnumElement &_other)
{
    mName=_other.mName;
    mValue=_other.mValue;
    mAttributes=_other.mAttributes;
    return *this;
}

const LMap<LString, LString> &LMetaProperty::getAttributes() const
{
    return mAttributes;
}

LString LMetaProperty::getAttribute(const LString &_key) const
{
    u32 _i;
    if((_i=mAttributes.findKey(_key))!=LMap<LString,LString>::nothing)
        return mAttributes.at(_i);
    return LString::empty;
}

void LMetaProperty::setObject(void *_obj)
{
    mObj=_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LMetaObject::LMetaObject(const LString &_name, const LString &_typename):
    mName(_name),
    mTypeName(_typename)
{

}

LMetaObject::~LMetaObject()
{

}

const LMap<LString, LString> &LMetaObject::getAttributes() const
{
    return mAttributes;
}

LString LMetaObject::getAttribute(const LString &_key) const
{
    u32 _i;
    if((_i=mAttributes.findKey(_key))!=LMap<LString,LString>::nothing)
        return mAttributes.at(_i);
    return LString::empty;
}





LNAMESPACE_END

