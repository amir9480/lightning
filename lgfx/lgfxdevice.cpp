#include "lgfxdevice.h"

LNAMESPACE_BEGIN



LGFXDevice::LGFXDevice():
    mMaxSampler(0),
    mMaxVertexBuffer(0),
    mMaxRenderTarget(0),
    mIsActivated(true)
{

}

LGFXDevice::~LGFXDevice()
{

}


void LGFXDevice::resetParameters()
{
    for(u32 i=0;i<mMaxSampler;i++)
        setTexture(i,nullptr);
    mMaxSampler=0;

    for(u16 i=0;i<mMaxVertexBuffer;i++)
    {
        setVertexBuffer(i,nullptr);
        setVertexBufferFrequency(i);
    }
    mMaxVertexBuffer=0;

    for(u32 i=0;i<mMaxRenderTarget;i++)
        setRenderTarget(i,nullptr);
    mMaxSampler=0;


    setVertexDeclaration(nullptr);
    setIndexBuffer(nullptr);
    setVertexShader(nullptr);
    setPixelShader(nullptr);
    setDepthCheckEnable();
    setDepthCheckFunction();
    setFillMode();
    setCullMode();
    setDepthWriteEnable();
    setDepthBias();
    setAlphaBlending();
    setStencilEnable();
    setStencilValue();
    setStencilCheckFunction();
    setStencilFailOperation();
    setStencilDepthFailOperation();
    setStencilPassOperation();
    setBackBufferWriteEnable();
    setViewPort();
}

LNAMESPACE_END
