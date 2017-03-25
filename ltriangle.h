#ifndef LTRIANGLE_H
#define LTRIANGLE_H
#include "ldefines.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN
/*!
 * v1 v2 v3 are our vertices
 * a1 a2 a3 are v1 v2 v3 angles
 * e1 is a vector from v2 to v3
 * e2 is a vector from v3 to v1
 * e3 is a vector from v1 to v2
 * l1 l2 l3 are e1 e2 e3 lengths
 * mNormal is triangle normal computed counter clockwise
 */
class LAPI LTriangle
{
public:
    linline                 LTriangle();

    linline                 LTriangle(const LVector3& _v1,const LVector3& _v2,const LVector3& _v3);

    //! Get Triangle Area
    linline f32             getArea()const;

    //! Get Barycentric Coordinates
    linline bool            getBarycentricCoordinates(const LVector3& v,f32 out[3]);

    //! Get Circumcenter Circle
    linline LVector3        getCircumcenter()const;

    //! Get Radius of  Circumcenter
    linline f32             getCircumcenterRadius()const;

    //! Get Center of Gravity
    linline LVector3        getGravityCenter()const;

    //! Get Incenter
    linline LVector3        getIncenter()const;

    //! Get Radius of Incenter Circle
    linline f32             getIncenterRadius()const;

    //! Get Triangle Perimeter
    linline f32             getPerimeter()const;

    //! Get Transformed Copy of this
    linline LTriangle       getTransformed(const LMatrix& _m)const;

    //! Set Triangle Parameters
    linline void            set(const LVector3& _v1,const LVector3& _v2,const LVector3& _v3);

    //! Transform this Triangle using Transformatrion Matrix
    linline void            transform(const LMatrix& _m);

    //! Update Triangle Values Based On Only Vertices
    linline void            update();

    //! Copy Operator
    linline LTriangle&      operator=(const LTriangle& _other);

    //! Compare
    linline bool            operator==(const LTriangle& _other)const;
    linline bool            operator!=(const LTriangle& _other)const;

public:
    LVector3 v1,v2,v3;  // Vertices
    f32      a1,a2,a3;  // Angles of vertices
    LVector3 e1,e2,e3;  // Edges
    f32      l1,l2,l3;  // Edge Length
    LVector3 mNormal;   // Normal Vector of Triangle
};

LTriangle::LTriangle()
{
    a1=a2=a3=l1=l2=l3=0.0f;
}

LTriangle::LTriangle(const LVector3 &_v1, const LVector3 &_v2, const LVector3 &_v3)
{
    this->set(_v1,_v2,_v3);
}

f32 LTriangle::getArea() const
{
    f32 s=getPerimeter()/2.0f;
    return lSqrt(s*(s-l1)*(s-l2)*(s-l3));
}

bool LTriangle::getBarycentricCoordinates(const LVector3 &v, f32 out[3])
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    f32 u1,u2,u3,u4;
    f32 w1,w2,w3,w4;
    if(lAbs(mNormal.x)>=lAbs(mNormal.y)&&lAbs(mNormal.x)>=lAbs(mNormal.z))
    {
        u1=v1.y-v3.y;
        u2=v2.y-v3.y;
        u3=v.y-v1.y;
        u4=v.y-v3.y;

        w1=v1.z-v3.z;
        w2=v2.z-v3.z;
        w3=v.z-v1.z;
        w4=v.z-v3.z;
    }
    else if(lAbs(mNormal.y)>=lAbs(mNormal.z))
    {
        u1=v1.z-v3.z;
        u2=v2.z-v3.z;
        u3=v.z-v1.z;
        u4=v.z-v3.z;

        w1=v1.x-v3.x;
        w2=v2.x-v3.x;
        w3=v.x-v1.x;
        w4=v.x-v3.x;
    }
    else
    {

        u1=v1.x-v3.x;
        u2=v2.x-v3.x;
        u3=v.x-v1.x;
        u4=v.x-v3.x;

        w1=v1.y-v3.y;
        w2=v2.y-v3.y;
        w3=v.y-v1.y;
        w4=v.y-v3.y;
    }
    f32 denom=w1*u2-w2*u1;
    if(lCompareFloat(0.0f,denom))
    {
        out[0]=out[1]=out[2]=lNaN;
        return false;
    }
    denom=1.0f/denom;

    out[0]=lRound((w4*u2-w2*u4)*denom,6);
    out[1]=lRound((w1*u3-w3*u1)*denom,6);
    out[2]=lRound(1.0f-out[0]-out[1],6);

    return true;
}

LVector3 LTriangle::getCircumcenter() const
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    f32 d1=-e2.getDotProduct(e3);
    f32 d2=-e3.getDotProduct(e1);
    f32 d3=-e1.getDotProduct(e2);
    f32 c1=d2*d3;
    f32 c2=d3*d1;
    f32 c3=d1*d2;
    f32 c=c1+c2+c3;
    LVector3 o=((c2+c3)*v1+(c3+c1)*v2+(c1+c2)*v3)/2.0f*c;
    return o;
}

f32 LTriangle::getCircumcenterRadius() const
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    f32 d1=-e2.getDotProduct(e3);
    f32 d2=-e3.getDotProduct(e1);
    f32 d3=-e1.getDotProduct(e2);
    f32 c1=d2*d3;
    f32 c2=d3*d1;
    f32 c3=d1*d2;
    f32 c=c1+c2+c3;
    return lSqrt((d1+d2)*(d2+d3)*(d3+d1)/c)/2.0f;
}

LVector3 LTriangle::getGravityCenter() const
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    return (v1+v2+v3)/3.0f;
}

LVector3 LTriangle::getIncenter() const
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    return (l1*v1+l2*v2+l3*v3)/getPerimeter();
}

f32 LTriangle::getIncenterRadius() const
{
    //Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    return getArea()/getPerimeter();
}

f32 LTriangle::getPerimeter() const
{
    return l1+l2+l3;
}

LTriangle LTriangle::getTransformed(const LMatrix &_m) const
{
    LTriangle o=*this;
    o.transform(_m);
    return o;
}

void LTriangle::set(const LVector3 &_v1, const LVector3 &_v2, const LVector3 &_v3)
{
    v1=_v1;
    v2=_v2;
    v3=_v3;
    update();
}

void LTriangle::transform(const LMatrix &_m)
{
    v1*=_m;
    v2*=_m;
    v3*=_m;
    update();
}

void LTriangle::update()
{
    e1=v3-v2;
    e2=v1-v3;
    e3=v2-v1;
    l1=e1.getLength();
    l2=e2.getLength();
    l3=e3.getLength();
    mNormal=e3.getCrossProduct(-e1).getNormalized();
    a1=e2.getAngelFrom(-e3);
    a2=e3.getAngelFrom(-e1);
    a3=e1.getAngelFrom(-e2);
}

LTriangle &LTriangle::operator=(const LTriangle &_other)
{
    v1=_other.v1;
    v2=_other.v2;
    v3=_other.v3;

    a1=_other.a1;
    a2=_other.a2;
    a3=_other.a3;

    e1=_other.e1;
    e2=_other.e2;
    e3=_other.e3;

    l1=_other.l1;
    l2=_other.l2;
    l3=_other.l3;

    mNormal=_other.mNormal;

    return *this;
}

bool LTriangle::operator==(const LTriangle &_other) const
{
    return(
               (
                    ((v1==_other.v1)&&(v2==_other.v2)&&(v3==_other.v3))||
                    ((v1==_other.v2)&&(v2==_other.v3)&&(v3==_other.v1))||
                    ((v1==_other.v3)&&(v2==_other.v1)&&(v3==_other.v2))
                )
                &&
                mNormal==_other.mNormal
          );
}

bool LTriangle::operator!=(const LTriangle &_other) const
{
    return !(*this==_other);
}

LNAMESPACE_END

#endif // LTRIANGLE_H
