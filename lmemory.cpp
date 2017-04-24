#include "lmemory.h"
LNAMESPACE_BEGIN

<<<<<<< HEAD
void LAPI lMemoryCopy(void *_dest, const void *_source, u32 _copysize)
=======
void lMemoryCopy(void *_dest, const void *_source, u32 _copysize)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
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

<<<<<<< HEAD
void LAPI lMemoryCopy2(void *_dest, const void *_source, u32 _copysize)
=======
void lMemoryCopy2(void *_dest, const void *_source, u32 _copysize)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
{
    uchar* _d=(uchar*)_dest;
    uchar* _s=(uchar*)_source;
    for(u32 i=0;i<_copysize;i++)
        _d[i]=_s[i];
}

<<<<<<< HEAD
void LAPI lMemoryMove(void *_dest, const void *_source, u32 _copysize)
=======
void lMemoryMove(void *_dest, const void *_source, u32 _copysize)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
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

<<<<<<< HEAD
i8 LAPI lMemoryCompare(const void *_a, const void *_b, u32 s)
=======
i8 lMemoryCompare(const void *_a, const void *_b, u32 s)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
{
    char* a=(char*)_a;
    char* b=(char*)_b;
    u8 o=0;
    for(u32 i=0;i<s;i++)
        if((o=(a[i]-b[i]))!=0)
            return o;
    return 0;
}

LNAMESPACE_END
