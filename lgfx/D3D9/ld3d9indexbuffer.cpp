#include "ld3d9indexbuffer.h"

LNAMESPACE_BEGIN

#if ( LGFX == LGFX_D3D9 )

LD3D9IndexBuffer::LD3D9IndexBuffer():
    mIndexBuffer(nullptr),
    mDevice(nullptr)
{

}

LD3D9IndexBuffer::~LD3D9IndexBuffer()
{
    this->destroy();
}

void LD3D9IndexBuffer::destroy()
{
    SAFE_RELEASE(mIndexBuffer);
    mBufferSize=0;
    if(mCopyData)
    {
        delete[] mCopyData;
        mCopyData=nullptr;
    }
}

void LD3D9IndexBuffer::getIndices(u32 *&_data) const
{
    u32* d;
    HR(mIndexBuffer->Lock(0,0,(void**)&d,D3DLOCK_READONLY));
    lMemoryCopy((void*)_data,(void*)d,mBufferSize);
    HR(mIndexBuffer->Unlock());
}

void LD3D9IndexBuffer::preReset()
{
    if(!mHasMemoryCopy)
    {
        mTemp=new u32[mBufferSize];
        getIndices(mTemp);
    }
    SAFE_RELEASE(mIndexBuffer);
}

void LD3D9IndexBuffer::postReset()
{
    HR(mDevice->CreateIndexBuffer(mBufferSize,0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&mIndexBuffer,0));
    if(mHasMemoryCopy)
    {
        updateBuffer(mCopyData,mBufferSize/4);
    }
    else
    {
        updateBuffer(mTemp,mBufferSize/4);
        delete[] mTemp;
    }
}

void LD3D9IndexBuffer::updateBuffer(const u32 *_data, u64 _indices_count)
{
    if(_indices_count*4!=mBufferSize)
    {
        destroy();
        mBufferSize=_indices_count*4;
        HR(mDevice->CreateIndexBuffer(_indices_count*4,0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&mIndexBuffer,0));
        if(mHasMemoryCopy)
            mCopyData=new u32[_indices_count];
    }
    u32* _id;
    mIndexBuffer->Lock(0,0,(void**)&_id,0);
    lMemoryCopy(_id,_data,mBufferSize);
    mIndexBuffer->Unlock();
    if(mHasMemoryCopy)
        lMemoryCopy(mCopyData,_data,mBufferSize);
}



#endif

LNAMESPACE_END
