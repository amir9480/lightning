#ifndef LD3D9INDEXBUFFER_H
#define LD3D9INDEXBUFFER_H

#include "../../lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"

#include "../../lcore/ldefines.h"
#include "../lgfxindexbuffer.h"

LNAMESPACE_BEGIN

class LD3D9Device;

class LAPI LD3D9IndexBuffer:public LGFXIndexBuffer
{
    friend class LD3D9Device;
public:
    LD3D9IndexBuffer();
    virtual ~LD3D9IndexBuffer();

    virtual void destroy();

    virtual void getIndices(u32*& _data)const;

    virtual void preReset();

    virtual void postReset();

    virtual void updateBuffer(const u32* _data,u64 _indices_count);

protected:
    IDirect3DIndexBuffer9*  mIndexBuffer;
    LD3D9Device*            mDevice;
};

LNAMESPACE_END

#endif// LGFX == LGFX_D3D9

#endif // LD3D9INDEXBUFFER_H
