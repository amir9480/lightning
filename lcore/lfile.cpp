#include "lfile.h"
#include <stdio.h>
LNAMESPACE_BEGIN

LFile::LFile()
{
    mData=0;
}

LFile::LFile(LString _fname, LFile::IOType _opentype)
{
    open(_fname,_opentype);
}

LFile::~LFile()
{
    close();
}

bool LFile::close()
{
    if(mData)
    {
        fclose((FILE*)mData);
        mData=0;
        mOpenType=(IOType)0;
        mFilename.clear();
        return true;
    }
    return false;
}

void LFile::flush()
{
    if(mData==0)
        return;
    fflush((FILE*)mData);
}

LString LFile::getFileName() const
{
    return mFilename;
}

bool LFile::isOpen() const
{
    return (mData!=0);
}

bool LFile::open(LString _fname, LFile::IOType _opentype)
{
    if(mData)
        return false;
    switch ((int)_opentype) {
    case (IOType::IOTypeRead):
        mData=fopen(_fname.toUTF8().getData(),"r");
        break;
    case (IOType::IOTypeWrite):
        mData=fopen(_fname.toUTF8().getData(),"w");
        break;
    case (IOType::IOTypeAppend):
        mData=fopen(_fname.toUTF8().getData(),"a");
        break;
    case (IOType::IOTypeRead|IOType::IOTypeWrite):
        mData=fopen(_fname.toUTF8().getData(),"r+");
        break;
    case (IOType::IOTypeRead|IOType::IOTypeAppend):
        mData=fopen(_fname.toUTF8().getData(),"a+");
        break;
    case (IOType::IOTypeRead|IOType::IOTypeBinary):
        mData=fopen(_fname.toUTF8().getData(),"rb");
        break;
    case (IOType::IOTypeWrite|IOType::IOTypeBinary):
        mData=fopen(_fname.toUTF8().getData(),"wb");
        break;
    case (IOType::IOTypeAppend|IOType::IOTypeBinary):
        mData=fopen(_fname.toUTF8().getData(),"ab");
        break;
    case (IOType::IOTypeRead|IOType::IOTypeWrite|IOType::IOTypeBinary):
        mData=fopen(_fname.toUTF8().getData(),"r+b");
        break;
    case (IOType::IOTypeRead|IOType::IOTypeAppend|IOType::IOTypeBinary):
        mData=fopen(_fname.toUTF8().getData(),"a+b");
        break;
    default:
        return false;
    }
    if(mData==0)
        return false;
    mFilename=_fname;
    mOpenType=_opentype;
    return true;
}

void LFile::read(void *_t, u64 _size)
{
    if(mData==0)
        return;
    //! Add excpetion mData=0
    fread(_t,1,_size,(FILE*)mData);
}

bool LFile::reopen(LFile::IOType _opentype)
{
    if(mData==0)
        return false;
    if(_opentype==mOpenType)// Already is open
        return true;
    fclose((FILE*)mData);
    mData=0;
    return open(mFilename,_opentype);
}

void LFile::seekp(i64 _newp)
{
    if(mData==0)
        return;
    if(_newp!=-1)
        fseek((FILE*)mData,_newp,SEEK_SET);
    else
        fseek((FILE*)mData,0,SEEK_END);
}

i32 LFile::tellp() const
{
    if(mData==0)
        return -1;
    return ftell((FILE*)mData);
}

void LFile::write(const void *_t, u64 _size)
{
    if(mData==0)
        return;
    //! Add excpetion mData=0
    fwrite(_t,1,_size,(FILE*)mData);
}

void LFile::write(const LString8 &_in)
{
    if(mData==0)
        return;
    u32 s= _in.getCapacity();
    fwrite(_in.getData(),1,s,(FILE*)mData);
}

void LFile::write(const LString &_in)
{
    write(_in.toUTF8());
}

void LFile::write(const LString32 &_in)
{
    write(_in.toUTF8());
}

LFile::IOType LFile::getOpenType() const
{
    return mOpenType;
}

i64 LFile::getSize()
{
    if(mFilename.isEmpty())
        return -1;
    i32 p1=tellp();
    seekp(-1);
    i32 s=tellp();
    seekp(p1);
    return s;
}

bool LFile::isEndOfFile() const
{
    return feof((FILE*)mData);
}


LNAMESPACE_END
