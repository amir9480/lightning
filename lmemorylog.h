#ifndef LMEMORYLOG_H
#define LMEMORYLOG_H

#include "lconfig.h"
#include <stdio.h>
#include <stdlib.h>

#if LTARGET == LTARGET_DEBUG

struct _lptrobj
{
    void*        mAddress;//Address of memory
    unsigned int mLine;// line of allocate
    const char*  mFile;// file name of allocate point
    unsigned int mSize;// size that allocated
};

class _lptrlogmanager
{
public:
    _lptrlogmanager()
    {
        FILE* f=fopen(LMLOG_FILE,"w");// clear previous session
        fclose(f);
        ptrs=(_lptrobj*)malloc(1*sizeof(_lptrobj));
        arrayptrs=(_lptrobj*)malloc(1*sizeof(_lptrobj));
        ptrssize=arrayptrssize=totalptrsize=totalarrayptrsize=0;
        wrongjob=false;
    }

    ~_lptrlogmanager()
    {
        FILE* f=fopen(LMLOG_FILE,"a");

        for(unsigned int i=0;i<ptrssize;i++)
            fprintf(f,"memory leak detected . var was allocated in %s ( %d ) address=%p \n\n",ptrs[i].mFile,ptrs[i].mLine,ptrs[i].mAddress);

        for(unsigned int i=0;i<arrayptrssize;i++)
            fprintf(f,"memory leak detected . array was allocated in %s ( %d ) address=%p \n\n",arrayptrs[i].mFile,arrayptrs[i].mLine,arrayptrs[i].mAddress);

        if(ptrssize>0||arrayptrssize>0||wrongjob)
            printf("\n\n***Memory leak detected please check file =\"%s\"***\n\n",LMLOG_FILE);

        fclose(f);
        free(ptrs);
        free(arrayptrs);
    }

    void addPtr(_lptrobj _in)
    {
        ptrssize+=1;
        ptrs=(_lptrobj*)realloc(ptrs,sizeof(_lptrobj)*ptrssize);
        ptrs[ptrssize-1]=_in;
        totalptrsize+=_in.mSize;
    }

    void addArrayPtr(_lptrobj _in)
    {
        arrayptrssize+=1;
        arrayptrs=(_lptrobj*)realloc(arrayptrs,sizeof(_lptrobj)*arrayptrssize);
        arrayptrs[arrayptrssize-1]=_in;
        totalarrayptrsize+=_in.mSize;
    }

    void removePtr(void* address)
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

    void removeArrayPtr(void* address)
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

private:
    void removePtrItem(unsigned int _index)
    {
        for(unsigned int i=_index;i<ptrssize-1;i++)
            ptrs[i]=ptrs[i+1];
        ptrssize--;
        ptrs=(_lptrobj*)realloc(ptrs,sizeof(_lptrobj)*ptrssize);
    }

    void removeArrayPtrItem(unsigned int _index)
    {
        for(unsigned int i=_index;i<arrayptrssize-1;i++)
            arrayptrs[i]=arrayptrs[i+1];
        arrayptrssize--;
        arrayptrs=(_lptrobj*)realloc(arrayptrs,sizeof(_lptrobj)*arrayptrssize);
    }

private:
    _lptrobj*          ptrs;
    unsigned int       ptrssize;
    unsigned int       totalptrsize;
    _lptrobj*          arrayptrs;
    unsigned int       arrayptrssize;
    unsigned int       totalarrayptrsize;

    bool               wrongjob;
};

extern _lptrlogmanager __lptrlogmanager;

inline void* operator new (unsigned int _size,const char* _filename,unsigned int _line)
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

inline void* operator new[] (unsigned int _size,const char* _filename,unsigned int _line)
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

inline void operator delete (void* ptr)
{
    __lptrlogmanager.removePtr(ptr);
    free(ptr);
}

inline void operator delete[] (void* ptr)
{
    __lptrlogmanager.removeArrayPtr(ptr);
    free(ptr);
}

#undef new
#define new new(__FILE__,__LINE__)

#endif// LTARGET == LTARGET_DEBUG

#endif // LMEMORYLOG_H
