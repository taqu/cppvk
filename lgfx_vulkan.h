#ifndef INC_LGFX_VULKAN_H_
#define INC_LGFX_VULKAN_H_
/**
@file lgfx_vulkan.h
@author t-sakai
@date 2018/09/19 create

//--- Usage
//-----------------------------------------------------------
Put '#define LGFX_VULKAN_IMPLEMENTATION' before including this file to create the implementation.
*/

namespace lgfx
{
#ifdef LGFX_VULKAN_IMPLEMENTATION
#   define LGFX_VK_EXPORTED_FUNCTION(name) PFN_ ## name name = LGFX_NULL;
#   include "VkFunctions.inc"
#else
#   define LGFX_VK_EXPORTED_FUNCTION(name) extern PFN_ ## name name = LGFX_NULL;
#   include "VkFunctions.inc"
#endif

    enum LGFX_RESULT : s32
    {
        LGFX_SUCCESS = VK_SUCCESS,
        LGFX_NOT_READY = VK_NOT_READY,
        LGFX_TIMEOUT = VK_TIMEOUT,
        LGFX_EVENT_SET = VK_EVENT_SET,
        LGFX_EVENT_RESET = VK_EVENT_RESET,
        LGFX_INCOMPLETE = VK_INCOMPLETE,
        LGFX_ERROR_OUT_OF_HOST_MEMORY = VK_ERROR_OUT_OF_HOST_MEMORY,
        LGFX_ERROR_OUT_OF_DEVICE_MEMORY = VK_ERROR_OUT_OF_DEVICE_MEMORY,
        LGFX_ERROR_INITIALIZATION_FAILED = VK_ERROR_INITIALIZATION_FAILED,
        LGFX_ERROR_DEVICE_LOST = VK_ERROR_DEVICE_LOST,
        LGFX_ERROR_MEMORY_MAP_FAILED = VK_ERROR_MEMORY_MAP_FAILED,
        LGFX_ERROR_LAYER_NOT_PRESENT = VK_ERROR_LAYER_NOT_PRESENT,
        LGFX_ERROR_EXTENSION_NOT_PRESENT = VK_ERROR_EXTENSION_NOT_PRESENT,
        LGFX_ERROR_FEATURE_NOT_PRESENT = VK_ERROR_FEATURE_NOT_PRESENT,
        LGFX_ERROR_INCOMPATIBLE_DRIVER = VK_ERROR_INCOMPATIBLE_DRIVER,
        LGFX_ERROR_TOO_MANY_OBJECTS = VK_ERROR_TOO_MANY_OBJECTS,
        LGFX_ERROR_FORMAT_NOT_SUPPORTED = VK_ERROR_FORMAT_NOT_SUPPORTED,
        LGFX_ERROR_FRAGMENTED_POOL = VK_ERROR_FRAGMENTED_POOL,
        LGFX_ERROR_SURFACE_LOST_KHR = VK_ERROR_SURFACE_LOST_KHR,
        LGFX_ERROR_NATIVE_WINDOW_IN_USE_KHR = VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,
        LGFX_SUBOPTIMAL_KHR = VK_SUBOPTIMAL_KHR,
        LGFX_ERROR_OUT_OF_DATE_KHR = VK_ERROR_OUT_OF_DATE_KHR,
        LGFX_ERROR_INCOMPATIBLE_DISPLAY_KHR = VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,
        LGFX_ERROR_VALIDATION_FAILED_EXT = VK_ERROR_VALIDATION_FAILED_EXT,
        LGFX_ERROR_INVALID_SHADER_NV = VK_ERROR_INVALID_SHADER_NV,
        LGFX_ERROR_OUT_OF_POOL_MEMORY_KHR = VK_ERROR_OUT_OF_POOL_MEMORY_KHR,
        LGFX_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR,
    };

    #define LGFX_VK_TO_RESULT(result) static_cast<LGFX_RESULT>(result)

    class Instance;
    class Device;
    class Swapchain;
    class CommandPool;
    class CommandBuffer;

    //--------------------------------------------------------------
    //---
    //--- SwapchainBuilderVulkanImpl
    //---
    //--------------------------------------------------------------
    class SwapchainBuilderVulkanImpl
    {
    public:
        bool checkSurfaceFormats(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats, bool supportHDR);

        bool checkSurfaceCapabilities(
            VkImageUsageFlags& imageUsageFlags,
            VkSurfaceTransformFlagBitsKHR& preTransform,
            VkCompositeAlphaFlagBitsKHR& compsiteAlpha,
            const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

        VkPresentModeKHR getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request);

        static bool defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace);
        static bool defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace);

        static bool defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
        static bool defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);

        Instance* instance_;
        SwapchainCreateInfo swapchainCreateInfo_;
    };

    typedef SwapchainBuilder<SwapchainBuilderVulkanImpl> SwapchainBuilderVulkan;

    //--------------------------------------------------------------
    //---
    //--- BuilderVulkanImpl
    //---
    //--------------------------------------------------------------
    class BuilderVulkanImpl
    {
    public:
        bool checkInstanceExtension(const VkExtensionProperties& properties);

        void checkQueueFamilies(
            u32 queueFamilyIndices[QueueType_Max],
            u32 numQueueFamilies,
            VkQueueFamilyProperties* queueFamilyProperties,
            const bool* queueFamilyPresentationSupports,
            const bool* requests);

        bool checkDeviceExtension(const VkExtensionProperties& properties);

        bool checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);


        bool checkSurfaceFormats(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats, bool supportHDR);

        bool checkSurfaceCapabilities(
            VkImageUsageFlags& imageUsageFlags,
            VkSurfaceTransformFlagBitsKHR& preTransform,
            VkCompositeAlphaFlagBitsKHR& compsiteAlpha,
            const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

        VkPresentModeKHR getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request);

        static bool defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace);
        static bool defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace);

        static bool defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
        static bool defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);

        SwapchainBuilderVulkan createSwapchainBuilder(Instance& instance, const SwapchainCreateInfo& swapchainCreateInfo);
    };

    typedef Builder<BuilderVulkanImpl> BuilderVulkan;

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

        LGFX_RESULT initialize();
        void terminate();
    private:
        Lib(const Lib&) = delete;
        Lib(Lib&&) = delete;
        Lib& operator=(const Lib&) = delete;
        Lib& operator=(Lib&&) = delete;

        LGFX_DLHANDLE handle_;
    };

    inline bool Lib::valid() const
    {
        return LGFX_NULL != handle_;
    }

    //--------------------------------------------------------------
    //---
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------
    /**
    Pysical device wraps VkPhysicalDevice.
    */
    class PhysicalDevice
    {
    public:
        inline PhysicalDevice();
        explicit inline PhysicalDevice(VkPhysicalDevice device);

        inline bool valid() const;
        inline operator const VkPhysicalDevice() const;
        inline operator VkPhysicalDevice();

        inline void swap(PhysicalDevice& rhs);

        /**
        @brief
        */
        void getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& features);

        /**
        @brief
        */
        void getPhysicalDeviceProperties(VkPhysicalDeviceProperties& properties);

        /**
        @brief
        */
        void getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties& formatProperties);

        /**
        @brief
        @return
        */
        LGFX_RESULT enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties);

        /**
        @brief
        @return
        */
        LGFX_RESULT getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties);

        /**
        @brief
        */
        void getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties);

        /**
        @brief
        */
        void getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProperties);

        /**
        @brief
        */
        u32 enumerateDeviceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName);

    private:
        VkPhysicalDevice device_;
    };

    inline PhysicalDevice::PhysicalDevice()
        :device_(LGFX_NULL)
    {}

    inline PhysicalDevice::PhysicalDevice(VkPhysicalDevice device)
        :device_(device)
    {}

    inline bool PhysicalDevice::valid() const
    {
        return LGFX_NULL != device_;
    }

    inline PhysicalDevice::operator const VkPhysicalDevice() const
    {
        return device_;
    }

    inline PhysicalDevice::operator VkPhysicalDevice()
    {
        return device_;
    }

    inline void PhysicalDevice::swap(PhysicalDevice& rhs)
    {
        lgfx::swap(device_, rhs.device_);
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
        static const s32 MaxSwapchainImages = LGFX_MAX_SWAPCHAINMAX;

        static LGFX_RESULT create(Swapchain& swapchain, Device& device, SwapchainBuilderVulkan& builder, const VkAllocationCallbacks* allocator);
        static void destroy(Swapchain& swapchain, Device& device, const VkAllocationCallbacks* allocator);

        Swapchain();
        ~Swapchain();

        inline bool valid() const;
        inline operator const VkSwapchainKHR() const;
        inline operator VkSwapchainKHR();
        void swap(Swapchain& rhs);

        inline s32 getNumImages() const;
        inline VkImage getImage(s32 index);
    private:
        Swapchain(const Swapchain&) = delete;
        Swapchain(Swapchain&&) = delete;
        Swapchain& operator=(const Swapchain&) = delete;
        Swapchain& operator=(Swapchain&&) = delete;

        VkSwapchainKHR swapchain_;
        u32 numImages_;
        VkImage images_[MaxSwapchainImages];
    };

    inline bool Swapchain::valid() const
    {
        return LGFX_NULL != swapchain_;
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
        LGFX_ASSERT(0<=numImages_ && numImages_<MaxSwapchainImages);
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
        explicit CommandPool(VkCommandPool commandPool);
        ~CommandPool();

        inline bool valid() const;
        inline operator const VkCommandPool() const;
        inline operator VkCommandPool();

        void swap(CommandPool& rhs);
    private:
        CommandPool(const CommandPool&) = delete;
        CommandPool(CommandPool&&) = delete;
        CommandPool& operator=(const CommandPool&) = delete;
        CommandPool& operator=(CommandPool&&) = delete;

        VkCommandPool commandPool_;
    };

    inline bool CommandPool::valid() const
    {
        return LGFX_NULL != commandPool_;
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
        explicit CommandBuffer(VkCommandBuffer commandBuffer);
        ~CommandBuffer();

        inline bool valid() const;
        inline operator const VkCommandBuffer() const;
        inline operator VkCommandBuffer();

        void swap(CommandBuffer& rhs);

        inline LGFX_RESULT begin(const VkCommandBufferBeginInfo& beginInfo);
        inline LGFX_RESULT end();
        inline LGFX_RESULT reset(VkCommandBufferResetFlags flags);

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
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer(CommandBuffer&&) = delete;
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        CommandBuffer& operator=(CommandBuffer&&) = delete;

        VkCommandBuffer commandBuffer_;
    };

    inline bool CommandBuffer::valid() const
    {
        return LGFX_NULL != commandBuffer_;
    }

    inline CommandBuffer::operator const VkCommandBuffer() const
    {
        return commandBuffer_;
    }

    inline CommandBuffer::operator VkCommandBuffer()
    {
        return commandBuffer_;
    }

    inline LGFX_RESULT CommandBuffer::begin(const VkCommandBufferBeginInfo& beginInfo)
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT( vkBeginCommandBuffer(commandBuffer_, &beginInfo) );
    }

    inline LGFX_RESULT CommandBuffer::end()
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT( vkEndCommandBuffer(commandBuffer_) );
    }

    inline LGFX_RESULT CommandBuffer::reset(VkCommandBufferResetFlags flags)
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT( vkResetCommandBuffer(commandBuffer_, flags) );
    }

    inline void CommandBuffer::pipelineBarrier(
        VkPipelineStageFlags srcStageMask,
        VkPipelineStageFlags dstStageMask,
        VkDependencyFlags dependencyFlags,
        u32 numMemoryBarriers, const VkMemoryBarrier* memoryBarriers,
        u32 numBufferBarriers, const VkBufferMemoryBarrier* bufferBarriers,
        u32 numImageBarriers, const VkImageMemoryBarrier* imageBarriers)
    {
        LGFX_ASSERT(valid());
        vkCmdPipelineBarrier(commandBuffer_, srcStageMask, dstStageMask, dependencyFlags, numMemoryBarriers, memoryBarriers, numBufferBarriers, bufferBarriers, numImageBarriers, imageBarriers);
    }

    inline void CommandBuffer::fillBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, u32 data)
    {
        LGFX_ASSERT(valid());
        vkCmdFillBuffer(commandBuffer_, buffer, offset , size, data);
    }

    inline void CommandBuffer::updateBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const u32* data)
    {
        LGFX_ASSERT(valid());
        vkCmdUpdateBuffer(commandBuffer_, buffer, offset, size, data);
    }

    inline void CommandBuffer::clearColorImage(VkImage image, VkImageLayout layout, const VkClearColorValue* color, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        LGFX_ASSERT(valid());
        vkCmdClearColorImage(commandBuffer_, image, layout, color, numRanges, ranges);
    }

    inline void CommandBuffer::clearDepthStencilImage(VkImage image, VkImageLayout layout, const VkClearDepthStencilValue* depthStencil, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        LGFX_ASSERT(valid());
        vkCmdClearDepthStencilImage(commandBuffer_, image, layout, depthStencil, numRanges, ranges);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkBuffer dst, u32 numRegions, const VkBufferCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyBuffer(commandBuffer_, src, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkImage dst, VkImageLayout layout, u32 numRegions, const VkBufferImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyBufferToImage(commandBuffer_, src, dst, layout, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout layout, VkBuffer dst, u32 numRegions, const VkBufferImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyImageToBuffer(commandBuffer_, src, layout, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions);
    }

    /**
    */
    inline void CommandBuffer::blit(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageBlit* regions, VkFilter filter)
    {
        LGFX_ASSERT(valid());
        vkCmdBlitImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions, filter);
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
        static LGFX_RESULT create(
            Device& device,
            PhysicalDevice& physicalDevice,
            const VkDeviceCreateInfo& deviceCreateInfo,
            const u32 queueFamilityIndices[QueueType_Max],
            SwapchainBuilderVulkan& swapchainBuilder,
            const VkAllocationCallbacks* allocator);

        static void destroy(
            Device& device,
            const VkAllocationCallbacks* allocator);

        Device();
        ~Device();

        inline bool valid() const;
        inline operator const VkDevice() const;
        inline operator VkDevice();

        inline explicit operator VkPhysicalDevice();

        LGFX_RESULT waitIdle();
        void clearPresentQueue();
        bool onWindowSizeChanged();

        ///**
        //*/
        //LGFX_RESULT createCommandPool(CommandPool& commandPool, const VkCommandPoolCreateInfo& createInfo, const VkAllocationCallbacks* allocator);
        ///**
        //*/
        //void destroyCommandPool(CommandPool& commandPool, const VkAllocationCallbacks* allocator);
        ///**
        //*/
        //LGFX_RESULT resetCommandPool(CommandPool& commandPool, VkCommandPoolResetFlags flags);

        ///**
        //*/
        //LGFX_RESULT allocateCommandBuffers(CommandBuffer* commandBuffers, const VkCommandBufferAllocateInfo& allocateInfo);
        ///**
        //*/
        //void deallocateCommandBuffers(u32 numBuffers, CommandBuffer* commandBuffers, CommandPool& commandPool);

#define LGFX_VK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

    private:
        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) = delete;

        void clear();
        void initialize();
        VkResult createSemaphores(const VkAllocationCallbacks* allocator);

        void destroySemaphores(const VkAllocationCallbacks* allocator);
        void destroyCommandPool();

        VkDevice device_;
        PhysicalDevice physicalDevice_;
        SwapchainBuilderVulkan swapchainBuilder_;
        Swapchain swapchain_;

        VkQueue queues_[QueueType_Max];
        VkSemaphore semaphoreImageAvailable_;
        VkSemaphore semaphoreRenderingFinished_;

        Array<VkCommandBuffer> presentCommandBuffers_;
        VkCommandPool presentCommandPool_;
    };

    inline bool Device::valid() const
    {
        return LGFX_NULL != device_;
    }

    inline Device::operator const VkDevice() const
    {
        return device_;
    }

    inline Device::operator VkDevice()
    {
        return device_;
    }

    inline Device::operator VkPhysicalDevice()
    {
        return (VkPhysicalDevice)physicalDevice_;
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    class Instance
    {
    public:
        static LGFX_RESULT create(
            Instance& instance,
            const VkInstanceCreateInfo& instanceCreateInfo,
            const SurfaceCreateInfo& surfaceCreateInfo,
            const VkAllocationCallbacks* allocator);

        static void destroy(
            Instance& instance,
            const VkAllocationCallbacks* allocator);

        Instance();
        ~Instance();

        inline bool valid() const;
        inline operator const VkInstance() const;
        inline operator VkInstance();

        void swap(Instance& rhs);

        u32 enumeratePhysicalDevices(u32 maxDevices, PhysicalDevice* devices) const;
        inline VkSurfaceKHR getPresentationSurface();

#define LGFX_VK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name;
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

        void initialize();
        VkResult createPresentationSurface(const SurfaceCreateInfo& createInfo, const VkAllocationCallbacks* allocator);

        VkInstance instance_;
        VkSurfaceKHR presentationSurface_;
    };

    inline bool Instance::valid() const
    {
        return LGFX_NULL != instance_;
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

        bool initialize(BuilderVulkan& builder);
        void terminate();

        inline Instance& getInstance();
        inline Device& getDevice(s32 index);
    private:
        System(const System&) = delete;
        System(System&&) = delete;
        System& operator=(const System&) = delete;
        System& operator=(System&&) = delete;

        u32 getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName);

        Lib lib_;
        Instance instance_;
        Device devices_[LGFX_MAX_PHYSICAL_DEVICES];

        const VkAllocationCallbacks* allocator_;
    };

    inline Instance& System::getInstance()
    {
        return instance_;
    }

    inline Device& System::getDevice(s32 index)
    {
        LGFX_ASSERT(0<=index && index<LGFX_MAX_PHYSICAL_DEVICES);
        LGFX_ASSERT(LGFX_NULL != devices_[index]);
        return devices_[index];
    }
}
#endif //INC_LGFX_VULKAN_H_

#ifdef LGFX_VULKAN_IMPLEMENTATION
#ifndef LGFX_VULKAN_IMPLEMENTATION_DONE
#define LGFX_VULKAN_IMPLEMENTATION_DONE
/**
@file lgfx_vulkan.cpp
@author t-sakai
@date 2018/09/19 create
*/

#ifdef _DEBUG
#include <stdio.h>
#ifdef LGFX_REPORT_ERROR
#define PRINT0_ERR(str) fprintf(stderr, str)
#define PRINT1_ERR(str, p0) fprintf(stderr, str, p0)
#else
#define PRINT0_ERR(str)
#define PRINT1_ERR(str, p0)
#endif

#ifdef LGFX_REPORT_WARNING
#define PRINT0_WARN(str) fprintf(stderr, str)
#define PRINT1_WARN(str, p0) fprintf(stderr, str, p0)
#else
#define PRINT0_WARN(str)
#define PRINT1_WARN(str, p0)
#endif

#else
#define PRINT0_ERR(str)
#define PRINT1_ERR(str, p0)
#define PRINT0_WARN(str)
#define PRINT1_WARN(str, p0)
#endif

namespace lgfx
{
//#   define LGFX_VK_EXPORTED_FUNCTION(name) PFN_ ## name name = LGFX_NULL;
//#   include "VkFunctions.inc"

    //--------------------------------------------------------------
    //---
    //--- SwapchainBuilderVulkanImpl
    //---
    //--------------------------------------------------------------
    bool SwapchainBuilderVulkanImpl::checkSurfaceFormats(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats, bool supportHDR)
    {
        if(supportHDR){
            if(defaultCheckSurfaceFormatHDR(dst, size, formats)){
                return true;
            }
        } else{
            if(defaultCheckSurfaceFormatSDR(dst, size, formats)){
                return true;
            }
        }
        return false;
    }


    bool SwapchainBuilderVulkanImpl::checkSurfaceCapabilities(
        VkImageUsageFlags& imageUsageFlags,
        VkSurfaceTransformFlagBitsKHR& preTransform,
        VkCompositeAlphaFlagBitsKHR& compsiteAlpha,
        const VkSurfaceCapabilitiesKHR& surfaceCapabilities)
    {
        return true;
    }

    VkPresentModeKHR SwapchainBuilderVulkanImpl::getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request)
    {
        LGFX_ASSERT(0<size);

        for(u32 i=0; i<size; ++i){
            if(presentModes[i] == request){
                return presentModes[i];
            }
        }
        for(u32 i=0; i<size; ++i){
            if(presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR){
                return presentModes[i];
            }
        }
        for(u32 i=0; i<size; ++i){
            if(presentModes[i] == VK_PRESENT_MODE_FIFO_KHR){
                return presentModes[i];
            }
        }
        return presentModes[0];
    }

    bool SwapchainBuilderVulkanImpl::defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace)
    {
        switch(colorSpace){
        case VK_COLOR_SPACE_SRGB_NONLINEAR_KHR:
        case VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT:
        case VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT:
        case VK_COLOR_SPACE_BT709_NONLINEAR_EXT:
            return true;
        default:
            return false;
        }
    }

    bool SwapchainBuilderVulkanImpl::defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace)
    {
        switch(colorSpace){
        case VK_COLOR_SPACE_BT2020_LINEAR_EXT:
        case VK_COLOR_SPACE_HDR10_ST2084_EXT:
        case VK_COLOR_SPACE_HDR10_HLG_EXT:
        case VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT:
            return true;
        default:
            return false;
        }
    }

    bool SwapchainBuilderVulkanImpl::defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
    {
        VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_MAX_ENUM_KHR;
        for(u32 i=0; i<size; ++i){
            if(defaultSupportedColorSpaceSDR(formats[i].colorSpace)){
                colorSpace = formats[i].colorSpace;
                break;
            }
        }
        if(VK_COLOR_SPACE_MAX_ENUM_KHR == colorSpace){
            return false;
        }

        VkFormat format = VK_FORMAT_UNDEFINED;
        for(u32 i=0; i<size; ++i){
            if(!defaultSupportedColorSpaceSDR(formats[i].colorSpace)){
                continue;
            }
            if(VK_FORMAT_B8G8R8A8_SRGB == formats[i].format
                || VK_FORMAT_R8G8B8A8_SRGB == formats[i].format){
                format = formats[i].format;
                break;
            }
        }
        if(VK_FORMAT_UNDEFINED != format){
            dst ={format, colorSpace};
            return true;
        }

        for(u32 i=0; i<size; ++i){
            if(!defaultSupportedColorSpaceSDR(formats[i].colorSpace)){
                continue;
            }
            if(VK_FORMAT_B8G8R8A8_UNORM == formats[i].format
                || VK_FORMAT_R8G8B8A8_UNORM == formats[i].format){
                format = formats[i].format;
                break;
            }
        }
        if(VK_FORMAT_UNDEFINED != format){
            dst ={format, colorSpace};
            return true;
        }
        return false;
    }

    bool SwapchainBuilderVulkanImpl::defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
    {
        LGFX_ASSERT(0<size);

        //Find a format supports the HDR color space
        VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_MAX_ENUM_KHR;
        for(u32 i=0; i<size; ++i){
            if(defaultSupportedColorSpaceHDR(formats[i].colorSpace)){
                colorSpace = formats[i].colorSpace;
                break;
            }
        }
        if(VK_COLOR_SPACE_MAX_ENUM_KHR == colorSpace){
            return defaultCheckSurfaceFormatSDR(dst, size, formats);
        }

        VkFormat format = VK_FORMAT_UNDEFINED;
        for(u32 i=0; i<size; ++i){
            if(!defaultSupportedColorSpaceHDR(formats[i].colorSpace)){
                continue;
            }
            if(VK_FORMAT_A2R10G10B10_UNORM_PACK32 == formats[i].format
                || VK_FORMAT_A2B10G10R10_UNORM_PACK32 == formats[i].format){
                format = formats[i].format;
                break;
            }
        }
        if(VK_FORMAT_UNDEFINED != format){
            dst ={format, colorSpace};
            return true;
        }

        for(u32 i=0; i<size; ++i){
            if(!defaultSupportedColorSpaceHDR(formats[i].colorSpace)){
                continue;
            }
            if(VK_FORMAT_R16G16B16A16_UNORM == formats[i].format){
                format = formats[i].format;
                break;
            }
        }
        if(VK_FORMAT_UNDEFINED != format){
            dst ={format, colorSpace};
            return true;
        }
        return defaultCheckSurfaceFormatSDR(dst, size, formats);
    }

    //--------------------------------------------------------------
    //---
    //--- BuilderVulkanImpl
    //---
    //--------------------------------------------------------------
    namespace
    {
        bool acceptQueueFamily(u32& queueFamilyIndex, u32 index, VkQueueFamilyProperties& properties, VkQueueFlagBits queueFlag)
        {
            if(QueueType_Invalid != queueFamilyIndex){
                return true;
            }
            if((0<properties.queueCount)
                && (properties.queueFlags & queueFlag)){
                --properties.queueCount;
                queueFamilyIndex = index;
                return true;
            }
            return false;
        }
    }

    bool BuilderVulkanImpl::checkInstanceExtension(const VkExtensionProperties& /*properties*/)
    {
        return true;
    }

    void BuilderVulkanImpl::checkQueueFamilies(
        u32 queueFamilyIndices[QueueType_Max],
        u32 numQueueFamilies,
        VkQueueFamilyProperties* queueFamilyProperties,
        const bool* queueFamilyPresentationSupports,
        const bool* requests)
    {
        for(u32 i=0; i<numQueueFamilies; ++i){
            if(QueueType_Invalid == queueFamilyIndices[QueueType_Present]
                && 0<queueFamilyProperties[i].queueCount
                && queueFamilyPresentationSupports[i]){
                --queueFamilyProperties[i].queueCount;
                queueFamilyIndices[QueueType_Present] = i;
            }

            acceptQueueFamily(queueFamilyIndices[QueueType_Graphics], i, queueFamilyProperties[i], VK_QUEUE_GRAPHICS_BIT);

            if(requests[QueueType_Compute]){
                acceptQueueFamily(queueFamilyIndices[QueueType_Compute], i, queueFamilyProperties[i], VK_QUEUE_COMPUTE_BIT);
            }
            if(requests[QueueType_Transfer]){
                acceptQueueFamily(queueFamilyIndices[QueueType_Transfer], i, queueFamilyProperties[i], VK_QUEUE_TRANSFER_BIT);
            }
            if(requests[QueueType_SparceBinding]){
                acceptQueueFamily(queueFamilyIndices[QueueType_SparceBinding], i, queueFamilyProperties[i], VK_QUEUE_SPARSE_BINDING_BIT);
            }
        }
    }

    bool BuilderVulkanImpl::checkDeviceExtension(const VkExtensionProperties& /*properties*/)
    {
        return true;
    }

    bool BuilderVulkanImpl::checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported)
    {
        dst = supported;
        return true;
    }

    SwapchainBuilderVulkan BuilderVulkanImpl::createSwapchainBuilder(Instance& instance, const SwapchainCreateInfo& swapchainCreateInfo)
    {
        SwapchainBuilderVulkan swapchainBuilder;
        swapchainBuilder.instance_ = &instance;
        swapchainBuilder.swapchainCreateInfo_ = swapchainCreateInfo;
        return swapchainBuilder;
    }

    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    Lib::Lib()
        :handle_(LGFX_NULL)
    {}

    Lib::~Lib()
    {
        terminate();
    }

    LGFX_RESULT Lib::initialize()
    {
        if(LGFX_NULL != handle_){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }
        handle_ = LGFX_DLOPEN(LGFX_VULKANLIB);
        if(LGFX_NULL == handle_){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

#define LGFX_VK_EXPORTED_FUNCTION(name) LGFX_VK_GET_FUNCTION(name, "Error: cannot get exported %s\n")

#define LGFX_VK_GET_FUNCTION(name, message) name = (PFN_ ## name)LGFX_DLSYM(handle_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_ERR(message, #name);\
        return LGFX_ERROR_INITIALIZATION_FAILED;\
    }

#define LGFX_VK_GET_FUNCTION_WARN(name, message) name = (PFN_ ## name)LGFX_DLSYM(handle_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_WARN(message, #name);\
    }

#include "VkFunctions.inc"

        return LGFX_SUCCESS;
    }

    void Lib::terminate()
    {
        if(LGFX_NULL == handle_){
            return;
        }

#define LGFX_VK_EXPORTED_FUNCTION(name) name = LGFX_NULL;
#include "VkFunctions.inc"

        LGFX_DLCLOSE(handle_);
        handle_ = LGFX_NULL;
    }
    //--------------------------------------------------------------
    //---
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------
    void PhysicalDevice::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& features)
    {
        vkGetPhysicalDeviceFeatures(device_, &features);
    }

    void PhysicalDevice::getPhysicalDeviceProperties(VkPhysicalDeviceProperties& properties)
    {
        vkGetPhysicalDeviceProperties(device_, &properties);
    }

    void PhysicalDevice::getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties& formatProperties)
    {
        vkGetPhysicalDeviceFormatProperties(device_, format, &formatProperties);
    }

    LGFX_RESULT PhysicalDevice::enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties)
    {
        return LGFX_VK_TO_RESULT( vkEnumerateDeviceLayerProperties(device_, propertyCount, properties) );
    }

    LGFX_RESULT PhysicalDevice::getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties)
    {
        return LGFX_VK_TO_RESULT( vkGetPhysicalDeviceImageFormatProperties(device_, format, type, tiling, usage, flags, &imageFormatProperties) );
    }

    void PhysicalDevice::getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties)
    {
        vkGetPhysicalDeviceSparseImageFormatProperties(device_, format, type, samples, usage, tiling, propertyCount, properties);
    }

    void PhysicalDevice::getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProperties)
    {
        vkGetPhysicalDeviceMemoryProperties(device_, &memoryProperties);
    }

    u32 PhysicalDevice::enumerateDeviceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName)
    {
        vkEnumerateDeviceExtensionProperties(device_, layerName, &maxExtensions, extensionProperties);
        return maxExtensions;
    }

    //--------------------------------------------------------------
    //---
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    LGFX_RESULT Swapchain::create(Swapchain& swapchain, Device& device, SwapchainBuilderVulkan& builder, const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(device.valid());

        VkSurfaceCapabilitiesKHR surfaceCapabilities;

        u32 swapChainCount;
        VkExtent2D surfaceExtent;
        VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        VkSurfaceTransformFlagBitsKHR imagePreTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        VkPresentModeKHR presentMode;
        VkSurfaceFormatKHR surfaceFormat;

        VkPhysicalDevice physicalDevice = (VkPhysicalDevice)device;
        Instance& instance = *builder.instance_;
        const SwapchainCreateInfo& swapchainCreateInfo = builder.swapchainCreateInfo_;
        VkSurfaceKHR presentationSurface = instance.getPresentationSurface();

        VkResult result;
        //--- Check surface capabilities
        //-------------------------------------------------------------
        result = instance.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, presentationSurface, &surfaceCapabilities);
        if(VK_SUCCESS != result){
            return LGFX_VK_TO_RESULT(result);
        }

        //Check swap chain image count
        swapChainCount = clamp(swapchainCreateInfo.swapchainCount_, surfaceCapabilities.minImageCount, surfaceCapabilities.maxImageCount);

        //Check image extent
        if(-1 != surfaceCapabilities.currentExtent.width){
            surfaceExtent = surfaceCapabilities.currentExtent;
        } else{
            surfaceExtent.width = clamp(swapchainCreateInfo.width_, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
            surfaceExtent.height = clamp(swapchainCreateInfo.height_, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
        }

        //Check usage flags
        if(VK_IMAGE_USAGE_TRANSFER_DST_BIT != (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }
        imageUsageFlags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        imagePreTransform = surfaceCapabilities.currentTransform;
        if(!builder.checkSurfaceCapabilities(imageUsageFlags, imagePreTransform, compositeAlpha, surfaceCapabilities)){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

        //--- Check present modes
        //-------------------------------------------------------------
        VkPresentModeKHR presentModes[LGFX_MAX_PRESENTMODES];
        u32 countPresentModes = LGFX_MAX_PRESENTMODES;
        result = instance.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, presentationSurface, &countPresentModes, presentModes);
        if(VK_SUCCESS != result || countPresentModes<=0){
            return LGFX_VK_TO_RESULT(result);
        }
        presentMode = builder.getPresentMode(countPresentModes, presentModes, static_cast<VkPresentModeKHR>(swapchainCreateInfo.presentMode_));

        //--- Check surface formats
        //-------------------------------------------------------------
        VkSurfaceFormatKHR surfaceFormats[LGFX_MAX_SURFACEFORMATS];
        u32 countSurfaceFormats = LGFX_MAX_SURFACEFORMATS;
        result = instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, presentationSurface, &countSurfaceFormats, surfaceFormats);
        if(VK_SUCCESS != result || countSurfaceFormats<=0){
            return LGFX_VK_TO_RESULT(result);
        }
        if(!builder.checkSurfaceFormats(surfaceFormat, countSurfaceFormats, surfaceFormats, swapchainCreateInfo.supportHDR_)){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

        VkSwapchainCreateInfoKHR createInfo = {
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, //structure type
            LGFX_NULL, //must be null
            0, //swapchain create flags, must set to 0
            presentationSurface,
            swapChainCount, //swapchain image count
            surfaceFormat.format,
            surfaceFormat.colorSpace,
            surfaceExtent,
            1, //the number of views in a multiview or stereo surface
            imageUsageFlags,
            VK_SHARING_MODE_EXCLUSIVE, //sharing mode
            0, //the number of queue family indices when imageSharingMode equals VK_SHARING_MODE_CONCURRENT
            LGFX_NULL, //an arrays of queue family indices when imageSharingMode equals VK_SHARING_MODE_CONCURRENT
            imagePreTransform,
            compositeAlpha,
            presentMode,
            VK_TRUE,
            LGFX_NULL,
        };


        if(LGFX_NULL != swapchain.swapchain_){
            createInfo.oldSwapchain = swapchain.swapchain_;
        }

        VkSwapchainKHR vkSwapchain = LGFX_NULL;
        if(VK_SUCCESS != (result = device.vkCreateSwapchainKHR(device, &createInfo, allocator, &vkSwapchain))){
            createInfo.oldSwapchain = LGFX_NULL;
            return LGFX_VK_TO_RESULT(result);
        }

        destroy(swapchain, device, allocator);
        swapchain.swapchain_ = vkSwapchain;

        swapchain.numImages_ = MaxSwapchainImages;
        if(VK_SUCCESS != (result = device.vkGetSwapchainImagesKHR(device, swapchain.swapchain_, &swapchain.numImages_, swapchain.images_))){
            Swapchain::destroy(swapchain, device, allocator);
            return LGFX_VK_TO_RESULT(result);
        }
        LGFX_ASSERT(0<swapchain.numImages_);
        return LGFX_SUCCESS;
    }

    void Swapchain::destroy(Swapchain& swapchain, Device& device, const VkAllocationCallbacks* allocator)
    {
        if(LGFX_NULL == swapchain.swapchain_){
            return;
        }
        device.vkDestroySwapchainKHR(device, swapchain.swapchain_, allocator);

        swapchain.numImages_ = 0;
        swapchain.swapchain_ = LGFX_NULL;
    }

    Swapchain::Swapchain()
        :swapchain_(LGFX_NULL)
        ,numImages_(0)
    {}

    Swapchain::~Swapchain()
    {}

    void Swapchain::swap(Swapchain& rhs)
    {
        lgfx::swap(swapchain_, rhs.swapchain_);
        lgfx::swap(numImages_, rhs.numImages_);
        for(s32 i=0; i<MaxSwapchainImages; ++i){
            lgfx::swap(images_[i], rhs.images_[i]);
        }
    }

    //--------------------------------------------------------------
    //---
    //--- CommandPool
    //---
    //--------------------------------------------------------------
    CommandPool::CommandPool()
        :commandPool_(LGFX_NULL)
    {}

    CommandPool::CommandPool(VkCommandPool commandPool)
        :commandPool_(commandPool)
    {}

    CommandPool::~CommandPool()
    {}

    void CommandPool::swap(CommandPool& rhs)
    {
        lgfx::swap(commandPool_, rhs.commandPool_);
    }

    //--------------------------------------------------------------
    //---
    //--- CommandBuffer
    //---
    //--------------------------------------------------------------
    CommandBuffer::CommandBuffer()
        :commandBuffer_(LGFX_NULL)
    {}

    CommandBuffer::CommandBuffer(VkCommandBuffer commandBuffer)
        :commandBuffer_(commandBuffer)
    {}

    CommandBuffer::~CommandBuffer()
    {}

    void CommandBuffer::swap(CommandBuffer& rhs)
    {
        lgfx::swap(commandBuffer_, rhs.commandBuffer_);
    }

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    Device::Device()
        :device_(LGFX_NULL)
        ,presentCommandPool_(LGFX_NULL)
#define LGFX_VK_EXT_DEVICE_FUNCTION(name) ,name(LGFX_NULL)
#include "VkFunctions.inc"
    {
        //clearColor_ = {0x00U, 0x00U, 0x00U, 0xFFU};
        for(u32 i=0; i<QueueType_Max; ++i){
            queues_[i] = LGFX_NULL;
        }
    }

    Device::~Device()
    {
#define LGFX_VK_EXT_DEVICE_FUNCTION(name) name = LGFX_NULL;
#include "VkFunctions.inc"
    }

    LGFX_RESULT Device::create(
        Device& device,
        PhysicalDevice& physicalDevice,
        const VkDeviceCreateInfo& deviceCreateInfo,
        const u32 queueFamilityIndices[QueueType_Max],
        SwapchainBuilderVulkan& swapchainBuilder,
        const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(physicalDevice.valid());
        LGFX_ASSERT(0<deviceCreateInfo.queueCreateInfoCount);

        if(device.valid()){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }
        VkResult result;
        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return LGFX_VK_TO_RESULT(result);
        }
        device.physicalDevice_ = physicalDevice;
        device.initialize();

        result = static_cast<VkResult>(Swapchain::create(device.swapchain_, device, swapchainBuilder, allocator));
        if(VK_SUCCESS != result){
            vkDestroyDevice(device.device_, allocator);
            device.clear();
            return LGFX_VK_TO_RESULT(result);
        }

        //Get queues
        //----------------------------------
        u32 queueIndices[QueueType_Max];
        memset(queueIndices, 0, sizeof(u32)*QueueType_Max);

        for(u32 i=0; i<QueueType_Max; ++i){
            u32 queueFamilyIndex = queueFamilityIndices[i];
            if(QueueType_Invalid == queueFamilyIndex){
                continue;
            }
            vkGetDeviceQueue(device, queueFamilyIndex, queueIndices[queueFamilyIndex], &device.queues_[i]);
            ++queueIndices[queueFamilyIndex];
        }


        result = device.createSemaphores(allocator);
        if(VK_SUCCESS != result){
            Swapchain::destroy(device.swapchain_, device, allocator);
            vkDestroyDevice(device.device_, allocator);
            device.clear();
            return LGFX_VK_TO_RESULT(result);
        }
        device.swapchainBuilder_ = swapchainBuilder;
        return LGFX_VK_TO_RESULT(result);
    }

    void Device::destroy(Device& device, const VkAllocationCallbacks* allocator)
    {
        if(!device.valid()){
            return;
        }
        device.waitIdle();

        device.destroyCommandPool();
        device.destroySemaphores(allocator);

        Swapchain::destroy(device.swapchain_, device, allocator);
        vkDestroyDevice(device.device_, allocator);
        device.clear();
    }

    LGFX_RESULT Device::waitIdle()
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        return LGFX_VK_TO_RESULT(vkDeviceWaitIdle(device_));
    }

    void Device::clearPresentQueue()
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        vkDeviceWaitIdle(device_);

        destroyCommandPool();
    }

#if 0
    VkResult Device::createCommandPool(CommandPool& commandPool, const VkCommandPoolCreateInfo& createInfo, const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        if(commandPool.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        VkResult result;
        if(VK_SUCCESS != (result = vkCreateCommandPool(device_, &createInfo, allocator, &commandPool.commandPool_))){
            return result;
        }
        return VK_SUCCESS;
    }

    void Device::destroyCommandPool(CommandPool& commandPool, const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        if(commandPool.valid()){
            vkDestroyCommandPool(device_, commandPool.commandPool_, allocator);
            commandPool.commandPool_ = LGFX_NULL;
        }
    }

    VkResult Device::resetCommandPool(CommandPool& commandPool, VkCommandPoolResetFlags flags)
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        LGFX_ASSERT(commandPool.valid());
        return vkResetCommandPool(device_, commandPool.commandPool_, flags);
    }


    VkResult Device::allocateCommandBuffers(CommandBuffer* commandBuffers, const VkCommandBufferAllocateInfo& allocateInfo)
    {
        LGFX_ASSERT(0<=allocateInfo.commandBufferCount && allocateInfo.commandBufferCount<=MaxCommandBuffers);
#ifdef _DEBUG
        for(u32 i=0; i<allocateInfo.commandBufferCount; ++i){
            if(commandBuffers[i].valid()){
                return VK_ERROR_INITIALIZATION_FAILED;
            }
        }
#endif
        VkCommandBuffer buffers[MaxCommandBuffers];
        VkResult result;
        if(VK_SUCCESS != (result = vkAllocateCommandBuffers(device_, &allocateInfo, buffers))){
            return result;
        }
        for(u32 i=0; i<allocateInfo.commandBufferCount; ++i){
            commandBuffers[i].commandBuffer_ = buffers[i];
        }
        return VK_SUCCESS;
    }

    void Device::deallocateCommandBuffers(u32 numBuffers, CommandBuffer* commandBuffers, CommandPool& commandPool)
    {
        LGFX_ASSERT(0<=numBuffers && numBuffers<=MaxCommandBuffers);
        LGFX_ASSERT(commandPool.valid());

        VkCommandBuffer buffers[MaxCommandBuffers];
        for(u32 i=0; i<numBuffers; ++i){
            buffers[i] = commandBuffers[i].commandBuffer_;
            commandBuffers[i].commandBuffer_ = LGFX_NULL;
        }

        vkFreeCommandBuffers(device_, commandPool, numBuffers, buffers);
    }
#endif

#if 0
    VkResult Device::createCommandBuffers()
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        VkResult result;

        VkCommandPoolCreateInfo commandPoolCreateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            LGFX_NULL,
            0,
            queueFamilyIndices_[PresentQueue],
        };
        if(VK_SUCCESS != (result = vkCreateCommandPool(device_, &commandPoolCreateInfo, allocator_, &presentQueueCommandPool_))){
            return result;
        }

        VkCommandBufferAllocateInfo commandBufferAllocateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            LGFX_NULL,
            presentQueueCommandPool_,
            VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            swapchainImageCount_,
        };
        if(VK_SUCCESS != (result = vkAllocateCommandBuffers(device_, &commandBufferAllocateInfo, presentQueueCommandBuffers_))){
            return result;
        }
        if(VK_SUCCESS != (result = recordCommandBuffers())){
            return result;
        }
        return VK_SUCCESS;
    }

    VkResult Device::clearCommandBuffers()
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        LGFX_ASSERT(LGFX_NULL != swapchain_);

        VkResult result;
        if(VK_SUCCESS != (result = vkDeviceWaitIdle(device_))){
            return result;
        }

        if(0<swapchainImageCount_){
            vkFreeCommandBuffers(device_, presentQueueCommandPool_, swapchainImageCount_, presentQueueCommandBuffers_);
            swapchainImageCount_ = 0;
        }

        if(LGFX_NULL != presentQueueCommandPool_){
            vkDestroyCommandPool(device_, presentQueueCommandPool_, allocator_);
            presentQueueCommandPool_ = LGFX_NULL;
        }
        return VK_SUCCESS;
    }

    VkResult Device::recordCommandBuffers()
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        LGFX_ASSERT(LGFX_NULL != swapchain_);
        VkResult result;
        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR_(device_, swapchain_, &swapchainImageCount_, swapchainImages_))){
            return result;
        }
        VkCommandBufferBeginInfo commandBufferBeginInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, //structure type
            LGFX_NULL,
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, //flags
            LGFX_NULL,
        };
        VkImageSubresourceRange imageSubresourceRange =
        {
            VK_IMAGE_ASPECT_COLOR_BIT, //flags
            0, 1, 0, 1,
        };

        VkImageMemoryBarrier barrierFromPresentToClear =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            LGFX_NULL,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            LGFX_NULL,
            imageSubresourceRange,
        };

        VkImageMemoryBarrier barrierFromClearToPresent =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            LGFX_NULL,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            LGFX_NULL,
            imageSubresourceRange,
        };

        for(u32 i=0; i<swapchainImageCount_; ++i){
            barrierFromPresentToClear.image = swapchainImages_[i];
            barrierFromClearToPresent.image = swapchainImages_[i];

            vkBeginCommandBuffer(presentQueueCommandBuffers_[i], &commandBufferBeginInfo);
            vkCmdPipelineBarrier(
                presentQueueCommandBuffers_[i],
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                0, 0,
                LGFX_NULL,
                0,
                LGFX_NULL,
                1,
                &barrierFromPresentToClear);

            vkCmdClearColorImage(
                presentQueueCommandBuffers_[i],
                swapchainImages_[i],
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                &clearColor_,
                1,
                &imageSubresourceRange);

            vkCmdPipelineBarrier(
                presentQueueCommandBuffers_[i],
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                0, 0,
                LGFX_NULL,
                0,
                LGFX_NULL,
                1,
                &barrierFromClearToPresent);
            if(VK_SUCCESS != (result = vkEndCommandBuffer(presentQueueCommandBuffers_[i]))){
                return result;
            }
        }
        return result;
    }

    bool Device::present()
    {
        VkResult result;
        u32 imageIndex;
        result = vkAcquireNextImageKHR_(device_, swapchain_, UINT64_MAX, semaphoreImageAvailable_, LGFX_NULL, &imageIndex);
        switch(result)
        {
        case VK_SUCCESS:
        case VK_SUBOPTIMAL_KHR:
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
            return onWindowSizeChanged();
        default:
            return false;
        }

        VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        VkSubmitInfo submitInfo =
        {
            VK_STRUCTURE_TYPE_SUBMIT_INFO, //structure type
            LGFX_NULL,
            1,
            &semaphoreImageAvailable_,
            &waitDstStageMask,
            1,
            &presentQueueCommandBuffers_[imageIndex],
            1,
            &semaphoreRenderingFinished_,
        };
        if(VK_SUCCESS != (result = vkQueueSubmit(queues_[PresentQueue], 1, &submitInfo, LGFX_NULL))){
            return false;
        }

        VkPresentInfoKHR presentInfo =
        {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            LGFX_NULL,
            1,
            &semaphoreRenderingFinished_,
            1,
            &swapchain_,
            &imageIndex,
            LGFX_NULL,
        };
        result = vkQueuePresentKHR_(queues_[PresentQueue], &presentInfo);
        switch(result)
        {
        case VK_SUCCESS:
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
        case VK_SUBOPTIMAL_KHR:
            return onWindowSizeChanged();
        default:
            return false;
        }
        return true;
    }

    bool Device::onWindowSizeChanged()
    {
        clearCommandBuffers();

        swapchainCreateInfo_.oldSwapchain = swapchain_;
        if(VK_SUCCESS != createSwapchain(swapchainCreateInfo_)){
            return false;
        }
        if(VK_SUCCESS != createCommandBuffers()){
            return false;
        }
        return true;
    }
#endif

    void Device::clear()
    {
        presentCommandPool_ = LGFX_NULL;
        presentCommandBuffers_.clear();
        semaphoreRenderingFinished_ = LGFX_NULL;
        semaphoreImageAvailable_ = LGFX_NULL;
        for(s32 i=0; i<QueueType_Max; ++i){
            queues_[i] = LGFX_NULL;
        }
        Swapchain().swap(swapchain_);
        swapchainBuilder_.instance_ = LGFX_NULL;
        PhysicalDevice().swap(physicalDevice_);
        device_ = LGFX_NULL;
    }

    void Device::initialize()
    {
        LGFX_ASSERT(LGFX_NULL != device_);

#define LGFX_VK_EXT_DEVICE_FUNCTION(name) if(LGFX_NULL == name) name = (PFN_ ## name)vkGetDeviceProcAddr(device_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_WARN("Warning: cannot get device function %s via vkGetDeviceProcAddr\n", #name);\
    }
#include "VkFunctions.inc"
    }

    VkResult Device::createSemaphores(const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        VkResult result;
        // create semaphores
        VkSemaphoreCreateInfo semaphoreCreateInfo =
        {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, //structure type
            LGFX_NULL,
            0,//flags
        };

        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator, &semaphoreImageAvailable_))){
            return result;
        }
        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator, &semaphoreRenderingFinished_))){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator);
            semaphoreImageAvailable_ = LGFX_NULL;
            return result;
        }

        return result;
    }

    void Device::destroySemaphores(const VkAllocationCallbacks* allocator)
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        if(LGFX_NULL != semaphoreRenderingFinished_){
            vkDestroySemaphore(device_, semaphoreRenderingFinished_, allocator);
            semaphoreRenderingFinished_ = LGFX_NULL;
        }
        if(LGFX_NULL != semaphoreImageAvailable_){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator);
            semaphoreImageAvailable_ = LGFX_NULL;
        }
    }

    void Device::destroyCommandPool()
    {
        if(0<presentCommandBuffers_.size()){
            vkFreeCommandBuffers(device_, presentCommandPool_, static_cast<u32>(presentCommandBuffers_.size()), &presentCommandBuffers_[0]); 
            presentCommandBuffers_.clear();
        }
        if(LGFX_NULL != presentCommandPool_){
            vkDestroyCommandPool(device_, presentCommandPool_, LGFX_NULL);
            presentCommandPool_ = LGFX_NULL;
        }
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(LGFX_NULL)
        ,presentationSurface_(LGFX_NULL)
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
        const SurfaceCreateInfo& surfaceCreateInfo,
        const VkAllocationCallbacks* allocator)
    {
        if(instance.valid()){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result;
        result = vkCreateInstance(&instanceCreateInfo, allocator, &instance.instance_);
        if(VK_SUCCESS != result){
            return LGFX_VK_TO_RESULT(result);
        }

        instance.initialize();

        result = instance.createPresentationSurface(surfaceCreateInfo, allocator);
        if(VK_SUCCESS != result){
            vkDestroyInstance(instance.instance_, allocator);
            instance.instance_ = LGFX_NULL;
            return LGFX_VK_TO_RESULT(result);
        }
        return LGFX_SUCCESS;
    }

    void Instance::destroy(Instance& instance, const VkAllocationCallbacks* allocator)
    {
        if(!instance.valid()){
            return;
        }

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

    VkResult Instance::createPresentationSurface(const SurfaceCreateInfo& createInfo, const VkAllocationCallbacks* allocator)
    {
        if(LGFX_NULL != presentationSurface_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
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

    //--------------------------------------------------------------
    //---
    //--- System
    //---
    //--------------------------------------------------------------
    namespace
    {
        template<class T>
        void init(u32 size, T* array, T value)
        {
            for(u32 i=0; i<size; ++i){
                array[i] = value;
            }
        }

        u32 createQueueCreateInfo(VkDeviceQueueCreateInfo* createInfo, u32 queueFamilyIndices[QueueType_Max], f32 queuePriorities[QueueType_Max][QueueType_Max])
        {
            u32 queueCount[QueueType_Max];
            memset(queueCount, 0, sizeof(u32)*QueueType_Max);

            for(u32 i=0; i<QueueType_Max; ++i){
                if(QueueType_Invalid == queueFamilyIndices[i]){
                    continue;
                }
                ++queueCount[queueFamilyIndices[i]];
            }
            u32 count = 0;
            for(u32 i=0; i<QueueType_Max; ++i){
                if(queueCount[i]<=0){
                    continue;
                }
                createInfo[count].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; //structure type
                createInfo[count].pNext = LGFX_NULL; //next. must be null
                createInfo[count].flags = 0; //device queue creation flags. must set to 0
                createInfo[count].queueFamilyIndex = i;
                createInfo[count].queueCount = queueCount[i];
                createInfo[count].pQueuePriorities = queuePriorities[i];
                for(u32 j=0; j<queueCount[i]; ++j){
                    queuePriorities[count][j] = j*0.1f;
                }
                ++count;
            }
            return count;
        }
    }

    System::System()
    {
    }

    System::~System()
    {
        terminate();
    }

    bool System::initialize(BuilderVulkan& builder)
    {
        if(VK_SUCCESS != lib_.initialize()){
            return false;
        }

        //Create Instance
        {
            InstanceCreateInfo& instanceCreateInfo = builder.instanceCreateInfo_;
            u32 enabledExtensionCount = 0;
            VkExtensionProperties extensionProperties[LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES];
            const Char* enabledExtensionNames[LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES];

            u32 numExtensionProperties = getInstanceExtensionProperties(LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES, extensionProperties, instanceCreateInfo.layerName_);

            for(u32 i=0; i<numExtensionProperties; ++i){
                if(!builder.checkInstanceExtension(extensionProperties[i])){
                    continue;
                }
                enabledExtensionNames[enabledExtensionCount++] = extensionProperties[i].extensionName;
            }

            VkApplicationInfo vkApplicationInfo = {
                VK_STRUCTURE_TYPE_APPLICATION_INFO, //structure type
                LGFX_NULL, //must be null
                instanceCreateInfo.applicationName_, //application name
                instanceCreateInfo.applicationVersion_, //application version
                instanceCreateInfo.engineName_, //engine name
                instanceCreateInfo.engineVersion_, //engine version
                instanceCreateInfo.apiVersion_, //api version
            };

            VkInstanceCreateInfo vkInstanceCreateInfo = {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //structure type
                LGFX_NULL, //must be null
                0, //instance creation flags. must set to 0
                &vkApplicationInfo, //application info
                instanceCreateInfo.enabledLayerCount_, //enabled layer count
                instanceCreateInfo.enabledLayerNames_, //enabled layer names
                enabledExtensionCount, //enabled extension count
                enabledExtensionNames, //enabled extension names
            };
            if(VK_SUCCESS != Instance::create(instance_, vkInstanceCreateInfo, builder.surfaceCreateInfo_, builder.allocator_)){
                return false;
            }
        }

        //Create device
        {
            const DeviceCreateInfo& deviceCreateInfo = builder.deviceCreateInfo_;
            SwapchainBuilderVulkan swapchainBuilder = builder.createSwapchainBuilder(instance_, builder.swapchainCreateInfo_);

            //Queue families
            u32 numQueueFamilyProperties;
            VkQueueFamilyProperties queueFamilyProperties[LGFX_MAX_QUEUE_FAMILY_PROPERTIES];
            bool queueFamilyPresentationSupports[LGFX_MAX_QUEUE_FAMILY_PROPERTIES];

            //Extensions
            u32 enabledExtensionCount;
            const Char* enabledExtensionNames[LGFX_MAX_DEVICE_EXTENSION_PROPERTIES];

            //Physical device features
            VkPhysicalDeviceFeatures features;
            VkPhysicalDeviceFeatures* enabledFeatures = LGFX_NULL;

            //Surface capabilities
            VkSurfaceCapabilitiesKHR surfaceCapabilities;
            u32 swapChainCount;
            VkExtent2D surfaceExtent;
            VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            VkSurfaceTransformFlagBitsKHR imagePreTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
            VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            VkPresentModeKHR presentMode;
            VkSurfaceFormatKHR surfaceFormat;

            PhysicalDevice physicalDevices[LGFX_MAX_PHYSICAL_DEVICES];
            u32 numPhysicalDevices = instance_.enumeratePhysicalDevices(LGFX_MAX_PHYSICAL_DEVICES, physicalDevices);

            u32 countDevice = 0;
            for(; countDevice<numPhysicalDevices; ++countDevice){
                PhysicalDevice physicalDevice = physicalDevices[countDevice];

                //--- Device
                //----------------------------------------------------------
                //Select queues for graphics and presentation
                //Get queue properties
                u32 queueFamilyIndices[QueueType_Max];
                init(QueueType_Max, queueFamilyIndices, static_cast<u32>(QueueType_Invalid));

                numQueueFamilyProperties = LGFX_MAX_QUEUE_FAMILY_PROPERTIES;
                vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &numQueueFamilyProperties, queueFamilyProperties);

                for(u32 j = 0; j<numQueueFamilyProperties; ++j){
                    queueFamilyPresentationSupports[j] = instance_.getPhysicalDevicePresentationSurfaceSupport(physicalDevice, j);
                }
                builder.checkQueueFamilies(queueFamilyIndices, numQueueFamilyProperties, queueFamilyProperties, queueFamilyPresentationSupports, deviceCreateInfo.requestQueueTypes_);

                if(QueueType_Invalid == queueFamilyIndices[QueueType_Present] || QueueType_Invalid == queueFamilyIndices[QueueType_Graphics]){
                    continue;
                }

                //Check device extensions
                VkExtensionProperties deviceExtensionProperties[LGFX_MAX_DEVICE_EXTENSION_PROPERTIES];
                u32 numExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties(LGFX_MAX_DEVICE_EXTENSION_PROPERTIES, deviceExtensionProperties, deviceCreateInfo.layerName_);
                enabledExtensionCount = 0;
                for(u32 i = 0; i<numExtensionProperties; ++i){
                    if(!builder.checkDeviceExtension(deviceExtensionProperties[i])){
                        continue;
                    }
                    enabledExtensionNames[enabledExtensionCount++] = deviceExtensionProperties[i].extensionName;
                }

                //Check device features
                VkPhysicalDeviceFeatures supported;
                physicalDevice.getPhysicalDeviceFeatures(supported);
                memset(&features, 0, sizeof(VkPhysicalDeviceFeatures));
                if(!builder.checkDeviceFeatures(features, supported)){
                    continue;
                }
                enabledFeatures = &features;

                VkDeviceQueueCreateInfo queueCreateInfo[QueueType_Max];
                f32 queuePriorities[QueueType_Max][QueueType_Max];
                u32 numQueueCreateInfo = createQueueCreateInfo(queueCreateInfo, queueFamilyIndices, queuePriorities);

                VkDeviceCreateInfo vkDeviceCreateInfo = {
                    VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //structure type
                    LGFX_NULL,
                    0, //device create flags, must set to 0
                    numQueueCreateInfo, //queue create info count,
                    queueCreateInfo, //queue create info
                    deviceCreateInfo.enabledLayerCount_, //enabled layer count
                    deviceCreateInfo.enabledLayerNames_, //enabled layer names
                    enabledExtensionCount, //enabled extension count
                    enabledExtensionNames, //enabled extension names
                    enabledFeatures, //enabled physical device features
                };

                if(VK_SUCCESS == Device::create(devices_[deviceCreateInfo.index_], physicalDevice, vkDeviceCreateInfo, queueFamilyIndices, swapchainBuilder, builder.allocator_)){
                    break;
                }
            }//for(; countDevice<physicalDevices.size();

            if(numPhysicalDevices<=countDevice){
                return false;
            }
        }
        allocator_ = builder.allocator_;
        return true;
    }

    void System::terminate()
    {
        for(s32 i=0; i<LGFX_MAX_PHYSICAL_DEVICES; ++i){
            Device::destroy(devices_[i], allocator_);
        }
        Instance::destroy(instance_, allocator_);
        lib_.terminate();
    }

    u32 System::getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName)
    {
        vkEnumerateInstanceExtensionProperties(layerName, &maxExtensions, extensionProperties);
        return maxExtensions;
    }
}
#endif //LGFX_VULKAN_IMPLEMENTATION_DONE
#endif //LGFX_VULKAN_IMPLEMENTATION
