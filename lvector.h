#ifndef LVECTOR_H
#define LVECTOR_H

#include "llog.h"
#include "ldefines.h"

LNAMESPACE_BEGIN

template<typename T>
class LAPI LVector
{
public:
    typedef T           type;
    typedef T*          iterator;
    typedef const T*    const_iterator;
public:
    LVector();
    virtual ~LVector();

    //! Get Access to vector Parameter
    linline T&                      at(const u32 _i);
    linline const T&                at(const u32 _i)const;

    //! it's pointer to vector start for range based for
    linline iterator                begin();
    linline const_iterator          begin()const;

    //! clear vector
    linline void                    clear();

    //! it's pointer to vector end for range based for
    linline iterator                end();
    linline const_iterator          end()const;

    //! erase part of vector . from _from to _from+_count
    linline void                    erase(u32 _from,u32 _count=(u32)-1);

    //! resize this vector as needed
    linline void                    flush();

    // get index of _what in vector from _from . if there was nothing returns false
    template<typename T2>
    linline u32                     find(const T2& _what,u32 _from=0) const;

    // get index of _what in vector from _from . if there was nothing returns false . this starts searching from right
    template<typename T2>
    linline u32                     findFromRight(const T2& _what,u32 _from=(u32)-1) const;

    //! Get Vector Capacity
    linline u32                     getCapacity()const;

    //! Get Vector Data Directly
    linline const T*                getData()const;

    //! Get Size of vector
    linline u32                     getSize()const;

    //! insert a new item at middle of vector
    linline void                    insert(const u32 _i,const T& _newitem);
    linline void                    insert(const u32 _i,T&& _newitem);


    //! Append a new Item at end of vector
    linline void                    pushBack(const T& _newitem);
    linline void                    pushBack(T&& _newitem);

    //! delete a item from end and returns it's value
    linline T                       popBack();

    //! Append a new Item at begin of vector
    linline void                    pushFront(const T& _newitem);
    linline void                    pushFront(T&& _newitem);

    //! delete a item from begin and returns it's value
    linline T                       popFront();

    //! remove an element of vector in _index
    linline void                    remove(u32 _index);

    //! change capacity of Vector
    linline void                    resize(const u32 _newsize);

    //! swap this vector with another
    linline void                    swap(LVector<T>& _other);

    //! swap two items of this vector
    linline void                    swap(const u32 _i1,const u32 _i2);

    //! Get Access to vector Parameter
    linline T&                      operator[](const u32 _i);
    linline const T&                operator[](const u32 _i)const;

    //! Just like pushBack
    linline LVector<T>&             operator<<(const T& _newitem);
    linline LVector<T>&             operator<<(T&& _newitem);

    static const u32                nothing;
protected:
    template<typename _T,typename _T2,const bool _have_operator>
    struct _LVector_Search{ linline static u32 __find(_T* _data,u32 _size,const _T2& _what); linline static u32 __rfind(_T* _data,u32 _size,const _T2& _what); };
    template<typename _T,typename _T2>
    struct _LVector_Search<_T,_T2,false>{ linline static u32 __find(_T* _data,u32 _size,const _T2& _what); linline static u32 __rfind(_T* _data,u32 _size,const _T2& _what); };

protected:
    T*  mData;
    u32 mSize;
    u32 mCapacity;
};
template<typename T>
const u32 LVector<T>::nothing=(u32)-1;

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
T &LVector<T>::at(const u32 _i)
{
    lError(_i>=mSize,"LVector<T>::at(u32 _i) : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
const T &LVector<T>::at(const u32 _i) const
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
void LVector<T>::erase(u32 _from, u32 _count)
{
    if(_count==(u32)-1)
        _count=mSize-_from;
    lError(_from>=mSize||_from+_count>mSize || _count==0,"void LVector<T>::erase(u32 _from, u32 _count): one of paramets is not acceptable");
    for(u32 i=_from;i<mSize-_count;i++)
        mData[i]=mData[i+_count];
    mSize-=_count;
}

template<typename T>
void LVector<T>::flush()
{
    resize(mSize);
}

template<typename T> template<typename T2>
u32 LVector<T>::find(const T2 &_what, u32 _from) const
{
    lError(_from>=mSize,"u32 LVector<T>::find(const T2 &_what, u32 _from) const: _from is not acceptable",nothing);
    return _from+_LVector_Search<T,T2,LHasOperator::Equal<T,T2>::value>::__find(&mData[_from],mSize-_from,_what);
}

template<typename T> template<typename T2>
u32 LVector<T>::findFromRight(const T2 &_what, u32 _from) const
{
    lError(_from>=mSize,"u32 LVector<T>::find(const T2 &_what, u32 _from) const: _from is not acceptable",nothing);
    if(_from==(u32)-1)
        _from=mSize-1;
    return _LVector_Search<T,T2,LHasOperator::Equal<T,T2>::value>::__rfind(mData,_from,_what);
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
void LVector<T>::insert(const u32 _i,T &&_newitem)
{
    lError(_i>=mSize+1,"void LVector<T>::insert(const u32 _i,T &&_newitem): _i is not acceptable");
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    for(u32 i=_i;i<mSize;i++)
        mData[i+1]=mData[i];
    mData[_i]=_newitem;
    mSize++;
}

template<typename T>
void LVector<T>::insert(const u32 _i,const T &_newitem)
{
    lError(_i>=mSize+1,"void LVector<T>::insert(u32 _i,const T &_newitem): _i is not acceptable");
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    for(u32 i=_i;i<mSize;i++)
        mData[i+1]=mData[i];
    mData[_i]=_newitem;
    mSize++;
}

template<typename T>
void LVector<T>::pushBack(T &&_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    mData[mSize]=lMove(_newitem);
    mSize++;
}

template<typename T>
void LVector<T>::pushBack(const T &_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    mData[mSize]=_newitem;
    mSize++;
}

template<typename T>
T LVector<T>::popBack()
{
    lError(mSize==0,"T LVector<T>::popBack(): vector size is not enough to pop",T());
    mSize--;
    return mData[mSize];
}

template<typename T>
void LVector<T>::pushFront(T &&_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    for(u32 i=mSize;i>0;i--)
        mData[i]=lMove(mData[i-1]);
    mData[0]=lMove(_newitem);
    mSize++;
}

template<typename T>
void LVector<T>::pushFront(const T &_newitem)
{
    if(mSize>=mCapacity)
        resize(mCapacity+ 16 );
    for(u32 i=mSize;i>0;i--)
        mData[i]=lMove(mData[i-1]);
    mData[0]=_newitem;
    mSize++;
}

template<typename T>
T LVector<T>::popFront()
{
    lError(mSize==0,"T LVector<T>::popFront(): vector size is not enough to pop",T());
    T o=mData[0];
    for(u32 i=0;i<mSize-1;i++)
        mData[i]=mData[i+1];
    mSize--;
    return o;
}

template<typename T>
void LVector<T>::remove(u32 _index)
{
    lError(_index>=mSize,"void LVector<T>::remove(u32 _index) : _index is not acceptable");
    erase(_index,1);
}

template<typename T>
void LVector<T>::resize(const u32 _newsize)
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
void LVector<T>::swap(const u32 _i1,const u32 _i2)
{
    lError(_i1>=mSize||_i2>=mSize,"void LVector<T>::swap(u32 _i1, u32 _i2) : _i1 or _i2 is not accpetable");
    lSwap(mData[_i1],mData[_i2]);
}

template<typename T>
T &LVector<T>::operator[](const u32 _i)
{
    lError(_i>=mSize,"T &LVector<T>::operator[](u32 _i) : _i is bigger not accpetable",mData[0]);
    return mData[_i];
}

template<typename T>
const T &LVector<T>::operator[](const u32 _i) const
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

template<typename T> template<typename _T,typename _T2,bool _have_operator>
u32 LVector<T>::_LVector_Search<_T,_T2,_have_operator>::__find(_T *_data, u32 _size, const _T2 &_what)
{
    for(u32 i=0;i<_size;i++)
        if(_data[i]==_what)
            return i;
    return nothing;
}

template<typename T> template<typename _T,typename _T2>
u32 LVector<T>::_LVector_Search<_T,_T2,false>::__find(_T *_data, u32 _size, const _T2 &_what)
{
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LVector:searching for this type is not available typeid= \"")+lGetTypeName<_T>()+" and "+lGetTypeName<_T2>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}

template<typename T> template<typename _T,typename _T2,bool _have_operator>
u32 LVector<T>::_LVector_Search<_T,_T2,_have_operator>::__rfind(_T *_data, u32 _size, const _T2 &_what)
{
    for(u32 i=_size;i>=0;i--)
        if(_data[i]==_what)
            return i;
    return nothing;
}

template<typename T> template<typename _T,typename _T2>
u32 LVector<T>::_LVector_Search<_T,_T2,false>::__rfind(_T *_data, u32 _size, const _T2 &_what)
{
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LVector:searching for this type is not available typeid= \"")+lGetTypeName<_T>()+" and "+lGetTypeName<_T2>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}

LNAMESPACE_END

#endif // LVECTOR_H
