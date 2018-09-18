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
    //--- Builder
    //---
    //--------------------------------------------------------------

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
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(CPPVK_NULL)
        ,allocator_(CPPVK_NULL)
        ,presentationSurface_(CPPVK_NULL)
#define CPPVK_EXT_INSTANCE_FUNCTION(name) ,name(CPPVK_NULL)
#include "VkFunctions.inc"
    {
    }

    Instance::~Instance()
    {
        destroy();
    }

    VkResult Instance::create(
        Instance& instance,
        const VkInstanceCreateInfo& instanceCreateInfo,
        const SurfaceCreateInfo& surfaceCreateInfo,
        const VkAllocationCallbacks* allocator)
    {
        if(instance.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result;
        result = vkCreateInstance(&instanceCreateInfo, allocator, &instance.instance_);
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

        result = instance.createPresentationSurface(surfaceCreateInfo);
        if(VK_SUCCESS != result){
            vkDestroyInstance(instance.instance_, allocator);
            instance.instance_ = CPPVK_NULL;
            instance.allocator_ = CPPVK_NULL;
            return result;
        }
        return VK_SUCCESS;
    }

    void Instance::destroy()
    {
        if(CPPVK_NULL == instance_){
            return;
        }

        if(CPPVK_NULL != presentationSurface_){
            vkDestroySurfaceKHR(instance_, presentationSurface_, allocator_);
            presentationSurface_ = CPPVK_NULL;
        }

        vkDestroyInstance(instance_, allocator_);
        allocator_ = CPPVK_NULL;
        instance_ = CPPVK_NULL;

#define CPPVK_EXT_INSTANCE_FUNCTION(name) name = CPPVK_NULL;
#include "VkFunctions.inc"
    }

    u32 Instance::enumeratePhysicalDevices(u32 maxPhysicalDevices, PhysicalDevice* devices) const
    {
        CPPVK_ASSERT(maxPhysicalDevices<=CPPVK_MAX_PHYSICAL_DEVICES);
        CPPVK_ASSERT(CPPVK_NULL != devices);

        u32 deviceCount = maxPhysicalDevices;
        VkPhysicalDevice tmp[CPPVK_MAX_PHYSICAL_DEVICES];
        if(VK_SUCCESS != vkEnumeratePhysicalDevices(instance_, &deviceCount, tmp)){
            return 0;
        }
        for(u32 i=0; i<deviceCount; ++i){
            devices[i].device_ = tmp[i];
        }
        return deviceCount;
    }

    VkResult Instance::createPresentationSurface(const SurfaceCreateInfo& createInfo)
    {
        if(CPPVK_NULL != presentationSurface_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
#ifdef CPPVK_USE_PLATFORM_XLIB_KHR
        VkXlibSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.display_,
            createInfo.window_,
        };
        VkResult result = vkCreateXlibSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef CPPVK_USE_PLATFORM_XCB_KHR
        VkXcbSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.connection_,
            createInfo.window_,
        };
        VkResult result = vkCreateXcbSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef CPPVK_USE_PLATFORM_WAYLAND_KHR
        VkWaylandSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.display_,
            createInfo.surface_,
        };
        VkResult result = vkCreateWaylandSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif
#ifdef CPPVK_USE_PLATFORM_MIR_KHR
        VkMirSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.connection_,
            createInfo.surface_,
        };
        VkResult result = vkCreateMirSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif

#ifdef CPPVK_USE_PLATFORM_ANDROID_KHR
        VkAndroidSurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.window_,
        };
        VkResult result = vkCreateAndroidSurfaceKHR(instance_, &implCreateInto, allocator, &presentationSurface_);
#endif

#ifdef CPPVK_USE_PLATFORM_WIN32_KHR
        VkWin32SurfaceCreateInfoKHR implCreateInto =
        {
            VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
            CPPVK_NULL,
            createInfo.flags_,
            createInfo.hInstance_,
            createInfo.hWnd_,
        };
        VkResult result = vkCreateWin32SurfaceKHR(instance_, &implCreateInto, allocator_, &presentationSurface_);
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
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    VkResult Swapchain::create(Swapchain& swapchain, Device& device, VkSwapchainCreateInfoKHR& createInfo, const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != device);

        if(CPPVK_NULL != swapchain.swapchain_){
            createInfo.oldSwapchain = swapchain.swapchain_;
        }

        VkSwapchainKHR vkSwapchain = CPPVK_NULL;
        VkResult result;
        if(VK_SUCCESS != (result = device.vkCreateSwapchainKHR(device, &createInfo, allocator, &vkSwapchain))){
            createInfo.oldSwapchain = CPPVK_NULL;
            return result;
        }

        swapchain.destroy(device);
        swapchain.swapchain_ = vkSwapchain;

        swapchain.numImages_ = MaxSwapchainImages;
        if(VK_SUCCESS != (result = device.vkGetSwapchainImagesKHR(device, swapchain.swapchain_, &swapchain.numImages_, swapchain.images_))){
            swapchain.destroy(device);
            return result;
        }
        CPPVK_ASSERT(0<swapchain.numImages_);
        return VK_SUCCESS;
    }

    Swapchain::Swapchain()
        :swapchain_(CPPVK_NULL)
        ,allocator_(CPPVK_NULL)
        ,numImages_(0)
    {
    }

    Swapchain::~Swapchain()
    {
    }

    void Swapchain::destroy(Device& device)
    {
        if(CPPVK_NULL == swapchain_){
            return;
        }
        device.vkDestroySwapchainKHR(device, swapchain_, allocator_);

        numImages_ = 0;
        allocator_ = CPPVK_NULL;
        swapchain_ = CPPVK_NULL;
    }

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    Device::Device()
        :device_(CPPVK_NULL)
        ,allocator_(CPPVK_NULL)
#define CPPVK_EXT_DEVICE_FUNCTION(name) ,name(CPPVK_NULL)
#include "VkFunctions.inc"
    {
        //clearColor_ = {0x00U, 0x00U, 0x00U, 0xFFU};
        for(u32 i=0; i<QueueType_Max; ++i){
            queues_[i] = CPPVK_NULL;
        }
    }

    Device::~Device()
    {
    }

    VkResult Device::create(
        Device& device,
        VkPhysicalDevice physicalDevice,
        const VkDeviceCreateInfo& deviceCreateInfo,
        const u32 queueFamilityIndices[QueueType_Max],
        VkSwapchainCreateInfoKHR& swapchainCreateInfo,
        const VkAllocationCallbacks* allocator)
    {
        CPPVK_ASSERT(CPPVK_NULL != physicalDevice);
        CPPVK_ASSERT(0<deviceCreateInfo.queueCreateInfoCount);

        if(device.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        VkResult result;
        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return result;
        }
        result = device.initialize();
        if(VK_SUCCESS != result){
            return result;
        }
        device.allocator_ = allocator;

        result = Swapchain::create(device.swapchain_, device, swapchainCreateInfo, allocator);
        if(VK_SUCCESS != result){
            vkDestroyDevice(device.device_, allocator);
            device.device_ = CPPVK_NULL;
            device.allocator_ = CPPVK_NULL;
            return result;
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


        result = device.createSemaphores();
        if(VK_SUCCESS != result){
            device.swapchain_.destroy(device);
            vkDestroyDevice(device.device_, allocator);
            device.device_ = CPPVK_NULL;
            device.allocator_ = CPPVK_NULL;
            for(u32 i=0; i<QueueType_Max; ++i){
                device.queues_[i] = CPPVK_NULL;
            }
            return result;
        }
        return result;
    }

    void Device::destroy()
    {
        if(CPPVK_NULL == device_){
            return;
        }
        waitIdle();

        if(CPPVK_NULL != semaphoreRenderingFinished_){
            vkDestroySemaphore(device_, semaphoreRenderingFinished_, allocator_);
            semaphoreRenderingFinished_ = CPPVK_NULL;
        }
        if(CPPVK_NULL != semaphoreImageAvailable_){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
            semaphoreImageAvailable_ = CPPVK_NULL;
        }

        swapchain_.destroy(*this);
        vkDestroyDevice(device_, allocator_);

        for(u32 i=0; i<QueueType_Max; ++i){
            queues_[i] = CPPVK_NULL;
        }

        allocator_ = CPPVK_NULL;
        device_ = CPPVK_NULL;

#define VLK_EXT_DEVICE_FUNCTION(name) name ## _ = CPPVK_NULL;
#include "VkFunctions.inc"
    }

    VkResult Device::waitIdle()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);
        return vkDeviceWaitIdle(device_);
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

    VkResult Device::initialize()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

#define CPPVK_EXT_DEVICE_FUNCTION(name) if(CPPVK_NULL == name) name = (PFN_ ## name)vkGetDeviceProcAddr(device_, #name);\
    if(CPPVK_NULL == name){\
        PRINT1_WARN("Warning: cannot get device function %s via vkGetDeviceProcAddr\n", #name);\
    }
#include "VkFunctions.inc"

        return VK_SUCCESS;
    }

    VkResult Device::createSemaphores()
    {
        CPPVK_ASSERT(CPPVK_NULL != device_);

        VkResult result;
        // create semaphores
        VkSemaphoreCreateInfo semaphoreCreateInfo =
        {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, //structure type
            CPPVK_NULL,
            0,//flags
        };

        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator_, &semaphoreImageAvailable_))){
            return result;
        }
        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator_, &semaphoreRenderingFinished_))){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
            semaphoreImageAvailable_ = CPPVK_NULL;
            return result;
        }

        return VK_SUCCESS;
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
    namespace
    {
        template<class T>
        void init(u32 size, T* array, T value)
        {
            for(u32 i=0; i<size; ++i){
                array[i] = value;
            }
        }

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
                createInfo[count].pNext = CPPVK_NULL; //next. must be null
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

    bool System::createInstance(const InstanceCreateInfo& instanceCreateInfo, const SurfaceCreateInfo& surfaceCreateInfo, const Char* layerName, const VkAllocationCallbacks* allocator)
    {
        u32 enabledExtensionCount = 0;
        const Char* enabledExtensionNames[CPPVK_MAX_INSTANCE_EXTENSION_PROPERTIES];

        if(CPPVK_NULL != instanceCreateInfo.checkExtensions_){
            InstanceExtensionProperties extensionProperties;
            getInstanceExtensionProperties(extensionProperties, layerName);
            enabledExtensionCount = extensionProperties.getExtensions(enabledExtensionNames, instanceCreateInfo.checkExtensions_);
        }

        VkApplicationInfo vkApplicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, //structure type
            CPPVK_NULL, //must be null
            instanceCreateInfo.applicationName_, //application name
            instanceCreateInfo.applicationVersion_, //application version
            instanceCreateInfo.engineName_, //engine name
            instanceCreateInfo.engineVersion_, //engine version
            instanceCreateInfo.apiVersion_, //api version
        };

        VkInstanceCreateInfo vkInstanceCreateInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //structure type
            CPPVK_NULL, //must be null
            0, //instance creation flags. must set to 0
            &vkApplicationInfo, //application info
            instanceCreateInfo.enabledLayerCount_, //enabled layer count
            instanceCreateInfo.enabledLayerNames_, //enabled layer names
            enabledExtensionCount, //enabled extension count
            enabledExtensionNames, //enabled extension names
        };
        if(VK_SUCCESS != Instance::create(instance_, vkInstanceCreateInfo, surfaceCreateInfo, allocator)){
            return false;
        }
        return true;
    }

    bool System::createDevice(
        s32 index,
        const DeviceCreateInfo& deviceCreateInfo,
        const SwapchainCreateInfo& swapchainCreateInfo,
        const Char* layerName,
        const VkAllocationCallbacks* allocator)
    {
        //Queue families
        PFN_checkQueueFamilies checkQueueFamilies = (CPPVK_NULL != deviceCreateInfo.checkQueueFamilies_)? deviceCreateInfo.checkQueueFamilies_ : defaultCheckQueueFamilies;
        u32 numQueueFamilyProperties;
        VkQueueFamilyProperties queueFamilyProperties[CPPVK_MAX_QUEUE_FAMILY_PROPERTIES];
        bool queueFamilyPresentationSupports[CPPVK_MAX_QUEUE_FAMILY_PROPERTIES];

        //Extensions
        DeviceExtensionProperties deviceExtensionProperties;
        u32 enabledExtensionCount;
        const Char* enabledExtensionNames[CPPVK_MAX_DEVICE_EXTENSION_PROPERTIES];

        //Physical device features
        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceFeatures* enabledFeatures = CPPVK_NULL;

        //Surface capabilities
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        u32 swapChainCount;
        VkExtent2D surfaceExtent;
        VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        VkSurfaceTransformFlagBitsKHR imagePreTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        VkPresentModeKHR presentMode;
        VkSurfaceFormatKHR surfaceFormat;

        PhysicalDevice physicalDevices[CPPVK_MAX_PHYSICAL_DEVICES];
        u32 numPhysicalDevices = instance_.enumeratePhysicalDevices(CPPVK_MAX_PHYSICAL_DEVICES, physicalDevices);

        u32 countDevice = 0;
        for(; countDevice<numPhysicalDevices; ++countDevice){
            PhysicalDevice physicalDevice = physicalDevices[countDevice];

            //--- Device
            //----------------------------------------------------------
            //Select queues for graphics and presentation
            //Get queue properties
            u32 queueFamilyIndices[QueueType_Max];
            init(QueueType_Max, queueFamilyIndices, static_cast<u32>(QueueType_Invalid));

            numQueueFamilyProperties = CPPVK_MAX_QUEUE_FAMILY_PROPERTIES;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &numQueueFamilyProperties, queueFamilyProperties);

            for(u32 j=0; j<numQueueFamilyProperties; ++j){
                queueFamilyPresentationSupports[j] = instance_.getPhysicalDevicePresentationSurfaceSupport(physicalDevice, j);
            }
            checkQueueFamilies(queueFamilyIndices, numQueueFamilyProperties, queueFamilyProperties, queueFamilyPresentationSupports, deviceCreateInfo.requestQueueTypes_);

            if(QueueType_Invalid == queueFamilyIndices[QueueType_Present] || QueueType_Invalid == queueFamilyIndices[QueueType_Graphics]){
                continue;
            }

            //Check device extensions
            if(CPPVK_NULL != deviceCreateInfo.checkExtensions_){
                physicalDevice.enumerateDeviceExtensionProperties(deviceExtensionProperties, layerName);
                enabledExtensionCount = deviceExtensionProperties.getExtensions(enabledExtensionNames, deviceCreateInfo.checkExtensions_);
            }

            //Check device features
            if(CPPVK_NULL != deviceCreateInfo.checkDeviceFeatures_){
                VkPhysicalDeviceFeatures supported;
                physicalDevice.getPhysicalDeviceFeatures(supported);
                memset(&features, 0, sizeof(VkPhysicalDeviceFeatures));
                if(!deviceCreateInfo.checkDeviceFeatures_(features, supported)){
                    continue;
                }
                enabledFeatures = &features;
            }

            VkDeviceQueueCreateInfo queueCreateInfo[QueueType_Max];
            f32 queuePriorities[QueueType_Max][QueueType_Max];
            u32 numQueueCreateInfo = createQueueCreateInfo(queueCreateInfo, queueFamilyIndices, queuePriorities);

            //--- Swapchain
            //-------------------------------------------------------------
            //Check surface capabilities
            {
                if(VK_SUCCESS != instance_.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, instance_.getPresentationSurface(), &surfaceCapabilities)){
                    continue;
                }

                //Check swap chain image count
                swapChainCount = clamp(swapchainCreateInfo.swapchainCount_, surfaceCapabilities.minImageCount, surfaceCapabilities.maxImageCount);

                //Check image extent
                if(-1 != surfaceCapabilities.currentExtent.width){
                    surfaceExtent = surfaceCapabilities.currentExtent;
                } else{
                    surfaceExtent.width = clamp(swapchainCreateInfo.surfaceExtent_.width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
                    surfaceExtent.height = clamp(swapchainCreateInfo.surfaceExtent_.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
                }

                //Check usage flags
                if(VK_IMAGE_USAGE_TRANSFER_DST_BIT != (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)){
                    continue;
                }
                imageUsageFlags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

                imagePreTransform = surfaceCapabilities.currentTransform;
                if(CPPVK_NULL != swapchainCreateInfo.checkSurfaceCapabilities_){
                    if(!swapchainCreateInfo.checkSurfaceCapabilities_(imageUsageFlags, imagePreTransform, compositeAlpha, surfaceCapabilities)){
                        continue;
                    }
                }
            }

            //Check present modes
            {
                VkPresentModeKHR presentModes[CPPVK_MAX_PRESENTMODES];
                u32 countPresentModes = CPPVK_MAX_PRESENTMODES;
                if(VK_SUCCESS != instance_.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, instance_.getPresentationSurface(), &countPresentModes, presentModes)
                    || countPresentModes<=0){
                    continue;
                }
                presentMode = getPresentMode(countPresentModes, presentModes, swapchainCreateInfo.presentMode_);
            }

            //Check surface formats
            {
                VkSurfaceFormatKHR surfaceFormats[CPPVK_MAX_SURFACEFORMATS];
                u32 countSurfaceFormats = CPPVK_MAX_SURFACEFORMATS;
                if(VK_SUCCESS != instance_.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, instance_.getPresentationSurface(), &countSurfaceFormats, surfaceFormats)
                    || countSurfaceFormats<=0){
                    continue;
                }
                if(CPPVK_NULL != swapchainCreateInfo.checkSurfaceFormats_){
                    if(!swapchainCreateInfo.checkSurfaceFormats_(surfaceFormat, countSurfaceFormats, surfaceFormats)){
                        continue;
                    }
                } else if(swapchainCreateInfo.supportHDR_){
                    if(!defaultCheckSurfaceFormatHDR(surfaceFormat, countSurfaceFormats, surfaceFormats)){
                        continue;
                    }
                } else{
                    if(!defaultCheckSurfaceFormatSDR(surfaceFormat, countSurfaceFormats, surfaceFormats)){
                        continue;
                    }
                }
            }

            VkDeviceCreateInfo vkDeviceCreateInfo = {
                VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //structure type
                CPPVK_NULL,
                0, //device create flags, must set to 0
                numQueueCreateInfo, //queue create info count,
                queueCreateInfo, //queue create info
                deviceCreateInfo.enabledLayerCount_, //enabled layer count
                deviceCreateInfo.enabledLayerNames_, //enabled layer names
                enabledExtensionCount, //enabled extension count
                enabledExtensionNames, //enabled extension names
                enabledFeatures, //enabled physical device features
            };

            VkSwapchainCreateInfoKHR vkSwapchainCreateInfo = {
                VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, //structure type
                CPPVK_NULL, //must be null
                0, //swapchain create flags, must set to 0
                instance_.getPresentationSurface(),
                swapChainCount, //swapchain image count
                surfaceFormat.format,
                surfaceFormat.colorSpace,
                surfaceExtent,
                1, //the number of views in a multiview or stereo surface
                imageUsageFlags,
                VK_SHARING_MODE_EXCLUSIVE, //sharing mode
                0, //the number of queue family indices when imageSharingMode equals VK_SHARING_MODE_CONCURRENT
                CPPVK_NULL, //an arrays of queue family indices when imageSharingMode equals VK_SHARING_MODE_CONCURRENT
                imagePreTransform,
                compositeAlpha,
                presentMode,
                VK_TRUE,
                CPPVK_NULL,
            };

            if(VK_SUCCESS == Device::create(devices_[index], physicalDevice, vkDeviceCreateInfo, queueFamilyIndices, vkSwapchainCreateInfo, allocator)){
                break;
            }
        }//for(; countDevice<physicalDevices.size();

        return countDevice<numPhysicalDevices;
    }

    void System::defaultCheckQueueFamilies(
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

    bool System::defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace)
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

    bool System::defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace)
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
    
    bool System::defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
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

    bool System::defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
    {
        CPPVK_ASSERT(0<size);

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

    VkPresentModeKHR System::getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request)
    {
        CPPVK_ASSERT(0<size);

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
}
