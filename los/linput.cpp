#include "linput.h"

LNAMESPACE_BEGIN

bool LInput::mKeyDowns[255]={0};
bool LInput::mKeyUps[255]={0};
bool LInput::mKeyPresses[255]={0};

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

void LInput::resetInputs()
{
    lMemorySet(mKeyDowns,sizeof(mKeyDowns),0);
    lMemorySet(mKeyUps,sizeof(mKeyUps),0);
}


LNAMESPACE_END
