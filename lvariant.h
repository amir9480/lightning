#ifndef LVARIANT_H
#define LVARIANT_H

#include "ldefines.h"
#include "llog.h"
#include "lutility.h"
#include "lvector.h"
#include <initializer_list>

LNAMESPACE_BEGIN

class LAPI LCustomVariant
{
    friend class LVariant;
public:
    LCustomVariant(){}
    virtual ~LCustomVariant(){}
protected:
    void* mData;
};

template<typename T>
class LClassVariant:public LCustomVariant
{
public:
    LClassVariant(const T& _in);
    virtual ~LClassVariant();
};

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

    template<typename T>
    LVariant(T _in);

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

    //! Get Property of Class Varaint
    virtual const LVariant*         getProperty(const LString& _propertyname)const;

    //! check is this a valid array
    bool                            isValidArray()const;

    //! check is this a valid reference
    bool                            isValidReference()const;

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

    template<typename T>
    LVariant& operator=(T _in);

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
LVariant::LVariant(const T _in):
    LVariant()
{
    (*this)=_in;
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
    static void call(void*& _a,void* _b){_a=_b;}
};

template<typename T>
LVariant &LVariant::operator=(T _in)
{
    if(mTypeName==lGetTypeName<T>()&&mType==VariantType::TCustom)
    {
        T* ptr=(T*)mCustomClass->mData;
        (*ptr)=_in;
        return *this;
    }
    if(mTypeName==lGetTypeName<T>()&&mType==VariantType::TCustomReference)
    {
        T* ptr=(T*)mCustom;
        (*ptr)=_in;
        return *this;
    }

    if(LIsPointer<T>::value)
    {
        this->destroy();
        mTypeName=lGetTypeName<typename LRemovePointer<T>::type>();
        mType=VariantType::TCustomReference;
        ___l_var_callif<LIsPointer<T>::value>::call(mCustom,_in);
    }
    else
    {
        this->destroy();
        mTypeName=lGetTypeName<T>();
        mType=VariantType::TCustom;
        mCustomClass=new LClassVariant<T>(_in);
    }
    return *this;
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
        return *((T*)mCustom);

    return *static_cast<T*>(mCustom);
}




LNAMESPACE_END

#endif // LVARIANT_H
