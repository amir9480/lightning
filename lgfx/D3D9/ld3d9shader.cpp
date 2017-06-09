#include "ld3d9shader.h"

LNAMESPACE_BEGIN

#if ( LGFX == LGFX_D3D9 )

LD3D9Shader::LD3D9Shader():
    mDevice(nullptr),
    mVS(nullptr),
    mConstantTable(nullptr)
{

}

LD3D9Shader::~LD3D9Shader()
{
    this->destroy();
}

bool LD3D9Shader::compile(const LString &_content, const LString &_main_function_name)
{
    bool out=true;
    this->destroy();
    mContent=_content;
    LString8 cont=mContent.toUTF8();

    ID3DXBuffer* sb=nullptr;
    ID3DXBuffer* errorsb=nullptr;
    if(mType==LGFXShader::ShaderType::pixelShader)
    {

    }
    else if(mType==LGFXShader::ShaderType::vertexShader)
    {
        D3DXCompileShader(cont.getData(),cont.getCapacity(),0,0,_main_function_name.toUTF8().getData(),D3DXGetVertexShaderProfile(mDevice),D3DXSHADER_DEBUG,&sb,&errorsb,&mConstantTable);
        if(errorsb)
        {
            lError2(1,LSTR("Lightning DirectX Shader Error:")+((const char*)errorsb->GetBufferPointer()));
            out=false;
        }
        else
        {
            HR(mDevice->CreateVertexShader((const DWORD*)sb->GetBufferPointer(),&mVS));
        }
    }
    SAFE_RELEASE(sb);
    SAFE_RELEASE(errorsb);
    return out;
}

void LD3D9Shader::destroy()
{

}

LGFXShader::ShaderType LD3D9Shader::getType() const
{
    return mType;
}

void LD3D9Shader::preReset()
{

}

void LD3D9Shader::postReset()
{

}




#endif

LNAMESPACE_END
