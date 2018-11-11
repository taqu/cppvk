#ifndef INC_LAPP_H_
#define INC_LAPP_H_
/**
@file lapp.h
@author t-sakai
@date 2018/10/29 create
*/
#ifdef _DEBUG
#   include <cassert>
#endif
#include <cstdint>
#include <utility>
#include <type_traits>

#ifdef _MSC_VER
#   include <Windows.h>
#else
#   include <cstdlib>
#endif

#include "lgfx.h"

#ifdef __cplusplus
#   if 201103L<=__cplusplus || 1900<=_MSC_VER
#       define LAPP_CPP11 1
#   endif
#   ifdef LAPP_CPP11
#       define LAPP_NULL nullptr
#   else
#       define LAPP_NULL 0
#   endif
#else //__cplusplus
#   define LAPP_NULL (void*)0
#endif //__cplusplus

//--- Assertion
//--------------------------------------------------------------
#ifdef _DEBUG
#   define LAPP_ASSERT(exp) assert(exp)
#else
#   define LAPP_ASSERT(exp)
#endif

//--- Allocation
//--------------------------------------------------------------
#if defined(_DEBUG)
#    define LAPP_NEW     new
#    define LAPP_NEW_RAW new
#    define LAPP_PLACEMENT_NEW(ptr) new(ptr)
#    define LAPP_DELETE(ptr)        delete (ptr); (ptr)=NULL
#    define LAPP_DELETE_RAW(ptr)    delete (ptr)

#    define LAPP_DELETE_ARRAY(ptr)  delete[] (ptr); (ptr)=NULL

#    define LAPP_MALLOC(size)  malloc(size)
#    define LAPP_FREE(ptr)     free(ptr); (ptr)=NULL
#    define LAPP_FREE_RAW(ptr) free(ptr)
#    define LAPP_REALLOC(ptr, size) realloc(ptr, size)

#else //defined(_DEBUG)
#    define LAPP_NEW     new
#    define LAPP_NEW_RAW new
#    define LAPP_PLACEMENT_NEW(ptr) new(ptr)
#    define LAPP_DELETE(ptr)        delete ptr; (ptr)=NULL
#    define LAPP_DELETE_RAW(ptr)    delete (ptr)

#    define LAPP_DELETE_ARRAY(ptr)  delete[] (ptr); (ptr)=NULL

#    define LAPP_MALLOC(size)  malloc(size)
#    define LAPP_FREE(ptr)     free(ptr); (ptr)=NULL
#    define LAPP_FREE_RAW(ptr) free(ptr)
#    define LAPP_REALLOC(ptr, size) realloc(ptr, size)
#endif

#define LAPP_NON_COPYABLE(name)\
    name(const name&) = delete;\
    name(name&&) = delete;\
    name& operator=(const name&) = delete;\
    name& operator=(name&&) = delete

namespace lapp
{
#ifndef LAPP_TYPES
#define LAPP_TYPES
    typedef char Char;
    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef float f32;
    typedef double f64;

    typedef std::size_t size_t;
    typedef std::intptr_t intptr_t;
    typedef std::uintptr_t uintptr_t;
    typedef std::ptrdiff_t ptrdiff_t;

    typedef s32 BOOL;
#endif

    //--------------------------------------------------------------
#define LAPP_TRUE  (1)
#define LAPP_FALSE (0)

    using std::move;
    using std::true_type;
    using std::false_type;
    using std::is_trivially_copyable;

    template<class T>
    inline T maximum(const T& x0, const T& x1)
    {
        return (x0<x1)? x1 : x0;
    }

    template<class T>
    inline T minimum(const T& x0, const T& x1)
    {
        return (x0<x1)? x0 : x1;
    }

    template<class T>
    T clamp(const T& x, const T& minx, const T& maxx)
    {
        if(x<minx){
            return minx;
        } else if(maxx<x){
            return maxx;
        } else{
            return x;
        }
    }

    template<class T>
    inline void swap(T& l, T& r)
    {
        T tmp(lgfx::move(l));
        l = lgfx::move(r);
        r = lgfx::move(tmp);
    }

    struct InputParam
    {
        HWND hWnd_;
        s32 maxGamePads_;
        bool mouse_;
        bool keyboard_;
    };

    struct InitParam
    {
        InitParam()
            :maxGamePads_(1)
            ,mouse_(true)
            ,keyboard_(true)
        {}

        lgfx::Window::InitParam windowParam_;
        lgfx::GraphicsInitParam graphicsParam_;

        s32 maxGamePads_;
        bool mouse_;
        bool keyboard_;
    };

#ifdef _DEBUG
    void printDebug(const Char* format, ...);
#define DEBUG_PRINT(format, ...)  printDebug(format, __VA_ARGS__)

#else
#define DEBUG_PRINT(format, ...) 
#endif


#define LAPP_DEFINE_MATH
#ifdef LAPP_DEFINE_MATH
    struct Vector3
    {
        f32 x_;
        f32 y_;
        f32 z_;
    };
    static_assert(std::is_trivially_copyable<Vector3>::value, "Vector3 must be trivially copyable");

    struct Vector4
    {
        f32 x_;
        f32 y_;
        f32 z_;
        f32 w_;
    };
    static_assert(std::is_trivially_copyable<Vector4>::value, "Vector4 must be trivially copyable");
#endif //LAPP_DEFINE_MATH
}

#endif //INC_LAPP_H_
