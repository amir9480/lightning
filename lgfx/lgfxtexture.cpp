#include "lgfxtexture.h"

LNAMESPACE_BEGIN

LGFXTexture::LGFXTexture():
    mFilter(TextureFilter_linear),
    mMipMapBias(0),
    mMaxMipMapLevel(0),
    mAddressU(TextureAddress_wrap),
    mAddressV(TextureAddress_wrap),
    mIsRenderTarget(false)
{

}

LGFXTexture::~LGFXTexture()
{

}

LGFXTexture::TextureType LGFXTexture::getType()
{
    return mType;
}

LGFXTexture::TextureFilter LGFXTexture::getFilter()
{
    return mFilter;
}

void LGFXTexture::setFilter(LGFXTexture::TextureFilter _f)
{
    mFilter=_f;
}
float LGFXTexture::getMipMapBias() const
{
    return mMipMapBias;
}

void LGFXTexture::setMipMapBias(float mipMapBias)
{
    mMipMapBias = mipMapBias;
}

int LGFXTexture::getMaxMipMapLevel() const
{
    return mMaxMipMapLevel;
}

void LGFXTexture::setMaxMipMapLevel(int maxMipMapLevel)
{
    mMaxMipMapLevel = maxMipMapLevel;
}

void LGFXTexture::setAddress(const LGFXTexture::TextureAddress &address)
{
    setAddressU(address);
    setAddressV(address);
}

LGFXTexture::TextureAddress LGFXTexture::getAddressU() const
{
    return mAddressU;
}

void LGFXTexture::setAddressU(const TextureAddress &addressU)
{
    mAddressU = addressU;
}

LGFXTexture::TextureAddress LGFXTexture::getAddressV() const
{
    return mAddressV;
}

bool LGFXTexture::isNull() const
{
    if(mWidth==0||mHeight==0||mMipMapCount==0||mFormat==LImage::Format_null)
        return true;
    return false;
}

void LGFXTexture::setAddressV(const TextureAddress &addressV)
{
    mAddressV = addressV;
}

u16 LGFXTexture::getWidth() const
{
    return mWidth;
}

u16 LGFXTexture::getHeight() const
{
    return mHeight;
}

u16 LGFXTexture::getMipMapCount() const
{
    return mMipMapCount;
}

LImage::Format LGFXTexture::getFormat() const
{
    return mFormat;
}


LNAMESPACE_END
