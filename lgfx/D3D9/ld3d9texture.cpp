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
    }
    return D3DTEXF_NONE;
}

D3DTEXTUREADDRESS lD3DTextureAddress(LGFXTexture::TextureAddress _a)
{
    switch (_a) {
    case LGFXTexture::TextureAddress_wrap:
        return D3DTADDRESS_WRAP;
    case LGFXTexture::TextureAddress_clamp:
        return D3DTADDRESS_CLAMP;
    case LGFXTexture::TextureAddress_mirror:
        return D3DTADDRESS_MIRROR;
    case LGFXTexture::TextureAddress_border:
        return D3DTADDRESS_BORDER;
    }
    return D3DTADDRESS_WRAP;
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
    lError(_data.getWidth()==0||_data.getHeight()==0||_mip_map_level>=mMipMapCount||_data.getFormat()==LImage::Format_null,"Some thing is wrong");
    D3DLOCKED_RECT r;
    HR(mTexture->LockRect(_mip_map_level,&r,0,D3DLOCK_DISCARD));

    lMemoryCopy(r.pBits,_data.getData(),_data.getPixelsCount()*_data.getBytePerPixel());

    HR(mTexture->UnlockRect(_mip_map_level));
}





LNAMESPACE_END

#endif // LGFX == LGFX_D3D9
