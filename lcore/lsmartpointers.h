#ifndef LMEMORYMANAGER_H
#define LMEMORYMANAGER_H

#include "ldefines.h"
#include "llog.h"
#include "lmemorylog.h"



LNAMESPACE_BEGIN

template<typename T,bool _is_native = LIsNativeType<T>::value || LIsEnum<T>::value>
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
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* getData()const
    {
        lError(mData==nullptr,"Data is null",mData);
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

    T* operator+(u32 _i)const
    {
        lError(mData==nullptr,"Data is null",mData);
        T* o=mData+_i;
        return o;
    }

    T& operator*()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    const T& operator*()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    T& operator[](const u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData[0]);
        return mData[_i];
    }

    T* operator-> ()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* operator-> ()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator T()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator T*()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator const T()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator const T*()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

private:
    T*      mData;
};





template<typename T>
class LAPI LUniquePointer<T[],false>
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
        lMemoryLogStartIgnore();
        LUniquePointer<T[]> out;
        out.mSize = _size;
        out.mData = new T[_size];
        lMemoryLogEndIgnore();
        return out;
    }


    void destroy()
    {
        lMemoryLogStartIgnore();
        if(mData)
        {
            delete[] mData;
            mData=nullptr;
            mSize=0;
        }
        lMemoryLogEndIgnore();
    }

    T* getData()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* getData()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }


    LUniquePointer& operator=(const LUniquePointer<T>& )=delete;
    LUniquePointer& operator=(LUniquePointer<T>&& _other)
    {
        destroy();
        mData=_other.mData;
        mSize=_other.mSize;
        _other.mData=nullptr;
        _other.mSize=0;
        return *this;
    }

    T* operator+(u32 _i)const
    {
        lError(mData==nullptr,"Data is null",mData);
        T* o=mData+_i;
        return o;
    }

    T& operator*()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    const T& operator*()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    T& operator[](const u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData[0]);
        return mData[_i];
    }

    T* operator-> ()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* operator-> ()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator T()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator T*()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator const T()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator const T*()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

private:
    T*      mData;
    u64     mSize;
};



template<typename T>
class LAPI LUniquePointer<T[],true>
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
        //lMemoryLogStartIgnore();
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

        //lMemoryLogEndIgnore();
        return out;
    }

    template<typename... ObjectArgs>
    static LUniquePointer<T[]> create(u64 _size,ObjectArgs... args)
    {
        //lMemoryLogStartIgnore();
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

        //lMemoryLogEndIgnore();
        return out;
    }

    void destroy()
    {
        //lMemoryLogStartIgnore();
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
        //lMemoryLogEndIgnore();
    }

    T* getData()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* getData()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }


    LUniquePointer& operator=(const LUniquePointer<T>& )=delete;
    LUniquePointer& operator=(LUniquePointer<T>&& _other)
    {
        destroy();
        mData=_other.mData;
        mSize=_other.mSize;
        _other.mData=nullptr;
        _other.mSize=0;
        return *this;
    }

    T* operator+(u32 _i)const
    {
        lError(mData==nullptr,"Data is null",mData);
        T* o=mData+_i;
        return o;
    }

    T& operator*()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    const T& operator*()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    T& operator[](const u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData[0]);
        return mData[_i];
    }

    T* operator-> ()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T* operator-> ()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator T()
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator T*()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    operator const T()const
    {
        lError(mData==nullptr,"Data is null",*mData);
        return *mData;
    }

    operator const T*()const
    {
        lError(mData==nullptr,"Data is null",mData);
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
public:
    LSharedPointer(T* _in)
    {
        mData=_in;
        mUsed=new u32(1);
    }
    LSharedPointer(const LSharedPointer<T>& _other)
    {
        mData=_other.mData;
        mUsed=_other.mUsed;
        (*mUsed)++;
    }

    LSharedPointer(LSharedPointer<T>&& _other)
    {
        mData=_other.mData;
        _other.mData=nullptr;
    }

    virtual ~LSharedPointer()
    {

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
        _other.mData=nullptr;
        return *this;
    }

    T*              getData()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    const T*        getData()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

    T*              operator+(u32 _i)const
    {
        lError(mData==nullptr,"Data is null",mData);
        T* o=mData+_i;
        return o;
    }

    T&              operator*()
    {
        lError(mData==nullptr,"Data is null",mData);
        return *mData;
    }

    const T&        operator*()const
    {
        lError(mData==nullptr,"Data is null",mData);
        return *mData;
    }

    T&              operator[](const u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData[_i];
    }

    const T         operator[](const u32 _i)const
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData[_i];
    }

    T*              operator-> ()
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData;
    }

private:
    T* mData;
    u32* mUsed;
};

LNAMESPACE_END



#endif // LMEMORYMANAGER_H
