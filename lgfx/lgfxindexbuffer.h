#ifndef LGFXINDEXBUFFER_H
#define LGFXINDEXBUFFER_H
#include "lcore.h"

LNAMESPACE_BEGIN

class LAPI LGFXIndexBuffer
{
    friend class LGFXDevice;
public:
    LGFXIndexBuffer();
    virtual ~LGFXIndexBuffer();

    virtual void                    destroy()=0;

    u64                             getBufferSize() const;

    virtual void                    getIndices(u32*& _data)const=0;

    u64                             getIndicesCount()const;

    bool                            hasMemoryCopy() const;

    u32*                            getMemoryIndices()const;

    virtual void                    preReset()=0;

    virtual void                    postReset()=0;

    void                            updateBuffer(const LVector<u32> &_data);

    void                            updateBuffer(const u32* _data);

    virtual void                    updateBuffer(const u32* _data,u64 _indices_count)=0;

protected:
    u32*  mCopyData;
    u64   mBufferSize;
    bool  mHasMemoryCopy:1;


    u32* mTemp;
};

LNAMESPACE_END

#endif // LGFXINDEXBUFFER_H
