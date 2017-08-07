#ifndef LMEMORYMANAGER_H
#define LMEMORYMANAGER_H

#include "ldefines.h"
#include "llog.h"



LNAMESPACE_BEGIN

template<typename T>
class LAPI LUniquePointer
{
public:
    LUniquePointer(T* _in)
    {
        mData=_in;
    }
    LUniquePointer(const LUniquePointer<T>& )=delete;
    LUniquePointer(LUniquePointer<T>&& _other)
    {
        mData=_other.mData;
        _other.mData=nullptr;
    }

    virtual ~LUniquePointer()
    {
        if(mData)
        {
            if(__lptrlogmanager.isValidPointer(mData))
            {
                if(__lptrlogmanager.isArrayPointer(mData))
                    delete[] mData;
                else
                    delete mData;
            }
        }
        mData=nullptr;
    }

    LUniquePointer& operator=(const LUniquePointer<T>& )=delete;
    LUniquePointer& operator=(LUniquePointer<T>&& _other)
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

    T&              operator[](u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData[_i];
    }

    const T&        operator[](u32 _i)const
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
    T*      mData;
    bool    mIsArray;
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
        if(mData)
        {
            (*mUsed)--;
            if(*mUsed==0)
            {
                if(__lptrlogmanager.isValidPointer(mData))
                {
                    if(__lptrlogmanager.isArrayPointer(mData))
                        delete[] mData;
                    else
                        delete mData;
                }
                mData=nullptr;
                delete mUsed;
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

    T&              operator[](u32 _i)
    {
        lError(mData==nullptr,"Data is null",mData);
        return mData[_i];
    }

    const T&        operator[](u32 _i)const
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
