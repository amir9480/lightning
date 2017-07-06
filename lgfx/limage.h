#ifndef LIMAGE_H
#define LIMAGE_H

#include "lcore.h"

LNAMESPACE_BEGIN

class LImage
{
public:
    enum Format
    {
        Format_null=0,

        Format_R8G8B8,
        Format_A8R8G8B8,

    };

    struct Pixel_R8G8B8
    {
        u8 __,r,g,b;
    };

    struct Pixel_A8R8G8B8
    {
        u8 a,r,g,b;
    };

public:
    LImage();
    virtual ~LImage();


    static u16      bytePerPixel(Format _type);

    void            destroy();

    char*           getData();

    const char*     getData()const;

    u16             getWidth() const;

    u16             getHeight() const;

    u16             getBytePerPixel() const;

    u64             getPixelsCount()const;

    Format          getFormat() const;

    void            init(u16 _width,u16 _height,Format _type);



protected:
    char*   mData;
    u16     mWidth;
    u16     mHeight;
    u16     mBytePerPixel;
    Format  mFormat;
};

LNAMESPACE_END

#endif // LIMAGE_H
