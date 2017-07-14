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

struct __PngRead_struct
{
    u32 index;
    char* data;
};

void ___png_read(png_struct* _pngStruct,png_byte* _pngData,png_size_t _readsize)
{
    png_voidp a = png_get_io_ptr(_pngStruct);
    __PngRead_struct* b=(__PngRead_struct*)a;
    lMemoryCopy((void*)_pngData,&b->data[b->index],_readsize);
    b->index+=_readsize;
}


LImage LImage::loadFromPng(char *_data)
{
    LImage o;
    png_struct* png_ptr;
    png_info* info_ptr;

    __PngRead_struct g;
    g.index=0;
    g.data=_data+8;

    png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    if(png_ptr==nullptr)
    {
        lError(1,"PNG LOAD ERROR : png_create_read_struct",o);
    }
    info_ptr=png_create_info_struct(png_ptr);
    if(info_ptr==nullptr)
    {
        png_destroy_read_struct(&png_ptr,0,0);
        lError(1,"PNG LOAD ERROR : png_create_info_struct",o);
    }
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr,&info_ptr,0);
        lError(1,"PNG LOAD ERROR : setjmp(jmp_buf(png_ptr))",o);
    }

    png_set_read_fn(png_ptr,(png_voidp)&g,___png_read);
    png_set_sig_bytes(png_ptr,8);
    png_read_info(png_ptr,info_ptr);

    u32 _width=png_get_image_width(png_ptr,info_ptr);
    u32 _height=png_get_image_height(png_ptr,info_ptr);
   // int _depth=png_get_bit_depth(png_ptr,info_ptr);
    //int _color_type=png_get_color_type(png_ptr,info_ptr);

    const u32 _bytes_per_row = png_get_rowbytes(png_ptr,info_ptr);
    u8* _rowData=new u8[_bytes_per_row];

    o.init(_width,_height,LImage::Format_X8R8G8B8);
    for(u32 i=0;i<_height;i++)
    {
        png_read_row(png_ptr,(png_bytep)_rowData,0);
        for(u32 j=0;j<_width;j++)
        {
            o.mData[(i*_width*o.mBytePerPixel)+(j*4)+0]=_rowData[j*4+2];
            o.mData[(i*_width*o.mBytePerPixel)+(j*4)+1]=_rowData[j*4+1];
            o.mData[(i*_width*o.mBytePerPixel)+(j*4)+2]=_rowData[j*4+0];
            o.mData[(i*_width*o.mBytePerPixel)+(j*4)+3]=0;
        }
    }
    delete[] _rowData;

    png_destroy_read_struct(&png_ptr,&info_ptr,0);

    return o;
}

LImage LImage::loadFromPngFile(const LString &_fileName)
{
    LFile f(_fileName,LFile::IOTypeRead|LFile::IOTypeBinary);
    if(f.isOpen()==false)
    {
        lError(1,"LImage::loadFromPngFile(const LString &_fileName): file not found",LImage());
    }
    u64 _fs=f.getSize();
    char* _data = new char[_fs];
    f.read((void*)_data,_fs);
    LImage o = loadFromPng(_data);
    delete[] _data;
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
    _other.mData=nullptr;
    return lMove(*this);
}

LNAMESPACE_END
