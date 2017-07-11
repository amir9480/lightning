#include "limage.h"

LNAMESPACE_BEGIN

LImage::LImage():
    mData(nullptr),
    mWidth(0),
    mHeight(0),
    mBytePerPixel(0)
{

}

LImage::~LImage()
{
    destroy();
}

u16 LImage::bytePerPixel(LImage::Format _type)
{
    switch(_type)
    {
    case Format::Format_null:
        return 0;
    case Format::Format_X8R8G8B8:
        return 4;
    case Format::Format_A8R8G8B8:
        return 4;
    }

    return 0;
}

void LImage::destroy()
{
    if(mData)
        delete[] mData;
    mData=nullptr;
    mWidth=0;
    mHeight=0;
    mBytePerPixel=0;
}

char *LImage::getData()
{
    return mData;
}

const char *LImage::getData() const
{
    return mData;
}

u16 LImage::getWidth() const
{
    return mWidth;
}

u16 LImage::getHeight() const
{
    return mHeight;
}

u16 LImage::getBytePerPixel() const
{
    return mBytePerPixel;
}

u64 LImage::getPixelsCount() const
{
    return mWidth*mHeight;
}

LImage::Format LImage::getFormat() const
{
    return mFormat;
}

void LImage::init(u16 _width, u16 _height, Format _type)
{
    destroy();
    mWidth=_width;
    mHeight=_height;
    mFormat=_type;
    mBytePerPixel=bytePerPixel(_type);

    mData=new char[mWidth*mHeight*mBytePerPixel];

}

LNAMESPACE_END
