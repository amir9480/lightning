#ifndef LFILE_H
#define LFILE_H

#include "ldefines.h"
#include "lstring.h"

LNAMESPACE_BEGIN


<<<<<<< HEAD
class LAPI LFile
=======
class LFile
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
{
public:
    enum IOType
    {
        IOType_Read     =0x01,
        IOType_Write    =0x02,
        IOType_Append   =0x04,
        IOType_Binary   =0x08
    };

public:
    LFile();

    LFile(LString _fname,IOType _opentype);

    virtual ~LFile();
    //! close if file is open . returns false if something was wrong
    bool        close();

    //! Get full path and name of file that you passed for open
    LString     getFileName()const;

    //! Get open type
    IOType      getOpenType() const;

    //! Get size of file in bytes
<<<<<<< HEAD
    i64         getSize();
=======
    i32         getSize();
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d

    //! is write/read position on end of file
    bool        isEndOfFile()const;

    //! is some file opened or there is nothing to read/write
    bool        isOpen()const;

    //! open a file. if some thing was wrong returns false
    bool        open(LString _fname,IOType _opentype);

    //! write _size byte of _t on file
<<<<<<< HEAD
    void        read(void* _t,u64 _size);
=======
    void        read(void* _t,u32 _size);
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d

    //! reopen file with diffrent method
    bool        reopen(IOType _opentype);

    //! seek write/read pointer . set 0 to begin and -1 to end
<<<<<<< HEAD
    void        seekp(i64 _newp);
=======
    void        seekp(i32 _newp);
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d

    //! returns current pointer offset from first of file
    i32         tellp()const;

    //! write _size byte of _t on file
<<<<<<< HEAD
    void        write(const void* _t,u64 _size);

    //! write some text
    void        write(const LString8& _in);
    void        write(const LString& _in);
    void        write(const LString32& _in);
=======
    void        write(const void* _t,u32 _size);
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
//private:
    void*       mData;
    LString     mFilename;
    IOType      mOpenType;
};

LNAMESPACE_END

#endif // LFILE_H
