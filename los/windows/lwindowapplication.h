#ifndef LWINDOWAPPLICATION_H
#define LWINDOWAPPLICATION_H

#include "../lapplication.h"

#if (LOS == LOS_WINDOWS)
#include "windows.h"

LNAMESPACE_BEGIN

LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);


LNAMESPACE_END

#endif
#endif // LWINDOWAPPLICATION_H
