#ifndef LBOUNDINGBOX_H
#define LBOUNDINGBOX_H
#include "lcore.h"
#include "lmathutility.h"
#include "lvector3.h"
#include "lmatrix.h"

LNAMESPACE_BEGIN

// forward declartion
class LPlane;
class LBoundingSphere;

/*!
 * \ingroup Math
 *
 * \en
 * \brief Axisally Aligned Bounding Box
 * \details This class is for Axisally Aligned Bounding Box and using for intersections and visability determinate
 * \details whereas AABB is computed by two point Min and Max, but if you need other corners you can use LBoundingBox::getCorner
 * \details Max corner is LCorner::right_top_front and min corner is LCorner::left_bottom_back
 * \enden
 *
 * \fa
 * \brief  AABB کلاس جعبه
 * \details که کاربرد آن برای تشخیص برخورد و تشخیص در دید بودن میباشد AABB کلاس جعبه
 * \details LBoundingBox::getCorner جعبه در اصل با نقطه بزرگترین و کوچکترین محاسبه میشود اما در صورت نیاز یه سایر گوشه ها میتوانید از تابع
 * \details میباشد LCorner::left_bottom_back و مقدار کمترین برابر LCorner::right_top_front استفاده کنید مقدار بیشترین برابر گوشه
 * \endfa
 */
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
    linline                 LBoundingBox(const LVector3& _min,const LVector3& _max);

    // Copy Constructor
    linline                 LBoundingBox(const LBoundingBox& _other);

    //! Add an Internal Point in this Bounding Box
    linline void            add(const LVector3& _p,bool _update=true);

    //! Check Bounding box is right or not  (checks mMax>=mMin) if was right returns true.
    linline bool            check()const;

    //! If BoundingBox parameters was not right will fix that
    linline void            fix();

    //! Get center point of bounding box
    linline LVector3        getCenter()const;

    //! Get one of corners
    linline const LVector3& getCorner(LCorner _t)const;

    //! Get all corners as pointer
    linline const LVector3* getCorners()const;

    //! Get Maximum point
    linline const LVector3& getMax()const;

    //! Get merged copy of this with another bounding box
    linline LBoundingBox    getMerged(const LBoundingBox& _other)const;

    //! Get Minimum point
    linline const LVector3& getMin()const;

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
    linline void            set(const LVector3& _min,const LVector3& _max);

    //!Set Maximum function
    linline void            setMax(const LVector3& _p);

    //! Set minimum function
    linline void            setMin(const LVector3& _p);

    //! Transform this box using transformatrion matrix
    linline void            transform(const LMatrix& _m);

    //! Update BoundingBox corners
    linline void            update();


    // Copy
    linline LBoundingBox&   operator=(const LBoundingBox& _other);

    // Compare
    linline bool            operator==(const LBoundingBox& _other)const;
    linline bool            operator!=(const LBoundingBox& _other)const;
protected:
    LVector3    mCorners[8];
    LVector3&   mMin;
    LVector3&   mMax;
};


/*!
 * \en
 * \brief LBoundingBox  Default constructor min= - Infinity and max= infinity other corners are 0
 * \enden
 *
 * \fa
 * \brief سازنده پیش فرض که در آن نقاط بیشترین برابر بی نهایت و کمترین برابر منفی بی نهایت و بقیه نقاط برابر صفر میباشد
 * \endfa
 */
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

/*!
* \en
* \brief Check is point inside box or not
* \param _p Point that need to be check
* \return If point was inside box returns true.
* \enden
*
* \fa
* \brief چک میکنه یک نقطه داخل جعبه قرار داره یا نه
* \param _p نقطه ای که باید چک بشه
* \return اگه نقطه داخل جعبه قرار داشت مقدار صحیح رو بر میگردونه
* \endfa
* \sa isContain(const LBoundingBox& _bb)const
*/
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

/*!
* \en
* \brief Check is all corner of another box is inside this box or not
* \param _bb box that need to be check
* \return If box was completly inside this box returns true.
* \enden
*
* \fa
* \brief چک میکنه آیا تمام گوشه های یه جعبه دیگه داخل این جعبه قرار داره یا نه
* \param _bb  جعبه ای که باید چک بشه
* \return اگه کل جعبه داخل این جعبه قرار داشت مقدار صحیح رو بر میگردونه
* \endfa
* \sa isContain(const LVector3& _p)const
*/
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

/*!
* \en
* \brief BoundingBox-BoundingBox Intersection Check
* \param _other BoundingBox that need to be check
* \return if BoundingBox intersects other BoundingBox returns true
* \enden
*
* \fa
* \brief تشخیص برخورد بین دوجعبه
* \param _other جعبه ای که باید چک بشه
* \return اگه جعبه با جعبه دیگری برخورد داشت مقدار صحیح رو برمیگردونه
* \endfa
*/
bool LBoundingBox::isIntersect(const LBoundingBox &_other) const
{
    // Adapted from http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
    if(mMax.x<_other.mMin.x)
        return false;
    if(mMin.x>_other.mMax.x)
        return false;
    if(mMax.y<_other.mMin.y)
        return false;
    if(mMin.y>_other.mMax.y)
        return false;
    if(mMax.z<_other.mMin.z)
        return false;
    if(mMin.z>_other.mMax.z)
        return false;
    return true;
}

/*!
 * \en
 * \brief Merge other box with this box
 * \enden
 *
 * \fa
 * \brief ترکیب کردن یه جعبه دیگه با این جعبه
 * \endfa
 * \sa getMerged(const LBoundingBox& _other)const
 */
void LBoundingBox::merge(const LBoundingBox &_other)
{
    add(_other.mMax);
    add(_other.mMin);
}

/*!
 * \en
 * \brief Add an Internal Point in this Bounding Box
 * \param _p Point that you want to add
 * \param _update if was true then when you call add . this will call update() after add. if you think update is not necessary , do not update
 * \enden
 *
 * \fa
 * \brief اضافه کردن نقطه ای به درون جعبه
 * \param _p نقطه ای میخواهید اضافه شه
 * \param _update فراخوانی خواهد شد update() اگر مقدار ان صحیح بود بلافاصله بعد اضافه کردن نقطه تابع
 *  \endfa
 * \sa update()
 */
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
    // if is not neccesary dont update
    if(_update&&(cM!=mMax||cm!=mMin))
        update();
}

/*!
 * \en
 * \brief Check Bounding box is right or not  (checks mMax>=mMin) if was right returns true.
 * \enden
 *
 * \fa
 * \brief چک میکنه پارامتر های جعبه درست هستن یا نه (چک میکنه که نقطه بیشترین از نقطه کمترین بیشتر باشه) اگه درست بود مقدار صحیح رو بر میگردونه
 * \endfa
 * \sa fix()
 */
bool LBoundingBox::check() const
{
    LVector3 s=getSizeVector();
    return (s.x>=0.0f&&s.y>=0.0f&&s.z>=0.0f);
}

/*!
 * \en
 * \brief If BoundingBox parameters was not right will fix that
 * \enden
 *
 * \fa
 * \brief اگه پارامتر های جعبه درست نباشن مقدارشون رو درست میکنه
 * \endfa
 *
 * \sa check()
 */
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

/*!
 * \en
 * \brief Get center point of bounding box
 * \enden
 *
 * \fa
 * \brief تهیه نقطه مرکز جعبه
 * \endfa
 */
LVector3 LBoundingBox::getCenter() const
{
    return (mMin+mMax)*0.5f;
}

/*!
 * \en
 * \brief Get one of corners
 * \warning Before call this check you AABB values is updated
 * \param _t corner address
 * \enden
 *
 * \fa
 * \brief تهیه کردن یکی از گوشه ها
 * \warning قبل از فراخوانی این تابع مطمئن شوید پارامتر ها به روز هستند
 * \param _t آدرس گوشه
 * \endfa
 * \sa update()
 */
const LVector3 &LBoundingBox::getCorner(LBoundingBox::LCorner _t) const
{
    // TODO : add index excption to _t
    return mCorners[_t];
}

/*!
 * \en
 * \brief Get all corners as pointer
 * \warning Before call this check you AABB values is updated
 * \enden
 *
 * \fa
 * \brief تهیه کردن تمام گوشه ها به عنوان اشاره گر
 * \warning قبل از فراخوانی این تابع مطمئن شوید پارامتر ها به روز هستند
 * \endfa
 * \sa update()
 */
const LVector3 *LBoundingBox::getCorners() const
{
    return mCorners;
}

/*!
 * \en
 * \brief Get Maximum point
 * \enden
 *
 * \fa
 * \brief  تهیه مکان بزرگترین نقطه
 * \endfa
 * \sa getMin()
 * \sa setMax
 */
const LVector3 &LBoundingBox::getMax() const
{
    return mMax;
}

/*!
 * \en
 * \brief  Get merged copy of this with another bounding box
 * \enden
 *
 * \fa
 * \brief  تهیه یک کپی ترکیب شده از همین جعبه با یک جعبه دیگر
 * \endfa
 * \sa merge()
 */
LBoundingBox LBoundingBox::getMerged(const LBoundingBox &_other)const
{
    LBoundingBox o=(*this);
    o.merge(_other);
    return o;
}

/*!
 * \en
 * \brief Get Minimum point
 * \enden
 *
 * \fa
 * \brief  تهیه مکان کوچکترین نقطه
 * \endfa
 * \sa getMax()
 * \sa setMin
 */
const LVector3 &LBoundingBox::getMin() const
{
    return mMin;
}

/*!
 * \en
 * \brief Get size vector . size vector is a vector from min to max
 * \enden
 *
 * \fa
 * \brief  تهیه کردن بردار اندازه. بردار اندازه برداری است که کوچکترین نقطه را به بزرگترین نقطه ی ممکن وصل میکند
 * \endfa
 */
LVector3 LBoundingBox::getSizeVector() const
{
    return mMax-mMin;
}

/*!
 * \en
 * \brief Get transformed copy of this
 * \param _m transformation matrix
 * \enden
 *
 * \fa
 * \brief  تهیه یک کپی جابه جا شده
 * \param _m ماتریس جابه جایی
 * \endfa
 * \sa transform(const LMatrix& _m)
 */
LBoundingBox LBoundingBox::getTransformed(const LMatrix &_m) const
{
    LBoundingBox o=(*this);
    o.transform(_m);
    return o;
}

/*!
* \en
* \brief Get volume of box
* \enden
*
* \fa
* \brief تهیه حجم جعبه
* \endfa
*/
f32 LBoundingBox::getVolume() const
{
    LVector3 s=getSizeVector();
    return s.x*s.y*s.z;
}

/*!
* \en
* \brief Set function from min and max
* \enden
*
* \fa
* \brief تابع ست با بزرگترین و کوچکترین نقطه
* \endfa
*/
void LBoundingBox::set(const LVector3 &_min, const LVector3 &_max)
{
    mMin=_min;
    mMax=_max;
    update();
}

/*!
* \en
* \brief Set minimum function
* \enden
*
* \fa
* \brief تابع تنظیم کوچکترین نقطه
* \endfa
* \sa getMin
* \sa setMax
*/
void LBoundingBox::setMin(const LVector3 &_p)
{
    mMin=_p;
    update();
}

/*!
* \en
* \brief Set Maximum function
* \enden
*
* \fa
* \brief تابع تنظیم کوچکترین نقطه
* \endfa
* \sa getMax
* \sa setMin
*/
void LBoundingBox::setMax(const LVector3 &_p)
{
    mMax=_p;
    update();
}

/*!
 * \en
 * \brief Transform this box using transformatrion matrix
 * \param _m transformation matrix
 * \enden
 *
 * \fa
 * \brief  جابه جا کردن این جعبه
 * \param _m ماتریس جابه جایی
 * \endfa
 * \sa getTransformed
 */
void LBoundingBox::transform(const LMatrix& _m)
{
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
}

/*!
 * \en
 * \brief Update BoundingBox corners . only min and max will compute if you call add(...,false), if you need all corners you need first update corners
 * \enden
 *
 * \fa
 * \brief  رو فراخوانی کنید تنها دو گوشه کوچکترین و بزرگترین محاسبه خواهند شد. اگر نیاز به تمام گوشه ها دارید اول باید جعبه را بروزرسانی کنید add(...,false)  بروز رسانی مکان گوشه ها اگه تابع
 * \endfa
 * \sa add
 */
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
