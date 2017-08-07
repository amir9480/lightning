#include "lstring.h"
#include "lmathutility.h"
#include "llog.h"
#include <cstdlib>
#include <cstdio>

LNAMESPACE_BEGIN

// type define
template class LString_Base<wchar_t>;
template class LString_Base<char>;
template class LString_Base<char32_t>;

template <typename chartype>
const LString_Base<chartype> LString_Base<chartype>::empty;

template <typename chartype>
const u32 LString_Base<chartype>::nothing=(u32)-1;

template <typename chartype>
LString_Base<chartype>::LString_Base()
{
    mData=0;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const chartype& _c)
{
    mData=new chartype[2];
    mData[0]=_c;
    mData[1]=(chartype)0;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const char *_firstvalue)
{
    mData=0;
    (*this)=_firstvalue;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const wchar_t *_firstvalue)
{
    mData=0;
    (*this)=_firstvalue;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const char32_t *_firstvalue)
{
    mData=0;
    (*this)=_firstvalue;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const LString_Base<char> &_other)
{
    mData=0;
    (*this)=_other;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const LString_Base<wchar_t> &_other)
{
    mData=0;
    (*this)=_other;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const LString_Base<char32_t> &_other)
{
    mData=0;
    (*this)=_other;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(LString_Base<chartype>&& _other)
{
    mData=0;
    (*this)=lMove(_other);
}

template <typename chartype>
LString_Base<chartype>::~LString_Base()
{
    if(mData)
        delete[] mData;
}

template <typename chartype>
void LString_Base<chartype>::append(const chartype *_other)
{
   (*this)+=_other;
}

template <typename chartype>
void LString_Base<chartype>::append(LString_Base<chartype> _other)
{
    (*this)+=_other;
}

template <typename chartype>
chartype &LString_Base<chartype>::at(u32 i)
{
    return mData[i];
}

template <typename chartype>
chartype LString_Base<chartype>::at(u32 i) const
{
    return mData[i];
}

template <typename chartype>
typename LString_Base<chartype>::iterator LString_Base<chartype>::begin()
{
    return mData;
}

template <typename chartype>
typename LString_Base<chartype>::const_iterator LString_Base<chartype>::begin() const
{
    return mData;
}

template <typename chartype>
void LString_Base<chartype>::clear()
{
    if(mData)
        delete[] mData;
    mData=0;
}

template <typename chartype>
typename LString_Base<chartype>::iterator LString_Base<chartype>::end()
{
    return &mData[getCapacity()];
}

template <typename chartype>
typename LString_Base<chartype>::const_iterator LString_Base<chartype>::end() const
{
    return &mData[getCapacity()];
}

template <typename chartype>
void LString_Base<chartype>::erase(u32 _start, u32 _n)
{
    u32 pc=getCapacity();
    lError(mData==0,"void LString_Base<chartype>::erase(u32 _start, u32 _n): string is completely empty. there is not any thing to erase");
    lError(_start>=pc,"void LString_Base<chartype>::erase(u32 _start, u32 _n): _start value is not acceptable");
    lError(_n>=pc&&_n!=(u32)-1,"void LString_Base<chartype>::erase(u32 _start, u32 _n): _n value is not acceptable");

    if(_n==(u32)-1)
    {
        LString_Base<chartype> t=*this;
        t[_start]=0;
        *this=t;
        return;
    }
    lMemoryMove(&mData[_start],&mData[_start+_n],(pc-(_start+_n)+1)*sizeof(*mData));
    resize(getCapacity());// flush
}

template <typename chartype>
u32 LString_Base<chartype>::find(const chartype *_what, u32 _from)const
{
    u32 strc=getCapacity();
    lError(_from>=strc,"u32 LString_Base<chartype>::find(const chartype *_what, u32 _from)const: _from value is not acceptable",nothing);
    if(_what==0||mData==0)
        return nothing;
    u32 whatc=__utility_strlen(_what);
    for(u32 i=_from;i<strc-whatc+1;i++)
        if(mData[i]==_what[0])
            for(u32 j=0;j<whatc;j++)
            {
                if(mData[j+i]!=_what[j])
                    break;
                if(j==whatc-1)
                    return i;
            }
    return nothing;
}

template <typename chartype>
u32 LString_Base<chartype>::find(const LString_Base<chartype> _what, u32 _from) const
{
    return find(_what.mData,_from);
}

template <typename chartype>
u32 LString_Base<chartype>::findFromRight(const chartype *_what, u32 _from) const
{
    u32 strc=getCapacity();
    lError(_from>=strc,"u32 LString_Base<chartype>::findFromRight(const chartype *_what, u32 _from)const: _from value is not acceptable",nothing);
    if(_what==0||mData==0)
        return nothing;
    u32 whatc=__utility_strlen(_what);
    for(u32 i=strc-whatc-_from-1;i>=0;i--)
        if(mData[i]==_what[0])
            for(u32 j=0;j<whatc;j++)
            {
                if(mData[j+i]!=_what[j])
                    break;
                if(j==whatc-1)
                    return i;
            }
    return nothing;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromShortInt(const short int &_in, const u32 _base)
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16," _base value is not accpetable . must be [2-16]",empty);
    LString_Base<chartype> o;
    o.resize(33);// maximum space requied (for _base = 2)
    short int v=(_in>0)?_in:-_in;

    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    if(_in<0)
        o.insert(0,"-");
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromUShortInt(const unsigned short int &_in, const u32 _base)
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16," _base value is not accpetable . must be [2-16]",empty);
    LString_Base<chartype> o;
    o.resize(33);// maximum space requied (for _base = 2)
    unsigned short int v=_in;
    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromInt(const int &_in, const u32 _base)
{
    LString_Base<chartype> o;
    lMemoryLogStartIgnore();// because this string will destroyed at end of program and gives a leak detect message
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    lMemoryLogEndIgnore();
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16," _base value is not accpetable . must be [2-16]",empty);

    o.resize(33);// maximum space requied (for _base = 2)
    int v=(_in>0)?_in:-_in;

    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    if(_in<0)
        o.insert(0,"-");
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromUInt(const unsigned int &_in, const u32 _base)
{
    lMemoryLogStartIgnore();
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    lMemoryLogEndIgnore();
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16," _base value is not accpetable . must be [2-16]",empty);
    LString_Base<chartype> o;
    o.resize(33);// maximum space requied (for _base = 2)
    unsigned int v=_in;
    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromLongLongInt(const long long int &_in, const u32 _base)
{
    lMemoryLogStartIgnore();
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    lMemoryLogEndIgnore();
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16," _base value is not accpetable . must be [2-16]",empty);
    LString_Base<chartype> o;
    o.resize(33);// maximum space requied (for _base = 2)
    long long int v=(_in>0)?_in:-_in;

    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    if(_in<0)
        o.insert(0,"-");
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromULongLongInt(const unsigned long long int &_in, const u32 _base)
{
    lMemoryLogStartIgnore();
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    lMemoryLogEndIgnore();
    if(_in==0)
        return LString_Base<chartype>("0");
    lError(_base<=1||_base>16,"_base value is not accpetable . must be [2-16]",empty);
    LString_Base<chartype> o;
    o.resize(33);// maximum space requied (for _base = 2)
    unsigned long long int v=_in;
    for(u32 i=0;v>0;i++)
    {
        o[i]=vt[v%_base];
        o[i+1]=(chartype)0;
        v/=_base;
    }
    o.reverse();
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromFloat(const float &_in)
{
    LString_Base<chartype> o;
    static char _data[255];
    snprintf(_data,254,"%f",_in);
    o=_data;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromDouble(const double &_in)
{
    LString_Base<chartype> o;
    static char _data[255];
    snprintf(_data,254,"%lf",_in);
    o=_data;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromLongDouble(const long double &_in)
{
    LString_Base<chartype> o;
    static char _data[255];
    snprintf(_data,254,"%lf",(double)_in);
    o=_data;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::fromUTF8(const LString8 &_in)
{
    return LString_Base<chartype>::fromUTF8(_in.getData());
}

template <>
LString_Base<char> LString_Base<char>::fromUTF8(const char* _in)
{
    return LString_Base<char>(_in);
}

template <>
LString_Base<wchar_t> LString_Base<wchar_t>::fromUTF8(const char* _in)
{
    LString_Base<wchar_t> o,out;
    u32 ins=__utility_strlen(_in);
    o.resize(ins);// maximum capacity that is needed
    u32 l=0;
    for(u32 i=0;i<ins;i++)
    {
        u32 t = __utility_utf8decode(&_in[l]);
        wchar_t* ue=__utility_utf16encode(t);
        u32 ues=(__utility_strlen(ue)+1)*sizeof(wchar_t);
        lMemoryCopy(&o.mData[i],ue,ues);

        if(t<=0x7f)
            l+=1;
        else if(t<=0x7ff)
            l+=2;
        else if(t<=0xffff)
            l+=3;
        else if(t<=0x1fffff)
            l+=4;
        else if(t<=0x3ffffff)
            l+=5;
        else if(t<=0x7fffffff)
            l+=6;
        if(t>=0x10000)
            i++;
    }
    out=o;
    return o;
}

template <>
LString_Base<char32_t> LString_Base<char32_t>::fromUTF8(const char* _in)
{
    LString_Base<char32_t> o,out;
    u32 ins=__utility_strlen(_in);
    o.resize(ins);// maximum capacity that is needed
    u32 l=0;
    for(u32 i=0;i<ins;i++)
    {
        u32 t = __utility_utf8decode(&_in[l]);
        o[i]=t;
        o[i+1]=0;

        if(t<=0x7f)
            l+=1;
        else if(t<=0x7ff)
            l+=2;
        else if(t<=0xffff)
            l+=3;
        else if(t<=0x1fffff)
            l+=4;
        else if(t<=0x3ffffff)
            l+=5;
        else if(t<=0x7fffffff)
            l+=6;
    }
    out=o;
    return o;
}

template <>
LString_Base<wchar_t> LString_Base<wchar_t>::fromUTF16(const wchar_t* _in)
{
    return LString(_in);
}

template <>
LString_Base<char32_t> LString_Base<char32_t>::fromUTF16(const wchar_t* _in)
{
    LString_Base<char32_t> o,out;
    u32 ins=__utility_strlen(_in);
    o.resize(ins);// maximum capacity that is needed
    u32 l=0;
    for(u32 i=0;i<ins;i++)
    {
        u32 t = __utility_utf16decode(&_in[l]);
        o[i]=t;
        o[i+1]=0;

        if(t>=0x10000)
            l+=2;
        else
            l++;
    }
    out=o;
    return o;
}

template <>
LString_Base<char32_t> LString_Base<char32_t>::fromUTF16(const LString& _in)
{
    return LString_Base<char32_t>::fromUTF16(_in.getData());
}

template <>
LString_Base<wchar_t> LString_Base<wchar_t>::fromUTF16(const LString& _in)
{
    return _in;
}

template <typename chartype>
u32 LString_Base<chartype>::getCapacity() const
{
    return __utility_strlen(mData);
}

template <typename chartype>
const chartype *LString_Base<chartype>::getData() const
{
    if(mData==0)
    {
        static chartype o[1];
        o[0]=(chartype)0;
        return o;
    }
    return mData;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::getReversed() const
{
    LString_Base<chartype> o=*this;
    o.reverse();
    return o;
}

template <>
u32 LString_Base<char>::getSize()const
{
    u32 out=0;
    u32 ins = getCapacity();
    for(u32 i=0;i<ins;)
    {
        u32 t = __utility_utf8decode(&mData[i]);

        if(t<=0x7f)
            i+=1;
        else if(t<=0x7ff)
            i+=2;
        else if(t<=0xffff)
            i+=3;
        else if(t<=0x1fffff)
            i+=4;
        else if(t<=0x3ffffff)
            i+=5;
        else if(t<=0x7fffffff)
            i+=6;
        out++;
    }
    return out;
}

template <>
u32 LString_Base<wchar_t>::getSize()const
{
    u32 out=0;
    u32 ins = getCapacity();
    for(u32 i=0;i<ins;)
    {
        u32 t = __utility_utf16decode(&mData[i]);
        if(t<0x10000)
            i+=1;
        else
            i+=2;
        out++;
    }
    return out;
}

template <>
u32 LString_Base<char32_t>::getSize()const
{
    return getCapacity();
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::getSubString(u32 _start, u32 _n) const
{
    u32 sc=getCapacity();
    lError(_start>=sc,"LString_Base<chartype> LString_Base<chartype>::getSubString(u32 _start, u32 _n) const: _start value is not acceptable",empty);
    lError(_n+_start>=sc&&_n!=(u32)-1,"LString_Base<chartype> LString_Base<chartype>::getSubString(u32 _start, u32 _n) const: _n value is not acceptable",empty);
    LString_Base<chartype> o;
    if(_n==(u32)-1)
        _n=sc-_start;
    o.resize(_n);
    for(u32 i=_start;i<_start+_n;i++)
        o[i-_start]=mData[i];
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::getWithoutWhiteSpaces() const
{
    LString_Base<chartype> o=(*this);
    o.removeWhiteSpaces();
    return o;
}

template <typename chartype>
void LString_Base<chartype>::insert(u32 _index, const chartype *_val)
{
    u32 valc=__utility_strlen(_val);
    u32 pc=getCapacity();
    lError(_index>=pc,"void LString_Base<chartype>::insert(u32 _index, const chartype *_val): _index is not accptable");
    if(_val==0)
        return;
    resize(getCapacity()+valc);
    lMemoryMove(&mData[_index+valc],&mData[_index],(pc-_index)*sizeof(*mData));
    lMemoryCopy(&mData[_index],_val,valc*sizeof(*mData));
}

template <typename chartype>
void LString_Base<chartype>::insert(u32 _index, const LString_Base<chartype> &_val)
{
    insert(_index,_val.mData);
}

template <typename chartype>
bool LString_Base<chartype>::isEmpty() const
{
    return (getCapacity()==0);
}

template <typename chartype>
bool LString_Base<chartype>::isInt(u32 _base) const
{
    lError(_base>16||_base<2,"bool LString_Base<chartype>::isInt(u32 _base) const: _base is not acceptable [2,16]",false);
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    LString_Base<chartype> _this=this->toUpper();
    u32 tc=getCapacity();
    _base -= 1;// for access string index must be [0-15]
    if(_this.mData[0]!=(chartype)'+'&&_this.mData[0]!=(chartype)'-')
        if((_this.mData[0]>(chartype)vt[_base]||_this.mData[0]<(chartype)'0')||
           (_this.mData[0]>(chartype)'9'&&_this.mData[0]<(chartype)'A'))
            return false;
    for(u32 i=1;i<tc;i++)
        if((_this.mData[i]>(chartype)vt[_base]||_this.mData[i]<(chartype)'0')||
           (_this.mData[i]>(chartype)'9'&&_this.mData[i]<(chartype)'A'))
            return false;
    return true;
}

template <typename chartype>
bool LString_Base<chartype>::isUInt(u32 _base) const
{
    lError(_base>16||_base<2,"bool LString_Base<chartype>::isUInt(u32 _base) const: _base is not acceptable [2,16]",false);
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    LString_Base<chartype> _this=this->toUpper();
    u32 tc=getCapacity();
    _base -= 1;// for access string index must be [0-15]
    for(u32 i=1;i<tc;i++)
        if((_this.mData[i]>(chartype)vt[_base]||_this.mData[i]<(chartype)'0')||
           (_this.mData[i]>(chartype)'9'&&_this.mData[i]<(chartype)'A'))
            return false;
    return true;
}

template <typename chartype>
void LString_Base<chartype>::remove(u32 _index)
{
    lError(_index>=getCapacity(),"void LString_Base<chartype>::remove(u32 _index): _index is not accpetable");
    erase(_index,1);
}

template <typename chartype>
void LString_Base<chartype>::removeWhiteSpaces()
{
    for(u32 i=0;i<getCapacity();i++)
        if(mData[i]==(chartype)' ')
        {
            remove(i);
            i--;
        }
}

template <typename chartype>
void LString_Base<chartype>::replace(u32 _index,const chartype* _val)
{
    u32 valc=__utility_strlen(_val);
    lError(_index>=getCapacity(),"void LString_Base<chartype>::replace(u32 _index,const chartype* _val): _index is not accptable");
    if(_val==0)
        return;
    if(valc+_index>getCapacity())
        resize(valc+_index);
    for(u32 i=0;i<valc;i++)
        mData[_index+i]=_val[i];
}

template <typename chartype>
void LString_Base<chartype>::replace(u32 _index, const LString_Base<chartype> &_val)
{
    replace(_index,_val.mData);
}

template <typename chartype>
void LString_Base<chartype>::replaceAll(const chartype *_what, const chartype *_with, u32 _start, u32 _end)
{
    u32 sc=getCapacity();
    LString_Base<chartype> t=*this;
    if(_end==(u32)-1)
        _end=getCapacity();
    lError(_start>=sc,"void LString_Base<chartype>::replaceAll(const chartype *_what, const chartype *_with, u32 _start, u32 _end): _start is not accpetable");
    lError(_end>sc,"void LString_Base<chartype>::replaceAll(const chartype *_what, const chartype *_with, u32 _start, u32 _end): _end is not accpetable");
    u32 whs=__utility_strlen(_what);
    u32 li=_start-1;
    while ((li=t.find(_what,li+1))!=LString::nothing && li<_end)
    {
        t.erase(li,whs);
        t.insert(li,_with);
    }
    *this=t;
}

template <typename chartype>
void LString_Base<chartype>::replaceAll(const LString_Base<chartype> &_what, const LString_Base<chartype> &_with, u32 _start, u32 _end)
{
    replaceAll(_what.mData,_with.mData,_start,_end);
}

template <typename chartype>
void LString_Base<chartype>::resize(u32 ns)
{
    if(ns==0)
    {
        if(mData)
        {
            delete[] mData;
            mData=0;
        }
        return;
    }
    u32 t_s=__utility_strlen(mData);
    chartype* _pd=mData;
    mData = new chartype[ns+1];
    mData[ns]=L'\0';
    for(u32 i=0;i<ns;i++)
        mData[i]=' ';
    // if there was a previos data copy it on new space
    if(_pd)
    {
        lMemoryCopy(mData,_pd,lMin(t_s,ns)*sizeof(*mData));
        delete[] _pd;
    }
}

template <typename chartype>
void LString_Base<chartype>::reverse()
{
    u32 sc=getCapacity();
    for(u32 i=0;i<sc/2;i++)
        lSwap(mData[i],mData[sc-i-1]);
}

template <typename chartype>
void LString_Base<chartype>::swap(LString_Base<chartype>& _other)
{
    lSwap(mData,_other.mData);
}

template <typename chartype>
short int LString_Base<chartype>::toShortInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    short int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    if(theData[0]==(chartype)'+'||theData[0]==(chartype)'-')
        i=1;
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base)," string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    if(mData[0]==(chartype)'-')
        o=-o;
    return o;
}

template <typename chartype>
unsigned short int LString_Base<chartype>::toUShortInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    unsigned short int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base),"const: string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    return o;
}

template <typename chartype>
int LString_Base<chartype>::toInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    if(theData[0]==(chartype)'+'||theData[0]==(chartype)'-')
        i=1;
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base)," string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    if(mData[0]==(chartype)'-')
        o=-o;
    return o;
}

template <typename chartype>
unsigned int LString_Base<chartype>::toUInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    unsigned int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base),"const: string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    return o;
}

template <typename chartype>
long long int LString_Base<chartype>::toLongLongInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    long long int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    if(theData[0]==(chartype)'+'||theData[0]==(chartype)'-')
        i=1;
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base)," string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    if(mData[0]==(chartype)'-')
        o=-o;
    return o;
}

template <typename chartype>
unsigned long long int LString_Base<chartype>::toULongLongInt(const u32 _base) const
{
    static const LString_Base<chartype> vt("0123456789ABCDEF");
    u32 sc=getCapacity();
    unsigned long long int o=0;
    u32 index=0,i=0;
    LString_Base<chartype> theData=toUpper();
    lError(_base<2||_base>16," _base is not acceptable",0);
    lWarning(!isInt(_base),"const: string is not integer");
    for(;i<sc;i++)
        if((index=vt.find(LString_Base<chartype>(theData[i])))!=nothing &&
            index<_base)
        {
            o= o*_base+index;
        }
        else
            return 0;
    return o;
}

template <typename chartype>
float LString_Base<chartype>::toFloat() const
{
    char* _end;
    u32 tc=getCapacity();
    char* _data=new char[tc];
    for(u32 i=0;i<tc;i++)
        _data[i]=(char)mData[i];
    float _o=strtof(_data,&_end);
    delete[] _data;
    return _o;
}

template <typename chartype>
double LString_Base<chartype>::toDouble() const
{
    char* _end;
    u32 tc=getCapacity();
    char* _data=new char[tc];
    for(u32 i=0;i<tc;i++)
        _data[i]=(char)mData[i];
    double _o=strtod(_data,&_end);
    delete[] _data;
    return _o;
}

template <typename chartype>
long double LString_Base<chartype>::toLongDouble() const
{
    char* _end;
    u32 tc=getCapacity();
    char* _data=new char[tc];
    for(u32 i=0;i<tc;i++)
        _data[i]=(char)mData[i];
    long double _o=strtold(_data,&_end);
    delete[] _data;
    return _o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::toLower() const
{
    u32 sc=getCapacity();
    LString_Base<chartype> o=*this;
    for (u32 i = 0; i < sc; i++)
        if(o[i]>=(chartype)'A'&&o[i]<=(chartype)'Z')
            o[i]+=(chartype)('z'-'Z');
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::toUpper() const
{
    u32 sc=getCapacity();
    LString_Base<chartype> o=*this;
    for (u32 i = 0; i < sc; i++)
        if(o[i]>=(chartype)'a'&&o[i]<=(chartype)'z')
            o[i]-=(chartype)('z'-'Z');
    return o;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const char *_other)
{
    u32 o_s=__utility_strlen(_other);
    clear();
    if(o_s==0)
        mData=0;
    resize(o_s);
    for(u32 i=0;i<o_s;i++)
        mData[i]=(chartype)_other[i];
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const wchar_t *_other)
{
    u32 o_s=__utility_strlen(_other);
    clear();
    if(o_s==0)
        mData=0;
    resize(o_s);
    for(u32 i=0;i<o_s;i++)
        mData[i]=(chartype)_other[i];
    return *this;
}


template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const char32_t *_other)
{
    u32 o_s=__utility_strlen(_other);
    clear();
    if(o_s==0)
        mData=0;
    resize(o_s);
    for(u32 i=0;i<o_s;i++)
        mData[i]=(chartype)_other[i];
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const LString_Base<char> &_other)
{
    *this=_other.mData;
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const LString_Base<wchar_t> &_other)
{
    *this=_other.mData;
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const LString_Base<char32_t> &_other)
{
    *this=_other.mData;
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator+=(const chartype *_other)
{
    u32 o_s=__utility_strlen(_other);
    u32 t_s=__utility_strlen(mData);
    chartype* _pd=mData;
    if(o_s+t_s==0)
    {
        clear();
        return *this;
    }
    mData = new chartype[o_s+t_s+1];
    mData[o_s+t_s]=0;
    if(_pd)
        lMemoryCopy(mData,_pd,t_s*sizeof(*mData));
    if(_other)
        lMemoryCopy(&mData[t_s],_other,o_s*sizeof(*mData));
    if(_pd)
        delete[] _pd;
    return *this;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(LString_Base<chartype>&& _other)
{
    clear();
    mData=_other.mData;
    _other.mData=0;
    return *this;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::operator+(const chartype _other)const
{
    LString_Base<chartype> o=*this;
    o+=_other;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::operator+(const chartype *_other)const
{
    LString_Base<chartype> o=*this;
    o+=_other;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::operator+(const LString_Base<chartype> &_other)const
{
    LString_Base<chartype> o=*this;
    o+=_other;
    return o;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator+=(const chartype _other)
{
    LString_Base<chartype> _o(_other);
    *this+=_o;
    return (*this);
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator+=(const LString_Base &_other)
{
    *this+=_other.mData;
    return *this;
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const LString_Base<chartype> &_other) const
{
    return (*this==_other.getData());
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const char *_other)const
{
    if(mData==0&&_other==0)
        return true;
    else if(mData==0&&_other!=0)
        return false;
    else if(mData!=0&&_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    u32 os = __utility_strlen(_other);
    if(ts!=os)
        return false;
    for(u32 i=0;i<ts;i++)
        if(mData[i]!=(chartype)_other[i])
            return false;
    return true;
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const wchar_t *_other)const
{
    if(mData==0&&_other==0)
        return true;
    else if(mData==0&&_other!=0)
        return false;
    else if(mData!=0&&_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    u32 os = __utility_strlen(_other);
    if(ts!=os)
        return false;
    for(u32 i=0;i<ts;i++)
        if(mData[i]!=(chartype)_other[i])
            return false;
    return true;
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const char32_t *_other)const
{
    if(mData==0&&_other==0)
        return true;
    else if(mData==0&&_other!=0)
        return false;
    else if(mData!=0&&_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    u32 os = __utility_strlen(_other);
    if(ts!=os)
        return false;
    for(u32 i=0;i<ts;i++)
        if(mData[i]!=(chartype)_other[i])
            return false;
    return true;
}


template <typename chartype>
bool LString_Base<chartype>::operator>(const LString_Base<chartype> &_other) const
{
    return (*this>_other.getData());
}

template <typename chartype>
bool LString_Base<chartype>::operator>(const char *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]>(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]<(chartype)_r.mData[i])
            return false;
    return false;
}

template <typename chartype>
bool LString_Base<chartype>::operator>(const wchar_t *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]>(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]<(chartype)_r.mData[i])
            return false;
    return false;
}

template <typename chartype>
bool LString_Base<chartype>::operator>(const char32_t *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]>(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]<(chartype)_r.mData[i])
            return false;
    return false;
}


template <typename chartype>
bool LString_Base<chartype>::operator<(const LString_Base<chartype> &_other) const
{
    return (*this<_other.getData());
}

template <typename chartype>
bool LString_Base<chartype>::operator<(const char *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]<(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]>(chartype)_r.mData[i])
            return false;
    return false;
}

template <typename chartype>
bool LString_Base<chartype>::operator<(const wchar_t *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]<(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]>(chartype)_r.mData[i])
            return false;
    return false;
}

template <typename chartype>
bool LString_Base<chartype>::operator<(const char32_t *_other)const
{
    if(mData==0||_other==0)
        return false;
    u32 ts = __utility_strlen(mData);
    ts = lMin(ts,__utility_strlen(_other));
    LString_Base<chartype> _l=toLower();
    LString_Base<chartype> _r=_other;
    _r=_r.toLower();
    for(u32 i=0;i<ts;i++)
        if(_l.mData[i]<(chartype)_r.mData[i])
            return true;
        else if(_l.mData[i]>(chartype)_r.mData[i])
            return false;
    return false;
}



template <typename chartype>
bool LString_Base<chartype>::operator!=(const chartype *_other) const
{
    return !(*this==_other);
}

template <typename chartype>
bool LString_Base<chartype>::operator!=(const LString_Base<chartype> &_other) const
{
    return !(*this==_other.getData());
}

template <typename chartype>
chartype& LString_Base<chartype>::operator[](u32 i)
{
    return mData[i];
}

template <typename chartype>
chartype LString_Base<chartype>::operator[](u32 i) const
{
    return mData[i];
}

template<typename chartype> template <typename T>
u32 LString_Base<chartype>::__utility_strlen(const T *_t)
{
    if(_t==0)
        return 0;
    for(u32 i=0; ;i++)
        if(_t[i]==0)
            return i;
    return 0;
}

template<>
LString8 LString_Base<char>::toUTF8() const
{
    return *this;
}

template<>
LString8 LString_Base<wchar_t>::toUTF8() const
{
    LString8 o,out;
    o.resize(getCapacity()*4);// maximum capacity is need for output
    u32 l=0;
    for(u32 i=0;i<getCapacity();i++)
    {
        u32 t=__utility_utf16decode(&mData[i]);
        char* ed=__utility_utf8encode(t);
        u32 eds=(__utility_strlen(ed)+1)*sizeof(char) ;
        lMemoryCopy(&o.mData[l],ed,eds);
        l+=eds-1;
        // Two charcters will show as one
        if(t>=0x10000)
            i++;
    }
    out=o;
    return out;
}

template<>
LString8 LString_Base<char32_t>::toUTF8() const
{
    LString8 o,out;
    o.resize(getCapacity()*6);// maximum capacity is need for output
    u32 l=0;
    for(u32 i=0;i<getCapacity();i++)
    {
        u32 t=mData[i];
        char* ed=__utility_utf8encode(t);
        u32 eds=(__utility_strlen(ed)+1);
        lMemoryCopy(&o.mData[l],ed,eds*sizeof(char));
        l+=eds-1;
    }
    out=o;
    return out;
}

template<>
LString LString_Base<wchar_t>::toUTF16() const
{
    return *this;
}

template<>
LString LString_Base<char32_t>::toUTF16() const
{
    LString o,out;
    o.resize(getCapacity()*2);// maximum capacity is need for output
    u32 l=0;
    for(u32 i=0;i<getCapacity();i++)
    {
        u32 t=mData[i];
        wchar_t* ed=__utility_utf16encode(t);
        u32 eds=(__utility_strlen(ed)+1);
        lMemoryCopy(&o.mData[l],ed,eds*sizeof(wchar_t));
        l+=eds-1;
    }
    out=o;
    return out;
}

template<>
LString LString_Base<char>::toUTF16() const
{
    return LString::fromUTF8(*this);
}


template<>
LString32 LString_Base<char>::toUTF32() const
{
    return LString32::fromUTF8(mData);
}

template<>
LString32 LString_Base<wchar_t>::toUTF32() const
{
    return LString32::fromUTF16(mData);
}

template<>
LString32 LString_Base<char32_t>::toUTF32() const
{
    return *this;
}



template <typename chartype>
char *LString_Base<chartype>::__utility_utf8encode(u32 _in)
{
    static char o[7];
    o[0]='\0';
    if(_in==0)
    {
        o[0]='\0';
    }
    else if(_in<=0x7f)
    {
        o[0]=_in;
        o[1]='\0';
    }
    else if(_in<=0x7ff)
    {
        o[0]=0xC0|_in>>6;
        o[1]=0x80|((_in)&(~(0xC0)));
        o[2]='\0';
    }
    else if(_in<=0xffff)
    {
        o[0]=0xE0|_in>>12;
        o[1]=0x80|((_in>>6)&(~(0xC0)));
        o[2]=0x80|((_in)&(~(0xC0)));
        o[3]='\0';
    }
    else if(_in<=0x1fffff)
    {
        o[0]=0xF0|_in>>18;
        o[1]=0x80|((_in>>12)&(~(0xC0)));
        o[2]=0x80|((_in>>6)&(~(0xC0)));
        o[3]=0x80|((_in)&(~(0xC0)));
        o[4]='\0';
    }
    else if(_in<=0x3FFFFFF)
    {
        o[0]=0xF8|_in>>24;
        o[1]=0x80|((_in>>18)&(~(0xC0)));
        o[2]=0x80|((_in>>12)&(~(0xC0)));
        o[3]=0x80|((_in>>6)&(~(0xC0)));
        o[4]=0x80|((_in)&(~(0xC0)));
        o[5]='\0';
    }
    else if(_in<=0x7FFFFFFF)
    {
        o[0]=0xFC|_in>>30;
        o[1]=0x80|((_in>>24)&(~(0xC0)));
        o[2]=0x80|((_in>>18)&(~(0xC0)));
        o[3]=0x80|((_in>>12)&(~(0xC0)));
        o[4]=0x80|((_in>>6)&(~(0xC0)));
        o[4]=0x80|((_in)&(~(0xC0)));
        o[5]='\0';
    }

    return o;
}

template <typename chartype>
u32 LString_Base<chartype>::__utility_utf8decode(const char *_in2)
{
    const unsigned char* _in=(unsigned char*)_in2;
    u32 o=0;
    if((_in[0]&0xFE)==0xFC)
    {
        o=(_in[0]&(~0xFE))<<30;
        o+=(_in[1]&(~0xC0))<<24;
        o+=(_in[2]&(~0xC0))<<18;
        o+=(_in[3]&(~0xC0))<<12;
        o+=(_in[4]&(~0xC0))<<6;
        o+=(_in[5]&(~0xC0));
    }
    else if((_in[0]&0xFC)==0xF8)
    {
        o=(_in[0]&(~0xFC))<<24;
        o+=(_in[1]&(~0xC0))<<18;
        o+=(_in[2]&(~0xC0))<<12;
        o+=(_in[3]&(~0xC0))<<6;
        o+=(_in[4]&(~0xC0));
    }
    else if((_in[0]&0xF8)==0xF0)
    {
        o=(_in[0]&(~0xF8))<<18;
        o+=(_in[1]&(~0xC0))<<12;
        o+=(_in[2]&(~0xC0))<<6;
        o+=(_in[3]&(~0xC0));
    }
    else if((_in[0]&0xF0)==0xE0)
    {
        o=(_in[0]&(~0xF0))<<12;
        o+=(_in[1]&(~0xC0))<<6;
        o+=(_in[2]&(~0xC0));
    }
    else if((_in[0]&0xE0)==0xC0)
    {
        o=(_in[0]&(~0xE0))<<6;
        o+=(_in[1]&(~0xC0));
    }
    else if((_in[0]&0xC0)==0xB0)
    {
        o=(_in[0]&(~0xC0));
    }
    else
        o=_in[0];

    return o;
}

template <typename chartype>
wchar_t* LString_Base<chartype>::__utility_utf16encode(u32 _in)
{
    static wchar_t o[3];
    o[0]=L'\0';
    if(_in==0)
        o[0]=L'\0';
    else if((_in<=0xD7FF)||(_in>=0xE000&&_in<=0xFFFF))
    {
        o[0]=_in;
        o[1]=L'\0';
    }
    else if(_in>=0x10000&&_in<=0x10FFFF)
    {
        _in=_in-0x10000;
        o[0]=0xD800|(_in>>10);
        o[1]=0xDC00|(_in&0x3FF);
        o[2]=L'\0';
    }
    return o;
}

template <typename chartype>
u32 LString_Base<chartype>::__utility_utf16decode(const wchar_t *_in)
{
    u32 o=0;
    if(((_in[0]&0xFC00)==0xD800)&&((_in[1]&0xFC00)==0xDC00))
    {
        o=0x10000;
        o+=(_in[0]&0x3FF)<<10;
        o+=(_in[1]&0x3FF);
    }
    else
    {
        o=_in[0];
    }
    return o;
}

template <typename chartype1,typename chartype2>
LString_Base<chartype1> operator +(const chartype1 *_a, const LString_Base<chartype2> &_b)
{
    LString_Base<chartype1> o=_a;
    o+=_b;
    return o;
}

template <typename chartype1,typename chartype2>
bool operator ==(const chartype1 *_a, const LString_Base<chartype2> &_b)
{
    return (_b==_a);
}

template LString_Base<char> operator +(const char *_a, const LString_Base<char> &_b);
template LString_Base<char> operator +(const char *_a, const LString_Base<wchar_t> &_b);
template LString_Base<char> operator +(const char *_a, const LString_Base<char32_t> &_b);

template LString_Base<wchar_t> operator +(const wchar_t *_a, const LString_Base<char> &_b);
template LString_Base<wchar_t> operator +(const wchar_t *_a, const LString_Base<wchar_t> &_b);
template LString_Base<wchar_t> operator +(const wchar_t *_a, const LString_Base<char32_t> &_b);

template LString_Base<char32_t> operator +(const char32_t *_a, const LString_Base<char> &_b);
template LString_Base<char32_t> operator +(const char32_t *_a, const LString_Base<wchar_t> &_b);
template LString_Base<char32_t> operator +(const char32_t *_a, const LString_Base<char32_t> &_b);



template bool operator ==(const char *_a, const LString_Base<char> &_b);
template bool operator ==(const char *_a, const LString_Base<wchar_t> &_b);
template bool operator ==(const char *_a, const LString_Base<char32_t> &_b);

template bool operator ==(const wchar_t *_a, const LString_Base<char> &_b);
template bool operator ==(const wchar_t *_a, const LString_Base<wchar_t> &_b);
template bool operator ==(const wchar_t *_a, const LString_Base<char32_t> &_b);

template bool operator ==(const char32_t *_a, const LString_Base<char> &_b);
template bool operator ==(const char32_t *_a, const LString_Base<wchar_t> &_b);
template bool operator ==(const char32_t *_a, const LString_Base<char32_t> &_b);

LNAMESPACE_END
