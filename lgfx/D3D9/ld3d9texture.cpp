#include "ld3d9texture.h"
#include "ld3d9device.h"

#if ( LGFX == LGFX_D3D9 )

LNAMESPACE_BEGIN


D3DFORMAT lD3DTextureFormat(LImage::Format _f)
{
    switch (_f) {
    case LImage::Format_null:
        return D3DFMT_UNKNOWN;
    case LImage::Format_A8R8G8B8:
        return D3DFMT_A8R8G8B8;
    case LImage::Format_X8R8G8B8:
        return D3DFMT_X8R8G8B8;
    }
    return D3DFMT_UNKNOWN;
}

D3DTEXTUREFILTERTYPE lD3DTextureFilter(LGFXTexture::TextureFilter _f)
{
    switch (_f) {
    case LGFXTexture::TextureFilter_none:
        return D3DTEXF_NONE;
    case LGFXTexture::TextureFilter_point:
        return D3DTEXF_POINT;
    case LGFXTexture::TextureFilter_linear:
        return D3DTEXF_LINEAR;
    case LGFXTexture::TextureFilter_anisotropic:
        return D3DTEXF_ANISOTROPIC;
    default:
        break;
    }
    return D3DTEXF_NONE;
}

LD3D9Texture::LD3D9Texture():
    mDevice(nullptr),
    mTexture(nullptr)
{

}

LD3D9Texture::~LD3D9Texture()
{
    this->destroy();
}

void LD3D9Texture::generateMipMaps()
{
    mTexture->GenerateMipSubLevels();
}

void LD3D9Texture::destroy()
{
    SAFE_RELEASE(mTexture);
    mWidth=mHeight=mMipMapCount=0;
    mFormat=LImage::Format_null;
}

void LD3D9Texture::preReset()
{

}

void LD3D9Texture::postReset()
{

}

void LD3D9Texture::updateTexture(u16 _mip_map_level, const LImage &_data)
{
    D3DLOCKED_RECT r;
    HR(mTexture->LockRect(_mip_map_level,&r,0,D3DLOCK_DISCARD));

    lMemoryCopy(r.pBits,_data.getData(),_data.getPixelsCount()*_data.getBytePerPixel());

    HR(mTexture->UnlockRect(_mip_map_level));
}




LNAMESPACE_END

#endif // LGFX == LGFX_D3D9
