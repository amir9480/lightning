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

void LObject::addAttribute(const LString &_name, LVariant _value)
{
    if( Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).hasAttribute(_name) )
    {
        lError(1,LSTR("Attribute (")+_name+") is alreay exists");
    }
    else
    {
        lError(lDynamicAttributes.findKey(_name) != lDynamicAttributes.nothing,LSTR("Attribute (")+_name+") is alreay exists");
        lDynamicAttributes[_name]=_value;
    }
}

void LObject::addPropertyAttribute(const LString &_property_name, const LString &_attribute_name, LVariant _value)
{
    lError( hasProperty(_property_name)==false ,LSTR("Property (")+_property_name+") Does not exists" );
    LMetaProperty* staticProp = LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_property_name);
    if( staticProp )
    {
        lError(staticProp->hasAttribute(_attribute_name),LSTR("Attribute (")+_attribute_name+") is alreay exists");
    }
    else if( lDynamicPropertyAttributes[_property_name].findKey(_attribute_name) == lDynamicPropertyAttributes.nothing )
        lDynamicPropertyAttributes[_property_name][_attribute_name]= _value;
    else
        lError(1,LSTR("Attribute (")+_attribute_name+") is alreay exists");
}

LVariant LObject::getProperty(const LString &_name)
{
    LMetaProperty* staticProp = LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
        return staticProp->get(LVariant::create(this));
    else if( lDynamicProperties.findKey(_name) != lDynamicProperties.nothing )
        return lDynamicProperties[_name];

    return LVariant();
}

LVariant LObject::getAttribute(const LString &_name)
{
    if( LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).hasAttribute(_name) )
        return LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getAttribute(_name);
    else if( lDynamicAttributes.findKey(_name) != lDynamicAttributes.nothing )
        return lDynamicAttributes[_name];

    return LVariant();
}

LVariant LObject::getPropertyAttribute(const LString &_property_name, const LString &_attribute_name)
{
    lError( hasProperty(_property_name)==false ,LSTR("Property (")+_property_name+") Does not exists" ,LVariant());
    LMetaProperty* staticProp = LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_property_name);
    if( staticProp && staticProp->hasAttribute(_attribute_name))
        return staticProp->getAttribute(_attribute_name);
    else if( lDynamicPropertyAttributes.findKey(_property_name) != lDynamicPropertyAttributes.nothing &&
             lDynamicPropertyAttributes[_property_name].findKey(_attribute_name) != lDynamicPropertyAttributes.nothing )
        return lDynamicPropertyAttributes[_property_name][_attribute_name];

    return LVariant();
}

bool LObject::hasProperty(const LString &_name)
{
    LMetaProperty* staticProp = Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
        return true;
    else if( lDynamicProperties.findKey(_name) != lDynamicProperties.nothing )
        return true;

    return false;
}

bool LObject::hasAttribute(const LString &_name)
{
    LMetaProperty* staticProp = Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
        return true;
    else if( lDynamicAttributes.findKey(_name) != lDynamicAttributes.nothing )
        return true;

    return false;
}

bool LObject::hasPropertyAttribute(const LString &_property_name, const LString &_attribute_name)
{
    if( hasProperty(_property_name)==false )
        return false;
    LMetaProperty* staticProp = LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_property_name);
    if( staticProp && staticProp->hasAttribute(_attribute_name) )
        return true;
    if( lDynamicPropertyAttributes.findKey(_property_name) != lDynamicPropertyAttributes.nothing &&
        lDynamicPropertyAttributes[_property_name].findKey(_attribute_name) != lDynamicPropertyAttributes.nothing )
        return true;

    return false;
}

void LObject::removeProperty(const LString &_name)
{
    lDynamicProperties.remove(_name);
    lDynamicPropertyAttributes.remove(_name);
}

void LObject::removeAttribute(const LString &_name)
{
    lDynamicAttributes.remove(_name);
}

void LObject::removePropertyAttribute(const LString &_property_name, const LString &_attribute_name)
{
    if( lDynamicPropertyAttributes.findKey(_property_name) )
        lDynamicPropertyAttributes[_property_name].remove(_attribute_name);
}

void LObject::setProperty(const LString &_name, LVariant _value)
{
    LMetaProperty* staticProp = Lightning::LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_name);
    if( staticProp )
        staticProp->set(LVariant::create(this),_value);
    else
        lDynamicProperties[_name] = _value;
}

void LObject::setAttribute(const LString &_name, LVariant _value)
{
    if( LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).hasAttribute(_name) )
        LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).setAttribute(_name,_value);
    else
        lDynamicAttributes[_name] = _value;
}

void LObject::setPropertyAttribute(const LString &_property_name, const LString &_attribute_name, LVariant _value)
{
    lError( hasProperty(_property_name)==false ,LSTR("Property (")+_property_name+") Does not exists" );
    LMetaProperty* staticProp = LMetaObjectManager::getMetaObjectByTypeName(__lGetTypeName()).getProperty(_property_name);
    if( staticProp && staticProp->hasAttribute(_attribute_name) )
        staticProp->setAttribute(_attribute_name,_value);
    else
        lDynamicPropertyAttributes[_property_name][_attribute_name] = _value;
}


LNAMESPACE_END
