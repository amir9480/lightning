#ifndef LFILE_H
#define LFILE_H

#include "ldefines.h"
#include "lstring.h"

LNAMESPACE_BEGIN


class LAPI LFile
{
public:
    enum IOType
    {
        IOTypeRead     =1<< 1,
        IOTypeWrite    =1<< 2,
        IOTypeAppend   =1<< 3,
        IOTypeBinary   =1<< 4
    };

public:
    LFile();

    LFile(LString _fname,int _opentype);

    virtual ~LFile();
    //! close if file is open . returns false if something was wrong
    bool            close();

    //! flush file
    void            flush();

    //! Get full path and name of file that you passed for open
    LString         getFileName()const;

    //! Get open type
    int             getOpenType() const;

    //! Get size of file in bytes
    u64             getSize();

    //! is write/read position on end of file
    bool            isEndOfFile()const;

    //! is some file opened or there is nothing to read/write
    bool            isOpen()const;

    //! open a file. if some thing was wrong returns false
    bool            open(LString _fname,int _opentype);

    //! write _size byte of _t on file
    void            read(void* _t,u64 _size);

    //! read all content of one file encoded with utf8
    static LString  readAll(const LString& _filename);

    //! reopen file with diffrent method
    bool            reopen(IOType _opentype);

    //! seek write/read pointer . set 0 to begin and -1 to end
    void            seekp(i64 _newp);

    //! returns current pointer offset from first of file
    i32             tellp()const;

    //! write _size byte of _t on file
    void            write(const void* _t,u64 _size);

    //! write some text
    void            write(const LString8& _in);
    void            write(const LString& _in);
    void            write(const LString32& _in);

    void            write(const void* _t,u32 _size);

protected:
    void*       mData;
    LString     mFilename;
    int         mOpenType;
};

LNAMESPACE_END

#endif // LFILE_H
