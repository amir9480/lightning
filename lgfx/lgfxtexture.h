#ifndef LGFXTEXTURE_H
#define LGFXTEXTURE_H

#include "../lcore/ldefines.h"
#include "limage.h"

LNAMESPACE_BEGIN

//! class to hold textures
class LAPI LGFXTexture
{
    LNONCOPYABLE_CLASS(LGFXTexture)
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
        TextureFilter_anisotropic2,
        TextureFilter_anisotropic4,
        TextureFilter_anisotropic8,
        TextureFilter_anisotropic16
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

    //! copy from this texture to another . when _other is render target do device->resetParameters before call this
    virtual void                    copyTo(LGFXTexture* _other)=0;

    //! destroy
    virtual void                    destroy()=0;

    //! Generate mip maps (if availble)
    virtual void                    generateMipMaps()=0;

    //! get Type of texture
    virtual TextureType             getType();

    //! get Filter type
    virtual TextureFilter           getFilter();

    //! get MipMap bias
    virtual float                   getMipMapBias() const;

    //! get max mip map level
    virtual int                     getMaxMipMapLevel() const;

    //! get UV addressing for UV.u
    virtual TextureAddress          getAddressU() const;

    //! get UV addressing for UV.v
    virtual TextureAddress          getAddressV() const;

    //! get Width of texture
    virtual u16                     getWidth() const;

    //! get Height of texture
    virtual u16                     getHeight() const;

    //! get mipmap count
    virtual u16                     getMipMapCount() const;

    //! get Texture format
    virtual LImage::Format          getFormat() const;

    //! get content of this texture
    virtual LImage                  getImage(u16 _mip_map_level=0)=0;

    //! check is this Render Target Has Depth Buffer
    virtual bool                    hasDepthBuffer()const=0;

    //! check texture is render target
    virtual bool                    isRenderTarget()const=0;

    //! check texture has nothing
    virtual bool                    isNull()const;

    //! before device reset . Note : Render targets will lose their content
    virtual void                    preReset()=0;

    //! after device reset
    virtual void                    postReset()=0;

    //! set filter type
    virtual void                    setFilter(TextureFilter _f);

    //! set mip map bias
    virtual void                    setMipMapBias(float mipMapBias=0.0f);

    //! set max mipmap level
    virtual void                    setMaxMipMapLevel(int maxMipMapLevel=0);

    //! set both address UV
    virtual void                    setAddress(const TextureAddress &address);

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
    TextureAddress  mAddressU;
    TextureAddress  mAddressV;
    bool            mIsRenderTarget;
};

LNAMESPACE_END

#endif // LGFXTEXTURE_H
