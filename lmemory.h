#ifndef LMEMORY_H
#define LMEMORY_H
#include "ldefines.h"

LNAMESPACE_BEGIN

#define LBITMASK(IN) (1<<IN)

//! Compare two memory byte by byte. if was zero memories is equal other wise is first byte-diffrence between a , b
<<<<<<< HEAD
i8 LAPI lMemoryCompare(const void* _a,const void* _b,u32 s);

//! Copy NOT(Byte by Byte) _source memory to _dest memory
void LAPI lMemoryCopy(void* _dest,const void* _source,u32 _copysize);

//! Copy Byte by Byte _source memory to _dest memory
void LAPI lMemoryCopy2(void* _dest,const void* _source,u32 _copysize);

//! Copy from _source memory-content to _dest memory
void LAPI lMemoryMove(void* _dest,const void* _source,u32 _copysize);
=======
i8 lMemoryCompare(const void* _a,const void* _b,u32 s);

//! Copy NOT(Byte by Byte) _source memory to _dest memory
void lMemoryCopy(void* _dest,const void* _source,u32 _copysize);

//! Copy Byte by Byte _source memory to _dest memory
void lMemoryCopy2(void* _dest,const void* _source,u32 _copysize);

//! Copy from _source memory-content to _dest memory
void lMemoryMove(void* _dest,const void* _source,u32 _copysize);
>>>>>>> 4e1b2c6514b92827801431d7569f5fd59851993d

LNAMESPACE_END

#endif // LMEMORY_H
