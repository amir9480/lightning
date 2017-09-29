#ifndef LMEMORYMANAGER_H
#define LMEMORYMANAGER_H

#include "ldefines.h"
#include "llog.h"
#include "lmemorylog.h"



LNAMESPACE_BEGIN

template<typename T>
class LAPI LUniquePointer
{
    LUniquePointer(){}
public:
    LUniquePointer(const LUniquePointer<T>& )=delete;
    LUniquePointer(LUniquePointer<T>&& _other)
    {
        mData=_other.mData;
        _other.mData=nullptr;
    }

    virtual ~LUniquePointer()
    {
        destroy();
    }

    static LUniquePointer<T> create()
    {
        LUniquePointer<T> out;
        out.mData = new T();
        return out;
    }

    template<typename... ObjectArgs>
    static LUniquePointer<T> create(ObjectArgs... args)
    {
        LUniquePointer<T> out;
        out.mData = new T(args...);
        return out;
    }

    void destroy()
    {
        if(mData)
        {
            delete mData;
            mData=nullptr;
        }
    }

    T* getData()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    const T* getData()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }


    LUniquePointer& operator=(const LUniquePointer<T>& )=delete;
    LUniquePointer& operator=(LUniquePointer<T>&& _other)
    {
        destroy();
        mData=_other.mData;
        _other.mData=nullptr;
        return *this;
    }

    T& operator*()
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    const T& operator*()const
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    T* operator-> ()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    const T* operator-> ()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    operator T()
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    operator T*()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    operator const T()const
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    operator const T*()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

private:
    T*      mData;
};


template<typename T>
class LAPI LUniquePointer<T[]>
{
    LUniquePointer(){}
public:
    LUniquePointer(const LUniquePointer<T[]>& )=delete;
    LUniquePointer(LUniquePointer<T[]>&& _other)
    {
        mData=_other.mData;
        mSize=_other.mSize;
        _other.mData=nullptr;
        _other.mSize=0;
    }

    virtual ~LUniquePointer()
    {
        destroy();
    }

    static LUniquePointer<T[]> create(u64 _size)
    {
        LUniquePointer<T[]> out;
        out.mSize = _size;

#undef new
#define new new

        out.mData =(T*) operator new[](sizeof(T)*_size);
        for(u64 i=0;i<_size;i++)
        {
            new (&out.mData[i]) T();
        }

#if LTARGET == LTARGET_DEBUG
        __lptrlogmanager.addArrayPtr({&out.mData[0],__LINE__,__FILE__,sizeof(T)*_size});
#endif

#undef new
#define new LIGHTNING_NEW

        return out;
    }

    template<typename... ObjectArgs>
    static LUniquePointer<T[]> create(u64 _size,ObjectArgs... args)
    {
        LUniquePointer<T[]> out;
        out.mSize = _size;

#undef new
#define new new

        out.mData =(T*) operator new[](sizeof(T)*_size);
        for(u64 i=0;i<_size;i++)
            new (&out.mData[i]) T(args...);


#if LTARGET == LTARGET_DEBUG
        __lptrlogmanager.addArrayPtr({&out.mData[0],__LINE__,__FILE__,sizeof(T)*_size});
#endif

#undef new
#define new LIGHTNING_NEW

        return out;
    }

    void destroy()
    {
        if(mData)
        {
            for(u64 i=mSize;i>0;i--)
            {
                mData[i-1].~T();
            }
            void* _data = (void*) mData;
            operator delete[](_data);
            mData=nullptr;
            mSize=0;
        }
    }

    T* getData()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    const T* getData()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    u64 getSize()const
    {
        return mSize;
    }


    LUniquePointer<T[]>& operator=(const LUniquePointer<T[]>& )=delete;
    LUniquePointer<T[]>& operator=(LUniquePointer<T[]>&& _other)
    {
        destroy();
        mData = _other.mData;
        mSize = _other.mSize;
        _other.mData = nullptr;
        _other.mSize = 0;
        return *this;
    }

    T* operator+(u32 _i)const
    {
        lAssert(mData==nullptr,"Data is null");
        lAssert(_i>=mSize,"_i is bigger than size");
        T* o = mData+_i;
        return o;
    }

    T& operator[](const u32 _i)
    {
        lAssert(mData==nullptr,"Data is null");
        lAssert(_i>=mSize,"index is bigger than size");
        return mData[_i];
    }

    operator T*()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    operator const T*()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

private:
    T*      mData;
    u64     mSize;
};




////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class LAPI LSharedPointer
{
    LSharedPointer()
    {
        mUsed=new u32(1);
    }
public:
    LSharedPointer(const LSharedPointer<T>& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        (*mUsed)++;
    }

    LSharedPointer(LSharedPointer<T>&& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        _other.mData=nullptr;
    }

    virtual ~LSharedPointer()
    {
        destroy();
    }


    static LSharedPointer<T> create()
    {
        LSharedPointer<T> out;
        out.mData = new T();
        return out;
    }

    template<typename... ObjectArgs>
    static LSharedPointer<T> create(ObjectArgs... args)
    {
        LSharedPointer<T> out;
        out.mData = new T(args...);
        return out;
    }

    void destroy()
    {
        if(mData)
        {
            (*mUsed)--;
            if( (*mUsed) ==0 )
            {
                delete mUsed;
                delete mData;
                mData=nullptr;
                mUsed=nullptr;
            }
        }
    }


    LSharedPointer& operator=(const LSharedPointer<T>& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        (*mUsed)++;
    }

    LSharedPointer& operator=(LSharedPointer<T>&& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        _other.mData=nullptr;
        return *this;
    }

    T* getData()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    const T* getData()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    T& operator*()
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    const T& operator*()const
    {
        lAssert(mData==nullptr,"Data is null");
        return *mData;
    }

    T* operator-> ()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

private:
    T* mData;
    u32* mUsed;
};




template<typename T>
class LAPI LSharedPointer<T[]>
{
    LSharedPointer()
    {
        mUsed = new u32(1);
    }
public:
    LSharedPointer(const LSharedPointer<T>& _other)
    {
        mData = _other.mData;
        mUsed = _other.mUsed;
        mSize = _other.mSize;
        (*mUsed)++;
    }

    LSharedPointer(LSharedPointer<T>&& _other)
    {
        mData = _other.mData;
        mUsed = _other.mUsed;
        mSize = _other.mSize;
        _other.mData = nullptr;
    }

    virtual ~LSharedPointer()
    {
        destroy();
    }

    static LSharedPointer<T[]> create(u64 _size)
    {
        LSharedPointer<T[]> out;
        out.mSize = _size;

#undef new
#define new new

        out.mData =(T*) operator new[](sizeof(T)*_size);
        for(u64 i=0;i<_size;i++)
        {
            new (&out.mData[i]) T();
        }

#if LTARGET == LTARGET_DEBUG
        __lptrlogmanager.addArrayPtr({&out.mData[0],__LINE__,__FILE__,sizeof(T)*_size});
#endif

#undef new
#define new LIGHTNING_NEW

        return out;
    }

    template<typename... ObjectArgs>
    static LSharedPointer<T[]> create(u64 _size,ObjectArgs... args)
    {
        LSharedPointer<T[]> out;
        out.mSize = _size;

#undef new
#define new new

        out.mData =(T*) operator new[](sizeof(T)*_size);
        for(u64 i=0;i<_size;i++)
            new (&out.mData[i]) T(args...);


#if LTARGET == LTARGET_DEBUG
        __lptrlogmanager.addArrayPtr({&out.mData[0],__LINE__,__FILE__,sizeof(T)*_size});
#endif

#undef new
#define new LIGHTNING_NEW

        return out;
    }

    void destroy()
    {
        if(mData)
        {
            (*mUsed)--;
            if((*mUsed)==0)
            {
                delete mUsed;
                for(u64 i=mSize;i>0;i--)
                {
                    mData[i-1].~T();
                }
                void* _data = (void*) mData;
                operator delete[](_data);
                mData=nullptr;
                mSize=0;
            }
        }
    }

    LSharedPointer& operator=(const LSharedPointer<T>& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        mSize = _other.mSize;
        (*mUsed)++;
    }

    LSharedPointer& operator=(LSharedPointer<T>&& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        mSize = _other.mSize;
        _other.mData=nullptr;
        return *this;
    }

    T* getData()
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    const T* getData()const
    {
        lAssert(mData==nullptr,"Data is null");
        return mData;
    }

    u64 getSize()const
    {
        return mSize;
    }

    T* operator+(u32 _i)const
    {
        lAssert(mData==nullptr,"Data is null");
        lAssert(_i>=mSize,"index is bigger than size");
        T* o=mData+_i;
        return o;
    }

    T& operator[](const u32 _i)
    {
        lAssert(mData==nullptr,"Data is null");
        lAssert(_i>=mSize,"index is bigger than size");
        return mData[_i];
    }

    const T operator[](const u32 _i)const
    {
        lAssert(mData==nullptr,"Data is null");
        lAssert(_i>=mSize,"index is bigger than size");
        return mData[_i];
    }

private:
    T*      mData;
    u64     mSize;
    u32*    mUsed;
};


LNAMESPACE_END
#endif // LMEMORYMANAGER_H
