#ifndef LGFXDEVICE_H
#define LGFXDEVICE_H

#include "lcore.h"
#include "lgfxvertexbuffer.h"
#include "lgfxindexbuffer.h"
#include "lgfxshader.h"

LNAMESPACE_BEGIN

class LAPI LGFXDevice
{
public:
    LGFXDevice(){}
    virtual ~LGFXDevice(){}

    //! create a new renderable window
    static LGFXDevice*              create();

    virtual void                    beginScene()=0;

    virtual void                    clear(int _r=0,int _g=0,int _b=0,bool _backbuffer=true,bool _zbuffer=true,bool _stencil=true,float _depthval=1.0f,u8 _stencilval=0)=0;

    virtual LGFXVertexDeclaration*  createVertexDeclaration(const LVector<LVertexElement>& _elements)=0;

    virtual LGFXVertexBuffer*       createVertexBuffer(bool _is_dynamic=false,bool _has_memory_copy=false)=0;

    virtual LGFXIndexBuffer*        createIndexBuffer(bool _has_memory_copy=false)=0;

    virtual LGFXShader*             createVertexShader()=0;

    virtual void                    endScene()=0;

    virtual void                    hideWindow()=0;

    virtual void                    initialize(bool _fullscreen,bool _vsync)=0;

    //! if process done returns 1 and if request was Quit returns 2
    virtual u8                      processOSMessage()=0;

    virtual void                    render()=0;

    virtual void                    release()=0;

    virtual void                    setTitle(const LString& _newname)=0;

    virtual void                    setVertexDeclaration(const LGFXVertexDeclaration* _decl)=0;

    virtual void                    setVertexBuffer(u16 _streamNumber,const LGFXVertexBuffer *_buffer)=0;

    virtual void                    setIndexBuffer(const LGFXIndexBuffer* _buffer)=0;

    virtual void                    showWindow()=0;

protected:
    LVector<LGFXVertexDeclaration*> mVertexDecls;
    LVector<LGFXVertexBuffer*>      mVertexBuffers;
    LVector<LGFXIndexBuffer*>       mIndexBuffers;
    LVector<LGFXShader*>            mShaders;
};

LNAMESPACE_END

#endif // LGFXDEVICE_H
