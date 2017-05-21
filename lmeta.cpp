#include "lmeta.h"

LNAMESPACE_BEGIN


LMetaEnum::LMetaEnum(const LMetaEnum &_other)
{
    *this=_other;
}

LMetaEnum &LMetaEnum::operator=(const LMetaEnum &_other)
{
    mName=_other.mName;
    mTypeName=_other.mTypeName;
    mData=_other.mData;
    mAttributes=_other.mAttributes;

    return *this;
}

LString LMetaEnum::getName() const
{
    return mName;
}

LString LMetaEnum::getTypeName() const
{
    return mTypeName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


LMetaEnumElement::LMetaProperty(const LMetaEnumElement &_other)
{
    *this=_other;
}

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

////////////////////////////////////////////////////////////////////////////////////////////////////

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

LString LMetaProperty::getName() const
{
    return mName;
}

LString LMetaProperty::getTypeName() const
{
    return mTypeName;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

LMetaObject::LMetaObject(const LString &_name, const LString &_typename):
    mName(_name),
    mTypeName(_typename)
{

}

LMetaObject::LMetaObject(const LMetaObject &_other)
{
    *this=_other;
}

LMetaObject::~LMetaObject()
{
    for(u32 i=0;i<mProperties.getSize();i++)
        if(__lptrlogmanager.isValidPointer(mProperties[i]))
            delete mProperties[i];
}

LMetaObject &LMetaObject::addProperty(LMetaProperty *_property)
{
    mProperties.pushBack(_property);
    return *this;
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

LUniquePointer<LMetaProperty> LMetaObject::getProperty(const LString &_name, void *_obj) const
{
    LMetaProperty* _o=nullptr;
    for(u32 i=0;i<mProperties.getSize();i++)
        if(mProperties[i]->mName==_name)
        {
            _o=mProperties[i]->clone();
            _o->setObject(_obj);
            break;
        }
    return LUniquePointer<LMetaProperty>(_o);
}

const LVector<LMetaProperty *> &LMetaObject::getProperties() const
{
    return mProperties;
}

LString LMetaObject::getName() const
{
    return mName;
}

LString LMetaObject::getTypeName() const
{
    return mTypeName;
}

LMetaObject &LMetaObject::operator=(const LMetaObject &_other)
{
    mName=_other.mName;
    mTypeName=_other.mTypeName;
    mAttributes=_other.mAttributes;


    for(u32 i=0;i<_other.mProperties.getSize();i++)
        mProperties[i]=_other.mProperties[i]->clone();

    return *this;
}






LNAMESPACE_END

