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

struct D3D9QuadVertex
{
    LVector3 pos;
    LVector2 uv;
    static LGFXVertexDeclaration* decl;
};
extern LVector<LVertexElement> _d3d9quad_decl;

extern D3D9QuadVertex _d3d9quad_vertex[];
extern LVector<u32> _d3d9quad_index;

extern const char* _d3d9quadshader;

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

    virtual LGFXTexture*            createTexture(u16 _width,u16 _height,LImage::Format _format,u16 _mipmap_count);

    virtual LGFXTexture*            createRenderTarget(u16 _width,u16 _height,LImage::Format _renderable_format);

    virtual void                    draw();

    virtual void                    drawQuad(LGFXTexture *_tex);

    virtual void                    endScene();

    virtual LImage                  getScreenShot();

    virtual void                    hideWindow();

    virtual void                    initialize(bool _fullscreen,bool _vsync);

    virtual bool                    processOSMessage();

    virtual void                    render();

    virtual void                    release();

    virtual void                    setTitle(const LString& _newname);

    virtual void                    setVertexDeclaration(LGFXVertexDeclaration *_decl);

    virtual void                    setVertexBuffer(u16 _streamNumber,LGFXVertexBuffer* _buffer);

    virtual void                    setVertexBufferFrequency(u16 _streamNumber,int _count);

    virtual void                    setIndexBuffer(LGFXIndexBuffer *_buffer);

    virtual void                    setVertexShader(LGFXShader* _shader);

    virtual void                    setPixelShader(LGFXShader *_shader);

    virtual void                    setTexture(u32 _sampler,LGFXTexture* _t);

    virtual void                    setRenderTarget(u32 _index,LGFXTexture* _rt);

    virtual void                    setDepthCheckEnable(bool _value);

    virtual void                    setDepthCheckFunction(LGFXCompareFunction _val=LGFXCompareFunction_LessEqual);

    virtual void                    setDepthWriteEnable(bool _value);

    virtual void                    setDepthBias(f32 _val);

    virtual void                    setBackBufferWriteEnable(bool _val);

    virtual void                    setFillMode(LGFXFillMode _type);

    virtual void                    setCullMode(LGFXCullMode _mode);

    virtual void                    setAlphaBlending(bool _value);

    virtual void                    setStencilEnable(bool _value);

    virtual void                    setStencilValue (i32 _value);

    virtual void                    setStencilCheckFunction(LGFXCompareFunction _f);

    virtual void                    setStencilFailOperation(LGFXStencilOperation _o);

    virtual void                    setStencilDepthFailOperation(LGFXStencilOperation _o);

    virtual void                    setStencilPassOperation(LGFXStencilOperation _o);

    virtual void                    showWindow();

protected:
    HWND                        mWindowHandler;
    IDirect3D9*                 mD3D9;
    IDirect3DDevice9*           mDevice;

    LD3D9VertexBuffer*          mCurrentVertexBuffer;
    LD3D9IndexBuffer*           mCurrentIndexBuffer;
    LD3D9VertexDeclaration*     mCurrentVertexDecl;
    LD3D9Shader*                mCurrentVertexShader;
    LD3D9Shader*                mCurrentPixelShader;


    IDirect3DSurface9*          mNativeBackBuffer;
    LD3D9Texture*               mMainBackBuffer;
    LD3D9VertexBuffer*          mQuadVertexBuffer;
    LD3D9IndexBuffer*           mQuadIndexBuffer;
    LD3D9Shader*                mQuadVertexShader;
    LD3D9Shader*                mQuadPixelShader;
};

LNAMESPACE_END

#endif // LGFX

#endif // LD3D9DEVICE_H
