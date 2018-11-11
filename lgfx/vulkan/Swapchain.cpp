/**
@file Swapchain.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    LGFX_RESULT Swapchain::create(Swapchain& swapchain, Device& device, SwapchainBuilderVulkan& builder)
    {
        LGFX_ASSERT(device.valid());

        const VkAllocationCallbacks* allocator = System::instance().getAllocator();
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
        if(!builder.checkSurfaceCapabilities_(imageUsageFlags, imagePreTransform, compositeAlpha, surfaceCapabilities)){
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
        presentMode = builder.getPresentMode_(countPresentModes, presentModes, static_cast<VkPresentModeKHR>(swapchainCreateInfo.presentMode_));

        //--- Check surface formats
        //-------------------------------------------------------------
        VkSurfaceFormatKHR surfaceFormats[LGFX_MAX_SURFACEFORMATS];
        u32 countSurfaceFormats = LGFX_MAX_SURFACEFORMATS;
        result = instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, presentationSurface, &countSurfaceFormats, surfaceFormats);
        if(VK_SUCCESS != result || countSurfaceFormats<=0){
            return LGFX_VK_TO_RESULT(result);
        }
        if(!builder.checkSurfaceFormats_(surfaceFormat, countSurfaceFormats, surfaceFormats, swapchainCreateInfo.supportHDR_)){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

        VkSwapchainCreateInfoKHR createInfo ={
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


        if(swapchain.swapchain_.valid()){
            createInfo.oldSwapchain = (VkSwapchainKHR)swapchain.swapchain_;
        }

        VkSwapchainKHR vkSwapchain = LGFX_NULL;
        if(VK_SUCCESS != (result = device.vkCreateSwapchainKHR(device, &createInfo, allocator, &vkSwapchain))){
            createInfo.oldSwapchain = LGFX_NULL;
            return LGFX_VK_TO_RESULT(result);
        }

        swapchain.destroy();
        swapchain.swapchain_ = Handle::allocate(device.getID(), vkSwapchain);

        swapchain.numImages_ = MaxSwapchainImages;
        if(VK_SUCCESS != (result = device.vkGetSwapchainImagesKHR(device, vkSwapchain, &swapchain.numImages_, swapchain.images_))){
            swapchain.destroy();
            return LGFX_VK_TO_RESULT(result);
        }
        LGFX_ASSERT(0<swapchain.numImages_);
        swapchain.width_ = surfaceExtent.width;
        swapchain.height_ = surfaceExtent.height;
        swapchain.format_ = surfaceFormat.format;
        return LGFX_SUCCESS;
    }

    Swapchain::Swapchain()
        :swapchain_(Handle::invalid())
        ,format_(VK_FORMAT_UNDEFINED)
        ,numImages_(0)
    {
    }

    Swapchain::~Swapchain()
    {}

    void Swapchain::destroy()
    {
        if(!valid()){
            return;
        }
        System& system = System::instance();
        Device& device = system.getDevice(swapchain_.device());
        utils::destroy(swapchain_, device.vkDestroySwapchainKHR);
        numImages_ = 0;
    }

    Swapchain::operator const VkSwapchainKHR() const
    {
        return (VkSwapchainKHR)swapchain_;
    }

    Swapchain::operator VkSwapchainKHR()
    {
        return (VkSwapchainKHR)swapchain_;
    }

    void Swapchain::swap(Swapchain& rhs)
    {
        swapchain_.swap(rhs.swapchain_);
        lgfx::swap(format_, rhs.format_);
        lgfx::swap(numImages_, rhs.numImages_);

        LGFX_SWAP(images_, rhs.images_, MaxSwapchainImages);
    }
}
