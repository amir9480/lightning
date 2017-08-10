#include "lvariant.h"

LNAMESPACE_BEGIN

LVariant::LVariant()
{
    mType=Type::TNull;
}

LVariant::LVariant(int _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned int _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(float _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(double _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(long double _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(bool _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(short _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned short _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(long long _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned long long _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(char _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned char _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(wchar_t _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(char16_t _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(char32_t _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(char *_val):
    LVariant()
{
    *this=LString::fromUTF8(_val);
}

LVariant::LVariant(wchar_t *_val):
    LVariant()
{
    *this=LString(_val);
}

LVariant::LVariant(char32_t *_val):
    LVariant()
{
    *this=LString(_val);
}

LVariant::LVariant(const char *_val):
    LVariant()
{
    *this=LString::fromUTF8(_val);
}

LVariant::LVariant(const wchar_t *_val):
    LVariant()
{
    *this=LString(_val);
}

LVariant::LVariant(const char32_t *_val):
    LVariant()
{
    *this=LString(_val);
}

LVariant::LVariant(LString _val):
    LVariant()
{
    *this=_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LVariant::LVariant(int* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned int* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(float* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(double* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(long double* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(bool* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(short* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned short* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(long long* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(unsigned long long* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(LString* _val):
    LVariant()
{
    *this=_val;
}

LVariant::LVariant(const LVariant &_other)
{
    *this=_other;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LVariant::~LVariant()
{
    destroy();
}

void LVariant::destroy()
{
    switch(mType)
    {
    case Type::TString:
        delete mString;
        break;
    case Type::TCustom:case Type::TCustomR:
        delete mCustomClass;
        break;
    default:
        break;
    }
    mType=Type::TNull;
    mTypeName.clear();
}

LVariant::Type LVariant::getType() const
{
    return mType;
}

LString LVariant::getTypeName() const
{
    return mTypeName;
}

bool LVariant::isConverible(const LString &_typename) const
{
    if(mType==Type::TNull)
        return false;
    if(mType>=Type::TInt&&mType<=Type::TString)
    {
        if(     lGetTypeName<int>()==_typename||
                lGetTypeName<unsigned int>()==_typename  ||
                lGetTypeName<float>()==_typename ||
                lGetTypeName<double>()==_typename ||
                lGetTypeName<long double>()==_typename ||
                lGetTypeName<bool>()==_typename ||
                lGetTypeName<short int>()==_typename ||
                lGetTypeName<unsigned short int>()==_typename ||
                lGetTypeName<long long int>()==_typename ||
                lGetTypeName<unsigned long long int>()==_typename||
                lGetTypeName<char>()==_typename ||
                lGetTypeName<unsigned char>()==_typename ||
                lGetTypeName<wchar_t>()==_typename ||
                lGetTypeName<char16_t>()==_typename ||
                lGetTypeName<char32_t>()==_typename ||
                lGetTypeName<LString>()==_typename
                )
            return true;
        else
            return false;
    }
    if(mType>=Type::TIntR&&mType<=Type::TStringR)
    {
        if(     lGetTypeName<int>()==_typename||
                lGetTypeName<unsigned int>()==_typename  ||
                lGetTypeName<float>()==_typename ||
                lGetTypeName<double>()==_typename ||
                lGetTypeName<long double>()==_typename ||
                lGetTypeName<bool>()==_typename ||
                lGetTypeName<short int>()==_typename ||
                lGetTypeName<unsigned short int>()==_typename ||
                lGetTypeName<long long int>()==_typename ||
                lGetTypeName<unsigned long long int>()==_typename||
                lGetTypeName<char>()==_typename ||
                lGetTypeName<unsigned char>()==_typename ||
                lGetTypeName<wchar_t>()==_typename ||
                lGetTypeName<char16_t>()==_typename ||
                lGetTypeName<char32_t>()==_typename ||
                lGetTypeName<LString>()==_typename ||
                lGetTypeName<int&>()==_typename||
                lGetTypeName<unsigned int&>()==_typename  ||
                lGetTypeName<float&>()==_typename ||
                lGetTypeName<double&>()==_typename ||
                lGetTypeName<long double&>()==_typename ||
                lGetTypeName<bool&>()==_typename ||
                lGetTypeName<short int&>()==_typename ||
                lGetTypeName<unsigned short int&>()==_typename ||
                lGetTypeName<long long int&>()==_typename ||
                lGetTypeName<unsigned long long int&>()==_typename||
                lGetTypeName<char&>()==_typename ||
                lGetTypeName<unsigned char&>()==_typename ||
                lGetTypeName<wchar_t&>()==_typename ||
                lGetTypeName<char16_t&>()==_typename ||
                lGetTypeName<char32_t&>()==_typename ||
                lGetTypeName<LString&>()==_typename)
            return true;
        else
            return false;
    }
    return (_typename==mTypeName);
}

int LVariant::toInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toInt();
    return _convert<int>();
}

unsigned int LVariant::toUInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toUInt();
    return _convert<unsigned int>();
}

float LVariant::toFloat()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toFloat();
    return _convert<float>();
}

double LVariant::toDouble()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toDouble();
    return _convert<double>();
}

long double LVariant::toLongDouble()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toLongDouble();
    return _convert<long double>();
}

bool LVariant::toBool()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
    {
        if(toString().toLower()=="true")
            return true;
        else if(toString().toLower()=="false")
            return false;
        return (bool)toString().toInt();
    }
    return _convert<bool>();
}

short LVariant::toShortInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toShortInt();
    return _convert<short int>();
}

unsigned short LVariant::toUShortInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toUShortInt();
    return _convert<unsigned short int>();
}

long long LVariant::toLongLongInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toLongLongInt();
    return _convert<long long int>();
}

unsigned long long LVariant::toULongLongInt()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return toString().toULongLongInt();
    return _convert<unsigned long long int>();
}

char LVariant::toChar()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return (char)toString()[0];
    return _convert<char>();
}

unsigned char LVariant::toUChar()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return (unsigned char)toString()[0];
    return _convert<unsigned char>();
}

wchar_t LVariant::toWChar_t()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return (wchar_t)toString()[0];
    return _convert<wchar_t>();
}

char16_t LVariant::toChar16_t()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return (char16_t)toString()[0];
    return _convert<char16_t>();
}

char32_t LVariant::toChar32_t()const
{
    lError(mType==Type::TNull,"LVariant is null",0);
    if(mType==Type::TString||mType==Type::TStringR)
        return (char32_t)toString()[0];
    return _convert<char32_t>();
}

LString LVariant::toString()const
{
    lError(mType==Type::TNull,"LVariant is null",LString::empty);
    switch (mType)
    {
    case Type::TString:
        return *mString;
    case Type::TStringR:
        return *((LString*)mCustom);
    case Type::TInt:case Type::TIntR:
        return LString::fromInt(toInt());
    case Type::TUInt:case Type::TUIntR:
        return LString::fromUInt(toUInt());
    case Type::TFloat:case Type::TFloatR:
        return LString::fromFloat(toFloat());
    case Type::TDouble:case Type::TDoubleR:
        return LString::fromDouble(toDouble());
    case Type::TLongDouble:case Type::TLongDoubleR:
        return LString::fromLongDouble(toLongDouble());
    case Type::TBool:case Type::TBoolR:
    {
        if(toBool())
            return LSTR("true");
        else
            return LSTR("false");
    }
    case Type::TShortInt:case Type::TShortIntR:
        return LString::fromShortInt(toShortInt());
    case Type::TUShortInt:case Type::TUShortIntR:
        return LString::fromUShortInt(toUShortInt());
    case Type::TLongLongInt:case Type::TLongLongIntR:
        return LString::fromLongLongInt(toLongLongInt());
    case Type::TULongLongInt:case Type::TULongLongIntR:
        return LString::fromULongLongInt(toULongLongInt());
    default:
        break;
    }
    return LString::empty;
}

LVariant &LVariant::operator=(const LVariant &_other)
{
    destroy();
    mTypeName=_other.mTypeName;
    mType=_other.mType;
    switch(mType)
    {
    case Type::TInt:
        mInt=_other.mInt;
        break;
    case Type::TUInt:
        mUInt=_other.mUInt;
        break;
    case Type::TFloat:
        mFloat=_other.mFloat;
        break;
    case Type::TDouble:
        mDouble=_other.mDouble;
        break;
    case Type::TLongDouble:
        mLongDouble=_other.mLongDouble;
        break;
    case Type::TBool:
        mBool=_other.mBool;
        break;
    case Type::TShortInt:
        mShortInt=_other.mShortInt;
        break;
    case Type::TUShortInt:
        mUShortInt=_other.mUShortInt;
        break;
    case Type::TLongLongInt:
        mLongLongInt=_other.mLongLongInt;
        break;
    case Type::TULongLongInt:
        mULongLongInt=_other.mULongLongInt;
        break;
    case Type::TChar:
        mChar=_other.mChar;
        break;
    case Type::TUChar:
        mUChar=_other.mUChar;
        break;
    case Type::TWChar_t:
        mWChar_t=_other.mWChar_t;
        break;
    case Type::TChar16_t:
        mChar16_t=_other.mChar16_t;
        break;
    case Type::TChar32_t:
        mChar32_t=_other.mChar32_t;
        break;
    case Type::TString:
        mString=_other.mString;
        break;

    case Type::TIntR:
    case Type::TUIntR:
    case Type::TFloatR:
    case Type::TDoubleR:
    case Type::TLongDoubleR:
    case Type::TBoolR:
    case Type::TShortIntR:
    case Type::TUShortIntR:
    case Type::TLongLongIntR:
    case Type::TULongLongIntR:
    case Type::TStringR:
    {
        mCustom = _other.mCustom;
        break;
    }
    case Type::TCustom:case Type::TCustomR:
    {
        this->mCustomClass=_other.mCustomClass->clone();
        break;
    }
    default:
        break;
    }
    return *this;
}

LVariant &LVariant::operator=(int _val)
{
    if(mType==Type::TIntR)
    {
       int* ptr = (int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TInt;
    mInt=_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned int _val)
{
    if(mType==Type::TUIntR)
    {
       unsigned int* ptr = (unsigned int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TUInt;
    mUInt=_val;
    return *this;
}

LVariant &LVariant::operator=(float _val)
{
    if(mType==Type::TFloatR)
    {
       float* ptr = (float*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TFloat;
    mFloat=_val;
    return *this;
}

LVariant &LVariant::operator=(double _val)
{
    if(mType==Type::TDoubleR)
    {
       double* ptr = (double*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TDouble;
    mDouble=_val;
    return *this;
}

LVariant &LVariant::operator=(long double _val)
{
    if(mType==Type::TLongDoubleR)
    {
       long double* ptr = (long double*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TLongDouble;
    mLongDouble=_val;
    return *this;
}

LVariant &LVariant::operator=(bool _val)
{
    if(mType==Type::TBoolR)
    {
       bool* ptr = (bool*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TBool;
    mBool=_val;
    return *this;
}

LVariant &LVariant::operator=(short _val)
{
    if(mType==Type::TShortIntR)
    {
       short int* ptr = (short int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TShortInt;
    mShortInt=_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned short _val)
{
    if(mType==Type::TUIntR)
    {
       unsigned int* ptr = (unsigned int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TUShortInt;
    mUShortInt=_val;
    return *this;
}

LVariant &LVariant::operator=(long long _val)
{
    if(mType==Type::TLongLongIntR)
    {
       long long int* ptr = (long long int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TLongLongInt;
    mLongLongInt=_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned long long _val)
{
    if(mType==Type::TIntR)
    {
       unsigned long long int* ptr = (unsigned long long int*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TULongLongInt;
    mLongLongInt=_val;
    return *this;
}

LVariant &LVariant::operator=(char _val)
{
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TChar;
    mChar=_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned char _val)
{
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TUChar;
    mUChar=_val;
    return *this;
}

LVariant &LVariant::operator=(wchar_t _val)
{
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TWChar_t;
    mWChar_t=_val;
    return *this;
}

LVariant &LVariant::operator=(char16_t _val)
{
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TChar16_t;
    mChar16_t=_val;
    return *this;
}

LVariant &LVariant::operator=(char32_t _val)
{
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TChar32_t;
    mChar32_t=_val;
    return *this;
}

LVariant &LVariant::operator=(char *_val)
{
    *this=LString::fromUTF8(_val);
    return *this;
}

LVariant &LVariant::operator=(wchar_t *_val)
{
    *this=LString(_val);
    return *this;
}

LVariant &LVariant::operator=(char32_t *_val)
{
    *this=LString(_val);
    return *this;
}

LVariant &LVariant::operator=(const char *_val)
{
    *this=LString::fromUTF8(_val);
    return *this;
}

LVariant &LVariant::operator=(const wchar_t *_val)
{
    *this=LString(_val);
    return *this;
}

LVariant &LVariant::operator=(const char32_t *_val)
{
    *this=LString(_val);
    return *this;
}

LVariant &LVariant::operator=(LString _val)
{
    if(mType==Type::TStringR)
    {
       LString* ptr = (LString*)mCustom;
       *ptr=_val;
       return *this;
    }
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TString;
    mString =new LString(_val);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LVariant &LVariant::operator=(int *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned int *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TUIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(float *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TFloatR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(double *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TDoubleR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(long double *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TLongDoubleR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(bool *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TBoolR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(short *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TShortIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned short *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TUShortIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(long long *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TLongLongIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(unsigned long long *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TULongLongIntR;
    mCustom=(void*)_val;
    return *this;
}

LVariant &LVariant::operator=(LString *_val)
{
    destroy();
    mTypeName=lGetTypeName<decltype(_val)>();
    mType=Type::TStringR;
    mCustom=(void*)_val;
    return *this;
}

LNAMESPACE_END
