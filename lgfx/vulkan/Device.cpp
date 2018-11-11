/**
@file Device.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

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
    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    Device::Device()
        :id_(0)
        ,device_(LGFX_NULL)
        ,presentCommandPool_(LGFX_NULL)
#define LGFX_VK_EXT_DEVICE_FUNCTION(name) ,name(LGFX_NULL)
#include "VkFunctions.inc"
    {
        for(u32 i=0; i<QueueType_Max; ++i){
            queues_[i].handle_ = LGFX_NULL;
        }
        clearColor_.float32[0] = 0.0f;
        clearColor_.float32[1] = 0.0f;
        clearColor_.float32[2] = 0.0f;
        clearColor_.float32[3] = 1.0f;

        LGFX_SETNULL(renderPasses_, LGFX_MAX_RENDERPASSES);
        LGFX_SETNULL(imageViews_, Swapchain::MaxSwapchainImages);
        LGFX_SETNULL(frameBuffers_, Swapchain::MaxSwapchainImages);
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
        SwapchainBuilderVulkan& swapchainBuilder)
    {
        LGFX_ASSERT(physicalDevice.valid());
        LGFX_ASSERT(0<deviceCreateInfo.queueCreateInfoCount);

        if(device.valid()){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }
        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        VkResult result;
        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return LGFX_VK_TO_RESULT(result);
        }
        device.physicalDevice_ = physicalDevice;
        device.initialize();

        result = static_cast<VkResult>(Swapchain::create(device.swapchain_, device, swapchainBuilder));
        if(VK_SUCCESS != result){
            device.destroy();
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

            vkGetDeviceQueue(device, queueFamilyIndex, queueIndices[queueFamilyIndex], &device.queues_[i].handle_);
            device.queues_[i].familyIndex_ = queueFamilyIndex;
            device.queues_[i].index_ = queueIndices[queueFamilyIndex];
            ++queueIndices[queueFamilyIndex];
        }


        result = device.createSemaphores();
        if(VK_SUCCESS != result){
            device.destroy();
            return LGFX_VK_TO_RESULT(result);
        }

        result = device.createCommandBuffers();
        if(VK_SUCCESS != result){
            device.destroy();
            return LGFX_VK_TO_RESULT(result);
        }

        device.swapchainBuilder_ = swapchainBuilder;
        return LGFX_VK_TO_RESULT(result);
    }

    void Device::destroy()
    {
        if(!valid()){
            return;
        }
        waitIdle();

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        LGFX_DEVICE_DESTROY(frameBuffers_, Swapchain::MaxSwapchainImages, vkDestroyFramebuffer, device_, allocator);
        LGFX_DEVICE_DESTROY(imageViews_, Swapchain::MaxSwapchainImages, vkDestroyImageView, device_, allocator);
        LGFX_DEVICE_DESTROY(renderPasses_, LGFX_MAX_RENDERPASSES, vkDestroyRenderPass, device_, allocator);

        destroyCommandBuffers();
        destroySemaphores();

        for(s32 i=0; i<QueueType_Max; ++i){
            queues_[i].handle_ = LGFX_NULL;
        }

        swapchain_.destroy();

        Swapchain().swap(swapchain_);
        swapchainBuilder_.instance_ = LGFX_NULL;

        vkDestroyDevice(device_, allocator);
        device_ = LGFX_NULL;

        PhysicalDevice().swap(physicalDevice_);
    }

    void Device::setID(s32 id)
    {
        id_ = id;
    }

    LGFX_RESULT Device::waitIdle()
    {
        LGFX_ASSERT(LGFX_NULL != device_);
        return LGFX_VK_TO_RESULT(vkDeviceWaitIdle(device_));
    }

    bool Device::onWindowSizeChanged()
    {
        waitIdle();

        destroyCommandBuffers();

        VkResult result;
        //Rebuild swapchain
        result = static_cast<VkResult>(Swapchain::create(swapchain_, *this, swapchainBuilder_));
        if(VK_SUCCESS != result){
            destroy();
            return false;
        }

        result = createCommandBuffers();
        if(VK_SUCCESS != result){
            destroy();
            return false;
        }
        return true;
    }

    bool Device::present()
    {
        VkResult result;

        //acquire available image index
        u32 imageIndex;
        result = vkAcquireNextImageKHR(device_, swapchain_, UINT64_MAX, semaphoreImageAvailable_, LGFX_NULL, &imageIndex);
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
            LGFX_NULL, //next
            1, //wait semaphore count
            &semaphoreImageAvailable_, //wait semaphores
            &waitDstStageMask, //wait destination stage mask
            1, //command buffer count
            &presentCommandBuffers_[imageIndex], //command buffers
            1,
            &semaphoreRenderingFinished_,
        };
        if(VK_SUCCESS != (result = vkQueueSubmit(queues_[QueueType_Present].handle_, 1, &submitInfo, LGFX_NULL))){
            return false;
        }

        VkSwapchainKHR swapchain = swapchain_;
        VkPresentInfoKHR presentInfo =
        {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR, //structure type
            LGFX_NULL, //next
            1, //wait semaphore count
            &semaphoreRenderingFinished_, //wait semaphores
            1, //swapchain count
            &swapchain, //swapchains
            &imageIndex, //image indices
            LGFX_NULL, //results
        };
        result = vkQueuePresentKHR(queues_[QueueType_Present].handle_, &presentInfo);
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

    bool Device::addRenderPass(s32 index)
    {
        LGFX_ASSERT(0<=index && index<LGFX_MAX_RENDERPASSES);
        VkAttachmentDescription attachmentDescriptions[] ={
            {
                0, //VkAttachmentDescriptionFlagBits
                swapchain_.getFormat(), //swapchain format
                VK_SAMPLE_COUNT_1_BIT, //VkSampleCountFlagBits
                VK_ATTACHMENT_LOAD_OP_CLEAR, //VkAttachmentLoadOp color load operation
                VK_ATTACHMENT_STORE_OP_STORE, //VkAttachmentStoreOp color store operation
                VK_ATTACHMENT_LOAD_OP_DONT_CARE, //VkAttachmentLoadOp stencil load operation
                VK_ATTACHMENT_STORE_OP_DONT_CARE, //VkAttachmentStoreOp stencil store operation
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, //VkImageLayout initial layout
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, //VkImageLayout final layout
            },
        };

        VkAttachmentReference colorAttachmentReferneces[] ={
            {
                0, //attachment
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, //layout
            },
        };

        VkSubpassDescription subpassDescriptions[] ={
            {
                0, //VkSubpassDescriptionFlagsBits
                VK_PIPELINE_BIND_POINT_GRAPHICS, //VkPipelineBindPoint 
                0, //input attachment count
                LGFX_NULL, //input attachments
                1, //color attachment count
                colorAttachmentReferneces, //color attachments
                LGFX_NULL, //resolbe attachments
                LGFX_NULL, //depth stencil attachment
                0, //preserve attachment count
                LGFX_NULL, //preserve attachments
            },
        };
        VkRenderPassCreateInfo renderPassCreateInfo ={
            VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkRenderPassCreateFlags
            1, //attachment count
            attachmentDescriptions, //attachments
            1, //subpass count
            subpassDescriptions, //subpasses
            0, //dependency count
            LGFX_NULL,
        };

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();
        VkRenderPass renderPass = LGFX_NULL;
        if(VK_SUCCESS != vkCreateRenderPass(device_, &renderPassCreateInfo, allocator, &renderPass)){
            return false;
        }

        for(s32 i=0; i<swapchain_.getNumImages(); ++i){
            //VkImageViewCreateInfo imageViewCreateInfo = {
            //    VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, //structure type
            //    LGFX_NULL, //next
            //    0, //VkImageViewCreateFlags
            //    swapchain.getImage(i), //image
            //    VK_IMAGE_VIEW_TYPE_2D, //image view type
            //    swapchain.getFormat(), //format
            //    {VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A}, //VkComponentMapping for swizzling
            //    {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}, //VkImageSubresourceRange
            //};

            //if(VK_SUCCESS != vkCreateImageView(device_, &imageViewCreateInfo, allocator_, &imageViews_[i])){
            //    Swapchain::destroy(swapchain, device, allocator);
            //    return false;
            //}

            VkFramebufferCreateInfo framebufferCreateInfo ={
                VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, //structure type
                LGFX_NULL, //next
                0, //VkFramebufferCreateFlags
                renderPass, //associated render pass
                1, //attachment count,
                &imageViews_[i], //attachments
                swapchain_.width(), //width
                swapchain_.height(), //height
                1, //layers
            };
            //if(VK_SUCCESS != vkCreateFrameBuffer(device_, &framebufferCreateInfo, allocator_, &swapchain_.frameBuffers_[i])){
            //    Swapchain::destroy(swapchain_, device_, allocator_);
            //    return false;
            //}
        }
        return true;
    }

    bool Device::createShader(Shader& shader, u64 size, const u8* binary)
    {
        VkShaderModuleCreateInfo createInfo =
        {
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkShaderModuleCreateFlags
            size,
            reinterpret_cast<const u32*>(binary),
        };

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();
        VkShaderModule shaderModule;
        if(VK_SUCCESS != vkCreateShaderModule(device_, &createInfo, allocator, &shaderModule)){
            return false;
        }
        Shader(getID(), shaderModule).swap(shader);
        return true;
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

    VkResult Device::createSemaphores()
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

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

    VkResult Device::createCommandBuffers()
    {
        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        //Create a command pool for presentation
        VkCommandPoolCreateInfo commandPoolCreateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkCommandPoolCreateFlagBits
            queues_[QueueType_Present].familyIndex_, //queueFamilyIndex
        };

        VkResult result;
        if(VK_SUCCESS != (result = vkCreateCommandPool(device_, &commandPoolCreateInfo, allocator, &presentCommandPool_))){
            return result;
        }

        u32 swapchainImageCount = swapchain_.getNumImages();
        if(swapchainImageCount<=0){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        presentCommandBuffers_.resize(swapchainImageCount);
        VkCommandBufferAllocateInfo commandBufferAllocateInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, //structure type
            LGFX_NULL, //next
            presentCommandPool_, //command pool
            VK_COMMAND_BUFFER_LEVEL_PRIMARY, //VkCommandBufferLevel
            swapchainImageCount, //command buffer count
        };
        if(VK_SUCCESS != (result = vkAllocateCommandBuffers(device_, &commandBufferAllocateInfo, &presentCommandBuffers_[0]))){
            return result;
        }

        if(VK_SUCCESS != (result = recordClearCommands())){
            return result;
        }
        return VK_SUCCESS;
    }

    void Device::destroySemaphores()
    {
        LGFX_ASSERT(LGFX_NULL != device_);

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        if(LGFX_NULL != semaphoreRenderingFinished_){
            vkDestroySemaphore(device_, semaphoreRenderingFinished_, allocator);
            semaphoreRenderingFinished_ = LGFX_NULL;
        }
        if(LGFX_NULL != semaphoreImageAvailable_){
            vkDestroySemaphore(device_, semaphoreImageAvailable_, allocator);
            semaphoreImageAvailable_ = LGFX_NULL;
        }
    }

    void Device::destroyCommandBuffers()
    {
        const VkAllocationCallbacks* allocator = System::instance().getAllocator();

        if(0<presentCommandBuffers_.size()){
            vkFreeCommandBuffers(device_, presentCommandPool_, static_cast<u32>(presentCommandBuffers_.size()), &presentCommandBuffers_[0]);
            presentCommandBuffers_.clear();
        }
        if(LGFX_NULL != presentCommandPool_){
            vkDestroyCommandPool(device_, presentCommandPool_, allocator);
            presentCommandPool_ = LGFX_NULL;
        }
    }

    VkResult Device::recordClearCommands()
    {
        VkCommandBufferBeginInfo commandBufferBeginInfo =
        {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, //structure type
            LGFX_NULL, //next
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, //VkCommandBufferUsageFlagBits
            LGFX_NULL, //VkCommandBufferInheritanceInfo
        };

        VkImageSubresourceRange imageSubresourceRange =
        {
            VK_IMAGE_ASPECT_COLOR_BIT, //VkImageAspectFlagBits
            0, //base mip level
            1, //level count
            0, //base array layer
            1, //layer count
        };

        VkResult result;
        for(s32 i=0; i<swapchain_.getNumImages(); ++i){
            VkImageMemoryBarrier barrierFromPresentToClear =
            {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
                LGFX_NULL, //next
                VK_ACCESS_MEMORY_READ_BIT, //source access
                VK_ACCESS_TRANSFER_WRITE_BIT, //destination access
                VK_IMAGE_LAYOUT_UNDEFINED, //old layout
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, //new layout
                VK_QUEUE_FAMILY_IGNORED, //source queue family index
                VK_QUEUE_FAMILY_IGNORED, //destination queue family index
                swapchain_.getImage(i), //image
                imageSubresourceRange, //subresource range
            };

            VkImageMemoryBarrier barrierFromClearToPresent =
            {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, //structure type
                LGFX_NULL, //next
                VK_ACCESS_TRANSFER_WRITE_BIT, //source access
                VK_ACCESS_MEMORY_READ_BIT, //destination access
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, //old layout
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, //new layout
                VK_QUEUE_FAMILY_IGNORED, //source queue family index
                VK_QUEUE_FAMILY_IGNORED, //destination queue family index
                swapchain_.getImage(i), //image
                imageSubresourceRange, //subresource range
            };

            vkBeginCommandBuffer(presentCommandBuffers_[i], &commandBufferBeginInfo);
            vkCmdPipelineBarrier(
                presentCommandBuffers_[i], //command buffer
                VK_PIPELINE_STAGE_TRANSFER_BIT, //source stage mask
                VK_PIPELINE_STAGE_TRANSFER_BIT, //destination stage mask
                0, //VkDependencyFlagBits
                0, //memory barrier count
                LGFX_NULL, //memory barriers
                0, //buffer memory barrier count
                LGFX_NULL, //buffer memory barries
                1, //image memory barrier count
                &barrierFromPresentToClear); //image memory barries

            vkCmdClearColorImage(
                presentCommandBuffers_[i], //command buffer
                swapchain_.getImage(i), //image
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, //image layout
                &clearColor_, //clea color
                1, //range count
                &imageSubresourceRange); //subresource range

            vkCmdPipelineBarrier(
                presentCommandBuffers_[i], //command buffer
                VK_PIPELINE_STAGE_TRANSFER_BIT, //source stage mask
                VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, //destination stage mask
                0, //VkDependencyFlagBits
                0, //memory barrier count
                nullptr, //memory barriers
                0, //buffer memory barrier count
                nullptr, //buffer memory barries
                1, //image memory barrier count
                &barrierFromClearToPresent); //image memory barries

            if(VK_SUCCESS != (result = vkEndCommandBuffer(presentCommandBuffers_[i]))){
                return result;
            }
        }
        return VK_SUCCESS;
    }
}
