#ifndef LVECTOR_H
#define LVECTOR_H

#include "llog.h"
#include "ldefines.h"

LNAMESPACE_BEGIN

template<typename T>
class LVector
{
public:
    typedef T           type;
    typedef T*          iterator;
    typedef const T*    const_iterator;
public:
    LVector();
    virtual ~LVector();

    //! Get Access to vector Parameter
    linline T&          at(u32 _i);
    linline const T&    at(u32 _i)const;

    //! it's pointer to vector start for range based for
    iterator                        begin();
    const_iterator                  begin()const;

    //! clear vector
    void                            clear();

    //! it's pointer to vector end for range based for
    iterator                        end();
    const_iterator                  end()const;

    //! resize this vector as needed
    void                            flush();

    //! Get Vector Capacity
    linline u32                     getCapacity()const;

    //! Get Vector Data Directly
    linline const T*                getData()const;

    //! Get Size of vector
    linline u32                     getSize()const;

    //! Append a new Item at end of vector
    linline void                    pushBack(const T& _newitem);
    linline void                    pushBack(T&& _newitem);

    //! change capacity of Vector
    linline void                    resize(u32 _newsize);

    //! swap this vector with another
    linline void                    swap(LVector<T>& _other);

    //! Get Access to vector Parameter
    linline T&                      operator[](u32 _i);
    linline const T&                operator[](u32 _i)const;

    linline LVector<T>&             operator<<(const T& _newitem);
    linline LVector<T>&             operator<<(T&& _newitem);
protected:
    T*  mData;
    u32 mSize;
    u32 mCapacity;
};


template<typename T>
LVector<T>::LVector()
{
    mData=0;
    mSize=0;
    mCapacity=0;
}

template<typename T>
LVector<T>::~LVector()
{
    if(mData)
        delete[] mData;
}

template<typename T>
T &LVector<T>::at(u32 _i)
{
    lError(_i>=mSize,"LVector<T>::at(u32 _i) : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
const T &LVector<T>::at(u32 _i) const
{
    lError(_i>=mSize,"LVector<T>::at(u32 _i)const : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
typename LVector<T>::iterator LVector<T>::begin()
{
    return mData;
}

template<typename T>
typename LVector<T>::const_iterator LVector<T>::begin() const
{
    return mData;
}

template<typename T>
void LVector<T>::clear()
{
    resize(0);
}

template<typename T>
typename LVector<T>::iterator LVector<T>::end()
{
    return &mData[mSize];
}

template<typename T>
typename LVector<T>::const_iterator LVector<T>::end() const
{
    return &mData[mSize];
}

template<typename T>
void LVector<T>::flush()
{
    resize(mSize);
}

template<typename T>
u32 LVector<T>::getCapacity() const
{
    return mCapacity;
}

template<typename T>
const T* LVector<T>::getData() const
{
    return mData;
}

template<typename T>
u32 LVector<T>::getSize() const
{
    return mSize;
}

template<typename T>
void LVector<T>::pushBack(T &&_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 8 );
    mData[mSize]=lMove(_newitem);
    mSize++;
}

template<typename T>
void LVector<T>::pushBack(const T &_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 8 );
    mData[mSize]=_newitem;
    mSize++;
}

template<typename T>
void LVector<T>::resize(u32 _newsize)
{
    // Exactly is same size
    if(_newsize==mCapacity)
        return;
    if(_newsize==0)
    {
        if(mData)
        {
            delete[] mData;
            mData=0;
            mSize=0;
            mCapacity=0;
        }
        return;
    }
    T* _pd=mData;
    mCapacity=_newsize;
    if(mSize>_newsize)
        mSize=_newsize;
    mData = new T[_newsize];
    // if there was a previos data copy it on new space
    if(_pd)
    {
        for(u32 i=0;i<mSize;i++)
            mData[i]=lMove(_pd[i]);
        delete[] _pd;
    }
}

template<typename T>
void LVector<T>::swap(LVector<T> &_other)
{
    lSwap(mData,_other.mData);
    lSwap(mSize,_other.mSize);
    lSwap(mCapacity,_other.mCapacity);
}

template<typename T>
T &LVector<T>::operator[](u32 _i)
{
    lError(_i>=mSize,"T &LVector<T>::operator[](u32 _i) : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
const T &LVector<T>::operator[](u32 _i) const
{
    lError(_i>=mSize,"const T &LVector<T>::operator[](u32 _i)const : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
LVector<T> &LVector<T>::operator<<(const T &_newitem)
{
    pushBack(_newitem);
    return *this;
}

template<typename T>
LVector<T> &LVector<T>::operator<<(T &&_newitem)
{
    pushBack(_newitem);
    return *this;
}

LNAMESPACE_END

#endif // LVECTOR_H
