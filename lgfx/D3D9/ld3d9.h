#ifndef LD3D9_H
#define LD3D9_H

#if ( LGFX == LGFX_D3D9 )

#include "d3d9.h"
#include "d3dx9.h"

// check HRESULT returns
#define HR(X)\
{\
    HRESULT __hr=X;\
    if(FAILED(__hr))\
    {\
        lError2(1,"ERROR");\
        exit(-1);\
    }\
}

//! check some thing is  NotZero (NZ)
#define NZ(X)\
{\
if(NULL==(X))\
{\
    LString _erm="Error:";\
    _erm += __FILE__;\
    _erm += ":";\
    _erm += LString::fromUInt(__LINE__);\
    _erm += "\n";\
    lError2(1,_erm);\
    exit(-1);\
}\
}

//! SAFE Release D3D Obejcts
#define SAFE_RELEASE(X)\
{\
    if(X)\
    {\
        X->Release();\
        X=NULL;\
    }\
}

#endif

#endif // LD3D9_H
