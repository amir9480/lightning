#include "lgfxindexbuffer.h"

LNAMESPACE_BEGIN



LGFXIndexBuffer::LGFXIndexBuffer():
    mCopyData(nullptr),
    mBufferSize(0),
    mHasMemoryCopy(false)
{

}

LGFXIndexBuffer::~LGFXIndexBuffer()
{

}

bool LGFXIndexBuffer::hasMemoryCopy() const
{
    return mHasMemoryCopy;
}

u32 *LGFXIndexBuffer::getMemoryIndices() const
{
    return mCopyData;
}

void LGFXIndexBuffer::updateBuffer(const LVector<u32> &_data)
{
    this->updateBuffer(_data.getData(),_data.getSize());
}

void LGFXIndexBuffer::updateBuffer(const u32 *_data)
{
    this->updateBuffer(_data,mBufferSize/4);
}

u64 LGFXIndexBuffer::getBufferSize() const
{
    return mBufferSize;
}

u64 LGFXIndexBuffer::getIndicesCount() const
{
    return mBufferSize/4;
}



LNAMESPACE_END
