#ifndef LOBJECT_H
#define LOBJECT_H

#include "ldefines.h"
#include "llog.h"
#include "lmap.h"
#include "lstring.h"
#include "lmetaproperty.h"

LNAMESPACE_BEGIN


class LVariant;

class LObject
{
    L_CLASS(LObject)
public:
    LObject();
    virtual ~LObject();

    //! add a new dynamic property . if _name exists error will happend
    void            addProperty(const LString& _name,LVariant _value=LVariant());

    //! add a new dynamic attribute . if _name exists error will happend
    void            addAttribute(const LString& _name,LVariant _value=LVariant());

    //! add a new dynamic property's attribute
    void            addPropertyAttribute(const LString& _property_name, const LString& _attribute_name, LVariant _value);

    //! get a static or dynamic property by it's name . if does not exists will returns null
    LVariant        getProperty(const LString& _name);

    //! get a static or dynamic attribute by it's name . if does not exists will returns null
    LVariant        getAttribute(const LString& _name);

    //! get a static or dynamic property's attribute .
    LVariant        getPropertyAttribute(const LString& _property_name, const LString& _attribute_name);

    //! check property exists
    bool            hasProperty(const LString& _name);

    //! check attribute exists
    bool            hasAttribute(const LString& _name);

    //! check property's attribute exists or not
    bool            hasPropertyAttribute(const LString &_property_name, const LString &_attribute_name);

    //! remove a dynamic property. if does not exists nothing will happened
    void            removeProperty(const LString& _name);

    //! remove a dynamic attribute. if does not exists nothing will happened
    void            removeAttribute(const LString& _name);

    //! remove a dynamic property's attribute
    void            removePropertyAttribute(const LString &_property_name, const LString &_attribute_name);

    //! set value of a dynamic or static property
    void            setProperty(const LString& _name,LVariant _value);

    //! set value of a dynamic or static attribute
    void            setAttribute(const LString& _name,LVariant _value);

    //! set a dynamic property's attribute . if you change static attribute will effects globally on all this type of object
    void            setPropertyAttribute(const LString &_property_name, const LString &_attribute_name, LVariant _value);

private:
    LMap<LString,LVariant>                  lDynamicProperties;
    LMap<LString,LVariant>                  lDynamicAttributes;
    LMap<LString,LMap<LString,LVariant>>    lDynamicPropertyAttributes;
};

LNAMESPACE_END

#endif // LOBJECT_H
