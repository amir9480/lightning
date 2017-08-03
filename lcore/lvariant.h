#ifndef LVARIANT_H
#define LVARIANT_H

#include "ldefines.h"
#include "lmemory.h"
#include "lstring.h"
#include "lutility.h"
#include "llog.h"

LNAMESPACE_BEGIN

//! forward decl
class LVariant;


class LAPI LCustomVariant
{
    template<typename T>
    friend struct __LVariantTypeCastHelper;

    friend class LVariant;
public:
    LCustomVariant(){}
    virtual ~LCustomVariant(){}



protected:

};

template<typename T>
class LAPI LCLassVariant:public LCustomVariant
{
    template<typename T2>
    friend struct __LVariantTypeCastHelper;

    friend class LVariant;
public:
    LCLassVariant(const T& _item);
    virtual ~LCLassVariant();

private:
    T   mData;
};

template<typename T>
class LAPI LClassVariantReference:public LCustomVariant
{
    template<typename T2>
    friend struct __LVariantTypeCastHelper;

    friend class LVariant;
public:
    LClassVariantReference(T& _item);
    virtual ~LClassVariantReference();

private:
    T*  mData;
};

template<typename T>
struct LAPI __LVariantTypeCastHelper
{
    static T cast(const LVariant& _in);
};
template<typename T>
struct LAPI __LVariantTypeCastHelper<T&>
{
    static T& cast(const LVariant& _in);
};
template<typename T>
struct LAPI __LVariantTypeCastHelper<T*>
{
    static T* cast(const LVariant& _in);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LAPI LVariant
{
    template<typename T>
    friend struct __LVariantTypeCastHelper;

public:
    enum class Type
    {
        TNull,

        TInt,   //int type
        TUInt,
        TFloat,
        TDouble,
        TLongDouble,
        TBool,
        TShortInt,
        TUShortInt,
        TLongLongInt,
        TULongLongInt,
        TChar,
        TUChar,
        TWChar_t,
        TChar16_t,
        TChar32_t,
        TString,

        TIntR,// int reference type
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

        TCustom,//custom class
        TCustomR,//Custom class reference
    };

public:
    LVariant();
    LVariant(int _val);
    LVariant(unsigned int _val);
    LVariant(float _val);
    LVariant(double _val);
    LVariant(long double _val);
    LVariant(bool _val);
    LVariant(short int _val);
    LVariant(unsigned short int _val);
    LVariant(long long int _val);
    LVariant(unsigned long long int _val);
    LVariant(char _val);
    LVariant(unsigned char _val);
    LVariant(wchar_t _val);
    LVariant(char16_t _val);
    LVariant(char32_t _val);
    LVariant(char* _val);
    LVariant(wchar_t* _val);
    LVariant(char32_t* _val);
    LVariant(const char* _val);
    LVariant(const wchar_t* _val);
    LVariant(const char32_t* _val);
    LVariant(LString _val);

    LVariant(int* _val);
    LVariant(unsigned int* _val);
    LVariant(float* _val);
    LVariant(double* _val);
    LVariant(long double* _val);
    LVariant(bool* _val);
    LVariant(short int* _val);
    LVariant(unsigned short int* _val);
    LVariant(long long int* _val);
    LVariant(unsigned long long int* _val);
    LVariant(LString* _val);

    virtual ~LVariant();

    //! destroy variant data
    void                    destroy();

    //! get type of variant
    Type                    getType() const;

    //! get typeid of variant
    LString                 getTypeName() const;

    int                     toInt()const;
    unsigned int            toUInt()const;
    float                   toFloat()const;
    double                  toDouble()const;
    long double             toLongDouble()const;
    bool                    toBool()const;
    short int               toShortInt()const;
    unsigned short int      toUShortInt()const;
    long long int           toLongLongInt()const;
    unsigned long long int  toULongLongInt()const;
    char                    toChar()const;
    unsigned char           toUChar()const;
    wchar_t                 toWChar_t()const;
    char16_t                toChar16_t()const;
    char32_t                toChar32_t()const;
    LString                 toString()const;

    template<typename T>
    T                       to();



    LVariant&               operator=(int _val);
    LVariant&               operator=(unsigned int _val);
    LVariant&               operator=(float _val);
    LVariant&               operator=(double _val);
    LVariant&               operator=(long double _val);
    LVariant&               operator=(bool _val);
    LVariant&               operator=(short int _val);
    LVariant&               operator=(unsigned short int _val);
    LVariant&               operator=(long long int _val);
    LVariant&               operator=(unsigned long long int _val);
    LVariant&               operator=(char _val);
    LVariant&               operator=(unsigned char _val);
    LVariant&               operator=(wchar_t _val);
    LVariant&               operator=(char16_t _val);
    LVariant&               operator=(char32_t _val);
    LVariant&               operator=(char* _val);
    LVariant&               operator=(wchar_t* _val);
    LVariant&               operator=(char32_t* _val);
    LVariant&               operator=(const char* _val);
    LVariant&               operator=(const wchar_t* _val);
    LVariant&               operator=(const char32_t* _val);
    LVariant&               operator=(LString _val);

    LVariant&               operator=(int* _val);
    LVariant&               operator=(unsigned int* _val);
    LVariant&               operator=(float* _val);
    LVariant&               operator=(double* _val);
    LVariant&               operator=(long double* _val);
    LVariant&               operator=(bool* _val);
    LVariant&               operator=(short int* _val);
    LVariant&               operator=(unsigned short int* _val);
    LVariant&               operator=(long long int* _val);
    LVariant&               operator=(unsigned long long int* _val);
    LVariant&               operator=(LString* _val);

    template<typename T>
    LVariant&               operator=(const T& _val);

    template<typename T>
    LVariant&               operator=(T* _val);

private:
    template<typename T>
    T                       _convert()const;

private:
    Type                        mType;
    LString                     mTypeName;
    union
    {
        int                     mInt;
        unsigned int            mUInt;
        float                   mFloat;
        double                  mDouble;
        long double             mLongDouble;
        bool                    mBool;
        short int               mShortInt;
        unsigned short int      mUShortInt;
        long long int           mLongLongInt;
        unsigned long long int  mULongLongInt;
        char                    mChar;
        unsigned char           mUChar;
        wchar_t                 mWChar_t;
        unsigned wchar_t        mUWChar_t;
        char16_t                mChar16_t;
        char32_t                mChar32_t;
        LString*                mString;

        void*                   mCustom;
        LCustomVariant*         mCustomClass;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LCLassVariant<T>::LCLassVariant(const T &_item):
    mData(_item)
{

}

template<typename T>
LCLassVariant<T>::~LCLassVariant()
{

}



template<typename T>
LClassVariantReference<T>::LClassVariantReference(T& _item):
    mData(&_item)
{

}

template<typename T>
LClassVariantReference<T>::~LClassVariantReference()
{

}


template<typename T>
T __LVariantTypeCastHelper<T>::cast(const LVariant &_in)
{
    if(LIsSameType<typename LRemoveReference<T>::type,int>::value || LIsSameType<typename LRemoveReference<T>::type,const int>::value)
    {
        int o=_in.toInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned int>::value)
    {
        unsigned int o=_in.toUInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,float>::value || LIsSameType<typename LRemoveReference<T>::type,const float>::value)
    {
        float o=_in.toFloat();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,double>::value || LIsSameType<typename LRemoveReference<T>::type,const double>::value)
    {
        double o=_in.toDouble();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,long double>::value || LIsSameType<typename LRemoveReference<T>::type,const long double>::value)
    {
        long double o=_in.toLongDouble();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,bool>::value || LIsSameType<typename LRemoveReference<T>::type,const bool>::value)
    {
        bool o=_in.toBool();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,short int>::value || LIsSameType<typename LRemoveReference<T>::type,const short int>::value)
    {
        short int o=_in.toShortInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned short int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned short int>::value)
    {
        unsigned short int o=_in.toUShortInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const long long  int>::value)
    {
        long long  int o=_in.toLongLongInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned long long  int>::value)
    {
        unsigned long long  int o=_in.toULongLongInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char>::value || LIsSameType<typename LRemoveReference<T>::type,const char>::value)
    {
        char o=_in.toChar();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned char>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned char>::value)
    {
        unsigned char o=_in.toUChar();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,wchar_t>::value || LIsSameType<typename LRemoveReference<T>::type,const wchar_t>::value)
    {
        wchar_t o=_in.toWChar_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char16_t>::value || LIsSameType<typename LRemoveReference<T>::type,const char16_t>::value)
    {
        char16_t o=_in.toChar16_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char32_t>::value || LIsSameType<typename LRemoveReference<T>::type,const char32_t>::value)
    {
        char32_t o=_in.toChar32_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,LString>::value || LIsSameType<typename LRemoveReference<T>::type,const LString>::value)
    {
        LString o=_in.toString();
        return *((T*)&o);
    }

    lError2( (_in.mType!=LVariant::Type::TCustom && _in.mType!=LVariant::Type::TCustomR) || _in.mTypeName!=lGetTypeName<T>() ,"Your type casting is not right");

    if(_in.mType==LVariant::Type::TCustom)
        return (dynamic_cast<LCLassVariant<T>*>(_in.mCustomClass)->mData);
    if(_in.mType==LVariant::Type::TCustomR)
        return *(dynamic_cast<LClassVariantReference<T>*>(_in.mCustomClass)->mData);

    return *static_cast<T*>(_in.mCustom);
}

template<typename T>
T& __LVariantTypeCastHelper<T&>::cast(const LVariant &_in)
{
    if(LIsSameType<typename LRemoveReference<T>::type,int>::value || LIsSameType<typename LRemoveReference<T>::type,const int>::value)
    {
        static int o;
        o=_in.toInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned int>::value)
    {
        static unsigned int o;
        o=_in.toUInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,float>::value || LIsSameType<typename LRemoveReference<T>::type,const float>::value)
    {
        static float o;
        o=_in.toFloat();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,double>::value || LIsSameType<typename LRemoveReference<T>::type,const double>::value)
    {
        static double o;
        o=_in.toDouble();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,long double>::value || LIsSameType<typename LRemoveReference<T>::type,const long double>::value)
    {
        static long double o;
        o=_in.toLongDouble();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,bool>::value || LIsSameType<typename LRemoveReference<T>::type,const bool>::value)
    {
        static bool o;
        o=_in.toBool();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,short int>::value || LIsSameType<typename LRemoveReference<T>::type,const short int>::value)
    {
        static short int o;
        o=_in.toShortInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned short int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned short int>::value)
    {
        static unsigned short int o;
        o=_in.toUShortInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const long long  int>::value)
    {
        static long long  int o;
        o=_in.toLongLongInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned long long  int>::value)
    {
        static unsigned long long  int o;
        o=_in.toULongLongInt();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char>::value || LIsSameType<typename LRemoveReference<T>::type,const char>::value)
    {
        static char o;
        o=_in.toChar();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,unsigned char>::value || LIsSameType<typename LRemoveReference<T>::type,const unsigned char>::value)
    {
        static unsigned char o;
        o=_in.toUChar();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,wchar_t>::value || LIsSameType<typename LRemoveReference<T>::type,const wchar_t>::value)
    {
        static wchar_t o;
        o=_in.toWChar_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char16_t>::value || LIsSameType<typename LRemoveReference<T>::type,const char16_t>::value)
    {
        static char16_t o;
        o=_in.toChar16_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,char32_t>::value || LIsSameType<typename LRemoveReference<T>::type,const char32_t>::value)
    {
        static char32_t o;
        o=_in.toChar32_t();
        return *((T*)&o);
    }
    else if(LIsSameType<typename LRemoveReference<T>::type,LString>::value || LIsSameType<typename LRemoveReference<T>::type,const LString>::value)
    {
        static LString o;
        o=_in.toString();
        return *((T*)&o);
    }

    if(_in.mType==LVariant::Type::TCustom)
        return (dynamic_cast<LCLassVariant<T>*>(_in.mCustomClass)->mData);
    if(_in.mType==LVariant::Type::TCustomR)
        return *(dynamic_cast<LClassVariantReference<T>*>(_in.mCustomClass)->mData);

    return *static_cast<T*>(_in.mCustom);
}

template<typename T>
T* __LVariantTypeCastHelper<T*>::cast(const LVariant &_in)
{

    if(_in.mType==LVariant::Type::TCustom)
        return &(dynamic_cast<LCLassVariant<T>*>(_in.mCustomClass)->mData);
    if(_in.mType==LVariant::Type::TCustomR)
        return (dynamic_cast<LClassVariantReference<T>*>(_in.mCustomClass)->mData);

    return *static_cast<T*>(_in.mCustom);
}
////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
LVariant& LVariant::operator=(const T& _val)
{
    if(mTypeName==lGetTypeName<T>())
    {
        if(mType==Type::TCustom)
        {
            T* _ptr = &(dynamic_cast<LCLassVariant<T>*>(mCustomClass)->mData);
            (*_ptr)=_val;
        }
        else if(mType==Type::TCustomR)
        {
            T* _ptr = (dynamic_cast<LClassVariantReference<T>*>(mCustomClass)->mData);
            (*_ptr)=_val;
        }
        return *this;
    }
    this->destroy();
    mType=Type::TCustom;
    mTypeName=lGetTypeName<T>();
    mCustomClass=new LCLassVariant<T>(_val);
    return *this;
}

template<typename T>
LVariant& LVariant::operator=(T* _val)
{
    this->destroy();
    mTypeName = lGetTypeName<typename LRemovePointer<T>::type>();
    mType=Type::TCustomR;
    mCustomClass =new LClassVariantReference<T>(*_val);
    return *this;
}

template<typename T>
T LVariant::_convert() const
{
    switch(mType)
    {
    case Type::TInt:
        return (T)mInt;
    case Type::TUInt:
        return (T)mUInt;
    case Type::TFloat:
        return (T)mFloat;
    case Type::TDouble:
        return (T)mDouble;
    case Type::TLongDouble:
        return (T)mLongDouble;
    case Type::TBool:
        return (T)mBool;
    case Type::TShortInt:
        return (T)mShortInt;
    case Type::TUShortInt:
        return (T)mUShortInt;
    case Type::TLongLongInt:
        return (T)mLongLongInt;
    case Type::TULongLongInt:
        return (T)mULongLongInt;
    case Type::TChar:
        return (T)mChar;
    case Type::TUChar:
        return (T)mUChar;
    case Type::TWChar_t:
        return (T)mWChar_t;
    case Type::TChar16_t:
        return (T)mChar16_t;
    case Type::TChar32_t:
        return (T)mChar32_t;
    case Type::TString:
    {
        return (*((T*)&mString));
    }

    case Type::TIntR:
        return (T)(*((int*)mCustom));
    case Type::TUIntR:
        return (T)(*((unsigned int*)mCustom));
    case Type::TFloatR:
        return (T)(*((float*)mCustom));
    case Type::TDoubleR:
        return (T)(*((double*)mCustom));
    case Type::TLongDoubleR:
        return (T)(*((long double*)mCustom));
    case Type::TBoolR:
        return (T)(*((bool*)mCustom));
    case Type::TShortIntR:
        return (T)(*((short int*)mCustom));
    case Type::TUShortIntR:
        return (T)(*((unsigned short*)mCustom));
    case Type::TLongLongIntR:
        return (T)(*((long long int*)mCustom));
    case Type::TULongLongIntR:
        return (T)(*((unsigned long long int*)mCustom));
    case Type::TStringR:
    {
        return (*((T*)mCustom));
    }
    default:
        break;
    }
    return *static_cast<T*>(mCustom);
}


template<typename T>
T LVariant::to()
{
    return __LVariantTypeCastHelper<T>::cast(*this);
}

LNAMESPACE_END

#endif // LVARIANT_H
