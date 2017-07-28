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
    case Format::Format_R8G8B8:
        return 3;
    case Format::Format_R8G8B8A8:
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

LImage LImage::getResized(u16 _width, u16 _height) const
{
    LImage o;
    o.init(_width,_height,mFormat);
    f32 _w=((float)mWidth)/_width;
    f32 _h=((float)mHeight)/_height;
    switch (mFormat)
    {
    case Format_R8G8B8:
    {
        for(u32 i=0;i<_height;i++)
        {
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+0]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*3)+0))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+1]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*3)+1))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+2]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*3)+2))];
            }
        }
        break;
    }
    case Format_R8G8B8A8:
    {
        for(u32 i=0;i<_height;i++)
        {
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+0]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*4)+0))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+1]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*4)+1))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+2]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*4)+2))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+3]=mData[(int)(((i*_width*_w*o.mBytePerPixel)+(j*_h*4)+3))];
            }
        }
        break;
    }
    case Format_null:
        break;
    }
    return o;
}

LImage LImage::getCropped(u16 _x, u16 _y, u16 _width, u16 _height) const
{
    LImage o;
    o.init(_width,_height,mFormat);
    switch (mFormat)
    {
    case Format_R8G8B8:
    {
        for(u32 i=0;i<_height;i++)
        {
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+0]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*3)+(j*3)+0))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+1]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*3)+(j*3)+1))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+2]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*3)+(j*3)+2))];
            }
        }
        break;
    }
    case Format_R8G8B8A8:
    {
        for(u32 i=0;i<_height;i++)
        {
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+0]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*4)+(j*4)+0))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+1]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*4)+(j*4)+1))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+2]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*4)+(j*4)+2))];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+3]=mData[(int)(((_y*mWidth*o.mBytePerPixel)+(i*mWidth*o.mBytePerPixel)+(_x*4)+(j*4)+3))];
            }
        }
        break;
    }
    case Format_null:
        break;
    }
    return o;
}

void LImage::init(u16 _width, u16 _height, Format _type)
{
    destroy();
    mWidth=_width;
    mHeight=_height;
    mFormat=_type;
    mBytePerPixel=bytePerPixel(_type);

    if(mWidth!=0&&mHeight!=0&&mBytePerPixel!=0)
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
    int _depth=png_get_bit_depth(png_ptr,info_ptr);
    int _color_type=png_get_color_type(png_ptr,info_ptr);

    if(_depth==16)
        png_set_strip_16(png_ptr);
    if(_color_type==PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if(_color_type==PNG_COLOR_TYPE_GRAY&&_depth<8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if(png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if(_color_type==PNG_COLOR_TYPE_GRAY||_color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    png_read_update_info(png_ptr,info_ptr);

    const u32 _bytes_per_row = png_get_rowbytes(png_ptr,info_ptr);
    u8* _rowData=new u8[_bytes_per_row];

    switch (_color_type) {
    case PNG_COLOR_TYPE_RGB:
        o.init(_width,_height,LImage::Format_R8G8B8);
        for(u32 i=0;i<_height;i++)
        {
            png_read_row(png_ptr,(png_bytep)_rowData,0);
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+0]=_rowData[j*3+0];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+1]=_rowData[j*3+1];
                o.mData[(i*_width*o.mBytePerPixel)+(j*3)+2]=_rowData[j*3+2];
            }
        }
        break;
    case PNG_COLOR_TYPE_RGBA:
        o.init(_width,_height,LImage::Format_R8G8B8A8);
        for(u32 i=0;i<_height;i++)
        {
            png_read_row(png_ptr,(png_bytep)_rowData,0);
            for(u32 j=0;j<_width;j++)
            {
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+0]=_rowData[j*4+0];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+1]=_rowData[j*4+1];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+2]=_rowData[j*4+2];
                o.mData[(i*_width*o.mBytePerPixel)+(j*4)+3]=_rowData[j*4+3];
            }
        }
        break;
    default:
        break;
    }
    delete[] _rowData;

    png_destroy_read_struct(&png_ptr,&info_ptr,0);

    return o;
}

LImage LImage::loadFromPngFile(const LString &_fileName)
{
    LImage o;
    o.init(1,1,LImage::Format_R8G8B8);
    o.getData()[0]=150;
    o.getData()[1]=0;
    o.getData()[2]=150;
    LFile f(_fileName,LFile::IOTypeRead|LFile::IOTypeBinary);
    if(f.isOpen()==false)
    {
        lError(1,"LImage::loadFromPngFile(const LString &_fileName): file not found",o);
    }
    u64 _fs=f.getSize();
    char* _data = new char[_fs];
    f.read((void*)_data,_fs);
    o = loadFromPng(_data);
    delete[] _data;
    return o;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

struct __PngWrite_struct
{
    u32 index;
    LMemoryStream* data;
};

void ___png_write(png_struct* _pngStruct,png_byte* _pngData,png_size_t _writesize)
{
//    png_voidp a = png_get_io_ptr(_pngStruct);
//    __PngWrite_struct* b=(__PngWrite_struct*)a;
//    lMemoryCopy((void*)_pngData,&b->data[b->index],_readsize);
//    b->index+=_readsize;
    png_voidp a = png_get_io_ptr(_pngStruct);
    __PngWrite_struct* b=(__PngWrite_struct*)a;
    b->data->write((void*)_pngData,_writesize);
    b->index+=_writesize;
}
void ___png_write_flush(png_struct* png_ptr)
{
    LUNUSED(png_ptr);
}

LMemoryStream LImage::saveAsPng()
{
    LMemoryStream o;
    png_struct* png_ptr;
    png_info* info_ptr;

    __PngWrite_struct buf;
    buf.data=&o;
    buf.index=0;

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    if(!png_ptr)
    {
        lError(1,"libpng save png_create_write_struct Error",o);
    }
    info_ptr=png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        lError(1,"libpng save png_create_info_struct Error",o);
    }
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        lError(1,"libpng setjmp(png_jmpbuf(png_ptr)) Error",o);
    }

    png_set_write_fn(png_ptr,&buf,___png_write,___png_write_flush);

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        lError(1,"libpng setjmp(png_jmpbuf(png_ptr)) Error",o);
    }

    int _color_type;

    switch (mFormat)
    {
    case Format_R8G8B8:
        _color_type=PNG_COLOR_TYPE_RGB;
        break;
    case Format_R8G8B8A8:
        _color_type=PNG_COLOR_TYPE_RGBA;
        break;
    default:
        lError(1,"libpng save format is not supported ",o);
        break;
    }

    png_set_IHDR(png_ptr,info_ptr,mWidth,mHeight,8,_color_type,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        lError(1,"libpng setjmp(png_jmpbuf(png_ptr)) Error",o);
    }
    for(u32 i=0;i<mHeight;i++)
    {
        png_write_row(png_ptr,(unsigned char*)&mData[i*mWidth*mBytePerPixel]);
    }
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        lError(1,"libpng setjmp(png_jmpbuf(png_ptr)) Error",o);
    }
    png_write_end(png_ptr, NULL);
    return o;
}

void LImage::saveAsPngFile(const LString &_filename)
{
    LFile f(_filename,LFile::IOTypeBinary|LFile::IOTypeWrite);
    LMemoryStream ms=saveAsPng();
    f.write(ms.getData(),ms.getSize());
    f.close();
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

LImage& LImage::operator=(LImage &&_other)
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
    return (*this);
}

LNAMESPACE_END
