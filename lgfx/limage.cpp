#include "limage.h"

LNAMESPACE_BEGIN

LImage::LImage():
    mData(nullptr),
    mWidth(0),
    mHeight(0),
    mBytePerPixel(0)
{

}

LImage::LImage(const LImage &_other):
    LImage()
{
    *this = _other;
}

LImage::LImage(LImage &&_other):
    LImage()
{
    *this = lMove(_other);
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

bool LImage::isNull() const
{
    return (mData==nullptr);
}

#if LIGHTNING_IMAGE_PNG

char* ___current_png_data;

void ___png_read(png_struct* _pngStruct,png_byte* _pngData,png_size_t _readsize)
{

}

LImage LImage::loadFromPng(char *_data)
{
    LImage o;
    png_struct* pngStruct;
    png_info*   pngInfo;
    u32         sigread=0;
    pngStruct=png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    lError(pngStruct==nullptr,"PNG ERROR: png_create_read_struct ",o);
    pngInfo=png_create_info_struct(pngStruct);
    if(pngInfo==nullptr)
    {
        png_destroy_read_struct(&pngStruct,0,0);
        lError(1,"PNG ERROR: png_create_info_struct ",o);
    }
    if(setjmp(png_jmpbuf(pngStruct)))
    {
        png_destroy_read_struct(&pngStruct,&pngInfo,0);
        lError(1,"PNG ERROR: setjmp(png_jmpbuf(pngStruct))",o);
    }

    png_destroy_read_struct(&pngStruct,&pngInfo,0);
    return o;
}

#endif

LImage &LImage::operator=(const LImage &_other)
{
    destroy();
    mWidth=_other.mWidth;
    mHeight=_other.mHeight;
    mBytePerPixel=_other.mBytePerPixel;
    mFormat=_other.mFormat;
    mData=new char[mWidth*mHeight*mBytePerPixel];
    lMemoryCopy(mData,_other.mData,mWidth*mHeight*mBytePerPixel);
    return *this;
}

LImage &&LImage::operator=(LImage &&_other)
{
    destroy();
    mWidth=_other.mWidth;
    mHeight=_other.mHeight;
    mBytePerPixel=_other.mBytePerPixel;
    mFormat=_other.mFormat;
    mData=_other.mData;
    _other.mWidth=0;
    _other.mHeight=0;
    _other.mBytePerPixel=0;
    _other.mFormat=Format_null;
    return lMove(*this);
}

LNAMESPACE_END
