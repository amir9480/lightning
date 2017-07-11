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
    enum TextureFilter
    {
        TextureFilter_none,
        TextureFilter_point,
        TextureFilter_linear,
        TextureFilter_anisotropic
    };

public:
    LGFXTexture();
    virtual ~LGFXTexture();


    virtual void                    destroy()=0;

    virtual void                    generateMipMaps()=0;

    virtual TextureType             getType();

    virtual TextureFilter           getFilter();

    virtual int                     getMaxAnisotropic() const;

    virtual float                   getMipMapBias() const;

    virtual int                     getMaxMipMapLevel() const;

    virtual void                    preReset()=0;

    virtual void                    postReset()=0;

    virtual void                    setFilter(TextureFilter _f);

    virtual void                    setMaxAnisotropic(int _in=1);

    virtual void                    setMipMapBias(float mipMapBias=0.0f);

    virtual void                    setMaxMipMapLevel(int maxMipMapLevel=0);

    virtual void                    updateTexture(u16 _mip_map_level,const LImage& _data)=0;

protected:
    u16             mWidth;
    u16             mHeight;
    u16             mMipMapCount;
    LImage::Format  mFormat;
    TextureType     mType;
    TextureFilter   mFilter;
    float           mMipMapBias;
    int             mMaxMipMapLevel;
    int             mMaxAnisotropic;
};

LNAMESPACE_END

#endif // LGFXTEXTURE_H
