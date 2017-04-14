#ifndef LString_Base_H
#define LString_Base_H

#include "ldefines.h"
#include "lmemory.h"

LNAMESPACE_BEGIN

template <typename chartype>
class LString_Base
{
public:
    typedef wchar_t*        iterator;
    typedef const wchar_t*  const_iterator;
public:
    LString_Base();
    LString_Base(const chartype& _c);
    LString_Base(const chartype* _firstvalue);
    LString_Base(const LString_Base<chartype>& _other);
    LString_Base(LString_Base<chartype> &&_other);
    virtual ~LString_Base();

    //! Append another string to this
    void                        append(const chartype* _other);
    void                        append(LString_Base<chartype> _other);

    //! returns character at index=i
    chartype&                   at(u32 i);
    chartype                    at(u32 i)const;

    //! Clear string
    void                        clear();

    //! erase part of string . _start = start point to erase and _n is size to erase if was -1 . it will erase from _start while string capasity
    void                        erase(u32 _start,u32 _n=-1);

    //! find index of a sub str. if was nothing returns LString::nothing
    u32                         find(const chartype* _what,u32 _from=0) const;
    u32                         find(const LString_Base<chartype> _what,u32 _from=0) const;
    //! find index of a sub str  started from right. if was nothing returns LString::nothing
    //! function searching inside str[0-_from]
    u32                         findFromRight(const chartype* _what,u32 _from=0) const;

    //! Get Capasity of string means that how much is allocated by string
    //! to get length you need use getLength
    u32                         getCapasity()const;

    //! returns string data directly
    chartype*                   getData()const;

    //! get part of string created from _n charcters from start. if end was -1 it means from _start to string end
    LString_Base<chartype>      getSubString(u32 _start,u32 _n=-1)const;

    //! insert another string inside this string
    void                        insert(u32 _index,const chartype* _val);
    void                        insert(u32 _index,const LString_Base<chartype>& _val);

    //! Check out this string is empty or not
    bool                        isEmpty()const;

    //! replace string from index with _val . note that if there was not enough space string will resize
    void                        replace(u32 _index,const chartype* _val);
    void                        replace(u32 _index,const LString_Base<chartype>& _val);

    //! resize string
    void                        resize(u32 ns);

    //! Asign Copy operators
    LString_Base&               operator=(const chartype* _other);
    LString_Base&               operator=(const LString_Base<chartype>& _other);
    LString_Base&               operator=(LString_Base<chartype>&& _other);

    //! returns this string that other appended
    LString_Base                operator+(const chartype* _other);
    LString_Base                operator+(const LString_Base<chartype>& _other);

    //! just like append
    LString_Base&               operator+=(const chartype* _other);
    LString_Base&               operator+=(const LString_Base<chartype>& _other);

    //! Compare functions
    bool                        operator==(const chartype* _other)const;
    bool                        operator==(const LString_Base<chartype>& _other)const;

    bool                        operator!=(const chartype* _other)const;
    bool                        operator!=(const LString_Base<chartype>& _other)const;

    //! just like at
    chartype&                   operator[](u32 i);
    chartype                    operator[](u32 i)const;

public:
    //! an Empty string
    static const LString_Base<chartype> empty;
    //! using this index value for functions like find  str.find(blabla)==LString::nothing means nothing finds
    static const u32            nothing;
//protected:
    //! convert a unicode to utf8 encoded string. note that don't try to release what returns
    static char*                __utility_utf8encode(u32 _in);
    //! convert a utf8 encoded to unicode
    static u32                  __utility_utf8decode(const char *_in2);
    //! convert a unicode to utf16 encoded string. note that don't try to release what returns
    static u32                  __utility_utf16decode(const wchar_t *_in);
    //! convert a utf16 encoded to unicode
    static wchar_t*             __utility_utf16encode(u32 _in);
    //! returns capasity of string t
    template <typename T>
    static u32                  __utility_strlen(const T* _t);
protected:
    chartype* mData;
};

typedef LString_Base<wchar_t>  LString;
typedef LString_Base<char>     LString8;
typedef LString_Base<char32_t> LString32;

LNAMESPACE_END
#endif // LString_Base_H
