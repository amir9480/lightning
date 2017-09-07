#ifndef LGFXINDEXBUFFER_H
#define LGFXINDEXBUFFER_H
#include "../lcore/ldefines.h"
#include "../lcore/lutility.h"
#include "../lcore/lvector.h"

LNAMESPACE_BEGIN

//! to hold index buffers
class LAPI LGFXIndexBuffer
{
    LNONCOPYABLE_CLASS(LGFXIndexBuffer)

    friend class LGFXDevice;
public:
    LGFXIndexBuffer();
    virtual ~LGFXIndexBuffer();

    //! to destroy index buffer
    virtual void                    destroy()=0;

    //! get buffer size in Bytes
    u64                             getBufferSize() const;

    //! copy indicies to a Memory Stream
    virtual void                    getIndices(u32*& _data)const=0;

    //! get count of indices
    u64                             getIndicesCount()const;

    //! check has memory copy
    bool                            hasMemoryCopy() const;

    //! get memory copy data
    u32*                            getMemoryIndices()const;

    //! before device reset
    virtual void                    preReset()=0;

    //! after device reset
    virtual void                    postReset()=0;

    //! update index buffer
    void                            updateBuffer(const LVector<u32> &_data);

    //! update index buffer
    void                            updateBuffer(const u32* _data);

    //! update index buffer, _indices_count must be same getIndicesCount()
    virtual void                    updateBuffer(const u32* _data,u64 _indices_count)=0;

protected:
    u32*  mCopyData;
    u64   mBufferSize;
    bool  mHasMemoryCopy:1;


    u32* mTemp;
};

LNAMESPACE_END

#endif // LGFXINDEXBUFFER_H
