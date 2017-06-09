#include "lmemory.h"


LNAMESPACE_BEGIN

void LAPI lMemoryCopy(void *_dest, const void *_source, u32 _copysize)
{
    uchar* _d=(uchar*)_dest;
    uchar* _s=(uchar*)_source;
    u64* _d8=(u64*)_dest;
    u64* _s8=(u64*)_source;
    for(u32 i=0;i<(_copysize/8);i++)
        _d8[i]=_s8[i];
    for(u32 i=(_copysize/8)*8;i<_copysize;i++)
        _d[i]=_s[i];
}

void LAPI lMemoryCopy2(void *_dest, const void *_source, u32 _copysize)
{
    uchar* _d=(uchar*)_dest;
    uchar* _s=(uchar*)_source;
    for(u32 i=0;i<_copysize;i++)
        _d[i]=_s[i];
}

void LAPI lMemoryMove(void *_dest, const void *_source, u32 _copysize)
{
    uchar* _d=(uchar*)_dest;
    uchar* _s=(uchar*)_source;

    uchar* t=new uchar[_copysize];
    for(u32 i=0;i<_copysize;i++)
        t[i]=_s[i];
    for(u32 i=0;i<_copysize;i++)
        _d[i]=t[i];
    delete[] t;
}

i8 LAPI lMemoryCompare(const void *_a, const void *_b, u32 s)
{
    char* a=(char*)_a;
    char* b=(char*)_b;
    u8 o=0;
    for(u32 i=0;i<s;i++)
        if((o=(a[i]-b[i]))!=0)
            return o;
    return 0;
}

void lMemorySet(void *_a, u32 _size, char _val)
{
    char* a=(char*)_a;
    for(u32 i=0;i<_size;i++)
        a[i]=_val;
}

LNAMESPACE_END

