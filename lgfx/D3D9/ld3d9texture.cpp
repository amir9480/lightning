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
    case LImage::Format_R8G8B8:
        return D3DFMT_X8R8G8B8;
    }
    return D3DFMT_UNKNOWN;
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
