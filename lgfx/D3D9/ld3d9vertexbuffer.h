#ifndef LD3D9VERTEXBUFFER_H
#define LD3D9VERTEXBUFFER_H

#include "lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"

#include "lcore.h"
#include "../lgfxvertexbuffer.h"

LNAMESPACE_BEGIN

class LGFXDevice;
class LD3D9Device;

LVector<D3DVERTEXELEMENT9> getVertexDecl(const LVector<LVertexElement>& _in);

class LAPI LD3D9VertexDeclaration:public LGFXVertexDeclaration
{
    friend class LD3D9Device;
    friend class LD3D9VertexBuffer;
public:
    LD3D9VertexDeclaration(const LVector<LVertexElement> &_es);
    virtual ~LD3D9VertexDeclaration();

    virtual void  destroy();

    virtual const LVector<LVertexElement> &getElements();

    virtual u32 getElementsSize();

    virtual void preReset();

    virtual void postReset();

protected:
    IDirect3DVertexDeclaration9*    mDecl;
    LD3D9Device*                    mDevice;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LAPI LD3D9VertexBuffer:public LGFXVertexBuffer
{
    friend class LD3D9Device;
public:
    LD3D9VertexBuffer();

    virtual ~LD3D9VertexBuffer();

    virtual void destroy();

    virtual void getVertices(char*& _data)const;

    virtual void preReset();

    virtual void postReset();

    virtual void updateBuffer(const char* _data,u64 _elementSize,u64 _number_of_elements);
private:
    IDirect3DVertexBuffer9* mVertexBuffer;
    LD3D9Device*            mDevice;
};

LNAMESPACE_END

#endif// LGFX

#endif // LD3D9VERTEXBUFFER_H
