#include "ld3d9device.h"

#if ( LGFX == LGFX_D3D9 )

LNAMESPACE_BEGIN

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

LGFXDevice* LGFXDevice::create()
{
    LGFXDevice* o =new LD3D9Device();
    return o;
}


LD3D9Device::LD3D9Device()
{
    mWindowHandler=0;
    mD3D9=0;
    mDevice=0;
    mCurrentIndexBuffer=0;
    mCurrentIndexBuffer=0;

    mWindowHandler = CreateWindowExW( NULL, L"lightningmainwindow",
                             L"Lightning",
                             /*WS_OVERLAPPEDWINDOW | WS_VISIBLE,*/
                             WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX|WS_VISIBLE,
                             0, 0, 640, 480, NULL, NULL, GetModuleHandleA(0), NULL );
}

LD3D9Device::~LD3D9Device()
{
    release();
    lLogMessage(1,"Direct3D9 Graphic Device Destroyed");
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
    LD3D9Texture* o=new LD3D9Texture;
    mTextures.pushBack(o);
    o->mDevice=this;
    o->mWidth=_width;
    o->mHeight=_height;
    o->mMipMapCount=_mipmap_count;
    o->mFormat = _format;
    o->mType=LGFXTexture::TextureType_2D;

    HR(mDevice->CreateTexture(_width,_height,_mipmap_count,0,lD3DTextureFormat(_format),D3DPOOL_MANAGED,(IDirect3DTexture9**)(&(o->mTexture)),0));
    o->generateMipMaps();

    return o;
}

void LD3D9Device::draw()
{
    HR(mDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,mCurrentVertexBuffer->getNumberOfElements(),0,mCurrentIndexBuffer->getIndicesCount()/3));
}

void LD3D9Device::endScene()
{
    mDevice->EndScene();
}

void LD3D9Device::hideWindow()
{
    ShowWindow(mWindowHandler,SW_HIDE);
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
    dpp.BackBufferWidth=GetSystemMetrics(SM_CXSCREEN);
    dpp.BackBufferHeight=GetSystemMetrics(SM_CYSCREEN);
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
}

u8 LD3D9Device::processOSMessage()
{
    MSG msg;
    if(PeekMessageW(&msg,0,0,0,PM_REMOVE))
    {
        if(msg.message==WM_QUIT)
            return 2;
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        return 1;
    }
    return 0;
}

void LD3D9Device::render()
{
    mDevice->Present(0,0,0,0);
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
    SAFE_RELEASE(mDevice);
    SAFE_RELEASE(mD3D9);
}

void LD3D9Device::setTitle(const LString &_newname)
{
    SetWindowTextW(mWindowHandler,_newname.getData());
}

void LD3D9Device::setVertexDeclaration(const LGFXVertexDeclaration *_decl)
{
    if(_decl==nullptr)
    {
        HR(mDevice->SetVertexDeclaration(0));
        return;
    }
    const LD3D9VertexDeclaration* decl=dynamic_cast<const LD3D9VertexDeclaration*>(_decl);
    HR(mDevice->SetVertexDeclaration(decl->mDecl));
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
    lError(_shader->getType()!=LGFXShader::ShaderType::vertexShader,"_shader type is not vertex shader");
    if(_shader==nullptr)
    {
        HR(mDevice->SetVertexShader(0));
        return;
    }
    HR(mDevice->SetVertexShader(dynamic_cast<LD3D9Shader*>(_shader)->mVS));
}

void LD3D9Device::setPixelShader(LGFXShader *_shader)
{
    lError(_shader->getType()!=LGFXShader::ShaderType::pixelShader,"_shader type is not pixel shader");
    if(_shader==nullptr)
    {
        HR(mDevice->SetPixelShader(0));
        return;
    }
    HR(mDevice->SetPixelShader(dynamic_cast<LD3D9Shader*>(_shader)->mPS));

}

void LD3D9Device::setTexture(u32 _sampler, LGFXTexture *_t)
{
    static float _mmld;
    _mmld=_t->getMipMapBias();
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MINFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAGFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MIPFILTER,lD3DTextureFilter(_t->getFilter())));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MIPMAPLODBIAS,*((LPDWORD)(&_mmld))));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAXANISOTROPY,_t->getMaxAnisotropic()));
    HR(mDevice->SetSamplerState(_sampler,D3DSAMP_MAXMIPLEVEL,_t->getMaxMipMapLevel()));
    HR(mDevice->SetTexture(_sampler, dynamic_cast<LD3D9Texture*>(_t)->mTexture));
}

void LD3D9Device::showWindow()
{
    ShowWindow(mWindowHandler,SW_SHOW);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


#endif //LGFX
LNAMESPACE_END
