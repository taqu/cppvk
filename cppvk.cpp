/**
@file vk.cpp
@author t-sakai
@date 2017/10/15 create
*/
#include "cppvk.h"
#ifdef _DEBUG
#include <stdio.h>
#endif

#ifdef _DEBUG
#ifdef CPPVK_REPORT_ERROR
#define PRINT0_ERR(str) fprintf(stderr, str)
#define PRINT1_ERR(str, p0) fprintf(stderr, str, p0)
#else
#define PRINT0_ERR(str)
#define PRINT0_ERR(str)
#endif

#ifdef CPPVK_REPORT_WARNING
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

namespace cppvk
{
#define CPPVK_EXPORTED_FUNCTION(name) PFN_ ## name name = CPPVK_NULL;
#include "VkFunctions.inc"

    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    Lib::Lib()
        :handle_(CPPVK_NULL)
    {}

    Lib::~Lib()
    {
        terminate();
    }

    VkResult Lib::initialize()
    {
        if(CPPVK_NULL != handle_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        handle_ = CPPVK_DLOPEN(CPPVK_VULKANLIB);
        if(CPPVK_NULL == handle_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

#define CPPVK_EXPORTED_FUNCTION(name) CPPVK_GET_FUNCTION(name, "Error: cannot get exported %s\n")

#define CPPVK_GET_FUNCTION(name, message) name = (PFN_ ## name)CPPVK_DLSYM(handle_, #name);\
    if(CPPVK_NULL == name){\
        PRINT1_ERR(message, #name);\
        return VK_ERROR_INITIALIZATION_FAILED;\
    }

#define CPPVK_GET_FUNCTION_WARN(name, message) name = (PFN_ ## name)CPPVK_DLSYM(handle_, #name);\
    if(CPPVK_NULL == name){\
        PRINT1_WARN(message, #name);\
    }

#include "VkFunctions.inc"

        return VK_SUCCESS;
    }

    void Lib::terminate()
    {
        if(CPPVK_NULL == handle_){
            return;
        }

#define CPPVK_EXPORTED_FUNCTION(name) name = CPPVK_NULL;
#include "VkFunctions.inc"

        CPPVK_DLCLOSE(handle_);
        handle_ = CPPVK_NULL;
    }

    //--------------------------------------------------------------
    //---
    //--- QueueFamilyProperties
    //---
    //--------------------------------------------------------------
    QueueFamilyProperties::QueueFamilyProperties()
        :numQueueFamilyProperties_(0)
    {
    }

    QueueFamilyProperties::~QueueFamilyProperties()
    {}

    s32 QueueFamilyProperties::selectQueueFamily(PFN_checkQueueFamily checkQueueFamily) const
    {
        CPPVK_ASSERT(CPPVK_NULL != checkQueueFamily);
        for(u32 i=0; i<numQueueFamilyProperties_; ++i){
            if(checkQueueFamily(queueFamilyProperties_[i])){
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
    void PhysicalDevice::getPhysicalDeviceQueueFamilyProperties(QueueFamilyProperties& queueFamilyProperties)
    {
        queueFamilyProperties.numQueueFamilyProperties_ = QueueFamilyProperties::MaxProperties;
        vkGetPhysicalDeviceQueueFamilyProperties(device_, &queueFamilyProperties.numQueueFamilyProperties_, queueFamilyProperties.queueFamilyProperties_);
    }

    void PhysicalDevice::enumerateDeviceExtensionProperties(DeviceExtensionProperties& properties, const Char* layerName)
    {
        properties.numExtensionProperties_ = DeviceExtensionProperties::MaxProperties;
        vkEnumerateDeviceExtensionProperties(device_, layerName, &properties.numExtensionProperties_, properties.extensionProperties_);
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(CPPVK_NULL)
        ,presentSurface_(CPPVK_NULL)
        ,allocator_(CPPVK_NULL)
#define CPPVK_EXT_INSTANCE_FUNCTION(name) ,name(CPPVK_NULL)
#include "VkFunctions.inc"
    {
    }

    Instance::~Instance()
    {
        destroy();
    }

    VkResult Instance::create(Instance& instance, const VkInstanceCreateInfo& createInfo, const VkAllocationCallbacks* allocator)
    {
        if(instance.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result;
        result = vkCreateInstance(&createInfo, allocator, &instance.instance_);
        if(VK_SUCCESS != result){
            return result;
        }

        result = instance.initialize();
        if(VK_SUCCESS != result){
            vkDestroyInstance(instance.instance_, allocator);
            instance.instance_ = CPPVK_NULL;
            return result;
        }

        instance.allocator_ = allocator;
        return VK_SUCCESS;
    }

    void Instance::destroy()
    {
        if(CPPVK_NULL != presentSurface_){
            vkDestroySurfaceKHR(instance_, presentSurface_, allocator_);
            presentSurface_ = CPPVK_NULL;
        }

        if(CPPVK_NULL == instance_){
            return;
        }

#define CPPVK_EXT_INSTANCE_FUNCTION(name) name = CPPVK_NULL;
#include "VkFunctions.inc"

        vkDestroyInstance(instance_, allocator_);
        instance_ = CPPVK_NULL;
        allocator_ = CPPVK_NULL;
    }

    PhysicalDevices Instance::enumeratePhysicalDevices()
    {
        u32 deviceCount = PhysicalDevices::MaxPhysicalDevices;
        VkPhysicalDevice devices[PhysicalDevices::MaxPhysicalDevices];
        VkResult result = vkEnumeratePhysicalDevices(instance_, &deviceCount, devices);
        if(VK_SUCCESS != result){
            deviceCount = 0;
        }

        PhysicalDevices ret;
        ret.numDevices_ = deviceCount;
        for(u32 i=0; i<deviceCount; ++i){
            ret.devices_[i].device_ = devices[i];
        }
        return ret;
    }

    VkResult Instance::createPresentSurface(const SurfaceCreateInfo& createInfo)
    {
        if(CPPVK_NULL != presentSurface_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
#ifdef CPPVK_USE_PLATFORM_XLIB_KHR
        VkResult result = vkCreateXlibSurfaceKHR(instance_, &createInfo, allocator, &surface.surface_);
#endif
#ifdef CPPVK_USE_PLATFORM_XCB_KHR
        VkResult result = vkCreateXcbSurfaceKHR(instance_, &createInfo, allocator, &surface.surface_);
#endif
#ifdef CPPVK_USE_PLATFORM_WAYLAND_KHR
        VkResult result = vkCreateWaylandSurfaceKHR(instance_, &createInfo, allocator, &surface.surface_);
#endif
#ifdef CPPVK_USE_PLATFORM_MIR_KHR
        VkResult result = vkCreateMirSurfaceKHR(instance_, &createInfo, allocator, &surface.surface_);
#endif
#ifdef CPPVK_USE_PLATFORM_ANDROID_KHR
        VkResult result = vkCreateAndroidSurfaceKHR(instance_, &createInfo, allocator, &surface.surface_);
#endif
#ifdef CPPVK_USE_PLATFORM_WIN32_KHR
        VkResult result = vkCreateWin32SurfaceKHR(instance_, &createInfo, allocator_, &presentSurface_);
#endif
        return result;

    }

    VkResult Instance::initialize()
    {
        CPPVK_ASSERT(CPPVK_NULL != instance_);

#define CPPVK_EXT_INSTANCE_FUNCTION(name) if(CPPVK_NULL == name) name = (PFN_ ## name)vkGetInstanceProcAddr(instance_, #name);\
    if(CPPVK_NULL == name){\
        PRINT1_WARN("Warning: cannot get instance function %s via vkGetInstanceProcAddr\n", #name);\
    }
#include "VkFunctions.inc"

        return VK_SUCCESS;
    }

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    Device::Device()
        :device_(CPPVK_NULL)
        ,numQueues_(0)
        ,allocator_(CPPVK_NULL)
#define CPPVK_EXT_DEVICE_FUNCTION(name) ,name(CPPVK_NULL)
#include "VkFunctions.inc"
    {
        //clearColor_ = {0x00U, 0x00U, 0x00U, 0xFFU};
        for(u32 i=0; i<MaxQueues; ++i){
            queueFamilyIndices_[i] = 0;
            queues_[i] = CPPVK_NULL;
        }
    }

    Device::~Device()
    {
    }

    VkResult Device::create(Device& device, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& createInfo, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != physicalDevice);
        CPPVK_ASSERT(0<createInfo.queueCreateInfoCount);

        if(device.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result = vkCreateDevice(physicalDevice, &createInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return result;
        }

        // get queues
        switch(createInfo.queueCreateInfoCount)
        {
        case 1:
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::GraphicsQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::ComputeQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::PresentQueue]);
            device.queueFamilyIndices_[Device::GraphicsQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::ComputeQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::PresentQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            break;
        case 2:
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::GraphicsQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::ComputeQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[1].queueFamilyIndex, 0, &device.queues_[Device::PresentQueue]);
            device.queueFamilyIndices_[Device::GraphicsQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::ComputeQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::PresentQueue] = createInfo.pQueueCreateInfos[1].queueFamilyIndex;
            break;
        case 3:
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::GraphicsQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[1].queueFamilyIndex, 0, &device.queues_[Device::ComputeQueue]);
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[2].queueFamilyIndex, 0, &device.queues_[Device::PresentQueue]);
            device.queueFamilyIndices_[Device::GraphicsQueue] = createInfo.pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::ComputeQueue] = createInfo.pQueueCreateInfos[1].queueFamilyIndex;
            device.queueFamilyIndices_[Device::PresentQueue] = createInfo.pQueueCreateInfos[2].queueFamilyIndex;
            break;
        default:
            vkDestroyDevice(device.device_, allocator);
            device.device_ = CPPVK_NULL;
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        device.numQueues_ = createInfo.queueCreateInfoCount;

        result = device.initialize(allocator);
        if(VK_SUCCESS != result){
            vkDestroyDevice(device.device_, allocator);
            device.device_ = CPPVK_NULL;
            device.numQueues_ = 0;
            return result;
        }

        for(u32 i=0; i<device.numQueues_; ++i){
            vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[i].queueFamilyIndex, 0, &device.queues_[i]);
        }
        return result;
    }

    VkResult Device::initialize(const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        allocator_ = allocator;

        VkResult result;
        // create semaphores
        VkSemaphoreCreateInfo semaphoreCreateInfo =
        {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, //structure type
            CPPVK_NULL,
            0,//flags
        };

        //if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator, &semaphoreImageAvailable_))){
        //    return result;
        //}
        //if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator, &semaphoreRenderingFinished_))){
        //    vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
        //    semaphoreImageAvailable_ = CPPVK_NULL;
        //    return result;
        //}

#define CPPVK_EXT_DEVICE_FUNCTION(name) if(CPPVK_NULL == name) name = (PFN_ ## name)vkGetDeviceProcAddr(device_, #name);\
    if(CPPVK_NULL == name){\
        PRINT1_WARN("Warning: cannot get device function %s via vkGetDeviceProcAddr\n", #name);\
    }
#include "VkFunctions.inc"

        return VK_SUCCESS;
    }

    void Device::destroy()
    {
        if(CPPVK_NULL == device_){
            return;
        }
        waitIdle();

        //vkDestroySemaphore(device_, semaphoreRenderingFinished_, allocator_);
        //semaphoreRenderingFinished_ = CPPVK_NULL;
        //vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
        //semaphoreImageAvailable_ = CPPVK_NULL;

#define VLK_EXT_DEVICE_FUNCTION(name) name ## _ = CPPVK_NULL;
#include "VkFunctions.inc"

        vkDestroyDevice(device_, allocator_);

        for(u32 i=0; i<numQueues_; ++i){
            queueFamilyIndices_[i] = 0;
            queues_[i] = CPPVK_NULL;
        }

        device_ = CPPVK_NULL;
        numQueues_ = 0;
    }

    VkResult Device::waitIdle()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        return vkDeviceWaitIdle(device_);
    }

    VkResult Device::createSwapchain(Swapchain& swapchain, VkSwapchainCreateInfoKHR& createInfo, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

        if(CPPVK_NULL != swapchain.swapchain_){
            createInfo.oldSwapchain = swapchain.swapchain_;
            swapchain.swapchain_ = CPPVK_NULL;
        }

        VkResult result;
        if(VK_SUCCESS != (result = vkCreateSwapchainKHR(device_, &createInfo, allocator, &swapchain.swapchain_))){
            swapchain.swapchain_ = createInfo.oldSwapchain;
            createInfo.oldSwapchain = CPPVK_NULL;
            return result;
        }

        if(CPPVK_NULL != createInfo.oldSwapchain){
            vkDestroySwapchainKHR(device_, createInfo.oldSwapchain, allocator);
            createInfo.oldSwapchain = CPPVK_NULL;
        }

        u32 numImages = swapchain.numImages_ = 0;
        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR(device_, swapchain.swapchain_, &numImages, CPPVK_NULL)) || numImages<=0){
            return result;
        }

        numImages = minimum(numImages, static_cast<u32>(Swapchain::MaxSwapchainImages));
        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR(device_, swapchain.swapchain_, &numImages, swapchain.images_))){
            return result;
        }
        swapchain.numImages_ = static_cast<s32>(numImages);
        return VK_SUCCESS;
    }

    void Device::destroySwapchain(Swapchain& swapchain, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

        if(swapchain.valid()){
            vkDestroySwapchainKHR(device_, swapchain.swapchain_, allocator);
            swapchain.swapchain_ = CPPVK_NULL;
            swapchain.numImages_ = 0;
        }
    }

    VkResult Device::createCommandPool(CommandPool& commandPool, const VkCommandPoolCreateInfo& createInfo, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

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
        CPPVK_ASSERT(CPPVK_NULL != device_);

        if(commandPool.valid()){
            vkDestroyCommandPool(device_, commandPool.commandPool_, allocator);
            commandPool.commandPool_ = CPPVK_NULL;
        }
    }

    VkResult Device::resetCommandPool(CommandPool& commandPool, VkCommandPoolResetFlags flags)
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        CPPVK_ASSERT(commandPool.valid());
        return vkResetCommandPool(device_, commandPool.commandPool_, flags);
    }


    VkResult Device::allocateCommandBuffers(CommandBuffer* commandBuffers, const VkCommandBufferAllocateInfo& allocateInfo)
    {
        CPPVK_ASSERT(0<=allocateInfo.commandBufferCount && allocateInfo.commandBufferCount<=MaxCommandBuffers);
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
        CPPVK_ASSERT(0<=numBuffers && numBuffers<=MaxCommandBuffers);
        CPPVK_ASSERT(commandPool.valid());

        VkCommandBuffer buffers[MaxCommandBuffers];
        for(u32 i=0; i<numBuffers; ++i){
            buffers[i] = commandBuffers[i].commandBuffer_;
            commandBuffers[i].commandBuffer_ = CPPVK_NULL;
        }

        vkFreeCommandBuffers(device_, commandPool, numBuffers, buffers);
    }

#if 0
    VkResult Device::createCommandBuffers()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

        VkResult result;

        VkCommandPoolCreateInfo commandPoolCreateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            CPPVK_NULL,
            0,
            queueFamilyIndices_[PresentQueue],
        };
        if(VK_SUCCESS != (result = vkCreateCommandPool(device_, &commandPoolCreateInfo, allocator_, &presentQueueCommandPool_))){
            return result;
        }

        VkCommandBufferAllocateInfo commandBufferAllocateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            CPPVK_NULL,
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
        CPPVK_ASSERT(CPPVK_NULL != device_);
        CPPVK_ASSERT(CPPVK_NULL != swapchain_);

        VkResult result;
        if(VK_SUCCESS != (result = vkDeviceWaitIdle(device_))){
            return result;
        }

        if(0<swapchainImageCount_){
            vkFreeCommandBuffers(device_, presentQueueCommandPool_, swapchainImageCount_, presentQueueCommandBuffers_);
            swapchainImageCount_ = 0;
        }

        if(CPPVK_NULL != presentQueueCommandPool_){
            vkDestroyCommandPool(device_, presentQueueCommandPool_, allocator_);
            presentQueueCommandPool_ = CPPVK_NULL;
        }
        return VK_SUCCESS;
    }

    VkResult Device::recordCommandBuffers()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        CPPVK_ASSERT(CPPVK_NULL != swapchain_);
        VkResult result;
        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR_(device_, swapchain_, &swapchainImageCount_, swapchainImages_))){
            return result;
        }
        VkCommandBufferBeginInfo commandBufferBeginInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, //structure type
            CPPVK_NULL,
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, //flags
            CPPVK_NULL,
        };
        VkImageSubresourceRange imageSubresourceRange =
        {
            VK_IMAGE_ASPECT_COLOR_BIT, //flags
            0, 1, 0, 1,
        };

        VkImageMemoryBarrier barrierFromPresentToClear =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            CPPVK_NULL,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            CPPVK_NULL,
            imageSubresourceRange,
        };

        VkImageMemoryBarrier barrierFromClearToPresent =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            CPPVK_NULL,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            CPPVK_NULL,
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
                CPPVK_NULL,
                0,
                CPPVK_NULL,
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
                CPPVK_NULL,
                0,
                CPPVK_NULL,
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
        result = vkAcquireNextImageKHR_(device_, swapchain_, UINT64_MAX, semaphoreImageAvailable_, CPPVK_NULL, &imageIndex);
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
            CPPVK_NULL,
            1,
            &semaphoreImageAvailable_,
            &waitDstStageMask,
            1,
            &presentQueueCommandBuffers_[imageIndex],
            1,
            &semaphoreRenderingFinished_,
        };
        if(VK_SUCCESS != (result = vkQueueSubmit(queues_[PresentQueue], 1, &submitInfo, CPPVK_NULL))){
            return false;
        }

        VkPresentInfoKHR presentInfo =
        {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            CPPVK_NULL,
            1,
            &semaphoreRenderingFinished_,
            1,
            &swapchain_,
            &imageIndex,
            CPPVK_NULL,
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

    //--------------------------------------------------------------
    //---
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    Swapchain::Swapchain()
        :swapchain_(CPPVK_NULL)
        ,numImages_(0)
    {
    }

    Swapchain::~Swapchain()
    {
    }

    //--------------------------------------------------------------
    //---
    //--- CommandPool
    //---
    //--------------------------------------------------------------
    CommandPool::CommandPool()
        :commandPool_(CPPVK_NULL)
    {
    }

    CommandPool::~CommandPool()
    {
    }

    //--------------------------------------------------------------
    //---
    //--- CommandBuffer
    //---
    //--------------------------------------------------------------
    CommandBuffer::CommandBuffer()
        :commandBuffer_(CPPVK_NULL)
    {
    }

    CommandBuffer::~CommandBuffer()
    {
    }

    //--------------------------------------------------------------
    //---
    //--- System
    //---
    //--------------------------------------------------------------
    System::System()
    {
    }

    System::~System()
    {
        terminate();
    }

    bool System::initialize()
    {
        return VK_SUCCESS == lib_.initialize();
    }

    void System::terminate()
    {
        for(s32 i=0; i<CPPVK_MAX_PHYSICAL_DEVICES; ++i){
            devices_[i].destroy();
        }
        instance_.destroy();
        lib_.terminate();
    }

    void System::getInstanceExtensionProperties(InstanceExtensionProperties& properties, const Char* layerName)
    {
        properties.numExtensionProperties_ = InstanceExtensionProperties::MaxProperties;
        vkEnumerateInstanceExtensionProperties(layerName, &properties.numExtensionProperties_, properties.extensionProperties_);
    }

    bool System::createInstance(InstanceCreateInfo& createInfo, const Char* layerName, PFN_checkExtensions checkExtensions, const VkAllocationCallbacks* allocator)
    {
        if(CPPVK_NULL != checkExtensions){
            InstanceExtensionProperties extensionProperties;
            getInstanceExtensionProperties(extensionProperties, layerName);
            createInfo.enabledExtensionCount_ = extensionProperties.getExtensions(createInfo.enabledExtensionNames_, checkExtensions);
        }

        VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, //structure type
            CPPVK_NULL,
            createInfo.applicationName_, //application name
            createInfo.applicationVersion_, //application version
            createInfo.engineName_, //engine name
            createInfo.engineVersion_, //engine version
            createInfo.apiVersion_, //api version
        };

        VkInstanceCreateInfo instanceCreateInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //structure type
            CPPVK_NULL,
            createInfo.createFlags_, //instance creation flags
            &applicationInfo, //application info
            createInfo.enabledLayerCount_, //enabled layer count
            createInfo.enabledLayerNames_, //enabled layer names
            createInfo.enabledExtensionCount_, //enabled extension count
            createInfo.enabledExtensionNames_, //enabled extension names
        };
        if(VK_SUCCESS == Instance::create(instance_, instanceCreateInfo, allocator)){
            return true;
        }
        return false;
    }

    PhysicalDevices System::enumeratePhysicalDevices()
    {
        return instance_.enumeratePhysicalDevices();
    }

    bool System::createDevice(s32 index, DeviceCreateInfo& createInfo, const Char* layerName, PFN_checkQueueFamily checkQueueFamily, PFN_checkExtensions checkExtensions, PFN_checkDeviceFeatures checkDeviceFeatures, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != checkQueueFamily);

        QueueFamilyProperties queueFamilyProperties;
        DeviceExtensionProperties deviceExtensionProperties;
        VkPhysicalDeviceFeatures features;

        PhysicalDevices physicalDevices = instance_.enumeratePhysicalDevices();
        for(u32 i=0; i<physicalDevices.size(); ++i){
            PhysicalDevice physicalDevice = physicalDevices[i];
            physicalDevice.getPhysicalDeviceQueueFamilyProperties(queueFamilyProperties);

            s32 selectedQueueFamily = queueFamilyProperties.selectQueueFamily(checkQueueFamily);
            if(selectedQueueFamily<0){
                continue;
            }

            if(CPPVK_NULL != checkExtensions){
                physicalDevice.enumerateDeviceExtensionProperties(deviceExtensionProperties, layerName);
                createInfo.enabledExtensionCount_ = deviceExtensionProperties.getExtensions(createInfo.enabledExtensionNames_, checkExtensions);
            }

            if(CPPVK_NULL != checkDeviceFeatures){
                VkPhysicalDeviceFeatures supported;
                physicalDevice.getPhysicalDeviceFeatures(supported);
                memset(&features, 0, sizeof(VkPhysicalDeviceFeatures));
                if(!checkDeviceFeatures(features, supported)){
                    continue;
                }
                createInfo.enabledFeatures_ = &features;
            }else{
                createInfo.enabledFeatures_ = CPPVK_NULL;
            }

            VkDeviceQueueCreateInfo queueCreateInfo ={
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //structure type
                CPPVK_NULL, //next
                createInfo.deviceQueueCreateFlags_, //device queue creation flags
                static_cast<u32>(selectedQueueFamily),//selected queue family's index
                createInfo.queueCount_, //queue count
                createInfo.queuePriorities_, //queue priorities
            };

            VkDeviceCreateInfo deviceCreateInfo ={
                VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //structure type
                CPPVK_NULL,
                createInfo.deviceCreateFlags_, //device create flags
                1, //queue create info count,
                &queueCreateInfo, //queue create info
                createInfo.enabledLayerCount_, //enabled layer count
                createInfo.enabledLayerNames_, //enabled layer names
                createInfo.enabledExtensionCount_, //enabled extension count
                createInfo.enabledExtensionNames_, //enabled extension names
                createInfo.enabledFeatures_, //enabled physical device features
            };

            if(VK_SUCCESS == Device::create(devices_[index], physicalDevice, deviceCreateInfo, allocator)){
                return true;
            }
        }
        return false;
    }

    bool System::createPresentSurface(const Instance::SurfaceCreateInfo& createInfo)
    {
        return VK_SUCCESS == instance_.createPresentSurface(createInfo);
    }
}
