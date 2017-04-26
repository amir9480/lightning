﻿#ifndef LCONFIG_H
#define LCONFIG_H

//! Name macro and version
#define LIGHTNING "Lightning"
#define LIGHTNING_VERSION "0.0.1"
#define LVERSION 1

//! Lightning compile type
#define LTARGET_DEBUG   1
#define LTARGET_RELEASE 2

//! How to make Lightning Library static or dynamic
#define LCOMPILE_STATIC     1
#define LCOMPILE_DYNAMIC    2

///////////////////////////////////////////////////////////////////////////////////////

//! if Namespace is requied set this to 1
#define LIGHTING_USING_NAMESPACE 1

//! Lightning compile type LTARGET_DEBUG or LTARGET_RELEASE
#define LTARGET LTARGET_DEBUG

//! How to make Lightning Library LCOMPILE_STATIC or LCOMPILE_DYNAMIC
#define LCOMPILE_TYPE LCOMPILE_DYNAMIC

///////////////////////////////////////////////////////////////////////////////////////

//! where save Lightning logs ?
#define LLOG_FILE "lightninglogs.txt"

//! where save Lightning memory logs (for memory leak detector only)?
#define LMLOG_FILE "lightningmemlogs.txt"

/*!
 * \def LIGHTING_USING_NAMESPACE
 * \en
 * \brief If was true then all classes and functions will have Lightning namespace
 * \enden
 *
 * \fa
 * \brief  خواهند داشت Lightning اگه مقدار صحیح جلوش باشه در انصورت تمام کلاس ها و توابع فضای نام
 * \endfa
 */

/*!
 * \def LTARGET
 * \en
 * \brief what is build target. LTARGET_DEBUG is for when compile is for debug and LTARGET_RELEASE when build is for release
 * \enden
 *
 * \fa
 * \brief بود هدف انتشار برنامه هست LTARGET_RELEASE بود یعنی هدف دیباگ کردن هستن ولی اگه  LTARGET_DEBUG هدف ساخت پروژه برای انجام چه کاری هست. اگه
 * \endfa
 */

/*!
 * \def LCOMPILE_DYNAMIC
 * \en
 * \brief if this was LCOMPILE_DYNAMIC project will be a dynamic library and when was LCOMPILE_STATIC project is a static libarary
 * \enden
 *
 * \fa
 * \brief بود یعنی پروژه به صورت کتابخانه استاتیک هست LCOMPILE_STATIC بود یعنی پروژه به صورت کتاب خانه دینامیک کامپایل بشه و اگه  LCOMPILE_DYNAMIC اگه مقدار این برابر
 * \endfa
 */



#endif // LCONFIG_H
