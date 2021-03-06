﻿#ifndef LMEMORY_H
#define LMEMORY_H
#include "ldefines.h"

LNAMESPACE_BEGIN

#define LBITMASK(IN) (1<<IN)

//! set memory
void LAPI lMemorySet(void* _a, u32 _size, char _val=0);

//! Compare two memory byte by byte. if was zero memories is equal other wise is first byte-diffrence between a , b
i8 LAPI lMemoryCompare(const void* _a, const void* _b, u32 s);

//! Copy NOT(Byte by Byte) _source memory to _dest memory
void LAPI lMemoryCopy(void* _dest, const void* _source, u32 _copysize);

//! Copy Byte by Byte _source memory to _dest memory
void LAPI lMemoryCopy2(void* _dest, const void* _source, u32 _copysize);

//! Copy from _source memory-content to _dest memory
void LAPI lMemoryMove(void* _dest, const void* _source, u32 _copysize);

i8 lMemoryCompare(const void* _a, const void* _b, u32 s);

//! Copy NOT(Byte by Byte) _source memory to _dest memory
void lMemoryCopy(void* _dest, const void* _source, u32 _copysize);

//! Copy Byte by Byte _source memory to _dest memory
void lMemoryCopy2(void* _dest, const void* _source, u32 _copysize);

//! Copy from _source memory-content to _dest memory
void lMemoryMove(void* _dest, const void* _source, u32 _copysize);

LNAMESPACE_END

#endif // LMEMORY_H
