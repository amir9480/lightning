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
//
///////////////////////////////////////
//
// add vector/list append
//

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
    ib->updateBuffer({2,1,3,0,1,2});

    LMatrix wvp;

    LGFXShader* vs=a->createVertexShader();
    vs->compile(myShader,"mainVS");
    vs->setMatrix("WVP",wvp);


    LGFXTexture* texture1=a->createTexture(512,512,1,te.getFormat());
    if(texture1!=nullptr)
    {
        texture1->updateTexture(0,te);
    }

    LGFXShader* ps=a->createPixelShader();
    ps->compile(myShader,"mainPS");
    ps->setVector("testvalue",LVector3(0.0f,0.0f,0.0f));
    if(texture1!=nullptr)
        ps->setTexture("t0",texture1);

    a->setVertexDeclaration(MyVertex::Decl);
    a->setVertexBuffer(0,vb);
    a->setIndexBuffer(ib);
    a->setVertexShader(vs);
    a->setPixelShader(ps);

    LVector3 camPos(0,0,-1);
    LQuaternion camRot;
    float m=1.0f;

    while (a->processOSMessage())
    {
        if(LInput::isKeyDown(LInput::KeyCode_Escape))
            break;
        if(LInput::isKeyPressed(LInput::KeyCode_LeftShift))
            m=0.1f;
        else
            m=0.05f;

        if(LInput::isKeyPressed(LInput::KeyCode_W))
            camPos+=camRot.getForward()*m;
        else if(LInput::isKeyPressed(LInput::KeyCode_S))
            camPos-=camRot.getForward()*m;
        if(LInput::isKeyPressed(LInput::KeyCode_A))
            camPos-=camRot.getRight()*m;
        else if(LInput::isKeyPressed(LInput::KeyCode_D))
            camPos+=camRot.getRight()*m;
        if(LInput::isKeyPressed(LInput::KeyCode_E))
            camPos+=camRot.getUp()*m;
        else if(LInput::isKeyPressed(LInput::KeyCode_Q))
            camPos-=camRot.getUp()*m;
        if(LInput::isMousePressed(LInput::MouseCode_left))
        {
            camRot*=LQuaternion(camRot.getRight(),-LInput::getMouseDeltaPos().y/4);
            camRot*=LQuaternion(LVector3::up,-LInput::getMouseDeltaPos().x/4);
        }

        wvp=LMatrix::createViewMatrixLH(camPos,camRot.getForward(),camRot.getUp())*LMatrix::createPerspectiveProjectionLH(50.0f);
        vs->setMatrix("WVP",wvp);


        a->beginScene();
        a->clear(20,20,20);
        a->draw();
        a->endScene();
        a->render();
        LInput::resetInputs();
    }

    delete a;


    lMemoryLogEnd();

    cout<<"\n\n";
    return 0;
}





