#include "lmetaproperty.h"

LNAMESPACE_BEGIN



LMetaAttributes::LMetaAttributes()
{

}

LMetaAttributes::LMetaAttributes(const LMap<LString, LString> &_attrs):
    mAttributes(_attrs)
{

}

LMetaAttributes::~LMetaAttributes()
{

}

void LMetaAttributes::addAttribute(const LString &_name, const LString &_value)
{
    mAttributes[_name]=_value;
}

bool LMetaAttributes::exists(const LString &_name) const
{
    return (mAttributes.findKey(_name)!=LMap<LString,LString>::nothing);
}

LString LMetaAttributes::getAttribute(const LString &_name,const LString& _default) const
{
    if(mAttributes.findKey(_name)!=LMap<LString,LString>::nothing)
        return mAttributes[_name];
    return _default;
}

const LMap<LString, LString>& LMetaAttributes::getAttributes() const
{
    return mAttributes;
}

bool LMetaAttributes::removeAttribute(const LString &_name)
{
    if(mAttributes.findKey(_name)!=LMap<LString,LString>::nothing)
    {
        mAttributes.remove(_name);
        return true;
    }
    return false;
}

bool LMetaAttributes::setAttribute(const LString &_name, const LString &_value)
{
    if(mAttributes.findKey(_name)!=LMap<LString,LString>::nothing)
    {
        mAttributes[_name]=_value;
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

LMetaEnumElement::LMetaEnumElement()
{

}

LMetaEnumElement::LMetaEnumElement(const LString &_name, const i64 &_value):
    mName(_name),
    mValue(_value)
{

}

LMetaEnumElement::LMetaEnumElement(const LString &_name, const i64 &_value, const LMap<LString, LString> &_attrs):
    LMetaAttributes(_attrs),
    mName(_name),
    mValue(_value)
{

}

LMetaEnumElement::~LMetaEnumElement()
{

}

LString LMetaEnumElement::getName() const
{
    return mName;
}

i64 LMetaEnumElement::getValue() const
{
    return mValue;
}




LMetaEnum::LMetaEnum()
{

}

LMetaEnum::LMetaEnum(const LString &_name, const LString &_typename, const LVector<LMetaEnumElement> &_elements):
    mName(_name),
    mTypeName(_typename),
    mElemenets(_elements)
{

}

LMetaEnum::LMetaEnum(const LString &_name, const LString &_typename, const LMap<LString, LString> &_attrs, const LVector<LMetaEnumElement> &_elements):
    LMetaAttributes(_attrs),
    mName(_name),
    mTypeName(_typename),
    mElemenets(_elements)
{

}

LMetaEnum::~LMetaEnum()
{

}

LMetaEnum& LMetaEnum::addElement(const LMetaEnumElement &_element)
{
    mElemenets.pushFront(_element);
    return *this;
}

const LVector<LMetaEnumElement> &LMetaEnum::getElements() const
{
    return mElemenets;
}

LMetaEnumElement &LMetaEnum::getElement(const LString &_name)
{
    static LMetaEnumElement _def;
    for(u32 i=0;i<mElemenets.getSize();i++)
        if(mElemenets[i].getName()==_name)
            return mElemenets[i];
    return _def;
}

LMetaEnumElement &LMetaEnum::getElement(const i64 _val)
{
    static LMetaEnumElement _def;
    for(u32 i=0;i<mElemenets.getSize();i++)
        if(mElemenets[i].getValue()==_val)
            return mElemenets[i];
    return _def;
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
LVector<LMetaEnum> LMetaObjectManager::mEnums;

LMetaObjectManager::LMetaObjectManager()
{

}

LMetaObjectManager::~LMetaObjectManager()
{

}

LMetaEnum &LMetaObjectManager::getMetaEnumByName(const LString &_name)
{
    static LMetaEnum def;
    for(u32 i=0;i<mEnums.getSize();i++)
        if(mEnums[i].getName()==_name)
            return mEnums[i];
    lError2(1,"Enum by name ("+_name+") Not Found");
    return def;
}

LMetaEnum &LMetaObjectManager::getMetaEnumByTypeName(const LString &_tname)
{
    static LMetaEnum def;
    for(u32 i=0;i<mEnums.getSize();i++)
        if(mEnums[i].getTypeName()==_tname)
            return mEnums[i];
    lError2(1,"Enum by type Name ("+_tname+") Not Found");
    return def;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


LMetaProperty::LMetaProperty(const LString &_name, const LString &_typename):
    mName(_name),
    mTypeName(_typename)
{

}

LMetaProperty::LMetaProperty(const LString &_name, const LString &_typename, const LMap<LString, LString> &_attrs):
    LMetaAttributes(_attrs),
    mName(_name),
    mTypeName(_typename)
{

}

LMetaProperty::~LMetaProperty()
{

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

LMetaObject::LMetaObject(const LString &_name, const LString &_typename, const LMap<LString, LString> &_attrs):
    LMetaAttributes(_attrs),
    mName(_name),
    mTypeName(_typename)
{

}

LMetaObject::~LMetaObject()
{
    for(u32 i=0;i<mProperties.getSize();i++)
        delete mProperties[i];
}

LMetaObject &LMetaObject::addProperty(LMetaProperty *_property)
{
    mProperties.pushBack(_property);
    return *this;
}

LString LMetaObject::getTypeName() const
{
    return mTypeName;
}

LMetaProperty *LMetaObject::getProperty(const LString &_name)
{
    for(u32 i=0;i<mProperties.getSize();i++)
        if(mProperties[i]->getName()==_name)
            return mProperties[i];
    return nullptr;
}

LVector<LMetaProperty *> &LMetaObject::getProperties()
{
    return mProperties;
}

LString LMetaObject::getName() const
{
    return mName;
}



LNAMESPACE_END



