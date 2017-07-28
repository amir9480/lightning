#ifndef LMEMORYSTREAM_H
#define LMEMORYSTREAM_H

#include "ldefines.h"
#include "lmathutility.h"
#include "lmemory.h"

LNAMESPACE_BEGIN

//! To hold on memory streams
class LAPI LMemoryStream
{
public:
    LMemoryStream();
    LMemoryStream(const LMemoryStream& _other);
    LMemoryStream(LMemoryStream&& _other);
    virtual ~LMemoryStream();

    //! to destroy any thing holding by this
    void        destroy();

    //! get Data
    char*       getData();

    //! get Data Size
    u64 getSize() const;

    //! is write/read position on end of stream
    bool        isEndOfStream()const;

    //! to resize stream
    void        resize(u64 _new_size);

    //! read data from stream
    void        read(void* _data,u64 _size);

    //! seek write/read pointer . set 0 to begin and -1 to end
    void        seekp(i64 _newp);

    //! copy from _data to this
    void        setData(const void* _data);

    //! to set data directly (Note _data must initilized with "new[]"   Not "new" . and _data will be destroyed automatically
    void        setData(void* _data,u64 _size);

    //! returns current pointer offset from first of file
    u64         tellp()const;

    //! write data to stream
    void        write(const void *_data, u64 _size);

    char& operator[](u64 _i);
    char  operator[](u64 _i)const;

    LMemoryStream& operator=(const LMemoryStream& _other);
    LMemoryStream& operator=(LMemoryStream&& _other);

private:
    char*   mData;
    u64     mSize;
    u64     mPointer;
};

LNAMESPACE_END

#endif // LMEMORYSTREAM_H
