#ifndef LMATRIX_H
#define LMATRIX_H
#include "ldefines.h"
#include "lmemory.h"
#include "llog.h"
#include "lmathutility.h"
#include "lutility.h"

LNAMESPACE_BEGIN

// forward declartion
class LVector3;

/*!
 * \ingroup Math
 *
 * \en
 * \brief Matrix
 * This class using for creating 4 x 4 matrix <br>
 * Matrix 4x4 = <br>
 *              m11 m12 m13 m14 <br>
 *              m21 m22 m23 m24 <br>
 *              m31 m32 m33 m34 <br>
 *              m41 m42 m43 m44 <br>
 * \enden
 */
class LAPI LMatrix
{
public:
    //! Default Matrix Constructor will Create Identity matrix
    linline                 LMatrix();

    //! Matrix with first value
    linline                 LMatrix(f32 _11,f32 _12,f32 _13,f32 _14,
                                    f32 _21,f32 _22,f32 _23,f32 _24,
                                    f32 _31,f32 _32,f32 _33,f32 _34,
                                    f32 _41,f32 _42,f32 _43,f32 _44
                                   );

    //! Matrix from pointer or array
    linline                 LMatrix(f32* _in);

    //! Matrix from 2D array
    linline                 LMatrix(f32 _in[4][4]);

    // Copy Constructor
    linline                 LMatrix(const LMatrix& _other);

    //! Access to Matrix element
    linline f32&            at(u32 i);
    //! \copydoc at(u32 i)
    linline f32&            at(u32 i,u32 j);
    //! \copydoc at(u32 i)
    linline f32             at(u32 i)const;
    //! \copydoc at(u32 i)
    linline f32             at(u32 i,u32 j)const;

    //! Creates an orthgraphic projection Left Handed by screen values
    linline static LMatrix  createOrthgraphicProjectionLH(const f32& _left=0.0f,const f32& _right=800.0f,const f32& _top=0.0f,const f32& _bottom=600.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates an orthgraphic Projection Right Handed by screen values
    linline static LMatrix  createOrthgraphicProjectionRH(const f32& _left=0.0f,const f32& _right=800.0f,const f32& _top=0.0f,const f32& _bottom=600.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates an orthgraphic Projection Left Handed
    linline static LMatrix  createOrthgraphicProjectionLH(const f32& _width=800.0f,const f32& _height=600.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates an orthgraphic Projection Right Handed
    linline static LMatrix  createOrthgraphicProjectionRH(const f32& _width=800.0f,const f32& _height=600.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates a Perspective Projection Left Handed
    linline static LMatrix  createPerspectiveProjectionLH(const f32& _fov=45.0f,const f32& _aspectratio=4.0f/3.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates a Perspective Projection Right Handed
    linline static LMatrix  createPerspectiveProjectionRH(const f32& _fov=45.0f,const f32& _aspectratio=4.0f/3.0f,const f32& _znear=0.1f,const f32& _zfar=1000.0f);

    //! Creates a Rotation Matrix from Axis
    static LMatrix          createRotationMatrixAxis(LVector3 _axis, const f32& _angle);

    //! Creates a Rotation Matrix from Yaw Pitch Roll
    //! roll  = z
    //! pitch = x
    //! yaw   = y
    linline static LMatrix  createRotationMatrix(const f32& _pitch,const f32& _yaw,const f32& _roll);

    //! Creates a RotationX Matrix
    linline static LMatrix  createRotationMatrixX(const f32& _angle);

    //! Creates a RotationY Matrix
    linline static LMatrix  createRotationMatrixY(const f32& _angle);

    //! Creates a RotationZ Matrix
    linline static LMatrix  createRotationMatrixZ(const f32& _angle);

    //! Creates a scale transform matrix
    static LMatrix          createScaleMatrix(const LVector3& _scale);

    //! Create a translation Matrix
    static LMatrix          createTranslationMatrix(const LVector3& _position);

    //! Create a View Matrix
    static LMatrix          createViewMatrix(const LVector3& _camerapos,const LVector3& axis_x, const LVector3& axis_y, const LVector3& axis_z);

    //! Create a View Matrix Left Handed
    static LMatrix          createViewMatrixLH(const LVector3& _camerapos, const LVector3& _forward, const LVector3& _up);

    //! Create a View Matrix Right Handed
    static LMatrix          createViewMatrixRH(const LVector3& _camerapos, const LVector3& _forward, const LVector3& _up);

    //! Get determinant of matrix
    linline f32             getDeterminant()const;

    //! Get Inversed copy of this matrix
    linline LMatrix         getInversed()const;

    //! Get inverse transposed of this . useful for compute normal vectors transform matrix
    linline LMatrix         getInverseTransposed()const;

    //! Get Rotation (where the matrix is a rotation matrix (only3x3 used)) will convert to euler angles
    LVector3                getRotationParameter()const;

    //! Get Scale (where the matrix is a scale matrix)
    LVector3                getScaleParameter()const;

    //! Get Only scale and rotation part of this matrix (copy) \sa  removeTranslation
    linline LMatrix         getRotationScaleOnly()const;

    //! Get only translation part of this matrix (copy) \sa removeRotationScale
    linline LMatrix         getTranslationOnly()const;

    //! Get Translation (where the matrix is a translation matrix)
    LVector3                getTranslationParameter()const;

    //! Get transposed copy of transposed this matrix
    linline LMatrix         getTransposed()const;

    //! Inverse the Matrix
    linline bool            inverse();

    //! If Matrix was Identity returns true . otherwise returns false
    linline bool            isIdentity()const;

    //! is Matrix able to inverse?
    linline bool            isInversable()const;

    //! remove translation part of matrix to convert to rotation and scale only
    //! will convert to
    //! m11 m12 m13 0
    //! m21 m22 m23 0
    //! m31 m32 m33 0
    //! 0   0   0   1
    linline void            removeTranslation();

    //! remove rotation/scale part of matrix and will convert to translation matix only
    //! 1   0   0   0
    //! 0   1   0   0
    //! 0   0   1   0
    //! m41 m42 m43 1
    linline void            removeRotationScale();

    // set Matrix
    linline void            set(f32 _11,f32 _12,f32 _13,f32 _14,
                                f32 _21,f32 _22,f32 _23,f32 _24,
                                f32 _31,f32 _32,f32 _33,f32 _34,
                                f32 _41,f32 _42,f32 _43,f32 _44
                                );
    // set Matrix
    linline void            set(f32* _in);
    // set Matrix
    linline void            set(f32 _in[4][4]);

    //! Transpose the Matrix
    linline void            transpose();

    //! Copy Assign Operator
    linline LMatrix& operator = (const LMatrix& _other);

    //! \copydoc at(u32 i)
    linline f32&            operator() (u32 i);
    //! \copydoc at(u32 i)
    linline f32&            operator() (u32 i,u32 j);
    //! \copydoc at(u32 i)
    linline f32             operator() (u32 i)const;
    //! \copydoc at(u32 i)
    linline f32             operator() (u32 i,u32 j)const;

    //! Access to Matrix row
    linline f32*            operator[] (u32 i);
    //! Access to Matrix row
    linline const f32*      operator[] (u32 i)const;

    //! Compare two matrix
    linline bool            operator == (const LMatrix& _other)const;

    //! Compare two matrix
    linline bool            operator != (const LMatrix& _other)const;

    //! Addtion
    linline LMatrix         operator + (const LMatrix& _other)const;
    linline LMatrix&        operator += (const LMatrix& _other);

    //! Sub
    linline LMatrix         operator - (const LMatrix& _other)const;
    linline LMatrix&        operator -= (const LMatrix& _other);

    //! Product
    linline LMatrix         operator * (const LMatrix& _other)const;
    linline LMatrix&        operator *= (const LMatrix& _other);
    linline LMatrix         operator * (const float& _other)const;
    linline LMatrix&        operator *= (const float& _other);

    //! Positive and Negetive sign
    linline LMatrix         operator + ()const;
    linline LMatrix         operator - ()const;

    //! Identity Matrix
    static const LMatrix identity;

    //! Zero Matrix
    static const LMatrix zero;

public:
    union
    {
        struct
        {
            f32 m11,m12,m13,m14;
            f32 m21,m22,m23,m24;
            f32 m31,m32,m33,m34;
            f32 m41,m42,m43,m44;
        };
        f32  m[4][4];
    };
};

/*!
 * \brief Default Matrix Constructor will Create Identity matrix
 *
 * \sa LMatrix::identity
 */
LMatrix::LMatrix():
    m{  {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}}
{

}

/*!
 * \en
 * \fn LMatrix::LMatrix(f32 _11, f32 _12, f32 _13, f32 _14,f32 _21, f32 _22, f32 _23, f32 _24,f32 _31, f32 _32, f32 _33, f32 _34,f32 _41, f32 _42, f32 _43, f32 _44):
 * \brief Matrix with first values
 * \enden
 *
 * \sa LMatrix::set(f32 _11,f32 _12,f32 _13,f32 _14,f32 _21,f32 _22,f32 _23,f32 _24,f32 _31,f32 _32,f32 _33,f32 _34,f32 _41,f32 _42,f32 _43,f32 _44)
 */
LMatrix::LMatrix(f32 _11, f32 _12, f32 _13, f32 _14,
                 f32 _21, f32 _22, f32 _23, f32 _24,
                 f32 _31, f32 _32, f32 _33, f32 _34,
                 f32 _41, f32 _42, f32 _43, f32 _44):
    m11(_11),
    m12(_12),
    m13(_13),
    m14(_14),

    m21(_21),
    m22(_22),
    m23(_23),
    m24(_24),

    m31(_31),
    m32(_32),
    m33(_33),
    m34(_34),

    m41(_41),
    m42(_42),
    m43(_43),
    m44(_44)
{

}

/*!
 * \en
 * \brief Create matrix from pointer or array
 * \enden
 *
 * \sa LMatrix::set(f32* _in)
 */
LMatrix::LMatrix(f32 *_in):
    m11(_in[0]),
    m12(_in[1]),
    m13(_in[2]),
    m14(_in[3]),

    m21(_in[4]),
    m22(_in[5]),
    m23(_in[6]),
    m24(_in[7]),

    m31(_in[8]),
    m32(_in[9]),
    m33(_in[10]),
    m34(_in[11]),

    m41(_in[12]),
    m42(_in[13]),
    m43(_in[14]),
    m44(_in[15])
{

}

/*!
 * \en
 * \brief Matrix from 2D 4x4 array
 * \enden
 *
 * \sa LMatrix::set(f32 _in[4][4])
 */
LMatrix::LMatrix(f32 _in[4][4]):
    m11(_in[0][0]),
    m12(_in[0][1]),
    m13(_in[0][2]),
    m14(_in[0][3]),

    m21(_in[1][0]),
    m22(_in[1][1]),
    m23(_in[1][2]),
    m24(_in[1][3]),

    m31(_in[2][0]),
    m32(_in[2][1]),
    m33(_in[2][2]),
    m34(_in[2][3]),

    m41(_in[3][0]),
    m42(_in[3][1]),
    m43(_in[3][2]),
    m44(_in[3][3])
{

}

LMatrix::LMatrix(const LMatrix &_other)
{
    (*this)=_other;
}

f32& LMatrix::at(u32 i)
{
    lError(i>=16,"f32& LMatrix::at(u32 i) : i is  not acceptable",m[0][0]);
    return m[i/4][i%4];
}

f32& LMatrix::at(u32 i, u32 j)
{
    lError(i>=4||j>=4,"f32& LMatrix::at(u32 i, u32 j) : i or j is  not acceptable",m[0][0]);
    return m[i][j];
}

f32 LMatrix::at(u32 i)const
{
    lError(i>=16,"f32 LMatrix::at(u32 i)const : i is  not acceptable",m[0][0]);
    return m[i/4][i%4];
}

f32 LMatrix::at(u32 i, u32 j)const
{
    lError(i>=4||j>=4,"f32 LMatrix::at(u32 i, u32 j)const : i or j is  not acceptable",m[0][0]);
    return m[i][j];
}

/*!
 * \en
 * \brief Creates an orthgraphic projection Left Handed by screen values
 * \param _left left screen position
 * \param _right right screen position
 * \param _top  top screen position
 * \param _bottom botton screen position
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createOrthgraphicProjectionLH(const f32 &_left, const f32 &_right, const f32 &_top, const f32 &_bottom, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m11=2.0f/(_right-_left);
    out.m22=2.0f/(_top-_bottom);
    out.m33=1.0f/(_znear-_zfar);
    out.m43=_znear*out.m33;
    out.m41=(_left+_right)/(_left-_right);
    out.m42=(_bottom+_top)/(_bottom-_top);
    return out;
}

/*!
 * \en
 * \brief Creates an orthgraphic projection Right Handed by screen values
 * \param _left left screen position
 * \param _right right screen position
 * \param _top  top screen position
 * \param _bottom botton screen position
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createOrthgraphicProjectionRH(const f32 &_left, const f32 &_right, const f32 &_top, const f32 &_bottom, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m11=2.0f/(_right-_left);
    out.m22=2.0f/(_top-_bottom);
    out.m33=1.0f/(_zfar-_znear);
    out.m43=_znear*out.m33;
    out.m41=(_left+_right)/(_left-_right);
    out.m42=(_bottom+_top)/(_bottom-_top);
    return out;
}

/*!
 * \en
 * \brief Creates an orthgraphic Projection Left Handed
 * \param _width screen width value
 * \param _height screen height value
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createOrthgraphicProjectionLH(const f32 &_width, const f32 &_height, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m11=2.0f/_width;
    out.m22=2.0f/_height;
    out.m33=1.0f/(_zfar-_znear);
    out.m43=-_znear*out.m33;
    return out;
}

/*!
 * \en
 * \brief Creates an orthgraphic Projection Right Handed
 * \param _width screen width value
 * \param _height screen height value
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createOrthgraphicProjectionRH(const f32 &_width, const f32 &_height, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m11=2.0f/_width;
    out.m22=2.0f/_height;
    out.m33=1.0f/(_znear-_zfar);
    out.m43=_znear*out.m33;
    return out;
}

/*!
 * \en
 * \brief Creates a Perspective Projection Left Handed
 * \param _fov field of view by degree (not radian)
 * \param _aspectratio aspect ratio
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createPerspectiveProjectionLH(const f32 &_fov, const f32 &_aspectratio, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m22=lCotan(_fov/2.0f);
    out.m11=out.m22/_aspectratio;
    out.m33=_zfar/(_zfar-_znear);
    out.m43=-_znear*out.m33;
    out.m34=1.0f;
    out.m44=0.0f;
    return out;
}

/*!
 * \en
 * \brief Creates a Perspective Projection Right Handed
 * \param _fov field of view by degree (not radian)
 * \param _aspectratio aspect ratio
 * \param _znear near clip value
 * \param _zfar far clip value
 * \enden
 */
LMatrix LMatrix::createPerspectiveProjectionRH(const f32 &_fov, const f32 &_aspectratio, const f32 &_znear, const f32 &_zfar)
{
    // Adapted from DirectX documents
    LMatrix out;
    out.m22=lCotan(_fov/2.0f);
    out.m11=out.m22/_aspectratio;
    out.m33=_zfar/(_znear-_zfar);
    out.m43=_znear*out.m33;
    out.m34=-1.0f;
    out.m44=0.0f;
    return out;
}

/*!
 * \en
 * \brief Create a rotation matrix around X axis
 * \param _angle by degree
 * \enden
 */
LMatrix LMatrix::createRotationMatrixX(const f32 &_angle)
{
    LMatrix out;
    f32 _ang=-lLimitedAngle180(_angle);
    out.m22=out.m33=lCos(_ang);
    out.m32=-(out.m23=lSin(_ang));
    return out;
}

/*!
 * \en
 * \brief Create a rotation matrix around Y axis
 * \param _angle by degree
 * \enden
 */
LMatrix LMatrix::createRotationMatrixY(const f32 &_angle)
{
    LMatrix out;
    f32 _ang=-lLimitedAngle180(_angle);
    out.m11=out.m33=lCos(_ang);
    out.m13=-(out.m31=lSin(_ang));
    return out;
}

/*!
 * \en
 * \brief Create a combined rotation matrix by pitch(X) , yaw(Y) and roll(Z). Product order is roll*pitch*yaw
 * \param _pitch rotation angle around X
 * \param _yaw rotation angle around Y
 * \param _roll rotation angle around Z
 * \enden
 */
LMatrix LMatrix::createRotationMatrix(const f32& _pitch,const f32& _yaw,const f32& _roll)
{
    LMatrix out;
    out*=LMatrix::createRotationMatrixZ(_roll);
    out*=LMatrix::createRotationMatrixX(_pitch);
    out*=LMatrix::createRotationMatrixY(_yaw);
    return out;
}

/*!
 * \en
 * \brief Create a rotation matrix around Z axis
 * \param _angle by degree
 * \enden
 */
LMatrix LMatrix::createRotationMatrixZ(const f32 &_angle)
{
    LMatrix out;
    f32 _ang=lLimitedAngle180(_angle);
    out.m11=out.m22=lCos(_ang);
    out.m21=-(out.m12=lSin(_ang));
    return out;
}

/*!
 * \en
 * \brief returns determinant of this matrix
 * \enden
 */
f32 LMatrix::getDeterminant() const
{
    /*
     * m22 m23 m24
     * -----------
     * m32 m33 m34
     * m42 m43 m44
     */
    //f32 A = m22*(m33*m44-m34*m43) -m23*(m32*m44-m34*m42) +m24*(m32*m43-m33*m42);

    /*
     * m21 m23 m24
     * -----------
     * m31 m33 m34
     * m41 m43 m44
     */
    //f32 B = m21*(m33*m44-m34*m43) -m23*(m31*m44-m34*m41) +m24*(m31*m43-m33*m41);

    /*
     * m21 m22 m24
     * -----------
     * m31 m32 m34
     * m41 m42 m44
     */
    //f32 C = m21*(m32*m44-m34*m42) -m22*(m31*m44-m34*m41) +m24*(m31*m42-m32*m41);

    /*
     * m21 m22 m23
     * -----------
     * m31 m32 m33
     * m41 m42 m43
     */
    //f32 D = m21*(m32*m43-m33*m42) -m22*(m31*m43-m33*m41) +m23*(m31*m42-m32*m41);

    /*
     * a   b   c   d
     * m21 m22 m23 m24
     * m31 m32 m33 m34
     * m41 m42 m43 m44
     */
    /*
     * a=m11;
     * b=m12;
     * c=m13;
     * d=m13;
    */
    //return A*m11-B*m12+C*m13-D*m14;

    // Combined version of previous algorithm
    return m11 * (m22*(m33*m44-m34*m43) -m23*(m32*m44-m34*m42) +m24*(m32*m43-m33*m42)) -
            m12 * (m21*(m33*m44-m34*m43) -m23*(m31*m44-m34*m41) +m24*(m31*m43-m33*m41)) +
            m13 * (m21*(m32*m44-m34*m42) -m22*(m31*m44-m34*m41) +m24*(m31*m42-m32*m41)) -
            m14 * (m21*(m32*m43-m33*m42) -m22*(m31*m43-m33*m41) +m23*(m31*m42-m32*m41));
}

/*!
 * \en
 * \brief  Get Inversed copy of this matrix
 * \enden
 *
 * \sa inverse()
 */
LMatrix LMatrix::getInversed() const
{
    LMatrix temp=(*this);
    temp.inverse();
    return temp;
}

/*!
 * \en
 * \brief  Get Inversed - Transposed of this matrix. using to transform normal vectors
 * \enden
 *
 * \sa inverse()
 * \sa transpose()
 */
LMatrix LMatrix::getInverseTransposed() const
{
    LMatrix out=(*this);
    out.inverse();
    out.transpose();
    return out;
}

LMatrix LMatrix::getRotationScaleOnly() const
{
    LMatrix o=*this;
    o.removeTranslation();
    return o;
}

LMatrix LMatrix::getTranslationOnly() const
{
    LMatrix o=*this;
    o.removeRotationScale();
    return o;
}

/*!
 * \en
 * \brief  Get Transposed of this matrix.
 * \enden
 *
 * \sa transpose()
 */
LMatrix LMatrix::getTransposed() const
{
    LMatrix temp=(*this);
    temp.transpose();
    return temp;
}

/*!
 * \en
 * \brief LMatrix::inverse() inverse this matrix. if a*Matrix=b then b*inversed_Matrix is same a. type of a maybe LMatrix or LVector4
 * \warning Before inverse be sure matrix is inversable with isInversable() .
 * \return If matrix was not iversable returns false.
 * \enden
 *
 * \sa getInversed()
 * \sa isInversable()
 */
bool LMatrix::inverse()
{
    // ToDo : Get Faster Algorithm
    /*
     * m11 m12 m13 m14
     * m21 m22 m23 m24
     * m31 m32 m33 m34
     * m41 m42 m43 m44
     */
    // Adapted from http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
    float det=this->getDeterminant();
    if(det==0.0f)
        return false;
    det=1.0f/det;
    LMatrix o;
    o.m11= det*(m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m22*m34*m43 - m23*m32*m44 - m24*m33*m42);
    o.m12= det*(m12*m34*m43 + m13*m32*m44 + m14*m33*m42 - m12*m33*m44 - m13*m34*m42 - m14*m32*m43);
    o.m13= det*(m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m12*m24*m43 - m13*m22*m44 - m14*m23*m42);
    o.m14= det*(m12*m24*m33 + m13*m22*m34 + m14*m23*m32 - m12*m23*m34 - m13*m24*m32 - m14*m22*m33);
    o.m21= det*(m21*m34*m43 + m23*m31*m44 + m24*m33*m41 - m21*m33*m44 - m23*m34*m41 - m24*m31*m43);
    o.m22= det*(m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m11*m34*m43 - m13*m31*m44 - m14*m33*m41);
    o.m23= det*(m11*m24*m43 + m13*m21*m44 + m14*m23*m41 - m11*m23*m44 - m13*m24*m41 - m14*m21*m43);
    o.m24= det*(m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m11*m24*m33 - m13*m21*m34 - m14*m23*m31);
    o.m31= det*(m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m21*m34*m42 - m22*m31*m44 - m24*m32*m41);
    o.m32= det*(m11*m34*m42 + m12*m31*m44 + m14*m32*m41 - m11*m32*m44 - m12*m34*m41 - m14*m31*m42);
    o.m33= det*(m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m11*m24*m42 - m12*m21*m44 - m14*m22*m41);
    o.m34= det*(m11*m24*m32 + m12*m21*m34 + m14*m22*m31 - m11*m22*m34 - m12*m24*m31 - m14*m21*m32);
    o.m41= det*(m21*m33*m42 + m22*m31*m43 + m23*m32*m41 - m21*m32*m43 - m22*m33*m41 - m23*m31*m42);
    o.m42= det*(m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m11*m33*m42 - m12*m31*m43 - m13*m32*m41);
    o.m43= det*(m11*m23*m42 + m12*m21*m43 + m13*m22*m41 - m11*m22*m43 - m12*m23*m41 - m13*m21*m42);
    o.m44= det*(m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31);
    (*this)=o;
    return true;
}

/*!
 * \en
 * \brief  check out this matrix is identity
 * \enden
 *
 * \sa LMatrix::identity
 */
bool LMatrix::isIdentity() const
{
    return(*this==identity);
}

/*!
 * \en
 * \brief  check out this matrix is Inversable or not
 * \return if matrix was Inversable returns true
 * \enden
 *
 * \sa inverse()
 */
bool LMatrix::isInversable() const
{
    return (getDeterminant()!=0.0f);
}

/*!
 * \en
 * will converted to
 *
 * m11 m12 m13 0
 * m21 m22 m23 0
 * m31 m32 m33 0
 * 0   0   0   1
 * \enden
 */
void LMatrix::removeTranslation()
{
    m41=m14=0.0f;
    m42=m24=0.0f;
    m43=m34=0.0f;
    m44=1.0f;
}

void LMatrix::removeRotationScale()
{
    m12=m13=m14=m21=m23=m24=m31=m32=m34=0.0f;
    m11=m22=m33=m44=1.0f;
}

/*!
 * \en
 * \brief  set Matrix with first value
 * \enden
 *
 */
void LMatrix::set(f32 _11, f32 _12, f32 _13, f32 _14,
                  f32 _21, f32 _22, f32 _23, f32 _24,
                  f32 _31, f32 _32, f32 _33, f32 _34,
                  f32 _41, f32 _42, f32 _43, f32 _44)
{
    m11=_11;
    m12=_12;
    m13=_13;
    m14=_14;

    m21=_21;
    m22=_22;
    m23=_23;
    m24=_24;

    m31=_31;
    m32=_32;
    m33=_33;
    m34=_34;

    m41=_41;
    m42=_42;
    m43=_43;
    m44=_44;
}

/*!
 * \en
 * \brief  set matrix from pointer or array
 * \enden
 *
 */
void LMatrix::set(f32 *_in)
{
    m11=_in[0];
    m12=_in[1];
    m13=_in[2];
    m14=_in[3];

    m21=_in[4];
    m22=_in[5];
    m23=_in[6];
    m24=_in[7];

    m31=_in[8];
    m32=_in[9];
    m33=_in[10];
    m34=_in[11];

    m41=_in[12];
    m42=_in[13];
    m43=_in[14];
    m44=_in[15];
}

/*!
 * \en
 * \brief  set Matrix from 2D 4x4 array
 * \enden
 *
 */
void LMatrix::set(f32 _in[4][4])
{
    m11=_in[0][0];
    m12=_in[0][1];
    m13=_in[0][2];
    m14=_in[0][3];

    m21=_in[1][0];
    m22=_in[1][1];
    m23=_in[1][2];
    m24=_in[1][3];

    m31=_in[2][0];
    m32=_in[2][1];
    m33=_in[2][2];
    m34=_in[2][3];

    m41=_in[3][0];
    m42=_in[3][1];
    m43=_in[3][2];
    m44=_in[3][3];
}

/*!
 * \en
 * \brief  transpose this matrix
 * transposed matrix is
 * Matrix = m11 m21 m31 m41
 *          m12 m22 m32 m42
 *          m13 m23 m33 m43
 *          m14 m24 m34 m44
 * \enden
 * \sa getTransposed()
 */
void LMatrix::transpose()
{
    lSwap(m12,m21);
    lSwap(m13,m31);
    lSwap(m14,m41);
    lSwap(m23,m32);
    lSwap(m24,m42);
    lSwap(m43,m34);
}

f32& LMatrix::operator()(u32 i)
{
    lError(i>=16,"f32& LMatrix::operator()(u32 i) : i is not acceptable",m[0][0]);
    return m[i/4][i%4];
}

f32& LMatrix::operator()(u32 i, u32 j)
{
    lError(i>=4||j>=4,"f32& LMatrix::operator()(u32 i, u32 j) : i is not acceptable",m[0][0]);
    return m[i][j];
}

f32 LMatrix::operator()(u32 i) const
{
    lError(i>=16,"f32& LMatrix::operator()(u32 i)const : i is not acceptable",m[0][0]);
    return m[i/4][i%4];
}

f32 LMatrix::operator()(u32 i, u32 j) const
{
    lError(i>=4||j>=4,"f32& LMatrix::operator()(u32 i, u32 j)const : i is not acceptable",m[0][0]);
    return m[i][j];
}

f32* LMatrix::operator[](u32 i)
{
    lError(i>=4,"f32* LMatrix::operator[](u32 i) : i is not acceptable",m[0]);
    return m[i];
}

const f32* LMatrix::operator[] (u32 i)const
{
    lError(i>=4,"f32* LMatrix::operator[](u32 i)const : i is not acceptable",m[0]);
    return m[i];
}

bool LMatrix::operator !=(const LMatrix &_other) const
{
    return !(*this==_other);
}

LMatrix& LMatrix::operator +=(const LMatrix &_other)
{
    (*this)=(*this)+_other;
    return (*this);
}

LMatrix& LMatrix::operator -=(const LMatrix &_other)
{
    (*this)=(*this)-_other;
    return (*this);
}

LMatrix& LMatrix::operator *=(const LMatrix &_other)
{
    (*this)=(*this)*_other;
    return (*this);
}


LMatrix& LMatrix::operator *= (const float& _other)
{
    (*this)=(*this)*_other;
    return (*this);
}

LMatrix LMatrix::operator +() const
{
    return (*this);
}

LMatrix& LMatrix::operator =(const LMatrix &_other)
{
    m11=_other.m11;
    m12=_other.m12;
    m13=_other.m13;
    m14=_other.m14;

    m21=_other.m21;
    m22=_other.m22;
    m23=_other.m23;
    m24=_other.m24;

    m31=_other.m31;
    m32=_other.m32;
    m33=_other.m33;
    m34=_other.m34;

    m41=_other.m41;
    m42=_other.m42;
    m43=_other.m43;
    m44=_other.m44;
    return *this;
}

bool LMatrix::operator ==(const LMatrix &_other) const
{
    if(
            lCompareFloat(m11,_other.m11)&&
            lCompareFloat(m12,_other.m12)&&
            lCompareFloat(m13,_other.m13)&&
            lCompareFloat(m14,_other.m14)&&

            lCompareFloat(m21,_other.m21)&&
            lCompareFloat(m22,_other.m22)&&
            lCompareFloat(m23,_other.m23)&&
            lCompareFloat(m24,_other.m24)&&

            lCompareFloat(m31,_other.m31)&&
            lCompareFloat(m32,_other.m32)&&
            lCompareFloat(m33,_other.m33)&&
            lCompareFloat(m34,_other.m34)&&

            lCompareFloat(m41,_other.m41)&&
            lCompareFloat(m42,_other.m42)&&
            lCompareFloat(m43,_other.m43)&&
            lCompareFloat(m44,_other.m44)
      )
        return true;
    return false;
}

LMatrix LMatrix::operator +(const LMatrix &_other) const
{
    LMatrix out;
    out.m11=m11+_other.m11;
    out.m12=m12+_other.m12;
    out.m13=m13+_other.m13;
    out.m14=m14+_other.m14;

    out.m21=m21+_other.m21;
    out.m22=m22+_other.m22;
    out.m23=m23+_other.m23;
    out.m24=m24+_other.m24;

    out.m31=m31+_other.m31;
    out.m32=m32+_other.m32;
    out.m33=m33+_other.m33;
    out.m34=m34+_other.m34;

    out.m41=m41+_other.m41;
    out.m42=m42+_other.m42;
    out.m43=m43+_other.m43;
    out.m44=m44+_other.m44;
    return out;
}

LMatrix LMatrix::operator -(const LMatrix &_other) const
{
    LMatrix out;
    out.m11=m11-_other.m11;
    out.m12=m12-_other.m12;
    out.m13=m13-_other.m13;
    out.m14=m14-_other.m14;

    out.m21=m21-_other.m21;
    out.m22=m22-_other.m22;
    out.m23=m23-_other.m23;
    out.m24=m24-_other.m24;

    out.m31=m31-_other.m31;
    out.m32=m32-_other.m32;
    out.m33=m33-_other.m33;
    out.m34=m34-_other.m34;

    out.m41=m41-_other.m41;
    out.m42=m42-_other.m42;
    out.m43=m43-_other.m43;
    out.m44=m44-_other.m44;
    return out;
}
/*
    a b c d    1  2  3  4     a1+b5+c9+d13  a2+b6+c10+d14  a3+b7+c11+d15  a4+b8+c12+d16
    e f g h  * 5  6  7  8   = e1+f5+g9+h13  e2+f6+g10+h14  e3+f7+g11+h15  e4+f8+g12+h16
    i j k l    9  10 11 12    i1+j5+k9+l13  i2+j6+k10+l14  i3+j7+k11+l15  i4+j8+k12+l16
    m n o p    13 14 15 16    m1+n5+o9+p13  m2+n6+o10+p14  m3+n7+o11+p15  m4+n8+o12+p16
*/
LMatrix LMatrix::operator *(const LMatrix &_other) const
{
    LMatrix out;
    out.m11 = m11*_other.m11+ m12*_other.m21+ m13*_other.m31+ m14*_other.m41;
    out.m12 = m11*_other.m12+ m12*_other.m22+ m13*_other.m32+ m14*_other.m42;
    out.m13 = m11*_other.m13+ m12*_other.m23+ m13*_other.m33+ m14*_other.m43;
    out.m14 = m11*_other.m14+ m12*_other.m24+ m13*_other.m34+ m14*_other.m44;

    out.m21 = m21*_other.m11+ m22*_other.m21+ m23*_other.m31+ m24*_other.m41;
    out.m22 = m21*_other.m12+ m22*_other.m22+ m23*_other.m32+ m24*_other.m42;
    out.m23 = m21*_other.m13+ m22*_other.m23+ m23*_other.m33+ m24*_other.m43;
    out.m24 = m21*_other.m14+ m22*_other.m24+ m23*_other.m34+ m24*_other.m44;

    out.m31 = m31*_other.m11+ m32*_other.m21+ m33*_other.m31+ m34*_other.m41;
    out.m32 = m31*_other.m12+ m32*_other.m22+ m33*_other.m32+ m34*_other.m42;
    out.m33 = m31*_other.m13+ m32*_other.m23+ m33*_other.m33+ m34*_other.m43;
    out.m34 = m31*_other.m14+ m32*_other.m24+ m33*_other.m34+ m34*_other.m44;

    out.m41 = m41*_other.m11+ m42*_other.m21+ m43*_other.m31+ m44*_other.m41;
    out.m42 = m41*_other.m12+ m42*_other.m22+ m43*_other.m32+ m44*_other.m42;
    out.m43 = m41*_other.m13+ m42*_other.m23+ m43*_other.m33+ m44*_other.m43;
    out.m44 = m41*_other.m14+ m42*_other.m24+ m43*_other.m34+ m44*_other.m44;
    return out;
}

LMatrix LMatrix::operator *(const float &_other) const
{
    LMatrix out;
    out.m11=m11*_other;
    out.m12=m12*_other;
    out.m13=m13*_other;
    out.m14=m14*_other;
    out.m21=m21*_other;
    out.m22=m22*_other;
    out.m23=m23*_other;
    out.m24=m24*_other;
    out.m31=m31*_other;
    out.m32=m32*_other;
    out.m33=m33*_other;
    out.m34=m34*_other;
    out.m41=m41*_other;
    out.m42=m42*_other;
    out.m43=m43*_other;
    out.m44=m44*_other;
    return out;
}

LMatrix LMatrix::operator -() const
{
    LMatrix out;
    out.m11=-m11;
    out.m12=-m12;
    out.m13=-m13;
    out.m14=-m14;

    out.m21=-m21;
    out.m22=-m22;
    out.m23=-m23;
    out.m24=-m24;

    out.m31=-m31;
    out.m32=-m32;
    out.m33=-m33;
    out.m34=-m34;

    out.m41=-m41;
    out.m42=-m42;
    out.m43=-m43;
    out.m44=-m44;
    return out;
}

LNAMESPACE_END
#endif // LMATRIX_H
