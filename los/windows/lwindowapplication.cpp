#include "lwindowapplication.h"
#include "../lgfx.h"

LNAMESPACE_BEGIN

#if (LOS == LOS_WINDOWS)


LApplication::LApplication()
{

}
LApplication::~LApplication()
{

}

void LApplication::exec()
{

}


LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
    switch(msg)
    {
    case WM_ERASEBKGND:
        return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO  m= (LPMINMAXINFO) lparam;
            m->ptMinTrackSize.x=640;
            m->ptMinTrackSize.y=480;
            break;
        }

    }
    return DefWindowProcW(hwnd,msg,wparam,lparam);
}

#endif

LNAMESPACE_END
