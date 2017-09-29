#include "lobject.h"
#include "lvariant.h"

LNAMESPACE_BEGIN

LObject::LObject()
{

}

LObject::~LObject()
{

}

void LObject::addProperty(const LString &_name, LVariant _value)
{
    LMetaProperty* staticProp = Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
    {
        lError(1,LSTR("Property (")+_name+") is alreay exists");
    }
    else
    {
        lError(lDynamicProperties.findKey(_name) != lDynamicProperties.nothing,LSTR("Property (")+_name+") is alreay exists");
        lDynamicProperties[_name]=_value;
    }
}

LVariant LObject::getProperty(const LString &_name)
{
    LMetaProperty* staticProp = Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
        return staticProp->get(LVariant::create(this));
    else
    {
        lError(lDynamicProperties.findKey(_name) == lDynamicProperties.nothing ,LSTR("Property (")+_name+") does not exists. so new one will create. please call addProperty before this function to disable warning",LVariant());
        return lDynamicProperties[_name];
    }
    return LVariant();
}

LNAMESPACE_END
