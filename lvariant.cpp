#include "lvariant.h"

LNAMESPACE_BEGIN

LVariant::LVariant()
{
    mType=VariantType::TNull;
}

LVariant::LVariant(int _in)
{
    (*this)=_in;
}

LVariant::LVariant(unsigned int _in)
{
    (*this)=_in;
}

LVariant::LVariant(float _in)
{
    (*this)=_in;
}

LVariant::LVariant(double _in)
{
    (*this)=_in;
}

LVariant::LVariant(long double _in)
{
    (*this)=_in;
}

LVariant::LVariant(char _in)
{
    (*this)=_in;
}

LVariant::LVariant(unsigned char _in)
{
    (*this)=_in;
}

LVariant::LVariant(bool _in)
{
    (*this)=_in;
}

LVariant::LVariant(short _in)
{
    (*this)=_in;
}

LVariant::LVariant(unsigned short _in)
{
    (*this)=_in;
}

LVariant::LVariant(long long _in)
{
    (*this)=_in;
}

LVariant::LVariant(unsigned long long _in)
{
    (*this)=_in;
}

LVariant::LVariant(wchar_t _in)
{
    (*this)=_in;
}

LVariant::LVariant(LString _in)
{
    (*this)=_in;
}

LVariant::LVariant(const char *_in)
{
    (*this)=_in;
}

LVariant::LVariant(const wchar_t *_in)
{
    (*this)=_in;
}

LVariant::LVariant(const char32_t *_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<int> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned int> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<float> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<double> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long double> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<char> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned char> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<bool> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<short> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned short> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long long> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned long long> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<wchar_t> &_in)
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const char *> &_in)
{
    (*this)=_in;
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
        delete mString;
        break;
    case VariantType::TIntA:
        delete mIntA;
        break;
    case VariantType::TUIntA:
        delete mUIntA;
        break;
    case VariantType::TFloatA:
        delete mFloatA;
        break;
    case VariantType::TDoubleA:
        delete mDoubleA;
        break;
    case VariantType::TLongDoubleA:
        delete mLongDoubleA;
        break;
    case VariantType::TCharA:
        delete mCharA;
        break;
    case VariantType::TUCharA:
        delete mUCharA;
        break;
    case VariantType::TBoolA:
        delete mBoolA;
        break;
    case VariantType::TShortIntA:
        delete mShortIntA;
        break;
    case VariantType::TUShortIntA:
        delete mUShortIntA;
        break;
    case VariantType::TLongLongIntA:
        delete mLongLongIntA;
        break;
    case VariantType::TULongLongIntA:
        delete mULongLongIntA;
        break;
    case VariantType::TWChar_tA:
        delete mWCharTA;
        break;
    case VariantType::TStringA:
        delete mStringA;
        break;
    default:
        break;
    }
    mType=VariantType::TNull;
    mTypeName.clear();
}

void LVariant::fromString(const LString &_in)
{
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
        mType==VariantType::TStringA
            )
        return true;
    return false;
}

int LVariant::toInt() const
{
    lWarning(mType!=VariantType::TInt,"variant type is not int");
    return mInt;
}

unsigned int LVariant::toUInt() const
{
    lWarning(mType!=VariantType::TUInt,"variant type is not unsigned int");
    return mUInt;
}

float LVariant::toFloat() const
{
    lWarning(mType!=VariantType::TFloat,"variant type is not float");
    return mFloat;
}

double LVariant::toDouble() const
{
    lWarning(mType!=VariantType::TDouble,"variant type is not double");
    return mDouble;
}

long double LVariant::toLongDouble() const
{
    lWarning(mType!=VariantType::TLongDouble,"variant type is not long double");
    return mLongDouble;
}

char LVariant::toChar() const
{
    lWarning(mType!=VariantType::TChar,"variant type is not char");
    return mChar;
}

unsigned char LVariant::toUChar() const
{
    lWarning(mType!=VariantType::TUChar,"variant type is not unsigned char");
    return mUChar;
}

bool LVariant::toBool() const
{
    lWarning(mType!=VariantType::TBool,"variant type is not bool");
    return mBool;
}

short int LVariant::toShortInt() const
{
    lWarning(mType!=VariantType::TShortInt,"variant type is not short int");
    return mShortInt;
}

unsigned short LVariant::toUShortInt() const
{
    lWarning(mType!=VariantType::TUShortInt,"variant type is not unsigned short");
    return mUShortInt;
}

long long int LVariant::toLongLongInt() const
{
    lWarning(mType!=VariantType::TLongLongInt,"variant type is not long long int");
    return mLongLongInt;
}

unsigned long long int LVariant::toULongLongInt() const
{
    lWarning(mType!=VariantType::TULongLongInt,"variant type is not unsigned long long int");
    return mULongLongInt;
}

wchar_t LVariant::toWCharT() const
{
    lWarning(mType!=VariantType::TWChar_t,"variant type is not wchar_t");
    return mWCharT;
}

LString LVariant::toString() const
{
    ///TODO update LVariant::toString()
    switch(mType)
    {
    case VariantType::TString:
        return *mString;
        break;
    case VariantType::TInt:
        return LString::fromInt(mInt);
        break;
    case VariantType::TChar:case VariantType::TUChar:
        return LString(mChar);
        break;
    case VariantType::TWChar_t:
        return LString(mWCharT);
        break;
    default:
        break;
    }

    lWarning(1,"variant type is not String ");
    return LString::empty;
}

LVariant &LVariant::operator=(int _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TInt;
    mInt=_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned int _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUInt;
    mUInt=_in;
    return *this;
}

LVariant &LVariant::operator=(float _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloat;
    mFloat=_in;
    return *this;
}

LVariant &LVariant::operator=(double _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDouble;
    mDouble=_in;
    return *this;
}

LVariant &LVariant::operator=(long double _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDouble;
    mLongDouble=_in;
    return *this;
}

LVariant &LVariant::operator=(char _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TChar;
    mChar=_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned char _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUChar;
    mUChar=_in;
    return *this;
}

LVariant &LVariant::operator=(bool _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBool;
    mBool=_in;
    return *this;
}

LVariant &LVariant::operator=(short _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortInt;
    mShortInt =_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned short _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortInt;
    mUShortInt=_in;
    return *this;
}

LVariant &LVariant::operator=(long long _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongInt;
    mLongLongInt=_in;
    return *this;
}

LVariant &LVariant::operator=(unsigned long long _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongInt;
    mULongLongInt=_in;
    return *this;
}

LVariant &LVariant::operator=(wchar_t _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TWChar_t;
    mWCharT=_in;
    return *this;
}

LVariant &LVariant::operator=(LString _in)
{
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





LVariant &LVariant::operator=(const std::initializer_list<int>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TIntA;
    mIntA=new LVector<int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned int>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUIntA;
    mUIntA=new LVector<unsigned int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<float>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TFloatA;
    mFloatA=new LVector<float>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<double>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TDoubleA;
    mDoubleA=new LVector<double>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<long double>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongDoubleA;
    mLongDoubleA=new LVector<long double>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<char>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TCharA;
    mCharA=new LVector<char>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned char>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUCharA;
    mUCharA=new LVector<unsigned char>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<bool>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TBoolA;
    mBoolA=new LVector<bool>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<short>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TShortIntA;
    mShortIntA =new LVector<short int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned short>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TUShortIntA;
    mUShortIntA=new LVector<unsigned short int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<long long>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TLongLongInt;
    mLongLongIntA=new LVector<long long int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<unsigned long long>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TULongLongIntA;
    mULongLongIntA=new LVector<unsigned long long int>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<wchar_t>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TWChar_tA;
    mWCharTA=new LVector<wchar_t>(_in);
    return *this;
}

LVariant &LVariant::operator=(const std::initializer_list<const char*>& _in)
{
    this->destroy();
    mTypeName=lGetTypeName(_in);
    mType=VariantType::TStringA;
    mStringA=new LVector<LString>();
    mStringA->resize(_in.size());
    for(u32 i=0;i<_in.size();i++)
        (*mStringA)[i]=_in.begin()[i];
    return *this;
}

LVariant LVariant::operator[](u32 i) const
{
    lError(!isValidArray(),"Varaiant type is not valid array",LVariant());
    if(mType==VariantType::TIntA)
        return LVariant((*mIntA)[i]);
    if(mType==VariantType::TUIntA)
        return LVariant((*mUIntA)[i]);
    if(mType==VariantType::TFloatA)
        return LVariant((*mFloatA)[i]);
    if(mType==VariantType::TDoubleA)
        return LVariant((*mDoubleA)[i]);
    if(mType==VariantType::TLongDoubleA)
        return LVariant((*mLongDoubleA)[i]);
    if(mType==VariantType::TUCharA)
        return LVariant((*mCharA)[i]);
    if(mType==VariantType::TBoolA)
        return LVariant((*mBoolA)[i]);
    if(mType==VariantType::TShortIntA)
        return LVariant((*mShortIntA)[i]);
    if(mType==VariantType::TUShortIntA)
        return LVariant((*mUShortIntA)[i]);
    if(mType==VariantType::TLongLongIntA)
        return LVariant((*mLongLongIntA)[i]);
    if(mType==VariantType::TULongLongIntA)
        return LVariant((*mULongLongIntA)[i]);
    if(mType==VariantType::TWChar_tA)
        return LVariant((*mWCharTA)[i]);
    if(mType==VariantType::TStringA)
        return LVariant((*mStringA)[i]);
    return LVariant();
}



LNAMESPACE_END
