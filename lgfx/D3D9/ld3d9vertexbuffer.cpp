#include "ld3d9vertexbuffer.h"
#include "ld3d9device.h"

LNAMESPACE_BEGIN

#if ( LGFX == LGFX_D3D9 )

LVector<D3DVERTEXELEMENT9> getVertexDecl(const LVector<LVertexElement> &_in)
{
    LVector<D3DVERTEXELEMENT9> o;
    D3DVERTEXELEMENT9 e;
    LMap<u64,u64>offsets;

    for(u32 i=0;i<_in.getSize();i++)
    {
        lMemorySet(&e,sizeof(e));
        e.Stream=_in[i].mStreamNumber;
        if(offsets.findKey(_in[i].mStreamNumber)==offsets.nothing)
            offsets.insert(_in[i].mStreamNumber,0);

        e.Offset=offsets[_in[i].mStreamNumber];
        e.UsageIndex=_in[i].mUsageIndex;

        switch (_in[i].mType )
        {
        case LVertexElementType_Float1:
            offsets[_in[i].mStreamNumber]+=4;
            e.Type=D3DDECLTYPE_FLOAT1;
            break;
        case LVertexElementType_Float2:
            offsets[_in[i].mStreamNumber]+=8;
            e.Type=D3DDECLTYPE_FLOAT2;
            break;
        case LVertexElementType_Float3:
            offsets[_in[i].mStreamNumber]+=12;
            e.Type=D3DDECLTYPE_FLOAT3;
            break;
        case LVertexElementType_Float4:
            offsets[_in[i].mStreamNumber]+=16;
            e.Type=D3DDECLTYPE_FLOAT4;
            break;
        case LVertexElementType_UByte4:
            offsets[_in[i].mStreamNumber]+=4;
            e.Type=D3DDECLTYPE_UBYTE4;
            break;
        case LVertexElementType_Short2:
            offsets[_in[i].mStreamNumber]+=2;
            e.Type=D3DDECLTYPE_SHORT2;
            break;
        case LVertexElementType_Short4:
            offsets[_in[i].mStreamNumber]+=4;
            e.Type=D3DDECLTYPE_SHORT4;
            break;
        }

        switch (_in[i].mUsage)
        {
        case LVertexElementUsage_Position:
            e.Usage=D3DDECLUSAGE_POSITION;
            break;
        case LVertexElementUsage_BlendWeight:
            e.Usage=D3DDECLUSAGE_BLENDWEIGHT;
            break;
        case LVertexElementUsage_Normal:
            e.Usage=D3DDECLUSAGE_NORMAL;
            break;
        case LVertexElementUsage_Tangent:
            e.Usage=D3DDECLUSAGE_TANGENT;
            break;
        case LVertexElementUsage_BiNormal:
            e.Usage=D3DDECLUSAGE_BINORMAL;
            break;
        case LVertexElementUsage_TextureCoordinate:
            e.Usage=D3DDECLUSAGE_TEXCOORD;
            break;
        }
        o.pushBack(e);
    }

    o.pushBack(D3DDECL_END());
    return o;
}

LD3D9VertexDeclaration::LD3D9VertexDeclaration(const LVector<LVertexElement> &_es):
    LGFXVertexDeclaration(_es),
    mDecl(nullptr),
    mDevice(nullptr)
{

}

LD3D9VertexDeclaration::~LD3D9VertexDeclaration()
{
    this->destroy();
}

void LD3D9VertexDeclaration::destroy()
{
    SAFE_RELEASE(mDecl);
}

const LVector<LVertexElement> &LD3D9VertexDeclaration::getElements()
{
    return mElements;
}

u32 LD3D9VertexDeclaration::getElementsSize()
{
    u32 o=0;
    for(u32 i=0;i<mElements.getSize();i++)
    {
        switch (mElements[i].mType )
        {
        case LVertexElementType_Float1:
            o+=4;
            break;
        case LVertexElementType_Float2:
            o+=8;
            break;
        case LVertexElementType_Float3:
            o+=12;
            break;
        case LVertexElementType_Float4:
            o+=16;
            break;
        case LVertexElementType_UByte4:
            o+=4;
            break;
        case LVertexElementType_Short2:
            o+=2;
            break;
        case LVertexElementType_Short4:
            o+=4;
            break;
        }
    }
    return o;
}

void LD3D9VertexDeclaration::preReset()
{
    SAFE_RELEASE(mDecl);
}

void LD3D9VertexDeclaration::postReset()
{
    HR(mDevice->mDevice->CreateVertexDeclaration(getVertexDecl(mElements).getData(),&mDecl));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

LD3D9VertexBuffer::LD3D9VertexBuffer():
    mVertexBuffer(nullptr),
    mDevice(nullptr)
{
}

LD3D9VertexBuffer::~LD3D9VertexBuffer()
{
    this->destroy();
}

void LD3D9VertexBuffer::destroy()
{
    SAFE_RELEASE(mVertexBuffer);
    this->mBufferSize=0;
    if(mCopyData)
    {
        delete[] mCopyData;
        mCopyData=nullptr;
    }
}

void LD3D9VertexBuffer::getVertices(char *&_data)const
{
    char* d;
    HR(mVertexBuffer->Lock(0,0,(void**)&d,D3DLOCK_READONLY));
    lMemoryCopy((void*)_data,(void*)d,mBufferSize);
    HR(mVertexBuffer->Unlock());
}

void LD3D9VertexBuffer::preReset()
{
//    if(!mHasMemoryCopy)
//    {
//        mTemp=new char[mBufferSize];
//        getVertices(mTemp);
//    }
//    SAFE_RELEASE(mVertexBuffer);
}

void LD3D9VertexBuffer::postReset()
{
//    HR(mDevice->mDevice->CreateVertexBuffer(mBufferSize,((mIsDynamic)?D3DUSAGE_DYNAMIC:0),0,D3DPOOL_DEFAULT,&mVertexBuffer,0));
//    if(mHasMemoryCopy)
//    {
//        updateBuffer(mCopyData,mElementSize,mBufferSize/mElementSize);
//    }
//    else
//    {
//        updateBuffer(mTemp,mElementSize,mBufferSize/mElementSize);
//        delete[] mTemp;
//    }
}

void LD3D9VertexBuffer::updateBuffer(const char *_data, u64 _elementSize, u64 _number_of_elements)
{
    mElementSize=_elementSize;
    u64 _buffersize=_elementSize*_number_of_elements;

    if(_buffersize!=mBufferSize)
    {
        this->destroy();
        HR(mDevice->mDevice->CreateVertexBuffer(_buffersize,((mIsDynamic)?D3DUSAGE_DYNAMIC:0),0,D3DPOOL_MANAGED,&mVertexBuffer,0));
        mBufferSize=_buffersize;
        if(mHasMemoryCopy)
            mCopyData=new char[_buffersize];
    }
    char* _vd;
    HR(mVertexBuffer->Lock(0,0,(void**)&_vd,0));
    lMemoryCopy(_vd,_data,_buffersize);
    HR(mVertexBuffer->Unlock());
    if(mHasMemoryCopy)
        lMemoryCopy(mCopyData,_data,_buffersize);
}

#endif

LNAMESPACE_END
