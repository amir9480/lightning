#include "lfile.h"
#include "stdio.h"
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
<<<<<<< HEAD
    switch ((int)_opentype) {
    case (IOType::IOType_Read):
        mData=fopen(_fname.toUTF8().getData(),"r");
        break;
    case (IOType::IOType_Write):
        mData=fopen(_fname.toUTF8().getData(),"w");
        break;
    case (IOType::IOType_Append):
        mData=fopen(_fname.toUTF8().getData(),"a");
        break;
    case (IOType::IOType_Read|IOType::IOType_Write):
        mData=fopen(_fname.toUTF8().getData(),"r+");
        break;
    case (IOType::IOType_Read|IOType::IOType_Append):
        mData=fopen(_fname.toUTF8().getData(),"a+");
        break;
    case (IOType::IOType_Read|IOType_Binary):
        mData=fopen(_fname.toUTF8().getData(),"rb");
        break;
    case (IOType::IOType_Write|IOType_Binary):
        mData=fopen(_fname.toUTF8().getData(),"wb");
        break;
    case (IOType::IOType_Append|IOType_Binary):
        mData=fopen(_fname.toUTF8().getData(),"ab");
        break;
    case (IOType::IOType_Read|IOType::IOType_Write|IOType_Binary):
        mData=fopen(_fname.toUTF8().getData(),"r+b");
        break;
    case (IOType::IOType_Read|IOType::IOType_Append|IOType_Binary):
        mData=fopen(_fname.toUTF8().getData(),"a+b");
        break;
    default:
        return false;
    }
    if(mData==0)
        return false;
=======
    if(_opentype==(IOType::IOType_Read))
    {
        mData=fopen(_fname.toUTF8().getData(),"r");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Write))
    {
        mData=fopen(_fname.toUTF8().getData(),"w");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Append))
    {
        mData=fopen(_fname.toUTF8().getData(),"a");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Read|IOType::IOType_Write))
    {
        mData=fopen(_fname.toUTF8().getData(),"r+");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Read|IOType::IOType_Append))
    {
        mData=fopen(_fname.toUTF8().getData(),"a+");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Read|IOType_Binary))
    {
        mData=fopen(_fname.toUTF8().getData(),"rb");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Write|IOType_Binary))
    {
        mData=fopen(_fname.toUTF8().getData(),"wb");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Append|IOType_Binary))
    {
        mData=fopen(_fname.toUTF8().getData(),"ab");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Read|IOType::IOType_Write|IOType_Binary))
    {
        mData=fopen(_fname.toUTF8().getData(),"r+b");
        if(mData==0)
            return false;
    }
    else if(_opentype==(IOType::IOType_Read|IOType::IOType_Append|IOType_Binary))
    {
        mData=fopen(_fname.toUTF8().getData(),"a+b");
        if(mData==0)
            return false;
    }

>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
    mFilename=_fname;
    mOpenType=_opentype;
    return true;
}

<<<<<<< HEAD
void LFile::read(void *_t, u64 _size)
=======
void LFile::read(void *_t, u32 _size)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
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
<<<<<<< HEAD
    if(_opentype==mOpenType)// Already is open
        return true;
=======
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
    fclose((FILE*)mData);
    mData=0;
    return open(mFilename,_opentype);
}

<<<<<<< HEAD
void LFile::seekp(i64 _newp)
=======
void LFile::seekp(i32 _newp)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
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

<<<<<<< HEAD
void LFile::write(const void *_t, u64 _size)
=======
void LFile::write(const void *_t, u32 _size)
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
{
    if(mData==0)
        return;
    //! Add excpetion mData=0
    fwrite(_t,1,_size,(FILE*)mData);
}

<<<<<<< HEAD
void LFile::write(const LString8 &_in)
{
    if(mData==0)
        return;
    u32 s= _in.getCapasity();
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

=======
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
LFile::IOType LFile::getOpenType() const
{
    return mOpenType;
}

<<<<<<< HEAD
i64 LFile::getSize()
=======
i32 LFile::getSize()
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d
{
    if(mFilename==0)
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
