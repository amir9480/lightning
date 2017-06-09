#ifndef LAPPLICATION_H
#define LAPPLICATION_H

#include "../lcore.h"

LNAMESPACE_BEGIN

class LApplication
{
public:
    LApplication();
    virtual ~LApplication();

    void exec();
};

LNAMESPACE_END


#endif // LAPPLICATION_H
