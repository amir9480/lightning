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

LNAMESPACE_BEGIN



LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);

class LAPI LD3D9Device:public LGFXDevice
{
    friend class LD3D9VertexDeclaration;
public:
    LD3D9Device();
    virtual ~LD3D9Device();

    virtual void                    beginScene();

    virtual void                    clear(int _r,int _g,int _b,bool _backbuffer, bool _zbuffer, bool _stencil,float _depthval,u8 _stencilval);

    virtual LGFXVertexDeclaration*  createVertexDeclaration(const LVector<LVertexElement> &_elements);

    virtual LGFXVertexBuffer*       createVertexBuffer(bool _is_dynamic, bool _has_memory_copy);

    virtual LGFXIndexBuffer*        createIndexBuffer(bool _has_memory_copy);

    virtual LGFXShader*             createVertexShader();

    virtual void                    endScene();

    virtual void                    hideWindow();

    virtual void                    initialize(bool _fullscreen,bool _vsync);

    virtual u8                      processOSMessage();

    virtual void                    render();

    virtual void                    release();

    virtual void                    setTitle(const LString& _newname);

    virtual void                    setVertexDeclaration(const LGFXVertexDeclaration *_decl);

    virtual void                    setVertexBuffer(u16 _streamNumber,const LGFXVertexBuffer* _buffer);

    virtual void                    setIndexBuffer(const LGFXIndexBuffer* _buffer);

    virtual void                    showWindow();

protected:
    HWND                mWindowHandler;
    IDirect3D9*         mD3D9;
    IDirect3DDevice9*   mDevice;
};

LNAMESPACE_END

#endif // LGFX

#endif // LD3D9DEVICE_H