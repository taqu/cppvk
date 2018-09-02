#ifndef INC_CPPVK_H_
#define INC_CPPVK_H_
/**
@file cppvk.h
@author t-sakai
@date 2017/10/15 create
*/
#ifdef _DEBUG
#include <cassert>
#endif

#ifdef __cplusplus
#   if 201103L<=__cplusplus || 1900<=_MSC_VER
#       define CPPVK_CPP11 1
#   endif
#endif

#ifdef __cplusplus
#   ifdef CPPVK_CPP11
#       define CPPVK_NULL nullptr
#   else
#       define CPPVK_NULL 0
#   endif
#else
#   define CPPVK_NULL (void*)0
#endif

#include <cstdint>

#ifdef _MSC_VER

#define CPPVK_DLHANDLE HMODULE
#define CPPVK_DLOPEN(path) LoadLibrary((path))
#define CPPVK_DLSYM(handle, name) GetProcAddress((handle), (name))
#define CPPVK_DLCLOSE(handle) FreeLibrary((handle))

#define CPPVK_VULKANLIB ("vulkan-1.dll")

#else

#define CPPVK_DLHANDLE void*
#define CPPVK_DLOPEN(path) dlopen((path), RTLD_NOW)
#define CPPVK_DLSYM(handle, name) dlsym((handle), (name))
#define CPPVK_DLCLOSE(handle) dlclose((handle))

#define CPPVK_VULKANLIB ("libvulkan.so.1")

#endif

#ifdef CPPVK_USE_PLATFORM_XLIB_KHR
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#ifdef CPPVK_USE_PLATFORM_XCB_KHR
#define VK_USE_PLATFORM_XCB_KHR
#endif

#ifdef CPPVK_USE_PLATFORM_WAYLAND_KHR
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif

#ifdef CPPVK_USE_PLATFORM_MIR_KHR
#define VK_USE_PLATFORM_MIR_KHR
#endif

#ifdef CPPVK_USE_PLATFORM_ANDROID_KHR
#define VK_USE_PLATFORM_ANDROID_KHR
#endif

#ifdef CPPVK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define VK_NO_PROTOTYPES 1
#include "vulkan.h"

#include "cppvk_config.h"

namespace cppvk
{
#define CPPVK_REPORT_ERROR 1
#define CPPVK_REPORT_WARNING 1

#ifdef _DEBUG
#define CPPVK_ASSERT(exp) assert(exp)
#else
#define CPPVK_ASSERT(exp)
#endif

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
#define CPPVK_EXPORTED_FUNCTION(name) extern PFN_ ## name name;
#include "VkFunctions.inc"

    //--------------------------------------------------------------
    typedef bool (*PFN_checkExtensions)(const VkExtensionProperties& properties);
    typedef bool (*PFN_checkQueueFamily)(const VkQueueFamilyProperties& properties);
    typedef bool (*PFN_checkDeviceFeatures)(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);

    class Instance;
    class Device;
    class Swapchain;
    class CommandPool;
    class CommandBuffer;

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
        VkInstanceCreateFlags createFlags_;
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[CPPVK_MAX_LAYERS];
        u32 enabledExtensionCount_;
        const Char* enabledExtensionNames_[CPPVK_MAX_INSTANCE_EXTENSION_PROPERTIES];
    };

    //--------------------------------------------------------------
    struct DeviceCreateInfo
    {
        //Device queue info
        VkDeviceQueueCreateFlags deviceQueueCreateFlags_;
        u32 queueFamilyIndex_;
        u32 queueCount_;
        const f32* queuePriorities_;

        //
        VkDeviceCreateFlags deviceCreateFlags_;
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[CPPVK_MAX_LAYERS];
        u32 enabledExtensionCount_;
        const Char* enabledExtensionNames_[CPPVK_MAX_DEVICE_EXTENSION_PROPERTIES];
        VkPhysicalDeviceFeatures* enabledFeatures_;
    };

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
    private:
        Lib(const Lib&) = delete;
        Lib& operator=(const Lib&) = delete;

        CPPVK_DLHANDLE handle_;
    };

    inline bool Lib::valid() const
    {
        return CPPVK_NULL != handle_;
    }

    //--------------------------------------------------------------
    //---
    //--- ExtensionProperties
    //---
    //--------------------------------------------------------------
    template<u32 N>
    class ExtensionProperties
    {
    public:
        static const u32 MaxProperties = N;

        ExtensionProperties();
        ~ExtensionProperties();

        u32 getExtensions(const Char** useExtensions, PFN_checkExtensions checkExtensions) const;
    private:
        friend class PhysicalDevice;
        friend class System;

        u32 numExtensionProperties_;
        VkExtensionProperties extensionProperties_[MaxProperties];
    };

    template<u32 N>
    ExtensionProperties<N>::ExtensionProperties()
        :numExtensionProperties_(0)
    {
    }

    template<u32 N>
    ExtensionProperties<N>::~ExtensionProperties()
    {}

    template<u32 N>
    u32 ExtensionProperties<N>::getExtensions(const Char** useExtensions, PFN_checkExtensions checkExtensions) const
    {
        CPPVK_ASSERT(CPPVK_NULL != useExtensions);
        CPPVK_ASSERT(CPPVK_NULL != checkExtensions);
        u32 count = 0;
        for(u32 i=0; i<numExtensionProperties_; ++i){
            if(!checkExtensions(extensionProperties_[i])){
                continue;
            }
            useExtensions[count++] = extensionProperties_[i].extensionName;
        }
        return count;
    }

    typedef ExtensionProperties<CPPVK_MAX_INSTANCE_EXTENSION_PROPERTIES> InstanceExtensionProperties;
    typedef ExtensionProperties<CPPVK_MAX_DEVICE_EXTENSION_PROPERTIES> DeviceExtensionProperties;

    //--------------------------------------------------------------
    //---
    //--- QueueFamilyProperties
    //---
    //--------------------------------------------------------------
    class QueueFamilyProperties
    {
    public:
        static const u32 MaxProperties = CPPVK_MAX_QUEUE_FAMILY_PROPERTIES;

        QueueFamilyProperties();
        ~QueueFamilyProperties();

        s32 selectQueueFamily(PFN_checkQueueFamily checkQueueFamily) const;
    private:
        friend class PhysicalDevice;

        u32 numQueueFamilyProperties_;
        VkQueueFamilyProperties queueFamilyProperties_[MaxProperties];
    };

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
        inline void getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& features);

        /**
        @brief
        */
        inline void getPhysicalDeviceProperties(VkPhysicalDeviceProperties& properties);

        /**
        @brief
        */
        inline void getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties& formatProperties);

        /**
        @brief
        @return
        */
        inline VkResult enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties);

        /**
        @brief
        @return
        */
        inline VkResult getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties);

        /**
        @brief
        */
        inline void getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties);

        /**
        @brief
        */
        inline void getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProperties);

        /**
        @brief
        */
        void getPhysicalDeviceQueueFamilyProperties(QueueFamilyProperties& queueFamilyProperties);

        /**
        @brief
        @return
        */
        void enumerateDeviceExtensionProperties(DeviceExtensionProperties& properties, const Char* layerName);
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

    inline void PhysicalDevice::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& features)
    {
        vkGetPhysicalDeviceFeatures(device_, &features);
    }

    inline void PhysicalDevice::getPhysicalDeviceProperties(VkPhysicalDeviceProperties& properties)
    {
        vkGetPhysicalDeviceProperties(device_, &properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties& formatProperties)
    {
        vkGetPhysicalDeviceFormatProperties(device_, format, &formatProperties);
    }

    inline VkResult PhysicalDevice::enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties)
    {
        return vkEnumerateDeviceLayerProperties(device_, propertyCount, properties);
    }

    inline VkResult PhysicalDevice::getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties)
    {
        return vkGetPhysicalDeviceImageFormatProperties(device_, format, type, tiling, usage, flags, &imageFormatProperties);
    }

    inline void PhysicalDevice::getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties)
    {
        vkGetPhysicalDeviceSparseImageFormatProperties(device_, format, type, samples, usage, tiling, propertyCount, properties);
    }

    inline void PhysicalDevice::getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProperties)
    {
        vkGetPhysicalDeviceMemoryProperties(device_, &memoryProperties);
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
        static const s32 MaxPhysicalDevices = CPPVK_MAX_PHYSICAL_DEVICES;
        /**
        */
        inline u32 size() const;

        /**
        */
        inline const PhysicalDevice& operator[](u32 index) const;

    private:
        friend class Instance;

        u32 numDevices_;
        PhysicalDevice devices_[MaxPhysicalDevices];
    };

    inline u32 PhysicalDevices::size() const
    {
        return numDevices_;
    }

    inline const PhysicalDevice& PhysicalDevices::operator[](u32 index) const
    {
        CPPVK_ASSERT(index<numDevices_);
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
        static VkResult create(Instance& instance, const VkInstanceCreateInfo& createInfo, const VkAllocationCallbacks* allocator);

        Instance();
        ~Instance();

        inline bool valid() const;
        inline operator const VkInstance() const;
        inline operator VkInstance();
        void destroy();

        inline const VkAllocationCallbacks* getAllocator();

        PhysicalDevices enumeratePhysicalDevices();
        inline VkSurfaceKHR getPresentSurface();

#ifdef CPPVK_USE_PLATFORM_XLIB_KHR
        typedef VkXlibSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef CPPVK_USE_PLATFORM_XCB_KHR
        typedef VkXcbSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef CPPVK_USE_PLATFORM_WAYLAND_KHR
        typedef VkWaylandSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef CPPVK_USE_PLATFORM_MIR_KHR
        typedef VkMirSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef CPPVK_USE_PLATFORM_ANDROID_KHR
        typedef VkAndroidSurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

#ifdef CPPVK_USE_PLATFORM_WIN32_KHR
        typedef VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo;
#endif

        VkResult createPresentSurface(const SurfaceCreateInfo& createInfo);


#define CPPVK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

    private:
        friend class Lib;

        Instance(const Instance&) = delete;
        Instance(Instance&& rhs) = delete;
        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&& rhs) = delete;

        VkResult initialize();

        VkInstance instance_;
        VkSurfaceKHR presentSurface_;
        const VkAllocationCallbacks* allocator_;
    };

    inline bool Instance::valid() const
    {
        return CPPVK_NULL != instance_;
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

    inline const VkAllocationCallbacks* Instance::getAllocator()
    {
        return allocator_;
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
        static const s32 MaxQueues = 4;
        static const s32 GraphicsQueue = 0;
        static const s32 ComputeQueue = 1;
        static const s32 PresentQueue = 2;
        static const s32 MaxCommandBuffers = 8;

        static VkResult create(Device& device, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& createInfo, const VkAllocationCallbacks* allocator);

        Device();
        ~Device();

        void destroy();

        inline bool valid() const;
        inline operator const VkDevice() const;
        inline operator VkDevice();

        VkResult waitIdle();

        /**
        */
        VkResult createSwapchain(Swapchain& swapchain, VkSwapchainCreateInfoKHR& createInfo, const VkAllocationCallbacks* allocator);
        /**
        */
        void destroySwapchain(Swapchain& swapchain, const VkAllocationCallbacks* allocator);

        /**
        */
        VkResult createCommandPool(CommandPool& commandPool, const VkCommandPoolCreateInfo& createInfo, const VkAllocationCallbacks* allocator);
        /**
        */
        void destroyCommandPool(CommandPool& commandPool, const VkAllocationCallbacks* allocator);
        /**
        */
        VkResult resetCommandPool(CommandPool& commandPool, VkCommandPoolResetFlags flags);

        /**
        */
        VkResult allocateCommandBuffers(CommandBuffer* commandBuffers, const VkCommandBufferAllocateInfo& allocateInfo);
        /**
        */
        void deallocateCommandBuffers(u32 numBuffers, CommandBuffer* commandBuffers, CommandPool& commandPool);

        inline u32 getNumQueues() const;
        inline VkQueue& getQueue(u32 index);

        inline VkResult submit(s32 queue, u32 numSubmits, const VkSubmitInfo* submits, VkFence fence);
        inline VkResult queueWaitIdle(s32 queue);

#define CPPVK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

    private:
        Device(const Device&) = delete;
        Device(Device&& rhs) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&& rhs) = delete;

        VkResult initialize(const VkAllocationCallbacks* allocator);

        VkDevice device_;
        u32 numQueues_;
        u32 queueFamilyIndices_[MaxQueues];
        VkQueue queues_[MaxQueues];
        //VkSemaphore semaphoreImageAvailable_;
        //VkSemaphore semaphoreRenderingFinished_;
        const VkAllocationCallbacks* allocator_;
    };

    inline bool Device::valid() const
    {
        return CPPVK_NULL != device_;
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
        CPPVK_ASSERT(0<=index && index<numQueues_);
        return queues_[index];
    }

    inline VkResult Device::submit(s32 queue, u32 numSubmits, const VkSubmitInfo* submits, VkFence fence)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        CPPVK_ASSERT(0<=queue && queue<MaxQueues);
        CPPVK_ASSERT(CPPVK_NULL != submits);
        return vkQueueSubmit(queues_[queue], numSubmits, submits, fence);
    }

    inline VkResult Device::queueWaitIdle(s32 queue)
    {
        return vkQueueWaitIdle(queues_[queue]);
    }

    //--------------------------------------------------------------
    //---
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    /**
    */
    class Swapchain
    {
    public:
        static const s32 MaxSwapchainImages = 4;

        Swapchain();
        ~Swapchain();

        inline bool valid() const;
        inline operator const VkSwapchainKHR() const;
        inline operator VkSwapchainKHR();

        inline s32 getNumImages() const;
        inline VkImage getImage(s32 index);
    private:
        friend class Device;

        Swapchain(const Swapchain&) = delete;
        Swapchain& operator=(const Swapchain&) = delete;

        VkSwapchainKHR swapchain_;
        s32 numImages_;
        VkImage images_[MaxSwapchainImages];
    };

    inline bool Swapchain::valid() const
    {
        return CPPVK_NULL != swapchain_;
    }

    inline Swapchain::operator const VkSwapchainKHR() const
    {
        return swapchain_;
    }

    inline Swapchain::operator VkSwapchainKHR()
    {
        return swapchain_;
    }

    inline s32 Swapchain::getNumImages() const
    {
        return numImages_;
    }

    inline VkImage Swapchain::getImage(s32 index)
    {
        CPPVK_ASSERT(0<=numImages_ && numImages_<MaxSwapchainImages);
        return images_[index];
    }

    //--------------------------------------------------------------
    //---
    //--- CommandPool
    //---
    //--------------------------------------------------------------
    /**
    */
    class CommandPool
    {
    public:
        CommandPool();
        ~CommandPool();

        inline bool valid() const;
        inline operator const VkCommandPool() const;
        inline operator VkCommandPool();
    private:
        friend class Device;

        CommandPool(const CommandPool&) = delete;
        CommandPool& operator=(const CommandPool&) = delete;

        VkCommandPool commandPool_;
    };

    inline bool CommandPool::valid() const
    {
        return CPPVK_NULL != commandPool_;
    }

    inline CommandPool::operator const VkCommandPool() const
    {
        return commandPool_;
    }

    inline CommandPool::operator VkCommandPool()
    {
        return commandPool_;
    }

    //--------------------------------------------------------------
    //---
    //--- CommandBuffer
    //---
    //--------------------------------------------------------------
    /**
    */
    class CommandBuffer
    {
    public:
        CommandBuffer();
        ~CommandBuffer();

        inline bool valid() const;
        inline operator const VkCommandBuffer() const;
        inline operator VkCommandBuffer();

        inline VkResult begin(const VkCommandBufferBeginInfo& beginInfo);
        inline VkResult end();
        inline VkResult reset(VkCommandBufferResetFlags flags);

        /**
        */
        inline void pipelineBarrier(
            VkPipelineStageFlags srcStageMask,
            VkPipelineStageFlags dstStageMask,
            VkDependencyFlags dependencyFlags,
            u32 numMemoryBarriers, const VkMemoryBarrier* memoryBarriers,
            u32 numBufferBarriers, const VkBufferMemoryBarrier* bufferBarriers,
            u32 numImageBarriers, const VkImageMemoryBarrier* imageBarriers);

        /**
        */
        inline void fillBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, u32 data);
        /**
        */
        inline void updateBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const u32* data);
        /**
        */
        inline void clearColorImage(VkImage image, VkImageLayout layout, const VkClearColorValue* color, u32 numRanges, const VkImageSubresourceRange* ranges);
        /**
        */
        inline void clearDepthStencilImage(VkImage image, VkImageLayout layout, const VkClearDepthStencilValue* depthStencil, u32 numRanges, const VkImageSubresourceRange* ranges);

        /**
        */
        inline void copy(VkBuffer src, VkBuffer dst, u32 numRegions, const VkBufferCopy* regions);
        /**
        */
        inline void copy(VkBuffer src, VkImage dst, VkImageLayout layout, u32 numRegions, const VkBufferImageCopy* regions);
        /**
        */
        inline void copy(VkImage src, VkImageLayout layout, VkBuffer dst, u32 numRegions, const VkBufferImageCopy* regions);
        /**
        */
        inline void copy(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageCopy* regions);

        /**
        */
        inline void blit(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageBlit* regions, VkFilter filter);

    private:
        friend class Device;

        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer& operator=(const CommandBuffer&) = delete;

        VkCommandBuffer commandBuffer_;
    };

    inline bool CommandBuffer::valid() const
    {
        return CPPVK_NULL != commandBuffer_;
    }

    inline CommandBuffer::operator const VkCommandBuffer() const
    {
        return commandBuffer_;
    }

    inline CommandBuffer::operator VkCommandBuffer()
    {
        return commandBuffer_;
    }

    inline VkResult CommandBuffer::begin(const VkCommandBufferBeginInfo& beginInfo)
    {
        CPPVK_ASSERT(valid());
        return vkBeginCommandBuffer(commandBuffer_, &beginInfo);
    }

    inline VkResult CommandBuffer::end()
    {
        CPPVK_ASSERT(valid());
        return vkEndCommandBuffer(commandBuffer_);
    }

    inline VkResult CommandBuffer::reset(VkCommandBufferResetFlags flags)
    {
        CPPVK_ASSERT(valid());
        return vkResetCommandBuffer(commandBuffer_, flags);
    }

    inline void CommandBuffer::pipelineBarrier(
        VkPipelineStageFlags srcStageMask,
        VkPipelineStageFlags dstStageMask,
        VkDependencyFlags dependencyFlags,
        u32 numMemoryBarriers, const VkMemoryBarrier* memoryBarriers,
        u32 numBufferBarriers, const VkBufferMemoryBarrier* bufferBarriers,
        u32 numImageBarriers, const VkImageMemoryBarrier* imageBarriers)
    {
        CPPVK_ASSERT(valid());
        vkCmdPipelineBarrier(commandBuffer_, srcStageMask, dstStageMask, dependencyFlags, numMemoryBarriers, memoryBarriers, numBufferBarriers, bufferBarriers, numImageBarriers, imageBarriers);
    }

    inline void CommandBuffer::fillBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, u32 data)
    {
        CPPVK_ASSERT(valid());
        vkCmdFillBuffer(commandBuffer_, buffer, offset , size, data);
    }

    inline void CommandBuffer::updateBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const u32* data)
    {
        CPPVK_ASSERT(valid());
        vkCmdUpdateBuffer(commandBuffer_, buffer, offset, size, data);
    }

    inline void CommandBuffer::clearColorImage(VkImage image, VkImageLayout layout, const VkClearColorValue* color, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        CPPVK_ASSERT(valid());
        vkCmdClearColorImage(commandBuffer_, image, layout, color, numRanges, ranges);
    }

    inline void CommandBuffer::clearDepthStencilImage(VkImage image, VkImageLayout layout, const VkClearDepthStencilValue* depthStencil, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        CPPVK_ASSERT(valid());
        vkCmdClearDepthStencilImage(commandBuffer_, image, layout, depthStencil, numRanges, ranges);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkBuffer dst, u32 numRegions, const VkBufferCopy* regions)
    {
        CPPVK_ASSERT(valid());
        vkCmdCopyBuffer(commandBuffer_, src, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkImage dst, VkImageLayout layout, u32 numRegions, const VkBufferImageCopy* regions)
    {
        CPPVK_ASSERT(valid());
        vkCmdCopyBufferToImage(commandBuffer_, src, dst, layout, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout layout, VkBuffer dst, u32 numRegions, const VkBufferImageCopy* regions)
    {
        CPPVK_ASSERT(valid());
        vkCmdCopyImageToBuffer(commandBuffer_, src, layout, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageCopy* regions)
    {
        CPPVK_ASSERT(valid());
        vkCmdCopyImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions);
    }

    /**
    */
    inline void CommandBuffer::blit(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageBlit* regions, VkFilter filter)
    {
        CPPVK_ASSERT(valid());
        vkCmdBlitImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions, filter);
    }

    //--------------------------------------------------------------
    //---
    //--- System
    //---
    //--------------------------------------------------------------
    /**
    */
    class System
    {
    public:
        System();
        ~System();

        bool initialize();
        void terminate();

        void getInstanceExtensionProperties(InstanceExtensionProperties& properties, const Char* layerName);
        PhysicalDevices enumeratePhysicalDevices();

        bool createInstance(InstanceCreateInfo& createInfo, const Char* layerName, PFN_checkExtensions checkExtensions, const VkAllocationCallbacks* allocator);
        bool createDevice(s32 index, DeviceCreateInfo& createInfo, const Char* layerName, PFN_checkQueueFamily checkQueueFamily, PFN_checkExtensions checkExtensions, PFN_checkDeviceFeatures checkDeviceFeatures, const VkAllocationCallbacks* allocator);
        bool createPresentSurface(const Instance::SurfaceCreateInfo& createInfo);
    private:
        System(const System&) = delete;
        System& operator=(const System&) = delete;

        Lib lib_;
        Instance instance_;
        Device devices_[CPPVK_MAX_PHYSICAL_DEVICES];
    };
}
#endif //INC_CPPVK_H_
