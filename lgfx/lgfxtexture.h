#ifndef LGFXTEXTURE_H
#define LGFXTEXTURE_H

#include "lcore.h"
#include "limage.h"

LNAMESPACE_BEGIN

class LGFXTexture
{
public:
    enum TextureType
    {
        TextureType_2D
    };

public:
    LGFXTexture();
    virtual ~LGFXTexture();

    virtual void                    destroy()=0;

    virtual void                    preReset()=0;

    virtual void                    postReset()=0;

    virtual void                    updateTexture(u16 _mip_map_level,const LImage& _data)=0;

protected:
    u16             mWidth;
    u16             mHeight;
    u16             mMipMapCount;
    LImage::Format  mFormat;
    TextureType     mType;

};

LNAMESPACE_END

#endif // LGFXTEXTURE_H
