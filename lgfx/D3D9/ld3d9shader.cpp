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
        D3DXCompileShader(cont.getData(),cont.getCapacity(),0,0,_main_function_name.toUTF8().getData(),D3DXGetPixelShaderProfile(mDevice),D3DXSHADER_DEBUG,&sb,&errorsb,&mConstantTable);
        if(errorsb)
        {
            lError2(1,LSTR("Lightning DirectX Shader Error:")+((const char*)errorsb->GetBufferPointer()));
            out=false;
        }
        else
        {
            HR(mDevice->CreatePixelShader((const DWORD*)sb->GetBufferPointer(),&mPS));
        }
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
    if(mType==LGFXShader::ShaderType::vertexShader)
    {
        SAFE_RELEASE(mVS);
    }
    else if(mType==LGFXShader::ShaderType::pixelShader)
    {
        SAFE_RELEASE(mPS);
    }
    SAFE_RELEASE(mConstantTable);
    mConstantCache.clear();
}

LGFXShader::ShaderType LD3D9Shader::getType() const
{
    return mType;
}

D3DXHANDLE LD3D9Shader::getConstantHandle(const LString &_name)
{
    if(mConstantCache.findKey(_name)==LMap<LString,D3DXHANDLE>::nothing)
    {
        D3DXHANDLE h=mConstantTable->GetConstantByName(0,_name.toUTF8().getData());
        lError(h==NULL,LSTR("Shader Constant \"")+_name+"\" Not Found",h);
        mConstantCache.insert(_name,h);
    }
    return mConstantCache[_name];
}

void LD3D9Shader::preReset()
{

}

void LD3D9Shader::postReset()
{

}

void LD3D9Shader::setBool(const LString &_name, bool _value)
{
    mConstantTable->SetBool(mDevice,getConstantHandle(_name),_value);
}

void LD3D9Shader::setBoolArray(const LString &_name, const bool *_value, u32 _count)
{
    WINBOOL* _v=new WINBOOL[_count];
    for(u32 i=0;i<_count;i++)
        _v[i]=(WINBOOL)_value[i];
    mConstantTable->SetBoolArray(mDevice,getConstantHandle(_name),_v,_count);
    delete[] _v;
}

void LD3D9Shader::setFloat(const LString &_name, float _value)
{
    mConstantTable->SetFloat(mDevice,getConstantHandle(_name),_value);
}

void LD3D9Shader::setFloatArray(const LString &_name, const float *_value, u32 _count)
{
    mConstantTable->SetFloatArray(mDevice,getConstantHandle(_name),_value,_count);
}

void LD3D9Shader::setInt(const LString &_name, int _value)
{
    mConstantTable->SetInt(mDevice,getConstantHandle(_name),_value);
}

void LD3D9Shader::setIntArray(const LString &_name, const int *_value, u32 _count)
{
    mConstantTable->SetIntArray(mDevice,getConstantHandle(_name),_value,_count);
}

void LD3D9Shader::setMatrix(const LString &_name, const LMatrix &_value)
{
    D3DXMATRIX _m(_value.m11,_value.m12,_value.m13,_value.m14,
                  _value.m21,_value.m22,_value.m23,_value.m24,
                  _value.m31,_value.m32,_value.m33,_value.m34,
                  _value.m41,_value.m42,_value.m43,_value.m44);
    mConstantTable->SetMatrix(mDevice,getConstantHandle(_name),&_m);
}

void LD3D9Shader::setVector(const LString &_name, const LVector2 &_value)
{
    mConstantTable->SetValue(mDevice,getConstantHandle(_name),(void*)&_value,sizeof(_value));
}

void LD3D9Shader::setVector(const LString &_name, const LVector3 &_value)
{
    mConstantTable->SetValue(mDevice,getConstantHandle(_name),(void*)&_value,sizeof(_value));
}

void LD3D9Shader::setVector(const LString &_name, const LVector4 &_value)
{
    mConstantTable->SetValue(mDevice,getConstantHandle(_name),(void*)&_value,sizeof(_value));
}

void LD3D9Shader::setValue(const LString &_name, const void *_value, u32 _value_size)
{
    mConstantTable->SetValue(mDevice,getConstantHandle(_name),_value,_value_size);
}




#endif

LNAMESPACE_END
