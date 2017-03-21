#ifndef LTRIANGLE_H
#define LTRIANGLE_H
#include "ldefines.h"
#include "lvector3.h"

LNAMESPACE_BEGIN

class LAPI LTriangle
{
public:
    linline LTriangle();

    linline LTriangle(const LVector3& _v1,const LVector3& _v2,const LVector3& _v3);

    //! Get Triangle Area
    linline f32             getArea()const;

    //! Get Triangle Perimeter
    linline f32             getPerimeter()const;

    //! Set Triangle Parameters
    linline void            set(const LVector3& _v1,const LVector3& _v2,const LVector3& _v3);

    //! Update Triangle Values Based On Only Vertices
    linline void            update();

public:
    LVector3 v1,v2,v3;  // Vertices
    f32      a1,a2,a3;  // Angles of vertices
    LVector3 e1,e2,e3;  // Edges
    f32      l1,l2,l3;  // Edge Length
    LVector3 normal;    // Normal Vector of Triangle
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

f32 LTriangle::getPerimeter() const
{
    return l1+l2+l3;
}

void LTriangle::set(const LVector3 &_v1, const LVector3 &_v2, const LVector3 &_v3)
{
    v1=_v1;
    v2=_v2;
    v3=_v3;
    update();
}

void LTriangle::update()
{
    e1=v3-v2;
    e2=v3-v1;
    e3=v2-v1;
    l1=e1.getLength();
    l2=e2.getLength();
    l3=e3.getLength();
    normal=e2.getCrossProduct(e3).getNormalized();
    a1=e2.getAngelFrom(e3);
    a2=e1.getAngelFrom(e3);
    a3=e1.getAngelFrom(e2);
}

LNAMESPACE_END

#endif // LTRIANGLE_H
