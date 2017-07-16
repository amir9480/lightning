#ifndef LGFXDEVICE_H
#define LGFXDEVICE_H

#include "lcore.h"
#include "lgfxvertexbuffer.h"
#include "lgfxindexbuffer.h"
#include "lgfxshader.h"
#include "lgfxtexture.h"

LNAMESPACE_BEGIN

//! To create a Graphic Device . ( use LGFXDevice::create )
class LAPI LGFXDevice
{
public:
    LGFXDevice();
    virtual ~LGFXDevice();

    //! create a new renderable window
    static LGFXDevice*              create();

    //! to start rendering
    virtual void                    beginScene()=0;

    //! clear back buffer | depth buffer | stencil buffer
    virtual void                    clear(int _r=0,int _g=0,int _b=0,bool _backbuffer=true,bool _zbuffer=true,bool _stencil=true,float _depthval=1.0f,u8 _stencilval=0)=0;

    //! create a vertex declaration
    virtual LGFXVertexDeclaration*  createVertexDeclaration(const LVector<LVertexElement>& _elements)=0;

    //! create a vertex buffer  _is_dynamic: dynamic or not  . _has_memory_copy = copy on RAM ( for read frequency vertex buffers and getMemoryVertices function )
    virtual LGFXVertexBuffer*       createVertexBuffer(bool _is_dynamic=false,bool _has_memory_copy=false)=0;

    //! create a index buffer
    virtual LGFXIndexBuffer*        createIndexBuffer(bool _has_memory_copy=false)=0;

    //! create a vertex shader
    virtual LGFXShader*             createVertexShader()=0;

    //! create a pixel shader
    virtual LGFXShader*             createPixelShader()=0;

    //! create a texture . _mipmap_count : Count of mip maps
    virtual LGFXTexture*            createTexture(u16 _width,u16 _height,u16 _mipmap_count,LImage::Format _format)=0;

    //! draw stage
    virtual void                    draw()=0;

    //! to end scene before render on screen
    virtual void                    endScene()=0;

    //! hide rendering window
    virtual void                    hideWindow()=0;

    //! initilize device
    virtual void                    initialize(bool _fullscreen,bool _vsync)=0;

    //! if process done returns 1 and if request was Quit returns 2
    virtual u8                      processOSMessage()=0;

    //! render on screen
    virtual void                    render()=0;

    //! release
    virtual void                    release()=0;

    //! set rendering window title
    virtual void                    setTitle(const LString& _newname)=0;

    //! set current vertex declration
    virtual void                    setVertexDeclaration(const LGFXVertexDeclaration* _decl)=0;

    //! set current vertex buffer
    virtual void                    setVertexBuffer(u16 _streamNumber,LGFXVertexBuffer *_buffer)=0;

    //! set current index buffer
    virtual void                    setIndexBuffer(LGFXIndexBuffer* _buffer)=0;

    //! set current vertex shader
    virtual void                    setVertexShader(LGFXShader* _shader)=0;

    //! set current pixel shader
    virtual void                    setPixelShader(LGFXShader* _shader)=0;

    //! set current texture
    virtual void                    setTexture(u32 _sampler,LGFXTexture* _t)=0;

    //! show rendering window
    virtual void                    showWindow()=0;

protected:
    LVector<LGFXVertexDeclaration*> mVertexDecls;
    LVector<LGFXVertexBuffer*>      mVertexBuffers;
    LVector<LGFXIndexBuffer*>       mIndexBuffers;
    LVector<LGFXShader*>            mShaders;
    LVector<LGFXTexture*>           mTextures;
};

LNAMESPACE_END

#endif // LGFXDEVICE_H
