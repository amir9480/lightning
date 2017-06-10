#ifndef LD3D9SHADER_H
#define LD3D9SHADER_H


#include "lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"
#include "lcore.h"
#include "../lgfxshader.h"

LNAMESPACE_BEGIN

class LD3D9Shader:public LGFXShader
{
    friend class LD3D9Device;
public:
    LD3D9Shader();
    virtual ~LD3D9Shader();

    virtual bool                    compile(const LString& _content,const LString& _main_function_name);

    virtual void                    destroy();

    virtual ShaderType              getType() const;

    virtual void                    preReset();

    virtual void                    postReset();


protected:
    IDirect3DDevice9*           mDevice;
    union
    {
        IDirect3DVertexShader9* mVS;
        IDirect3DPixelShader9*  mPS;
    };
    ShaderType                  mType;
    ID3DXConstantTable*         mConstantTable;
};

LNAMESPACE_END

#endif

#endif // LD3D9SHADER_H
