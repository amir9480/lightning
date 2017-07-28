#ifndef LCONFIG_H
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

////////////////////////////////////////////////////////////////////////////////////////////////////
#define LGFX_NONE 0
#define LGFX_D3D9 1

#define LGFX LGFX_D3D9


/*!
 * \def LIGHTING_USING_NAMESPACE
 * \en
 * \brief If was true then all classes and functions will have Lightning namespace
 * \enden
 *
 */

/*!
 * \def LTARGET
 * \en
 * \brief what is build target. LTARGET_DEBUG is for when compile is for debug and LTARGET_RELEASE when build is for release
 * \enden
 *
 */

/*!
 * \def LCOMPILE_DYNAMIC
 * \en
 * \brief if this was LCOMPILE_DYNAMIC project will be a dynamic library and when was LCOMPILE_STATIC project is a static libarary
 * \enden
 *
 */



#endif // LCONFIG_H
