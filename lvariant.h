#ifndef LVARIANT_H
#define LVARIANT_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"
#include <initializer_list>

LNAMESPACE_BEGIN

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
        TCustom, // custom classes


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

    virtual ~LVariant();

    //! destroy current data
    virtual void                    destroy();

    //! set variant from stirng
    virtual void                    fromString(const LString& _in);

    //! Get Valid type of this variant
    VariantType                     getType()const;

    //! Get Type name of this Varaint
    LString                         getTypeName() const;

    //! check is this a valid array
    bool                            isValidArray()const;

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
    linline T                       to()const;

    LVariant& operator=(int _in);
    LVariant& operator=(unsigned int _in);
    LVariant& operator=(float _in);
    LVariant& operator=(double _in);
    LVariant& operator=(long double _in);
    LVariant& operator=(char _in);
    LVariant& operator=(unsigned char _in);
    LVariant& operator=(bool _in);
    LVariant& operator=(short int _in);
    LVariant& operator=(unsigned short int _in);
    LVariant& operator=(long long int  _in);
    LVariant& operator=(unsigned long long int _in);
    LVariant& operator=(wchar_t _in);
    LVariant& operator=(LString _in);
    LVariant& operator=(const char* _in);
    LVariant& operator=(const wchar_t* _in);
    LVariant& operator=(const char32_t* _in);

    LVariant& operator=(const std::initializer_list<int>& _in);
    LVariant& operator=(const std::initializer_list<unsigned int>& _in);
    LVariant& operator=(const std::initializer_list<float>& _in);
    LVariant& operator=(const std::initializer_list<double>& _in);
    LVariant& operator=(const std::initializer_list<long double>& _in);
    LVariant& operator=(const std::initializer_list<char>& _in);
    LVariant& operator=(const std::initializer_list<unsigned char>& _in);
    LVariant& operator=(const std::initializer_list<bool>& _in);
    LVariant& operator=(const std::initializer_list<short int>& _in);
    LVariant& operator=(const std::initializer_list<unsigned short int>& _in);
    LVariant& operator=(const std::initializer_list<long long int>&  _in);
    LVariant& operator=(const std::initializer_list<unsigned long long int>& _in);
    LVariant& operator=(const std::initializer_list<wchar_t>& _in);
    LVariant& operator=(const std::initializer_list<const char*>& _in);// for string

    LVariant  operator[](u32 _i)const;

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

        LVector<int>*                    mIntA;
        LVector<unsigned int>*           mUIntA;
        LVector<float>*                  mFloatA;
        LVector<double>*                 mDoubleA;
        LVector<long double>*            mLongDoubleA;
        LVector<char>*                   mCharA;
        LVector<unsigned char>*          mUCharA;
        LVector<bool>*                   mBoolA;
        LVector<short int>*              mShortIntA;
        LVector<unsigned short int>*     mUShortIntA;
        LVector<long long int>*          mLongLongIntA;
        LVector<unsigned long long int>* mULongLongIntA;
        LVector<wchar_t>*                mWCharTA;
        LVector<LString>*                mStringA;

        void*                            mCustom;
    };
};


template<typename T>
class LClassVariant:public LVariant
{
public:
    LClassVariant();
    LClassVariant(const T& _in);
    virtual ~LClassVariant();

    void destroy();

    void fromString(const LString &_in);

    LString toString() const;

    LClassVariant<T>& operator=(const LClassVariant<T>& _in);

};


////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T LVariant::to() const
{
    lError2(mTypeName!=lGetTypeName<T>(),"Looks like type is not correct");
    if( LIsSameType<T,int>::value )
        return *((T*)&mInt);
    if( LIsSameType<T,unsigned int>::value )
        return *((T*)&mUInt);
    if( LIsSameType<T,float>::value )
        return *((T*)&mFloat);
    if( LIsSameType<T,double>::value )
        return *((T*)&mDouble);
    if( LIsSameType<T,long double>::value )
        return *((T*)&mLongDouble);
    if( LIsSameType<T,char>::value )
        return *((T*)&mChar);
    if( LIsSameType<T,unsigned char>::value )
        return *((T*)&mUChar);
    if( LIsSameType<T,bool>::value )
        return *((T*)&mBool);
    if( LIsSameType<T,short int>::value )
        return *((T*)&mShortInt);
    if( LIsSameType<T,unsigned short int>::value )
        return *((T*)&mUShortInt);
    if( LIsSameType<T,long long int>::value )
        return *((T*)&mLongLongInt);
    if( LIsSameType<T,unsigned long long int>::value )
        return *((T*)&mULongLongInt);
    if( LIsSameType<T,wchar_t>::value )
        return *((T*)&mWCharT);
    return *static_cast<T*>(mCustom);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LClassVariant<T>::LClassVariant()
{
    mType=VariantType::TCustom;
    mTypeName=lGetTypeName<T>();
    mCustom=(void*)new T;
}

template<typename T>
LClassVariant<T>::LClassVariant(const T &_in)
{
    mType=VariantType::TCustom;
    mTypeName=lGetTypeName<T>();
    mCustom=(void*)new T(_in);
}

template<typename T>
LClassVariant<T>::~LClassVariant()
{
    destroy();
}

template<typename T>
void LClassVariant<T>::destroy()
{
    if(mType==VariantType::TNull)
        return;
    if(mTypeName!=lGetTypeName<T>())
    {
        dynamic_cast<LVariant*>(this)->destroy();
        return;
    }
    T* ptr=(T*)mCustom;
    delete ptr;
    mType=VariantType::TNull;
    mTypeName.clear();
}

template<typename T>
void LClassVariant<T>::fromString(const LString &_in)
{
    if(mType!=TCustom)
        return;
    T* ptr=(T*)mCustom;
    ptr->lFromString(_in);
}

template<typename T>
LString LClassVariant<T>::toString() const
{
    if(mType!=TCustom)
        return LString::empty;
    T* ptr=(T*)mCustom;
    return ptr->lToString();
}

template<typename T>
LClassVariant<T>& LClassVariant<T>::operator=(const LClassVariant<T>& _in)
{
    destroy();
    mType=_in.mType;
    mTypeName=_in.mTypeName;
    mCustom=new T;
    T* ptr=(T*)mCustom;
    (*ptr)=*((T*)_in.mCustom);
    return *this;
}


LNAMESPACE_END

#endif // LVARIANT_H
