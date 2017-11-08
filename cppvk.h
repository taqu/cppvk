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
#   if 201103L<=__cplusplus || 1900<=_MSC_VER
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

#define VK_NO_PROTOTYPES 1
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
    typedef char Char;
    typedef __int32 s32;
    typedef unsigned __int32 u32;

#else
    typedef char Char;
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

    static const u32 MaxProperties = 32;

    //-------------------------------------------------------------------------------
#define VLK_EXPORTED_FUNCTION(name) extern PFN_ ## name name;
#define VLK_INSTANCE_FUNCTION(name) extern PFN_ ## name name;
#define VLK_DEVICE_FUNCTION(name) extern PFN_ ## name name;
#define VLK_PHYSICALDEVICE_FUNCTION(name) extern PFN_ ## name name;

#define VLK_EXT_EXPORTED_FUNCTION(name) extern PFN_ ## name name;
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
    //--- ExtensionProperties
    //---
    //--------------------------------------------------------------
    template<u32 MaxCount>
    class ExtensionProperties
    {
    public:
        ExtensionProperties();
        ~ExtensionProperties();

        VkResult enumerateInstanceExtensionProperties(const Char* layerName = VLK_NULL);
        VkResult enumerateDeviceExtensionProperties(VkPhysicalDevice device, const Char* layerName = VLK_NULL);

        inline u32 size() const;
        inline const VkExtensionProperties& get(u32 index) const;

        /**
        @return get it index [0,size), otherwise -1
        @param name ... no null, an extension name to find
        */
        s32 find(const Char* name) const;
    private:
        ExtensionProperties(const ExtensionProperties&) = delete;
        ExtensionProperties& operator=(const ExtensionProperties&) = delete;

        u32 numProperties_;
        VkExtensionProperties properties_[MaxCount];
    };

    template<u32 MaxCount>
    ExtensionProperties<MaxCount>::ExtensionProperties()
        :numProperties_(0)
    {
    }

    template<u32 MaxCount>
    ExtensionProperties<MaxCount>::~ExtensionProperties()
    {
    }

    template<u32 MaxCount>
    VkResult ExtensionProperties<MaxCount>::enumerateInstanceExtensionProperties(const Char* layerName)
    {
        numProperties_ = MaxCount;
        VkResult result = vkEnumerateInstanceExtensionProperties(layerName, &numProperties_, properties_);
        if(VK_SUCCESS != result){
            numProperties_ = 0;
        }
        return result;
    }

    template<u32 MaxCount>
    VkResult ExtensionProperties<MaxCount>::enumerateDeviceExtensionProperties(VkPhysicalDevice device, const Char* layerName)
    {
        numProperties_ = MaxCount;
        VkResult result = vkEnumerateDeviceExtensionProperties(device, layerName, &numProperties_, properties_);
        if(VK_SUCCESS != result){
            numProperties_ = 0;
        }
        return result;
    }

    template<u32 MaxCount>
    inline u32 ExtensionProperties<MaxCount>::size() const
    {
        return numProperties_;
    }

    template<u32 MaxCount>
    inline const VkExtensionProperties& ExtensionProperties<MaxCount>::get(u32 index) const
    {
        VLK_ASSERT(0<=index && index<numProperties_);
        return properties_[index];
    }

    template<u32 MaxCount>
    s32 ExtensionProperties<MaxCount>::find(const Char* name) const
    {
        VLK_ASSERT(VLK_NULL != name);
        for(u32 i=0; i<numProperties_; ++i){
            if(0==strcmp(name, properties_[i].extensionName)){
                return static_cast<s32>(i);
            }
        }
        return -1;
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
        inline operator const VkPhysicalDevice() const;
        inline operator VkPhysicalDevice();

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

        VkResult createDevice(
            Device& device,
            const VkDeviceCreateInfo* createInfo,
            const VkAllocationCallbacks* allocator);

    private:
        friend class Instance;

        VkPhysicalDevice device_;
    };

    inline PhysicalDevice::operator const VkPhysicalDevice() const
    {
        return device_;
    }

    inline PhysicalDevice::operator VkPhysicalDevice()
    {
        return device_;
    }

    inline void PhysicalDevice::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* features)
    {
        vkGetPhysicalDeviceFeatures(device_, features);
    }

    inline void PhysicalDevice::getPhysicalDeviceProperties(VkPhysicalDeviceProperties* properties)
    {
        vkGetPhysicalDeviceProperties(device_, properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties* formatProperties)
    {
        vkGetPhysicalDeviceFormatProperties(device_, format, formatProperties);
    }

    inline VkResult PhysicalDevice::enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties)
    {
        return vkEnumerateDeviceLayerProperties(device_, propertyCount, properties);
    }

    inline VkResult PhysicalDevice::getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* imageFormatProperties)
    {
        return vkGetPhysicalDeviceImageFormatProperties(device_, format, type, tiling, usage, flags, imageFormatProperties);
    }

    inline void PhysicalDevice::getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties)
    {
        vkGetPhysicalDeviceSparseImageFormatProperties(device_, format, type, samples, usage, tiling, propertyCount, properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* memoryProperties)
    {
        vkGetPhysicalDeviceMemoryProperties(device_, memoryProperties);
    }

    inline void PhysicalDevice::getPhysicalDeviceQueueFamilyProperties(u32* queueFamilyPropertyCount, VkQueueFamilyProperties* queueFamilyProperties)
    {
        vkGetPhysicalDeviceQueueFamilyProperties(device_, queueFamilyPropertyCount, queueFamilyProperties);
    }

    inline VkResult PhysicalDevice::enumerateDeviceExtensionProperties(const char* layerName, u32* propertyCount, VkExtensionProperties* properties)
    {
        vkEnumerateDeviceExtensionProperties(device_, layerName, propertyCount, properties);
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
        inline u32 size() const;

        /**
        */
        inline PhysicalDevice& getDevice(u32 index);

    private:
        friend class Instance;

        u32 numDevices_;
        PhysicalDevice devices_[MaxDevices];
    };

    inline u32 PhysicalDevices::size() const
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
        inline operator const VkInstance() const;
        inline operator VkInstance();

        void destroy();

        PhysicalDevices enumeratePhysicalDevices();
        inline VkSurfaceKHR getPresentSurface();

#ifdef VK_USE_PLATFORM_XLIB_KHR
        typedef VkXlibSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
        typedef VkXcbSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        typedef VkWaylandSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
        typedef VkMirSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef VK_USE_PLATFORM_ANDROID_KHR
        typedef VkAndroidSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
        typedef VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

        VkResult createPresentSurface(const SurfaceCreateInfo& createInfo);

#define VLK_EXT_INSTANCE_MEMBER
#define VLK_EXT_DECL_INSTANCE_MEMBER(name) name
#define VLK_EXT_IMPL_INSTANCE_MEMBER(name) name ## _

#define VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(name) name
#define VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(name) name ## _

#define VLK_MEMBER_INSTANCE instance_
#include "VkFunctions.inc"

        Instance& operator=(Instance&& rhs);
    private:
        friend class Lib;

        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        VkResult initialize();

        VkInstance instance_;
        VkSurfaceKHR presentSurface_;
        const VkAllocationCallbacks* allocator_;

#define VLK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name ## _;
#include "VkFunctions.inc"
    };

    inline bool Instance::valid() const
    {
        return VLK_NULL != instance_;
    }

    inline Instance::operator const VkInstance() const
    {
        return instance_;
    }

    inline Instance::operator VkInstance()
    {
        return instance_;
    }

    inline VkSurfaceKHR Instance::getPresentSurface()
    {
        return presentSurface_;
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
        static const u32 MaxQueues = 4;
        static const u32 MaxSwapchainImages = 4;
        static const u32 GraphicsQueue = 0;
        static const u32 PresentQueue = 1;

        Device();
        ~Device();

        void destroy();

        inline bool valid() const;
        inline operator const VkDevice() const;
        inline operator VkDevice();

        VkResult createSwapchain(VkSwapchainCreateInfoKHR& createInfo);

        /**
        */
        VkResult createCommandBuffers();

        /**
        */
        VkResult clearCommandBuffers();

        /**
        */
        VkResult recordCommandBuffers();

        bool present();

        /**
        */
        bool onWindowSizeChanged();

        inline u32 getNumQueues() const;
        inline VkQueue& getQueue(u32 index);

#define VLK_EXT_DECL_DEVICE_MEMBER(name) name
#define VLK_EXT_IMPL_DEVICE_MEMBER(name) name ## _
#define VLK_MEMBER_DEVICE device_
#include "VkFunctions.inc"

    private:
        friend class PhysicalDevice;
        Device(const Device&) = delete;
        Device(Device&& rhs) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&& rhs) = delete;

        VkResult initialize();

#define VLK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name ## _;
#include "VkFunctions.inc"

        VkDevice device_;
        VkSwapchainCreateInfoKHR swapchainCreateInfo_;
        VkSwapchainKHR swapchain_;
        u32 numQueues_;
        u32 queueFamilyIndices_[MaxQueues];
        VkQueue queues_[MaxQueues];
        VkSemaphore semaphoreImageAvailable_;
        VkSemaphore semaphoreRenderingFinished_;
        u32 swapchainImageCount_;
        VkImage swapchainImages_[MaxSwapchainImages];
        VkCommandBuffer presentQueueCommandBuffers_[MaxSwapchainImages];
        VkCommandPool presentQueueCommandPool_;
        VkClearColorValue clearColor_;
        const VkAllocationCallbacks* allocator_;
    };

    inline bool Device::valid() const
    {
        return VLK_NULL != device_;
    }

    inline Device::operator const VkDevice() const
    {
        return device_;
    }

    inline Device::operator VkDevice()
    {
        return device_;
    }

    inline u32 Device::getNumQueues() const
    {
        return numQueues_;
    }

    inline VkQueue& Device::getQueue(u32 index)
    {
        VLK_ASSERT(0<=index && index<numQueues_);
        return queues_[index];
    }
}
#endif //INC_VK_H_
