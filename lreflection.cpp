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


LMetaObject::LMetaObject(LString _metatype):
    mMetaType(_metatype)
{
}

LMetaObject::~LMetaObject()
{
    for(u32 i=0;i<mFunctions.getSize();i++)
        delete mFunctions[i];
    for(u32 i=0;i<mProperties.getSize();i++)
        delete mProperties[i];
    for(u32 i=0;i<mEnums.getSize();i++)
        delete mEnums[i];
}

LMetaObject &LMetaObject::addFunction(LFunctionPtr *_f)
{
    mFunctions.pushBack(_f);
    return *this;
}

LMetaObject &LMetaObject::addProperty(LPropertyBase *_f)
{
    mProperties.pushBack(_f);
    return *this;
}

LMetaObject &LMetaObject::addEnum(LEnum *_f)
{
    mEnums.pushBack(_f);
    return *this;
}

LFunctionPtr *LMetaObject::getFunction(void *ptr) const
{
    for(u32 i=0;i<mFunctions.getSize();i++)
        if(ptr==mFunctions[i]->mPointer)
            return mFunctions[i];
    lError(1,LSTR("Function Not found , please be carefull about function pointer"),nullptr);
}

LFunctionPtr *LMetaObject::getFunction(LString fullname) const
{
    for(u32 i=0;i<mFunctions.getSize();i++)
        if(fullname==mFunctions[i]->mFullname)
            return mFunctions[i];
    lError(1,LSTR("Function \"")+fullname+"\" Not found , please be carefull about function name",nullptr);
}

LPropertyBase *LMetaObject::getProperty(LString name) const
{
    for(u32 i=0;i<mProperties.getSize();i++)
        if(name==mProperties[i]->mName)
            return mProperties[i];
    lError(1,LSTR("Property \"")+name+"\" Not found , please be carefull about property name",nullptr);
}

LUniquePointer<LPropertyBase> LMetaObject::getProperty(void *_obj, LString name) const
{
    for(u32 i=0;i<mProperties.getSize();i++)
        if(name==mProperties[i]->mName)
        {
            LUniquePointer<LPropertyBase>o=mProperties[i]->clone();
            o->setObj(_obj);
            return o;
        }
    lError(1,LSTR("Property \"")+name+"\" Not found , please be carefull about property name",nullptr);
}

LEnum *LMetaObject::getEnum(LString name) const
{
    for(u32 i=0;i<mEnums.getSize();i++)
        if(name==mEnums[i]->mEnumName)
            return mEnums[i];
    lError(1,LSTR("Enum \"")+name+"\" Not found , please be carefull about enum name",nullptr);
}

const LVector<LFunctionPtr *> &LMetaObject::getFunctions() const
{
    return mFunctions;
}

const LVector<LPropertyBase *> &LMetaObject::getProperties() const
{
    return mProperties;
}

const LVector<LEnum *> &LMetaObject::getEnums() const
{
    return mEnums;
}




LNAMESPACE_END

