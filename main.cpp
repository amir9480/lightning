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
// *** Make Shared Pointer Thread Safe
// *** Make Image::loadFromPNG Thread Safe

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
    {LVector3(-0.5f,0.5f,0.0f)  ,LVector3(0.0f,0.0f,-1.0f)  ,LVector2(0,0)},
    {LVector3(0.5f,0.5f,0.0f)   ,LVector3(0.0f,0.0f,-1.0f)  ,LVector2(1,0)},
    {LVector3(-0.5f,-0.5f,0.0f) ,LVector3(0.0f,0.0f,-1.0f)  ,LVector2(0,1)},
    {LVector3(0.5f,-0.5f,0.0f)  ,LVector3(0.0f,0.0f,-1.0f)  ,LVector2(1,1)}
};

const char* myShader=
R"(
uniform extern float3 testvalue;
uniform extern float4x4 WVP;

uniform extern sampler2D t0;

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
    float2 uv:TEXCOORD1;
};


VSOut mainVS(VSInput _in)
{
    VSOut o;
    o.pos.xyz=_in.pos;
    o.pos.w=1.0f;
    o.pos=mul(o.pos,WVP);
    o.vcolor=_in.normal;
    o.uv=_in.uv;
    return o;
}


float4 mainPS(VSOut _in):COLOR0
{
    float4 o=float4(0.0f,0.0f,0.0f,1.0f);
    //o.rgb=_in.vcolor*testvalue;
    o.rgb=tex2D(t0,_in.uv.xy).rgb+testvalue;
    //o.rgb+=0.1;
    return o;
}



)";


int main()
{
    lMemoryLogStart();


    LImage te=LImage::loadFromPngFile("image.png");
    //te.init(8,8,LImage::Format::Format_A8R8G8B8);
    //for(u32 i=0;i<te.getPixelsCount()*te.getBytePerPixel();i+=4)
    //{
            //te.getData()[i]=255;
            //te.getData()[i+1]=i;
            //te.getData()[i+2]=0;
            //te.getData()[i+3]=0;
    //}

    LGFXDevice* a=LGFXDevice::create();
    a->initialize(0,1);
    a->setTitle("Hello Lightning");
    MyVertex::Decl=a->createVertexDeclaration({
                                                   {0,LVertexElementType_Float3,LVertexElementUsage_Position,0},
                                                   {0,LVertexElementType_Float3,LVertexElementUsage_TextureCoordinate,0},
                                                   {0,LVertexElementType_Float2,LVertexElementUsage_TextureCoordinate,1}
                                               });

    LGFXVertexBuffer* vb=a->createVertexBuffer();
    vb->updateBuffer((const char*)_mv,sizeof(MyVertex),4);

    LGFXIndexBuffer* ib=a->createIndexBuffer();
    ib->updateBuffer({0,1,2,3,2,1});

    LMatrix wvp=LMatrix::createViewMatrixLH(LVector3(0.0f,0.0f,1.5f),LVector3(0.0f,0.15f,0.0f),LVector3(0.0f,1.0f,0.0f))*LMatrix::createPerspectiveProjectionLH(50.0f);

    LGFXShader* vs=a->createVertexShader();
    vs->compile(myShader,"mainVS");
    vs->setMatrix("WVP",wvp);

    cout<<"###"<<te.getWidth()<<" "<<te.getHeight()<<endl;

    LGFXTexture* texture1=a->createTexture(te.getWidth(),te.getHeight(),1,LImage::Format_X8R8G8B8);
    if(texture1!=nullptr)
        texture1->updateTexture(0,te);

    LGFXShader* ps=a->createPixelShader();
    ps->compile(myShader,"mainPS");
    ps->setVector("testvalue",LVector3(0.0f,0.0f,0.0f));
    if(texture1!=nullptr)
        ps->setTexture("t0",texture1);
    //ps->setMatrix("WVP",wvp);


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

    delete a;



    lMemoryLogEnd();

    cout<<"\n\n";
    return 0;
}





