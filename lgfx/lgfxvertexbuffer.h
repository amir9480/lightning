#ifndef LGFXVERTEXBUFFER_H
#define LGFXVERTEXBUFFER_H

#include "../lcore/ldefines.h"
#include "../lcore/lvector.h"

LNAMESPACE_BEGIN

enum LVertexElementType
{
    LVertexElementType_Float1,
    LVertexElementType_Float2,
    LVertexElementType_Float3,
    LVertexElementType_Float4,
    LVertexElementType_UByte4,
    LVertexElementType_Short2,
    LVertexElementType_Short4,

    //LVertexElementType_Float16_2,
    //LVertexElementType_Float16_4
};

enum LVertexElementUsage
{
    LVertexElementUsage_Position,
    LVertexElementUsage_BlendWeight,
    LVertexElementUsage_Normal,
    LVertexElementUsage_Tangent,
    LVertexElementUsage_BiNormal,
    LVertexElementUsage_TextureCoordinate
};

//! holds one vertex element type
struct LAPI LVertexElement
{
    //! number of stream
    u16                 mStreamNumber;
    //! vertex type
    LVertexElementType  mType;
    //! usage of vertex
    LVertexElementUsage mUsage;
    //! usage index
    u8                  mUsageIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LGFXDevice;

class LAPI LGFXVertexDeclaration
{
    LNONCOPYABLE_CLASS(LGFXVertexDeclaration)
public:
    LGFXVertexDeclaration(const LVector<LVertexElement>& _es);
    virtual ~LGFXVertexDeclaration();

    virtual void                            destroy()=0;

    virtual const LVector<LVertexElement>&  getElements()=0;

    virtual u32                             getElementsSize()=0;

    virtual void                            preReset()=0;

    virtual void                            postReset()=0;

protected:
    LVector<LVertexElement> mElements;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class LAPI LGFXVertexBuffer
{
    LNONCOPYABLE_CLASS(LGFXVertexBuffer)
    friend class LGFXDevice;
public:
    LGFXVertexBuffer();
    virtual ~LGFXVertexBuffer();

    //! destroy
    virtual void                    destroy()=0;

    //! note that prepare _Data memory before call this function
    //! needed size to prepare is getBufferSize
    virtual void                    getVertices(char*& _Data)const=0;

    //! call this if vertex buffer has memory copy : getHasMemoryCopy.
    //! this recommended for frequency reading buffer
    char*                           getMemoryVertices() const;

    //! get one element size in Bytes
    u64                             getElementSize() const;

    //! check has memory copy
    bool                            hasMemoryCopy() const;

    //! get all elements size in Byte
    u64                             getBufferSize() const;

    //! get Count of elements
    u64                             getNumberOfElements()const;

    //! check is dynamic
    bool                            isDynamic() const;

    //! before device reset
    virtual void                    preReset()=0;

    //! after device reset
    virtual void                    postReset()=0;

    //! update vertex buffer content
    void                            updateBuffer(const char* _data);

    //! to update vertex buffer content . it's recommended to _element size be getElementSize() and _number_of_elements be getNumberOfElements() . if was not then new buffer will created
    virtual void                    updateBuffer(const char* _data,u64 _elementSize,u64 _number_of_elements)=0;


protected:
    char* mCopyData;// based on memory to get more speed for read frequency vertex buffers
    u64   mBufferSize;
    u64   mElementSize;
    bool  mIsDynamic:1;
    bool  mHasMemoryCopy:1;

    char* mTemp;// just a temp for every object
};


LNAMESPACE_END

#endif // LGFXVERTEXBUFFER_H
