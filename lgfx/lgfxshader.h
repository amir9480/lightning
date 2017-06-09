#ifndef LGFXSHADER_H
#define LGFXSHADER_H

#include "lcore.h"

LNAMESPACE_BEGIN

class LGFXShader
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


protected:
    LString         mContent;
};

LNAMESPACE_END

#endif // LGFXSHADER_H
