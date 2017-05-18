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
public:
    LClassVariantReference(const T& _in);
    virtual ~LClassVariantReference();

    LCustomVariant* clone();
    void            fromString(const LString& _in)override;
    LString         toString() const override;
    void            setProperty(const LString& _name,const LVariant &_in)override;
    LVariant        getProperty(const LString &_name)const override;
};


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
 */

class LAPI LVariant
{
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
    T                               to()const;


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
T LVariant::to() const
{
    //lError2(mTypeName!=lGetTypeName<T>(),LSTR("Looks like type is not correct current type:(")+mTypeName+") and what you want ("+lGetTypeName<T>()+")");
    if(!isValidReference())
    {
        if( LIsSameType<typename LRemoveReference<T>::type,int>::value )
            return *((T*)&mInt);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned int>::value )
            return *((T*)&mUInt);
        if( LIsSameType<typename LRemoveReference<T>::type,float>::value )
            return *((T*)&mFloat);
        if( LIsSameType<typename LRemoveReference<T>::type,double>::value )
            return *((T*)&mDouble);
        if( LIsSameType<typename LRemoveReference<T>::type,long double>::value )
            return *((T*)&mLongDouble);
        if( LIsSameType<typename LRemoveReference<T>::type,char>::value )
            return *((T*)&mChar);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned char>::value )
            return *((T*)&mUChar);
        if( LIsSameType<typename LRemoveReference<T>::type,bool>::value )
            return *((T*)&mBool);
        if( LIsSameType<typename LRemoveReference<T>::type,short int>::value )
            return *((T*)&mShortInt);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned short int>::value )
            return *((T*)&mUShortInt);
        if( LIsSameType<typename LRemoveReference<T>::type,long long int>::value )
            return *((T*)&mLongLongInt);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned long long int>::value )
            return *((T*)&mULongLongInt);
        if( LIsSameType<typename LRemoveReference<T>::type,wchar_t>::value )
            return *((T*)&mWCharT);
        if( LIsSameType<typename LRemoveReference<T>::type,LString>::value )
        {
            LString o=toString();
            return *((T*)&o);
        }
    }
    else
    {
        if( LIsSameType<typename LRemoveReference<T>::type,int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,float&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,double&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,long double&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,char&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned char&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,bool&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,short int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned short int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,long long int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,unsigned long long int&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,wchar_t&>::value )
            return *((T*)mCustom);
        if( LIsSameType<typename LRemoveReference<T>::type,LString>::value )
        {
            return *((T*)mCustom);
        }
    }

    if(mType==VariantType::TCustom)
        return *((T*)mCustomClass->mData);
    if(mType==VariantType::TCustomReference)
        return *((T*)mCustomClass->mData);

    return *static_cast<T*>(mCustom);
}




LNAMESPACE_END

#endif // LVARIANT_H
