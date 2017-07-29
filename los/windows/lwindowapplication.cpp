#include "lwindowapplication.h"
#include "../../lgfx.h"
#include "../linput.h"

LNAMESPACE_BEGIN

#if (LOS == LOS_WINDOWS)

void __linput_set_keyDown(LInput::KeyCode,bool);
void __linput_set_keyUp(LInput::KeyCode,bool);
void __linput_set_keyPress(LInput::KeyCode,bool);
bool __linput_get_keyDown(LInput::KeyCode _code);
bool __linput_get_keyUp(LInput::KeyCode _code);
bool __linput_get_keyPress(LInput::KeyCode _code);

void __linput_set_mouseDown(LInput::MouseCode,bool);
void __linput_set_mouseUp(LInput::MouseCode,bool);
void __linput_set_mousePress(LInput::MouseCode,bool);
bool __linput_get_mouseDown(LInput::MouseCode _code);
bool __linput_get_mouseUp(LInput::MouseCode _code);
bool __linput_get_mousePress(LInput::MouseCode _code);

void __linput_set_mouse_pos(int _x,int _y);
void __linput_set_mouse_wheel_delta(int _v);


bool __is_changing_window=false;
LMap<HWND,LGFXDevice*> __window_deivces;

LApplication::LApplication()
{

}
LApplication::~LApplication()
{

}

void LApplication::exec()
{

}

void lShowMessageBox(const LString& _title,const LString& _content)
{
    MessageBoxW((HWND)NULL,_content.getData(),_title.getData(),MB_OK);
}

LRESULT CALLBACK lightningmainwindowproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
    switch(msg)
    {
    case WM_CREATE:
    {
        if(__is_changing_window)
            break;
        break;
    }
    case WM_ERASEBKGND:
        return 0;
        break;
    case WM_DESTROY:
        if(__is_changing_window)
            break;
        PostQuitMessage(0);
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO  m= (LPMINMAXINFO) lparam;
            m->ptMinTrackSize.x=640;
            m->ptMinTrackSize.y=480;
            break;
        }
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __LIGHTNING_KEY_UPDATE(_WIN_CODE,_LIGHTNING_CODE)\
    case _WIN_CODE:\
    {\
        if(msg==WM_KEYDOWN)\
        {\
            if(__linput_get_keyPress(_LIGHTNING_CODE)==false)\
            {\
                __linput_set_keyDown(_LIGHTNING_CODE,true);\
                __linput_set_keyPress(_LIGHTNING_CODE,true);\
            }\
        }\
        else if(msg==WM_KEYUP)\
        {\
            if(__linput_get_keyPress(_LIGHTNING_CODE)==true)\
            {\
                __linput_set_keyUp(_LIGHTNING_CODE,true);\
                __linput_set_keyPress(_LIGHTNING_CODE,false);\
            }\
        }\
        break;\
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
    case WM_KEYDOWN:case WM_KEYUP:
    {
        WPARAM _wparam = wparam;
        //! check Shift/Alt/Ctrl is right or left
        switch (wparam)
        {
        case VK_SHIFT:
            _wparam=MapVirtualKey((lparam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
            break;
        case VK_CONTROL:
            _wparam=MapVirtualKey((lparam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
            break;
        case VK_MENU:
            _wparam=MapVirtualKey((lparam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
            break;
        default:
            break;
        }
        switch (_wparam)
        {
        __LIGHTNING_KEY_UPDATE('0',LInput::KeyCode_0);
        __LIGHTNING_KEY_UPDATE('1',LInput::KeyCode_1);
        __LIGHTNING_KEY_UPDATE('2',LInput::KeyCode_2);
        __LIGHTNING_KEY_UPDATE('3',LInput::KeyCode_3);
        __LIGHTNING_KEY_UPDATE('4',LInput::KeyCode_4);
        __LIGHTNING_KEY_UPDATE('5',LInput::KeyCode_5);
        __LIGHTNING_KEY_UPDATE('6',LInput::KeyCode_6);
        __LIGHTNING_KEY_UPDATE('7',LInput::KeyCode_7);
        __LIGHTNING_KEY_UPDATE('8',LInput::KeyCode_8);
        __LIGHTNING_KEY_UPDATE('9',LInput::KeyCode_9);

        __LIGHTNING_KEY_UPDATE(VK_NUMPAD0,LInput::KeyCode_0);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD1,LInput::KeyCode_1);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD2,LInput::KeyCode_2);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD3,LInput::KeyCode_3);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD4,LInput::KeyCode_4);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD5,LInput::KeyCode_5);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD6,LInput::KeyCode_6);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD7,LInput::KeyCode_7);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD8,LInput::KeyCode_8);
        __LIGHTNING_KEY_UPDATE(VK_NUMPAD9,LInput::KeyCode_9);

        __LIGHTNING_KEY_UPDATE('A',LInput::KeyCode_A);
        __LIGHTNING_KEY_UPDATE('B',LInput::KeyCode_B);
        __LIGHTNING_KEY_UPDATE('C',LInput::KeyCode_C);
        __LIGHTNING_KEY_UPDATE('D',LInput::KeyCode_D);
        __LIGHTNING_KEY_UPDATE('E',LInput::KeyCode_E);
        __LIGHTNING_KEY_UPDATE('F',LInput::KeyCode_F);
        __LIGHTNING_KEY_UPDATE('G',LInput::KeyCode_G);
        __LIGHTNING_KEY_UPDATE('H',LInput::KeyCode_H);
        __LIGHTNING_KEY_UPDATE('I',LInput::KeyCode_I);
        __LIGHTNING_KEY_UPDATE('J',LInput::KeyCode_J);
        __LIGHTNING_KEY_UPDATE('K',LInput::KeyCode_K);
        __LIGHTNING_KEY_UPDATE('L',LInput::KeyCode_L);
        __LIGHTNING_KEY_UPDATE('M',LInput::KeyCode_M);
        __LIGHTNING_KEY_UPDATE('N',LInput::KeyCode_N);
        __LIGHTNING_KEY_UPDATE('O',LInput::KeyCode_O);
        __LIGHTNING_KEY_UPDATE('P',LInput::KeyCode_P);
        __LIGHTNING_KEY_UPDATE('Q',LInput::KeyCode_Q);
        __LIGHTNING_KEY_UPDATE('R',LInput::KeyCode_R);
        __LIGHTNING_KEY_UPDATE('S',LInput::KeyCode_S);
        __LIGHTNING_KEY_UPDATE('T',LInput::KeyCode_T);
        __LIGHTNING_KEY_UPDATE('U',LInput::KeyCode_U);
        __LIGHTNING_KEY_UPDATE('V',LInput::KeyCode_V);
        __LIGHTNING_KEY_UPDATE('W',LInput::KeyCode_W);
        __LIGHTNING_KEY_UPDATE('X',LInput::KeyCode_X);
        __LIGHTNING_KEY_UPDATE('Y',LInput::KeyCode_Y);
        __LIGHTNING_KEY_UPDATE('Z',LInput::KeyCode_Z);

        __LIGHTNING_KEY_UPDATE(VK_F1,LInput::KeyCode_F1);
        __LIGHTNING_KEY_UPDATE(VK_F2,LInput::KeyCode_F2);
        __LIGHTNING_KEY_UPDATE(VK_F3,LInput::KeyCode_F3);
        __LIGHTNING_KEY_UPDATE(VK_F4,LInput::KeyCode_F4);
        __LIGHTNING_KEY_UPDATE(VK_F5,LInput::KeyCode_F5);
        __LIGHTNING_KEY_UPDATE(VK_F6,LInput::KeyCode_F6);
        __LIGHTNING_KEY_UPDATE(VK_F7,LInput::KeyCode_F7);
        __LIGHTNING_KEY_UPDATE(VK_F8,LInput::KeyCode_F8);
        __LIGHTNING_KEY_UPDATE(VK_F9,LInput::KeyCode_F9);
        __LIGHTNING_KEY_UPDATE(VK_F10,LInput::KeyCode_F10);
        __LIGHTNING_KEY_UPDATE(VK_F11,LInput::KeyCode_F11);
        __LIGHTNING_KEY_UPDATE(VK_F12,LInput::KeyCode_F12);

        __LIGHTNING_KEY_UPDATE(VK_ADD,LInput::KeyCode_Add);
        __LIGHTNING_KEY_UPDATE(VK_OEM_PLUS,LInput::KeyCode_Add);
        __LIGHTNING_KEY_UPDATE(VK_DIVIDE,LInput::KeyCode_Divide);
        __LIGHTNING_KEY_UPDATE(VK_OEM_2,LInput::KeyCode_Divide);
        __LIGHTNING_KEY_UPDATE(VK_SUBTRACT,LInput::KeyCode_Subtract);
        __LIGHTNING_KEY_UPDATE(VK_OEM_MINUS,LInput::KeyCode_Subtract);
        __LIGHTNING_KEY_UPDATE(VK_MULTIPLY,LInput::KeyCode_Multiply);

        __LIGHTNING_KEY_UPDATE(VK_BACK,LInput::KeyCode_BackSpace);
        __LIGHTNING_KEY_UPDATE(VK_CANCEL,LInput::KeyCode_Cancel);
        __LIGHTNING_KEY_UPDATE(VK_CLEAR,LInput::KeyCode_Clear);
        __LIGHTNING_KEY_UPDATE(VK_DECIMAL,LInput::KeyCode_Dot);
        __LIGHTNING_KEY_UPDATE(VK_OEM_PERIOD,LInput::KeyCode_Dot);
        __LIGHTNING_KEY_UPDATE(VK_ESCAPE,LInput::KeyCode_Escape);
        __LIGHTNING_KEY_UPDATE(VK_EXECUTE,LInput::KeyCode_Execute);
        __LIGHTNING_KEY_UPDATE(VK_RETURN,LInput::KeyCode_Enter);
        __LIGHTNING_KEY_UPDATE(VK_SELECT,LInput::KeyCode_Select);
        __LIGHTNING_KEY_UPDATE(VK_SEPARATOR,LInput::KeyCode_Separator);
        __LIGHTNING_KEY_UPDATE(VK_SPACE,LInput::KeyCode_Space);
        __LIGHTNING_KEY_UPDATE(VK_TAB,LInput::KeyCode_Tab);
        __LIGHTNING_KEY_UPDATE(VK_CAPITAL,LInput::KeyCode_CapsLock);
        __LIGHTNING_KEY_UPDATE(VK_DELETE,LInput::KeyCode_Delete);
        __LIGHTNING_KEY_UPDATE(VK_UP,LInput::KeyCode_ArrowUp);
        __LIGHTNING_KEY_UPDATE(VK_DOWN,LInput::KeyCode_ArrowDown);
        __LIGHTNING_KEY_UPDATE(VK_LEFT,LInput::KeyCode_ArrowLeft);
        __LIGHTNING_KEY_UPDATE(VK_RIGHT,LInput::KeyCode_ArrowRight);
        __LIGHTNING_KEY_UPDATE(VK_END,LInput::KeyCode_End);
        __LIGHTNING_KEY_UPDATE(VK_HELP,LInput::KeyCode_Help);
        __LIGHTNING_KEY_UPDATE(VK_LCONTROL,LInput::KeyCode_LeftCtrl);
        __LIGHTNING_KEY_UPDATE(VK_RCONTROL,LInput::KeyCode_RightCtrl);
        __LIGHTNING_KEY_UPDATE(VK_LMENU,LInput::KeyCode_LeftAlt);
        __LIGHTNING_KEY_UPDATE(VK_RMENU,LInput::KeyCode_RightAlt);
        __LIGHTNING_KEY_UPDATE(VK_LSHIFT,LInput::KeyCode_LeftShift);
        __LIGHTNING_KEY_UPDATE(VK_RSHIFT,LInput::KeyCode_RightShift);
        __LIGHTNING_KEY_UPDATE(VK_LWIN,LInput::KeyCode_LeftWin);
        __LIGHTNING_KEY_UPDATE(VK_RWIN,LInput::KeyCode_RightWin);
        __LIGHTNING_KEY_UPDATE(VK_NEXT,LInput::KeyCode_PageDown);
        __LIGHTNING_KEY_UPDATE(VK_PRIOR,LInput::KeyCode_PageUp);
        __LIGHTNING_KEY_UPDATE(VK_NUMLOCK,LInput::KeyCode_NumLock);
        __LIGHTNING_KEY_UPDATE(VK_PAUSE,LInput::KeyCode_Pause);
        __LIGHTNING_KEY_UPDATE(VK_PRINT,LInput::KeyCode_Print);
        __LIGHTNING_KEY_UPDATE(VK_SCROLL,LInput::KeyCode_ScrollLock);
        __LIGHTNING_KEY_UPDATE(VK_SNAPSHOT,LInput::KeyCode_PrintScreen);
        __LIGHTNING_KEY_UPDATE(VK_VOLUME_DOWN,LInput::KeyCode_VolumeDown);
        __LIGHTNING_KEY_UPDATE(VK_VOLUME_UP,LInput::KeyCode_VolumeUp);
        __LIGHTNING_KEY_UPDATE(VK_VOLUME_MUTE,LInput::KeyCode_VolumeMute);

        default:
            break;
        }
        break;
    }

    case WM_MOUSEMOVE:
    {
        POINT _p;
        GetCursorPos(&_p);
        __linput_set_mouse_pos(_p.x,_p.y);
        break;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __LIGHTNING_MOUSE_KEY_UPDATE(_WIN_CODE_DOWN,_WIN_CODE_UP,_LIGHTNING_CODE)\
    case _WIN_CODE_DOWN:\
    {\
        if(__linput_get_mousePress(_LIGHTNING_CODE)==false)\
        {\
            __linput_set_mouseDown(_LIGHTNING_CODE,true);\
            __linput_set_mousePress(_LIGHTNING_CODE,true);\
        }\
        break;\
    }\
    case _WIN_CODE_UP:\
    {\
        if(__linput_get_mousePress(_LIGHTNING_CODE)==true)\
        {\
            __linput_set_mouseUp(_LIGHTNING_CODE,true);\
            __linput_set_mousePress(_LIGHTNING_CODE,false);\
        }\
        break;\
    }

    __LIGHTNING_MOUSE_KEY_UPDATE(WM_LBUTTONDOWN,WM_LBUTTONUP,LInput::MouseCode_left)
    __LIGHTNING_MOUSE_KEY_UPDATE(WM_RBUTTONDOWN,WM_RBUTTONUP,LInput::MouseCode_right)
    __LIGHTNING_MOUSE_KEY_UPDATE(WM_MBUTTONDOWN,WM_MBUTTONUP,LInput::MouseCode_middle)

    case WM_MOUSEWHEEL:
    {
        __linput_set_mouse_wheel_delta(GET_WHEEL_DELTA_WPARAM(wparam)/120);
        break;
    }
    }
    return DefWindowProcW(hwnd,msg,wparam,lparam);
}

#endif

LNAMESPACE_END
