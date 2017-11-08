#include "cppvk.h"
#include <stdio.h>

#include "Window.h"

typedef vk::ExtensionProperties<32> ExtensionProperties;

bool selectQueueFamily(vk::PhysicalDevice& physicalDevice, vk::u32& selectedGraphicsQueueFamily, vk::u32& selectedPresentQueueFamily, vk::Instance& instance);
bool selectPhysicalDevice(vk::PhysicalDevice& selectedDevice, vk::u32& selectedGraphicsQueueFamily, vk::u32& selectedPresentQueueFamily, vk::s32 numExtensions, const vk::Char** extensions, vk::Instance& instance);
bool selectPresentMode(
    VkSurfaceFormatKHR& selectedFormat,
    VkPresentModeKHR& selectedMode,
    vk::u32 width,
    vk::u32 height,
    vk::u32 swapChainImages,
    VkImageUsageFlags supportedFlags,
    VkSurfaceTransformFlagsKHR supportedTransform,
    VkFormat format,
    VkColorSpaceKHR colorSpace,
    VkPresentModeKHR mode,
    vk::Instance& instance,
    vk::PhysicalDevice& physicalDevice);

bool checkInstanceExtensions(vk::s32 numExtensions, const vk::Char** extensions);
bool checkDeviceExtensions(vk::PhysicalDevice& physicalDevice, vk::s32 numExtensions, const vk::Char** extensions);

void printInstanceExtensions();
void printDeviceExtentions(vk::PhysicalDevice& physicalDevice);

int main(int /*argc*/, char** /*argv*/)
{
    static const vk::u32 Width = 400;
    static const vk::u32 Height = 300;

    //Load library
    vk::Lib lib;
    if(VK_SUCCESS != lib.initialize()){
        fprintf(stderr, "Fail to initialize lib\n");
        return 0;
    }

    //Create a window
    lgfx::Window window;
    {
        lgfx::Window::InitParam param;
        param.instance_ = VLK_NULL;
        param.width_ = Width;
        param.height_ = Height;
        param.style_ = 0;
        param.exStyle_ = 0;
        param.wndProc_ = VLK_NULL;
        param.title_ = "Vulkan Sample";
        param.windowed_ = true;
        if(!window.create(param)){
            return 0;
        }
    }

    vk::Instance instance;
    vk::Device device;
    {
        printInstanceExtensions();

        // Check instance extensions
        //---------------------------------------------------------------------
        const vk::Char* instanceExtensions[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_WIN32_KHR)
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XCB_KHR)
            VK_KHR_XCB_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
            VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#endif
        };
        if(!checkInstanceExtensions(sizeof(instanceExtensions)/sizeof(instanceExtensions[0]), instanceExtensions)){
            return 0;
        }

        // Create an instance
        //---------------------------------------------------------------------
        VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, //structure type
            VLK_NULL,
            "Tutorial Vulkan", //application name
            VK_MAKE_VERSION(1,0,0), //application version
            "Tutorial Engine", //engine name
            VK_MAKE_VERSION(1,0,0), //engine version
            VK_API_VERSION_1_0, //api version
        };
        VkInstanceCreateInfo instanceCreateInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //structure type
            VLK_NULL,
            0, //instance creation flags
            &applicationInfo, //application info
            0, //enabled layer count
            VLK_NULL, //enabled layer names
            sizeof(instanceExtensions)/sizeof(instanceExtensions[0]), //enabled extension count
            instanceExtensions, //enabled extension names
        };
        if(VK_SUCCESS != lib.createInstance(instance, &instanceCreateInfo, VLK_NULL)){
            fprintf(stderr, "Fail to create an instance\n");
            return 0;
        }

        // Create a presentation surface
        //---------------------------------------------------------------------
#ifdef VK_USE_PLATFORM_WIN32_KHR
        vk::Instance::SurfaceCreateInfo surfaceCreateInfo =
        {
            VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, //structure type
            VLK_NULL,
            0, //flags
            window.getInstance(),
            window.getHandle(),
        };
#endif
        if(VK_SUCCESS != instance.createPresentSurface(surfaceCreateInfo)){
            fprintf(stderr, "Fail to a presentation surface\n");
            return 0;
        }

        // Create a device
        //---------------------------------------------------------------------
        vk::PhysicalDevice physicalDevice;
        vk::u32 graphicsQueueFamily, presentQueueFamily;
        const vk::Char* deviceExtensions[] = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };
        if(!selectPhysicalDevice(physicalDevice, graphicsQueueFamily, presentQueueFamily, sizeof(deviceExtensions)/sizeof(deviceExtensions[0]), deviceExtensions, instance)){
            fprintf(stderr, "Fail to find a physical device\n");
            return 0;
        }

        // Create a logical device
        //---------------------------------------------------------------------
        vk::u32 numQueues = 1;
        if(graphicsQueueFamily != presentQueueFamily){
            ++numQueues;
        }

        VkDeviceQueueCreateInfo queueCreateInfo[vk::MaxProperties];
        const float queuePriorities[] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f};
        queueCreateInfo[0] = {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //structure type
            VLK_NULL,
            0, //device queue creation flags
            graphicsQueueFamily, //selected queue family's index
            numQueues, //queue count
            queuePriorities, //queue priorities
        };
        if(graphicsQueueFamily != presentQueueFamily){
            queueCreateInfo[1] = {
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //structure type
                VLK_NULL,
                0, //device queue creation flags
                presentQueueFamily, //selected queue family's index
                numQueues, //queue count
                queuePriorities, //queue priorities
            };
        }


        VkDeviceCreateInfo deviceCreateInfo = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //structure type
            VLK_NULL,
            0, //device creation flags
            numQueues, //queue create info count,
            queueCreateInfo, //queue create info
            0, //enabled layer count
            VLK_NULL, //enabled layer names
            sizeof(deviceExtensions)/sizeof(deviceExtensions[0]), //enabled extension count
            deviceExtensions, //enabled extension names
            VLK_NULL, //enabled physical device features
        };

        if(VK_SUCCESS != physicalDevice.createDevice(device, &deviceCreateInfo, VLK_NULL)){
            fprintf(stderr, "Fail to create device\n");
            return 0;
        }

        // Select a present mode and swap chain image formats
        //---------------------------------------------------------------------
        VkSurfaceFormatKHR surfaceFormat;
        VkPresentModeKHR presentMode;
        vk::u32 numSwapchainSurfaces = 2;
        if(!selectPresentMode(
            surfaceFormat,
            presentMode,
            Width,
            Height,
            numSwapchainSurfaces,
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT,
            VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
            VK_FORMAT_B8G8R8A8_UNORM,
            VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
            VK_PRESENT_MODE_FIFO_KHR,
            instance, physicalDevice))
        {
            fprintf(stderr, "Fail to find a swap chain image\n");
            return 0;
        }

        VkExtent2D swapchainExtent = {Width, Height};

        VkSwapchainCreateInfoKHR swapchainCreateInfo =
        {
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            VLK_NULL, //structure type
            0, //swapchain create flags
            instance.getPresentSurface(), //surface
            numSwapchainSurfaces, //num of surfaces
            surfaceFormat.format, //surface format
            surfaceFormat.colorSpace, //color space
            {Width, Height}, //image extent
            1, //image array layers
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT, //image usage
            VK_SHARING_MODE_EXCLUSIVE, //sharing mode
            1,
            &presentQueueFamily,
            VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            presentMode,
            VK_TRUE,
            VLK_NULL,
        };
        if(VK_SUCCESS != device.createSwapchain(swapchainCreateInfo)){
            fprintf(stderr, "Fail to create swapchain\n");
            return 0;
        }
        if(VK_SUCCESS != device.createCommandBuffers()){
            fprintf(stderr, "Fail to create command buffers\n");
            return 0;
        }
    }
    while(window.peekEvent()){
        device.present();
    }

    device.destroy();
    instance.destroy();

    window.destroy();
    lib.terminate();
    return 0;
}

bool selectQueueFamily(vk::PhysicalDevice& physicalDevice, vk::u32& selectedGraphicsQueueFamily, vk::u32& selectedPresentQueueFamily, vk::Instance& instance)
{
    VkQueueFamilyProperties queueProperties[vk::MaxProperties];

    // Get queue family properties
    vk::u32 countProperties = 0;
    physicalDevice.getPhysicalDeviceQueueFamilyProperties(&countProperties, VLK_NULL);
    countProperties = vk::minimum(countProperties, vk::MaxProperties);
    physicalDevice.getPhysicalDeviceQueueFamilyProperties(&countProperties, queueProperties);

    static const vk::u32 Invalid = static_cast<vk::u32>(-1);
    // 
    vk::u32 graphicsQueueFamily = Invalid;
    vk::u32 presentQueueFamily = Invalid;
    for(vk::u32 i=0; i<countProperties; ++i){
        //Skip invalid empty queue
        if(queueProperties[i].queueCount<=0){
            continue;
        }
        //Select first graphics supported queue
        if(queueProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
            if(Invalid == graphicsQueueFamily){
                graphicsQueueFamily = i;
                continue;
            }
        }
        //Select first queue that support the surface
        VkBool32 surfaceSupported = 0;
        instance.vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, instance.getPresentSurface(), &surfaceSupported);
        if(surfaceSupported){
            if(Invalid == presentQueueFamily){
                presentQueueFamily = i;
                continue;
            }
        }
    }
    if(Invalid == presentQueueFamily){
        for(vk::u32 i=0; i<countProperties; ++i){
            //Skip invalid empty queue
            if(queueProperties[i].queueCount<=0){
                continue;
            }
            //Select first queue that support the surface
            VkBool32 surfaceSupported = 0;
            instance.vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, instance.getPresentSurface(), &surfaceSupported);
            if(surfaceSupported){
                presentQueueFamily = i;
                break;
            }
        }
    }

    if(Invalid == graphicsQueueFamily || Invalid == presentQueueFamily){
        return false;
    }
    selectedGraphicsQueueFamily = graphicsQueueFamily;
    selectedPresentQueueFamily = presentQueueFamily;
    return true;
}

bool selectPhysicalDevice(vk::PhysicalDevice& selectedDevice, vk::u32& selectedGraphicsQueueFamily, vk::u32& selectedPresentQueueFamily, vk::s32 numExtensions, const vk::Char** extensions, vk::Instance& instance)
{
    vk::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
    for(vk::u32 i=0; i<physicalDevices.size(); ++i){
        vk::PhysicalDevice& physicalDevice = physicalDevices.getDevice(i);
        if(selectQueueFamily(physicalDevice, selectedGraphicsQueueFamily, selectedPresentQueueFamily, instance)){
            printDeviceExtentions(physicalDevice);
            if(checkDeviceExtensions(physicalDevice, numExtensions, extensions)){
                selectedDevice = physicalDevice;
                return true;
            }
        }
    }
    return false;
}

bool selectPresentMode(
    VkSurfaceFormatKHR& selectedFormat,
    VkPresentModeKHR& selectedMode,
    vk::u32 width,
    vk::u32 height,
    vk::u32 swapChainImages,
    VkImageUsageFlags supportedFlags,
    VkSurfaceTransformFlagsKHR supportedTransform,
    VkFormat format,
    VkColorSpaceKHR colorSpace,
    VkPresentModeKHR mode,
    vk::Instance& instance,
    vk::PhysicalDevice& physicalDevice)
{
    static const vk::u32 MaxSurfaceFormats = 16;
    static const vk::u32 MaxPresentModes = 8;
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vk::u32 numSurfaceFormats = 0;
    vk::u32 numPresentModes = 0;
    VkSurfaceFormatKHR surfaceFormats[MaxSurfaceFormats];
    VkPresentModeKHR presentModes[MaxPresentModes];

    VkSurfaceKHR surface = instance.getPresentSurface();
    if(VK_SUCCESS != instance.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities)){
        return false;
    }
    if(width<surfaceCapabilities.minImageExtent.width || surfaceCapabilities.maxImageExtent.width<width){
        return false;
    }
    if(height<surfaceCapabilities.minImageExtent.height || surfaceCapabilities.maxImageExtent.height<height){
        return false;
    }
    if(swapChainImages < surfaceCapabilities.minImageCount || surfaceCapabilities.maxImageCount<swapChainImages){
        return false;
    }

    //supported flags
    //---------------------------------------------------------------
    if(supportedFlags != (surfaceCapabilities.supportedUsageFlags & supportedFlags)){
        return false;
    }

    //supported transform
    //---------------------------------------------------------------
    if(supportedTransform != (surfaceCapabilities.supportedTransforms & supportedTransform)){
        return false;
    }

    selectedFormat.format = VK_FORMAT_UNDEFINED;
    instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &numSurfaceFormats, VLK_NULL);
    numSurfaceFormats = vk::minimum(numSurfaceFormats, MaxSurfaceFormats);
    instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &numSurfaceFormats, surfaceFormats);
    for(vk::u32 i=0; i<numSurfaceFormats; ++i){
        if(surfaceFormats[i].format == format && surfaceFormats[i].colorSpace == colorSpace){
            selectedFormat = surfaceFormats[i];
            break;
        }
    }
    if(VK_FORMAT_UNDEFINED == selectedFormat.format){
        return false;
    }

    selectedMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
    instance.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &numPresentModes, VLK_NULL);
    numPresentModes = vk::minimum(numPresentModes, MaxPresentModes);
    instance.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &numPresentModes, presentModes);
    for(vk::u32 i=0; i<numPresentModes; ++i){
        if(presentModes[i] == mode){
            selectedMode = presentModes[i];
            break;
        }
    }
    if(VK_PRESENT_MODE_MAX_ENUM_KHR == selectedMode){
        return false;
    }
    return true;
}

bool checkInstanceExtensions(vk::s32 numExtensions, const vk::Char** extensions)
{
    ExtensionProperties properties;
    if(VK_SUCCESS != properties.enumerateInstanceExtensionProperties(VLK_NULL)){
        fprintf(stderr, "Fail to enumerate instance extensions\n");
        return false;
    }

    for(vk::s32 i=0; i<numExtensions; ++i){
        if(properties.find(extensions[i])<0){
            fprintf(stderr, "Fail to find an instance extension %s\n", extensions[i]);
            return false;
        }
    }
    return true;
}

bool checkDeviceExtensions(vk::PhysicalDevice& physicalDevice, vk::s32 numExtensions, const vk::Char** extensions)
{
    ExtensionProperties properties;
    if(VK_SUCCESS != properties.enumerateDeviceExtensionProperties(physicalDevice, VLK_NULL)){
        fprintf(stderr, "Fail to enumerate device extensions\n");
        return false;
    }
    for(vk::s32 i=0; i<numExtensions; ++i){
        if(properties.find(extensions[i])<0){
            fprintf(stderr, "Fail to find an device extension %s\n", extensions[i]);
            return false;
        }
    }
    return true;
}

void printInstanceExtensions()
{
    ExtensionProperties properties;
    if(VK_SUCCESS != properties.enumerateInstanceExtensionProperties(VLK_NULL)){
        fprintf(stderr, "Fail to enumerate instance extensions\n");
        return;
    }
    for(vk::u32 i=0; i<properties.size(); ++i){
        printf("%s %d\n", properties.get(i).extensionName, properties.get(i).specVersion);
    }
}

void printDeviceExtentions(vk::PhysicalDevice& physicalDevice)
{
    ExtensionProperties properties;
    if(VK_SUCCESS != properties.enumerateDeviceExtensionProperties(physicalDevice, VLK_NULL)){
        fprintf(stderr, "Fail to enumerate physical device extensions\n");
        return;
    }
    for(vk::u32 i=0; i<properties.size(); ++i){
        printf("%s %d\n", properties.get(i).extensionName, properties.get(i).specVersion);
    }
}
