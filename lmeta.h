#ifndef LMETA_H
#define LMETA_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"
#include "lstring.h"
#include "lpair.h"
#include "lvariant.h"
#include "lmap.h"
#include "lmemorymanager.h"

LNAMESPACE_BEGIN



////////////////////////////////////////////////////////////////////////////////////////////////////
class LAPI LMetaEnumElement
{
    friend class LMetaEnum;
    template<typename U>
    friend class LEnum;
public:
    LMetaEnumElement(){}
    LMetaEnumElement(const LString& _name,const u64& _value,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        mName(_name),
        mValue(_value),
        mAttributes(_attrs)
    {}
    LMetaProperty(const LMetaEnumElement& _other);
    virtual ~LMetaEnumElement(){}

    //! Get Name of this enum element
    LString                         getName()const;

    //! Get Value of this enum element
    u64                             getValue()const;

    //! Get Custom properties that attached on this meta enum element
    const LMap<LString,LString>&    getAttributes()const;

    //! Get Custom property that attached on this meta enum element by name
    LString                         getAttribute(const LString& _key)const;


    LMetaEnumElement& operator=(const LMetaEnumElement& _other);

protected:
    LString mName;
    u64 mValue;
    LMap<LString,LString> mAttributes;
};

//! a class to hold Attributes about enums
class LAPI LMetaEnum
{
public:
    LMetaEnum(){}
    LMetaEnum(const LString& _name,const LString& _typename,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        mName(_name),
        mTypeName(_typename),
        mAttributes(_attrs)
    {
    }
    LMetaEnum(const LMetaEnum& _other);
    virtual ~LMetaEnum()
    {
    }
    //! Add a new element to Meta
    virtual void                    addElement(const LMetaEnumElement& _ni)=0;

    //! Get element struct
    virtual const LMetaEnumElement& getElement(const LString& _other)const=0;

    //! Get element value by name
    virtual u64                     getElementByName(const LString& _other)const=0;

    //! Get element name by value
    virtual LString                 getElementName(const u64& _in)const=0;

    //! Type name of enum
    LString                         getName() const;

    //! Get TypeName of enum
    LString                         getTypeName() const;


    LMetaEnum&                      operator=(const LMetaEnum& _other);
protected:
    LString                     mName;
    LString                     mTypeName;
    LVector<LMetaEnumElement>   mData;
    LMap<LString,LString>       mAttributes;
};

template<typename T>
class LAPI LEnum:public LMetaEnum
{
public:
    LEnum(const LString& _name,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        LMetaEnum(_name,lGetTypeName<T>(),_attrs)
    {}
    ~LEnum(){}

    void                    addElement(const LMetaEnumElement& _ni);
    const LMetaEnumElement& getElement(const LString& _other)const;
    u64                     getElementByName(const LString &_in) const;
    LString                 getElementName(const u64 &_in) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//! a class to hold attributes about class fields
class LAPI LMetaProperty
{
    template<typename ClassType,typename VarType>
    friend class LProperty;
    template<typename ClassType,typename VarType,typename GetterType>
    friend class LPropertyWithGet;
    template<typename ClassType,typename VarType,typename SetterType>
    friend class LPropertyWithSet;
    template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
    friend class LPropertyWithGetSet;
    friend class LMetaObject;
public:
    LMetaProperty(){}
    LMetaProperty(const LString& _name,const LString& _type,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
        mName(_name),
        mTypeName(_type),
        mObj(nullptr),
        mAttributes(_attrs)
    {}
    virtual ~LMetaProperty(){}

    //! get copy of this . \warning ***** Dont forget delete what returns after you jub done *****
    virtual LMetaProperty*          clone()const=0;

    //! Get Value of this . object must be availble . use setObject to set Object !!!
    virtual LVariant                get()=0;

    //! Get Custom properties that attached on this meta property
    const LMap<LString,LString>&    getAttributes()const;

    //! Get Custom property that attached on this meta property by name
    LString                         getAttribute(const LString& _key)const;

    //! Get Property of this Property by name . (this will work if type also is your custom class and _NEEDED_ function was availble . see LVariant for more details)
    virtual LVariant                getProperty(const LString &_property_name)=0;

    //! Value of this property if object was availble
    virtual void                    set(LVariant _in)=0;

    //! set object of this property to do jobs like set and get
    void                            setObject(void* _obj);

    //! set Property of this
    virtual void                    setProperty(const LString& _property_name,const LVariant& _newVal)=0;

    //! Get name of this Meta Property
    LString                         getName() const;

    //! Get typename of this meta property
    LString                         getTypeName() const;

protected:
    LString                 mName;
    LString                 mTypeName;
    void*                   mObj;
    LMap<LString,LString>   mAttributes;
};


//! this using for public fields with out any setter/getter functions
template<typename ClassType,typename VarType>
class LAPI LProperty:public LMetaProperty
{
public:
    LProperty(const LString& _name,VarType ClassType::*_data,void* _obj=nullptr,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
            LMetaProperty(_name,lGetTypeName<VarType>(),_attrs),
            mData(_data)
    {
        mObj=_obj;
    }
    virtual ~LProperty(){}

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            set(LVariant _in);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:
    VarType ClassType::*mData;
};


//! this using for Private properties without any setter/getter   (just holds name of field  (-_-)  )
template<typename ClassType,typename VarType>
class LAPI LPrivateProperty:public LMetaProperty
{
public:
    LPrivateProperty(const LString& _name,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
            LMetaProperty(_name,lGetTypeName<VarType>(),_attrs)
    {
    }
    virtual ~LPrivateProperty(){}

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual void            set(LVariant _in);
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:

};


//! this using for (public/private) fields that only have getter function for that
template<typename ClassType,typename VarType,typename GetterType>
class LAPI LPropertyWithGet:public LMetaProperty
{
public:
    LPropertyWithGet(const LString& _name,GetterType _getter,void* _obj=nullptr,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
            LMetaProperty(_name,lGetTypeName<VarType>(),_attrs),
            mGetter(_getter)
    {
        mObj=_obj;
    }
    virtual ~LPropertyWithGet()
    {
    }

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            set(LVariant _in);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:
    VarType ClassType::*mData;
    GetterType mGetter;
};


//! this using for (public/private) fields that only have setter function for that
template<typename ClassType,typename VarType,typename SetterType>
class LAPI LPropertyWithSet:public LMetaProperty
{
public:
    LPropertyWithSet(const LString& _name,SetterType _setter,void* _obj=nullptr,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
            LMetaProperty(_name,lGetTypeName<VarType>(),_attrs),
            mSetter(_setter)
    {
        mObj=_obj;
    }
    virtual ~LPropertyWithSet()
    {
    }

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            set(LVariant _in);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:
    VarType ClassType::*mData;
    SetterType mSetter;
};


//! this using for (public/private) fields that have getter and setter function for that
template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
class LAPI LPropertyWithGetSet:public LMetaProperty
{
public:
    LPropertyWithGetSet(const LString& _name,GetterType _getter,SetterType _setter,void* _obj=nullptr,const LMap<LString,LString>& _attrs=LMap<LString,LString>()):
            LMetaProperty(_name,lGetTypeName<VarType>(),_attrs),
            mGetter(_getter),
            mSetter(_setter)
    {
        mObj=_obj;
    }
    virtual ~LPropertyWithGetSet()
    {
    }

    virtual LMetaProperty*  clone()const;
    virtual LVariant        get();
    virtual LVariant        getProperty(const LString &_property_name);
    virtual void            set(LVariant _in);
    virtual void            setProperty(const LString &_property_name, const LVariant &_newVal);

protected:
    VarType ClassType::*mData;
    GetterType mGetter;
    SetterType mSetter;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LAPI LMetaObject
{
public:
    LMetaObject(){}
    //! _name is your class unique name and create _typename with lGetTypeName
    LMetaObject(const LString& _name,const LString& _typename);
    LMetaObject(const LMetaObject& _other);
    virtual ~LMetaObject();

    LMetaObject&                    addProperty(LMetaProperty *_property);

    const LMap<LString,LString>&    getAttributes()const;

    LString                         getAttribute(const LString& _key)const;

    LUniquePointer<LMetaProperty>   getProperty(const LString& _name,void* _obj=nullptr)const;

    const LVector<LMetaProperty*>&  getProperties()const;

    LString                         getName() const;

    LString                         getTypeName() const;


    LMetaObject&                    operator=(const LMetaObject& _other);

protected:
    LString mName;
    LString mTypeName;
    LVector<LMetaProperty*> mProperties;

    LMap<LString,LString>   mAttributes;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void LEnum<T>::addElement(const LMetaEnumElement& _ni)
{
    mData.pushBack(_ni);
}

template<typename T>
const LMetaEnumElement& LEnum<T>::getElement(const LString &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mName==_in)
            return mData[i];
    lError2(1,LSTR("Enum Element ")+_in+" not found");
    return mData[0];
}

template<typename T>
u64 LEnum<T>::getElementByName(const LString &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mName==_in)
            return mData[i].mValue;
    return 0;
}

template<typename T>
LString LEnum<T>::getElementName(const u64 &_in) const
{
    for(u32 i=0;i<mData.getSize();i++)
        if(mData[i].mValue==_in)
            return mData[i].mName;
    return LString::empty;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename ClassType,typename VarType>
LMetaProperty* LProperty<ClassType,VarType>::clone() const
{
    LMetaProperty* o = new LProperty<ClassType,VarType>(mName,mData);
    o->mName=mName;
    o->mTypeName=mTypeName;
    o->mAttributes=mAttributes;
    o->mObj=mObj;
    return o;
}

template<typename ClassType,typename VarType>
LVariant LProperty<ClassType,VarType>::get()
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        return o;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType>
LVariant LProperty<ClassType,VarType>::getProperty(const LString &_property_name)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        return o.getProperty(_property_name);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType>
void LProperty<ClassType,VarType>::set(LVariant _in)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        (cp->*mData)=_in.to<VarType>();
        return;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}

template<typename ClassType,typename VarType>
void LProperty<ClassType,VarType>::setProperty(const LString &_property_name, const LVariant &_newVal)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        o.setProperty(_property_name,_newVal);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}

////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename ClassType,typename VarType,typename GetterType>
LMetaProperty* LPropertyWithGet<ClassType,VarType,GetterType>::clone() const
{
    LMetaProperty* o = new LPropertyWithGet<ClassType,VarType,GetterType>(mName,mGetter,mObj);
    o->mName=mName;
    o->mTypeName=mTypeName;
    o->mAttributes=mAttributes;
    return o;
}

template<typename ClassType,typename VarType,typename GetterType>
LVariant LPropertyWithGet<ClassType,VarType,GetterType>::get()
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o= (cp->*mGetter)();
        return o;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType,typename GetterType>
LVariant LPropertyWithGet<ClassType,VarType,GetterType>::getProperty(const LString &_property_name)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=(cp->*mGetter)();
        return o.getProperty(_property_name);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType,typename GetterType>
void LPropertyWithGet<ClassType,VarType,GetterType>::set(LVariant)
{
    lError2(1,"Property is private and has no setter");
}

template<typename ClassType,typename VarType,typename GetterType>
void LPropertyWithGet<ClassType,VarType,GetterType>::setProperty(const LString &_property_name, const LVariant &_newVal)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        o.setProperty(_property_name,_newVal);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}

////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename ClassType,typename VarType,typename SetterType>
LMetaProperty* LPropertyWithSet<ClassType,VarType,SetterType>::clone() const
{
    LMetaProperty* o = new LPropertyWithSet<ClassType,VarType,SetterType>(mName,mSetter,mObj);
    o->mName=mName;
    o->mTypeName=mTypeName;
    o->mAttributes=mAttributes;
    return o;
}

template<typename ClassType,typename VarType,typename SetterType>
LVariant LPropertyWithSet<ClassType,VarType,SetterType>::get()
{
    lError2(1,"Property is private and has no getter");
    return LVariant();
}

template<typename ClassType,typename VarType,typename SetterType>
LVariant LPropertyWithSet<ClassType,VarType,SetterType>::getProperty(const LString &)
{
    lError2(1,"Property is private and has no getter");
    return LVariant();
}

template<typename ClassType,typename VarType,typename SetterType>
void LPropertyWithSet<ClassType,VarType,SetterType>::set(LVariant _in)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        (cp->*mSetter)(_in.to<VarType>());
        return;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}

template<typename ClassType,typename VarType,typename SetterType>
void LPropertyWithSet<ClassType,VarType,SetterType>::setProperty(const LString &, const LVariant &)
{
    lError2(1,"Property is private and has no getter");
}


////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
LMetaProperty* LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>::clone() const
{
    LMetaProperty* o = new LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>(mName,mGetter,mSetter,mObj);
    o->mName=mName;
    o->mTypeName=mTypeName;
    o->mAttributes=mAttributes;
    return o;
}

template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
LVariant LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>::get()
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o= (cp->*mGetter)();
        return o;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
LVariant LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>::getProperty(const LString &_property_name)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=(cp->*mGetter)();
        return o.getProperty(_property_name);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
    return LVariant();
}

template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
void LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>::set(LVariant _in)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        (cp->*mSetter)(_in.to<VarType>());
        return;
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}

template<typename ClassType,typename VarType,typename GetterType,typename SetterType>
void LPropertyWithGetSet<ClassType,VarType,GetterType,SetterType>::setProperty(const LString &_property_name, const LVariant &_newVal)
{
    if(mObj)
    {
        ClassType* cp=(ClassType*)mObj;
        LVariant o;
        o=&(cp->*mData);
        o.setProperty(_property_name,_newVal);
    }
    lError2(1,"Property has no Obj . use setObject function to set object ");
}


////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename ClassType,typename VarType>
LMetaProperty* LPrivateProperty<ClassType,VarType>::clone() const
{
    LMetaProperty* o = new LPrivateProperty<ClassType,VarType>(mName);
    o->mName=mName;
    o->mTypeName=mTypeName;
    o->mAttributes=mAttributes;
    return o;
}

template<typename ClassType,typename VarType>
LVariant LPrivateProperty<ClassType,VarType>::get()
{
    lError2(1,"Property is private and has no getter setter");
    return LVariant();
}

template<typename ClassType,typename VarType>
void LPrivateProperty<ClassType,VarType>::set(LVariant)
{

    lError2(1,"Property is private and has no getter setter");
}

template<typename ClassType,typename VarType>
LVariant LPrivateProperty<ClassType,VarType>::getProperty(const LString &)
{
    lError2(1,"Property is private and has no getter setter");
    return LVariant();
}

template<typename ClassType,typename VarType>
void LPrivateProperty<ClassType,VarType>::setProperty(const LString &, const LVariant &)
{
    lError2(1,"Property is private and has no getter setter");
}

LNAMESPACE_END

#endif // LMETA_H
