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

    virtual LCustomVariant* clone()=0;// get a copy of this

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

    virtual LCustomVariant* clone();

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

    virtual LCustomVariant* clone();

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
/*!
 * Working with variants
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
 *
 * LVariant a = LVariant::create(TestClass(...));
 *
 *  * Or *
 *
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
 * You can also use:
 * cout<<a.to<int>()<<endl;
 * or:
 * cout<<(int)a<<endl;
 *
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
 * how to create dynamic variant?
 * LVariant a = new int(44);
 *
 * how use it
 * ... a.to<int*>() ...
 *
 * how to delete it?
 * delete a.to<int*>();
 *
 * call a.destroy() will NOT free your allocated memory so free it before destroy
 *
 */
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

        TEnum,
        TEnumR,

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
    LVariant(const LVariant& _other);

    virtual ~LVariant();

    template<typename T>
    static LVariant         create(const T& _val);

    template<typename T>
    static LVariant         create(T* _val);

    //! destroy variant data
    void                    destroy();

    //! get type of variant
    Type                    getType() const;

    //! get typeid of variant
    LString                 getTypeName() const;

    //! is convertible by typename
    bool                    isConverible(const LString& _typename)const;

    //! is convertible by type
    template<typename T>
    bool                    isConverible()const;


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

    LVariant&               operator=(const LVariant& _other);

    template<typename T>
    operator T();

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
        char16_t                mChar16_t;
        char32_t                mChar32_t;
        LString*                mString;

        void*                   mCustom;
        LCustomVariant*         mCustomClass;
    };
    unsigned int                mValueSize;
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
LCustomVariant *LCLassVariant<T>::clone()
{
    LCLassVariant* o=new LCLassVariant(mData);
    return o;
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
LCustomVariant *LClassVariantReference<T>::clone()
{
    LClassVariantReference* o=new LClassVariantReference(*mData);
    return o;
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
    else if(LIsSameType<typename LRemoveReference<T>::type,LVariant>::value || LIsSameType<typename LRemoveReference<T>::type,const LVariant>::value)
    {
        LVariant o=_in;
        return *((T*)&o);
    }

    lError2( (_in.mType!=LVariant::Type::TCustom && _in.mType!=LVariant::Type::TCustomR && _in.mType!=LVariant::Type::TEnum && _in.mType != LVariant::Type::TEnumR ) && _in.mTypeName!=lGetTypeName<T>() ,"Your type casting is not right");

    if(_in.mType==LVariant::Type::TEnum)
    {
        switch (sizeof(T))
        {
        case 1:
        {
            i8 value = (i8)_in.mLongLongInt;
            return *((T*)(&value));
        }
        case 2:
        {
            i16 value = (i16)_in.mLongLongInt;
            return *((T*)(&value));
        }
        case 4:
        {
            i32 value = (i32)_in.mLongLongInt;
            return *((T*)(&value));
        }
        case 8:
        {
            i64 value = (i64)_in.mLongLongInt;
            return *((T*)(&value));
        }
        default:
            break;
        }
    }
    if(_in.mType==LVariant::Type::TEnumR)
    {
        T* value = (T*)_in.mCustom;
        return *value;
    }
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
    else if(LIsSameType<typename LRemoveReference<T>::type,long long int>::value || LIsSameType<typename LRemoveReference<T>::type,const long long  int>::value )
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
        lMemoryLogStartIgnore();
        static LString o;
        lMemoryLogEndIgnore();
        o=_in.toString();
        return *((T*)&o);
    }
    else if(_in.mType>=LVariant::Type::TIntR&&_in.mType<=LVariant::Type::TStringR)
        return *static_cast<T*>(_in.mCustom);

    //lError2(_in.mTypeName!=lGetTypeName<T>(),"LVariant Converting is not right");


    if(_in.mType==LVariant::Type::TEnum)
    {
        static T* value = (T*)_in.mLongLongInt;
        return *value;
    }
    if(_in.mType==LVariant::Type::TEnumR)
    {
        T* value = (T*)_in.mCustom;
        return *value;
    }
    if(_in.mType==LVariant::Type::TCustom)
        return (reinterpret_cast<LCLassVariant<T>*>(_in.mCustomClass)->mData);
    if(_in.mType==LVariant::Type::TCustomR)
        return *(reinterpret_cast<LClassVariantReference<T>*>(_in.mCustomClass)->mData);
    lMemoryLogStartIgnore();
    static T o = T();
    lMemoryLogEndIgnore();
    return o;
}

template<typename T>
T* __LVariantTypeCastHelper<T*>::cast(const LVariant &_in)
{
    if(LIsSameType<typename LRemoveReference<T*>::type,char*>::value || LIsSameType<typename LRemoveReference<T*>::type,const char*>::value)
    {
        LString8 _o = _in.mString->toUTF8();
        lMemoryLogStartIgnore();
        static char* o = nullptr;
        if(o)
           delete[] o;
        o = new char[_o.getCapacity()+1];
        lMemoryCopy(o,_o.getData(),(_o.getCapacity()*sizeof(char))+1);
        lMemoryLogEndIgnore();
        return (*((T**)&o));
    }
    else if(LIsSameType<typename LRemoveReference<T*>::type,wchar_t*>::value || LIsSameType<typename LRemoveReference<T*>::type,const wchar_t*>::value)
    {
        LString _o = *_in.mString;
        lMemoryLogStartIgnore();
        static wchar_t* o = nullptr;
        if(o)
            delete[] o;
        o = new wchar_t[_o.getCapacity()+1];
        lMemoryCopy(o,_o.getData(),(_o.getCapacity()*sizeof(wchar_t))+1);
        lMemoryLogEndIgnore();
        return (*((T**)&o));
    }
    else if(LIsSameType<typename LRemoveReference<T*>::type,char32_t*>::value || LIsSameType<typename LRemoveReference<T*>::type,const char32_t*>::value)
    {
        LString32 _o = _in.mString->toUTF32();
        lMemoryLogStartIgnore();
        static char32_t* o = nullptr;
        if(o)
            delete[] o;
        o = new char32_t[_o.getCapacity()+1];
        lMemoryCopy(o,_o.getData(),(_o.getCapacity()*sizeof(char32_t))+1);
        lMemoryLogEndIgnore();
        return (*((T**)&o));
    }
    else if(_in.mType>=LVariant::Type::TIntR&&_in.mType<=LVariant::Type::TStringR)
        return static_cast<T*>(_in.mCustom);

    lLogMessage(1,LString::fromInt((int)_in.mType));

    //lError2(_in.mTypeName!=lGetTypeName<T>(),"LVariant Converting is not right");

    if(_in.mType==LVariant::Type::TEnumR)
        return ((T*)_in.mCustom);

    if(_in.mType==LVariant::Type::TCustom)
        return &(dynamic_cast<LCLassVariant<T>*>(_in.mCustomClass)->mData);
    if(_in.mType==LVariant::Type::TCustomR)
        return (dynamic_cast<LClassVariantReference<T>*>(_in.mCustomClass)->mData);
    lError2(1,"You\'r type casting is not right");
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
LVariant& LVariant::operator=(const T& _val)
{
    if(mType==Type::TEnum||mType==Type::TEnumR)
    {
        if(     LIsSameType<int,T>::value||
                LIsSameType<unsigned int,T>::value  ||
                LIsSameType<short int,T>::value ||
                LIsSameType<unsigned short int,T>::value ||
                LIsSameType<long long int,T>::value ||
                LIsSameType<unsigned long long int,T>::value )
        {
            if(mType==Type::TEnum)
            {
                switch (sizeof(T))
                {
                case 1:
                {
                    i8* value = (i8*)&_val;
                    mLongLongInt=(long long int)(*value);
                    break;
                }
                case 2:
                {
                    i16* value = (i16*)&_val;
                    mLongLongInt=(long long int)(*value);
                    break;
                }
                case 4:
                {
                    i32* value = (i32*)&_val;
                    mLongLongInt=(long long int)(*value);
                    break;
                }
                case 8:
                {
                    i64* value = (i64*)&_val;
                    mLongLongInt=(long long int)(*value);
                    break;
                }
                default:
                    break;
                }
            }
            else
            {
                switch (mValueSize)
                {
                case 1:
                {
                    i8* value = (i8*)mCustom;
                    *value = *((i8*)&_val);
                    break;
                }
                case 2:
                {
                    i16* value = (i16*)mCustom;
                    *value = *((i16*)&_val);
                    break;
                }
                case 4:
                {
                    i32* value = (i32*)mCustom;
                    *value = *((i32*)&_val);
                    break;
                }
                case 8:
                {
                    i64* value = (i64*)mCustom;
                    *value = *((i64*)&_val);
                    break;
                }
                default:
                    break;
                }
            }
            return *this;
        }
    }
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
        else if(mType==Type::TEnum)
        {
            switch (sizeof(T))
            {
            case 1:
            {
                i8* value = (i8*)&_val;
                mLongLongInt=(long long int)(*value);
                break;
            }
            case 2:
            {
                i16* value = (i16*)&_val;
                mLongLongInt=(long long int)(*value);
                break;
            }
            case 4:
            {
                i32* value = (i32*)&_val;
                mLongLongInt=(long long int)(*value);
                break;
            }
            case 8:
            {
                i64* value = (i64*)&_val;
                mLongLongInt=(long long int)(*value);
                break;
            }
            default:
                break;
            }
        }
        else if(mType==Type::TEnumR)
        {
            T* value = (T*)mCustom;
            *value = _val;
        }
        return *this;
    }
    this->destroy();
    if(LIsEnum<T>::value)
    {
        mType=Type::TEnum;
        switch (sizeof(T))
        {
        case 1:
        {
            i8* value = (i8*)&_val;
            mLongLongInt=(long long int)(*value);
            break;
        }
        case 2:
        {
            i16* value = (i16*)&_val;
            mLongLongInt=(long long int)(*value);
            break;
        }
        case 4:
        {
            i32* value = (i32*)&_val;
            mLongLongInt=(long long int)(*value);
            break;
        }
        case 8:
        {
            i64* value = (i64*)&_val;
            mLongLongInt=(long long int)(*value);
            break;
        }
        default:
            break;
        }
    }
    else
    {
        mType=Type::TCustom;
        mCustomClass=new LCLassVariant<T>(_val);
    }
    mTypeName=lGetTypeName<T>();
    mValueSize=sizeof(T);
    return *this;
}

template<typename T>
LVariant& LVariant::operator=(T* _val)
{
    this->destroy();
    mTypeName = lGetTypeName<typename LRemovePointer<T>::type>();
    if(LIsEnum<T>::value)
    {
        mType=Type::TEnumR;
        mCustom=(void*)_val;
    }
    else
    {
        mType=Type::TCustomR;
        mCustomClass =new LClassVariantReference<T>(*_val);
    }
    mValueSize=sizeof(T);
    return *this;
}


template<typename T>
LVariant LVariant::create(const T& _val)
{
    LVariant o;
    o=_val;
    return o;
}

template<typename T>
LVariant LVariant::create(T* _val)
{
    LVariant o;
    o=_val;
    return o;
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

    case Type::TEnum:
    {
        if(     LIsSameType<int,T>::value||
                LIsSameType<unsigned int,T>::value  ||
                LIsSameType<short int,T>::value ||
                LIsSameType<unsigned short int,T>::value ||
                LIsSameType<long long int,T>::value ||
                LIsSameType<unsigned long long int,T>::value )
        {
            switch (sizeof(T))
            {
            case 1:
            {
                i8 value = (i8)mLongLongInt;
                return *((T*)(&value));
            }
            case 2:
            {
                i16 value = (i16)mLongLongInt;
                return *((T*)(&value));
            }
            case 4:
            {
                i32 value = (i32)mLongLongInt;
                return *((T*)(&value));
            }
            case 8:
            {
                i64 value = (i64)mLongLongInt;
                return *((T*)(&value));
            }
            default:
                break;
            }
        }
        break;
    }
    case Type::TEnumR:
    {
        switch (mValueSize)
        {
        case 1:
        {
            i8* value = (i8*)mCustom;
            return *((T*)value);
            break;
        }
        case 2:
        {
            i16* value = (i16*)mCustom;
            return *((T*)value);
            break;
        }
        case 4:
        {
            i32* value = (i32*)mCustom;
            return *((T*)value);
            break;
        }
        case 8:
        {
            i64* value = (i64*)mCustom;
            return *((T*)value);
            break;
        }
        default:
            break;
        }
        break;
    }


    default:
        break;
    }
    return *static_cast<T*>(mCustom);
}


template<typename T>
bool LVariant::isConverible() const
{
    return isConverible(lGetTypeName<T>());
}

template<typename T>
T LVariant::to()
{
    return __LVariantTypeCastHelper<T>::cast(*this);
}

template<typename T>
LVariant::operator T()
{
    return this->to<T>();
}

LNAMESPACE_END

#endif // LVARIANT_H
