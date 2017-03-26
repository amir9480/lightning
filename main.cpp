#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "Lightning"
using namespace std;

int main(int argc, char *argv[])
{
    L_UNUSED(argc);
    L_UNUSED(argv);

    LRay r(LVector3(-2.0f,3.0f,2.0f),LVector3::down);

    LTriangle t(LVector3::left*3.0f,LVector3::zero,LVector3::forward*3.0f);

    cout<<r.isIntersect(t)<<endl;

    for(int i=0;i<3;i++)
        cout<<r.getPoint(r.isIntersect(t)).at(i)<<"\t";

    cout<<"\n\n";

    for(int i=0;i<3;i++)
        cout<<t.mNormal.at(i)<<"\t";

    cout<<"\n\n";
    return 0;
}

