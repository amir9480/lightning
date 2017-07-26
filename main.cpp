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


const char* myShader=
R"(
uniform extern float4x4 WVP;

uniform extern sampler2D t0;

struct VSInput
{
    float3 pos:POSITION0;
    float2 uv:TEXCOORD0;
};

struct VSOut
{
    float4 pos:POSITION0;
    float2 uv:TEXCOORD0;
};


VSOut mainVS(VSInput _in)
{
    VSOut o;
    o.pos.xyz=_in.pos;
    o.pos.w=1.0f;
    o.pos=mul(o.pos,WVP);
    o.uv=_in.uv;
    return o;
}


float4 mainPS(VSOut _in):COLOR0
{
    float4 o=float4(0.0f,0.0f,0.0f,1.0f);
    o.rgb=tex2D(t0,_in.uv.xy).rgb;
    //if(_in.uv.x>=0.25f&&_in.uv.x<=0.75f&&_in.uv.y>=0.25f&&_in.uv.y<=0.75f)
    //    o.a=0.0f;
    //else
    //    o.a=1.0f;
    return o;
}



)";

////////////////////////////////////////////////////////////////////////////////////////////////////


struct MyVertex1
{
    LVector3 pos;
    LVector2 uv;
    static LGFXVertexDeclaration* decl;
};
LGFXVertexDeclaration* MyVertex1::decl=nullptr;
LVector<LVertexElement> _myVertex1Decl={
    {0,LVertexElementType_Float3,LVertexElementUsage_Position,0},
    {0,LVertexElementType_Float2,LVertexElementUsage_TextureCoordinate,0},
};


MyVertex1 vplane[]=
{
    {LVector3(-1,0,1),LVector2(0,0)},
    {LVector3(1,0,1),LVector2(6,0)},
    {LVector3(-1,0,-1),LVector2(0,6)},
    {LVector3(1,0,-1),LVector2(6,6)},
};
LVector<u32> iplane={0,1,2 , 2,1,3};

MyVertex1 vbox[]=
{
    {LVector3(-1,1,1),LVector2(1,0)},
    {LVector3(-1,-1,1),LVector2(1,1)},
    {LVector3(1,1,1),LVector2(0,0)},
    {LVector3(1,-1,1),LVector2(0,1)},

    {LVector3(-1,1,-1),LVector2(0,0)},
    {LVector3(-1,-1,-1),LVector2(0,1)},
    {LVector3(1,1,-1),LVector2(1,0)},
    {LVector3(1,-1,-1),LVector2(1,1)},


    {LVector3(-1,1,-1),LVector2(1,0)},
    {LVector3(-1,-1,-1),LVector2(1,1)},
    {LVector3(-1,1,1),LVector2(0,0)},
    {LVector3(-1,-1,1),LVector2(0,1)},

    {LVector3(1,1,-1),LVector2(0,0)},
    {LVector3(1,-1,-1),LVector2(0,1)},
    {LVector3(1,1,1),LVector2(1,0)},
    {LVector3(1,-1,1),LVector2(1,1)},


    {LVector3(-1,1,1),LVector2(0,0)},
    {LVector3(-1,1,-1),LVector2(0,1)},
    {LVector3(1,1,1),LVector2(1,0)},
    {LVector3(1,1,-1),LVector2(1,1)},

    {LVector3(-1,-1,1),LVector2(1,0)},
    {LVector3(-1,-1,-1),LVector2(1,1)},
    {LVector3(1,-1,1),LVector2(0,0)},
    {LVector3(1,-1,-1),LVector2(0,1)},
};
LVector<u32> ibox={
  0,1,2,2,1,3,
  4,6,5,5,6,7,
  8,9,10,10,9,11,
  12,14,13,13,14,15,
  17,16,18,17,18,19,
  20,21,22,22,21,23
};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum TypeA
{
    TypeA_1=1,
    TypeA_2=2,
    TypeA_3=3
};

enum TypeB
{
    TypeB_1=101,
    TypeB_2=102,
    TypeB_3=103
};


int main()
{
    lMemoryLogStart();

    LImage image01 = LImage::loadFromPngFile("image3.png");
    LImage image02 = LImage::loadFromPngFile("image.png");

    LGFXDevice* dev = LGFXDevice::create(0,1);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXVertexDeclaration* myVertex1Decl = dev->createVertexDeclaration(_myVertex1Decl);
    LGFXVertexBuffer* vbplane = dev->createVertexBuffer();
    vbplane->updateBuffer((char*)vplane,myVertex1Decl->getElementsSize(),sizeof(vplane)/sizeof(vplane[0]));

    LGFXVertexBuffer* vbbox = dev->createVertexBuffer();
    vbbox->updateBuffer((char*)vbox,myVertex1Decl->getElementsSize(),sizeof(vbox)/sizeof(vbox[0]));
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXIndexBuffer* ibplane = dev->createIndexBuffer();
    ibplane->updateBuffer(iplane);

    LGFXIndexBuffer* ibbox = dev->createIndexBuffer();
    ibbox->updateBuffer(ibox);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXTexture* texture01 = dev->createTexture(image01.getWidth(),image01.getHeight(),5,image01.getFormat());
    texture01->updateTexture(0,image01);
    texture01->updateTexture(1,image01.getResized(image01.getWidth()/2,image01.getHeight()/2));
    texture01->updateTexture(2,image01.getResized(image01.getWidth()/4,image01.getHeight()/4));
    texture01->updateTexture(3,image01.getResized(image01.getWidth()/8,image01.getHeight()/8));
    texture01->updateTexture(4,image01.getResized(image01.getWidth()/16,image01.getHeight()/16));
    texture01->setMipMapBias(-1.5f);


    LGFXTexture* texture02 = dev->createTexture(image02.getWidth(),image02.getHeight(),5,image02.getFormat());
    texture02->updateTexture(0,image02);
    texture02->updateTexture(1,image02.getResized(image02.getWidth()/2,image02.getHeight()/2));
    texture02->updateTexture(2,image02.getResized(image02.getWidth()/4,image02.getHeight()/4));
    texture02->updateTexture(3,image02.getResized(image02.getWidth()/8,image02.getHeight()/8));
    texture02->updateTexture(4,image02.getResized(image02.getWidth()/16,image02.getHeight()/16));

    LGFXTexture* myrendertarget01 = dev->createRenderTarget(800,600,LImage::Format_R8G8B8);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXShader* shadervs01=dev->createVertexShader();
    shadervs01->compile(myShader,"mainVS");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXShader* shaderps01=dev->createPixelShader();
    shaderps01->compile(myShader,"mainPS");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LMatrix world,view,viewprojection,WVP,projection=LMatrix::createPerspectiveProjectionLH(60.0f,4.0f/3.0f,0.01f,1000.0f);

    LVector3 camPos=LVector3(0,0.8,-4.5);
    LQuaternion camRot=LQuaternion(LVector3::forward,0.0f);

    LVector3 boxPos=LVector3(0,1,0);
    LQuaternion boxRot;


    while(dev->processOSMessage())
    {
        float camspeed=0.1f;

        if(LInput::isKeyDown(LInput::KeyCode_Escape))
            break;

        if(LInput::isMousePressed(LInput::MouseCode_right))
        {
            if(LInput::isKeyPressed(LInput::KeyCode_W))
                boxPos+=LVector3::forward*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_S))
                boxPos-=LVector3::forward*camspeed;
            if(LInput::isKeyPressed(LInput::KeyCode_A))
                boxPos-=LVector3::right*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_D))
                boxPos+=LVector3::right*camspeed;
            if(LInput::isKeyPressed(LInput::KeyCode_Q))
                boxPos-=LVector3::up*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_E))
                boxPos+=LVector3::up*camspeed;
        }
        else if(LInput::isMousePressed(LInput::MouseCode_middle))
        {
            boxRot*=LQuaternion(LVector3::up,LInput::getMouseDelta().x*0.5f);
            boxRot*=LQuaternion(LVector3::right,-LInput::getMouseDelta().y*0.5f);
        }
        else
        {
            if(LInput::isKeyPressed(LInput::KeyCode_LeftShift))
                camspeed=0.1f;
            else
                camspeed=0.05f;
            if(LInput::isKeyPressed(LInput::KeyCode_W))
                camPos+=camRot.getForward()*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_S))
                camPos-=camRot.getForward()*camspeed;
            if(LInput::isKeyPressed(LInput::KeyCode_A))
                camPos-=camRot.getRight()*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_D))
                camPos+=camRot.getRight()*camspeed;
            if(LInput::isKeyPressed(LInput::KeyCode_Q))
                camPos-=camRot.getUp()*camspeed;
            else if(LInput::isKeyPressed(LInput::KeyCode_E))
                camPos+=camRot.getUp()*camspeed;
            if(LInput::isMousePressed(LInput::MouseCode_left))
            {
                camRot*=LQuaternion(LVector3::up,-LInput::getMouseDelta().x*0.5f);
                camRot*=LQuaternion(camRot.getRight(),-LInput::getMouseDelta().y*0.5f);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        view = LMatrix::createViewMatrixLH(camPos,camRot.getForward(),camRot.getUp());
        viewprojection = view*projection;

        ////////////////////////////////////////////////////////////////////////////////////////////////////


        // render target
        dev->resetParameters();
        dev->setRenderTarget(0,myrendertarget01);
        dev->clear(0,150,255);
        dev->beginScene();
        {
            dev->setCullMode(LGFXCullMode_None);
            world=LMatrix::createScaleMatrix({6,6,6});
            WVP=world*viewprojection;
            shaderps01->setTexture("t0",texture02);
            shadervs01->setMatrix("WVP",WVP);
            dev->setVertexDeclaration(myVertex1Decl);
            dev->setVertexBuffer(0,vbplane);
            dev->setIndexBuffer(ibplane);
            dev->setPixelShader(shaderps01);
            dev->setVertexShader(shadervs01);

            dev->draw();
        }
        dev->setRenderTarget(0,nullptr);
        // render target end
        dev->endScene();


        dev->clear(50,50,50);
        dev->beginScene();
        dev->drawQuad(myrendertarget01);
//        dev->resetParameters();
//        {
//            world=boxRot.toRotationMatrix()*boxPos.toTranslationMatrix();
//            WVP=world*viewprojection;
//            shaderps01->setTexture("t0",myrendertarget01);
//            shadervs01->setMatrix("WVP",WVP);
//            dev->setVertexDeclaration(myVertex1Decl);
//            dev->setVertexBuffer(0,vbbox);
//            dev->setIndexBuffer(ibbox);
//            dev->setPixelShader(shaderps01);
//            dev->setVertexShader(shadervs01);

//            dev->draw();
//        }
//        dev->resetParameters();
//        {
//            dev->setCullMode(LGFXCullMode_None);
//            world=LMatrix::createScaleMatrix({6,6,6});
//            WVP=world*viewprojection;
//            shaderps01->setTexture("t0",texture01);
//            shadervs01->setMatrix("WVP",WVP);
//            dev->setVertexDeclaration(myVertex1Decl);
//            dev->setVertexBuffer(0,vbplane);
//            dev->setIndexBuffer(ibplane);
//            dev->setPixelShader(shaderps01);
//            dev->setVertexShader(shadervs01);

//            dev->draw();
//        }

        dev->endScene();
        dev->render();
        LInput::resetInputs();
    }

    delete dev;

    lMemoryLogEnd();
    cout<<"\n\n";
    return 0;
}




