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

#include <utility>

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
    //--------------------------------------------------------------
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

    using std::move;

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

    //--------------------------------------------------------------
#define CPPVK_EXPORTED_FUNCTION(name) extern PFN_ ## name name;
#include "VkFunctions.inc"

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

    //--------------------------------------------------------------
    typedef bool (*PFN_checkExtensions)(const VkExtensionProperties& properties);
    typedef void (*PFN_checkQueueFamilies)(u32 queueFamilyIndices[QueueType_Max], u32 numQueueFamilies, VkQueueFamilyProperties* queueFamilyProperties, const bool* queueFamilyPresentationSupports, const bool* requests);
    typedef bool (*PFN_checkDeviceFeatures)(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);
    typedef bool (*PFN_checkSurfaceFormats)(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
    typedef bool (*PFN_checkSurfaceCapabilities)(VkImageUsageFlags& imageUsageFlags, VkSurfaceTransformFlagBitsKHR& preTransform, VkCompositeAlphaFlagBitsKHR& compsiteAlpha, const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

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
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[CPPVK_MAX_LAYERS];

        PFN_checkExtensions checkExtensions_;
    };

    //--------------------------------------------------------------
    struct DeviceCreateInfo
    {
        //Device queue info
        bool requestQueueTypes_[QueueType_Max];

        //
        u32 enabledLayerCount_;
        const Char* enabledLayerNames_[CPPVK_MAX_LAYERS];

        //
        PFN_checkQueueFamilies checkQueueFamilies_;
        PFN_checkExtensions checkExtensions_;
        PFN_checkDeviceFeatures checkDeviceFeatures_;
    };

    //--------------------------------------------------------------
    struct SurfaceCreateInfo
    {
#ifdef CPPVK_USE_PLATFORM_XLIB_KHR
        VkXlibSurfaceCreateFlagsKHR flags_;
        Display* display_;
        Window window_;
#endif

#ifdef CPPVK_USE_PLATFORM_XCB_KHR
        VkXcbSurfaceCreateFlagsKHR flags_;
        xcb_connection_t* connection_;
        xcb_window_t window_;
#endif

#ifdef CPPVK_USE_PLATFORM_WAYLAND_KHR
        VkWaylandSurfaceCreateFlagsKHR flags_;
        wl_display* display_;
        wl_surface* surface_;
#endif

#ifdef CPPVK_USE_PLATFORM_MIR_KHR
        VkMirSurfaceCreateFlagsKHR flags_;
        MirConnection* connection_;
        MirSurface* surface_;
#endif

#ifdef CPPVK_USE_PLATFORM_ANDROID_KHR
        VkAndroidSurfaceCreateFlagsKHR flags_;
        ANativeWindow* window_;
#endif

#ifdef CPPVK_USE_PLATFORM_WIN32_KHR
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
        VkPresentModeKHR presentMode_;
        VkExtent2D surfaceExtent_;

        PFN_checkSurfaceCapabilities checkSurfaceCapabilities_;
        PFN_checkSurfaceFormats checkSurfaceFormats_;
    };

    //--------------------------------------------------------------
    //---
    //--- Builder
    //---
    //--------------------------------------------------------------

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
        Lib(Lib&&) = delete;
        Lib& operator=(const Lib&) = delete;
        Lib& operator=(Lib&&) = delete;

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
        inline void enumerateDeviceExtensionProperties(DeviceExtensionProperties& properties, const Char* layerName);
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

    inline void PhysicalDevice::enumerateDeviceExtensionProperties(DeviceExtensionProperties& properties, const Char* layerName)
    {
        properties.numExtensionProperties_ = DeviceExtensionProperties::MaxProperties;
        vkEnumerateDeviceExtensionProperties(device_, layerName, &properties.numExtensionProperties_, properties.extensionProperties_);
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    class Instance
    {
    public:
        static VkResult create(
            Instance& instance,
            const VkInstanceCreateInfo& instanceCreateInfo,
            const SurfaceCreateInfo& surfaceCreateInfo,
            const VkAllocationCallbacks* allocator);

        Instance();
        ~Instance();

        inline bool valid() const;
        inline operator const VkInstance() const;
        inline operator VkInstance();
        void destroy();

        inline const VkAllocationCallbacks* getAllocator();

        u32 enumeratePhysicalDevices(u32 maxDevices, PhysicalDevice* devices) const;
        inline VkSurfaceKHR getPresentationSurface();

#define CPPVK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

        /**
        @brief
        */
        bool getPhysicalDevicePresentationSurfaceSupport(PhysicalDevice physicalDevice, u32 queueFamilyIndex);

    private:
        Instance(const Instance&) = delete;
        Instance(Instance&&) = delete;
        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) = delete;

        VkResult initialize();
        VkResult createPresentationSurface(const SurfaceCreateInfo& createInfo);

        VkInstance instance_;
        const VkAllocationCallbacks* allocator_;
        VkSurfaceKHR presentationSurface_;
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

    inline VkSurfaceKHR Instance::getPresentationSurface()
    {
        return presentationSurface_;
    }

    inline const VkAllocationCallbacks* Instance::getAllocator()
    {
        return allocator_;
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
        static const s32 MaxSwapchainImages = CPPVK_MAX_SWAPCHAINMAX;

        static VkResult create(Swapchain& swapchain, Device& device, VkSwapchainCreateInfoKHR& createInfo, const VkAllocationCallbacks* allocator);

        Swapchain();
        ~Swapchain();

        void destroy(Device& device);

        inline bool valid() const;
        inline operator const VkSwapchainKHR() const;
        inline operator VkSwapchainKHR();

        inline s32 getNumImages() const;
        inline VkImage getImage(s32 index);
    private:
        Swapchain(const Swapchain&) = delete;
        Swapchain(Swapchain&&) = delete;
        Swapchain& operator=(const Swapchain&) = delete;
        Swapchain& operator=(Swapchain&&) = delete;

        VkSwapchainKHR swapchain_;
        const VkAllocationCallbacks* allocator_;
        u32 numImages_;
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
    //--- Device
    //---
    //--------------------------------------------------------------
    /**
    */
    class Device
    {
    public:
        static const s32 MaxCommandBuffers = 8;

        static VkResult create(
            Device& device,
            VkPhysicalDevice physicalDevice,
            const VkDeviceCreateInfo& deviceCreateInfo,
            const u32 queueFamilityIndices[QueueType_Max],
            VkSwapchainCreateInfoKHR& swapchainCreateInfo,
            const VkAllocationCallbacks* allocator);

        Device();
        ~Device();

        void destroy();

        inline bool valid() const;
        inline operator const VkDevice() const;
        inline operator VkDevice();

        VkResult waitIdle();

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

        inline VkQueue& getQueue(u32 index);

        inline VkResult submit(s32 queue, u32 numSubmits, const VkSubmitInfo* submits, VkFence fence);
        inline VkResult queueWaitIdle(s32 queue);

#define CPPVK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

    private:
        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) = delete;

        VkResult initialize();
        VkResult createSemaphores();

        VkDevice device_;
        const VkAllocationCallbacks* allocator_;
        VkQueue queues_[QueueType_Max];
        VkSemaphore semaphoreImageAvailable_;
        VkSemaphore semaphoreRenderingFinished_;
        Swapchain swapchain_;
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

    inline VkQueue& Device::getQueue(u32 index)
    {
        return queues_[index];
    }

    inline VkResult Device::submit(s32 queue, u32 numSubmits, const VkSubmitInfo* submits, VkFence fence)
    {
        //CPPVK_ASSERT(CPPVK_NULL != device_);
        //CPPVK_ASSERT(0<=queue && queue<MaxQueues);
        CPPVK_ASSERT(CPPVK_NULL != submits);
        return vkQueueSubmit(queues_[queue], numSubmits, submits, fence);
    }

    inline VkResult Device::queueWaitIdle(s32 queue)
    {
        return vkQueueWaitIdle(queues_[queue]);
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

        inline Instance& getInstance();

        void getInstanceExtensionProperties(InstanceExtensionProperties& properties, const Char* layerName);

        bool createInstance(
            const InstanceCreateInfo& instanceCreateInfo,
            const SurfaceCreateInfo& surfaceCreateInfo,
            const Char* layerName,
            const VkAllocationCallbacks* allocator);

        bool createDevice(
            s32 index,
            const DeviceCreateInfo& deviceCreateInfo,
            const SwapchainCreateInfo& swapchainCreateInfo,
            const Char* layerName,
            const VkAllocationCallbacks* allocator);

        static void defaultCheckQueueFamilies(
            u32 queueFamilyIndices[QueueType_Max],
            u32 numQueueFamilies,
            VkQueueFamilyProperties* queueFamilyProperties,
            const bool* queueFamilyPresentationSupports,
            const bool* requests);
        static bool defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace);
        static bool defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace);

        static bool defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
        static bool defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
    private:
        System(const System&) = delete;
        System(System&&) = delete;
        System& operator=(const System&) = delete;
        System& operator=(System&&) = delete;

        static VkPresentModeKHR getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request);

        Lib lib_;
        Instance instance_;
        Device devices_[CPPVK_MAX_PHYSICAL_DEVICES];
    };

    inline Instance& System::getInstance()
    {
        return instance_;
    }
}
#endif //INC_CPPVK_H_
