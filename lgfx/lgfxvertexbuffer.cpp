#include "lgfxvertexbuffer.h"

LNAMESPACE_BEGIN

LGFXVertexDeclaration::LGFXVertexDeclaration(const LVector<LVertexElement> &_es)
{
    mElements=_es;
}

LGFXVertexDeclaration::~LGFXVertexDeclaration()
{

}

LGFXVertexBuffer::LGFXVertexBuffer():
    mCopyData(nullptr),
    mBufferSize(0),
    mElementSize(0),
    mIsDynamic(false),
    mHasMemoryCopy(false)
{

}

LGFXVertexBuffer::~LGFXVertexBuffer()
{
    if(mCopyData)
        delete[] mCopyData;
}

u64 LGFXVertexBuffer::getBufferSize() const
{
    return mBufferSize;
}

u64 LGFXVertexBuffer::getNumberOfElements() const
{
    return mBufferSize/mElementSize;
}

bool LGFXVertexBuffer::isDynamic() const
{
    return mIsDynamic;
}

void LGFXVertexBuffer::updateBuffer(const char *_data)
{
    this->updateBuffer(_data,mElementSize,mBufferSize/mElementSize);
}

u64 LGFXVertexBuffer::getElementSize() const
{
    return mElementSize;
}

bool LGFXVertexBuffer::hasMemoryCopy() const
{
    return mHasMemoryCopy;
}

char *LGFXVertexBuffer::getMemoryVertices() const
{
    return mCopyData;
}

LNAMESPACE_END



