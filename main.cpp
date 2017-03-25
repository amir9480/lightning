#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "Lightning"
using namespace std;

int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);
    LBoundingSphere a(LVector3::left,2.0f);
    LBoundingSphere b(LVector3::right,2.0f);
    a.merge(b);
    for(int i=0;i<3;i++)
        cout<<a.getPos().at(i)<<"\t";
    cout<<"\n"<<a.getRadius()<<endl;

    return 0;
}

