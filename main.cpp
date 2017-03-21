#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "Lightning"
using namespace std;


int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);
    //LTriangle a;
    //a.set(LVector3::left,LVector3::zero,LVector3::up);
    //for (int i = 0; i < 3; ++i) {
        //cout<<a.normal.at(i)<<"\t";
    //}
    LPlane a(LVector3::up,LVector3::up*2.0f);
    cout<<a.isFrontSide(LVector3::up*0.5f)<<endl;

    cout<<"\n\n";
    return 0;
}

