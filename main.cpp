#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "Lightning"
using namespace std;

int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);

    LBoundingBox a(LVector3(-1.0f,-1.0f,-1.0f),LVector3(1.0f,1.0f,1.0f));
    LBoundingBox b(LVector3(2.0f,2.0f,2.0f),LVector3(3.0f,3.0f,3.0f));
    cout<<a.isIntersect(b)<<endl;

    cout<<"\n\n";
    return 0;
}

