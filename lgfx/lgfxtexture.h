#ifndef LGFXTEXTURE_H
#define LGFXTEXTURE_H

#include "lcore.h"
#include "limage.h"

LNAMESPACE_BEGIN

//! class to hold textures
class LAPI LGFXTexture
{
public:
    enum TextureType
    {
        TextureType_2D,
        TextureType_RenderTarget
    };
    enum TextureFilter
    {
        TextureFilter_none,
        TextureFilter_point,
        TextureFilter_linear,
        TextureFilter_anisotropic
    };
    enum TextureAddress
    {
        TextureAddress_wrap,
        TextureAddress_mirror,
        TextureAddress_clamp,
        TextureAddress_border
    };

public:
    LGFXTexture();
    virtual ~LGFXTexture();

    //! destroy
    virtual void                    destroy()=0;

    //! Generate mip maps (if availble)
    virtual void                    generateMipMaps()=0;

    //! get Type of texture
    virtual TextureType             getType();

    //! get Filter type
    virtual TextureFilter           getFilter();

    //! get Max Value for Anistropic
    virtual int                     getMaxAnisotropic() const;

    //! get MipMap bias
    virtual float                   getMipMapBias() const;

    //! get max mip map level
    virtual int                     getMaxMipMapLevel() const;

    //! get UV addressing for UV.u
    virtual TextureAddress          getAddressU() const;

    //! get UV addressing for UV.v
    virtual TextureAddress          getAddressV() const;

    //! check texture has nothing
    virtual bool                    isNull()const;

    //! before device reset
    virtual void                    preReset()=0;

    //! after device reset
    virtual void                    postReset()=0;

    //! set filter type
    virtual void                    setFilter(TextureFilter _f);

    //! set max anistropic value
    virtual void                    setMaxAnisotropic(int _in=1);

    //! set mip map bias
    virtual void                    setMipMapBias(float mipMapBias=0.0f);

    //! set max mipmap level
    virtual void                    setMaxMipMapLevel(int maxMipMapLevel=0);

    //! set UV addressing UV.u
    virtual void                    setAddressU(const TextureAddress &addressU);

    //! set UV addressing UV.v
    virtual void                    setAddressV(const TextureAddress &addressV);

    //! update texture content
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
    TextureAddress  mAddressU;
    TextureAddress  mAddressV;
    bool            mIsRenderTarget;
};

LNAMESPACE_END

#endif // LGFXTEXTURE_H
