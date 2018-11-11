#ifndef INC_LGFX_H_
#define INC_LGFX_H_
/**
@file lgfx.h
@author t-sakai
@date 2018/09/19 create

//--- Usage
//-----------------------------------------------------------
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

#    define LGFX_MALLOC(size)  malloc(size)
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

#ifdef LGFX_DX12
#include <d3d12.h>
#include <dxgi1_6.h>
#endif

#ifdef LGFX_VULKAN
#   ifdef LGFX_USE_XLIB
#       define VK_USE_PLATFORM_XLIB_KHR
#   endif

#   ifdef LGFX_USE_XCB
#       define VK_USE_PLATFORM_XCB_KHR
#   endif

#   ifdef LGFX_USE_WAYLAND
#       define VK_USE_PLATFORM_WAYLAND_KHR
#   endif

#   ifdef LGFX_USE_MIR
#       define VK_USE_PLATFORM_MIR_KHR
#   endif

#   ifdef LGFX_USE_ANDROID
#       define VK_USE_PLATFORM_ANDROID_KHR
#   endif

#   ifdef LGFX_USE_WIN32
#       define VK_USE_PLATFORM_WIN32_KHR
#   endif

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

    typedef std::size_t size_t;
    typedef std::intptr_t intptr_t;
    typedef std::ptrdiff_t ptrdiff_t;

    typedef s32 BOOL;
#endif

    //--------------------------------------------------------------
#define LGFX_TRUE  (1)
#define LGFX_FALSE (0)

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

    constexpr f32 DefaultMinDepth = 0.0f;
    constexpr f32 DefaultMaxDepth = 1.0f;

    //--------------------------------------------------------------
    //---
    //--- Viewport
    //---
    //--------------------------------------------------------------
    struct Viewport
    {
        f32 x_;
        f32 y_;
        f32 width_;
        f32 height_;
        f32 minDepth_;
        f32 maxDepth_;
    };

    //--------------------------------------------------------------
    //---
    //--- RectS32
    //---
    //--------------------------------------------------------------
    struct RectS32
    {
        s32 left_;
        s32 top_;
        s32 right_;
        s32 bottom_;

        s32 width() const{ return right_-left_;}
        s32 height() const{ return bottom_-top_;}
    };

    //--------------------------------------------------------------
#ifdef LGFX_VULKAN
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

    enum PresentMode
    {
        PresentMode_Immediate   = VK_PRESENT_MODE_IMMEDIATE_KHR,
        PresentMode_MailBox     = VK_PRESENT_MODE_MAILBOX_KHR,
        PresentMode_FIFO        = VK_PRESENT_MODE_FIFO_KHR,
        PresentMode_FIFORelaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
    };

    //--------------------------------------------------------------
    //---
    //--- Handle
    //---
    //--------------------------------------------------------------
    struct Handle
    {
    public:
        inline static Handle create(s32 handle){ return {handle};}
        inline static Handle invalid(){ return {-1};}

        static Handle allocate(s32 device, void* resource);
        static void release(Handle& handle);

        template<class T>
        operator const T() const;
        template<class T>
        operator T();

        inline bool valid() const;
        inline s32 handle() const;

        s32 count() const;
        s32 device() const;

        /**
        @return count after increment
        */
        s32 inc();

        /**
        @return count after decrement
        */
        s32 dec();

        void swap(Handle& rhs);

        s32 handle_;
    };

    template<class T>
    Handle::operator const T() const
    {
        return reinterpret_cast<const T>(ResourceTable::instance()[handle_].resource_);
    }

    template<class T>
    Handle::operator T()
    {
        return reinterpret_cast<T>(ResourceTable::instance()[handle_].resource_);
    }

    inline bool Handle::valid() const
    {
        return 0<=handle_;
    }

    inline s32 Handle::handle() const
    {
        return handle_;
    }

    //--------------------------------------------------------------
    //---
    //--- ResourceTable
    //---
    //--------------------------------------------------------------
    class ResourceTable
    {
    public:
        static const s32 ExpandSize = 1024;

        struct ReferenceCounted
        {
            void* resource_;
            s32 count_;
            s32 device_;
        };

        static void initialize();
        static void terminate();
        static inline ResourceTable& instance();

        inline const ReferenceCounted& operator[](s32 index) const;
        inline ReferenceCounted& operator[](s32 index);

        Handle pop(s32 device, void* resource);
        void push(Handle handle);
    private:
        ResourceTable(const ResourceTable&) = delete;
        ResourceTable(ResourceTable&&) = delete;
        ResourceTable& operator=(const ResourceTable&) = delete;
        ResourceTable& operator=(ResourceTable&&) = delete;

        static ResourceTable instance_;

        ResourceTable();
        ~ResourceTable();

        void destroy();

        union Entry
        {
        public:
            ReferenceCounted refCounted_;
            s32 next_;
        };

        s32 capacity_;
        s32 size_;
        s32 freeList_;
        Entry* entries_;
    };

    inline ResourceTable& ResourceTable::instance()
    {
        return instance_;
    }

    inline const ResourceTable::ReferenceCounted& ResourceTable::operator[](s32 index) const
    {
        LGFX_ASSERT(0<=index && index<size_);
        return entries_[index].refCounted_;
    }

    inline ResourceTable::ReferenceCounted& ResourceTable::operator[](s32 index)
    {
        LGFX_ASSERT(0<=index && index<size_);
        return entries_[index].refCounted_;
    }

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
    class Builder
    {
    public:
        inline Builder();
        inline virtual ~Builder();

        virtual bool build(System& system) =0;

        InstanceCreateInfo instanceCreateInfo_;
        DeviceCreateInfo deviceCreateInfo_;
        SurfaceCreateInfo surfaceCreateInfo_;
        SwapchainCreateInfo swapchainCreateInfo_;
    };

    inline Builder::Builder()
    {}

    inline Builder::~Builder()
    {}
#endif
}

#ifdef LGFX_VULKAN
#include "lgfx_vulkan.h"
#endif

#ifdef LGFX_DX12
#include "lgfx_dx12.h"
#endif

#endif //INC_LGFX_H_
