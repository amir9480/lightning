#include "lmemorylog.h"
#include "llog.h"

#if LTARGET == LTARGET_DEBUG

int ___lmemlog_allowed=0;

#undef new
#define new new

_lptrlogmanager __lptrlogmanager;

void operator delete(void *ptr)noexcept
{
    if(___lmemlog_allowed==1)
        __lptrlogmanager.removePtr(ptr);
    free(ptr);
}

void operator delete[](void *ptr)noexcept
{
    if(___lmemlog_allowed==1)
        __lptrlogmanager.removeArrayPtr(ptr);
    free(ptr);
}

void *operator new(size_t _size, const char *_filename, unsigned int _line)
{
    void* o=malloc(_size);
    _lptrobj a;
    a.mAddress=o;
    a.mFile=_filename;
    a.mLine=_line;
    a.mSize=_size;
    if(___lmemlog_allowed==1)
        __lptrlogmanager.addPtr(a);
    return o;
}

void *operator new[](size_t _size, const char *_filename, unsigned int _line)
{
    void* o=malloc(_size);
    _lptrobj a;
    a.mAddress=o;
    a.mFile=_filename;
    a.mLine=_line;
    a.mSize=_size;
    if(___lmemlog_allowed==1)
        __lptrlogmanager.addArrayPtr(a);
    return o;
}


#undef new
#define new new(__FILE__,__LINE__)




_lptrlogmanager::_lptrlogmanager()
{
    FILE* f=fopen(LMLOG_FILE,"w");// clear previous session
    fclose(f);
    ptrs=(_lptrobj*)malloc(1*sizeof(_lptrobj));
    arrayptrs=(_lptrobj*)malloc(1*sizeof(_lptrobj));
    ptrssize=arrayptrssize=totalptrsize=totalarrayptrsize=0;
    wrongjob=false;
}

_lptrlogmanager::~_lptrlogmanager()
{
    FILE* f=fopen(LMLOG_FILE,"a");

    fprintf(f,"undestroyed Allocated size is %d B \n\n",ptrssize+arrayptrssize);

    for(unsigned int i=0;i<ptrssize;i++)
        fprintf(f,"memory leak detected . var was allocated in %s ( %d ) address=%p \n\n",ptrs[i].mFile,ptrs[i].mLine,ptrs[i].mAddress);

    for(unsigned int i=0;i<arrayptrssize;i++)
        fprintf(f,"memory leak detected . array was allocated in %s ( %d ) address=%p \n\n",arrayptrs[i].mFile,arrayptrs[i].mLine,arrayptrs[i].mAddress);

    Lightning::lSetConsoleColor(Lightning::LConsoleColor::Red);
    if(ptrssize>0||arrayptrssize>0||wrongjob)
        printf("\n*************************************************************************\n*** Memory leak detected please check file =\"%s\" ***\n*************************************************************************\n",LMLOG_FILE);
    Lightning::lSetConsoleColor(Lightning::LConsoleColor::Cyan);

    if(ptrssize+arrayptrssize==0)
        fprintf(f,"Every thing is OK . thanks for checking \n\n");

    fclose(f);

    free(ptrs);
    free(arrayptrs);
}

void _lptrlogmanager::addPtr(_lptrobj _in)
{
    ptrssize+=1;
    _lptrobj* t=ptrs;
    ptrs = (_lptrobj*)malloc(sizeof(_lptrobj)*ptrssize);
    memcpy(ptrs,t,sizeof(_lptrobj)*(ptrssize-1));
    free(t);
    ptrs[ptrssize-1]=_in;
    totalptrsize+=_in.mSize;
}

void _lptrlogmanager::addArrayPtr(_lptrobj _in)
{
    arrayptrssize+=1;
    _lptrobj* t=arrayptrs;
    arrayptrs = (_lptrobj*)malloc(sizeof(_lptrobj)*arrayptrssize);
    memcpy(arrayptrs,t,sizeof(_lptrobj)*(arrayptrssize-1));
    free(t);
    arrayptrs[arrayptrssize-1]=_in;
    totalarrayptrsize+=_in.mSize;
}

bool _lptrlogmanager::isValidPointer(void *address)
{
    for(unsigned int i=0;i<ptrssize;i++)
        if(ptrs[i].mAddress==address)
            return true;
    for(unsigned int i=0;i<arrayptrssize;i++)
        if(arrayptrs[i].mAddress==address)
            return true;
    return false;
}

bool _lptrlogmanager::isSimplePointer(void *address)
{
    for(unsigned int i=0;i<ptrssize;i++)
        if(ptrs[i].mAddress==address)
            return true;
    return false;
}

bool _lptrlogmanager::isArrayPointer(void *address)
{
    for(unsigned int i=0;i<arrayptrssize;i++)
        if(arrayptrs[i].mAddress==address)
            return true;
    return false;
}

void _lptrlogmanager::removePtr(void *address)
{
    for(unsigned int i=0;i<ptrssize;i++)
        if(ptrs[i].mAddress==address)
        {
            totalptrsize-=ptrs[i].mSize;
            removePtrItem(i);
            return;
        }
    for(unsigned int i=0;i<arrayptrssize;i++)
        if(arrayptrs[i].mAddress==address)
        {
            FILE* f=fopen(LMLOG_FILE,"a");
            fprintf(f,"wrong type of delete . you need to use delete[] instead of delete address=%p \n\n",address);
            wrongjob=true;
            fclose(f);
            return;
        }

    FILE* f=fopen(LMLOG_FILE,"a");
    fprintf(f,"you delete nothing! address=%p \n\n",address);
    wrongjob=true;
    fclose(f);
}

void _lptrlogmanager::removeArrayPtr(void *address)
{
    for(unsigned int i=0;i<arrayptrssize;i++)
        if(arrayptrs[i].mAddress==address)
        {
            totalarrayptrsize-=arrayptrs[i].mSize;
            removeArrayPtrItem(i);
            return;
        }
    for(unsigned int i=0;i<ptrssize;i++)
        if(ptrs[i].mAddress==address)
        {
            FILE* f=fopen(LMLOG_FILE,"a");
            fprintf(f,"wrong type of delete . you need to use delete instead of delete[] address=%p \n\n",address);
            wrongjob=true;
            fclose(f);
            return;
        }
    FILE* f=fopen(LMLOG_FILE,"a");
    fprintf(f,"you delete nothing! address=%p \n\n",address);
    wrongjob=true;
    fclose(f);
}

void _lptrlogmanager::removePtrItem(unsigned int _index)
{
    for(unsigned int i=_index;i<ptrssize-1;i++)
        ptrs[i]=ptrs[i+1];
    ptrssize--;
    if(ptrssize>0)
        ptrs=(_lptrobj*)realloc(ptrs,sizeof(_lptrobj)*ptrssize);
}

void _lptrlogmanager::removeArrayPtrItem(unsigned int _index)
{
    for(unsigned int i=_index;i<arrayptrssize-1;i++)
        arrayptrs[i]=arrayptrs[i+1];
    arrayptrssize--;
    if(arrayptrssize>0)
        arrayptrs=(_lptrobj*)realloc(arrayptrs,sizeof(_lptrobj)*arrayptrssize);
}


#endif
