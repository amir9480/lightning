#include "lquaternion.h"
LNAMESPACE_BEGIN

#include "lvector3.h"

const LQuaternion LQuaternion::identity = LQuaternion(0.0f,0.0f,0.0f,1.0f);
const LQuaternion LQuaternion::zero     = LQuaternion(0.0f,0.0f,0.0f,0.0f);

LQuaternion::LQuaternion(const LVector3 &_right, const LVector3 &_up, const LVector3 &_forward)
{
    set(_right,_up,_forward);
}

LQuaternion::LQuaternion(const LVector3 &_a, const f32 &_angle)
{
    set(_a,_angle);
}

LQuaternion::LQuaternion(const LVector3 &_e)
{
    set(_e.x,_e.y,_e.z);
}

LQuaternion::LQuaternion(const LVector3 &_a, const LVector3 &_b)
{
    set(_a,_b);
}

LVector3 LQuaternion::getForward() const
{
    return LVector3(lRound(2.0f*(x*z-w*y),6),
                    lRound(2.0f*(y*z+w*x),6),
                    lRound(1.0f-2.0f*(x*x+y*y),6)
                    );
}

LVector3 LQuaternion::getRight() const
{
    return LVector3(lRound(1.0f-2.0f*(y*y+z*z),6),
                    lRound(2.0f*(x*y-w*z),6),
                    lRound(2.0f*(x*z+w*y),6)
                    );
}

LVector3 LQuaternion::getRotated(const LVector3& _in) const
{
    LVector3 out;
    LQuaternion tq(_in.x,_in.y,_in.z,0.0f);
    tq= this->getConjugated() * tq * (*this);
    out.set(lRound(tq.x,4),lRound(tq.y,4),lRound(tq.z,4));
    return out;
}

LVector3 LQuaternion::getUp() const
{
    return LVector3(lRound(2.0f*(x*y+w*z),6),
                    lRound(1.0f-2.0f*(x*x+z*z),6),
                    lRound(2.0f*(y*z-w*x),6)
                    );
}

void LQuaternion::set(const LVector3 &_right, const LVector3 &_up, const LVector3 &_forward)
{
    set(LMatrix( _right.x   ,_right.y   ,_right.z   ,0.0f,
                 _up.x      ,_up.y      ,_up.z      ,0.0f,
                 _forward.x ,_forward.y ,_forward.z ,0.0f,
                 0.0f       ,0.0f       ,0.0f       ,1.0f
                 ));
}

void LQuaternion::set(const LVector3 &_a, const f32 &_angle)
{
    f32 sa=lSin(_angle/2.0f);
    w=lCos(_angle/2.0f);
    x=_a.x*sa;
    y=_a.y*sa;
    z=_a.z*sa;
}

void LQuaternion::set(const LVector3 &_a, const LVector3 &_b)
{
    LVector3 c=_a.getCrossProduct(_b).getNormalized();
    x=c.x;
    y=c.y;
    z=c.z;
    f32 al=_a.getLength();
    f32 bl=_b.getLength();
    w=lSqrt(al*al+bl*bl)+_a.getDotProduct(_b);
}

void LQuaternion::set(const LVector3 &_e)
{
    set(_e.x,_e.y,_e.z);
}

void LQuaternion::toAxes(LVector3 &_right, LVector3 &_up, LVector3 &_forward) const
{
    _right=getRight();
    _up=getUp();
    _forward=getForward();
}

void LQuaternion::toAxisAngle(LVector3 &_axis_, f32 &_angle_) const
{
    LQuaternion t=(*this);
    t.normalize();
    _angle_=2.0f*lACos(t.w);
    _axis_.x=t.x;
    _axis_.y=t.y;
    _axis_.z=t.z;
    if(lSqrt(1.0f-t.w*t.w)>0.001f)
       _axis_/=lSqrt(1.0f-t.w*t.w);
}

LVector3 LQuaternion::toEulerAngel() const
{
    LVector3 out;
    float sp=-2.0f*(y*z-w*x);
    if(lAbs(sp)>0.9999f)
    {
        out.x=sp*90.0f;
        out.y=lATan2(-x*z-w*y,0.5f-y*y-z*z);
        out.z=0.0f;
    }
    else
    {
        out.x=lASin(sp);
        out.y=lATan2(x*z+w*y,0.5f-x*x-y*y);
        out.z=lATan2(x*y+w*z,0.5f-x*x-z*z);
    }
    /*out.x=lASin(-2.0f*(x*z-w*y));
    out.y=lATan2(2.0f*(y*z+w*x),w*w - x*x - y*y + z*z);
    out.z=lATan2(2.0f*(x*y+w*z),w*w - x*x - y*y + z*z);*/
    return out;
}

LNAMESPACE_END
