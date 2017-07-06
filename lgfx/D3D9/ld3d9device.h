#ifndef LD3D9DEVICE_H
#define LD3D9DEVICE_H

#include "lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"

#include "lcore.h"
#include "../lgfxdevice.h"
#include "ld3d9vertexbuffer.h"
#include "ld3d9indexbuffer.h"
#include "ld3d9shader.h"
#include "ld3d9texture.h"

LNAMESPACE_BEGIN



LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);

class LAPI LD3D9Device:public LGFXDevice
{
    friend class LD3D9VertexDeclaration;
    friend class LD3D9Shader;
    friend class LD3D9VertexBuffer;
    friend class LD3D9IndexBuffer;
    friend class LD3D9Texture;
public:
    LD3D9Device();
    virtual ~LD3D9Device();

    virtual void                    beginScene();

    virtual void                    clear(int _r,int _g,int _b,bool _backbuffer, bool _zbuffer, bool _stencil,float _depthval,u8 _stencilval);

    virtual LGFXVertexDeclaration*  createVertexDeclaration(const LVector<LVertexElement> &_elements);

    virtual LGFXVertexBuffer*       createVertexBuffer(bool _is_dynamic, bool _has_memory_copy);

    virtual LGFXIndexBuffer*        createIndexBuffer(bool _has_memory_copy);

    virtual LGFXShader*             createVertexShader();

    virtual LGFXShader*             createPixelShader();

    virtual LGFXTexture*            createTexture(u16 _width,u16 _height,u16 _mipmap_count,LImage::Format _format);

    virtual void                    draw();

    virtual void                    endScene();

    virtual void                    hideWindow();

    virtual void                    initialize(bool _fullscreen,bool _vsync);

    virtual u8                      processOSMessage();

    virtual void                    render();

    virtual void                    release();

    virtual void                    setTitle(const LString& _newname);

    virtual void                    setVertexDeclaration(const LGFXVertexDeclaration *_decl);

    virtual void                    setVertexBuffer(u16 _streamNumber,LGFXVertexBuffer* _buffer);

    virtual void                    setIndexBuffer(LGFXIndexBuffer *_buffer);

    virtual void                    setVertexShader(LGFXShader* _shader);

    virtual void                    setPixelShader(LGFXShader *_shader);

    virtual void                    setTexture(u32 _sampler,LGFXTexture* _t);

    virtual void                    showWindow();

protected:
    HWND                mWindowHandler;
    IDirect3D9*         mD3D9;
    IDirect3DDevice9*   mDevice;

    LD3D9VertexBuffer*  mCurrentVertexBuffer;
    LD3D9IndexBuffer*   mCurrentIndexBuffer;
};

LNAMESPACE_END

#endif // LGFX

#endif // LD3D9DEVICE_H
