#include "lvariant.h"

LNAMESPACE_BEGIN

LVariant::LVariant()
{
    mType=VariantType::TNull;
}

LVariant::LVariant(const std::initializer_list<int> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned int> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<float> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<double> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long double> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<char> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned char> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<bool> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<short> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned short> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long long> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned long long> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<wchar_t> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const char *> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const wchar_t *> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const char32_t *> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const LString> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const LVariant> &_in)
{
    mType=VariantType::TNull;
    (*this)=_in;
}

LVariant::LVariant(const LVariant &_other)
{
    mType=VariantType::TNull;
    (*this)=_other;
}


LVariant::~LVariant()
{
    destroy();
}

void LVariant::destroy()
{
    switch (mType)
    {
    case VariantType::TString:
    case VariantType::TIntA:
    case VariantType::TUIntA:
    case VariantType::TFloatA:
    case VariantType::TDoubleA:
    case VariantType::TLongDoubleA:
    case VariantType::TCharA:
    case VariantType::TUCharA:
    case VariantType::TBoolA:
    case VariantType::TShortIntA:
    case VariantType::TUShortIntA:
    case VariantType::TLongLongIntA:
    case VariantType::TULongLongIntA:
    case VariantType::TWChar_tA:
    case VariantType::TStringA:
    case VariantType::TVariantA:
        delete mArray;
        break;
    case VariantType::TCustom:
    case VariantType::TCustomReference:
        delete mCustomClass;
        break;
    default:
        break;
    }
    mType=VariantType::TNull;
    mTypeName.clear();
}

void LVariant::fromString(const LString &_in)
{
    if(mType==VariantType::TNull)
        return;
    if(mType==VariantType::TCustom||mType==VariantType::TCustomReference)
    {
        mCustomClass->fromString(_in);
        return;
    }
    destroy();
    mType=VariantType::TString;
    mTypeName=lGetTypeName<LString>();
    mString=new LString;
    *mString=_in;
}

LVariant::VariantType LVariant::getType() const
{
    return mType;
}

LString LVariant::getTypeName() const
{
    return mTypeName;
}

const LVariant LVariant::getProperty(const LString &_propertyname) const
{
    if(mType==VariantType::TNull)
        return LVariant();
    if(mType==VariantType::TCustom||mType==VariantType::TCustomReference)
    {
        return mCustomClass->getProperty(_propertyname);
    }
    LUNUSED(_propertyname);
    lError2(1,LSTR("properties is not availble for this type : ")+mTypeName);
    return LVariant();
}

bool LVariant::isValidArray() const
{
    if(
        mType==VariantType::TIntA||
        mType==VariantType::TUIntA||
        mType==VariantType::TFloatA||
        mType==VariantType::TDoubleA||
        mType==VariantType::TLongDoubleA||
        mType==VariantType::TCharA||
        mType==VariantType::TUCharA||
        mType==VariantType::TBoolA||
        mType==VariantType::TShortIntA||
        mType==VariantType::TUShortIntA||
        mType==VariantType::TLongLongIntA||
        mType==VariantType::TULongLongIntA||
        mType==VariantType::TWChar_tA||
        mType==VariantType::TStringA||
        mType==VariantType::TVariantA
            )
        return true;
    return false;
}

bool LVariant::isValidReference() const
{
    if(
        mType==VariantType::TIntR||
        mType==VariantType::TUIntR||
        mType==VariantType::TFloatR||
        mType==VariantType::TDoubleR||
        mType==VariantType::TLongDoubleR||
        mType==VariantType::TBoolR||
        mType==VariantType::TShortIntR||
        mType==VariantType::TUShortIntR||
        mType==VariantType::TLongLongIntR||
        mType==VariantType::TULongLongIntR||
        mType==VariantType::TStringR||
        mType==VariantType::TCustomReference
            )
        return true;
    return false;
}

void LVariant::setProperty(const LString &_propertyname, const LVariant &_newvalue)
{
    if(mType==VariantType::TNull)
        return;
    if(mType==VariantType::TCustom||mType==VariantType::TCustomReference)
    {
        mCustomClass->setProperty(_propertyname,_newvalue);
        return;
    }
    lError(1,LSTR("properties is not availble for this type : ")+mTypeName);
}

int LVariant::toInt() const
{
    lWarning(mType!=VariantType::TInt&&mType!=VariantType::TIntR,"variant type is not int");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((int*)mCustom);
    return mInt;
}

unsigned int LVariant::toUInt() const
{
    lWarning(mType!=VariantType::TUInt&&mType!=VariantType::TUIntR,"variant type is not unsigned int");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((unsigned int*)mCustom);
    return mUInt;
}

float LVariant::toFloat() const
{
    lWarning(mType!=VariantType::TFloat&&mType!=VariantType::TFloatR,"variant type is not float");
    if(mType==VariantType::TNull)
        return 0.0f;
    if(isValidReference())
        return *((float*)mCustom);
    return mFloat;
}

double LVariant::toDouble() const
{
    lWarning(mType!=VariantType::TDouble&&mType!=VariantType::TDoubleR,"variant type is not double");
    if(mType==VariantType::TNull)
        return 0.0;
    if(isValidReference())
        return *((double*)mCustom);
    return mDouble;
}

long double LVariant::toLongDouble() const
{
    lWarning(mType!=VariantType::TLongDouble&&mType!=VariantType::TLongDoubleR,"variant type is not long double");
    if(mType==VariantType::TNull)
        return 0.0;
    if(isValidReference())
        return *((long double*)mCustom);
    return mLongDouble;
}

char LVariant::toChar() const
{
    lWarning(mType!=VariantType::TChar,"variant type is not char");
    if(mType==VariantType::TNull)
        return '\0';
    if(isValidReference())
        return *((char*)mCustom);
    return mChar;
}

unsigned char LVariant::toUChar() const
{
    lWarning(mType!=VariantType::TUChar,"variant type is not unsigned char");
    if(mType==VariantType::TNull)
        return '\0';
    if(isValidReference())
        return *((unsigned char*)mCustom);
    return mUChar;
}

bool LVariant::toBool() const
{
    lWarning(mType!=VariantType::TBool&&mType!=VariantType::TBoolR,"variant type is not bool");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((bool*)mCustom);
    return mBool;
}

short int LVariant::toShortInt() const
{
    lWarning(mType!=VariantType::TShortInt&&mType!=VariantType::TShortIntR,"variant type is not short int");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((short int*)mCustom);
    return mShortInt;
}

unsigned short LVariant::toUShortInt() const
{
    lWarning(mType!=VariantType::TUShortInt&&mType!=VariantType::TUShortIntR,"variant type is not unsigned short");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((unsigned short int*)mCustom);
    return mUShortInt;
}

long long int LVariant::toLongLongInt() const
{
    lWarning(mType!=VariantType::TLongLongInt&&mType!=VariantType::TLongLongIntR,"variant type is not long long int");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((long long int*)mCustom);
    return mLongLongInt;
}

unsigned long long int LVariant::toULongLongInt() const
{
    lWarning(mType!=VariantType::TULongLongInt&&mType!=VariantType::TULongLongIntR,"variant type is not unsigned long long int");
    if(mType==VariantType::TNull)
        return 0;
    if(isValidReference())
        return *((unsigned long long int*)mCustom);
    return mULongLongInt;
}

wchar_t LVariant::toWCharT() const
{
    lWarning(mType!=VariantType::TWChar_t,"variant type is not wchar_t");
    if(mType==VariantType::TNull)
        return L'\0';
    if(isValidReference())
        return *((wchar_t*)mCustom);
    return mWCharT;
}

LString LVariant::toString() const
{
    if(mType==VariantType::TNull)
        return LString::empty;
    if(mType==VariantType::TCustom||mType==VariantType::TCustomReference)
    {
        return mCustomClass->toString();
    }
    ///TODO update LVariant::toString()
    switch(mType)
    {
    case VariantType::TNull:
        return LSTR("null");
    case VariantType::TString:
        return *mString;
    case VariantType::TStringR:
        return *((LString*)mCustom);
    case VariantType::TChar:case VariantType::TUChar:
        return LString(toChar());
    case VariantType::TWChar_t:
        return LString(toWCharT());
    case VariantType::TBool:
        if(this->mBool)
            return LSTR("true");
        else
            return LSTR("false");
    case VariantType::TBoolR:
        if( *((bool*)mCustom) )
            return LSTR("true");
        else
            return LSTR("false");
    case VariantType::TDouble:case VariantType::TDoubleR:
        return LString::fromDouble(toDouble());
    case VariantType::TFloat:case VariantType::TFloatR:
        return LString::fromFloat(toFloat());
    case VariantType::TLongDouble:case VariantType::TLongDoubleR:
        return LString::fromLongDouble(toLongDouble());

    case VariantType::TInt:case VariantType::TIntR:
        return LString::fromInt(toInt());
    case VariantType::TLongLongInt:case VariantType::TLongLongIntR:
        return LString::fromLongLongInt(toLongLongInt());
    case VariantType::TShortInt:case VariantType::TShortIntR:
        return LString::fromShortInt(toShortInt());

    case VariantType::TUInt:case VariantType::TUIntR:
        return LString::fromUInt(toUInt());
    case VariantType::TULongLongInt:case VariantType::TULongLongIntR:
        return LString::fromULongLongInt(toULongLongInt());
    case VariantType::TUShortInt:case VariantType::TUShortIntR:
        return LString::fromUShortInt(toUShortInt());
    default:
        break;
    }

    lWarning(1,"variant type can not convert to string ");
    return LString::empty;
}

LVariant &LVariant::operator=(const LVariant &_in)
{
    this->destroy();
    mTypeName=_in.mTypeName;
    mType=_in.mType;
    switch(_in.mType)
    {
    case VariantType::TNull:
        break;
    case VariantType::TInt:
        mInt=_in.mInt;
        break;
    case VariantType::TUInt:
        mUInt=_in.mUInt;
        break;
    case VariantType::TFloat:
        mFloat=_in.mFloat;
        break;
    case VariantType::TDouble:
        mDouble=_in.mDouble;
        break;
    case VariantType::TLongDouble:
        mLongDouble=_in.mLongDouble;
        break;
    case VariantType::TChar:
        mChar=_in.mChar;
        break;
    case VariantType::TUChar:
        mUChar=_in.mUChar;
        break;
    case VariantType::TBool:
        mBool=_in.mBool;
        break;
    case VariantType::TShortInt:
        mShortInt=_in.mShortInt;
        break;
    case VariantType::TUShortInt:
        mUShortInt=_in.mUShortInt;
        break;
    case VariantType::TLongLongInt:
        mLongLongInt=_in.mLongLongInt;
        break;
    case VariantType::TULongLongInt:
        mULongLongInt=_in.mULongLongInt;
        break;
    case VariantType::TWChar_t:
        mWCharT=_in.mWCharT;
        break;
    case VariantType::TString:
        mString=_in.mString;
        break;


    case VariantType::TIntR:
    case VariantType::TUIntR:
    case VariantType::TFloatR:
    case VariantType::TDoubleR:
    case VariantType::TLongDoubleR:
    case VariantType::TBoolR:
    case VariantType::TShortIntR:
    case VariantType::TUShortIntR:
    case VariantType::TLongLongIntR:
    case VariantType::TULongLongIntR:
    case VariantType::TStringR:
        mCustom=_in.mCustom;
        break;

    case VariantType::TIntA:
    case VariantType::TUIntA:
    case VariantType::TFloatA:
    case VariantType::TDoubleA:
    case VariantType::TLongDoubleA:
    case VariantType::TCharA:
    case VariantType::TUCharA:
    case VariantType::TBoolA:
    case VariantType::TShortIntA:
    case VariantType::TUShortIntA:
    case VariantType::TLongLongIntA:
    case VariantType::TULongLongIntA:
    case VariantType::TWChar_tA:
    case VariantType::TStringA:
    case VariantType::TVariantA:
        mArray=_in.mArray;
        break;
    case VariantType::TCustom:
        mCustomClass=_in.mCustomClass->clone();
        break;
    case VariantType::TCustomReference:
        mCustomClass=_in.mCustomClass->clone();
        break;
    default:
        break;
    }
    return *this;
}

LVariant &LVariant::operator=(const int& _in)
{
    if(mType==VariantType::TIntR)
    {
        int* ptr=(int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TInt;
    mInt=_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned int& _in)
{
    if(mType==VariantType::TUIntR)
    {
        unsigned int* ptr=(unsigned int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUInt;
    mUInt=_in;
    return *this;
}

LVariant &LVariant::operator=(const float& _in)
{
    if(mType==VariantType::TFloatR)
    {
        float* ptr=(float*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloat;
    mFloat=_in;
    return *this;
}

LVariant &LVariant::operator=(const double& _in)
{
    if(mType==VariantType::TDoubleR)
    {
        double* ptr=(double*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDouble;
    mDouble=_in;
    return *this;
}

LVariant &LVariant::operator=(const long double& _in)
{
    if(mType==VariantType::TLongDoubleR)
    {
        long double* ptr=(long double*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDouble;
    mLongDouble=_in;
    return *this;
}

LVariant &LVariant::operator=(const char& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TChar;
    mChar=_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned char& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUChar;
    mUChar=_in;
    return *this;
}

LVariant &LVariant::operator=(const bool& _in)
{
    if(mType==VariantType::TBoolR)
    {
        bool* ptr=(bool*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBool;
    mBool=_in;
    return *this;
}

LVariant &LVariant::operator=(const short& _in)
{
    if(mType==VariantType::TShortIntR)
    {
        short int* ptr=(short int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortInt;
    mShortInt =_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned short& _in)
{
    if(mType==VariantType::TUShortIntR)
    {
        unsigned short int* ptr=(unsigned short int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortInt;
    mUShortInt=_in;
    return *this;
}

LVariant &LVariant::operator=(const long long& _in)
{
    if(mType==VariantType::TLongLongIntR)
    {
        long long int* ptr=(long long int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongInt;
    mLongLongInt=_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned long long& _in)
{
    if(mType==VariantType::TULongLongIntR)
    {
        unsigned long long int* ptr=(unsigned long long int*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongInt;
    mULongLongInt=_in;
    return *this;
}

LVariant &LVariant::operator=(const wchar_t& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TWChar_t;
    mWCharT=_in;
    return *this;
}

LVariant &LVariant::operator=(const LString& _in)
{
    if(mType==VariantType::TStringR)
    {
        LString* ptr=(LString*)mCustom;
        *ptr=_in;
        return *this;
    }
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TString;
    mString=new LString;
    *mString=_in;
    return *this;
}

LVariant &LVariant::operator=(const char *_in)
{
    (*this)=LString(_in);
    return *this;
}

LVariant &LVariant::operator=(const wchar_t *_in)
{
    (*this)=LString(_in);
    return *this;
}

LVariant &LVariant::operator=(const char32_t *_in)
{
    (*this)=LString(_in);
    return *this;
}



LVariant &LVariant::operator=(int* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TIntR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned int* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUIntR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(float* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloatR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(double* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDoubleR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(long double* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDoubleR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(bool* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBoolR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(short* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortIntR;
    mCustom =_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned short* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortIntR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(long long* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongIntR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned long long* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongIntR;
    mCustom=_in;
    return *this;
}

LVariant &LVariant::operator=(LString* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringR;
    mCustom=_in;
    return *this;
}


LVariant &LVariant::operator=(const int* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TIntR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned int* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUIntR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const float* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloatR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const double* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDoubleR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const long double* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDoubleR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const bool* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBoolR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const short* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortIntR;
    mCustom =(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned short* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortIntR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const long long* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongIntR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const unsigned long long* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongIntR;
    mCustom=(void*)_in;
    return *this;
}

LVariant &LVariant::operator=(const LString* _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringR;
    mCustom=(void*)_in;
    return *this;
}



LVariant &LVariant::operator=(const std::initializer_list<int>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TIntA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TInt;
        (*mArray)[i].mTypeName=lGetTypeName<int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned int>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUIntA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TUInt;
        (*mArray)[i].mTypeName=lGetTypeName<unsigned int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<float>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloatA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TFloat;
        (*mArray)[i].mTypeName=lGetTypeName<float>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<double>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDoubleA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TDouble;
        (*mArray)[i].mTypeName=lGetTypeName<double>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<long double>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDoubleA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TLongDouble;
        (*mArray)[i].mTypeName=lGetTypeName<long double>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<char>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TCharA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TChar;
        (*mArray)[i].mTypeName=lGetTypeName<char>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned char>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUCharA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TUChar;
        (*mArray)[i].mTypeName=lGetTypeName<unsigned char>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<bool>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBoolA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TBool;
        (*mArray)[i].mTypeName=lGetTypeName<bool>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<short>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortIntA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TShortInt;
        (*mArray)[i].mTypeName=lGetTypeName<short int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned short>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortIntA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TUShortInt;
        (*mArray)[i].mTypeName=lGetTypeName<unsigned short int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<long long>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongInt;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TLongLongInt;
        (*mArray)[i].mTypeName=lGetTypeName<long long int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned long long>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongIntA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TULongLongInt;
        (*mArray)[i].mTypeName=lGetTypeName<unsigned long long int>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<wchar_t>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TWChar_tA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
    {
        (*mArray)[i]=_in.begin()[i];
        (*mArray)[i].mType=VariantType::TWChar_t;
        (*mArray)[i].mTypeName=lGetTypeName<wchar_t>();
    }
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const char*>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mArray)[i]=LString(_in.begin()[i]);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const LVariant> &_in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TVariantA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mArray)[i]=(_in.begin()[i]);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const LString> &_in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mArray)[i]=LString(_in.begin()[i]);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const char32_t *> &_in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mArray)[i]=LString(_in.begin()[i]);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const wchar_t *> &_in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringA;
    mArray=new LVector<LVariant>();
    mArray->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mArray)[i]=LString(_in.begin()[i]);
    return *this;
}

LVariant& LVariant::operator[](u32 i) const
{
    static LVariant d;
    if(mType==VariantType::TNull)
        return d;
    lError(!isValidArray(),"Varaiant type is not valid array",d);
    return (*mArray)[i];
}




LNAMESPACE_END
