#ifndef LLIST_H
#define LLIST_H

#include "ldefines.h"
#include "llog.h"

LNAMESPACE_BEGIN

//! Class to hold linked list
template<typename T>
class LList
{
public:
    struct Iterator
    {
        friend class LList;
    private:
        Iterator();
    private:
        T mVal;
        Iterator* mNext;
    };

public:
    LList();

    //! Get Size of List
    linline u32                     getSize()const;

    //! Append a new Item at end of list
    linline void                    pushBack(const T& _newitem);
    linline void                    pushBack(T&& _newitem);

    //! Append a new Item at begin of list
    linline void                    pushFront(const T& _newitem);
    linline void                    pushFront(T&& _newitem);

    //! swap this list with another
    linline void                    swap(LList<T>& _other);

    //! swap two items of this list
    linline void                    swap(const u32 _i1,const u32 _i2);

    //! Get Access to list Parameter
    linline T&                      operator[](const u32 _i);
    linline const T&                operator[](const u32 _i)const;

    static const u32                nothing;
private:
    Iterator* mFirst;
    Iterator* mLast;
    u32       mSize;
};

template<typename T>
const u32 LList<T>::nothing=(u32)-1;

template<typename T>
LList<T>::Iterator::Iterator()
{
    mNext=nullptr;
}


template<typename T>
LList<T>::LList()
{
    mFirst=nullptr;
    mLast=nullptr;
    mSize=0;
}

template<typename T>
u32 LList<T>::getSize() const
{
    return mSize;
}

template<typename T>
void LList<T>::pushBack(const T &_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new Iterator;
        mFirst->mVal=_newitem;
    }
    else
    {
        mLast->mNext=new Iterator;
        mLast->mNext->mVal=_newitem;
        mLast=mLast->mNext;
    }
}

template<typename T>
void LList<T>::pushBack(T &&_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new Iterator;
        mFirst->mVal=_newitem;
    }
    else
    {
        mLast->mNext=new Iterator;
        mLast->mNext->mVal=_newitem;
        mLast=mLast->mNext;
    }
}

template<typename T>
void LList<T>::pushFront(const T &_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new Iterator;
        mFirst->mVal=_newitem;
    }
    else
    {
        Iterator* fnext=mFirst;
        mFirst=new Iterator;
        mFirst->mVal=_newitem;
        mFirst->mNext=fnext;
    }
}

template<typename T>
void LList<T>::pushFront(T &&_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new Iterator;
        mFirst->mVal=_newitem;
    }
    else
    {
        Iterator* fnext=mFirst;
        mFirst=new Iterator;
        mFirst->mVal=_newitem;
        mFirst->mNext=fnext;
    }
}

template<typename T>
void LList<T>::swap(LList<T> &_other)
{
    lSwap(mSize,_other.mSize);
    lSwap(mFirst,_other.mFirst);
    lSwap(mLast,_other.mLast);
}

template<typename T>
void LList<T>::swap(const u32 _i1, const u32 _i2)
{
    lError(_i1>=mSize||_i2>=mSize,"void LList<T>::swap(const u32 _i1, const u32 _i2) : _i1 or _i2 is not accpetable");
    lSwap((*this)[_i1],(*this)[_i2]);
}

template<typename T>
T &LList<T>::operator[](const u32 _i)
{
    static T d;
    lError(getSize()<=_i,"T &LList<T>::operator[](const u32 _i) , _i is not acceptable",d);
    Iterator* f=mFirst;
    for(u32 i=0;i<_i;i++)
    {
        f=f->mNext;
    }
    return f->mVal;
}

template<typename T>
const T &LList<T>::operator[](const u32 _i) const
{
    static T d;
    lError(getSize()<=_i,"T &LList<T>::operator[](const u32 _i) , _i is not acceptable",d);
    Iterator* f=mFirst;
    for(u32 i=0;i<_i;i++)
    {
        f=f->mNext;
    }
    return f->mVal;
}

LNAMESPACE_END

#endif // LLIST_H
