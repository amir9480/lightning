//! \cond
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "windows.h"
#include "Lightning"
using namespace std;
using namespace Lightning;


int main(int argc, char **argv)
{
    L_UNUSED(argc);
    L_UNUSED(argv);

   // LString8 a="Hello";
    //LString8 b="Hello";
    //cout<<(a==b)<<endl;
    LString a=L"say Hello World and again Hello to world";
    cout<<a.findFromRight(L"Hello",25)<<endl;
    MessageBoxW(0,a.getData(),L"Test",0);
    cout<<"\n\n";
    return 0;
}

//! \endcond
