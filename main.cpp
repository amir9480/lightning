#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "Lightning"
using namespace std;

int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);
    LTriangle a(LVector3::right,LVector3::zero,LVector3::up);
    cout<<a.a1<<" "<<a.a2<<" "<<a.a3<<endl;
    f32 b[3];
    if(!a.getBarycentricCoordinates((LVector3::left+LVector3::back)/3.0f,b))
        return -1;
    for(int i=0;i<3;i++)
        cout<<b[i]<<"\t";
    cout<<"\n\n";
    return 0;
}

