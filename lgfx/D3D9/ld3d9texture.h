#ifndef LD3D9TEXTURE_H
#define LD3D9TEXTURE_H

#include "../../lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"

#include "../../lcore.h"
#include "../lgfxtexture.h"

LNAMESPACE_BEGIN

D3DFORMAT               lD3DTextureFormat(LImage::Format _f);
D3DTEXTUREFILTERTYPE    lD3DTextureFilter(LGFXTexture::TextureFilter _f);
D3DTEXTUREADDRESS       lD3DTextureAddress(LGFXTexture::TextureAddress _a);

class LD3D9Device;

class LAPI LD3D9Texture:public LGFXTexture
{
    friend class LD3D9Device;
public:
    LD3D9Texture();
    virtual ~LD3D9Texture();

    virtual void copyTo(LGFXTexture* _other);

    virtual void destroy();

    virtual void generateMipMaps();

    virtual LImage getImage(u16 _mip_map_level=0);

    virtual bool hasDepthBuffer()const;

    virtual bool isRenderTarget()const;

    virtual void preReset();

    virtual void postReset();

    virtual void updateTexture(u16 _mip_map_level,const LImage& _data);

protected:
    LD3D9Device*        mDevice;
    IDirect3DTexture9*  mTexture;

    bool                mHasDepthBuffer;
    IDirect3DSurface9*  mRenderTargetDepthStencil;

    LD3D9Texture*       mTemp;// temp for reset render targets
};


LNAMESPACE_END

#endif // LGFX == LGFX_D3D9

#endif // LD3D9TEXTURE_H
