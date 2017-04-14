#include "lboundingbox.h"
#include "lplane.h"
#include "lboundingsphere.h"

LNAMESPACE_BEGIN

/*!
 * \enum LBoundingBox::LCorner
 * \en
 * \brief Using to access to AABB corners
 * \enden
 *
 * \fa
 * \brief  جهت دسترسی به گوشه های یک جعبه می باشد
 * \endfa
 * \sa getCorner(LCorner _t)const
 */


/*!
* \en
* \brief BoundingBox-Plane Intersection Check
* \param _other Plane that need to be check
* \return if BoundingBox intersects other plane will returns true
* \enden
*
* \fa
* \brief تشخیص برخورد بین جعبه و صفحه
* \param _other صفحه ای که باید چک بشه
* \return اگه جعبه با صفحه دیگری برخورد داشت مقدار صحیح رو برمیگردونه
* \endfa
*/
bool LBoundingBox::isIntersect(const LPlane &_other) const
{
    bool a=_other.isFrontSide(mCorners[0]);
    return !(
                _other.isFrontSide(mCorners[1])==a&&
                _other.isFrontSide(mCorners[2])==a&&
                _other.isFrontSide(mCorners[3])==a&&
                _other.isFrontSide(mCorners[4])==a&&
                _other.isFrontSide(mCorners[5])==a&&
                _other.isFrontSide(mCorners[6])==a&&
                _other.isFrontSide(mCorners[7])==a
            );
}

/*!
* \en
* \brief BoundingBox-BoundingSphere Intersection Check
* \param _other Sphere that need to be check
* \return if BoundingBox intersects other sphere returns true
* \enden
*
* \fa
* \brief تشخیص برخورد بین جعبه و کره
* \param _other صفحه ای که باید چک بشه
* \return اگه جعبه با صفحه دیگری برخورد داشت مقدار صحیح رو برمیگردونه
* \endfa
*/
bool LBoundingBox::isIntersect(const LBoundingSphere &_other) const
{
    LVector3 spos=_other.getPos();
    LVector3 cp;// closest point to sphere

    if(spos.x>=mMax.x)
        cp.x=mMax.x;
    else if(spos.x<=mMin.x)
        cp.x=mMin.x;

    if(spos.y>=mMax.y)
        cp.y=mMax.y;
    else if(spos.y<=mMin.y)
        cp.y=mMin.y;

    if(spos.z>=mMax.z)
        cp.z=mMax.z;
    else if(spos.z<=mMin.z)
        cp.z=mMin.z;

    return (cp.getDistanceFrom(spos)<=_other.getRadius());
}


LNAMESPACE_END


