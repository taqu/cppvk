#ifndef INC_VK_H_
#define INC_VK_H_
/**
@file vk.h
@author t-sakai
@date 2017/10/15 create
*/
#ifdef _DEBUG
#include <cassert>
#endif

#ifdef __cplusplus
#   if 201103L<=_cplusplus || 1900<=_MSC_VER
#       define VLK_CPP11 1
#   endif
#endif

#ifdef __cplusplus
#   ifdef VLK_CPP11
#       define VLK_NULL nullptr
#   else
#       define VLK_NULL 0
#   endif
#else
#   define VLK_NULL (void*)0
#endif

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif

#ifdef _WIN32
#define VLK_DLHANDLE HMODULE
#define VLK_DLOPEN(path) LoadLibrary((path))
#define VLK_DLSYM(handle, name) GetProcAddress((handle), (name))
#define VLK_DLCLOSE(handle) FreeLibrary((handle))

#define VLK_VULKANLIB ("vulkan-1.dll")

#else
#define VLK_DLHANDLE void*
#define VLK_DLOPEN(path) dlopen((path), RTLD_NOW)
#define VLK_DLSYM(handle, name) dlsym((handle), (name))
#define VLK_DLCLOSE(handle) dlclose((handle))

#define VLK_VULKANLIB ("libvulkan.so.1")

#endif

#include "vulkan.h"

namespace vk
{
#define VLK_REPORT_ERROR 1
#define VLK_REPORT_WARNING 1

#ifdef _DEBUG
#define VLK_ASSERT(exp) assert(exp)
#else
#define VLK_ASSERT(exp)
#endif

#ifdef _MSC_VER
    typedef __int32 s32;
    typedef unsigned __int32 u32;

#else
    typedef int32_t s32;
    typedef uint32_t u32;
#endif
    template<class T>
    inline const T& maximum(const T& x0, const T& x1)
    {
        return (x0<x1)? x1 : x0;
    }

    template<class T>
    inline const T& minimum(const T& x0, const T& x1)
    {
        return (x0<x1)? x0 : x1;
    }

    //-------------------------------------------------------------------------------
#define VLK_EXPORTED_FUNCTION(name) extern PFN_ ## name name ## _;
#define VLK_INSTANCE_FUNCTION(name) extern PFN_ ## name name ## _;
#define VLK_DEVICE_FUNCTION(name) extern PFN_ ## name name ## _;
#define VLK_PHYSICALDEVICE_FUNCTION(name) extern PFN_ ## name name ## _;

#define VLK_EXT_EXPORTED_FUNCTION(name) extern PFN_ ## name name ## _;
#include "VkFunctions.inc"

    //--------------------------------------------------------------
    class Instance;
    class Device;

    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    class Lib
    {
    public:
        Lib();
        ~Lib();

        inline bool valid() const;

        VkResult initialize();
        void terminate();

        VkResult createInstance(Instance& instance, const VkInstanceCreateInfo* createInfo, const VkAllocationCallbacks* allocator);
    private:
        Lib(const Lib&) = delete;
        Lib& operator=(const Lib&) = delete;

        VLK_DLHANDLE handle_;
    };

    inline bool Lib::valid() const
    {
        return VLK_NULL != handle_;
    }

    //--------------------------------------------------------------
    //---
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------
    /**
    Pysical device class wraps VkPhysicalDevice.
    */
    class PhysicalDevice
    {
    public:
        /**
        @brief
        */
        inline void getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* features);

        /**
        @brief
        */
        inline void getPhysicalDeviceProperties(VkPhysicalDeviceProperties* properties);

        /**
        @brief
        */
        inline void getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties* formatProperties);

        /**
        @brief
        @return
        */
        inline VkResult enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties);

        /**
        @brief
        @return
        */
        inline VkResult getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* imageFormatProperties);

        /**
        @brief
        */
        inline void getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties);

        /**
        @brief
        */
        inline void getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* memoryProperties);

        /**
        @brief
        */
        inline void getPhysicalDeviceQueueFamilyProperties(u32* queueFamilyPropertyCount, VkQueueFamilyProperties* queueFamilyProperties);

        /**
        @brief
        @return
        */
        inline VkResult enumerateDeviceExtensionProperties(const char* layerName, u32* propertyCount, VkExtensionProperties* properties);


        VkResult createDevice(Device& device, const VkDeviceCreateInfo* createInfo, const VkAllocationCallbacks* allocator);

    private:
        friend class Instance;

        VkPhysicalDevice device_;
    };

    inline void PhysicalDevice::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* features)
    {
        vkGetPhysicalDeviceFeatures_(device_, features);
    }

    inline void PhysicalDevice::getPhysicalDeviceProperties(VkPhysicalDeviceProperties* properties)
    {
        vkGetPhysicalDeviceProperties_(device_, properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties* formatProperties)
    {
        vkGetPhysicalDeviceFormatProperties_(device_, format, formatProperties);
    }

    inline VkResult PhysicalDevice::enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties)
    {
        vkEnumerateDeviceLayerProperties_(device_, propertyCount, properties);
    }

    inline VkResult PhysicalDevice::getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* imageFormatProperties)
    {
        return vkGetPhysicalDeviceImageFormatProperties_(device_, format, type, tiling, usage, flags, imageFormatProperties);
    }

    inline void PhysicalDevice::getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties)
    {
        vkGetPhysicalDeviceSparseImageFormatProperties_(device_, format, type, samples, usage, tiling, propertyCount, properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* memoryProperties)
    {
        vkGetPhysicalDeviceMemoryProperties_(device_, memoryProperties);
    }

    inline void PhysicalDevice::getPhysicalDeviceQueueFamilyProperties(u32* queueFamilyPropertyCount, VkQueueFamilyProperties* queueFamilyProperties)
    {
        vkGetPhysicalDeviceQueueFamilyProperties_(device_, queueFamilyPropertyCount, queueFamilyProperties);
    }

    inline VkResult PhysicalDevice::enumerateDeviceExtensionProperties(const char* layerName, u32* propertyCount, VkExtensionProperties* properties)
    {
        vkEnumerateDeviceExtensionProperties_(device_, layerName, propertyCount, properties);
    }

    //--------------------------------------------------------------
    //---
    //--- PhysicalDevices
    //---
    //--------------------------------------------------------------
    /**
    */
    class PhysicalDevices
    {
    public:
        static const u32 MaxDevices = 8;

        /**
        */
        inline u32 getNumDevices() const;

        /**
        */
        inline PhysicalDevice& getDevice(u32 index);

    private:
        friend class Instance;

        u32 numDevices_;
        PhysicalDevice devices_[MaxDevices];
    };

    inline u32 PhysicalDevices::getNumDevices() const
    {
        return numDevices_;
    }

    inline PhysicalDevice& PhysicalDevices::getDevice(u32 index)
    {
        VLK_ASSERT(index<numDevices_);
        return devices_[index];
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    class Instance
    {
    public:
        Instance();
        Instance(Instance&& rhs);
        ~Instance();

        inline bool valid() const;

#define VLK_EXT_DECL_INSTANCE_MEMBER(name) name
#define VLK_EXT_IMPL_INSTANCE_MEMBER(name) name ## _
#define VLK_MEMBER_INSTANCE instance_
#include "VkFunctions.inc"

        void destroy();

        PhysicalDevices enumeratePhysicalDevices();

        Instance& operator=(Instance&& rhs);
    private:
        friend class Lib;

        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        VkResult initialize();

        VkInstance instance_;
        const VkAllocationCallbacks* allocator_;

#define VLK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name ## _;
#include "VkFunctions.inc"
    };

    inline bool Instance::valid() const
    {
        return VLK_NULL != instance_;
    }

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    /**
    */
    class Device
    {
    public:
        Device();
        Device(Device&& rhs);
        ~Device();

        inline bool valid() const;

#define VLK_EXT_DECL_DEVICE_MEMBER(name) name
#define VLK_EXT_IMPL_DEVICE_MEMBER(name) name ## _
#define VLK_MEMBER_DEVICE device_
#include "VkFunctions.inc"

        void destroy();

        Device& operator=(Device&& rhs);
    private:
        friend class PhysicalDevice;
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;

        VkResult initialize();

#define VLK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name ## _;
#include "VkFunctions.inc"

        VkDevice device_;
        u32 queueFamily_;
        const VkAllocationCallbacks* allocator_;
    };

    inline bool Device::valid() const
    {
        return VLK_NULL != device_;
    }
}
#endif //INC_VK_H_
