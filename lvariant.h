#ifndef LVARIANT_H
#define LVARIANT_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"
#include <initializer_list>

LNAMESPACE_BEGIN

class LVariant;

class LAPI LCustomVariant
{
    template<typename T>
    friend class __LVariantTypeCastHelper;
    friend class LVariant;
public:
    LCustomVariant(){}
    virtual ~LCustomVariant(){}

    //! Get a copy of this
    virtual LCustomVariant*     clone()=0;

    virtual void                fromString(const LString& _in)=0;
    virtual LString             toString()const=0;

    virtual LVariant            getProperty(const LString& _name)const=0;
    virtual void                setProperty(const LString& _name,const LVariant& _in)=0;
protected:
    void* mData;
};

template<typename T>
class LClassVariant:public LCustomVariant
{
    template<typename U>
    friend class __LVariantTypeCastHelper;
public:
    LClassVariant(const T& _in);
    virtual ~LClassVariant();

    LCustomVariant* clone();
    void            fromString(const LString& _in)override;
    LString         toString() const override;
    void            setProperty(const LString& _name,const LVariant &_in)override;
    LVariant        getProperty(const LString &_name)const override;
};

template<typename T>
class LClassVariantReference:public LCustomVariant
{
    template<typename U>
    friend class __LVariantTypeCastHelper;
public:
    LClassVariantReference(const T& _in);
    virtual ~LClassVariantReference();

    LCustomVariant* clone();
    void            fromString(const LString& _in)override;
    LString         toString() const override;
    void            setProperty(const LString& _name,const LVariant &_in)override;
    LVariant        getProperty(const LString &_name)const override;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct __LVariantTypeCastHelper
{
    static T cast(LVariant& _in);
};

template<typename T>
struct __LVariantTypeCastHelper<T&>
{
    static T& cast(LVariant& _in);
};

template<typename T>
struct __LVariantTypeCastHelper<T*>
{
    static T* cast(LVariant& _in);
};
////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * Working with vaiants
 *
 * //how to define a variant
 * LVariant a = 12;
 *
 * //how to use it's value
 * cout<<a.toInt()<<endl;
 *
 * // how to destroy variant
 * a.destroy(); // will convert to null
 *
 * // how to create variant for custom class type
 * LVariant a;
 * a=TestClass(...);
 *
 * // how to use it's value
 * a.to<TestClass>(). ....
 *
 * // how to create variant as reference
 * int value = 12;
 * LVariant a= & value;
 * cout<<a.toInt()<<" "<<value<<endl; // prints 12 12
 * a=444;
 * cout<<a.toInt()<<" "<<value<<endl; // prints 444 444
 * a.destroy(); // destroy current session and prevent from changing value
 * a=147;
 * cout<<a.toInt()<<" "<<value<<endl; // prints 147 444
 *
 * it is recommended to cast to prevent from run time error ( because of RTTI )
 * LVariant o=(int*)&a;
 *
 *
 * // how create reference from custom class
 * a=(CustomClass*)&obj;
 *
 * note : for custom class references and classes , your class should have these functions
 *
 * void lFromString(const LString& _in);
 * LString lToString() const;
 * void lSetProperty(const LString& _name,const LVariant &_in);
 * LVariant lGetProperty(const LString &_name)const;
 *
 *
 * // Variant and Variant Arrays
 * // to create an array
 *
 * LVariant a={1,2,3};
 *
 * //and to use it
 *
 * for(int i=0;i<a.getArraySize();i++)
 *    cout<<a[i].toInt()<<endl;
 *
 * how to create dynamic variant?
 * LVariant a = new int(44);
 *
 * how use it
 * ... a.to<int*>() ...
 *
 * how to delete it?
 * delete a.to<int*>();
 *
 * also call a.destroy() will destroy it
 * and if you dont delete that LVariant will do after LVariant desturctor called
 *
 */

class LAPI LVariant
{
template<typename T>
friend class __LVariantTypeCastHelper;
public:
    enum VariantType
    {
        TNull,

        TInt, // int
        TUInt,
        TFloat,
        TDouble,
        TLongDouble,
        TChar,
        TUChar,
        TBool,
        TShortInt,
        TUShortInt,
        TLongLongInt,
        TULongLongInt,
        TWChar_t,
        TString,

        TIntR, // int Reference
        TUIntR,
        TFloatR,
        TDoubleR,
        TLongDoubleR,
        TBoolR,
        TShortIntR,
        TUShortIntR,
        TLongLongIntR,
        TULongLongIntR,
        TStringR,

        TIntA, // int array
        TUIntA,
        TFloatA,
        TDoubleA,
        TLongDoubleA,
        TCharA,
        TUCharA,
        TBoolA,
        TShortIntA,
        TUShortIntA,
        TLongLongIntA,
        TULongLongIntA,
        TWChar_tA,
        TStringA,
        TVariantA,


        TCustom, // custom classes
        TCustomReference//reference type
    };

    LVariant();
    LVariant(const std::initializer_list<int>& _in);
    LVariant(const std::initializer_list<unsigned int>& _in);
    LVariant(const std::initializer_list<float>& _in);
    LVariant(const std::initializer_list<double>& _in);
    LVariant(const std::initializer_list<long double>& _in);
    LVariant(const std::initializer_list<char>& _in);
    LVariant(const std::initializer_list<unsigned char>& _in);
    LVariant(const std::initializer_list<bool>& _in);
    LVariant(const std::initializer_list<short int>& _in);
    LVariant(const std::initializer_list<unsigned short int>& _in);
    LVariant(const std::initializer_list<long long int>&  _in);
    LVariant(const std::initializer_list<unsigned long long int>& _in);
    LVariant(const std::initializer_list<wchar_t>& _in);
    LVariant(const std::initializer_list<const char*>& _in);// for string
    LVariant(const std::initializer_list<const wchar_t*>& _in);// for string
    LVariant(const std::initializer_list<const char32_t*>& _in);// for string
    LVariant(const std::initializer_list<const LString>& _in);// for string
    LVariant(const std::initializer_list<const LVariant>& _in);
    LVariant(const LVariant& _other);

    template<typename T>
    LVariant(T _in);

    virtual ~LVariant();

    //! destroy current data
    virtual void                    destroy();

    //! set variant from stirng
    virtual void                    fromString(const LString& _in);

    //! Convert to custom reference ( only for custom classes and custom class references )
    template<typename T>
    T*                              getCustomData();

    //! Get Valid type of this variant
    VariantType                     getType()const;

    //! Get Type name of this Varaint
    LString                         getTypeName() const;

    //! Get Property of Class Varaint
    virtual const LVariant          getProperty(const LString& _propertyname)const;

    //! if was array variant . returns size of array
    u32                             getArraySize()const;

    //! check is this a valid array
    bool                            isValidArray()const;

    //! check is this a valid reference
    bool                            isValidReference()const;

    //! set variant from dynamic pointer
    template<typename T>
    void                            setFromPointer(T* _in);

    //! set Property of Class Varaint
    virtual void                    setProperty(const LString& _propertyname,const LVariant& _newvalue);

    int                             toInt()const;
    unsigned int                    toUInt()const;
    float                           toFloat()const;
    double                          toDouble()const;
    long double                     toLongDouble()const;
    char                            toChar()const;
    unsigned char                   toUChar()const;
    bool                            toBool()const;
    short int                       toShortInt()const;
    unsigned short int              toUShortInt()const;
    long long int                   toLongLongInt()const;
    unsigned long long int          toULongLongInt()const;
    wchar_t                         toWCharT()const;
    virtual LString                 toString()const;
    template<typename T>
    T                               to();


    virtual LVariant& operator=(const int& _in);
    virtual LVariant& operator=(const unsigned int& _in);
    virtual LVariant& operator=(const float& _in);
    virtual LVariant& operator=(const double& _in);
    virtual LVariant& operator=(const long double& _in);
    virtual LVariant& operator=(const char& _in);
    virtual LVariant& operator=(const unsigned char& _in);
    virtual LVariant& operator=(const bool& _in);
    virtual LVariant& operator=(const short int& _in);
    virtual LVariant& operator=(const unsigned short int& _in);
    virtual LVariant& operator=(const long long int&  _in);
    virtual LVariant& operator=(const unsigned long long int& _in);
    virtual LVariant& operator=(const wchar_t& _in);
    virtual LVariant& operator=(const LString& _in);
    virtual LVariant& operator=(const char* _in);
    virtual LVariant& operator=(const wchar_t* _in);
    virtual LVariant& operator=(const char32_t* _in);

    virtual LVariant& operator=(int* _in);
    virtual LVariant& operator=(unsigned int* _in);
    virtual LVariant& operator=(float* _in);
    virtual LVariant& operator=(double* _in);
    virtual LVariant& operator=(long double* _in);
    virtual LVariant& operator=(bool* _in);
    virtual LVariant& operator=(short int* _in);
    virtual LVariant& operator=(unsigned short int* _in);
    virtual LVariant& operator=(long long int* _in);
    virtual LVariant& operator=(unsigned long long int* _in);
    virtual LVariant& operator=(LString* _in);

    virtual LVariant& operator=(const int* _in);
    virtual LVariant& operator=(const unsigned int* _in);
    virtual LVariant& operator=(const float* _in);
    virtual LVariant& operator=(const double* _in);
    virtual LVariant& operator=(const long double* _in);
    virtual LVariant& operator=(const bool* _in);
    virtual LVariant& operator=(const short int* _in);
    virtual LVariant& operator=(const unsigned short int* _in);
    virtual LVariant& operator=(const long long int* _in);
    virtual LVariant& operator=(const unsigned long long int* _in);
    virtual LVariant& operator=(const LString* _in);


    virtual LVariant& operator=(const std::initializer_list<int>& _in);
    virtual LVariant& operator=(const std::initializer_list<unsigned int>& _in);
    virtual LVariant& operator=(const std::initializer_list<float>& _in);
    virtual LVariant& operator=(const std::initializer_list<double>& _in);
    virtual LVariant& operator=(const std::initializer_list<long double>& _in);
    virtual LVariant& operator=(const std::initializer_list<char>& _in);
    virtual LVariant& operator=(const std::initializer_list<unsigned char>& _in);
    virtual LVariant& operator=(const std::initializer_list<bool>& _in);
    virtual LVariant& operator=(const std::initializer_list<short int>& _in);
    virtual LVariant& operator=(const std::initializer_list<unsigned short int>& _in);
    virtual LVariant& operator=(const std::initializer_list<long long int>&  _in);
    virtual LVariant& operator=(const std::initializer_list<unsigned long long int>& _in);
    virtual LVariant& operator=(const std::initializer_list<wchar_t>& _in);
    virtual LVariant& operator=(const std::initializer_list<const char*>& _in);// for string
    virtual LVariant& operator=(const std::initializer_list<const wchar_t*>& _in);// for string
    virtual LVariant& operator=(const std::initializer_list<const char32_t*>& _in);// for string
    virtual LVariant& operator=(const std::initializer_list<const LString>& _in);// for string

    virtual LVariant& operator=(const std::initializer_list<const LVariant>& _in);

    virtual LVariant& operator=(const LVariant& _in);

    template<typename T>
    LVariant&         operator=(T _in);

    template<typename T>
    LVariant&         operator=(T* _in);

    template<typename T>
    LVariant&         operator=(const T* _in);

    virtual LVariant& operator[](u32 _i)const;

protected:
    template<typename T>
    T                 _convert()const;
protected:
    VariantType mType;
    LString     mTypeName;
    union
    {
        int                              mInt;
        unsigned int                     mUInt;
        float                            mFloat;
        double                           mDouble;
        long double                      mLongDouble;
        char                             mChar;
        unsigned char                    mUChar;
        bool                             mBool;
        short int                        mShortInt;
        unsigned short int               mUShortInt;
        long long int                    mLongLongInt;
        unsigned long long int           mULongLongInt;
        wchar_t                          mWCharT;
        LString*                         mString;

        LVector<LVariant>*               mArray;

        void*                            mCustom;

        LCustomVariant*                  mCustomClass;
    };
};
////////////////////////////////////////////////////////////////////////////////////////////////////
lConfigCallIfExist(_lhas_fromString,void,lFromString,const LString&)
lConfigCallIfExistConst(_lhas_toString,LString,lToString)

lConfigCallIfExist(_lhas_setProperty,void,lSetProperty,const LString&,const LVariant&)
lConfigCallIfExistConst(_lhas_getProperty,LVariant,lGetProperty,const LString&)

template<typename T>
LClassVariant<T>::LClassVariant(const T &_in)
{
    mData=new T(_in);
}

template<typename T>
LClassVariant<T>::~LClassVariant()
{
    T* ptr = (T*)mData;
    delete ptr;
}

template<typename T>
LCustomVariant *LClassVariant<T>::clone()
{
    LCustomVariant* o = new LClassVariant(*((T*)mData));
    return o;
}

template<typename T>
void LClassVariant<T>::fromString(const LString& _in)
{
    T* d=((T*)mData);
    _lhas_fromString<T>::call(*d,_in);
}

template<typename T>
LString LClassVariant<T>::toString() const
{
    T* d=((T*)mData);
    return _lhas_toString<T>::call(*d);
}

template<typename T>
LVariant LClassVariant<T>::getProperty(const LString& _name)const
{
    T* d=((T*)mData);
    return _lhas_getProperty<T>::call(*d,_name);
}

template<typename T>
void LClassVariant<T>::setProperty(const LString &_name, const LVariant &_in)
{
    T* d=((T*)mData);
    _lhas_setProperty<T>::call(*d,_name,_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LClassVariantReference<T>::LClassVariantReference(const T &_in)
{
    mData=(void*)&_in;
}

template<typename T>
LClassVariantReference<T>::~LClassVariantReference()
{
    if(__lptrlogmanager.isValidPointer(mData))
    {
        T* ptr=(T*)mData;
        if(__lptrlogmanager.isSimplePointer(mData))
            delete ptr;
        else
            delete[] ptr;
    }
}

template<typename T>
LCustomVariant *LClassVariantReference<T>::clone()
{
    LCustomVariant* o = new LClassVariantReference(*((T*)mData));
    return o;
}

template<typename T>
void LClassVariantReference<T>::fromString(const LString& _in)
{
    T* d=((T*)mData);
    _lhas_fromString<T>::call(*d,_in);
}

template<typename T>
LString LClassVariantReference<T>::toString() const
{
    T* d=((T*)mData);
    return _lhas_toString<T>::call(*d);
}

template<typename T>
LVariant LClassVariantReference<T>::getProperty(const LString& _name)const
{
    T* d=((T*)mData);
    return _lhas_getProperty<T>::call(*d,_name);
}

template<typename T>
void LClassVariantReference<T>::setProperty(const LString &_name, const LVariant &_in)
{
    T* d=((T*)mData);
    return _lhas_setProperty<T>::call(*d,_name,_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LVariant::LVariant(T _in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

template<typename T>
void LVariant::setFromPointer(T *_in)
{
    this->destroy();
    mTypeName=lGetTypeName<T>();
    mType=VariantType::TCustom;
    mCustomClass=new LClassVariant<T>(*_in);
    delete reinterpret_cast<T*>(mCustomClass->mData);
    mCustomClass->mData = _in;
}

template<bool con>
struct ___l_var_callif
{
    template<typename A,typename B>
    static void call(A _a,B _b){LUNUSED(_a);LUNUSED(_b);}
};
template<>
struct ___l_var_callif<true>
{
    static void call(void*& _a,const void* _b){_a=(void*)_b;}
};

template<typename T>
LVariant &LVariant::operator=(T _in)
{
    if(mTypeName==lGetTypeName<T>()&&(mType==VariantType::TCustom||mType==VariantType::TCustomReference))
    {
        T* ptr=(T*)mCustomClass->mData;
        (*ptr)=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName<T>();
    mType=VariantType::TCustom;
    mCustomClass=new LClassVariant<T>(_in);
    return *this;
}

template<typename T>
LVariant &LVariant::operator=(T* _in)
{
    this->destroy();
    mTypeName=lGetTypeName<typename LRemovePointer<T>::type>();
    mType=VariantType::TCustomReference;
    mCustomClass=new LClassVariantReference<T>(*_in);
    return *this;
}

template<typename T>
LVariant &LVariant::operator=(const T* _in)
{
    this->destroy();
    mTypeName=lGetTypeName<typename LRemovePointer<T>::type>();
    mType=VariantType::TCustomReference;
    mCustomClass=new LClassVariantReference<T>(*_in);
    return *this;
}

template<typename T>
T* LVariant::getCustomData()
{
    lError(mType!=VariantType::TCustom&&mType!=VariantType::TCustomReference,"Variant Type is not OK to call this function",nullptr);
    return ((T*)mCustomClass->mData);
}

template<typename T>
T LVariant::to()
{
    return __LVariantTypeCastHelper<T>::cast(*this);
}



template<typename T>
T LVariant::_convert() const
{
    //lError2(mTypeName!=lGetTypeName<T>(),LSTR("Looks like type is not correct current type:(")+mTypeName+") and what you want ("+lGetTypeName<T>()+")");
    if(!isValidReference())
    {
        if( mType == VariantType::TInt )
            return (T)mInt;
        if( mType == VariantType::TUInt )
            return (T)mUInt;
        if( mType == VariantType::TFloat )
            return (T)mFloat;
        if( mType == VariantType::TDouble )
            return (T)mDouble;
        if( mType == VariantType::TLongDouble )
            return (T)mLongDouble;
        if( mType == VariantType::TChar )
            return (T)mChar;
        if( mType == VariantType::TUChar )
            return (T)mUChar;
        if( mType == VariantType::TBool )
            return (T)mBool;
        if( mType == VariantType::TShortInt )
            return (T)mShortInt;
        if( mType == VariantType::TUShortInt )
            return (T)mUShortInt;
        if( mType == VariantType::TLongLongInt )
            return (T)mLongLongInt;
        if( mType == VariantType::TULongLongInt )
            return (T)mULongLongInt;
        if( mType == VariantType::TWChar_t )
            return (T)mWCharT;
        if( mType == VariantType::TString )
        {
            LString o=toString();
            return *((T*)&o);
        }
    }
    else
    {
        if( mType == VariantType::TIntR )
            return (T)(*((int*)mCustom));
        if( mType == VariantType::TUIntR )
            return (T)(*((unsigned int*)mCustom));
        if( mType == VariantType::TFloatR )
            return (T)(*((float*)mCustom));
        if( mType == VariantType::TDoubleR )
            return (T)(*((double*)mCustom));
        if( mType == VariantType::TLongDoubleR )
            return (T)(*((long double*)mCustom));
        if( mType == VariantType::TBoolR )
            return (T)(*((bool*)mCustom));
        if( mType == VariantType::TShortIntR )
            return (T)(*((short int*)mCustom));
        if( mType == VariantType::TUShortIntR )
            return (T)(*((unsigned short int*)mCustom));
        if( mType == VariantType::TLongLongIntR )
            return (T)(*((long long int*)mCustom));
        if( mType == VariantType::TULongLongIntR )
            return (T)(*((unsigned long long int*)mCustom));
        if( mType == VariantType::TStringR )
        {
            LString o=toString();
            return (T)o.toLongLongInt();
        }
    }

    return *static_cast<T*>(mCustom);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T __LVariantTypeCastHelper<T>::cast(LVariant& _in)
{
    if( LIsSameType<typename LRemoveReference<T>::type,int>::value || LIsSameType<typename LRemoveReference<T>::type,const int>::value )
    {
        int o=_in.toInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,unsigned int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned int>::value )
    {
        unsigned int o=_in.toUInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,float>::value || LIsSameType<typename LRemoveReference<T>::type,const float>::value )
    {
        float o=_in.toFloat();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,double>::value || LIsSameType<typename LRemoveReference<T>::type,const double>::value )
    {
        double o=_in.toDouble();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,long double>::value || LIsSameType<typename LRemoveReference<T>::type,const long double>::value)
    {
        long double o=_in.toLongDouble();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,char>::value || LIsSameType<typename LRemoveReference<T>::type,const char>::value)
    {
        char o=_in.toChar();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,unsigned char>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned char>::value)
    {
        unsigned char o=_in.toUChar();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,bool>::value || LIsSameType<typename LRemoveReference<T>::type,const bool>::value)
    {
        bool o=_in.toBool();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,short int>::value || LIsSameType<typename LRemoveReference<T>::type,const short int>::value)
    {
        short int o=_in.toShortInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,unsigned short int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned short int>::value)
    {
        unsigned short int o=_in.toUShortInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const long long int>::value)
    {
        long long int o=_in.toLongLongInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,unsigned long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned long long int>::value)
    {
        unsigned long long int o=_in.toULongLongInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,wchar_t>::value || LIsSameType<typename LRemoveReference<T>::type,const wchar_t>::value)
    {
        wchar_t o=_in.toWCharT();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,LString>::value || LIsSameType<typename LRemoveReference<T>::type,const LString>::value)
    {
        LString o=_in.toString();
        return *((T*)&o);
    }

    lError2( (_in.mType!=LVariant::VariantType::TCustom && _in.mType!=LVariant::VariantType::TCustomReference) || _in.mTypeName!=lGetTypeName<T>() ,"You type casting is not right");

    if(_in.mType==LVariant::VariantType::TCustom)
        return *((T*)_in.mCustomClass->mData);
    if(_in.mType==LVariant::VariantType::TCustomReference)
        return *((T*)_in.mCustomClass->mData);

    return *static_cast<T*>(_in.mCustom);
}



template<typename T>
T& __LVariantTypeCastHelper<T&>::cast(LVariant& _in)
{
    if( LIsSameType<typename LRemoveReference<T>::type,const int>::value )
    {
        static int o;
        o=_in.toInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const unsigned int>::value )
    {
        static unsigned int o;
        o=_in.toUInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const float>::value )
    {
        static float o;
        o=_in.toFloat();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const double>::value )
    {
        static double o;
        o=_in.toDouble();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const long double>::value )
    {
        static long double o;
        o=_in.toLongDouble();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const char>::value )
    {
        static char o;
        o=_in.toChar();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const unsigned char>::value )
    {
        static unsigned char o;
        o=_in.toUChar();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const bool>::value )
    {
        static bool o;
        o=_in.toBool();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const short int>::value )
    {
        static short int o;
        o=_in.toShortInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const unsigned short int>::value )
    {
        static unsigned short int o;
        o=_in.toUShortInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const long long int>::value )
    {
        static long long int o;
        o=_in.toLongLongInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const unsigned long long int>::value )
    {
        static unsigned long long int o;
        o=_in.toULongLongInt();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const wchar_t>::value )
    {
        static wchar_t o;
        o=_in.toWCharT();
        return *((T*)&o);
    }
    if( LIsSameType<typename LRemoveReference<T>::type,const LString>::value )
    {
        static LString o;
        o=_in.toString();
        return *((T*)&o);
    }

    if(_in.mType==LVariant::VariantType::TCustom)
        return *((T*)_in.mCustomClass->mData);
    if(_in.mType==LVariant::VariantType::TCustomReference)
        return *((T*)_in.mCustomClass->mData);

    return *(T*)(_in.mCustom);
}

template<typename T>
T* __LVariantTypeCastHelper<T*>::cast(LVariant& _in)
{
    if(_in.mType==LVariant::VariantType::TCustom)
        return ((T*)_in.mCustomClass->mData);
    if(_in.mType==LVariant::VariantType::TCustomReference)
        return ((T*)_in.mCustomClass->mData);

    return (T*)(_in.mCustom);
}


LNAMESPACE_END

#endif // LVARIANT_H
