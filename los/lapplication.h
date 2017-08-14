#ifndef LAPPLICATION_H
#define LAPPLICATION_H

#include "../lcore.h"
#include "../lgfx.h"

LNAMESPACE_BEGIN

void LAPI lShowMessageBox(const LString& _title,const LString& _content);

void LAPI lSetConsoleColor(LConsoleColor _text_color,LConsoleColor _background_color);

void LAPI lConsoleClear();

LPoint LAPI lGetMousePos();

class LAPI LApplication
{
public:
    LApplication();
    virtual ~LApplication();

    void exec();
};

LNAMESPACE_END


#endif // LAPPLICATION_H
