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

    void        addProperty(const LString& _name,LVariant _value=LVariant());

    LVariant    getProperty(const LString& _name);

private:
    LMap<LString,LVariant>      lDynamicProperties;
};

LNAMESPACE_END

#endif // LOBJECT_H
