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
// LD3D9Device::checkErrors() add sleep function
// Screen Resolution change make more optimize
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
    o.rgba=tex2D(t0,_in.uv.xy).rgba;
    return o;
}



)";

const char* myShader2=
R"(
uniform extern float4x4 VP;

uniform extern sampler2D t0;

struct VSInput
{
    float3 pos:POSITION0;
    float2 uv:TEXCOORD0;

    float4 r1:TEXCOORD1;
    float4 r2:TEXCOORD2;
    float4 r3:TEXCOORD3;
    float4 r4:TEXCOORD4;
};

struct VSOut
{
    float4 pos:POSITION0;
    float2 uv:TEXCOORD0;
};

float4x4 fromv4tom4(float4 a,float4 b,float4 c,float4 d)
{
    return float4x4(a.x,a.y,a.z,a.w,
                    b.x,b.y,b.z,b.w,
                    c.x,c.y,c.z,c.w,
                    d.x,d.y,d.z,d.w
                    );
}

VSOut mainVS(VSInput _in)
{
    VSOut o;
    o.pos.xyz=_in.pos;
    o.pos.w=1.0f;
    float4x4 WVP = mul(fromv4tom4(_in.r1,_in.r2,_in.r3,_in.r4),VP);
    //o.pos= mul(o.pos,VP);
    o.pos=mul(o.pos,WVP);
    //o.pos+=_in.r4;
    o.uv=_in.uv;
    return o;
}


float4 mainPS(VSOut _in):COLOR0
{
    float4 o=float4(0.0f,0.0f,0.0f,1.0f);
    o.rgb=tex2D(t0,_in.uv.xy).rgb;
    return o;
}

)";

////////////////////////////////////////////////////////////////////////////////////////////////////


struct MyVertex2
{
    LVector4 r1,r2,r3,r4;
    static LGFXVertexDeclaration* decl;
};
LGFXVertexDeclaration* MyVertex2::decl=nullptr;
LVector<LVertexElement> _myVertex2Decl={
    {0,LVertexElementType_Float3,LVertexElementUsage_Position,0},
    {0,LVertexElementType_Float2,LVertexElementUsage_TextureCoordinate,0},

    {1,LVertexElementType_Float4,LVertexElementUsage_TextureCoordinate,1},
    {1,LVertexElementType_Float4,LVertexElementUsage_TextureCoordinate,2},
    {1,LVertexElementType_Float4,LVertexElementUsage_TextureCoordinate,3},
    {1,LVertexElementType_Float4,LVertexElementUsage_TextureCoordinate,4},
};


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




int main()
{
    lMemoryLogStart();

    LImage image01 = LImage::loadFromPngFile("image3.png");
    LImage image02 = LImage::loadFromPngFile("image.png");


    LGFXDevice* dev = LGFXDevice::create(0,0,800,600);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXVertexDeclaration* myVertex1Decl = dev->createVertexDeclaration(_myVertex1Decl);
    LGFXVertexDeclaration* myVertex2Decl = dev->createVertexDeclaration(_myVertex2Decl);


    LGFXVertexBuffer* vbplane = dev->createVertexBuffer();
    vbplane->updateBuffer((char*)vplane,myVertex1Decl->getElementsSize(),sizeof(vplane)/sizeof(vplane[0]));

    LGFXVertexBuffer* vbbox = dev->createVertexBuffer();
    vbbox->updateBuffer((char*)vbox,myVertex1Decl->getElementsSize(),sizeof(vbox)/sizeof(vbox[0]));

    LVector<LMatrix> _vboxinstance;
    for(int i=-50;i<=50;i+=3)
        for(int j=-50;j<=50;j+=3)
        {
            _vboxinstance.pushBack(LMatrix());
            _vboxinstance[_vboxinstance.getSize()-1]=LMatrix::createTranslationMatrix(LVector3(i,1,j));
        }
    LGFXVertexBuffer* vbboxinstance=dev->createVertexBuffer();
    vbboxinstance->updateBuffer((char*)_vboxinstance.getData(),sizeof(float)*4*4,_vboxinstance.getSize());
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXIndexBuffer* ibplane = dev->createIndexBuffer();
    ibplane->updateBuffer(iplane);

    LGFXIndexBuffer* ibbox = dev->createIndexBuffer();
    ibbox->updateBuffer(ibox);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXTexture* texture01 = dev->createTexture(image01.getWidth(),image01.getHeight(),image01.getFormat());
    texture01->updateTexture(0,image01);


    LGFXTexture* texture02 = dev->createTexture(image02.getWidth(),image02.getHeight(),image02.getFormat());
    texture02->updateTexture(0,image02.getResized(image02.getWidth(),image02.getHeight()));
    texture02->setAddress(LGFXTexture::TextureAddress_clamp);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXShader* shadervs01=dev->createVertexShader();
    shadervs01->compile(myShader,"mainVS");

    LGFXShader* shadervs02=dev->createVertexShader();
    shadervs02->compile(myShader2,"mainVS");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LGFXShader* shaderps01=dev->createPixelShader();
    shaderps01->compile(myShader,"mainPS");

    LGFXShader* shaderps02=dev->createPixelShader();
    shaderps02->compile(myShader2,"mainPS");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    LMatrix world,view,viewprojection,WVP,projection;
    float camFOV=60.0f;

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
                camspeed=0.2f;
            else
                camspeed=0.1f;
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

        if(LInput::isKeyDown(LInput::KeyCode_F2))
            dev->getScreenShot().saveAsPngFile("screenshot.png");

        static bool _isr=false;
        if(LInput::isKeyDown(LInput::KeyCode_F1))
        {
            if(_isr)
            {
                dev->reset(0,1,800,600);
                _isr=false;
            }
            else
            {
                dev->reset(1,1,1360,768);
                _isr=true;
            }
        }

        camFOV += -LInput::getMouseWheelDelta()*3;
        camFOV = lClamp(camFOV,1.0f,179.0f);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        projection =LMatrix::createPerspectiveProjectionLH(camFOV,4.0f/3.0f,0.01f,10000.0f);
        view = LMatrix::createViewMatrixLH(camPos,camRot.getForward(),camRot.getUp());
        viewprojection = view*projection;

        ////////////////////////////////////////////////////////////////////////////////////////////////////



        dev->clear(50,50,80);
        dev->beginScene();


        // Plane
        dev->resetParameters();
        {
            dev->setCullMode(LGFXCullMode_None);
            world=LMatrix::createScaleMatrix({6,6,6});
            WVP=world*viewprojection;
            shaderps01->setTexture("t0",texture01);
            shadervs01->setMatrix("WVP",WVP);
            dev->setVertexDeclaration(myVertex1Decl);
            dev->setVertexBuffer(0,vbplane);
            dev->setIndexBuffer(ibplane);
            dev->setPixelShader(shaderps01);
            dev->setVertexShader(shadervs01);
            dev->draw();
        }

        // Box
        dev->resetParameters();
        {
            world=boxRot.toRotationMatrix()*boxPos.toTranslationMatrix();
            WVP=world*viewprojection;
            shaderps01->setTexture("t0",texture02);
            shadervs01->setMatrix("WVP",WVP);
            dev->setVertexDeclaration(myVertex1Decl);
            dev->setVertexBuffer(0,vbbox);
            dev->setIndexBuffer(ibbox);
            dev->setPixelShader(shaderps01);
            dev->setVertexShader(shadervs01);
            dev->setAlphaBlending(true);

            dev->draw();
        }

//        dev->resetParameters();
//        {
//            shaderps02->setTexture("t0",texture02);
//            shadervs02->setMatrix("VP",viewprojection);
//            dev->setVertexDeclaration(myVertex2Decl);
//            dev->setVertexBuffer(0,vbbox);
//            dev->setVertexBuffer(1,vbboxinstance);
//            dev->setVertexBufferFrequency(0,_vboxinstance.getSize());
//            dev->setVertexBufferFrequency(1,0);
//            dev->setIndexBuffer(ibbox);
//            dev->setPixelShader(shaderps02);
//            dev->setVertexShader(shadervs02);

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


////////////////////////////////////////////////////////////////////////////////////////////////////


