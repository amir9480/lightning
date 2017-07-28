#include "ld3d9texture.h"
#include "ld3d9device.h"

#if ( LGFX == LGFX_D3D9 )

LNAMESPACE_BEGIN

D3DFORMAT LAPI lD3DTextureFormat(LImage::Format _f)
{
    switch (_f) {
    case LImage::Format_null:
        return D3DFMT_UNKNOWN;
    case LImage::Format_R8G8B8A8:
        return D3DFMT_A8R8G8B8;
    case LImage::Format_R8G8B8:
        return D3DFMT_X8R8G8B8;
    }
    return D3DFMT_UNKNOWN;
}

D3DTEXTUREFILTERTYPE LAPI lD3DTextureFilter(LGFXTexture::TextureFilter _f)
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

D3DTEXTUREADDRESS LAPI lD3DTextureAddress(LGFXTexture::TextureAddress _a)
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
    lError(mMipMapCount>1,"generateMipMaps Error . use mipmap =1 on CreateTextureFunction");
    mTexture->GenerateMipSubLevels();
}

LImage LD3D9Texture::getImage(u16 _mip_map_level)
{
    LImage o;
    o.init(mWidth,mHeight,mFormat);

    switch(mType)
    {
    case TextureType_2D:
    {
        D3DLOCKED_RECT r;
        HR(mTexture->LockRect(_mip_map_level,&r,0,D3DLOCK_READONLY));

        switch(mFormat)
        {
        case LImage::Format_R8G8B8:
            for(u32 i=0;i<o.getPixelsCount();i++)
            {
                o.getData()[i*3+2]=((char*)r.pBits)[i*4+0];
                o.getData()[i*3+1]=((char*)r.pBits)[i*4+1];
                o.getData()[i*3+0]=((char*)r.pBits)[i*4+2];
            }
            break;
        case LImage::Format_R8G8B8A8:
            for(u32 i=0;i<o.getPixelsCount();i++)
            {
                o.getData()[i*4+2]=((char*)r.pBits)[i*4+0];
                o.getData()[i*4+1]=((char*)r.pBits)[i*4+1];
                o.getData()[i*4+0]=((char*)r.pBits)[i*4+2];
                o.getData()[i*4+3]=((char*)r.pBits)[i*4+3];
            }
            break;
        case LImage::Format_null:
            lError(1,"LD3D9Texture::getImage : format is null",o);
        }

        HR(mTexture->UnlockRect(_mip_map_level));
        break;
    }
    case TextureType_RenderTarget:
    {
        IDirect3DTexture9* _temp;
        D3DFORMAT _tfmt;
        IDirect3DSurface9* _dests;
        IDirect3DSurface9* _srcs;

        switch(mFormat)
        {
        case LImage::Format_R8G8B8:
            _tfmt = D3DFMT_X8R8G8B8;
            break;
        case LImage::Format_R8G8B8A8:
            _tfmt = D3DFMT_A8R8G8B8;
            break;
        case LImage::Format_null:
            lError(1,"LD3D9Texture::getImage : format is null",o);
        }
        HR(mDevice->mDevice->CreateTexture(mWidth,mHeight,1,D3DUSAGE_DYNAMIC,_tfmt,D3DPOOL_SYSTEMMEM,&_temp,0));

        HR(_temp->GetSurfaceLevel(0,&_dests));
        HR(mTexture->GetSurfaceLevel(0,&_srcs));
        HR(mDevice->mDevice->GetRenderTargetData(_srcs,_dests));

        D3DLOCKED_RECT r;
        HR(_temp->LockRect(_mip_map_level,&r,0,D3DLOCK_READONLY));
        switch(mFormat)
        {
        case LImage::Format_R8G8B8:
            for(u32 i=0;i<o.getPixelsCount();i++)
            {
                o.getData()[i*3+2]=((char*)r.pBits)[i*4+0];
                o.getData()[i*3+1]=((char*)r.pBits)[i*4+1];
                o.getData()[i*3+0]=((char*)r.pBits)[i*4+2];
            }
            break;
        case LImage::Format_R8G8B8A8:
            for(u32 i=0;i<o.getPixelsCount();i++)
            {
                o.getData()[i*4+2]=((char*)r.pBits)[i*4+0];
                o.getData()[i*4+1]=((char*)r.pBits)[i*4+1];
                o.getData()[i*4+0]=((char*)r.pBits)[i*4+2];
                o.getData()[i*4+3]=((char*)r.pBits)[i*4+3];
            }
            break;
        default:
            break;
        }
        HR(_temp->UnlockRect(_mip_map_level));

        HR(_temp->Release());
        break;
    }
    }
    return o;
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

    switch (_data.getFormat())
    {
    case LImage::Format_R8G8B8:
        for(u32 i=0;i<_data.getPixelsCount();i++)
        {
            ((char*)r.pBits)[i*4+0]=_data.getData()[i*3+2];
            ((char*)r.pBits)[i*4+1]=_data.getData()[i*3+1];
            ((char*)r.pBits)[i*4+2]=_data.getData()[i*3+0];
            ((char*)r.pBits)[i*4+3]=0;
        }
        break;
    case LImage::Format_R8G8B8A8:
        for(u32 i=0;i<_data.getPixelsCount();i++)
        {
            ((char*)r.pBits)[i*4+0]=_data.getData()[i*4+2];
            ((char*)r.pBits)[i*4+1]=_data.getData()[i*4+1];
            ((char*)r.pBits)[i*4+2]=_data.getData()[i*4+0];
            ((char*)r.pBits)[i*4+3]=_data.getData()[i*4+3];
        }
        break;
    case LImage::Format_null:
        lError(1,"LD3D9Texture::updateTexture : format is null");
    }

    //lMemoryCopy(r.pBits,_data.getData(),_data.getPixelsCount()*_data.getBytePerPixel());

    HR(mTexture->UnlockRect(_mip_map_level));
    generateMipMaps();
}





LNAMESPACE_END

#endif // LGFX == LGFX_D3D9
