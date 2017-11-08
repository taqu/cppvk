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
#ifdef VLK_REPORT_ERROR
#define PRINT0_ERR(str) fprintf(stderr, str)
#define PRINT1_ERR(str, p0) fprintf(stderr, str, p0)
#else
#define PRINT0_ERR(str)
#define PRINT0_ERR(str)
#endif

#ifdef VLK_REPORT_WARNING
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

namespace vk
{
#define VLK_EXPORTED_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_INSTANCE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_DEVICE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_PHYSICALDEVICE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_EXT_EXPORTED_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#define VLK_EXT_PHYSICALDEVICE_FUNCTION(name) PFN_ ## name name = VLK_NULL;
#include "VkFunctions.inc"

    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    Lib::Lib()
        :handle_(VLK_NULL)
    {
    }

    Lib::~Lib()
    {
        terminate();
    }

    VkResult Lib::initialize()
    {
        if(VLK_NULL != handle_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        handle_ = VLK_DLOPEN(VLK_VULKANLIB);
        if(VLK_NULL == handle_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

#define VLK_EXPORTED_FUNCTION(name) VLK_GET_FUNCTION(name, "Error: cannot get exported %s\n")
#define VLK_INSTANCE_FUNCTION(name) VLK_GET_FUNCTION(name, "Error: cannot get instance function %s\n")
#define VLK_DEVICE_FUNCTION(name) VLK_GET_FUNCTION(name, "Error: cannot get device function %s\n")
#define VLK_PHYSICALDEVICE_FUNCTION(name) VLK_GET_FUNCTION(name, "Error: cannot get physicaldevice function %s\n")

#define VLK_EXT_EXPORTED_FUNCTION(name) VLK_GET_FUNCTION_WARN(name, "Warning: cannot get exported extension %s\n")

#define VLK_GET_FUNCTION(name, message) name = (PFN_ ## name)VLK_DLSYM(handle_, #name);\
    if(VLK_NULL == name){\
        PRINT1_ERR(message, #name);\
        return VK_ERROR_INITIALIZATION_FAILED;\
    }

#define VLK_GET_FUNCTION_WARN(name, message) name = (PFN_ ## name)VLK_DLSYM(handle_, #name);\
    if(VLK_NULL == name){\
        PRINT1_WARN(message, #name);\
    }

#include "VkFunctions.inc"

#undef VLK_GET_FUNCTION
#undef VLK_GET_FUNCTION_WARN

        return VK_SUCCESS;
    }

    void Lib::terminate()
    {
#define VLK_EXPORTED_FUNCTION(name) name = VLK_NULL;
#define VLK_INSTANCE_FUNCTION(name) name = VLK_NULL;
#define VLK_DEVICE_FUNCTION(name) name = VLK_NULL;
#define VLK_PHYSICALDEVICE_FUNCTION(name) name = VLK_NULL;

#define VLK_EXT_EXPORTED_FUNCTION(name) name = VLK_NULL;
#include "VkFunctions.inc"

        if(VLK_NULL != handle_){
            VLK_DLCLOSE(handle_);
            handle_ = VLK_NULL;
        }
    }

    VkResult Lib::createInstance(Instance& instance, const VkInstanceCreateInfo* createInfo, const VkAllocationCallbacks* allocator)
    {
        if(instance.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result = vkCreateInstance(createInfo, allocator, &instance.instance_);
        if(VK_SUCCESS != result){
            return result;
        }

        result = instance.initialize();
        if(VK_SUCCESS != result){
            vkDestroyInstance(instance.instance_, allocator);
            instance.instance_ = VLK_NULL;
            return result;
        }

        instance.allocator_ = allocator;
        return VK_SUCCESS;
    }

    //--------------------------------------------------------------
    //---
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------
    VkResult PhysicalDevice::createDevice(Device& device, const VkDeviceCreateInfo* createInfo, const VkAllocationCallbacks* allocator)
    {
        VLK_ASSERT(VLK_NULL != createInfo);
        VLK_ASSERT(0<createInfo->queueCreateInfoCount);

        if(device.valid()){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result = vkCreateDevice(device_, createInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return result;
        }

        // get queues
        switch(createInfo->queueCreateInfoCount)
        {
        case 1:
            vkGetDeviceQueue(device, createInfo->pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::GraphicsQueue]);
            vkGetDeviceQueue(device, createInfo->pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::PresentQueue]);
            device.queueFamilyIndices_[Device::GraphicsQueue] = createInfo->pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::PresentQueue] = createInfo->pQueueCreateInfos[0].queueFamilyIndex;
            break;
        case 2:
            vkGetDeviceQueue(device, createInfo->pQueueCreateInfos[0].queueFamilyIndex, 0, &device.queues_[Device::GraphicsQueue]);
            vkGetDeviceQueue(device, createInfo->pQueueCreateInfos[1].queueFamilyIndex, 0, &device.queues_[Device::PresentQueue]);
            device.queueFamilyIndices_[Device::GraphicsQueue] = createInfo->pQueueCreateInfos[0].queueFamilyIndex;
            device.queueFamilyIndices_[Device::PresentQueue] = createInfo->pQueueCreateInfos[1].queueFamilyIndex;
            break;
        default:
            vkDestroyDevice(device.device_, allocator);
            device.device_ = VLK_NULL;
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        device.numQueues_ = createInfo->queueCreateInfoCount;
        device.allocator_ = allocator;

        result = device.initialize();
        if(VK_SUCCESS != result){
            vkDestroyDevice(device.device_, allocator);
            device.device_ = VLK_NULL;
            device.allocator_ = VLK_NULL;
            device.numQueues_ = 0;
            return result;
        }

        for(u32 i=0; i<device.numQueues_; ++i){
            vkGetDeviceQueue(device, createInfo->pQueueCreateInfos[i].queueFamilyIndex, 0, &device.queues_[i]);
        }
        return result;
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(VLK_NULL)
        ,presentSurface_(VLK_NULL)
        ,allocator_(VLK_NULL)
#define VLK_EXT_INSTANCE_FUNCTION(name) ,name ## _(VLK_NULL)
#include "VkFunctions.inc"
    {
    }

    Instance::Instance(Instance&& rhs)
        :instance_(rhs.instance_)
        ,presentSurface_(rhs.presentSurface_)
        ,allocator_(rhs.allocator_)
#define VLK_EXT_INSTANCE_FUNCTION(name) ,name ## _(rhs.name ## _)
#include "VkFunctions.inc"
    {
        rhs.instance_ = VLK_NULL;
        rhs.presentSurface_ = VLK_NULL;
        rhs.allocator_ = VLK_NULL;
#define VLK_EXT_INSTANCE_FUNCTION(name) rhs.name ## _ = VLK_NULL;
#include "VkFunctions.inc"
    }

    Instance::~Instance()
    {
        destroy();
    }

    void Instance::destroy()
    {
        if(VLK_NULL != presentSurface_){
            vkDestroySurfaceKHR(presentSurface_, allocator_);
            presentSurface_ = VLK_NULL;
        }

        if(VLK_NULL == instance_){
            return;
        }

#define VLK_EXT_INSTANCE_FUNCTION(name) name ## _ = VLK_NULL;
#include "VkFunctions.inc"

        vkDestroyInstance(instance_, allocator_);
        instance_ = VLK_NULL;
        allocator_ = VLK_NULL;
    }

    Instance& Instance::operator=(Instance&& rhs)
    {
        if(this == &rhs){
            return *this;
        }
        instance_ = rhs.instance_;
        presentSurface_ = rhs.presentSurface_;
        allocator_ = rhs.allocator_;
#define VLK_EXT_INSTANCE_FUNCTION(name) name ## _ = rhs.name ## _;
#include "VkFunctions.inc"

        rhs.instance_ = VLK_NULL;
        rhs.presentSurface_ = VLK_NULL;
        rhs.allocator_ = VLK_NULL;
#define VLK_EXT_INSTANCE_FUNCTION(name) rhs.name ## _ = VLK_NULL;
#include "VkFunctions.inc"
        return *this;
    }

    PhysicalDevices Instance::enumeratePhysicalDevices()
    {
        u32 deviceCount = PhysicalDevices::MaxDevices;
        VkPhysicalDevice devices[PhysicalDevices::MaxDevices];
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
        if(VLK_NULL != presentSurface_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }
#ifdef VK_USE_PLATFORM_XLIB_KHR
        VkResult result = vkCreateXlibSurfaceKHR(&createInfo, allocator, &surface.surface_);
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
        VkResult result = vkCreateXcbSurfaceKHR(&createInfo, allocator, &surface.surface_);
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        VkResult result = vkCreateWaylandSurfaceKHR(&createInfo, allocator, &surface.surface_);
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
        VkResult result = vkCreateMirSurfaceKHR(&createInfo, allocator, &surface.surface_);
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
        VkResult result = vkCreateAndroidSurfaceKHR(&createInfo, allocator, &surface.surface_);
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
        VkResult result = vkCreateWin32SurfaceKHR(&createInfo, allocator_, &presentSurface_);
#endif
        return result;

    }

    VkResult Instance::initialize()
    {
        VLK_ASSERT(VLK_NULL != instance_);

#define VLK_EXT_INSTANCE_FUNCTION(name) if(VLK_NULL == name ## _) name ## _ = (PFN_ ## name)vkGetInstanceProcAddr(instance_, #name);\
    if(VLK_NULL == name ## _){\
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
        :device_(VLK_NULL)
        ,swapchain_(VLK_NULL)
        ,numQueues_(0)
        ,semaphoreImageAvailable_(VLK_NULL)
        ,semaphoreRenderingFinished_(VLK_NULL)
        ,swapchainImageCount_(0)
        ,presentQueueCommandPool_(VLK_NULL)
        ,allocator_(VLK_NULL)
#define VLK_EXT_DEVICE_FUNCTION(name) ,name ## _(VLK_NULL)
#include "VkFunctions.inc"
    {
        clearColor_ = {0x00U, 0x00U, 0x00U, 0xFFU};
        for(u32 i=0; i<MaxQueues; ++i){
            queueFamilyIndices_[i] = 0;
            queues_[i] = VLK_NULL;
        }
        for(u32 i=0; i<MaxSwapchainImages; ++i){
            swapchainImages_[i] = VLK_NULL;
            presentQueueCommandBuffers_[i] = VLK_NULL;
        }
    }

    Device::~Device()
    {
        destroy();
    }

    void Device::destroy()
    {
        if(VLK_NULL != device_ && VLK_NULL != swapchain_){
            clearCommandBuffers();
        }

        if(VLK_NULL != swapchain_){
            vkDestroySwapchainKHR_(device_, swapchain_, allocator_);
            swapchain_ = VLK_NULL;
        }
        if(VLK_NULL == device_){
            return;
        }
        vkDestroySemaphore(device_, semaphoreRenderingFinished_, allocator_);
        semaphoreRenderingFinished_ = VLK_NULL;
        vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
        semaphoreImageAvailable_ = VLK_NULL;

#define VLK_EXT_DEVICE_FUNCTION(name) name ## _ = VLK_NULL;
#include "VkFunctions.inc"

        swapchainImageCount_ = 0;
        vkDestroyDevice(device_, allocator_);

        for(u32 i=0; i<numQueues_; ++i){
            queueFamilyIndices_[i] = 0;
            queues_[i] = VLK_NULL;
        }

        device_ = VLK_NULL;
        numQueues_ = 0;
        allocator_ = VLK_NULL;
    }

    VkResult Device::createSwapchain(VkSwapchainCreateInfoKHR& createInfo)
    {
        VLK_ASSERT(VLK_NULL != device_);

        VkSwapchainKHR swapchain = swapchain_;
        createInfo.oldSwapchain = swapchain;
        VkResult result;
        if(VK_SUCCESS != (result = vkCreateSwapchainKHR_(device_, &createInfo, allocator_, &swapchain_))){
            return result;
        }
        swapchainCreateInfo_ = createInfo;
        if(swapchain != VLK_NULL){
            vkDestroySwapchainKHR_(device_, swapchain, allocator_);
        }

        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR_(device_, swapchain_, &swapchainImageCount_, VLK_NULL)) || swapchainImageCount_<=0){
            return result;
        }
        swapchainImageCount_ = minimum(swapchainImageCount_, MaxSwapchainImages);
        return result;
    }

    VkResult Device::createCommandBuffers()
    {
        VLK_ASSERT(VLK_NULL != device_);
        VLK_ASSERT(VLK_NULL != swapchain_);

        VkResult result;

        VkCommandPoolCreateInfo commandPoolCreateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            VLK_NULL,
            0,
            queueFamilyIndices_[PresentQueue],
        };
        if(VK_SUCCESS != (result = vkCreateCommandPool(device_, &commandPoolCreateInfo, allocator_, &presentQueueCommandPool_))){
            return result;
        }

        VkCommandBufferAllocateInfo commandBufferAllocateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            VLK_NULL,
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
        VLK_ASSERT(VLK_NULL != device_);
        VLK_ASSERT(VLK_NULL != swapchain_);

        VkResult result;
        if(VK_SUCCESS != (result = vkDeviceWaitIdle(device_))){
            return result;
        }

        if(0<swapchainImageCount_){
            vkFreeCommandBuffers(device_, presentQueueCommandPool_, swapchainImageCount_, presentQueueCommandBuffers_);
            swapchainImageCount_ = 0;
        }

        if(VLK_NULL != presentQueueCommandPool_){
            vkDestroyCommandPool(device_, presentQueueCommandPool_, allocator_);
            presentQueueCommandPool_ = VLK_NULL;
        }
        return VK_SUCCESS;
    }

    VkResult Device::recordCommandBuffers()
    {
        VLK_ASSERT(VLK_NULL != device_);
        VLK_ASSERT(VLK_NULL != swapchain_);
        VkResult result;
        if(VK_SUCCESS != (result = vkGetSwapchainImagesKHR_(device_, swapchain_, &swapchainImageCount_, swapchainImages_))){
            return result;
        }
        VkCommandBufferBeginInfo commandBufferBeginInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, //structure type
            VLK_NULL,
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, //flags
            VLK_NULL,
        };
        VkImageSubresourceRange imageSubresourceRange =
        {
            VK_IMAGE_ASPECT_COLOR_BIT, //flags
            0, 1, 0, 1,
        };

        VkImageMemoryBarrier barrierFromPresentToClear =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            VLK_NULL,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            VLK_NULL,
            imageSubresourceRange,
        };

        VkImageMemoryBarrier barrierFromClearToPresent =
        {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
            VLK_NULL,
            VK_ACCESS_TRANSFER_WRITE_BIT,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_QUEUE_FAMILY_IGNORED,
            VK_QUEUE_FAMILY_IGNORED,
            VLK_NULL,
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
                VLK_NULL,
                0,
                VLK_NULL,
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
                VLK_NULL,
                0,
                VLK_NULL,
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
        result = vkAcquireNextImageKHR_(device_, swapchain_, UINT64_MAX, semaphoreImageAvailable_, VLK_NULL, &imageIndex);
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
            VLK_NULL,
            1,
            &semaphoreImageAvailable_,
            &waitDstStageMask,
            1,
            &presentQueueCommandBuffers_[imageIndex],
            1,
            &semaphoreRenderingFinished_,
        };
        if(VK_SUCCESS != (result = vkQueueSubmit(queues_[PresentQueue], 1, &submitInfo, VLK_NULL))){
            return false;
        }

        VkPresentInfoKHR presentInfo =
        {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            VLK_NULL,
            1,
            &semaphoreRenderingFinished_,
            1,
            &swapchain_,
            &imageIndex,
            VLK_NULL,
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

    VkResult Device::initialize()
    {
        VLK_ASSERT(VLK_NULL != device_);

        // create semaphores
        VkSemaphoreCreateInfo semaphoreCreateInfo =
        {
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, //structure type
            VLK_NULL,
            0,//flags
        };

        VkResult result;
        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator_, &semaphoreImageAvailable_))){
            return result;
        }
        if(VK_SUCCESS != (result = vkCreateSemaphore(device_, &semaphoreCreateInfo, allocator_, &semaphoreRenderingFinished_))){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator_);
            semaphoreImageAvailable_ = VLK_NULL;
            return result;
        }

#define VLK_EXT_DEVICE_FUNCTION(name) if(VLK_NULL == name ## _) name ## _ = (PFN_ ## name)vkGetDeviceProcAddr(device_, #name);\
    if(VLK_NULL == name ## _){\
        PRINT1_WARN("Warning: cannot get device function %s via vkGetDeviceProcAddr\n", #name);\
    }

#include "VkFunctions.inc"

        return VK_SUCCESS;
    }

}
