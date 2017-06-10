#include <bits/stdc++.h>
#include "Lightning"
//#include "windows.h"


using namespace std;
using namespace Lightning;

ostream& operator<<(ostream& _in,const LString& _str)
{
    _in<<_str.toUTF8().getData();
    return _in;
}

// TODO :
// Dont forget LAPI
// Add Reflection Support

struct MyVertex
{
    LVector3 pos;
    LVector3 normal;
    LVector2 UV0;

    static LGFXVertexDeclaration* Decl;
};
LGFXVertexDeclaration* MyVertex::Decl;

MyVertex _mv[]=
{
    {LVector3(0.0f,0.5f,0.0f),LVector3(1.0f,0.0f,0.0f),LVector2(0,0)},
    {LVector3(0.5f,-0.3f,0.0f),LVector3(0.0f,1.0f,0.0f),LVector2(0,0)},
    {LVector3(-0.5f,-0.3f,0.0f),LVector3(0.0f,0.0f,1.0f),LVector2(0,0)}
};

const char* myShader=
R"(
struct VSInput
{
    float3 pos:POSITION0;
    float3 normal:TEXCOORD0;
    float2 uv:TEXCOORD1;
};

struct VSOut
{
    float4 pos:POSITION0;
    float3 vcolor:TEXCOORD0;
};

VSOut mainVS(VSInput _in)
{
    VSOut o;
    o.pos.xyz=_in.pos;
    o.pos.w=1.0f;
    o.vcolor=_in.normal;
    return o;
}


float4 mainPS(VSOut _in):COLOR0
{
    float4 o=float4(1.0f,1.0f,1.0f,1.0f);
    o.rgb=_in.vcolor;
    return o;
}
)";

int main()
{
    lMainStart();

    LGFXDevice* a=LGFXDevice::create();
    a->initialize(0,1);
    a->setTitle("Hello Lightning");
    cout<<"##"<<sizeof(MyVertex)<<endl;
    MyVertex::Decl=a->createVertexDeclaration({
                                                   {0,LVertexElementType_Float3,LVertexElementUsage_Position,0},
                                                   {0,LVertexElementType_Float3,LVertexElementUsage_TextureCoordinate,0},
                                                   {0,LVertexElementType_Float2,LVertexElementUsage_TextureCoordinate,1}
                                               });

    LGFXVertexBuffer* vb=a->createVertexBuffer();
    vb->updateBuffer((const char*)_mv,sizeof(MyVertex),3);

    LGFXIndexBuffer* ib=a->createIndexBuffer();
    ib->updateBuffer({0,1,2,2,1,0});

    LGFXShader* vs=a->createVertexShader();
    vs->compile(myShader,"mainVS");

    LGFXShader* ps=a->createPixelShader();
    ps->compile(myShader,"mainPS");

    a->setVertexDeclaration(MyVertex::Decl);
    a->setVertexBuffer(0,vb);
    a->setIndexBuffer(ib);
    a->setVertexShader(vs);
    a->setPixelShader(ps);


    while (a->processOSMessage()!=2)
    {
        a->beginScene();
        a->clear();
        a->draw();
        a->endScene();
        a->render();
    }
    a->release();

    delete a;




    cout<<"\n\n";
    lMainEnd();
    return 0;
}




