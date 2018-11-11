/**
@file Instance.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(LGFX_NULL)
        , presentationSurface_(LGFX_NULL)
#define LGFX_VK_EXT_INSTANCE_FUNCTION(name) ,name(LGFX_NULL)
#include "VkFunctions.inc"
    {
    }

    Instance::~Instance()
    {
#define LGFX_VK_EXT_INSTANCE_FUNCTION(name) name = LGFX_NULL;
#include "VkFunctions.inc"
    }

    LGFX_RESULT Instance::create(
        Instance& instance,
        const VkInstanceCreateInfo& instanceCreateInfo,
        const SurfaceCreateInfo& surfaceCreateInfo)
    {
        if(instance.valid()){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        VkResult result;
        result = vkCreateInstance(&instanceCreateInfo, allocator, &instance.instance_);
        if(VK_SUCCESS != result){
            return LGFX_VK_TO_RESULT(result);
        }

        instance.initialize();

        result = instance.createPresentationSurface(surfaceCreateInfo);
        if(VK_SUCCESS != result){
            vkDestroyInstance(instance.instance_, allocator);
            instance.instance_ = LGFX_NULL;
            return LGFX_VK_TO_RESULT(result);
        }
        return LGFX_SUCCESS;
    }

    void Instance::destroy(Instance& instance)
    {
        if(!instance.valid()){
            return;
        }

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();
        if(LGFX_NULL != instance.presentationSurface_){
            instance.vkDestroySurfaceKHR(instance, instance.presentationSurface_, allocator);
            instance.presentationSurface_ = LGFX_NULL;
        }

        vkDestroyInstance(instance, allocator);
        instance.instance_ = LGFX_NULL;
    }

    void Instance::swap(Instance& rhs)
    {
        lgfx::swap(instance_, rhs.instance_);
        lgfx::swap(presentationSurface_, rhs.presentationSurface_);
    }

    u32 Instance::enumeratePhysicalDevices(u32 maxPhysicalDevices, PhysicalDevice* devices) const
    {
        LGFX_ASSERT(maxPhysicalDevices<=LGFX_MAX_PHYSICAL_DEVICES);
        LGFX_ASSERT(LGFX_NULL != devices);

        u32 deviceCount = maxPhysicalDevices;
        VkPhysicalDevice tmp[LGFX_MAX_PHYSICAL_DEVICES];
        if(VK_SUCCESS != vkEnumeratePhysicalDevices(instance_, &deviceCount, tmp)){
            return 0;
        }
        for(u32 i=0; i<deviceCount; ++i){
            devices[i] = PhysicalDevice(tmp[i]);
        }
        return deviceCount;
    }

    VkResult Instance::createPresentationSurface(const SurfaceCreateInfo& createInfo)
    {
        if(LGFX_NULL != presentationSurface_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

#ifdef LGFX_USE_XLIB
        VkXlibSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.display_,
            createInfo.window_,
        };
        VkResult result = vkCreateXlibSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef LGFX_USE_XCB
        VkXcbSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.connection_,
            createInfo.window_,
        };
        VkResult result = vkCreateXcbSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef LGFX_USE_WAYLAND
        VkWaylandSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.display_,
            createInfo.surface_,
        };
        VkResult result = vkCreateWaylandSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef LGFX_USE_MIR
        VkMirSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.connection_,
            createInfo.surface_,
        };
        VkResult result = vkCreateMirSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif

#ifdef LGFX_USE_ANDROID
        VkAndroidSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.window_,
        };
        VkResult result = vkCreateAndroidSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif

#ifdef LGFX_USE_WIN32
        VkWin32SurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
            LGFX_NULL,
            createInfo.flags_,
            createInfo.hInstance_,
            createInfo.hWnd_,
        };
        VkResult result = vkCreateWin32SurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
        return result;
    }

    void Instance::initialize()
    {
        LGFX_ASSERT(LGFX_NULL != instance_);

#define LGFX_VK_EXT_INSTANCE_FUNCTION(name) if(LGFX_NULL == name) name = (PFN_ ## name)vkGetInstanceProcAddr(instance_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_WARN("Warning: cannot get instance function %s via vkGetInstanceProcAddr\n", #name);\
    }
#include "VkFunctions.inc"

    }

    bool Instance::getPhysicalDevicePresentationSurfaceSupport(PhysicalDevice physicalDevice, u32 queueFamilyIndex)
    {
        VkBool32 support = VK_FALSE;
        if(VK_SUCCESS != vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, presentationSurface_, &support)){
            support = VK_FALSE;
        }
        return (VK_TRUE == support);
    }
}
