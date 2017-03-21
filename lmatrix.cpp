#include "lmatrix.h"
#include "lvector3.h"
LNAMESPACE_BEGIN

const LMatrix LMatrix::identity(
        1.0f,0.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f
        );
const LMatrix LMatrix::zero(
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f
        );


LMatrix LMatrix::createRotationMatrixAxis(LVector3 _axis,const f32& _angle)
{
    // Adapted from : https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
    LMatrix out;
    _axis.normalize();
    f32 cosang=lCos(-_angle);
    f32 sinang=lSin(-_angle);
    f32 onesubcosang=1-cosang;

    out.m11=cosang+((_axis.x*_axis.x)*(onesubcosang));
    out.m12=(_axis.x*_axis.y*(onesubcosang))-(_axis.z*sinang);
    out.m13=(_axis.x*_axis.z*(onesubcosang))+(_axis.y*sinang);

    out.m21=(_axis.y*_axis.z*(onesubcosang))+(_axis.z*sinang);
    out.m22=cosang+((_axis.y*_axis.y)*(onesubcosang));
    out.m23=(_axis.y*_axis.z*(onesubcosang))-(_axis.x*sinang);

    out.m31=(_axis.z*_axis.x*(onesubcosang))-(_axis.y*sinang);
    out.m32=(_axis.z*_axis.y*(onesubcosang))+(_axis.x*sinang);
    out.m33=cosang+((_axis.z*_axis.z)*(onesubcosang));

    return out;
}

LMatrix LMatrix::createScaleMatrix(const LVector3 &_scale)
{
    LMatrix out;
    out.m11=_scale.x;
    out.m22=_scale.y;
    out.m33=_scale.z;
    return out;
}

LMatrix LMatrix::createTranslationMatrix(const LVector3 &_position)
{
    LMatrix out;
    out.m41=_position.x;
    out.m42=_position.y;
    out.m43=_position.z;
    return out;
}

LMatrix LMatrix::createViewMatrix(const LVector3 &_camerapos,const LVector3 &axis_x, const LVector3 &axis_y, const LVector3 &axis_z)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m11=axis_x.x;
    out.m12=axis_y.x;
    out.m13=axis_z.x;

    out.m21=axis_x.y;
    out.m22=axis_y.y;
    out.m23=axis_z.y;

    out.m31=axis_x.z;
    out.m32=axis_y.z;
    out.m33=axis_z.z;

    out.m41=-LVector3::dotProduct(axis_x,_camerapos);
    out.m42=-LVector3::dotProduct(axis_y,_camerapos);
    out.m43=-LVector3::dotProduct(axis_z,_camerapos);
    return out;
}

LMatrix LMatrix::createViewMatrixLH(const LVector3 &_camerapos, const LVector3 &_lookat, const LVector3 &_up)
{
    // Adapted from DirectX documents
    LVector3 axis_z=(_lookat-_camerapos).getNormalized();
    LVector3 axis_x=LVector3::crossProduct(axis_z,_up).getNormalized();
    LVector3 axis_y=LVector3::crossProduct(axis_z,axis_x);
    return createViewMatrix(_camerapos,axis_x,axis_y,axis_z);
}

LMatrix LMatrix::createViewMatrixRH(const LVector3 &_camerapos, const LVector3 &_lookat, const LVector3 &_up)
{
    // Adapted from DirectX documents
    LVector3 axis_z=(_camerapos-_lookat).getNormalized();
    LVector3 axis_x=LVector3::crossProduct(axis_z,_up).getNormalized();
    LVector3 axis_y=LVector3::crossProduct(axis_z,axis_x);
    return createViewMatrix(_camerapos,axis_x,axis_y,axis_z);
}

LVector3 LMatrix::getRotationParameter() const
{
    LVector3 out;
    //!Algorithm1 Adapted from '3D Math Primer for Graphics and Game Development' book by Fletcher Dunn and lan Parberry
    /*f32 sy=-m23;
    if(sy<=-1.0f)
        out.x=-90.0f;
    else if(sy>=1.0f)
        out.x=90.0f;
    else
    {
        //out.x=lASin(-sy);
        // this not working for x<=-90.0f
    }

    if(sy>0.9999f)
    {
        out.y=lATan2(-m31,m11);
        out.z=0.0f;
    }
    else
    {
        out.y=lATan2(-m13,m33);
        out.z=lATan2(-m21,m22);
    }
    */
    /////////////////////////////////////////////////
    //Algorithm 2 Adapted from 'Extracting Euler Angles from a Rotation Matrix' By 'Mike Day'
    /*out.x=lATan2(m23,m33);
    out.y=lATan2(-m13,lSqrt(m11*m11+m12*m12));
    f32 sx=lSin(out.x);
    f32 cx=lCos(out.x);
    out.z=lATan2(sx*m31-cx*m21,cx*m22-sx*m32);*/
    //////////////////////////////////////////////////////////////////////////
    f32 sy=-m23;
    if(sy<=-1.0f)
        out.x=-90.0f;
    else if(sy>=1.0f)
        out.x=90.0f;
    else
    {
        //out.x=lASin(-sy);
        // this not working for x<=-90.0f
        out.x=lATan2(m23,m33);
    }

    if(sy>0.9999f)
    {
        out.y=lATan2(-m31,m11);
        out.z=0.0f;
    }
    else
    {
        out.y=lATan2(-m13,m33);
        out.z=lATan2(-m21,m22);
    }
    return out;
}

LVector3 LMatrix::getScaleParameter() const
{
    return LVector3(m11,m22,m33);
}

LVector3 LMatrix::getTranslationParameter() const
{
    return LVector3(m41,m42,m43);
}

LNAMESPACE_END

