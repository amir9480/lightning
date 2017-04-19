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

    //LString8 a="Hello";
    //LString8 b="Hello";
    //cout<<(a==b)<<endl;
    //ofstream outf("test.txt");
    /*LString a=L"Hello world and hello and Hello";
    LString8 b="hello";
    a=b;
    MessageBoxW(0,a.getData(),L"TEST",MB_OK );*/
    //outf<<a.toUTF8().getData();
    //outf.close();
    LFile a;
    a.open("test.txt",LFile::IOType::IOType_Read);
    cout<<a.getSize()<<endl;
    char str[20];
    cout<<a.tellp()<<endl;
    a.read((void*)str,12);
    cout<<a.tellp()<<endl;
    cout<<str<<endl;
    cout<<a.isEndOfFile()<<endl;

    a.close();

    cout<<"\n\n";
    return 0;
}

//! \endcond
