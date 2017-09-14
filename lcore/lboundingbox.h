#ifndef LBOUNDINGBOX_H
#define LBOUNDINGBOX_H
#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

// forward declartion
class LPlane;
class LBoundingSphere;


//! Axisally Aligned Bounding Box
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
    //! LBoundingBox  Default constructor min= - Infinity and max= infinity other corners are 0
    linline                 LBoundingBox();

    //! \ref set(const LVector3& _min,const LVector3& _max)
    linline                 LBoundingBox(const LVector3& _min, const LVector3& _max);

    // Copy Constructor
    linline                 LBoundingBox(const LBoundingBox& _other);

    //! Add an Internal Point in this Bounding Box . Note that point must not be translated
    linline void            add(const LVector3& _p);

    //! Check Bounding box is right or not  (checks mMax>=mMin) if was right returns true.
    linline bool            check()const;

    //! If BoundingBox parameters was not right will fix that
    linline void            fix();

    //! Get center point of bounding box
    linline LVector3        getCenter()const;

    //! Get one of corners
    linline const LVector3  getCorner(LCorner _t)const;

    //! Get all corners as pointer. do not try release what returns
    linline const LVector3* getCorners()const;

    //! Get transformed by center Maximum point
    linline const LVector3  getMax()const;

    //! Get merged copy of this with another bounding box
    linline LBoundingBox    getMerged(const LBoundingBox& _other)const;

    //! Get transformed by center Minimum point
    linline const LVector3  getMin()const;

    //! Get Center position of bounding box
    linline const LVector3& getPos()const;

    //! Get Plain no transformed Minimum point
    linline const LVector3& getPlainMin()const;

    //!Get Plain no transformed Minimum point
    linline const LVector3& getPlainMax()const;

    //! Get size vector . size vector is a vector from min to max
    linline LVector3        getSizeVector()const;

    //! Get transformed copy of this
    linline LBoundingBox    getTransformed(const LMatrix& _m)const;

    //! Get volume of box
    linline f32             getVolume()const;

    //! Check is point inside box or not
    linline bool            isContain(const LVector3& _p)const;

    //! Check is all corner of another box is inside this box or not
    linline bool            isContain(const LBoundingBox& _bb)const;

    //! BoundingBox-Plane Intersection Check
    bool                    isIntersect(const LPlane& _other)const;

    //! BoundingBox-BoundingSphere Intersection Check
    bool                    isIntersect(const LBoundingSphere& _other)const;

    //! BoundingBox-BoundingBox Intersection Check
    linline bool            isIntersect(const LBoundingBox& _other)const;

    //! Merge other box with this box
    linline void            merge(const LBoundingBox& _other);

    //! Set function from min and max
    linline void            set(const LVector3& _min, const LVector3& _max);

    //!Set plain Maximum function
    linline void            setMax(const LVector3& _p);

    //! Set plain minimum function
    linline void            setMin(const LVector3& _p);

    //! Set ceneter function
    linline void            setPos(const LVector3& _p);

    //! Transform this box using transformatrion matrix
    linline void            transform(const LMatrix& _m);

    // Copy
    linline LBoundingBox&   operator=(const LBoundingBox& _other);

    // Compare
    linline bool            operator==(const LBoundingBox& _other)const;
    linline bool            operator!=(const LBoundingBox& _other)const;
protected:
    LVector3    mPos;
    LVector3    mMin;
    LVector3    mMax;
};


LBoundingBox::LBoundingBox()
{
    mMin=-lInfinity;
    mMax=lInfinity;
}

LBoundingBox::LBoundingBox(const LVector3 &_min, const LVector3 &_max)
{
    set(_min,_max);
}

LBoundingBox::LBoundingBox(const LBoundingBox &_other)
{
    (*this)=_other;
}

bool LBoundingBox::isContain(const LVector3 &_p) const
{
    return (
                _p.x>=mMin.x+mPos.x&&
                _p.y>=mMin.y+mPos.y&&
                _p.z>=mMin.z+mPos.z&&
                _p.x<=mMax.x+mPos.x&&
                _p.y<=mMax.y+mPos.y&&
                _p.z<=mMax.z+mPos.z
                );
}

bool LBoundingBox::isContain(const LBoundingBox &_bb) const
{
    const LVector3* corners=_bb.getCorners();
    return (
                isContain(corners[0])&&
                isContain(corners[1])&&
                isContain(corners[2])&&
                isContain(corners[3])&&
                isContain(corners[4])&&
                isContain(corners[5])&&
                isContain(corners[6])&&
                isContain(corners[7])
            );
}

bool LBoundingBox::isIntersect(const LBoundingBox &_other) const
{
    // Adapted from http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
    LVector3 tmax=getMax();
    LVector3 tmin=getMin();
    LVector3 omin=_other.getMin();
    LVector3 omax=_other.getMax();

    if(tmax.x<omin.x)
        return false;
    if(tmin.x>omax.x)
        return false;
    if(tmax.y<omin.y)
        return false;
    if(tmin.y>omax.y)
        return false;
    if(tmax.z<omin.z)
        return false;
    if(tmin.z>omax.z)
        return false;
    return true;
}

void LBoundingBox::merge(const LBoundingBox &_other)
{
    add(_other.getMax());
    add(_other.getMin());
}

void LBoundingBox::add(const LVector3 &_p)
{
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
    }
}

LVector3 LBoundingBox::getCenter() const
{
    return (getMin()+getMax())*0.5f;
}

const LVector3 LBoundingBox::getCorner(LBoundingBox::LCorner _t) const
{
    switch (_t)
    {
    case LCorner::left_bottom_back:
        return mPos+LVector3(mMin.x,mMin.y,mMin.z);
    case LCorner::left_bottom_front:
        return mPos+LVector3(mMin.x,mMin.y,mMax.z);
    case LCorner::left_top_back:
        return mPos+LVector3(mMin.x,mMax.y,mMin.z);
    case LCorner::left_top_front:
        return mPos+LVector3(mMin.x,mMax.y,mMax.z);
    case LCorner::right_bottom_back:
        return mPos+LVector3(mMax.x,mMin.y,mMin.z);
    case LCorner::right_bottom_front:
        return mPos+LVector3(mMax.x,mMin.y,mMax.z);
    case LCorner::right_top_back:
        return mPos+LVector3(mMax.x,mMax.y,mMin.z);
    case LCorner::right_top_front:
        return mPos+LVector3(mMax.x,mMax.y,mMax.z);
    default:
        break;
    }
    lError(1,"const LVector3 &LBoundingBox::getCorner(LBoundingBox::LCorner _t) const:There is no corner like this",LVector3());
}

const LVector3 *LBoundingBox::getCorners() const
{
    static LVector3 corners[8];
    for(u32 i=0;i<8;i++)
        corners[i]=getCorner((LCorner)i);
    return corners;
}

const LVector3 LBoundingBox::getMax() const
{
    return mMax+mPos;
}

LBoundingBox LBoundingBox::getMerged(const LBoundingBox &_other)const
{
    LBoundingBox o=(*this);
    o.merge(_other);
    return o;
}

const LVector3 LBoundingBox::getMin() const
{
    return mMin+mPos;
}

const LVector3 &LBoundingBox::getPos() const
{
    return mPos;
}

const LVector3 &LBoundingBox::getPlainMin() const
{
    return mMin;
}

const LVector3 &LBoundingBox::getPlainMax() const
{
    return mMax;
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
}

void LBoundingBox::setMin(const LVector3 &_p)
{
    mMin=_p;
}

void LBoundingBox::setPos(const LVector3 &_p)
{
    mPos=_p;
}

void LBoundingBox::setMax(const LVector3 &_p)
{
    mMax=_p;
}

void LBoundingBox::transform(const LMatrix& _m)
{
    LVector3 vm=mMin;
    LVector3 vM=mMax;
    LMatrix msr=_m.getRotationScaleOnly();
    LMatrix mt=_m.getTranslationOnly();

    LVector3 t;
    mMin=mMax=0.0f;
    t=vm;       add(t*msr);// min min min
    t.x=vM.x;   add(t*msr);// Max min min
    t.y=vM.y;   add(t*msr);// Max Max min
    t.z=vM.z;   add(t*msr);// Max Max Max
    t.x=vm.x;   add(t*msr);// min Max Max
    t.y=vm.y;   add(t*msr);// min min Max
    t.x=vM.x;   add(t*msr);// Max min Max
    t=vm;
    t.y=vM.y;   add(t*msr);// min Max min

    mPos=mPos*mt;

    fix();
}

LBoundingBox &LBoundingBox::operator=(const LBoundingBox &_other)
{
    mMin=_other.mMin;
    mMax=_other.mMax;
    mPos=_other.mPos;
    return (*this);
}

bool LBoundingBox::operator==(const LBoundingBox &_other) const
{
    return (getMin()==_other.getMin()&&getMax()==_other.getMax());
}

bool LBoundingBox::operator!=(const LBoundingBox &_other) const
{
    return !(*this==_other);
}


LNAMESPACE_END
#endif // LBOUNDINGBOX_H
