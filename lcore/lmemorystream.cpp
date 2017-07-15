#include "lmemorystream.h"

LNAMESPACE_BEGIN

LMemoryStream::LMemoryStream():
    mData(nullptr),
    mSize(0),
    mPointer(0)
{

}

LMemoryStream::LMemoryStream(const LMemoryStream &_other)
{
    (*this)=_other;
}

LMemoryStream::LMemoryStream(LMemoryStream &&_other)
{
    (*this)=lMove(_other);
}

LMemoryStream::~LMemoryStream()
{
    destroy();
}

void LMemoryStream::destroy()
{
    if(mData)
    {
        delete[] mData;
        mSize=0;
        mPointer=0;
    }
}

char *LMemoryStream::getData()
{
    return mData;
}

bool LMemoryStream::isEndOfStream() const
{
    return (mPointer==mSize);
}

void LMemoryStream::resize(u64 _new_size)
{
    if(_new_size==mSize)
        return;
    if(_new_size==0)
        return destroy();
    if(mData)
    {
        char* _prev_data;
        mData=new char[_new_size];
        lMemoryCopy(mData,_prev_data,lMin(mSize,_new_size)*sizeof(*mData));
        delete[] _prev_data;
    }
    else
    {
        mPointer=0;
        mData=new char[_new_size];
    }
    mSize=_new_size;
}

void LMemoryStream::read(void *_data, u64 _size)
{
    lError(_size+mPointer>=mSize,"LMemoryStream::read(char *_data, u64 _size): _size is not acceptable . please use seekp or resize first");
    lMemoryCopy(_data,&mData[mPointer],_size);
    mPointer+=_size;
}

void LMemoryStream::seekp(i64 _newp)
{
    if(_newp==-1)
    {
        mPointer=mSize;
        return;
    }
    mPointer=_newp;
}

void LMemoryStream::setData(const void *_data)
{
    lMemoryCopy(mData,_data,mSize);
}

void LMemoryStream::setData(void *_data, u64 _size)
{
    resize(_size);
    lMemoryCopy(mData,_data,_size);
}

u64 LMemoryStream::tellp() const
{
    return mPointer;
}

void LMemoryStream::write(const void *_data, u64 _size)
{
    resize(lMax(mPointer+_size,mSize));
    lMemoryCopy(&mData[mPointer],_data,_size);
    mPointer+=_size;
}

char &LMemoryStream::operator[](u64 _i)
{
    static char _fake;
    lError(_i>=mSize,"LMemoryStream::operator[](u64 _i): _i is not acceptable",_fake);
    return mData[_i];
}

char LMemoryStream::operator[](u64 _i) const
{
    static char _fake;
    lError(_i>=mSize,"LMemoryStream::operator[](u64 _i): _i is not acceptable",_fake);
    return mData[_i];
}

LMemoryStream &LMemoryStream::operator=(const LMemoryStream &_other)
{
    resize(_other.mSize);
    mPointer=_other.mPointer;
    setData(_other.mData,_other.mSize);
    return *this;
}

LMemoryStream &&LMemoryStream::operator=(LMemoryStream &&_other)
{
    destroy();
    mData=_other.mData;
    mSize=_other.mSize;
    mPointer=_other.mPointer;
    _other.mData=nullptr;
    _other.mSize=0;
    _other.mPointer=0;
    return lMove(*this);
}

LNAMESPACE_END
