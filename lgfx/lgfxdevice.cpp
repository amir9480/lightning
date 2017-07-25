#include "lgfxdevice.h"

LNAMESPACE_BEGIN



LGFXDevice::LGFXDevice():
    mMaxSampler(0),
    mMaxVertexBuffer(0)
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
        setVertexBuffer(i,nullptr);
    setVertexDeclaration(nullptr);
    setIndexBuffer(nullptr);
    setVertexShader(nullptr);
    setPixelShader(nullptr);
    setDepthCheckEnable();
    setDepthCheckFunction();
    setFillMode();
    setCullMode();
    setDepthWriteEnable();
}

LNAMESPACE_END
