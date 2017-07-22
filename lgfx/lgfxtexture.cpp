#include "lgfxtexture.h"

LNAMESPACE_BEGIN

LGFXTexture::LGFXTexture():
    mFilter(TextureFilter_linear),
    mMipMapBias(0),
    mMaxMipMapLevel(0),
    mMaxAnisotropic(1),
    mAddressU(TextureAddress_wrap),
    mAddressV(TextureAddress_wrap)
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

int LGFXTexture::getMaxAnisotropic() const
{
    return mMaxAnisotropic;
}

void LGFXTexture::setFilter(LGFXTexture::TextureFilter _f)
{
    mFilter=_f;
}

void LGFXTexture::setMaxAnisotropic(int _in)
{
    mMaxAnisotropic=_in;
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


LNAMESPACE_END
