/**
@file Builder.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- SwapchainBuilderVulkan
    //---
    //--------------------------------------------------------------
    bool SwapchainBuilderVulkan::checkSurfaceFormats(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats, bool supportHDR)
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


    bool SwapchainBuilderVulkan::checkSurfaceCapabilities(
        VkImageUsageFlags& /*imageUsageFlags*/,
        VkSurfaceTransformFlagBitsKHR& /*preTransform*/,
        VkCompositeAlphaFlagBitsKHR& /*compsiteAlpha*/,
        const VkSurfaceCapabilitiesKHR& /*surfaceCapabilities*/)
    {
        return true;
    }

    VkPresentModeKHR SwapchainBuilderVulkan::getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request)
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

    bool SwapchainBuilderVulkan::defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace)
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

    bool SwapchainBuilderVulkan::defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace)
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

    bool SwapchainBuilderVulkan::defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
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

    bool SwapchainBuilderVulkan::defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats)
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
    //--- BuilderVulkan
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

        template<class T>
        void initializeArray(u32 size, T* array, T value)
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

    bool BuilderVulkan::build(System& system)
    {
        if(VK_SUCCESS != system.lib_.initialize()){
            return false;
        }

        if(!buildInstance(system)){
            system.lib_.terminate();
            return false;
        }

        if(!buildDevice(system)){
            Instance::destroy(system.instance_);
            system.lib_.terminate();
            return false;
        }
        return true;
    }

    bool BuilderVulkan::buildInstance(System& system)
    {
        u32 enabledExtensionCount = 0;
        VkExtensionProperties extensionProperties[LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES];
        const Char* enabledExtensionNames[LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES];

        u32 numExtensionProperties = getInstanceExtensionProperties(LGFX_MAX_INSTANCE_EXTENSION_PROPERTIES, extensionProperties, instanceCreateInfo_.layerName_);

        for(u32 i = 0; i<numExtensionProperties; ++i){
            if(!checkInstanceExtension_(extensionProperties[i])){
                continue;
            }
            enabledExtensionNames[enabledExtensionCount++] = extensionProperties[i].extensionName;
        }

        VkApplicationInfo vkApplicationInfo ={
            VK_STRUCTURE_TYPE_APPLICATION_INFO, //structure type
            LGFX_NULL, //must be null
            instanceCreateInfo_.applicationName_, //application name
            instanceCreateInfo_.applicationVersion_, //application version
            instanceCreateInfo_.engineName_, //engine name
            instanceCreateInfo_.engineVersion_, //engine version
            instanceCreateInfo_.apiVersion_, //api version
        };

        VkInstanceCreateInfo vkInstanceCreateInfo ={
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //structure type
            LGFX_NULL, //must be null
            0, //instance creation flags. must set to 0
            &vkApplicationInfo, //application info
            instanceCreateInfo_.enabledLayerCount_, //enabled layer count
            instanceCreateInfo_.enabledLayerNames_, //enabled layer names
            enabledExtensionCount, //enabled extension count
            enabledExtensionNames, //enabled extension names
        };
        return VK_SUCCESS == Instance::create(system.instance_, vkInstanceCreateInfo, surfaceCreateInfo_);
    }

    bool BuilderVulkan::buildDevice(System& system)
    {
        SwapchainBuilderVulkan swapchainBuilder = createSwapchainBuilder(system.instance_);

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

        PhysicalDevice physicalDevices[LGFX_MAX_PHYSICAL_DEVICES];
        u32 numPhysicalDevices = system.instance_.enumeratePhysicalDevices(LGFX_MAX_PHYSICAL_DEVICES, physicalDevices);

        u32 countDevice = 0;
        for(; countDevice<numPhysicalDevices; ++countDevice){
            PhysicalDevice physicalDevice = physicalDevices[countDevice];

            //--- Device
            //----------------------------------------------------------
            //Select queues for graphics and presentation
            //Get queue properties
            u32 queueFamilyIndices[QueueType_Max];
            initializeArray(QueueType_Max, queueFamilyIndices, static_cast<u32>(QueueType_Invalid));

            numQueueFamilyProperties = LGFX_MAX_QUEUE_FAMILY_PROPERTIES;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &numQueueFamilyProperties, queueFamilyProperties);

            for(u32 j = 0; j<numQueueFamilyProperties; ++j){
                queueFamilyPresentationSupports[j] = system.instance_.getPhysicalDevicePresentationSurfaceSupport(physicalDevice, j);
            }
            checkQueueFamilies_(queueFamilyIndices, numQueueFamilyProperties, queueFamilyProperties, queueFamilyPresentationSupports, deviceCreateInfo_.requestQueueTypes_);

            if(QueueType_Invalid == queueFamilyIndices[QueueType_Present] || QueueType_Invalid == queueFamilyIndices[QueueType_Graphics]){
                continue;
            }

            //Check device extensions
            VkExtensionProperties deviceExtensionProperties[LGFX_MAX_DEVICE_EXTENSION_PROPERTIES];
            u32 numExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties(LGFX_MAX_DEVICE_EXTENSION_PROPERTIES, deviceExtensionProperties, deviceCreateInfo_.layerName_);
            enabledExtensionCount = 0;
            for(u32 i = 0; i<numExtensionProperties; ++i){
                if(!checkDeviceExtension_(deviceExtensionProperties[i])){
                    continue;
                }
                enabledExtensionNames[enabledExtensionCount++] = deviceExtensionProperties[i].extensionName;
            }

            //Check device features
            VkPhysicalDeviceFeatures supported;
            physicalDevice.getPhysicalDeviceFeatures(supported);
            memset(&features, 0, sizeof(VkPhysicalDeviceFeatures));
            if(!checkDeviceFeatures_(features, supported)){
                continue;
            }
            enabledFeatures = &features;

            VkDeviceQueueCreateInfo queueCreateInfo[QueueType_Max];
            f32 queuePriorities[QueueType_Max][QueueType_Max];
            u32 numQueueCreateInfo = createQueueCreateInfo(queueCreateInfo, queueFamilyIndices, queuePriorities);

            VkDeviceCreateInfo vkDeviceCreateInfo ={
                VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //structure type
                LGFX_NULL,
                0, //device create flags, must set to 0
                numQueueCreateInfo, //queue create info count,
                queueCreateInfo, //queue create info
                deviceCreateInfo_.enabledLayerCount_, //enabled layer count
                deviceCreateInfo_.enabledLayerNames_, //enabled layer names
                enabledExtensionCount, //enabled extension count
                enabledExtensionNames, //enabled extension names
                enabledFeatures, //enabled physical device features
            };

            if(VK_SUCCESS == Device::create(system.devices_[deviceCreateInfo_.index_], physicalDevice, vkDeviceCreateInfo, queueFamilyIndices, swapchainBuilder)){
                break;
            }
        }//for(; countDevice<physicalDevices.size();

        return countDevice<numPhysicalDevices;
    }

    bool BuilderVulkan::checkInstanceExtension(const VkExtensionProperties& /*properties*/)
    {
        return true;
    }

    void BuilderVulkan::checkQueueFamilies(
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

    bool BuilderVulkan::checkDeviceExtension(const VkExtensionProperties& /*properties*/)
    {
        return true;
    }

    bool BuilderVulkan::checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported)
    {
        dst = supported;
        return true;
    }

    u32 BuilderVulkan::getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName)
    {
        vkEnumerateInstanceExtensionProperties(layerName, &maxExtensions, extensionProperties);
        return maxExtensions;
    }

    SwapchainBuilderVulkan BuilderVulkan::createSwapchainBuilder(Instance& instance)
    {
        SwapchainBuilderVulkan swapchainBuilder;

        swapchainBuilder.instance_ = &instance;
        swapchainBuilder.swapchainCreateInfo_ = swapchainCreateInfo_;

        swapchainBuilder.checkSurfaceFormats_ = checkSurfaceFormats_;
        swapchainBuilder.checkSurfaceCapabilities_ = checkSurfaceCapabilities_;
        swapchainBuilder.getPresentMode_ = getPresentMode_;

        return swapchainBuilder;
    }
}
