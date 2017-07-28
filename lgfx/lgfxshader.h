#ifndef LGFXSHADER_H
#define LGFXSHADER_H

#include "lcore.h"
#include "lgfxtexture.h"

LNAMESPACE_BEGIN

class LAPI LGFXShader
{
    LNONCOPYABLE_CLASS(LGFXShader)
public:
    enum class ShaderType
    {
        vertexShader,
        pixelShader
    };

public:
    LGFXShader();
    virtual ~LGFXShader();

    //! to compile from string , _main_function_name : entry point function name
    virtual bool                    compile(LString _content, LString _main_function_name)=0;

    //! destroy
    virtual void                    destroy()=0;

    //! get shader source
    LString                         getContent() const;

    //! get Type of shader
    virtual ShaderType              getType() const=0;

    //! before device reset
    virtual void                    preReset()=0;

    //! after device reset
    virtual void                    postReset()=0;

    //! set bool constant
    virtual void                    setBool(const LString& _name,bool _value)=0;

    //! set bool array constant
    virtual void                    setBoolArray(const LString& _name,const bool* _value,u32 _count)=0;

    //! set float constant
    virtual void                    setFloat(const LString& _name,float _value)=0;

    //! set float array constant
    virtual void                    setFloatArray(const LString& _name,const float* _value,u32 _count)=0;

    //! set int constant
    virtual void                    setInt(const LString& _name,int _value)=0;

    //! set int array constant
    virtual void                    setIntArray(const LString& _name,const int* _value,u32 _count)=0;

    //! set matrix constant
    virtual void                    setMatrix(const LString& _name,const LMatrix& _value)=0;

    //! set sampler / texture constant
    virtual void                    setTexture(const LString& _name,LGFXTexture *_texture)=0;

    //! set vector 2d constant
    virtual void                    setVector(const LString& _name,const LVector2& _value)=0;

    //! set vector 3d constant
    virtual void                    setVector(const LString& _name,const LVector3& _value)=0;

    //! set vector 4d constant
    virtual void                    setVector(const LString& _name,const LVector4& _value)=0;

    //! set some value
    virtual void                    setValue(const LString& _name,const void* _value,u32 _value_size)=0;

protected:
    LString         mContent;
    LString         mMainFunction;
};

LNAMESPACE_END

#endif // LGFXSHADER_H
