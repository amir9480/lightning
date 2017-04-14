#include "lstring.h"
#include "lmathutility.h"

LNAMESPACE_BEGIN
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
LString_Base<chartype>::LString_Base(const chartype *_other)
{
    mData=0;
    (*this)=_other;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(const LString_Base<chartype> &_other)
{
    mData=0;
    (*this)=_other;
}

template <typename chartype>
LString_Base<chartype>::LString_Base(LString_Base<chartype>&& _other)
{
    mData=0;
    (*this)=_other;
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
void LString_Base<chartype>::clear()
{
    if(mData)
        delete[] mData;
    mData=0;
}

template <typename chartype>
void LString_Base<chartype>::erase(u32 _start, u32 _n)
{
    if(_n==(u32)-1)
    {
        LString_Base<chartype> t=*this;
        t[_start]=0;
        *this=t;
        return;
    }
    u32 pc=getCapasity();
    lMemoryMove(&mData[_start],&mData[_start+_n],(pc-(_start+_n)+1)*sizeof(*mData));
    resize(getCapasity());// flush
}

template <typename chartype>
u32 LString_Base<chartype>::find(const chartype *_what, u32 _from)const
{
    u32 strc=getCapasity();
    u32 whatc=__utility_strlen(_what);
    for(u32 i=_from;i<strc-whatc;i++)
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
    u32 strc=getCapasity();
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
u32 LString_Base<chartype>::getCapasity() const
{
    return __utility_strlen(mData);
}

template <typename chartype>
chartype *LString_Base<chartype>::getData() const
{
    return mData;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::getSubString(u32 _start, u32 _n) const
{
    LString_Base<chartype> o;
    if(_n==(u32)-1)
        _n=getCapasity()-_start;
    o.resize(_n);
    for(u32 i=_start;i<_start+_n;i++)
        o[i-_start]=mData[i];
    return o;
}

template <typename chartype>
void LString_Base<chartype>::insert(u32 _index, const chartype *_val)
{
    u32 valc=__utility_strlen(_val);
    u32 pc=getCapasity();
    resize(getCapasity()+valc);
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
    return (getCapasity()==0);
}

template <typename chartype>
void LString_Base<chartype>::replace(u32 _index,const chartype* _val)
{
    u32 valc=__utility_strlen(_val);
    if(valc+_index>getCapasity())
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
void LString_Base<chartype>::resize(u32 ns)
{
    u32 t_s=__utility_strlen(mData);
    chartype* _pd=mData;
    mData = new chartype[ns+1];
    mData[ns]=L'\0';
    for(u32 i=0;i<ns;i++)
        mData[i]=' ';
    if(_pd)
    {
        lMemoryCopy(mData,_pd,lMin(t_s,ns)*sizeof(*mData));
        delete[] _pd;
    }
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator=(const chartype *_other)
{
    u32 o_s=__utility_strlen(_other);
    clear();
    if(o_s==0)
        mData=0;
    resize(o_s);
    lMemoryCopy(mData,_other,o_s*sizeof(*mData));
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
LString_Base<chartype> &LString_Base<chartype>::operator=(const LString_Base<chartype>& _other)
{
    *this=_other.mData;
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
LString_Base<chartype> LString_Base<chartype>::operator+(const chartype *_other)
{
    LString_Base o=*this;
    o+=_other;
    return o;
}

template <typename chartype>
LString_Base<chartype> LString_Base<chartype>::operator+(const LString_Base<chartype> &_other)
{
    LString_Base o=*this;
    o+=_other;
    return o;
}

template <typename chartype>
LString_Base<chartype> &LString_Base<chartype>::operator+=(const LString_Base &_other)
{
    *this+=_other.mData;
    return *this;
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const chartype *_other) const
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
    return (lMemoryCompare(mData,_other,ts*sizeof(*mData))==0);
}

template <typename chartype>
bool LString_Base<chartype>::operator==(const LString_Base<chartype> &_other) const
{
    return (*this==_other.getData());
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


// type define
template class LString_Base<wchar_t>;
template class LString_Base<char>;
template class LString_Base<char32_t>;

LNAMESPACE_END
