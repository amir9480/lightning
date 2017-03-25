#ifndef LBOUNDINGBOX_H
#define LBOUNDINGBOX_H
#include "ldefines.h"
#include "lmathutility.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

//! This class is for Axisally Aligned Bounding Box
class LAPI LBoundingBox
{
public:
    enum LCorner
    {
        left_bottom_back=0,
        left_bottom_front,
        left_top_back,
        left_top_front,
        right_bottom_back,
        right_bottom_front,
        right_top_back,
        right_top_front
    };

public:
    //! Default Constructor
    linline                 LBoundingBox();

    //! Bounding Box from min and max values
    linline                 LBoundingBox(const LVector3& _min,const LVector3& _max);

    //! Copy Constructor
    linline                 LBoundingBox(const LBoundingBox& _other);

    //! Add an Internal Point in this Bounding Box
    linline void            add(const LVector3& _p,bool _update=true);

    //! Check Bounding box is right or not  (checks mMax>=mMin) if was right returns true. other wise returns false
    linline bool            check()const;

    //! fix if bounding box is not right
    linline void            fix();

    //! Get Center Point
    linline LVector3        getCenter()const;

    //! Get one corner
    linline const LVector3& getCorner(LCorner _t)const;

    //! Get All Corners at Pointer
    linline const LVector3* getCorners()const;

    //! Get Maximum point
    linline const LVector3& getMax()const;

    //! Get Merged copy of this with another
    linline LBoundingBox    getMerged(const LBoundingBox& _other)const;

    //! Get Minimum point
    linline const LVector3& getMin()const;

    //! Get size vector . a vector from min to max
    linline LVector3        getSizeVector()const;

    //! Get Transformed Copy of this
    linline LBoundingBox    getTransformed(const LMatrix& _m)const;

    //! Get Volume of this box
    linline f32             getVolume()const;

    //! Check is point inside box or not. if was returns true. otherwise returns false
    linline bool            isContain(const LVector3& _p)const;

    //! Check is all corner of another box is inside or not. if was returns true otherwise returns false;
    linline bool            isContain(const LBoundingBox& _bb)const;

    //! Merge Another box with this
    linline void            merge(const LBoundingBox& _other);

    //! Set Function from min and max
    linline void            set(const LVector3& _min,const LVector3& _max);

    //! Set Minimum point
    linline void            setMin(const LVector3& _p);

    //! Set Maximum point
    linline void            setMax(const LVector3& _p);

    //! Transform this Box using Transformatrion Matrix
    linline void            transform(const LMatrix& _m);

    //! Update Bounding Box values
    linline void            update();


    //! Copy
    linline LBoundingBox&   operator=(const LBoundingBox& _other);

    //! Compare
    linline bool            operator==(const LBoundingBox& _other)const;
    linline bool            operator!=(const LBoundingBox& _other)const;
protected:
    LVector3    mCorners[8];
    LVector3&   mMin;
    LVector3&   mMax;
};

LBoundingBox::LBoundingBox():
    mMin(mCorners[LCorner::left_bottom_back]),
    mMax(mCorners[LCorner::right_top_front])
{
    mCorners[1]=mCorners[2]=mCorners[3]=mCorners[4]=mCorners[5]=mCorners[6]=0.0f;
    mMin=-lInfinity;
    mMax=lInfinity;
}

LBoundingBox::LBoundingBox(const LVector3 &_min, const LVector3 &_max):
    mMin(mCorners[LCorner::left_bottom_back]),
    mMax(mCorners[LCorner::right_top_front])
{
    set(_min,_max);
}

LBoundingBox::LBoundingBox(const LBoundingBox &_other):
    mMin(mCorners[LCorner::left_bottom_back]),
    mMax(mCorners[LCorner::right_top_front])
{
    (*this)=_other;
}

bool LBoundingBox::isContain(const LVector3 &_p) const
{
    return (
                _p.x>=mMin.x&&
                _p.y>=mMin.y&&
                _p.z>=mMin.z&&
                _p.x<=mMax.x&&
                _p.y<=mMax.y&&
                _p.z<=mMax.z
                );
}

bool LBoundingBox::isContain(const LBoundingBox &_bb) const
{
    return (
                isContain(_bb.mCorners[0])&&
                isContain(_bb.mCorners[1])&&
                isContain(_bb.mCorners[2])&&
                isContain(_bb.mCorners[3])&&
                isContain(_bb.mCorners[4])&&
                isContain(_bb.mCorners[5])&&
                isContain(_bb.mCorners[6])&&
                isContain(_bb.mCorners[7])
            );
}

void LBoundingBox::merge(const LBoundingBox &_other)
{
    add(_other.mMax);
    add(_other.mMin);
}

void LBoundingBox::add(const LVector3 &_p,bool _update)
{
    LVector3 cM=mMax;
    LVector3 cm=mMin;

    if(_p.x<mMin.x)
        mMin.x=_p.x;
    if(_p.y<mMin.y)
        mMin.y=_p.y;
    if(_p.z<mMin.z)
        mMin.z=_p.z;

    if(_p.x>mMax.x)
        mMax.x=_p.x;
    if(_p.y>mMax.y)
        mMax.y=_p.y;
    if(_p.z>mMax.z)
        mMax.z=_p.z;
    //! if is not neccesary dont update
    if(_update&&(cM!=mMax||cm!=mMin))
        update();
}

bool LBoundingBox::check() const
{
    LVector3 s=getSizeVector();
    return (s.x>=0.0f&&s.y>=0.0f&&s.z>=0.0f);
}

void LBoundingBox::fix()
{
    // if bounding box is not right
    if(!check())
    {
        LVector3 _min=mMin;
        LVector3 _max=mMax;
        add(_min);
        add(_max);
        update();
    }
}

LVector3 LBoundingBox::getCenter() const
{
    return (mMin+mMax)/2.0f;
}

const LVector3 &LBoundingBox::getCorner(LBoundingBox::LCorner _t) const
{
    return mCorners[_t];
}

const LVector3 *LBoundingBox::getCorners() const
{
    return mCorners;
}

const LVector3 &LBoundingBox::getMax() const
{
    return mMax;
}

LBoundingBox LBoundingBox::getMerged(const LBoundingBox &_other)const
{
    LBoundingBox o=(*this);
    o.merge(_other);
    return o;
}

const LVector3 &LBoundingBox::getMin() const
{
    return mMin;
}

LVector3 LBoundingBox::getSizeVector() const
{
    return mMax-mMin;
}

LBoundingBox LBoundingBox::getTransformed(const LMatrix &_m) const
{
    LBoundingBox o=(*this);
    o.transform(_m);
    return o;
}

f32 LBoundingBox::getVolume() const
{
    LVector3 s=getSizeVector();
    return s.x*s.y*s.z;
}

void LBoundingBox::set(const LVector3 &_min, const LVector3 &_max)
{
    mMin=_min;
    mMax=_max;
    update();
}

void LBoundingBox::setMin(const LVector3 &_p)
{
    mMin=_p;
    update();
}

void LBoundingBox::setMax(const LVector3 &_p)
{
    mMax=_p;
    update();
}

void LBoundingBox::transform(const LMatrix& _m)
{
    LVector3 currentPos=getCenter();
    mMin-=currentPos;
    mMax-=currentPos;
    LVector3 vm=mMin;
    LVector3 vM=mMax;
    LVector3 t;
    mMin=mMax=0.0f;
    t=vm;       add(t*_m);// min min min
    t.x=vM.x;   add(t*_m);// Max min min
    t.y=vM.y;   add(t*_m);// Max Max min
    t.z=vM.z;   add(t*_m);// Max Max Max
    t.x=vm.x;   add(t*_m);// min Max Max
    t.y=vm.y;   add(t*_m);// min min Max
    t.x=vM.x;   add(t*_m);// Max min Max
    t=vm;
    t.y=vM.y;   add(t*_m);// min Max min

    fix();
    update();
    mMin+=currentPos;
    mMax+=currentPos;
}

void LBoundingBox::update()
{
    if(mMin==-lInfinity&&mMax==lInfinity)
    {
        mCorners[1]=mCorners[2]=mCorners[3]=mCorners[4]=mCorners[5]=mCorners[6]=0.0f;
        return;
    }

    mCorners[LCorner::left_bottom_front]    =LVector3(mMin.x,mMin.y,mMax.z);
    mCorners[LCorner::left_top_back]        =LVector3(mMin.x,mMax.y,mMin.z);
    mCorners[LCorner::left_top_front]       =LVector3(mMin.x,mMax.y,mMax.z);
    mCorners[LCorner::right_bottom_back]    =LVector3(mMax.x,mMin.y,mMin.z);
    mCorners[LCorner::right_bottom_front]   =LVector3(mMax.x,mMin.y,mMax.z);
    mCorners[LCorner::right_top_back]       =LVector3(mMax.x,mMax.y,mMin.z);
}

LBoundingBox &LBoundingBox::operator=(const LBoundingBox &_other)
{
    mCorners[0]=_other.mCorners[0];
    mCorners[1]=_other.mCorners[1];
    mCorners[2]=_other.mCorners[2];
    mCorners[3]=_other.mCorners[3];
    mCorners[4]=_other.mCorners[4];
    mCorners[5]=_other.mCorners[5];
    mCorners[6]=_other.mCorners[6];
    mCorners[7]=_other.mCorners[7];
    return (*this);
}

bool LBoundingBox::operator==(const LBoundingBox &_other) const
{
    return (mMin==_other.mMin&&mMax==_other.mMax);
}

bool LBoundingBox::operator!=(const LBoundingBox &_other) const
{
    return !(*this==_other);
}


LNAMESPACE_END
#endif // LBOUNDINGBOX_H
