#ifndef LLIST_H
#define LLIST_H

#include <initializer_list>
#include "ldefines.h"
#include "llog.h"

LNAMESPACE_BEGIN

//! Class to hold linked list
template<typename T>
class LAPI LList
{
public:
    struct ListNode
    {
        friend class LList;
        friend class Iterator;
        friend class ConstIterator;
    private:
        linline ListNode();
    private:
        T mVal;
        ListNode* mNext;
        ListNode* mPrev;
    };

    class Iterator
    {
        friend class LList;
    public:
        linline Iterator();
        linline Iterator(typename LList<T>::ListNode* _n);

        linline Iterator    operator +(i32 _i)const;
        linline Iterator    operator -(i32 _i)const;
        linline T&          operator *();
        linline T&          operator [](i32 _i);
        linline T*          operator->();
        linline operator    bool()const;
        linline bool        operator !()const;
        linline Iterator&   operator++();
        linline Iterator&   operator--();
        linline Iterator    operator++(i32 _i);
        linline Iterator    operator--(i32 _i);
        linline bool        operator==(const Iterator& _other)const;
        linline bool        operator!=(const Iterator& _other)const;
    private:
        ListNode* mNode;
    };

    class ConstIterator
    {
        friend class LList;
    public:
        linline ConstIterator();
        linline ConstIterator(typename LList<T>::ListNode* _n);

        linline ConstIterator    operator +(i32 _i)const;
        linline ConstIterator    operator -(i32 _i)const;
        linline const T&         operator *()const;
        linline const T&         operator [](i32 _i)const;
        linline const T*         operator->()const;
        linline operator         bool()const;
        linline bool             operator !()const;
        linline ConstIterator&   operator++();
        linline ConstIterator&   operator--();
        linline ConstIterator    operator++(i32 _i);
        linline ConstIterator    operator--(i32 _i);
        linline bool             operator==(const ConstIterator& _other)const;
        linline bool             operator!=(const ConstIterator& _other)const;
    private:
        ListNode* mNode;
    };

public:
    linline LList();
    linline LList(const std::initializer_list<T> _vals);
    linline LList(const LList<T>& _other);
    linline LList(LList<T>&& _other);
    virtual ~LList();

    //! Get Access to list Parameter
    linline T&                      at(const u32 _i);
    linline const T&                at(const u32 _i)const;

    //! iterator for list from start
    linline Iterator                begin();
    linline ConstIterator           begin()const;

    //! Clear all elements of list
    linline void                    clear();

    //! iterator for list from end
    linline Iterator                end();
    linline ConstIterator           end()const;

    //! erase part of list . from _from to _from+_count
    linline void                    erase(u32 _from,u32 _count=(u32)-1);

    // get index of _what in list from _from . if there was nothing returns LList::nothing
    template<typename T2>
    linline u32                     find(const T2& _what,u32 _from=0) const;

    // get index of _what in list from _from . if there was nothing returns LList::nothing . this starts searching from right
    template<typename T2>
    linline u32                     findFromRight(const T2& _what,u32 _from=(u32)-1) const;

    //! Get Size of List
    linline u32                     getSize()const;

    //! insert a new item at middle of list
    linline void                    insert(const u32 _i,const T& _newitem);
    linline void                    insert(const u32 _i,T&& _newitem);

    //! insert new items at middle of list
    linline void                    insert(const u32 _i,const std::initializer_list<T> _items);
    linline void                    insert(const u32 _i,const LList<T>& _other);

    //! Append a new Item at end of list
    linline void                    pushBack(const T& _newitem);
    linline void                    pushBack(T&& _newitem);

    //! Append new items at end of list
    linline void                    pushBack(const std::initializer_list<T> _items);
    linline void                    pushBack(const LList<T>& _other);

    //! delete a item from end and returns it's value
    linline T                       popBack();

    //! Append a new Item at begin of list
    linline void                    pushFront(const T& _newitem);
    linline void                    pushFront(T&& _newitem);

    //! Append new items at begin of list
    linline void                    pushFront(const std::initializer_list<T> _items);
    linline void                    pushFront(const LList<T>& _other);

    //! delete a item from begin and returns it's value
    linline T                       popFront();

    //! sort this list if operator > and operator < is availbe for type T
    linline void                    sort(LSortType _sorttype=LSortTypeAscending);

    //! remove an element of list in _index
    linline void                    remove(u32 _index);

    //! change size of list and new spaces will fill with default value of T
    linline void                    resize(const u32 _newsize);

    //! reverse this list elements
    linline void                    reverse();

    //! swap this list with another
    linline void                    swap(LList<T>& _other);

    //! swap two items of this list
    linline void                    swap(const u32 _i1,const u32 _i2);

    //! Get Access to list Parameter
    linline T&                      operator[](const u32 _i);
    linline const T&                operator[](const u32 _i)const;

    //! Just like pushBack
    linline LList<T>&               operator<<(const T& _newitem);
    linline LList<T>&               operator<<(T&& _newitem);

    //! Copy Assign
    linline LList<T>&               operator=(const LList<T>& _other);

    //! Move Assign
    linline LList<T>&               operator=(LList<T>&& _other);

    //! Append a new Item at end of vector
    linline LList<T>&               operator+=(const T& _newitem);
    linline LList<T>&               operator+=(T&& _newitem);
    //! Append new items at end of vector
    linline LList<T>&               operator+=(const std::initializer_list<T> _items);
    linline LList<T>&               operator+=(const LList<T>& _other);

    //! Append new items at end of vector
    linline LList<T>                operator+(const std::initializer_list<T> _items);
    linline LList<T>                operator+(const LList<T>& _other);

    static const u32                nothing;
protected:
    template<typename _T,typename _T2,const bool _have_operator>
    struct _LList_Search{ linline static u32 __find(_T _data,u32 _size,const _T2& _what,u32 _from); linline static u32 __rfind(_T _data,u32 _size,const _T2& _what,u32 _from); };
    template<typename _T,typename _T2>
    struct _LList_Search<_T,_T2,false>{ linline static u32 __find(_T _data,u32 _size,const _T2& _what,u32 _from); linline static u32 __rfind(_T _data,u32 _size,const _T2& _what,u32 _from); };

    template<typename _T,const bool _have_operator>
    struct _LList_Sort{ linline static void _sort(_T _data,u32 _size,LSortType _type);};
    template<typename _T>
    struct _LList_Sort<_T,false>{ linline static void _sort(_T _data,u32 _size,LSortType _type);};
protected:
    ListNode* mFirst;
    ListNode* mLast;
    u32       mSize;
};

template<typename T>
const u32 LList<T>::nothing=(u32)-1;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
LList<T>::ListNode::ListNode()
{
    mNext=nullptr;
    mPrev=nullptr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LList<T>::Iterator::Iterator()
{
    mNode=nullptr;
}

template<typename T>
LList<T>::Iterator::Iterator(typename LList<T>::ListNode *_n)
{
    mNode=_n;
}


template<typename T>
typename LList<T>::Iterator LList<T>::Iterator::operator+(i32 _i)const
{
    LList<T>::Iterator o;
    o.mNode=mNode;
    if(_i>=0)
    {
        for(i32 i=0;i<_i;i++)
        {
            if(o.mNode!=nullptr)
                o.mNode=o.mNode->mNext;
            else
            {
                o.mNode=mNode;
                lError(1,LSTR("LList<T>::Iterator LList<T>::Iterator::operator+(i32 _i): _i is not acceptable or this Iterator is nothing"),o);
            }
        }
    }
    else
    {
        for(i32 i=0;i>_i;i--)
        {
            if(o.mNode!=nullptr)
                o.mNode=o.mNode->mPrev;
            else
            {
                o.mNode=mNode;
                lError(1,LSTR("LList<T>::Iterator LList<T>::Iterator::operator+(i32 _i): _i is not acceptable or this Iterator is nothing"),o);
            }
        }
    }
    return o;
}

template<typename T>
typename LList<T>::Iterator LList<T>::Iterator::operator-(i32 _i)const
{
    return (*this)+(-_i);
}

template<typename T>
T& LList<T>::Iterator::operator*()
{
    static T d;
    lError(mNode==nullptr,"LList<T>::Iterator LList<T>::Iterator::operator*(), iterator is nothing",d);
    return mNode->mVal;
}

template<typename T>
T& LList<T>::Iterator::operator[](i32 _i)
{
    static T d;
    Iterator ot;
    if(mNode!=nullptr)
        ot=(*this)+_i;
    lError(ot.mNode==nullptr,"T& LList<T>::Iterator::operator[](i32 _i),_is is not acceptable or iterator is nothing",d);
    return ot.mNode->mVal;
}

template<typename T>
T* LList<T>::Iterator::operator->()
{
    static T d;
    lError(mNode==nullptr,"T* LList<T>::Iterator::operator->(): iterator is nothing",(&d));
    return &(mNode->mVal);
}

template<typename T>
bool LList<T>::Iterator::operator!()const
{
    return (mNode==nullptr);
}

template<typename T>
LList<T>::Iterator::operator bool()const
{
    return (mNode!=nullptr);
}

template<typename T>
typename LList<T>::Iterator& LList<T>::Iterator::operator++()
{
    (*this)=(*this)+1;
    return (*this);
}

template<typename T>
typename LList<T>::Iterator& LList<T>::Iterator::operator--()
{
    (*this)=(*this)+(-1);
    return (*this);
}

template<typename T>
typename LList<T>::Iterator LList<T>::Iterator::operator++(i32 _i)
{
    LUNUSED(_i);
    Iterator o=(*this);
    (*this)=(*this)+1;
    return (o);
}

template<typename T>
typename LList<T>::Iterator LList<T>::Iterator::operator--(i32 _i)
{
    LUNUSED(_i);
    Iterator o=(*this);
    (*this)=(*this)+(-1);
    return (o);
}

template<typename T>
bool LList<T>::Iterator::operator==(const typename LList<T>::Iterator& _other)const
{
    return (mNode==_other.mNode);
}

template<typename T>
bool LList<T>::Iterator::operator!=(const typename LList<T>::Iterator& _other)const
{
    return (mNode!=_other.mNode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LList<T>::ConstIterator::ConstIterator()
{
    mNode=nullptr;
}

template<typename T>
LList<T>::ConstIterator::ConstIterator(typename LList<T>::ListNode *_n)
{
    mNode=_n;
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::ConstIterator::operator+(i32 _i)const
{
    LList<T>::ConstIterator o;
    o.mNode=mNode;
    if(_i>=0)
    {
        for(i32 i=0;i<_i;i++)
        {
            if(o.mNode!=nullptr)
                o.mNode=o.mNode->mNext;
            else
            {
                o.mNode=mNode;
                lError(1,LSTR("LList<T>::Iterator LList<T>::Iterator::operator+(i32 _i): _i is not acceptable or this Iterator is nothing"),o);
            }
        }
    }
    else
    {
        for(i32 i=0;i>_i;i--)
        {
            if(o.mNode!=nullptr)
                o.mNode=o.mNode->mPrev;
            else
            {
                o.mNode=mNode;
                lError(1,LSTR("LList<T>::Iterator LList<T>::Iterator::operator+(i32 _i): _i is not acceptable or this Iterator is nothing"),o);
            }
        }
    }
    return o;
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::ConstIterator::operator-(i32 _i)const
{
    return (*this)+(-_i);
}

template<typename T>
const T& LList<T>::ConstIterator::operator*()const
{
    static T d;
    lError(mNode==nullptr,"LList<T>::Iterator LList<T>::Iterator::operator*(), iterator is nothing",d);
    return mNode->mVal;
}

template<typename T>
const T& LList<T>::ConstIterator::operator[](i32 _i)const
{
    static T d;
    ConstIterator ot;
    if(mNode!=nullptr)
        ot=(*this)+_i;
    lError(ot.mNode==nullptr,"T& LList<T>::Iterator::operator[](i32 _i),_is is not acceptable or iterator is nothing",d);
    return ot.mNode->mVal;
}

template<typename T>
const T* LList<T>::ConstIterator::operator->()const
{
    static T d;
    lError(mNode==nullptr,"T* LList<T>::Iterator::operator->(): iterator is nothing",(&d));
    return &(mNode->mVal);
}

template<typename T>
bool LList<T>::ConstIterator::operator!()const
{
    return (mNode==nullptr);
}

template<typename T>
LList<T>::ConstIterator::operator bool()const
{
    return (mNode!=nullptr);
}

template<typename T>
typename LList<T>::ConstIterator& LList<T>::ConstIterator::operator++()
{
    (*this)=(*this)+1;
    return (*this);
}

template<typename T>
typename LList<T>::ConstIterator& LList<T>::ConstIterator::operator--()
{
    (*this)=(*this)+(-1);
    return (*this);
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::ConstIterator::operator++(i32 _i)
{
    LUNUSED(_i);
    Iterator o=(*this);
    (*this)=(*this)+1;
    return (o);
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::ConstIterator::operator--(i32 _i)
{
    LUNUSED(_i);
    Iterator o=(*this);
    (*this)=(*this)+(-1);
    return (o);
}

template<typename T>
bool LList<T>::ConstIterator::operator==(const typename LList<T>::ConstIterator& _other)const
{
    return (mNode==_other.mNode);
}

template<typename T>
bool LList<T>::ConstIterator::operator!=(const typename LList<T>::ConstIterator& _other)const
{
    return (mNode!=_other.mNode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
LList<T>::LList()
{
    mFirst=nullptr;
    mLast=nullptr;
    mSize=0;
}

template<typename T>
LList<T>::LList(const std::initializer_list<T> _vals)
{
    mFirst=nullptr;
    mLast=nullptr;
    mSize=0;
    resize(_vals.size());
    mSize=_vals.size();
    for(u32 i=0;i<mSize;i++)
        (*this)[i]=_vals.begin()[i];
}

template<typename T>
LList<T>::LList(const LList<T> &_other)
{
    mSize=0;
    mFirst=nullptr;
    mLast=nullptr;
    *this=_other;
}

template<typename T>
LList<T>::LList(LList<T> &&_other)
{
    mSize=0;
    mFirst=nullptr;
    mLast=nullptr;
    *this=lMove(_other);
}

template<typename T>
LList<T>::~LList()
{
    clear();
}

template<typename T>
T &LList<T>::at(const u32 _i)
{
    static T d;
    lError(getSize()<=_i,"T &LList<T>::operator[](const u32 _i) , _i is not acceptable",d);
    ListNode* f=mFirst;
    for(u32 i=0;i<_i;i++)
    {
        f=f->mNext;
    }
    return f->mVal;
}

template<typename T>
const T &LList<T>::at(const u32 _i) const
{
    static T d;
    lError(getSize()<=_i,"T &LList<T>::operator[](const u32 _i) , _i is not acceptable",d);
    ListNode* f=mFirst;
    for(u32 i=0;i<_i;i++)
    {
        f=f->mNext;
    }
    return f->mVal;
}

template<typename T>
typename LList<T>::Iterator LList<T>::begin()
{
    Iterator o;
    o.mNode=mFirst;
    return o;
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::begin()const
{
    ConstIterator o;
    o.mNode=mFirst;
    return o;
}

template<typename T>
void LList<T>::clear()
{
    ListNode* ttd=mFirst;
    ListNode* ttn;
    while (ttd!=nullptr)
    {
        ttn=ttd->mNext;
        delete ttd;
        ttd=ttn;
    }
    mSize=0;
    mLast=nullptr;
    mFirst=nullptr;
}

template<typename T>
typename LList<T>::Iterator LList<T>::end()
{
    Iterator o;
    return o;
}

template<typename T>
typename LList<T>::ConstIterator LList<T>::end()const
{
    ConstIterator o;
    return o;
}

template<typename T>
void LList<T>::erase(u32 _from, u32 _count)
{
    if(_count==(u32)-1)
        _count=mSize-_from;
    lError(_from>=mSize||_from+_count>mSize || _count==0,"void LList<T>::erase(u32 _from, u32 _count): one of paramets is not acceptable");
    ListNode* _b=mFirst;
    ListNode* _e;
    ListNode* _t;
    for(u32 i=0;i<_from;i++)
        _b=_b->mNext;
    _e=_b;
    for(u32 i=1;i<_count;i++)
        _e=_e->mNext;
    if(_from==0)
        mFirst=_e->mNext;
    if(_from+_count>=mSize)
        mLast=_b->mPrev;
    if(_b->mPrev)
        _b->mPrev->mNext=_e->mNext;
    if(_e&&_e->mNext)
    {
        _e->mNext->mPrev=_b->mPrev;
        _e->mNext=nullptr;
    }
    _t=_b;
    while (_t!=nullptr)
    {
        _b=_t->mNext;
        delete _t;
        _t=_b;
    }

    mSize-=_count;
}


template<typename T> template<typename T2>
u32 LList<T>::find(const T2 &_what, u32 _from) const
{
    if(mSize==0)
        return nothing;
    lError(_from>=mSize,"u32 LList<T>::find(const T2 &_what, u32 _from) const: _from is not acceptable",nothing);
    return _LList_Search<decltype(*this),T2,LHasOperator::Equal<T,T2>::value>::__find((*this),mSize,_what,_from);
}

template<typename T> template<typename T2>
u32 LList<T>::findFromRight(const T2 &_what, u32 _from) const
{
    if(mSize==0)
        return nothing;
    lError(_from>=mSize,"u32 LList<T>::find(const T2 &_what, u32 _from) const: _from is not acceptable",nothing);
    if(_from==(u32)-1)
        _from=mSize-1;
    return _LList_Search<decltype(*this),T2,LHasOperator::Equal<T,T2>::value>::__rfind((*this),mSize,_what,_from);
}

template<typename T>
u32 LList<T>::getSize() const
{
    return mSize;
}

template<typename T>
void LList<T>::insert(const u32 _i,T &&_newitem)
{
    lError(_i>=mSize+1,"void LList<T>::insert(const u32 _i,T &&_newitem): _i is not acceptable");
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=lMove(_newitem);
        return;
    }
    if(_i==0)
    {
        pushFront(_newitem);
        return;
    }
    if(_i==mSize)
    {
        pushBack(_newitem);
        return;
    }
    ListNode* _prev=mFirst;
    for(u32 i=1;i<_i;i++)
        _prev=_prev->mNext;
    ListNode*_next=_prev->mNext;
    _prev->mNext=new ListNode;
    _prev->mNext->mVal=lMove(_newitem);
    _prev->mNext->mNext=_next;
    _prev->mNext->mPrev=_prev;
    mSize++;
}

template<typename T>
void LList<T>::insert(const u32 _i,const T &_newitem)
{

    lError(_i>=mSize+1,"void LList<T>::insert(const u32 _i,T &&_newitem): _i is not acceptable");
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=lMove(_newitem);
        return;
    }
    if(_i==0)
    {
        pushFront(_newitem);
        return;
    }
    if(_i==mSize)
    {
        pushBack(_newitem);
        return;
    }
    ListNode* _prev=mFirst;
    for(u32 i=1;i<_i;i++)
        _prev=_prev->mNext;
    ListNode*_next=_prev->mNext;
    _prev->mNext=new ListNode;
    _prev->mNext->mVal=lMove(_newitem);
    _prev->mNext->mNext=_next;
    _prev->mNext->mPrev=_prev;
    mSize++;
}

template<typename T>
void LList<T>::insert(const u32 _i, const std::initializer_list<T> _items)
{
    for(u32 i=_items.size();i>0;i--)
        insert(_i,(_items.begin())[i-1]);
}

template<typename T>
void LList<T>::insert(const u32 _i, const LList<T> &_other)
{
    for(u32 i=_other.mSize;i>0;i--)
        insert(_i,(_other)[i-1]);
}

template<typename T>
void LList<T>::pushBack(const T &_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=_newitem;
    }
    else
    {
        mLast->mNext=new ListNode;
        mLast->mNext->mVal=_newitem;
        mLast->mNext->mPrev=mLast;
        mLast=mLast->mNext;
    }
}

template<typename T>
void LList<T>::pushBack(T &&_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=lMove(_newitem);
    }
    else
    {
        mLast->mNext=new ListNode;
        mLast->mNext->mVal=lMove(_newitem);
        mLast->mNext->mPrev=mLast;
        mLast=mLast->mNext;
    }
}

template<typename T>
void LList<T>::pushBack(const std::initializer_list<T> _items)
{
    for(u32 i=0;i<_items.size();i++)
        pushBack((_items.begin())[i]);
}

template<typename T>
void LList<T>::pushBack(const LList<T> &_other)
{
    for(u32 i=0;i<_other.mSize;i++)
        pushBack((_other)[i]);
}

template<typename T>
T LList<T>::popBack()
{
    lError(mSize==0,"T LList<T>::popBack(): list size is not enough to pop",T());
    T o = lMove((*this)[mSize-1]);
    remove(mSize-1);
    return o;
}

template<typename T>
void LList<T>::pushFront(const T &_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=_newitem;
    }
    else
    {
        ListNode* fnext=mFirst;
        mFirst=new ListNode;
        mFirst->mVal=_newitem;
        mFirst->mNext=fnext;
        fnext->mPrev=mFirst;
    }
}

template<typename T>
void LList<T>::pushFront(T &&_newitem)
{
    mSize++;
    if(mFirst==nullptr)
    {
        mLast=mFirst=new ListNode;
        mFirst->mVal=_newitem;
    }
    else
    {
        ListNode* fnext=mFirst;
        mFirst=new ListNode;
        mFirst->mVal=lMove(_newitem);
        mFirst->mNext=fnext;
        fnext->mPrev=mFirst;
    }
}

template<typename T>
void LList<T>::pushFront(const std::initializer_list<T> _items)
{
    for(u32 i=_items.size();i>0;i--)
        pushFront((_items.begin())[i-1]);
}

template<typename T>
void LList<T>::pushFront(const LList<T> &_other)
{
    for(u32 i=_other.mSize;i>0;i--)
        pushFront((_other)[i-1]);
}

template<typename T>
T LList<T>::popFront()
{
    lError(mSize==0,"T LList<T>::popBack(): list size is not enough to pop",T());
    T o = lMove((*this)[0]);
    remove(0);
    return o;
}

template<typename T>
void LList<T>::sort(LSortType _sorttype)
{
    _LList_Sort<decltype(*this),LHasOperator::Greater<T>::value && LHasOperator::Less<T>::value>::_sort((*this),mSize,_sorttype);
}

template<typename T>
void LList<T>::remove(u32 _index)
{
    lError(_index>=mSize,"void LList<T>::remove(u32 _index) : _index is not acceptable");
    erase(_index,1);
}

template<typename T>
void LList<T>::resize(const u32 _newsize)
{
    if(_newsize==mSize)
        return;
    if(_newsize==0)
    {
        clear();
        return;
    }
    static T d;
    if(_newsize>mSize)
        while (_newsize!=mSize)
            pushBack(d);
    else
        erase(_newsize-1);
}

template<typename T>
void LList<T>::reverse()
{
    u32 sc=getSize();
    for(u32 i=0;i<sc/2;i++)
        lSwap((*this)[i],(*this)[sc-i-1]);
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
    ListNode* f=mFirst;
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
    ListNode* f=mFirst;
    for(u32 i=0;i<_i;i++)
    {
        f=f->mNext;
    }
    return f->mVal;
}

template<typename T>
LList<T> &LList<T>::operator<<(const T &_newitem)
{
    pushBack(_newitem);
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator<<(T &&_newitem)
{
    pushBack(_newitem);
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator=(const LList<T> &_other)
{
    clear();
    resize(_other.mSize);
    for(u32 i=0;i<mSize;i++)
        (*this)[i]=_other[i];
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator=(LList<T>&& _other)
{
    clear();
    mSize=_other.mSize;
    mFirst=_other.mFirst;
    mLast=_other.mLast;
    _other.mSize=0;
    _other.mFirst=_other.mLast=nullptr;
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator+=(const T &_newitem)
{
    pushBack(_newitem);
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator+=(T &&_newitem)
{
    pushBack(_newitem);
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator+=(const std::initializer_list<T> _items)
{
    pushBack(_items);
    return *this;
}

template<typename T>
LList<T> &LList<T>::operator+=(const LList<T> &_other)
{
    pushBack(_other);
    return *this;
}

template<typename T>
LList<T> LList<T>::operator+(const std::initializer_list<T> _items)
{
    LList<T> o;
    o.pushBack(*this);
    o.pushBack(_items);
    return o;
}

template<typename T>
LList<T> LList<T>::operator+(const LList<T> &_other)
{
    LList<T> o;
    o.pushBack(*this);
    o.pushBack(_other);
    return o;
}

template<typename T> template<typename _T,typename _T2,bool _have_operator>
u32 LList<T>::_LList_Search<_T,_T2,_have_operator>::__find(_T _data, u32 _size, const _T2 &_what,u32 _from)
{
    for(u32 i=_from;i<_size;i++)
        if(_data[i]==_what)
            return i;
    return nothing;
}

template<typename T> template<typename _T,typename _T2>
u32 LList<T>::_LList_Search<_T,_T2,false>::__find(_T _data, u32 _size, const _T2 &_what,u32 _from)
{
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LList:searching for this type is not available typeid= \"")+lGetTypeName<_T>()+" and "+lGetTypeName<_T2>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}

template<typename T> template<typename _T,typename _T2,bool _have_operator>
u32 LList<T>::_LList_Search<_T,_T2,_have_operator>::__rfind(_T _data, u32 _size, const _T2 &_what,u32 _from)
{
    LUNUSED(_size);
    for(i64 i=_from;i>=0;i--)
        if(_data[i]==_what)
            return i;
    return nothing;
}

template<typename T> template<typename _T,typename _T2>
u32 LList<T>::_LList_Search<_T,_T2,false>::__rfind(_T _data, u32 _size, const _T2 &_what,u32 _from)
{
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LList:searching for this type is not available typeid= \"")+lGetTypeName<_T>()+" and "+lGetTypeName<_T2>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}


template<typename T> template<typename _T,bool _have_operator>
void LList<T>::_LList_Sort<_T,_have_operator>::_sort(_T _data, u32 _size,LSortType _type)
{
    lSort(_data,_size,_type);
}

template<typename T> template<typename _T>
void LList<T>::_LList_Sort<_T,false>::_sort(_T _data, u32 _size,LSortType _type)
{
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_type);
    LString _error_message=LSTR("LList:sorting for this type is not available typeid= \"")+lGetTypeName<_T>()+"\" you need to define bool operator> and bool operator< for this type to support sorting";
    lError(1,_error_message);
}

LNAMESPACE_END

#endif // LLIST_H
