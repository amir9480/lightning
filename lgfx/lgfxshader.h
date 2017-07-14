#ifndef LGFXSHADER_H
#define LGFXSHADER_H

#include "lcore.h"
#include "lgfxtexture.h"

LNAMESPACE_BEGIN

class LAPI LGFXShader
{
public:
    enum class ShaderType
    {
        vertexShader,
        pixelShader
    };

public:
    LGFXShader();
    virtual ~LGFXShader();

    virtual bool                    compile(const LString& _content,const LString& _main_function_name)=0;

    virtual void                    destroy()=0;

    LString                         getContent() const;

    virtual ShaderType              getType() const=0;

    virtual void                    preReset()=0;

    virtual void                    postReset()=0;

    virtual void                    setBool(const LString& _name,bool _value)=0;

    virtual void                    setBoolArray(const LString& _name,const bool* _value,u32 _count)=0;

    virtual void                    setFloat(const LString& _name,float _value)=0;

    virtual void                    setFloatArray(const LString& _name,const float* _value,u32 _count)=0;

    virtual void                    setInt(const LString& _name,int _value)=0;

    virtual void                    setIntArray(const LString& _name,const int* _value,u32 _count)=0;

    virtual void                    setMatrix(const LString& _name,const LMatrix& _value)=0;

    virtual void                    setTexture(const LString& _name,LGFXTexture *_texture)=0;

    virtual void                    setVector(const LString& _name,const LVector2& _value)=0;

    virtual void                    setVector(const LString& _name,const LVector3& _value)=0;

    virtual void                    setVector(const LString& _name,const LVector4& _value)=0;

    virtual void                    setValue(const LString& _name,const void* _value,u32 _value_size)=0;

protected:
    LString         mContent;
};

LNAMESPACE_END

#endif // LGFXSHADER_H
