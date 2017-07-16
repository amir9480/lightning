#ifndef LINPUT_H
#define LINPUT_H

#include "lcore.h"

LNAMESPACE_BEGIN

class LAPI LInput
{
    LInput(const LInput&);
    LInput(LInput&&);
    LInput& operator=(const LInput&);
    LInput& operator=(LInput&&);
public:
    //! list of key codes availble
    enum KeyCode
    {
        KeyCode_0 = 1,
        KeyCode_1,
        KeyCode_2,
        KeyCode_3,
        KeyCode_4,
        KeyCode_5,
        KeyCode_6,
        KeyCode_7,
        KeyCode_8,
        KeyCode_9,

        KeyCode_A,
        KeyCode_B,
        KeyCode_C,
        KeyCode_D,
        KeyCode_E,
        KeyCode_F,
        KeyCode_G,
        KeyCode_H,
        KeyCode_I,
        KeyCode_J,
        KeyCode_K,
        KeyCode_L,
        KeyCode_M,
        KeyCode_N,
        KeyCode_O,
        KeyCode_P,
        KeyCode_Q,
        KeyCode_R,
        KeyCode_S,
        KeyCode_T,
        KeyCode_U,
        KeyCode_V,
        KeyCode_W,
        KeyCode_X,
        KeyCode_Y,
        KeyCode_Z,

        KeyCode_F1,
        KeyCode_F2,
        KeyCode_F3,
        KeyCode_F4,
        KeyCode_F5,
        KeyCode_F6,
        KeyCode_F7,
        KeyCode_F8,
        KeyCode_F9,
        KeyCode_F10,
        KeyCode_F11,
        KeyCode_F12,

        KeyCode_Add,
        KeyCode_BackSpace,
        KeyCode_Cancel,
        KeyCode_Clear,
        KeyCode_Dot,
        KeyCode_Divide,
        KeyCode_Escape,
        KeyCode_Execute,
        KeyCode_Enter,
        KeyCode_Select,
        KeyCode_Separator,
        KeyCode_Space,
        KeyCode_Multiply,
        KeyCode_Subtract,
        KeyCode_Tab,
        KeyCode_CapsLock,
        KeyCode_Delete,
        KeyCode_ArrowUp,
        KeyCode_ArrowLeft,
        KeyCode_ArrowDown,
        KeyCode_ArrowRight,
        KeyCode_End,
        KeyCode_Help,
        KeyCode_Home,
        KeyCode_Insert,
        KeyCode_LeftCtrl,
        KeyCode_RightCtrl,
        KeyCode_LeftAlt,
        KeyCode_RightAlt,
        KeyCode_LeftShift,
        KeyCode_RightShift,
        KeyCode_LeftWin,
        KeyCode_RightWin,
        KeyCode_PageUp,
        KeyCode_PageDown,
        KeyCode_NumLock,
        KeyCode_Pause,
        KeyCode_Print,
        KeyCode_PrintScreen,
        KeyCode_VolumeUp,
        KeyCode_VolumeDown,
        KeyCode_VolumeMute,
        KeyCode_ScrollLock
    };

    //! check key push down right last frame
    static bool isKeyDown(KeyCode _code);

    //! check key push up right last frame
    static bool isKeyUp(KeyCode _code);

    //! check key still is down
    static bool isKeyPressed(KeyCode _code);


    //! do reset ( must be called end of every frame )
    static void resetInputs();

protected:
    static bool mKeyDowns[255];
    static bool mKeyUps[255];
    static bool mKeyPresses[255];


    friend void __linput_set_keyDown(LInput::KeyCode,bool);
    friend void __linput_set_keyUp(LInput::KeyCode,bool);
    friend void __linput_set_keyPress(LInput::KeyCode,bool);
    friend bool __linput_get_keyDown(LInput::KeyCode _code);
    friend bool __linput_get_keyUp(LInput::KeyCode _code);
    friend bool __linput_get_keyPress(LInput::KeyCode _code);
};

LNAMESPACE_END

#endif // LINPUT_H
