/**
@file PhysicalDevice.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
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
        return LGFX_VK_TO_RESULT(vkEnumerateDeviceLayerProperties(device_, propertyCount, properties));
    }

    LGFX_RESULT PhysicalDevice::getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties)
    {
        return LGFX_VK_TO_RESULT(vkGetPhysicalDeviceImageFormatProperties(device_, format, type, tiling, usage, flags, &imageFormatProperties));
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
}
