#ifndef INC_LGFX_H_
#define INC_LGFX_H_
/**
@file lgfx.h
@author t-sakai
@date 2018/09/19 create

//--- Usage
//-----------------------------------------------------------
# For using Vulkan
#define LGFX_VULKAN

Put '#define LGFX_IMPLEMENTATION' before including this file to create the implementation.
*/
#define LGFX_IMPLEMENTATION
#ifdef _DEBUG
#   include <cassert>
#endif
#include <cstdint>
#include <utility>

#ifdef _MSC_VER
#   include <Windows.h>
#else
#   include <cstdlib>
#endif

#ifdef __cplusplus
#   if 201103L<=__cplusplus || 1900<=_MSC_VER
#       define LGFX_CPP11 1
#   endif
#   ifdef LGFX_CPP11
#       define LGFX_NULL nullptr
#   else
#       define LGFX_NULL 0
#   endif
#else //__cplusplus
#   define LGFX_NULL (void*)0
#endif //__cplusplus

//--- Assertion
//--------------------------------------------------------------
#ifdef _DEBUG
#   define LGFX_ASSERT(exp) assert(exp)
#else
#   define LGFX_ASSERT(exp)
#endif


//--- Allocation
//--------------------------------------------------------------
#if defined(_DEBUG)
#    define LGFX_NEW     new
#    define LGFX_NEW_RAW new
#    define LGFX_PLACEMENT_NEW(ptr) new(ptr)
#    define LGFX_DELETE(ptr)        delete (ptr); (ptr)=NULL
#    define LGFX_DELETE_RAW(ptr)    delete (ptr)

#    define LGFX_DELETE_ARRAY(ptr)  delete[] (ptr); (ptr)=NULL

#    define LGFX_MALLOC(size)  malloc(size, __FILE__, __LINE__)
#    define LGFX_FREE(ptr)     free(ptr); (ptr)=NULL
#    define LGFX_FREE_RAW(ptr) free(ptr)
#    define LGFX_REALLOC(ptr, size) realloc(ptr, size)

#else //defined(_DEBUG)
#    define LGFX_NEW     new
#    define LGFX_NEW_RAW new
#    define LGFX_PLACEMENT_NEW(ptr) new(ptr)
#    define LGFX_DELETE(ptr)        delete ptr; (ptr)=NULL
#    define LGFX_DELETE_RAW(ptr)    delete (ptr)

#    define LGFX_DELETE_ARRAY(ptr)  delete[] (ptr); (ptr)=NULL

#    define LGFX_MALLOC(size)  malloc(size)
#    define LGFX_FREE(ptr)     free(ptr); (ptr)=NULL
#    define LGFX_FREE_RAW(ptr) free(ptr)
#    define LGFX_REALLOC(ptr, size) realloc(ptr, size)
#endif

#ifdef LGFX_USE_XLIB
#   define VK_USE_PLATFORM_XLIB_KHR
#endif

#ifdef LGFX_USE_XCB
#   define VK_USE_PLATFORM_XCB_KHR
#endif

#ifdef LGFX_USE_WAYLAND
#   define VK_USE_PLATFORM_WAYLAND_KHR
#endif

#ifdef LGFX_USE_MIR
#   define VK_USE_PLATFORM_MIR_KHR
#endif

#ifdef LGFX_USE_ANDROID
#   define VK_USE_PLATFORM_ANDROID_KHR
#endif

#ifdef LGFX_USE_WIN32
#   define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef LGFX_VULKAN
#   define VK_NO_PROTOTYPES 1
#   include "vulkan.h"

#   ifdef _MSC_VER

#       define LGFX_DLHANDLE HMODULE
#       define LGFX_DLOPEN(path) LoadLibrary((path))
#       define LGFX_DLSYM(handle, name) GetProcAddress((handle), (name))
#       define LGFX_DLCLOSE(handle) FreeLibrary((handle))

#       define LGFX_VULKANLIB ("vulkan-1.dll")

#   else

#       define LGFX_DLHANDLE void*
#       define LGFX_DLOPEN(path) dlopen((path), RTLD_NOW)
#       define LGFX_DLSYM(handle, name) dlsym((handle), (name))
#       define LGFX_DLCLOSE(handle) dlclose((handle))

#       define LGFX_VULKANLIB ("libvulkan.so.1")

#   endif
#endif //LGFX_VULKAN

#include "Window.h"
#include "lgfx_config.h"

namespace lgfx
{
#ifndef LGFX_TYPES
#define LGFX_TYPES
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
#endif

    //--------------------------------------------------------------
    using std::move;
    using std::true_type;
    using std::false_type;

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
        }else if(maxx<x){
            return maxx;
        }else{
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
}

#include "Array.inc"

namespace lgfx
{
    //--------------------------------------------------------------
    enum QueueType : u32
    {
        QueueType_Present =0,
        QueueType_Graphics,
        QueueType_Compute,
        QueueType_Transfer,
        QueueType_SparceBinding,
        QueueType_Max,
        QueueType_Invalid = 0xFFFFFFFFU,
    };

#ifdef LGFX_VULKAN
    enum PresentMode
    {
        PresentMode_Immediate   = VK_PRESENT_MODE_IMMEDIATE_KHR,
        PresentMode_MailBox     = VK_PRESENT_MODE_MAILBOX_KHR,
        PresentMode_FIFO        = VK_PRESENT_MODE_FIFO_KHR,
        PresentMode_FIFORelaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
    };
#endif

    //--------------------------------------------------------------
    class System;

    //--------------------------------------------------------------
    struct InstanceCreateInfo
    {
        //Application info
        const Char* applicationName_;
        u32 applicationVersion_;
        const Char* engineName_;
        u32 engineVersion_;
        u32 apiVersion_;

        //Instance info
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[LGFX_MAX_LAYERS];
        const Char* layerName_;
    };

    //--------------------------------------------------------------
    struct DeviceCreateInfo
    {
        s32 index_;
        bool requestQueueTypes_[QueueType_Max]; //

        //
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[LGFX_MAX_LAYERS];
        const Char* layerName_;
    };

    //--------------------------------------------------------------
    struct SurfaceCreateInfo
    {
#ifdef LGFX_USE_XLIB
        VkXlibSurfaceCreateFlagsKHR flags_;
        Display* display_;
        Window window_;
#endif

#ifdef LGFX_USE_XCB
        VkXcbSurfaceCreateFlagsKHR flags_;
        xcb_connection_t* connection_;
        xcb_window_t window_;
#endif

#ifdef LGFX_USE_WAYLAND
        VkWaylandSurfaceCreateFlagsKHR flags_;
        wl_display* display_;
        wl_surface* surface_;
#endif

#ifdef LGFX_USE_MIR
        VkMirSurfaceCreateFlagsKHR flags_;
        MirConnection* connection_;
        MirSurface* surface_;
#endif

#ifdef LGFX_USE_ANDROID
        VkAndroidSurfaceCreateFlagsKHR flags_;
        ANativeWindow* window_;
#endif

#ifdef LGFX_USE_WIN32
        VkWin32SurfaceCreateFlagsKHR flags_;
        HINSTANCE hInstance_;
        HWND hWnd_;
#endif
    };

    //--------------------------------------------------------------
    struct SwapchainCreateInfo
    {
        bool supportHDR_;
        u32 swapchainCount_;
        PresentMode presentMode_;
        u32 width_;
        u32 height_;
    };

    //--------------------------------------------------------------
    //---
    //--- Builder
    //---
    //--------------------------------------------------------------
    template<class TImpl>
    class Builder : public TImpl
    {
    public:
        Builder();
        ~Builder();

        bool build(System& system)
        {
            return system.initialize(*this);
        }

        InstanceCreateInfo instanceCreateInfo_;
        DeviceCreateInfo deviceCreateInfo_;
        SurfaceCreateInfo surfaceCreateInfo_;
        SwapchainCreateInfo swapchainCreateInfo_;

        const VkAllocationCallbacks* allocator_;
    };

    template<class TImpl>
    Builder<TImpl>::Builder()
        :allocator_(LGFX_NULL)
    {}

    template<class TImpl>
    Builder<TImpl>::~Builder()
    {}

    template<class TImpl>
    class SwapchainBuilder : public TImpl
    {
    public:
        SwapchainBuilder();
        ~SwapchainBuilder();
    };

    template<class TImpl>
    SwapchainBuilder<TImpl>::SwapchainBuilder()
    {}

    template<class TImpl>
    SwapchainBuilder<TImpl>::~SwapchainBuilder()
    {}
}

#ifdef LGFX_VULKAN
#include "lgfx_vulkan.h"
#endif

#endif //INC_LGFX_H_

#ifdef LGFX_IMPLEMENTATION
#ifndef LGFX_IMPLEMENTATION_DONE
#define LGFX_IMPLEMENTATION_DONE
/**
@file lgfx.cpp
@author t-sakai
@date 2018/09/19 create
*/

#define LGFX_WINDOW_IMPLEMENTATION
#include "Window.h"

#ifdef LGFX_VULKAN
#define LGFX_VULKAN_IMPLEMENTATION
#include "lgfx_vulkan.h"
#endif

#endif //LGFX_IMPLEMENTATION_DONE
#endif //LGFX_IMPLEMENTATION
