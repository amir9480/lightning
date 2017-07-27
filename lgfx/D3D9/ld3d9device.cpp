#include "ld3d9device.h"

#if ( LGFX == LGFX_D3D9 )

LNAMESPACE_BEGIN

LGFXVertexDeclaration* D3D9QuadVertex::decl=nullptr;
LVector<LVertexElement> _d3d9quad_decl={
    {0,LVertexElementType_Float3,LVertexElementUsage_Position,0},
    {0,LVertexElementType_Float2,LVertexElementUsage_TextureCoordinate,0},
};

D3D9QuadVertex _d3d9quad_vertex[]=
{
    {LVector3(-1,1,0.2f),LVector2(0,0)},
    {LVector3(1,1,0.2f),LVector2(1,0)},
    {LVector3(-1,-1,0.2f),LVector2(0,1)},
    {LVector3(1,-1,0.2f),LVector2(1,1)}
};
LVector<u32> _d3d9quad_index={1,2,0 , 1,3,2};
const char* _d3d9quadshader=
R"(
uniform extern sampler2D t0;

struct VSInput
{
    float3 pos:POSITION0;
    float2 uv:TEXCOORD0;
};

struct VSOut
{
    float4 pos:SV_POSITION0;
    float2 uv:TEXCOORD0;
};


VSOut mainVS(VSInput _in)
{
    VSOut o;
    o.pos.xyz=_in.pos;
    o.pos.w=1.0f;
    o.uv=_in.uv;
    return o;
}


float4 mainPS(VSOut _in):COLOR0
{
    float4 o=float4(0.0f,0.0f,0.0f,1.0f);
    o.rgb=tex2D(t0,_in.uv.xy).rgb;
    return o;
}



)";

LENUM_CONVERTOR_CUSTOM( LAPI,LGFXCullMode               ,D3DCULL,
                        LGFXCullMode_None               ,D3DCULL_NONE,
                        LGFXCullMode_Clockwise          ,D3DCULL_CW,
                        LGFXCullMode_CounterClockwise   ,D3DCULL_CCW)

LENUM_CONVERTOR_CUSTOM( LAPI,LGFXFillMode               ,D3DFILLMODE,
                        LGFXFillMode_Point              ,D3DFILL_POINT,
                        LGFXFillMode_Wireframe          ,D3DFILL_WIREFRAME,
                        LGFXFillMode_Solid              ,D3DFILL_SOLID)

LENUM_CONVERTOR_CUSTOM( LAPI,LGFXCompareFunction        ,D3DCMPFUNC,
                        LGFXCompareFunction_Never       ,D3DCMP_NEVER,
                        LGFXCompareFunction_Less        ,D3DCMP_LESS,
                        LGFXCompareFunction_Equal       ,D3DCMP_EQUAL,
                        LGFXCompareFunction_LessEqual   ,D3DCMP_LESSEQUAL,
                        LGFXCompareFunction_Greater     ,D3DCMP_GREATER,
                        LGFXCompareFunction_NotEqual    ,D3DCMP_NOTEQUAL,
                        LGFXCompareFunction_GreaterEqual,D3DCMP_GREATEREQUAL,
                        LGFXCompareFunction_Always      ,D3DCMP_ALWAYS)

LENUM_CONVERTOR_CUSTOM( LAPI,LGFXStencilOperation       ,D3DSTENCILOP,
                        LGFXStencilOperation_Zero       ,D3DSTENCILOP_ZERO,
                        LGFXStencilOperation_Keep       ,D3DSTENCILOP_KEEP,
                        LGFXStencilOperation_SetValue   ,D3DSTENCILOP_REPLACE,
                        LGFXStencilOperation_Invert     ,D3DSTENCILOP_INVERT,
                        LGFXStencilOperation_Increment  ,D3DSTENCILOP_INCRSAT,
                        LGFXStencilOperation_Decrement  ,D3DSTENCILOP_DECRSAT)

void lCallOnStart()
{
    WNDCLASSW mywndclass;
    lMemorySet(&mywndclass,sizeof(mywndclass),0);
    mywndclass.hbrBackground=(HBRUSH)COLOR_WINDOW;
    mywndclass.hCursor=LoadCursor(0,IDC_ARROW);
    mywndclass.hInstance=GetModuleHandleW(0);
    mywndclass.lpfnWndProc=lightningmainwindowproc;
    mywndclass.lpszClassName=L"lightningmainwindow";
    mywndclass.style=CS_HREDRAW|CS_VREDRAW;
    RegisterClassW(&mywndclass);
}

void lCallOnEnd()
{
    UnregisterClassW(L"lightningmainwindow",GetModuleHandleW(0));
}

LGFXDevice* LGFXDevice::create(bool _fullscreen, bool _vsync)
{
    LGFXDevice* o =new LD3D9Device();
    o->initialize(_fullscreen,_vsync);
    return o;
}


LD3D9Device::LD3D9Device()
{
    mWindowHandler=0;
    mD3D9=0;
    mDevice=0;
    mCurrentIndexBuffer=0;
    mCurrentIndexBuffer=0;
    mNativeBackBuffer=0;
    mMainBackBuffer=0;
    mQuadVertexBuffer=0;
    mQuadIndexBuffer=0;
    mCurrentVertexDecl=0;
    mCurrentVertexShader=0;
    mCurrentPixelShader=0;

    mWindowHandler = CreateWindowExW( (DWORD)NULL, L"lightningmainwindow",
                             (LSTR(LIGHTNING)+" "+LIGHTNING_VERSION).getData(),
                             /*WS_OVERLAPPEDWINDOW | WS_VISIBLE,*/
                             WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX|WS_VISIBLE,
                             0, 0, 800, 600, (HWND)NULL,(HMENU)NULL, GetModuleHandleA(0),(LPVOID)NULL );
}

LD3D9Device::~LD3D9Device()
{
    release();
    lLogMessage(1,"Direct3D9 Graphic Device Destroyed");
}

void LD3D9Device::initialize(bool _fullscreen, bool _vsync)
{
    release();
    NZ(mD3D9=Direct3DCreate9(D3D_SDK_VERSION));
    static D3DPRESENT_PARAMETERS dpp;
    lMemorySet(&dpp,sizeof(dpp),0);
    dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    dpp.Windowed= !_fullscreen;
    dpp.BackBufferCount=1;
    dpp.BackBufferWidth=2048;//GetSystemMetrics(SM_CXSCREEN);
    dpp.BackBufferHeight=2048;//GetSystemMetrics(SM_CYSCREEN);
    if(_fullscreen)
        dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    else
        dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    dpp.EnableAutoDepthStencil = true;
    dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    dpp.hDeviceWindow = mWindowHandler;
    dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    if(!_vsync)
        dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    else
        dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    HR(mD3D9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE::D3DDEVTYPE_HAL,mWindowHandler,
                           D3DCREATE_HARDWARE_VERTEXPROCESSING,&dpp,&mDevice));
    lLogMessage(1,"Direct3D9 Graphic Device Initialized Successfully");

    HR(mDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&mNativeBackBuffer));

    mMainBackBuffer = new LD3D9Texture;
    mMainBackBuffer->mWidth=800;
    mMainBackBuffer->mHeight=600;
    mMainBackBuffer->mFormat=LImage::Format_R8G8B8;
    mMainBackBuffer->mIsRenderTarget=true;
    mMainBackBuffer->mAddressU=LGFXTexture::TextureAddress_border;
    mMainBackBuffer->mAddressV=LGFXTexture::TextureAddress_border;
    mMainBackBuffer->mDevice=this;
    mMainBackBuffer->mFilter=LGFXTexture::TextureFilter_anisotropic;
    mMainBackBuffer->mMipMapCount=1;
    mMainBackBuffer->mType = LGFXTexture::TextureType_RenderTarget;
    HR(mDevice->CreateTexture(mMainBackBuffer->mWidth,mMainBackBuffer->mHeight,1,D3DUSAGE_RENDERTARGET,lD3DTextureFormat(mMainBackBuffer->mFormat),D3DPOOL_DEFAULT,(IDirect3DTexture9**)(&(mMainBackBuffer->mTexture)),0));

    D3D9QuadVertex::decl=createVertexDeclaration(_d3d9quad_decl);
    mQuadVertexBuffer=dynamic_cast<LD3D9VertexBuffer*>(createVertexBuffer(0,0));
    mQuadVertexBuffer->updateBuffer((char*)_d3d9quad_vertex,sizeof(_d3d9quad_vertex[0]),4);
    mQuadIndexBuffer=dynamic_cast<LD3D9IndexBuffer*>(createIndexBuffer(0));
    mQuadIndexBuffer->updateBuffer(_d3d9quad_index.getData(),_d3d9quad_index.getSize());
    mQuadVertexShader=dynamic_cast<LD3D9Shader*>(createVertexShader());
    mQuadVertexShader->compile(_d3d9quadshader,"mainVS");
    mQuadPixelShader=dynamic_cast<LD3D9Shader*>(createPixelShader());
    mQuadPixelShader->compile(_d3d9quadshader,"mainPS");
    setRenderTarget(0,nullptr);
}

void LD3D9Device::beginScene()
{
    mDevice->BeginScene();
}

void LD3D9Device::clear(int _r,int _g,int _b,bool _backbuffer, bool _zbuffer, bool _stencil, float _depthval, u8 _stencilval)
{
    DWORD fs=0;
    if(_backbuffer)
        fs|=D3DCLEAR_TARGET;
    if(_zbuffer)
        fs|=D3DCLEAR_ZBUFFER;
    if(_stencil)
        fs|=D3DCLEAR_STENCIL;

    mDevice->Clear(0,0,fs,D3DCOLOR_XRGB(_r,_g,_b),_depthval,_stencilval);
}

LGFXVertexDeclaration *LD3D9Device::createVertexDeclaration(const LVector<LVertexElement> &_elements)
{
    LD3D9VertexDeclaration* decl=new LD3D9VertexDeclaration(_elements);
    decl->mDevice=this;
    HR(mDevice->CreateVertexDeclaration(getVertexDecl(_elements).getData(),&decl->mDecl));
    mVertexDecls.pushBack(decl);
    return decl;
}

LGFXVertexBuffer *LD3D9Device::createVertexBuffer( bool _is_dynamic, bool _has_memory_copy)
{
    LD3D9VertexBuffer* o=new LD3D9VertexBuffer;
    mVertexBuffers.pushBack(o);
    o->mDevice=this;
    o->mHasMemoryCopy=_has_memory_copy;
    o->mIsDynamic=_is_dynamic;
    return o;
}

LGFXIndexBuffer *LD3D9Device::createIndexBuffer(bool _has_memory_copy)
{
    LD3D9IndexBuffer* o=new LD3D9IndexBuffer;
    mIndexBuffers.pushBack(o);
    o->mDevice=this;
    o->mHasMemoryCopy=_has_memory_copy;
    return o;
}

LGFXShader *LD3D9Device::createVertexShader()
{
    LD3D9Shader* o=new LD3D9Shader;
    mShaders.pushBack(o);
    o->mDevice=this;
    o->mType=LGFXShader::ShaderType::vertexShader;
    return o;
}

LGFXShader *LD3D9Device::createPixelShader()
{
    LD3D9Shader* o=new LD3D9Shader;
    mShaders.pushBack(o);
    o->mDevice=this;
    o->mType=LGFXShader::ShaderType::pixelShader;
    return o;
}

LGFXTexture *LD3D9Device::createTexture(u16 _width, u16 _height, u16 _mipmap_count, LImage::Format _format)
{
    lError(_width==0||_height==0||_mipmap_count==0||_format==LImage::Format_null,"Some thing is wrong",nullptr);
    LD3D9Texture* o=new LD3D9Texture;
    mTextures.pushBack(o);
    o->mDevice=this;
    o->mWidth=_width;
    o->mHeight=_height;
    o->mMipMapCount=_mipmap_count;
    o->mFormat = _format;
    o->mType=LGFXTexture::TextureType_2D;

    HR(mDevice->CreateTexture(_width,_height,_mipmap_count,0,lD3DTextureFormat(_format),D3DPOOL_MANAGED,(IDirect3DTexture9**)(&(o->mTexture)),0));

    return o;
}

LGFXTexture *LD3D9Device::createRenderTarget(u16 _width, u16 _height, LImage::Format _renderable_format)
{
    lError(_width==0||_height==0||_renderable_format==LImage::Format_null,"Some thing is wrong",nullptr);
    LD3D9Texture* o =new LD3D9Texture;
    mTextures.pushBack(o);
    o->mDevice=this;
    o->mWidth=_width;
    o->mHeight=_height;
    o->mMipMapCount=1;
    o->mFormat=_renderable_format;
    o->mIsRenderTarget=true;
    o->mType = LGFXTexture::TextureType_RenderTarget;
    HR(mDevice->CreateTexture(_width,_height,1,D3DUSAGE_RENDERTARGET,lD3DTextureFormat(_renderable_format),D3DPOOL_DEFAULT,(IDirect3DTexture9**)(&(o->mTexture)),0));
    return o;
}

void LD3D9Device::draw()
{
    HR(mDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,mCurrentVertexBuffer->getNumberOfElements(),0,mCurrentIndexBuffer->getIndicesCount()/3));
}

void LD3D9Device::drawQuad(LGFXTexture *_tex)
{
    resetParameters();
    setVertexDeclaration(D3D9QuadVertex::decl);
    setVertexBuffer(0,mQuadVertexBuffer);
    setIndexBuffer(mQuadIndexBuffer);
    setDepthWriteEnable(false);
    setDepthCheckEnable(false);
    setVertexShader(mQuadVertexShader);
    if(mCurrentPixelShader==nullptr)
    {
        setPixelShader(mQuadPixelShader);
        mQuadPixelShader->setTexture("t0",_tex);
    }

    draw();
    resetParameters();
}

void LD3D9Device::endScene()
{
    mDevice->EndScene();
}

void LD3D9Device::hideWindow()
{
    ShowWindow(mWindowHandler,SW_HIDE);
}

bool LD3D9Device::processOSMessage()
{
    MSG msg;
    if(PeekMessageW(&msg,0,0,0,PM_REMOVE))
    {
        if(msg.message==WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        return processOSMessage();
    }
    return true;
}

void LD3D9Device::render()
{
    resetParameters();
    setVertexDeclaration(D3D9QuadVertex::decl);
    setVertexBuffer(0,mQuadVertexBuffer);
    setIndexBuffer(mQuadIndexBuffer);
    setDepthWriteEnable(false);
    setDepthCheckEnable(false);
    setVertexShader(mQuadVertexShader);
    if(mCurrentPixelShader==nullptr)
    {
        setPixelShader(mQuadPixelShader);
        mQuadPixelShader->setTexture("t0",mMainBackBuffer);
    }

    HR(mDevice->SetRenderTarget(0,mNativeBackBuffer));
    draw();


    mDevice->Present(0,0,0,0);


    resetParameters();
    setRenderTarget(0,nullptr);
}

void LD3D9Device::release()
{
    while(mVertexDecls.getSize()>0)
    {
        delete mVertexDecls[0];
        mVertexDecls.remove(0);
    }
    while(mVertexBuffers.getSize()>0)
    {
        delete mVertexBuffers[0];
        mVertexBuffers.remove(0);
    }
    while(mIndexBuffers.getSize()>0)
    {
        delete mIndexBuffers[0];
        mIndexBuffers.remove(0);
    }
    while(mShaders.getSize()>0)
    {
        delete mShaders[0];
        mShaders.remove(0);
    }
    while(mTextures.getSize()>0)
    {
        delete mTextures[0];
        mTextures.remove(0);
    }

    delete mMainBackBuffer;
    mCurrentIndexBuffer=0;
    mCurrentPixelShader=0;
    mCurrentVertexBuffer=0;
    mCurrentVertexDecl=0;
    mCurrentVertexShader=0;

    SAFE_RELEASE(mDevice);
    SAFE_RELEASE(mD3D9);
}

void LD3D9Device::setTitle(const LString &_newname)
{
    SetWindowTextW(mWindowHandler,_newname.getData());
}

void LD3D9Device::setVertexDeclaration(LGFXVertexDeclaration *_decl)
{
    if(_decl==nullptr)
    {
        mCurrentVertexDecl=nullptr;
        HR(mDevice->SetVertexDeclaration(0));
        return;
    }
    mCurrentVertexDecl=dynamic_cast<LD3D9VertexDeclaration*>(_decl);
    HR(mDevice->SetVertexDeclaration(mCurrentVertexDecl->mDecl));
}

void LD3D9Device::setVertexBuffer(u16 _streamNumber, LGFXVertexBuffer *_buffer)
{
    if(_buffer==nullptr)
    {
        HR(mDevice->SetStreamSource(0,0,0,0));
        mCurrentVertexBuffer=nullptr;
        return;
    }
    mCurrentVertexBuffer=dynamic_cast<LD3D9VertexBuffer*>(_buffer);
    HR(mDevice->SetStreamSource(_streamNumber,dynamic_cast<LD3D9VertexBuffer*>(_buffer)->mVertexBuffer,0,_buffer->getElementSize()));
    mMaxVertexBuffer = lMax(_streamNumber,mMaxVertexBuffer);
}

void LD3D9Device::setVertexBufferFrequency(u16 _streamNumber, u32 _count)
{
    if(_count==0)
    {
        HR(mDevice->SetStreamSourceFreq(_streamNumber,1));
    }
    else if(_count==1)
    {
        HR(mDevice->SetStreamSourceFreq(_streamNumber,D3DSTREAMSOURCE_INSTANCEDATA|1));
    }
    else
    {
        HR(mDevice->SetStreamSourceFreq(_streamNumber,D3DSTREAMSOURCE_INDEXEDDATA |_count));
    }
}

void LD3D9Device::setIndexBuffer(LGFXIndexBuffer *_buffer)
{
    if(_buffer==nullptr)
    {
        HR(mDevice->SetIndices(0));
        mCurrentVertexBuffer=nullptr;
        return;
    }
    mCurrentIndexBuffer=dynamic_cast<LD3D9IndexBuffer*>(_buffer);
    HR(mDevice->SetIndices(dynamic_cast<LD3D9IndexBuffer*>(_buffer)->mIndexBuffer));
}

void LD3D9Device::setVertexShader(LGFXShader *_shader)
{
    if(_shader==nullptr)
    {
        mCurrentVertexShader=nullptr;
        HR(mDevice->SetVertexShader(0));
        return;
    }
    lError(_shader->getType()!=LGFXShader::ShaderType::vertexShader,"_shader type is not vertex shader");
    mCurrentVertexShader=dynamic_cast<LD3D9Shader*>(_shader);
    HR(mDevice->SetVertexShader(dynamic_cast<LD3D9Shader*>(_shader)->mVS));
}

void LD3D9Device::setPixelShader(LGFXShader *_shader)
{
    if(_shader==nullptr)
    {
        mCurrentPixelShader=nullptr;
        HR(mDevice->SetPixelShader(0));
        return;
    }
    lError(_shader->getType()!=LGFXShader::ShaderType::pixelShader,"_shader type is not pixel shader");
    mCurrentPixelShader=dynamic_cast<LD3D9Shader*>(_shader);
    HR(mDevice->SetPixelShader(dynamic_cast<LD3D9Shader*>(_shader)->mPS));

}

void LD3D9Device::setTexture(u32 _sampler, LGFXTexture *_t)
{
    if(_t==nullptr || _t->isNull())
    {
        HR(mDevice->SetTexture(_sampler,nullptr));
        return;
    }
    static float _mmld;
    _mmld=_t->getMipMapBias();
    HR(mDevice->SetTexture(_sampler, dynamic_cast<LD3D9Texture*>(_t)->mTexture));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MINFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAGFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MIPFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MIPMAPLODBIAS,*((LPDWORD)(&_mmld))));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAXANISOTROPY,_t->getMaxAnisotropic()));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAXMIPLEVEL,_t->getMaxMipMapLevel()));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_ADDRESSU,lD3DTextureAddress(_t->getAddressU())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_ADDRESSV,lD3DTextureAddress(_t->getAddressV())));
    mMaxSampler = lMax(mMaxSampler,_sampler);
}

void LD3D9Device::setRenderTarget(u32 _index, LGFXTexture *_rt)
{
    if(_rt==nullptr || _rt->isNull())
    {
        if(_index!=0)
        {
            HR(mDevice->SetRenderTarget(_index,nullptr));
        }
        else
        {
            setRenderTarget(0,mMainBackBuffer);
        }
        return;
    }
    LD3D9Texture* d3drt=dynamic_cast<LD3D9Texture*>(_rt);
    IDirect3DSurface9* _rs=nullptr;
    d3drt->mTexture->GetSurfaceLevel(0,&_rs);
    HR(mDevice->SetRenderTarget(_index,_rs));
    mMaxRenderTarget=lMax(mMaxRenderTarget,_index);
}

void LD3D9Device::setDepthCheckEnable(bool _value)
{
    if(_value)
    {
        HR(mDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE));
    }
    else
    {
        HR(mDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE));
    }
}

void LD3D9Device::setDepthCheckFunction(LGFXCompareFunction _val)
{
    HR(mDevice->SetRenderState(D3DRS_ZFUNC,fromLGFXCompareFunctionToD3DCMPFUNC(_val)));
}

void LD3D9Device::setDepthWriteEnable(bool _value)
{
    HR(mDevice->SetRenderState(D3DRS_ZWRITEENABLE,_value));
}

void LD3D9Device::setDepthBias(f32 _val)
{
    HR(mDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,*((DWORD*)&_val)));
}

void LD3D9Device::setBackBufferWriteEnable(bool _val)
{
    if(_val)
    {
        mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
        mDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
        mDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
    }
    else
    {
        mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
        mDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
        mDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
    }

}

void LD3D9Device::setFillMode(LGFXFillMode _type)
{
    HR(mDevice->SetRenderState(D3DRS_FILLMODE,fromLGFXFillModeToD3DFILLMODE(_type)));
}

void LD3D9Device::setCullMode(LGFXCullMode _mode)
{
    HR(mDevice->SetRenderState(D3DRS_CULLMODE,fromLGFXCullModeToD3DCULL(_mode)));
}

void LD3D9Device::setAlphaBlending(bool _value)
{
    if(_value)
    {
        mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
        mDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
        mDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    }
    else
    {
        mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
        mDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
        mDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO );
    }
}

void LD3D9Device::setStencilEnable(bool _value)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILENABLE,_value));
}

void LD3D9Device::setStencilValue(i32 _value)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILREF,_value));
}

void LD3D9Device::setStencilCheckFunction(LGFXCompareFunction _f)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILFUNC,fromLGFXCompareFunctionToD3DCMPFUNC(_f)));
}

void LD3D9Device::setStencilPassOperation(LGFXStencilOperation _o)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILPASS,fromLGFXStencilOperationToD3DSTENCILOP(_o)));
}

void LD3D9Device::setStencilDepthFailOperation(LGFXStencilOperation _o)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILZFAIL,fromLGFXStencilOperationToD3DSTENCILOP(_o)));
}

void LD3D9Device::setStencilFailOperation(LGFXStencilOperation _o)
{
    HR(mDevice->SetRenderState(D3DRS_STENCILFAIL,fromLGFXStencilOperationToD3DSTENCILOP(_o)));
}

void LD3D9Device::showWindow()
{
    ShowWindow(mWindowHandler,SW_SHOW);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


#endif //LGFX
LNAMESPACE_END
