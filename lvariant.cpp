#include "lvariant.h"

LNAMESPACE_BEGIN

LVariant::LVariant()
{
    mType=VariantType::TNull;
}

LVariant::LVariant(int _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned int _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(float _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(double _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(long double _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(char _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned char _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(bool _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(short _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned short _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(long long _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned long long _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(wchar_t _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(LString _in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const char *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const wchar_t *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const char32_t *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(int *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned int *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(float *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(double *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(long double *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(bool *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(short *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned short *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(long long *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(unsigned long long *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(LString *_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<int> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned int> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<float> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<double> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long double> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<char> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned char> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<bool> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<short> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned short> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<long long> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<unsigned long long> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<wchar_t> &_in):
    LVariant()
{
    (*this)=_in;
}

LVariant::LVariant(const std::initializer_list<const char *> &_in):
    LVariant()
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
        delete mArray;
        break;
    case VariantType::TCustom:
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

const LVariant *LVariant::getProperty(const LString &_propertyname) const
{
    LUNUSED(_propertyname);
    lError(1,LSTR("properties is not availble for this type : ")+mTypeName,nullptr);
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
        mType==VariantType::TStringR
            )
        return true;
    return false;
}

void LVariant::setProperty(const LString &_propertyname, const LVariant &_newvalue)
{
    LUNUSED(_propertyname);
    LUNUSED(_newvalue);
    lError(1,LSTR("properties is not availble for this type : ")+mTypeName);
}

int LVariant::toInt() const
{
    lWarning(mType!=VariantType::TInt&&mType!=VariantType::TIntR,"variant type is not int");
    if(isValidReference())
        return *((int*)mCustom);
    return mInt;
}

unsigned int LVariant::toUInt() const
{
    lWarning(mType!=VariantType::TUInt&&mType!=VariantType::TUIntR,"variant type is not unsigned int");
    if(isValidReference())
        return *((unsigned int*)mCustom);
    return mUInt;
}

float LVariant::toFloat() const
{
    lWarning(mType!=VariantType::TFloat&&mType!=VariantType::TFloatR,"variant type is not float");
    if(isValidReference())
        return *((float*)mCustom);
    return mFloat;
}

double LVariant::toDouble() const
{
    lWarning(mType!=VariantType::TDouble&&mType!=VariantType::TDoubleR,"variant type is not double");
    if(isValidReference())
        return *((double*)mCustom);
    return mDouble;
}

long double LVariant::toLongDouble() const
{
    lWarning(mType!=VariantType::TLongDouble&&mType!=VariantType::TLongDoubleR,"variant type is not long double");
    if(isValidReference())
        return *((long double*)mCustom);
    return mLongDouble;
}

char LVariant::toChar() const
{
    lWarning(mType!=VariantType::TChar,"variant type is not char");
    if(isValidReference())
        return *((char*)mCustom);
    return mChar;
}

unsigned char LVariant::toUChar() const
{
    lWarning(mType!=VariantType::TUChar,"variant type is not unsigned char");
    if(isValidReference())
        return *((unsigned char*)mCustom);
    return mUChar;
}

bool LVariant::toBool() const
{
    lWarning(mType!=VariantType::TBool&&mType!=VariantType::TBoolR,"variant type is not bool");
    if(isValidReference())
        return *((bool*)mCustom);
    return mBool;
}

short int LVariant::toShortInt() const
{
    lWarning(mType!=VariantType::TShortInt&&mType!=VariantType::TShortIntR,"variant type is not short int");
    if(isValidReference())
        return *((short int*)mCustom);
    return mShortInt;
}

unsigned short LVariant::toUShortInt() const
{
    lWarning(mType!=VariantType::TUShortInt&&mType!=VariantType::TUShortIntR,"variant type is not unsigned short");
    if(isValidReference())
        return *((unsigned short int*)mCustom);
    return mUShortInt;
}

long long int LVariant::toLongLongInt() const
{
    lWarning(mType!=VariantType::TLongLongInt&&mType!=VariantType::TLongLongIntR,"variant type is not long long int");
    if(isValidReference())
        return *((long long int*)mCustom);
    return mLongLongInt;
}

unsigned long long int LVariant::toULongLongInt() const
{
    lWarning(mType!=VariantType::TULongLongInt&&mType!=VariantType::TULongLongIntR,"variant type is not unsigned long long int");
    if(isValidReference())
        return *((unsigned long long int*)mCustom);
    return mULongLongInt;
}

wchar_t LVariant::toWCharT() const
{
    lWarning(mType!=VariantType::TWChar_t,"variant type is not wchar_t");
    if(isValidReference())
        return *((wchar_t*)mCustom);
    return mWCharT;
}

LString LVariant::toString() const
{
    ///TODO update LVariant::toString()
    if(isValidReference())
        return *((LString*)mCustom);
    switch(mType)
    {
    case VariantType::TString:
        return *mString;
        break;
    case VariantType::TInt:
        return LString::fromInt(toInt());
        break;
    case VariantType::TChar:case VariantType::TUChar:
        return LString(toChar());
        break;
    case VariantType::TWChar_t:
        return LString(toWCharT());
        break;
    default:
        break;
    }

    lWarning(1,"variant type is not String ");
    return LString::empty;
}

LVariant &LVariant::operator=(int _in)
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

LVariant &LVariant::operator=(unsigned int _in)
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

LVariant &LVariant::operator=(float _in)
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

LVariant &LVariant::operator=(double _in)
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

LVariant &LVariant::operator=(long double _in)
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

LVariant &LVariant::operator=(short _in)
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

LVariant &LVariant::operator=(unsigned short _in)
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

LVariant &LVariant::operator=(long long _in)
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

LVariant &LVariant::operator=(unsigned long long _in)
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

LVariant& LVariant::operator[](u32 i) const
{
    static LVariant d;
    lError(!isValidArray(),"Varaiant type is not valid array",d);
    return (*mArray)[i];
}



LNAMESPACE_END
