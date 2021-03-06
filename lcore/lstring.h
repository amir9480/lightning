﻿#ifndef LString_Base_H
#define LString_Base_H

#include "ldefines.h"
#include "lmemory.h"

LNAMESPACE_BEGIN
/*
 * TO DO : Add Convertion from and to numbers
 */

//! Literal for LString
#define LSTR(_STR) (LString::fromUTF8(_STR))

template <typename chartype>
class LAPI LString_Base
{

    template<typename T>
    friend struct __LVariantTypeCastHelper;
    friend class LString_Base<char>;
    friend class LString_Base<wchar_t>;
    friend class LString_Base<char32_t>;
public:
    typedef chartype         type;
    typedef chartype*        iterator;
    typedef const chartype*  const_iterator;

    typedef LString_Base<wchar_t>  LString;
    typedef LString_Base<char>     LString8;
    typedef LString_Base<char32_t> LString32;
public:

    LString_Base();
    LString_Base(const chartype& _c);
    LString_Base(const char* _firstvalue);
    LString_Base(const wchar_t* _firstvalue);
    LString_Base(const char32_t* _firstvalue);
    LString_Base(const LString_Base<char>& _other);
    LString_Base(const LString_Base<wchar_t>& _other);
    LString_Base(const LString_Base<char32_t>& _other);
    LString_Base(LString_Base<chartype>&& _other);
    virtual ~LString_Base();

    //! Append another string to this
    void                            append(const chartype* _other);
    void                            append(LString_Base<chartype> _other);

    //! returns character at index=i
    chartype&                       at(u32 i);
    chartype                        at(u32 i)const;

    //! it's pointer to string start for range based for
    iterator                        begin();
    const_iterator                  begin()const;

    //! Clear string
    void                            clear();

    //! it's pointer to string end for range based for
    iterator                        end();
    const_iterator                  end()const;

    //! erase part of string . _start = start point to erase and _n is size to erase if was -1 . it will erase from _start while string capacity
    void                            erase(u32 _start,u32 _n=-1);

    //! find index of a sub str. if was no result returns LString::nothing
    u32                             find(const chartype* _what,u32 _from=0) const;
    u32                             find(const LString_Base<chartype> _what,u32 _from=0) const;
    //! find index of a sub str  started from right. if was nothing returns LString::nothing
    //! function searching inside str[0-_from]
    u32                             findFromRight(const chartype* _what,u32 _from=0) const;

    //! Create string from short integer
    static LString_Base<chartype>   fromShortInt(const short int& _in,const u32 _base=10);

    //! Create string from unsigned short integer
    static LString_Base<chartype>   fromUShortInt(const short unsigned int& _in,const u32 _base=10);

    //! Create string from integer \sa toInt
    static LString_Base<chartype>   fromInt(const int& _in,const u32 _base=10);

    //! Create string from unsigned integer
    static LString_Base<chartype>   fromUInt(const unsigned int& _in,const u32 _base=10);

    //! Create string from integer \sa toInt
    static LString_Base<chartype>   fromLongLongInt(const long long int& _in,const u32 _base=10);

    //! Create string from unsigned integer
    static LString_Base<chartype>   fromULongLongInt(const unsigned long long int& _in,const u32 _base=10);

    //! Create string from float
    static LString_Base<chartype>   fromFloat(const float& _in);

    //! Create string from double
    static LString_Base<chartype>   fromDouble(const double& _in);

    //! Create string from long double (this function is not working well)
    static LString_Base<chartype>   fromLongDouble(const long double& _in);

    //! Create string from utf8-encoded string
    static LString_Base<chartype>   fromUTF8(const LString8& _in);
    static LString_Base<chartype>   fromUTF8(const char* _in);

    //! Create string from utf16-encoded string
    static LString_Base<chartype>   fromUTF16(const LString& _in);
    static LString_Base<chartype>   fromUTF16(const wchar_t* _in);


    //! Get capacity of string means that how much is allocated by string
    //! to get length you need use getLength \sa getSize
    u32                             getCapacity()const;

    //! returns string data directly
    const chartype*                 getData()const;

    //! get reversed copy of this
    LString_Base<chartype>          getReversed()const;

    //! get real size of this string \sa getCapacity
    u32                             getSize()const;

    //! get part of string created from _n charcters from start. if end was -1 it means from _start to string end
    LString_Base<chartype>          getSubString(u32 _start,u32 _n=-1)const;

    //! Get copy of this string without white spaces
    LString_Base<chartype>          getWithoutWhiteSpaces()const;

    //! insert another string inside this string
    void                            insert(u32 _index,const chartype* _val);
    void                            insert(u32 _index,const LString_Base<chartype>& _val);

    //! Check out this string is empty or not
    bool                            isEmpty()const;

    //! Check all of string is integer number only
    bool                            isInt(u32 _base=10)const;

    //! Check all of string is unsigned integer number only
    bool                            isUInt(u32 _base=10)const;

    //! remove a character in _index
    void                            remove(u32 _index);

    //! remove all white spaces
    void                            removeWhiteSpaces();

    //! replace string from index with _val . note that if there was not enough space string will resize
    void                            replace(u32 _index,const chartype* _val);
    void                            replace(u32 _index,const LString_Base<chartype>& _val);

    //! Replace all _what words with _with word
    void                            replaceAll(const chartype* _what,const chartype* _with,u32 _start=0,u32 _end=-1);
    void                            replaceAll(const LString_Base<chartype>& _what,const LString_Base<chartype>& _with,u32 _start=0,u32 _end=-1);

    //! resize string
    void                            resize(u32 ns);

    //! reverse string
    void                            reverse();

    //! swap this string with another string
    void                            swap(LString_Base<chartype>& _other);

    //! Convert string to short integer
    short int                       toShortInt(const u32 _base=10)const;

    //! Convert string to unsigned short integer
    unsigned short int              toUShortInt(const u32 _base=10)const;

    //! Convert string to integer \sa fromInt
    int                             toInt(const u32 _base=10)const;

    //! Convert string to unsigned integer
    unsigned int                    toUInt(const u32 _base=10)const;

    //! Convert string to long integer
    long long int                   toLongLongInt(const u32 _base=10)const;

    //! Convert string to unsigned long integer
    unsigned long long int          toULongLongInt(const u32 _base=10)const;

    //! Convert string to float
    float                           toFloat()const;

    //! Convert string to double
    double                          toDouble()const;

    //! Convert string to long double
    long double                     toLongDouble()const;

    //! Convert all latin characters to lowercase
    LString_Base<chartype>          toLower()const;

    //! Convert all latin characters to uppercase
    LString_Base<chartype>          toUpper()const;

    //! Convert to utf8
    LString8                        toUTF8()const;

    //! convert to utf16
    LString                         toUTF16()const;

    //! convert to utf32
    LString32                       toUTF32()const;

    //! Asign Copy operators
    LString_Base<chartype>&         operator=(const char* _other);
    LString_Base<chartype>&         operator=(const wchar_t* _other);
    LString_Base<chartype>&         operator=(const char32_t* _other);
    LString_Base<chartype>&         operator=(const LString_Base<char>& _other);
    LString_Base<chartype>&         operator=(const LString_Base<wchar_t>& _other);
    LString_Base<chartype>&         operator=(const LString_Base<char32_t>& _other);
    LString_Base<chartype>&         operator=(LString_Base<chartype>&& _other);

    //! returns this string that other appended
    LString_Base<chartype>          operator+(const chartype _other)const;
    LString_Base<chartype>          operator+(const chartype* _other)const;
    LString_Base<chartype>          operator+(const LString_Base<chartype>& _other)const;

    //! just like append
    LString_Base<chartype>&         operator+=(const chartype _other);
    LString_Base<chartype>&         operator+=(const chartype* _other);
    LString_Base<chartype>&         operator+=(const LString_Base<chartype>& _other);

    //! Compare functions
    bool                            operator==(const char* _other)const;
    bool                            operator==(const wchar_t* _other)const;
    bool                            operator==(const char32_t* _other)const;
    bool                            operator==(const LString_Base<chartype>& _other)const;

    bool                            operator>(const char* _other)const;
    bool                            operator>(const wchar_t* _other)const;
    bool                            operator>(const char32_t* _other)const;
    bool                            operator>(const LString_Base<chartype>& _other)const;

    bool                            operator<(const char* _other)const;
    bool                            operator<(const wchar_t* _other)const;
    bool                            operator<(const char32_t* _other)const;
    bool                            operator<(const LString_Base<chartype>& _other)const;

    bool                            operator!=(const chartype* _other)const;
    bool                            operator!=(const LString_Base<chartype>& _other)const;

    //! just like at
    chartype&                       operator[](u32 i);
    chartype                        operator[](u32 i)const;

public:
    //! an Empty string
    static const LString_Base<chartype> empty;
    //! using this index value for functions like find  str.find(blabla)==LString::nothing means nothing finds
    static const u32                nothing;
//protected:
    //! convert a unicode to utf8 encoded string. note that don't try to release what returns
    static char*                    __utility_utf8encode(u32 _in);
    //! convert a utf8 encoded to unicode
    static u32                      __utility_utf8decode(const char *_in2);
    //! convert a unicode to utf16 encoded string. note that don't try to release what returns
    static u32                      __utility_utf16decode(const wchar_t *_in);
    //! convert a utf16 encoded to unicode
    static wchar_t*                 __utility_utf16encode(u32 _in);
    //! returns capacity of string t
    template <typename T>
    static u32                      __utility_strlen(const T* _t);

protected:
    chartype* mData;
};

template <typename chartype1,typename chartype2>
LString_Base<chartype1> operator +(const chartype1 *_a, const LString_Base<chartype2> &_b);

template <typename chartype1,typename chartype2>
bool operator==(const chartype1 *_a, const LString_Base<chartype2> &_b);

typedef LString_Base<wchar_t>  LString;
typedef LString_Base<char>     LString8;
typedef LString_Base<char32_t> LString32;

LNAMESPACE_END
#endif // LString_Base_H
