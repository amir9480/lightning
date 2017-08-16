#ifndef LMETAPROPERTY_H
#define LMETAPROPERTY_H

#include "ldefines.h"
#include "lfunction.h"
#include "lvariant.h"
#include "lmap.h"

#define LMETA_ATTR( _NAME , _VALUE ) { _NAME , _VALUE }


#define LMETAENUM_BEGIN_DEFINE( _NAME , _TYPE , ...)\
    template<>\
    class LMetaEnumDefine<_TYPE>\
    {\
        LNONCOPYABLE_CLASS(LMetaEnumDefine)\
    public:\
        LMetaEnumDefine(){}\
        virtual ~LMetaEnumDefine(){}\
        static Lightning::LMetaEnum& get()\
        {\
            typedef _TYPE _THE_TYPE;\
            lMemoryLogStartIgnore();\
            static Lightning::LMetaEnum o(_NAME,Lightning::lGetTypeName<_TYPE>(),{ __VA_ARGS__ },{

#define LMETAENUM_END_DEFINE( _TYPE ) \
    }); \
    static bool _done=false;\
    if(!_done)\
    {\
        Lightning::LMetaObjectManager::mEnums.pushBack(o);\
        _done=true;\
    }\
    lMemoryLogEndIgnore(); \
    return o; \
} \
};\
void lCallOnStart()\
{\
    LMetaEnumDefine<_TYPE>::get();\
}


#define LMETAENUM_ELEMENT( _NAME , _VAL , ...)\
    Lightning::LMetaEnumElement(_NAME,(i64)_THE_TYPE::_VAL,{__VA_ARGS__}),

LNAMESPACE_BEGIN

//! to define addtional attributes
class LMetaAttributes
{
public:
    LMetaAttributes();
    LMetaAttributes(const LMap<LString,LString>& _attrs);
    virtual ~LMetaAttributes();

    //! set an attribute or if doesnt exist create new one
    void                            addAttribute(const LString& _name,const LString& _value);

    //! check attribute exists or not
    bool                            exists(const LString& _name)const;

    //! get an attribute by name if exists otherwise returns default
    LString                         getAttribute(const LString& _name,const LString& _default=LString::empty)const;

    //! get all attributes
    const LMap<LString, LString>&   getAttributes() const;

    //! removes an attribute if exists. if doesn't exists returns false
    bool                            removeAttribute(const LString& _name);

    //! set an attribute if exist. if doesn't exists returns false
    bool                            setAttribute(const LString& _name,const LString& _value);

protected:
    LMap<LString,LString>   mAttributes;
};

class LMetaEnumElement:public LMetaAttributes
{
public:
    LMetaEnumElement();
    LMetaEnumElement(const LString& _name,const i64& _value);
    LMetaEnumElement(const LString& _name,const i64& _value, const LMap<LString,LString>& _attrs);
    virtual ~LMetaEnumElement();

    //! get name of enum element
    LString                         getName() const;

    //! get value of enum element (as integer)
    i64                             getValue() const;

private:
    LString                 mName;
    i64                     mValue;
};

//! to define meta for enums
class LMetaEnum:public LMetaAttributes
{
public:
    LMetaEnum();
    LMetaEnum(const LString& _name,const LString& _typename,const LVector<LMetaEnumElement>& _elements);
    LMetaEnum(const LString& _name,const LString& _typename,const LMap<LString,LString>& _attrs,const LVector<LMetaEnumElement>& _elements);
    virtual ~LMetaEnum();

    //! add a new Enum element
    LMetaEnum&                          addElement(const LMetaEnumElement& _element);

    //! get elements directly
    const LVector<LMetaEnumElement>&    getElements()const;

    //! get element by name . if does't exists will returns something as default
    LMetaEnumElement&                   getElement(const LString& _name);

    //! get element by value . if does't exists will returns something as default
    LMetaEnumElement&                   getElement(const i64 _val);

    //! get name of enum
    LString                             getName() const;

    //! get type name id
    LString                             getTypeName() const;

private:
    LString                     mName;
    LString                     mTypeName;
    LVector<LMetaEnumElement>   mElemenets;
};


LNAMESPACE_END // Lightning namespace End


//! to define new meta for enum
template<typename T>
class LMetaEnumDefine
{
    LNONCOPYABLE_CLASS(LMetaEnumDefine)
public:
    LMetaEnumDefine(){}
    virtual ~LMetaEnumDefine(){}
    static Lightning::LMetaEnum& get()
    {
        static Lightning::LMetaEnum o;
        return o;
    }
};


LNAMESPACE_BEGIN

class LMetaProperty:public LMetaAttributes
{
public:
    LMetaProperty(const LString& _name,const LString& _typename);
    LMetaProperty(const LString& _name,const LString& _typename,const LMap<LString,LString>& _attrs);
    virtual ~LMetaProperty();

    LString             getName() const;

    LString             getTypeName() const;

    virtual LVariant    get( LVariant _obj)=0;

    virtual void        set( LVariant _obj, LVariant _new_value)=0;

protected:
    LString     mName;
    LString     mTypeName;
};


template<typename ClassType,typename PropertyType>
class LMetaPropertyRaw:public LMetaProperty
{
public:
    LMetaPropertyRaw(const LString& _name,PropertyType ClassType::*_property);
    LMetaPropertyRaw(const LString& _name,PropertyType ClassType::*_property,const LMap<LString,LString>& _attrs);
    virtual ~LMetaPropertyRaw();

    virtual LVariant    get( LVariant _obj);

    virtual void        set( LVariant _obj, LVariant _new_value);

private:
    PropertyType    ClassType::*mProperty;
};

template<typename ClassType,typename GetterType>
class LMetaPropertyWithGetter:public LMetaProperty
{
public:
    LMetaPropertyWithGetter(const LString& _name,GetterType  _getter);
    LMetaPropertyWithGetter(const LString& _name,GetterType  _getter,const LMap<LString,LString>& _attrs);
    virtual ~LMetaPropertyWithGetter();

    virtual LVariant    get( LVariant _obj);

    virtual void        set( LVariant _obj, LVariant _new_value);

private:
    GetterType          mGetter;
};

template<typename ClassType,typename SetterType>
class LMetaPropertyWithSetter:public LMetaProperty
{
public:
    LMetaPropertyWithSetter(const LString& _name,SetterType  _setter);
    LMetaPropertyWithSetter(const LString& _name,SetterType  _setter,const LMap<LString,LString>& _attrs);
    virtual ~LMetaPropertyWithSetter();

    virtual LVariant    get( LVariant _obj);

    virtual void        set( LVariant _obj, LVariant _new_value);

private:
    SetterType          mSetter;
};


template<typename ClassType,typename GetterType,typename SetterType>
class LMetaPropertyWithGetterSetter:public LMetaProperty
{
public:
    LMetaPropertyWithGetterSetter(const LString& _name,GetterType  _getter, SetterType _setter);
    LMetaPropertyWithGetterSetter(const LString& _name,GetterType  _getter, SetterType _setter,const LMap<LString,LString>& _attrs);
    virtual ~LMetaPropertyWithGetterSetter();

    virtual LVariant    get( LVariant _obj);

    virtual void        set( LVariant _obj, LVariant _new_value);

private:
    GetterType          mGetter;
    SetterType          mSetter;
};

class LMetaObject:public LMetaAttributes
{
public:
    LMetaObject(const LString& _name,const LString& _typename);
    LMetaObject(const LString& _name,const LString& _typename,const LMap<LString,LString>& _attrs);
    virtual ~LMetaObject();

    //! add new property directly
    LMetaObject&                addProperty(LMetaProperty* _property);

    //! add raw property
    template<typename ClassType,typename PropertyType>
    LMetaObject&                addPropertyRaw(const LString& _name,PropertyType ClassType::*_property,const LMap<LString,LString>& _attrs={});

    //! add property with getter
    template<typename GetterType>
    LMetaObject&                addPropertyWithGetter(const LString& _name,GetterType  _getter,const LMap<LString,LString>& _attrs={});

    //! add property with setter
    template<typename SetterType>
    LMetaObject&                addPropertyWithSetter(const LString& _name,SetterType  _setter,const LMap<LString,LString>& _attrs={});

    //! get class name
    LString                     getName() const;

    //! get class typename
    LString                     getTypeName() const;

    //! get a property
    LMetaProperty*              getProperty(const LString& _name);

    //! get all properties
    LVector<LMetaProperty*>&    getProperties();

protected:
    LString                     mName;
    LString                     mTypeName;
    LVector<LMetaProperty*>     mProperties;
};


class LMetaObjectManager
{
    template<typename T>
    friend LMetaEnum& LMetaEnumDefine<T>::get();

    LNONCOPYABLE_CLASS(LMetaObjectManager)
    LMetaObjectManager();
public:
    virtual ~LMetaObjectManager();

    //! Get a Enum meta by it's name . returns something when Not found
    static LMetaEnum&                   getMetaEnumByName(const LString& _name);

    //! Get a Enum meta by it's type name . with lGetTypeName . returns something when Not found
    static LMetaEnum&                   getMetaEnumByTypeName(const LString& _tname);

    //! Get a Enum meta by it's Type . returns something when Not found
    template<typename T>
    static LMetaEnum&                   getMetaEnumByType();

private:
    static LVector<LMetaEnum>           mEnums;
};


template<typename T>
LMetaEnum &LMetaObjectManager::getMetaEnumByType()
{
    return LMetaEnumDefine<T>::get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename ClassType,typename PropertyType>
LMetaPropertyRaw<ClassType,PropertyType>::LMetaPropertyRaw(const LString &_name, PropertyType ClassType::*_property):
    LMetaProperty(_name,lGetTypeName<PropertyType>()),
    mProperty(_property)
{

}
template<typename ClassType,typename PropertyType>
LMetaPropertyRaw<ClassType,PropertyType>::LMetaPropertyRaw(const LString &_name, PropertyType ClassType::*_property,const LMap<LString,LString>& _attrs):
    LMetaProperty(_name,lGetTypeName<PropertyType>(),_attrs),
    mProperty(_property)
{

}

template<typename ClassType,typename PropertyType>
LMetaPropertyRaw<ClassType,PropertyType>::~LMetaPropertyRaw()
{

}

template<typename ClassType,typename PropertyType>
LVariant LMetaPropertyRaw<ClassType,PropertyType>::get(LVariant _obj)
{
    return LVariant::create(&((_obj.to<ClassType&>()).*mProperty));
}

template<typename ClassType,typename PropertyType>
void LMetaPropertyRaw<ClassType,PropertyType>::set(LVariant _obj, LVariant _new_value)
{
    (_obj.to<ClassType&>()).*mProperty = _new_value.to<PropertyType>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename ClassType,typename GetterType>
LMetaPropertyWithGetter<ClassType,GetterType>::LMetaPropertyWithGetter(const LString &_name, GetterType _getter):
    LMetaProperty(_name,lGetTypeName<GetterType>()),
    mGetter(_getter)
{

}
template<typename ClassType,typename GetterType>
LMetaPropertyWithGetter<ClassType,GetterType>::LMetaPropertyWithGetter(const LString &_name, GetterType _getter,const LMap<LString,LString>& _attrs):
    LMetaProperty(_name,lGetTypeName<GetterType>(),_attrs),
    mGetter(_getter)
{

}

template<typename ClassType,typename GetterType>
LMetaPropertyWithGetter<ClassType,GetterType>::~LMetaPropertyWithGetter()
{

}

template<typename ClassType,typename GetterType>
LVariant LMetaPropertyWithGetter<ClassType,GetterType>::get(LVariant _obj)
{
    return LVariant::create(((_obj.to<ClassType&>()).*mGetter)());
}

template<typename ClassType,typename GetterType>
void LMetaPropertyWithGetter<ClassType,GetterType>::set(LVariant , LVariant )
{
    lWarning(1,mName+" is Read Only Property");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct ___property_setter_helper
{
};

template<typename RT,typename CT,typename AT>
struct ___property_setter_helper<RT (CT::*)(AT)>
{
    typedef RT ReturnType;
    typedef CT ClassType;
    typedef AT ArgType;
};
template<typename RT,typename CT,typename AT>
struct ___property_setter_helper<RT (CT::*)(AT&)>
{
    typedef RT ReturnType;
    typedef CT ClassType;
    typedef AT& ArgType;
};
template<typename RT,typename CT,typename AT>
struct ___property_setter_helper<RT (CT::*)(const AT&)>
{
    typedef RT ReturnType;
    typedef CT ClassType;
    typedef AT ArgType;
};

template<typename T>
struct ___property_getter_helper
{
};
template<typename RT,typename CT>
struct ___property_getter_helper<RT (CT::*)()>
{
    typedef RT ReturnType;
    typedef CT ClassType;
};
template<typename RT,typename CT>
struct ___property_getter_helper<RT (CT::*)()const>
{
    typedef RT ReturnType;
    typedef CT ClassType;
};


template<typename ClassType,typename SetterType>
LMetaPropertyWithSetter<ClassType,SetterType>::LMetaPropertyWithSetter(const LString &_name, SetterType _setter):
    LMetaProperty(_name,lGetTypeName<SetterType>()),
    mSetter(_setter)
{

}

template<typename ClassType,typename SetterType>
LMetaPropertyWithSetter<ClassType,SetterType>::LMetaPropertyWithSetter(const LString &_name, SetterType _setter,const LMap<LString,LString>& _attrs):
    LMetaProperty(_name,lGetTypeName<SetterType>(),_attrs),
    mSetter(_setter)
{

}

template<typename ClassType,typename SetterType>
LMetaPropertyWithSetter<ClassType,SetterType>::~LMetaPropertyWithSetter()
{

}

template<typename ClassType,typename SetterType>
LVariant LMetaPropertyWithSetter<ClassType,SetterType>::get(LVariant )
{
    lWarning(1,mName+" is Set Only Property");
    return LVariant();
}

template<typename ClassType,typename SetterType>
void LMetaPropertyWithSetter<ClassType,SetterType>::set(LVariant _obj, LVariant _new_value)
{
    ((_obj.to<ClassType&>()).*mSetter)( _new_value.to< typename ___property_setter_helper<SetterType>::ArgType >() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename ClassType,typename GetterType,typename SetterType>
LMetaPropertyWithGetterSetter<ClassType,GetterType,SetterType>::LMetaPropertyWithGetterSetter(const LString &_name, GetterType _getter, SetterType _setter):
    LMetaProperty(_name,lGetTypeName<SetterType>()),
    mGetter(_getter),
    mSetter(_setter)
{
}
template<typename ClassType,typename GetterType,typename SetterType>
LMetaPropertyWithGetterSetter<ClassType,GetterType,SetterType>::LMetaPropertyWithGetterSetter(const LString &_name, GetterType _getter, SetterType _setter,const LMap<LString,LString>& _attrs):
    LMetaProperty(_name,lGetTypeName<SetterType>(),_attrs),
    mGetter(_getter),
    mSetter(_setter)
{
}

template<typename ClassType,typename GetterType,typename SetterType>
LMetaPropertyWithGetterSetter<ClassType,GetterType,SetterType>::~LMetaPropertyWithGetterSetter()
{

}

template<typename ClassType,typename GetterType,typename SetterType>
LVariant LMetaPropertyWithGetterSetter<ClassType,GetterType,SetterType>::get(LVariant _obj)
{
    return LVariant::create(((_obj.to<ClassType&>()).*mGetter)());
}

template<typename ClassType,typename GetterType,typename SetterType>
void LMetaPropertyWithGetterSetter<ClassType,GetterType,SetterType>::set(LVariant _obj, LVariant _new_value)
{
    ((_obj.to<ClassType&>()).*mSetter)( _new_value.to< typename ___property_setter_helper<SetterType>::ArgType >() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename ClassType,typename PropertyType>
LMetaObject &LMetaObject::addPropertyRaw(const LString &_name, PropertyType ClassType::*_property, const LMap<LString, LString> &_attrs)
{
    mProperties.pushBack(new LMetaPropertyRaw<ClassType,PropertyType>(_name,_property,_attrs));
    return *this;
}


template<typename GetterType>
LMetaObject &LMetaObject::addPropertyWithGetter(const LString &_name, GetterType _getter, const LMap<LString, LString> &_attrs)
{
    mProperties.pushBack(new LMetaPropertyWithGetter<typename ___property_getter_helper<GetterType>::ClassType,GetterType>(_name,_getter,_attrs));
    return *this;
}


template<typename SetterType>
LMetaObject &LMetaObject::addPropertyWithSetter(const LString &_name,SetterType _setter, const LMap<LString, LString> &_attrs)
{
    mProperties.pushBack(new LMetaPropertyWithSetter<typename ___property_setter_helper<SetterType>::ClassType,SetterType>(_name,_setter,_attrs));
    return *this;
}


LNAMESPACE_END

#endif // LMETAPROPERTY_H
