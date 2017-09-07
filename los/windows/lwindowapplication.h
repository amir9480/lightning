#ifndef LWINDOWAPPLICATION_H
#define LWINDOWAPPLICATION_H

#include "../lapplication.h"
#include "../../lgfx/lgfxdevice.h"

#if (LOS == LOS_WINDOWS)
#include "windows.h"
#include "windowsx.h"

LNAMESPACE_BEGIN

extern bool __is_changing_window;
extern LMap<HWND,LGFXDevice*> __window_deivces;

LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);


LNAMESPACE_END

#endif
#endif // LWINDOWAPPLICATION_H
