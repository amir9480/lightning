#include "ld3d9texture.h"
#include "ld3d9device.h"

#if ( LGFX == LGFX_D3D9 )

LNAMESPACE_BEGIN

D3DFORMAT lD3DTextureFormat(LImage::Format _f)
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

D3DTEXTUREFILTERTYPE lD3DTextureFilter(LGFXTexture::TextureFilter _f)
{
    switch (_f) {
    case LGFXTexture::TextureFilter_none:
        return D3DTEXF_NONE;
    case LGFXTexture::TextureFilter_point:
        return D3DTEXF_POINT;
    case LGFXTexture::TextureFilter_linear:
        return D3DTEXF_LINEAR;
    case LGFXTexture::TextureFilter_anisotropic2:case LGFXTexture::TextureFilter_anisotropic4:case LGFXTexture::TextureFilter_anisotropic8:case LGFXTexture::TextureFilter_anisotropic16:
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
    mTexture(nullptr),
    mHasDepthBuffer(false),
    mRenderTargetDepthStencil(nullptr)
{

}

LD3D9Texture::~LD3D9Texture()
{
    u32 _i;
    if((_i = mDevice->mTextures.find(this))==LVector<LD3D9Texture>::nothing)
        return;
    mDevice->mTextures.remove(_i);
    this->destroy();
}

void LD3D9Texture::copyTo(LGFXTexture *_other)
{
    LD3D9Texture* other = (LD3D9Texture*)(_other);
    lError(_other==nullptr,"LD3D9Texture::copyTo : something is wrong");

    switch(mType)
    {
    case TextureType_2D:
    {
        if(other->mType==TextureType_2D)
        {
            D3DLOCKED_RECT r1;
            D3DLOCKED_RECT r2;
            HR(mTexture->LockRect(0,&r1,0,D3DLOCK_DISCARD));
            HR(other->mTexture->LockRect(0,&r2,0,D3DLOCK_DISCARD));
            switch(mFormat)
            {
            case LImage::Format_R8G8B8:case LImage::Format_R8G8B8A8:
                for(u32 i=0;i<((u32)other->mWidth)*((u32)other->mHeight)*((u32)4);i++)
                {
                    ((char*)r2.pBits)[i]=((char*)r1.pBits)[i];
                }
                break;
            case LImage::Format_null:
                lError(1,"LD3D9Texture::copyTo . format is null!");
                break;
            }

            HR(mTexture->UnlockRect(0));
            HR(other->mTexture->UnlockRect(0));
        }
        else if(other->mType==TextureType_RenderTarget)
        {
            mDevice->setRenderTarget(0,other);
            mDevice->drawQuad(this);
            mDevice->setRenderTarget(0,0);
        }
        break;
    }
    case TextureType_RenderTarget:
    {
        if(other->mType==TextureType_2D)
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
                lError(1,"LD3D9Texture::copyTo : format is null");
            }
            HR(mDevice->mDevice->CreateTexture(mWidth,mHeight,1,D3DUSAGE_DYNAMIC,_tfmt,D3DPOOL_SYSTEMMEM,&_temp,0));

            HR(_temp->GetSurfaceLevel(0,&_dests));
            HR(mTexture->GetSurfaceLevel(0,&_srcs));
            HR(mDevice->mDevice->GetRenderTargetData(_srcs,_dests));

            D3DLOCKED_RECT r1;
            D3DLOCKED_RECT r2;
            HR(other->mTexture->LockRect(0,&r1,0,D3DLOCK_DISCARD));
            HR(_temp->LockRect(0,&r2,0,D3DLOCK_READONLY));
            switch(mFormat)
            {
            case LImage::Format_R8G8B8:case LImage::Format_R8G8B8A8:
                for(u32 i=0;i<((u32)other->mWidth)*((u32)other->mHeight)*((u32)4);i++)
                {
                    ((char*)r1.pBits)[i]=((char*)r2.pBits)[i];
                }
                break;
            case LImage::Format_null:
                lError(1,"LD3D9Texture::copyTo . format is null!");
                break;
            }
            HR(_temp->UnlockRect(0));
            HR(other->mTexture->UnlockRect(0));

            SAFE_RELEASE(_temp);
            SAFE_RELEASE(_srcs);
            SAFE_RELEASE(_dests);
            break;
        }
        else if(other->mType==TextureType_RenderTarget)
        {
            mDevice->setRenderTarget(0,other);
            mDevice->drawQuad(this);
            mDevice->setRenderTarget(0,0);
        }
        break;
    }
    }
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

        SAFE_RELEASE(_temp);
        SAFE_RELEASE(_srcs);
        SAFE_RELEASE(_dests);
        break;
    }
    }
    return o;
}

bool LD3D9Texture::hasDepthBuffer() const
{
    return mHasDepthBuffer;
}

bool LD3D9Texture::isRenderTarget() const
{
    return mIsRenderTarget;
}

void LD3D9Texture::destroy()
{
    SAFE_RELEASE(mTexture);
    SAFE_RELEASE(mRenderTargetDepthStencil);
    mWidth=mHeight=mMipMapCount=0;
    mFormat=LImage::Format_null;
}

void LD3D9Texture::preReset()
{
    if(mType==TextureType_RenderTarget&&mIsRenderTarget==true)
    {
        SAFE_RELEASE(mTexture);
        SAFE_RELEASE(mRenderTargetDepthStencil);
    }
}

void LD3D9Texture::postReset()
{
    if(mType==TextureType_RenderTarget&&mIsRenderTarget==true)
    {
        HR(mDevice->mDevice->CreateTexture(mWidth,mHeight,1,D3DUSAGE_RENDERTARGET,lD3DTextureFormat(mFormat),D3DPOOL_DEFAULT,(IDirect3DTexture9**)(&(mTexture)),0));
        if(mHasDepthBuffer)
            HR(mDevice->mDevice->CreateDepthStencilSurface(mWidth,mHeight,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,0,&mRenderTargetDepthStencil,0));
    }
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
