#include <bits/stdc++.h>
#include <windows.h>
#include "Lightning.h"

using namespace std;
using namespace Lightning;

int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);

    LFile a;
    a.open("test.txt",LFile::IOType_Write);
    a.write(LString("Hello World"));
    a.close();

    return 0;
}
