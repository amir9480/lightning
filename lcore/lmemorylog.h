#ifndef LMEMORYLOG_H
#define LMEMORYLOG_H

#include "../lconfig.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define lMemoryLogStart()\
    __lmemlog_allowed=true;{

#define lMemoryLogEnd()\
    }__lmemlog_allowed=false;

#define lMemoryLogStartIgnore()\
    __lmemlog_allowed=false;

#define lMemoryLogEndIgnore()\
    __lmemlog_allowed=true;


/*!
 * Note That Memory log only working with new and delete
 * it does not support malloc or free and ...
 */
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
    _lptrlogmanager();

    ~_lptrlogmanager();

    void addPtr(_lptrobj _in);

    void addArrayPtr(_lptrobj _in);

    //! check is address a valid allocated space
    bool isValidPointer(void* address);

    //! check pointer is a simple dynamically allocated  (Not Array)
    bool isSimplePointer(void* address);

    // pointer is a array dynamically allocated
    bool isArrayPointer(void* address);

    void removePtr(void* address);

    void removeArrayPtr(void* address);


private:
    void removePtrItem(unsigned int _index);

    void removeArrayPtrItem(unsigned int _index);

private:
    _lptrobj*          ptrs;
    unsigned int       ptrssize;
    unsigned int       totalptrsize;
    _lptrobj*          arrayptrs;
    unsigned int       arrayptrssize;
    unsigned int       totalarrayptrsize;

    bool               wrongjob;
};
//! default memory logger
extern _lptrlogmanager __lptrlogmanager;

extern bool __lmemlog_allowed;

void* operator new (size_t _size,const char* _filename,unsigned int _line);

void* operator new[] (size_t _size,const char* _filename,unsigned int _line);

void operator delete (void* ptr)noexcept;

void operator delete[] (void* ptr)noexcept;

#undef new
#define new  new(__FILE__,__LINE__)


#endif // LMEMORYLOG_H
