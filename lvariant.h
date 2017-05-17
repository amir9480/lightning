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

    virtual void        fromString(const LString _in){LUNUSED(_in);}
    virtual LString     toString()const{ return LString::empty;}

    virtual LVariant    getProperty(const LString& _name)const;
    virtual void        setProperty(const LString& _name,const LVariant& _in);
protected:
    void* mData;
};

template<typename T>
class LClassVariant:public LCustomVariant
{
public:
    LClassVariant(const T& _in);
    virtual ~LClassVariant();

    void        fromString(const LString _in)override;
    LString     toString() const override;
    void        setProperty(const LString& _name,const LVariant &_in)override;
    LVariant    getProperty(const LString &_name)const override;
};

template<typename T>
class LClassVariantReference:public LCustomVariant
{
public:
    LClassVariantReference(T& _in);
    virtual ~LClassVariantReference();

    void        fromString(const LString _in)override;
    LString     toString() const override;
    void        setProperty(const LString& _name,const LVariant &_in)override;
    LVariant    getProperty(const LString &_name)const override;
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
 * a.setFromCustomClass(...);
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


        TCustom, // custom classes
        TCustomReference//reference type
    };

    LVariant();

    LVariant(int _in);
    LVariant(unsigned int _in);
    LVariant(float _in);
    LVariant(double _in);
    LVariant(long double _in);
    LVariant(char _in);
    LVariant(unsigned char _in);
    LVariant(bool _in);
    LVariant(short int _in);
    LVariant(unsigned short int _in);
    LVariant(long long int  _in);
    LVariant(unsigned long long int _in);
    LVariant(wchar_t _in);
    LVariant(LString _in);
    LVariant(const char* _in);
    LVariant(const wchar_t* _in);
    LVariant(const char32_t* _in);

    LVariant(int* _in);
    LVariant(unsigned int* _in);
    LVariant(float* _in);
    LVariant(double* _in);
    LVariant(long double* _in);
    LVariant(bool* _in);
    LVariant(short int* _in);
    LVariant(unsigned short int* _in);
    LVariant(long long int* _in);
    LVariant(unsigned long long int* _in);
    LVariant(LString* _in);

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

    LVariant(const LVariant& _other);

    virtual ~LVariant();

    //! destroy current data
    virtual void                    destroy();

    //! set variant from stirng
    virtual void                    fromString(const LString& _in);

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

    //! set Property of Class Varaint
    virtual void                    setProperty(const LString& _propertyname,const LVariant& _newvalue);

    template<typename T>
    void                            setFromCustomClass(T _in);

    template<typename T>
    void                            setFromCustomReference(T* _in);

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

    virtual LVariant& operator=(int _in);
    virtual LVariant& operator=(unsigned int _in);
    virtual LVariant& operator=(float _in);
    virtual LVariant& operator=(double _in);
    virtual LVariant& operator=(long double _in);
    virtual LVariant& operator=(char _in);
    virtual LVariant& operator=(unsigned char _in);
    virtual LVariant& operator=(bool _in);
    virtual LVariant& operator=(short int _in);
    virtual LVariant& operator=(unsigned short int _in);
    virtual LVariant& operator=(long long int  _in);
    virtual LVariant& operator=(unsigned long long int _in);
    virtual LVariant& operator=(wchar_t _in);
    virtual LVariant& operator=(LString _in);
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

    virtual LVariant& operator=(const LVariant& _in);

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
void LClassVariant<T>::fromString(const LString _in)
{
    T* d=((T*)mData);
    d->fromString(_in);
}

template<typename T>
LString LClassVariant<T>::toString() const
{
    T* d=((T*)mData);
    return d->toString();
}

template<typename T>
LVariant LClassVariant<T>::getProperty(const LString& _name)const
{
    T* d=((T*)mData);
    return d->getProperty(_name);
}

template<typename T>
void LClassVariant<T>::setProperty(const LString &_name, const LVariant &_in)
{
    T* d=((T*)mData);
    d->setProperty(_name,_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LClassVariantReference<T>::LClassVariantReference(T &_in)
{
    mData=(void*)&_in;
}

template<typename T>
LClassVariantReference<T>::~LClassVariantReference()
{

}

template<typename T>
void LClassVariantReference<T>::fromString(const LString _in)
{
    T* d=((T*)mData);
    d->fromString(_in);
}

template<typename T>
LString LClassVariantReference<T>::toString() const
{
    T* d=((T*)mData);
    return d->toString();
}

template<typename T>
LVariant LClassVariantReference<T>::getProperty(const LString& _name)const
{
    T* d=((T*)mData);
    return d->getProperty(_name);
}

template<typename T>
void LClassVariantReference<T>::setProperty(const LString &_name, const LVariant &_in)
{
    T* d=((T*)mData);
    d->setProperty(_name,_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void LVariant::setFromCustomClass(T _in)
{
    if(mTypeName==lGetTypeName<T>()&&mType==VariantType::TCustom)
    {
        T* ptr=(T*)mCustomClass->mData;
        (*ptr)=_in;
        return;
    }
    if(mTypeName==lGetTypeName<T>()&&mType==VariantType::TCustomReference)
    {
        T* ptr=(T*)mCustomClass->mData;
        (*ptr)=*_in;
        return;
    }
    this->destroy();
    mTypeName=lGetTypeName<T>();
    mType=VariantType::TCustom;
    mCustomClass=new LClassVariant<T>(_in);
}

template<typename T>
void LVariant::setFromCustomReference(T* _in)
{
    if(mTypeName==lGetTypeName<T>()&&mType==VariantType::TCustomReference)
    {
        T* ptr=(T*)mCustomClass->mData;
        (*ptr)=*_in;
        return;
    }
    this->destroy();
    mTypeName=lGetTypeName<typename LRemovePointer<T>::type>();
    mType=VariantType::TCustomReference;
    mCustomClass=new LClassVariantReference<T>(*_in);
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
