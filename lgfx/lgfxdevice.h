#ifndef LGFXDEVICE_H
#define LGFXDEVICE_H

#include "lcore.h"
#include "lgfxvertexbuffer.h"
#include "lgfxindexbuffer.h"
#include "lgfxshader.h"
#include "lgfxtexture.h"

LNAMESPACE_BEGIN

enum LGFXFillMode
{
    LGFXFillMode_Point,
    LGFXFillMode_Wireframe,
    LGFXFillMode_Solid
};

enum LGFXCullMode
{
    LGFXCullMode_None,
    LGFXCullMode_Clockwise,
    LGFXCullMode_CounterClockwise
};

enum LGFXCompareFunction
{
    LGFXCompareFunction_Never,
    LGFXCompareFunction_Less,
    LGFXCompareFunction_Equal,
    LGFXCompareFunction_LessEqual,
    LGFXCompareFunction_Greater,
    LGFXCompareFunction_NotEqual,
    LGFXCompareFunction_GreaterEqual,
    LGFXCompareFunction_Always
};

enum LGFXStencilOperation
{
    LGFXStencilOperation_Keep,
    LGFXStencilOperation_Zero,
    LGFXStencilOperation_SetValue,
    LGFXStencilOperation_Invert,
    LGFXStencilOperation_Increment ,
    LGFXStencilOperation_Decrement
};


//! To create a Graphic Device . ( use LGFXDevice::create )
class LAPI LGFXDevice
{
    LNONCOPYABLE_CLASS(LGFXDevice)
public:
    LGFXDevice();
    virtual ~LGFXDevice();

    //! create a new renderable window and initialize device
    static LGFXDevice*              create();

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

    //! create a texture . _mipmap_count : Count of mip maps. use 0 to auto MipMaping
    virtual LGFXTexture*            createTexture(u16 _width,u16 _height,LImage::Format _format,u16 _mipmap_count=0)=0;

    //! create a renderable texture
    virtual LGFXTexture*            createRenderTarget(u16 _width,u16 _height,LImage::Format _renderable_format,bool _has_depth_buffer)=0;

    //! check device has any problem or not and tring to fix
    virtual void                    checkErrors()=0;

    //! release
    virtual void                    destroy()=0;

    //! draw stage
    virtual void                    draw()=0;

    //! draw a texture on screen . note if you are not using custom pixel shader then set texture from here ( use setPixelShader(0) before call this or resetParameters ) . otherwise set from you pixel shader. use getBackBuffer to access a copy of backbuffer
    virtual void                    drawQuad(LGFXTexture* _tex=0)=0;

    //! Get screen Resolution ( Not Rendering window ) \sa getResolution
    virtual LSize                   getScreenResolution()const=0;

    //! Get Availble Resolutions ( to pass into Initialize and Reset )
    virtual LVector<LSize>          getAvailbleResolutions()=0;

    //! get a scrren shot! (Note : this function creates a screen shot from back buffer . do screen shot when you'r render is done
    virtual LImage                  getScreenShot()=0;

    //! get resolution of rendering window ( NOT Entire Screen ) \sa getScreenResolution
    virtual LSize                   getResolution()const=0;

    //! get Maximum Width Height can used for textures
    virtual LSize                   getMaxTextureSize()const=0;

    //! get a copy of backbuffer as texture . because this function uses texture->copyTo so please resetParameters before call this
    //! what return's is static and you can change texture parameters like texture addressing
    virtual LGFXTexture*            getBackBuffer()=0;

    //! hide rendering window
    virtual void                    hideWindow()=0;

    //! initilize device
    virtual void                    initialize(bool _fullscreen,bool _vsync,u16 _screen_width,u16 _screen_height)=0;

    //! check game is fullscreen or not
    virtual bool                    isFullScreen()const=0;

    //! check is V-Sync Enabled or not
    virtual bool                    isVSyncEnabled()const=0;

    //! check game window is activate
    virtual bool                    isActivated()const;

    //! if process done returns 1 and if request was Quit returns 2
    virtual bool                    processOSMessage()=0;

    //! render on screen
    virtual void                    render()=0;

    //! reset device
    virtual void                    reset(bool _fullscreen,bool _vsync,u16 _screen_width,u16 _screen_height)=0;

    //! reset parameters to default
    virtual void                    resetParameters();

    //! set rendering window title
    virtual void                    setTitle(const LString& _newname)=0;

    //! set game window active or decative
    virtual void                    setActive(bool _val)=0;

    //! set view port based on limited range 0-1 . all parameters must be between (0-1)
    virtual void                    setViewPort(LRectF _in)=0;

    //! set view port based on  resolution
    virtual void                    setViewPort(LRect _in=LRect())=0;

    //! set current vertex declration
    virtual void                    setVertexDeclaration(LGFXVertexDeclaration* _decl)=0;

    //! set current vertex buffer
    virtual void                    setVertexBuffer(u16 _streamNumber,LGFXVertexBuffer *_buffer)=0;

    //! set vertex buffer frequency. set _count to -1 to disable . 0 to set instanced data and _count>0 to set gemetry count
    //! always use _streamNumber=0 for Geomety data NOT instanced data
    virtual void                    setVertexBufferFrequency(u16 _streamNumber,int _count=-1)=0;

    //! set current index buffer
    virtual void                    setIndexBuffer(LGFXIndexBuffer* _buffer)=0;

    //! set current vertex shader
    virtual void                    setVertexShader(LGFXShader* _shader)=0;

    //! set current pixel shader
    virtual void                    setPixelShader(LGFXShader* _shader)=0;

    //! set current texture
    virtual void                    setTexture(u32 _sampler,LGFXTexture* _t)=0;

    //! set Render Target
    virtual void                    setRenderTarget(u32 _index,LGFXTexture* _rt)=0;

    //! set depth check is enable or not
    virtual void                    setDepthCheckEnable(bool _value=true)=0;

    //! set write to depth buffer is enabled or not
    virtual void                    setDepthWriteEnable(bool _value=true)=0;

    //! set depth bias value
    virtual void                    setDepthBias(f32 _val=0.0f)=0;

    //! set depth check function
    virtual void                    setDepthCheckFunction(LGFXCompareFunction _val=LGFXCompareFunction_LessEqual)=0;

    //! set Back buffer true or false (for depth or stencil only drawing)
    virtual void                    setBackBufferWriteEnable(bool _val=true)=0;

    //! set fill mode
    virtual void                    setFillMode(LGFXFillMode _type=LGFXFillMode_Solid)=0;

    //! set cull mode
    virtual void                    setCullMode(LGFXCullMode _mode=LGFXCullMode_CounterClockwise)=0;

    //! set alpha blending is enabled or not
    virtual void                    setAlphaBlending(bool _value=false)=0;

    //! set stencil is enable or not
    virtual void                    setStencilEnable(bool _value=false)=0;

    //! set stencil check function
    virtual void                    setStencilCheckFunction(LGFXCompareFunction _f=LGFXCompareFunction_Always)=0;

    //! set what to do on stencil check fail
    virtual void                    setStencilFailOperation(LGFXStencilOperation _o=LGFXStencilOperation_Keep)=0;

    //! set what to do on stencil depth fail
    virtual void                    setStencilDepthFailOperation(LGFXStencilOperation _o=LGFXStencilOperation_Keep)=0;

    //! set what to do on stencil check pass
    virtual void                    setStencilPassOperation(LGFXStencilOperation _o=LGFXStencilOperation_Keep)=0;

    //! set stencil reference value
    virtual void                    setStencilValue (i32 _value=0)=0;

    //! show rendering window
    virtual void                    showWindow()=0;

protected:
    LVector<LGFXVertexDeclaration*> mVertexDecls;
    LVector<LGFXVertexBuffer*>      mVertexBuffers;
    LVector<LGFXIndexBuffer*>       mIndexBuffers;
    LVector<LGFXShader*>            mShaders;
    LVector<LGFXTexture*>           mTextures;

    u32                             mMaxSampler;
    u16                             mMaxVertexBuffer;
    u32                             mMaxRenderTarget;

    bool                            mIsActivated;

};

LNAMESPACE_END

#endif // LGFXDEVICE_H
