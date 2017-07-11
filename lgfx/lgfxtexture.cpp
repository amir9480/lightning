#include "lgfxtexture.h"

LNAMESPACE_BEGIN

LGFXTexture::LGFXTexture():
    mFilter(TextureFilter_linear),
    mMipMapBias(0),
    mMaxMipMapLevel(0),
    mMaxAnisotropic(1)
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


LNAMESPACE_END
