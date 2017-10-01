#ifndef LMAP_H
#define LMAP_H

#include "ldefines.h"
#include "llog.h"
#include "lvector.h"
#include "lpair.h"
#include <initializer_list>

LNAMESPACE_BEGIN

//! Map Class
template<typename T1,typename T2>
class LAPI LMap
{
public:
    typedef T1 KeyType;
    typedef T2 ValueType;
    typedef typename LVector<LPair<T1,T2>>::Iterator      Iterator;
    typedef typename LVector<LPair<T1,T2>>::ConstIterator ConstIterator;
public:
    LMap();
    LMap(const std::initializer_list<LPair<T1,T2>> _other);
    LMap(const LMap<T1,T2>& _other);
    LMap(LMap<T1,T2>&& _other);
    virtual ~LMap();

    //! Get Access to Map elements by index
    linline T2&                             at(const u32 _i);
    linline const T2&                       at(const u32 _i)const;

    //! it's pointer to vector start for range based for
    linline Iterator                        begin();
    linline ConstIterator                   begin()const;

    //! clear map
    linline void                            clear();

    //! it's pointer to vector end for range based for
    linline Iterator                        end();
    linline ConstIterator                   end()const;

    //! erase part of map by index . from _from to _from+_count
    linline void                            erase(u32 _from,u32 _count=(u32)-1);

    //! find index and key of an element. if there was nothing retruns.second is LMap::nothing
    template<typename T3>
    linline LPair<u32,T1>                   find(const T3& _what, u32 _from=0)const;

    //! find index and key of an element and search starting from right. if there was nothing retruns.second is LMap::nothing
    template<typename T3>
    linline LPair<u32,T1>                   findFromRight(const T3& _what, u32 _from=(u32)-1)const;

    //! get index of key . if there was nothing returns LMap::nothing
    linline u32                             findKey(const T1& _key)const;

    //! resize this map as needed
    linline void                            flush();

    //! Get map Capacity
    linline u32                             getCapacity()const;

    //! Get map Data Directly
    linline const LVector<LPair<T1,T2>>&    getData()const;

    //! Get Size of map
    linline u32                             getSize()const;

    //! insert a new item , _newkey = key of new item and _newitem is value of new item
    linline void                            insert(const T1& _newkey, const T2& _newitem);
    linline void                            insert(const T1& _newkey, T2&& _newitem);
    linline void                            insert(T1&& _newkey, const T2& _newitem);
    linline void                            insert(T1&& _newkey, T2&& _newitem);

    //! Get Access to Map keys by index
    linline T1&                             keyAt(const u32 _i);
    linline const T1&                       keyAt(const u32 _i)const;

    //! remove an element of map by key value. if key does not exists nothing will happened
    linline void                            remove(const T1& _key);

    //! reserve capacity for add new items for futur . every (16) insertion will make a new operate and
    //! will cause speed down insertion . use this when you tring to add many items . it's highly recomended
    linline void                            reserve(const u32 _newsize);

    //! swap this list with another
    linline void                            swap(LMap<T1,T2>& _other);

    //! Get Access to map elements by key value
    linline T2&                             operator[](const T1& _key);
    linline const T2                        operator[](const T1& _key)const;

    //! Copy Assign
    linline LMap<T1,T2>&                    operator=(const LMap<T1,T2>& _other);

    //! Move Assign
    linline LMap<T1,T2>&                    operator=(LMap<T1,T2>&& _other);

    static const u32                        nothing;
protected:
    template<typename _T1,typename _T2,typename _T3,const bool _have_operator>
    struct _LMap_Search{ linline static u32 __find(const LVector<LPair<_T1,_T2>>& _data,u32 _size,const _T3& _what,u32 _from); linline static u32 __rfind(const LVector<LPair<_T1,_T2>>& _data,u32 _size,const _T3& _what,u32 _from); };
    template<typename _T1,typename _T2,typename _T3>
    struct _LMap_Search<_T1,_T2,_T3,false>{ linline static u32 __find(const LVector<LPair<_T1,_T2>>& _data,u32 _size,const _T3& _what,u32 _from); linline static u32 __rfind(const LVector<LPair<_T1,_T2>>& _data,u32 _size,const _T3& _what,u32 _from); };
private:
    LVector<LPair<T1,T2>> mData;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1,typename T2>
const u32 LMap<T1,T2>::nothing=(u32)-1;


template<typename T1,typename T2>
LMap<T1,T2>::LMap()
{

}

template<typename T1,typename T2>
LMap<T1,T2>::LMap(const std::initializer_list<LPair<T1,T2> > _other):
    mData(_other)
{

}

template<typename T1,typename T2>
LMap<T1,T2>::LMap(const LMap<T1,T2> &_other)
{
    *this = _other;
}

template<typename T1,typename T2>
LMap<T1,T2>::LMap(LMap<T1,T2> &&_other)
{
    *this = lMove(_other);
}

template<typename T1,typename T2>
LMap<T1,T2>::~LMap()
{
    mData.clear();
}

template<typename T1,typename T2>
T2 &LMap<T1,T2>::at(const u32 _i)
{
    static T2 d;
    lError(_i>=mData.getSize(),"T2 &LMap<T1,T2>::at(const u32 _i),_i is not accptable",d);
    return mData[_i].second;
}

template<typename T1,typename T2>
const T2 &LMap<T1,T2>::at(const u32 _i) const
{
    static T2 d;
    lError(_i>=mData.getSize(),"T2 &LMap<T1,T2>::at(const u32 _i),_i is not accptable",d);
    return mData[_i].second;
}

template<typename T1,typename T2>
typename LMap<T1,T2>::Iterator LMap<T1,T2>::begin()
{
    return mData.begin();
}

template<typename T1,typename T2>
typename LMap<T1,T2>::ConstIterator LMap<T1,T2>::begin() const
{
    return mData.begin();
}

template<typename T1,typename T2>
void LMap<T1,T2>::clear()
{
    mData.clear();
}

template<typename T1,typename T2>
typename LMap<T1,T2>::Iterator LMap<T1,T2>::end()
{
    return mData.end();
}

template<typename T1,typename T2>
typename LMap<T1,T2>::ConstIterator LMap<T1,T2>::end() const
{
    return mData.end();
}

template<typename T1,typename T2>
void LMap<T1,T2>::erase(u32 _from, u32 _count)
{
    lError(_from>=mData.getSize()||_from+_count>mData.getSize() || _count==0,"void LMap<T1,T2>::erase(u32 _from, u32 _count): one of paramets is not acceptable");
    mData.erase(_from,_count);
}

template<typename T1,typename T2> template<typename T3>
LPair<u32,T1> LMap<T1,T2>::findFromRight(const T3 &_what, u32 _from) const
{
    if(_from==(u32)-1)
        _from=mData.getSize()-1;
    static T1 d;
    lError(_from>=mData.getSize(),"u32 LMap<T>::findFromRight(const T3 &_what, u32 _from) const: _from is not acceptable",(LPair<u32,T1>(nothing,d)));
    u32 _i=_LMap_Search<T1,T2,T3,LHasOperator::Equal<T2,T3>::value>::__rfind(mData,mData.getSize(),_what,_from);
    if(_i!=(u32)-1)
        return LPair<u32,T1>(_i,keyAt(_i));
    return LPair<u32,T1>(_i,d);
}

template<typename T1,typename T2> template<typename T3>
LPair<u32,T1> LMap<T1,T2>::find(const T3 &_what, u32 _from) const
{
    static T1 d;
    lError(_from>=mData.getSize(),"u32 LMap<T>::find(const T3 &_what, u32 _from) const: _from is not acceptable",(LPair<u32,T1>(nothing,d)));
    u32 _i=_LMap_Search<T1,T2,T3,LHasOperator::Equal<T2,T3>::value>::__find(mData,mData.getSize(),_what,_from);
    if(_i!=(u32)-1)
        return LPair<u32,T1>(_i,keyAt(_i));
    return LPair<u32,T1>(_i,d);
}

template<typename T1,typename T2>
u32 LMap<T1,T2>::findKey(const T1 &_key)const
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_key)
            return i;
    return nothing;
}

template<typename T1,typename T2>
void LMap<T1,T2>::flush()
{
    mData.flush();
}

template<typename T1,typename T2>
u32 LMap<T1,T2>::getCapacity() const
{
    return mData.getCapacity();
}

template<typename T1,typename T2>
const LVector<LPair<T1,T2>>& LMap<T1,T2>::getData() const
{
    return mData;
}

template<typename T1,typename T2>
u32 LMap<T1,T2>::getSize() const
{
    return mData.getSize();
}

template<typename T1,typename T2>
void LMap<T1,T2>::insert(const T1 &_newkey, const T2 &_newitem)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_newkey)
        {
            mData[i].second=_newitem;
            return;
        }
    mData.pushBack(lMove(LPair<T1,T2>(_newkey,_newitem)));
}

template<typename T1,typename T2>
void LMap<T1,T2>::insert(const T1 &_newkey, T2 &&_newitem)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_newkey)
        {
            mData[i].second=lMove(_newitem);
            return;
        }
    mData.pushBack(lMove(LPair<T1,T2>(_newkey,lMove(_newitem))));
}

template<typename T1,typename T2>
void LMap<T1,T2>::insert(T1 &&_newkey, const T2 &_newitem)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_newkey)
        {
            mData[i].second=_newitem;
            return;
        }
    mData.pushBack(lMove(LPair<T1,T2>(lMove(_newkey),_newitem)));
}

template<typename T1,typename T2>
void LMap<T1,T2>::insert(T1 &&_newkey,T2 &&_newitem)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_newkey)
        {
            mData[i].second=lMove(_newitem);
            return;
        }
    mData.pushBack(lMove(LPair<T1,T2>(lMove(_newkey),lMove(_newitem))));
}


template<typename T1,typename T2>
T1 &LMap<T1,T2>::keyAt(const u32 _i)
{
    static T1 d;
    lError(_i>=mData.getSize(),"T1 &LMap<T1,T2>::keyAt(const u32 _i),_i is not accptable",d);
    return mData[_i].first;
}

template<typename T1,typename T2>
const T1 &LMap<T1,T2>::keyAt(const u32 _i) const
{
    static T1 d;
    lError(_i>=mData.getSize(),"T1 &LMap<T1,T2>::keyAt(const u32 _i),_i is not accptable",d);
    return mData[_i].first;
}

template<typename T1,typename T2>
void LMap<T1,T2>::remove(const T1 &_key)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_key)
        {
            mData.remove(i);
            return;
        }
}

template<typename T1,typename T2>
void LMap<T1,T2>::reserve(const u32 _newsize)
{
    mData.reserve(_newsize);
}

template<typename T1,typename T2>
void LMap<T1,T2>::swap(LMap<T1,T2> &_other)
{
    mData.swap(_other.mData);
}

template<typename T1,typename T2>
T2 &LMap<T1,T2>::operator[](const T1 &_key)
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_key)
            return mData[i].second;
    insert(_key,T2());
    return mData[ds].second;
}

template<typename T1,typename T2>
const T2 LMap<T1,T2>::operator[](const T1 &_key) const
{
    u32 ds=mData.getSize();
    for(u32 i=0;i<ds;i++)
        if(mData[i].first==_key)
            return mData[i].second;
    return T2();
}

template<typename T1,typename T2>
LMap<T1,T2> &LMap<T1,T2>::operator=(const LMap<T1,T2> &_other)
{
    mData=_other.mData;
    return *this;
}

template<typename T1,typename T2>
LMap<T1,T2> &LMap<T1,T2>::operator=(LMap<T1,T2> &&_other)
{
    mData=lMove(_other.mData);
    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1,typename T2> template<typename _T1,typename _T2,typename _T3,bool _have_operator>
u32 LMap<T1,T2>::_LMap_Search<_T1,_T2,_T3,_have_operator>::__find(const LVector<LPair<_T1,_T2>>& _data, u32 _size, const _T3 &_what,u32 _from)
{
    for(u32 i=_from;i<_size;i++)
        if(_data[i].second==_what)
            return i;
    return nothing;
}

template<typename T1,typename T2> template<typename _T1,typename _T2,typename _T3>
u32 LMap<T1,T2>::_LMap_Search<_T1,_T2,_T3,false>::__find(const LVector<LPair<_T1,_T2>>& _data, u32 _size, const _T3 &_what,u32 _from)
{
    LUNUSED(_from);
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LMap:searching for this type is not available typeid= \"")+lGetTypeName<_T2>()+" and "+lGetTypeName<_T3>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}

template<typename T1,typename T2> template<typename _T1,typename _T2,typename _T3,bool _have_operator>
u32 LMap<T1,T2>::_LMap_Search<_T1,_T2,_T3,_have_operator>::__rfind(const LVector<LPair<_T1,_T2>>& _data, u32 _size, const _T3 &_what,u32 _from)
{
    LUNUSED(_size);
    for(i64 i=_from;i>=0;i--)
        if(_data[i].second==_what)
            return i;
    return nothing;
}

template<typename T1,typename T2> template<typename _T1,typename _T2,typename _T3>
u32 LMap<T1,T2>::_LMap_Search<_T1,_T2,_T3,false>::__rfind(const LVector<LPair<_T1,_T2>>& _data, u32 _size, const _T3 &_what,u32 _from)
{
    LUNUSED(_from);
    LUNUSED(_data);
    LUNUSED(_size);
    LUNUSED(_what);
    LString _error_message=LSTR("LMap:searching for this type is not available typeid= \"")+lGetTypeName<_T2>()+" and "+lGetTypeName<_T3>()+"\" you need to define bool operator== for this type to support seraching";
    lError(1,_error_message,nothing);
    return nothing;
}

LNAMESPACE_END

#endif // LMAP_H
