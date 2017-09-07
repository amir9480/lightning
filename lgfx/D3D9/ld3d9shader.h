#ifndef LD3D9SHADER_H
#define LD3D9SHADER_H


#include "../../lconfig.h"

#if ( LGFX == LGFX_D3D9 )

#include "ld3d9.h"
#include "../../lcore/ldefines.h"
#include "../../lcore/lstring.h"
#include "../../lcore/lmap.h"
#include "../lgfxshader.h"

LNAMESPACE_BEGIN

class LD3D9Device;

class LAPI LD3D9Shader:public LGFXShader
{
    friend class LD3D9Device;
public:
    LD3D9Shader();
    virtual ~LD3D9Shader();

    virtual bool                    compile(LString _content, LString _main_function_name);

    virtual void                    destroy();

    virtual ShaderType              getType() const;

    D3DXHANDLE                      getConstantHandle(const LString& _name);

    virtual void                    preReset();

    virtual void                    postReset();

    virtual void                    setBool(const LString &_name, bool _value);

    virtual void                    setBoolArray(const LString &_name, const bool *_value, u32 _count);

    virtual void                    setFloat(const LString &_name, float _value);

    virtual void                    setFloatArray(const LString &_name, const float *_value, u32 _count);

    virtual void                    setInt(const LString &_name, int _value);

    virtual void                    setIntArray(const LString &_name, const int *_value, u32 _count);

    virtual void                    setMatrix(const LString &_name, const LMatrix &_value);

    virtual void                    setTexture(const LString& _name, LGFXTexture *_texture);

    virtual void                    setVector(const LString &_name, const LVector2 &_value);

    virtual void                    setVector(const LString &_name, const LVector3 &_value);

    virtual void                    setVector(const LString &_name, const LVector4 &_value);

    virtual void                    setValue(const LString &_name, const void *_value, u32 _value_size);

protected:
    LD3D9Device*                mDevice;
    union
    {
        IDirect3DVertexShader9* mVS;
        IDirect3DPixelShader9*  mPS;
    };
    ShaderType                  mType;
    ID3DXConstantTable*         mConstantTable;
    LMap<LString,D3DXHANDLE>    mConstantCache;
};

LNAMESPACE_END

#endif

#endif // LD3D9SHADER_H
