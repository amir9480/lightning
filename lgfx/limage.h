#ifndef LIMAGE_H
#define LIMAGE_H

#include "../lcore.h"

#if LIGHTNING_IMAGE_PNG
	#include <png.h>
#endif



LNAMESPACE_BEGIN

//! hold image contents
class LAPI LImage
{
public:
    enum Format
    {
        Format_null=0,

        Format_R8G8B8,
        Format_R8G8B8A8,

    };

public:
    LImage();
    LImage(const LImage& _other);
    LImage(LImage&& _other);
    virtual ~LImage();


    //! get one pixel size in bytes from Format
    static u16      bytePerPixel(Format _type);

    //! destroy
    void            destroy();

    //! get Data directly
    char*           getData();

    //! get Data Directly
    const char*     getData()const;

    //! get Image width
    u16             getWidth() const;

    //! get Image height
    u16             getHeight() const;

    //! get this image one pixel size in bytes
    u16             getBytePerPixel() const;

    //! get number of pixels
    u64             getPixelsCount()const;

    //! get image format
    Format          getFormat() const;

    //! get resized copy of this
    LImage          getResized(u16 _width,u16 _height)const;

    //! get cropped copy of this
    LImage          getCropped(u16 _x,u16 _y,u16 _width,u16 _height)const;

    //! init a new image
    void            init(u16 _width,u16 _height,Format _type);

    //! check this texture is nothing
    bool            isNull()const;

#if LIGHTNING_IMAGE_PNG
    //! load from PNG format
    static LImage   loadFromPng(char* _data);
    static LImage   loadFromPngFile(const LString &_fileName);

    //! save image as PNG
    LMemoryStream   saveAsPng();
    void            saveAsPngFile(const LString& _filename);
#endif



    LImage& operator=(const LImage& _other);
    LImage& operator=(LImage&& _other);

protected:
    char*   mData;
    u16     mWidth;
    u16     mHeight;
    u16     mBytePerPixel;
    Format  mFormat;
};

LNAMESPACE_END

#endif // LIMAGE_H
