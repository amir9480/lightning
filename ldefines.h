#ifndef LDEFINES_H
#define LDEFINES_H

//! if Namespace is requied set this to 1
#define LIGHTING_USING_NAMESPACE 0

//! set Lightning namespace Dynamically
#if LIGHTING_USING_NAMESPACE
#define LNAMESPACE_BEGIN namespace Lightning{
#define LNAMESPACE_END   }
#else
#define LNAMESPACE_BEGIN
#define LNAMESPACE_END
#endif

//! Lightning compile type
#define LTARGET_DEBUG 1
#define LTARGET_RELEASE 2

//! Lightning compile type
#define LTARGET LTARGET_DEBUG

//! How to make Lightning Library static or dynamic
#define LCOMPILE_STATIC 1
#define LCOMPILE_DYNAMIC 2
//! How to make Lightning Library static or dynamic
#define LCOMPILE_TYPE LCOMPILE_DYNAMIC


#define LHEADER_USAGE_IMPORT 1
#define LHEADER_USAGE_EXPORT 2
//! If you tring to compile set this to HEADER_USAGE_COMPILING otherwise set to HEADER_USAGE_INTERFACE
#define LHEADER_USAGE_TYPE LHEADER_USAGE_EXPORT

//! OS is windows
#define LOS_WINDOWS 1

//! Check Operation System
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
    //! Current OS is windows
    #define LOS LOS_WINDOWS
#else
    #error Lightning compile time error: Undefined OS
#endif

//! Compiler is MSVC
#define LCOMPILER_MSVC 1
//! Compiler is GCC
#define LCOMPILER_GCC 2
//! Compiler is CLANG
#define LCOMPILER_CLANG 3
//! Compiler is MINGW
#define LCOMPILER_MINGW 4

#if defined(__MINGW32__)
    //! Compiler is MinGW
    #define LCOMPILER LCOMPILER_MINGW
#elif  defined(__GNUC__) || defined(__GNUG__)
    //! Compiler is GCC
    #define LCOMPILER LCOMPILER_GCC
#elif defined(__MSVCRT__)
    //! Compiler is MSVC
    #define LCOMPILE LCOMPILER_MSVC
#else
    #error Lightning compile time error:Undefined Compiler
#endif

#if COMPILE_TYPE == COMPILE_DYNAMIC && LOS == LOS_WINDOWS
    #define LAPI __declspec(dllexport)
#else
    #define LAPI
#endif


//! Set inline to always_inline
#if LCOMPILER==LCOMPILER_MINGW || LCOMPILER == LCOMPILER_GCC
    //! Causes inline functions always be inline
    #define linline inline __attribute__((always_inline))
#else
    #define linline inline
#endif

LNAMESPACE_BEGIN

typedef char                     i8  ;
typedef short int                i16 ;
typedef int                      i32 ;
typedef long long int            i64 ,slong;

typedef unsigned char            u8  ;
typedef unsigned short int       u16 ;
typedef unsigned int             u32 ;
typedef unsigned long long int   u64 ,ulong;

typedef float                    f32 ;
typedef double                   f64 ;
typedef long double              f96 ;

LNAMESPACE_END
#endif // LDEFINES_H
