#ifndef LIMAGE_H
#define LIMAGE_H

#include "lcore.h"

#if LIGHTNING_IMAGE_PNG
#include <png.h>
#endif

LNAMESPACE_BEGIN

class LAPI LImage
{
public:
    enum Format
    {
        Format_null=0,

        // Remeber this channels are reserved on DX9
        Format_X8R8G8B8,
        Format_A8R8G8B8,

    };

public:
    LImage();
    LImage(const LImage& _other);
    LImage(LImage&& _other);
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

    bool            isNull()const;

#if LIGHTNING_IMAGE_PNG
    static LImage   loadFromPng(char* _data);
    static LImage   loadFromPngFile(const LString& _fileName);
#endif

    LImage& operator=(const LImage& _other);

    LImage&& operator=(LImage&& _other);

protected:
    char*   mData;
    u16     mWidth;
    u16     mHeight;
    u16     mBytePerPixel;
    Format  mFormat;
};

LNAMESPACE_END

#endif // LIMAGE_H
