#include "lmemorylog.h"

#if LTARGET == LTARGET_DEBUG

#undef new
#define new new

_lptrlogmanager __lptrlogmanager;

#endif
