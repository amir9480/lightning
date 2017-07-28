#include "linput.h"

LNAMESPACE_BEGIN

bool LInput::mKeyDowns[255]={0};
bool LInput::mKeyUps[255]={0};
bool LInput::mKeyPresses[255]={0};
bool LInput::mMouseDowns[32]={0};
bool LInput::mMouseUps[32]={0};
bool LInput::mMousePresses[32]={0};
int LInput::mMouse_x=0;
int LInput::mMouse_y=0;
int LInput::mMouseLast_x=0;
int LInput::mMouseLast_y=0;
int LInput::mMouseWheelDelta=0;

void __linput_set_keyDown(LInput::KeyCode _code,bool _val)
{
    LInput::mKeyDowns[_code]=_val;
}
void __linput_set_keyUp(LInput::KeyCode _code,bool _val)
{
    LInput::mKeyUps[_code]=_val;
}
void __linput_set_keyPress(LInput::KeyCode _code,bool _val)
{
    LInput::mKeyPresses[_code]=_val;
}

bool __linput_get_keyDown(LInput::KeyCode _code)
{
    return LInput::mKeyDowns[_code];
}
bool __linput_get_keyUp(LInput::KeyCode _code)
{
    return LInput::mKeyUps[_code];
}
bool __linput_get_keyPress(LInput::KeyCode _code)
{
    return LInput::mKeyPresses[_code];
}

void __linput_set_mouseDown(LInput::MouseCode _code,bool _val)
{
    LInput::mMouseDowns[_code]=_val;
}
void __linput_set_mouseUp(LInput::MouseCode _code,bool _val)
{
    LInput::mMouseUps[_code]=_val;
}
void __linput_set_mousePress(LInput::MouseCode _code,bool _val)
{
    LInput::mMousePresses[_code]=_val;
}

bool __linput_get_mouseDown(LInput::MouseCode _code)
{
    return LInput::mMouseDowns[_code];
}
bool __linput_get_mouseUp(LInput::MouseCode _code)
{
    return LInput::mMouseUps[_code];
}
bool __linput_get_mousePress(LInput::MouseCode _code)
{
    return LInput::mMousePresses[_code];
}

void __linput_set_mouse_wheel_delta(int _v)
{
    LInput::mMouseWheelDelta = _v;
}

void __linput_set_mouse_pos(int _x,int _y)
{
    static u32 _last_x=_x;
    static u32 _last_y=_y;
    LInput::mMouseLast_x=_last_x;
    LInput::mMouseLast_y=_last_y;
    LInput::mMouse_x=_x;
    LInput::mMouse_y=_y;


    _last_x=_x;
    _last_y=_y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool LInput::isKeyDown(LInput::KeyCode _code)
{
    return mKeyDowns[_code];
}

bool LInput::isKeyUp(LInput::KeyCode _code)
{
    return mKeyUps[_code];
}

bool LInput::isKeyPressed(LInput::KeyCode _code)
{
    return mKeyPresses[_code];
}

bool LInput::isMouseDown(LInput::MouseCode _code)
{
    return mMouseDowns[_code];
}

bool LInput::isMouseUp(LInput::MouseCode _code)
{
    return mMouseUps[_code];
}

bool LInput::isMousePressed(LInput::MouseCode _code)
{
    return mMousePresses[_code];
}

LVector2 LInput::getMousePos()
{
    return LVector2(mMouse_x,mMouse_y);
}

LVector2 LInput::getPreviousMousePos()
{
    return LVector2(mMouseLast_x,mMouseLast_y);
}

LVector2 LInput::getMouseDelta()
{
    return LVector2(mMouse_x-mMouseLast_x,mMouse_y-mMouseLast_y);
}

int LInput::getMouseWheelDelta()
{
    return mMouseWheelDelta;
}

void LInput::resetInputs()
{
    lMemorySet(mKeyDowns,sizeof(mKeyDowns),0);
    lMemorySet(mKeyUps,sizeof(mKeyUps),0);
    lMemorySet(mMouseDowns,sizeof(mMouseDowns),0);
    lMemorySet(mMouseUps,sizeof(mMouseUps),0);
    mMouseLast_x=mMouse_x;
    mMouseLast_y=mMouse_y;
    mMouseWheelDelta=0;
}


LNAMESPACE_END
