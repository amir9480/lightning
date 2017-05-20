#include "lmemorylog.h"



#undef new
#define new new


void operator delete(void *ptr)noexcept
{
    __lptrlogmanager.removePtr(ptr);
    free(ptr);
}

void operator delete[](void *ptr)noexcept
{
    __lptrlogmanager.removeArrayPtr(ptr);
    free(ptr);
}

void *operator new(unsigned int _size, const char *_filename, unsigned int _line)
{
    void* o=malloc(_size);
    _lptrobj a;
    a.mAddress=o;
    a.mFile=_filename;
    a.mLine=_line;
    a.mSize=_size;
    __lptrlogmanager.addPtr(a);
    return o;
}

void *operator new[](unsigned int _size, const char *_filename, unsigned int _line)
{
    void* o=malloc(_size);
    _lptrobj a;
    a.mAddress=o;
    a.mFile=_filename;
    a.mLine=_line;
    a.mSize=_size;
    __lptrlogmanager.addArrayPtr(a);
    return o;
}


#undef new
#define new new(__FILE__,__LINE__)

_lptrlogmanager __lptrlogmanager;


