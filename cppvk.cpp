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
#define VLK_EXPORTED_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_INSTANCE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_DEVICE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_PHYSICALDEVICE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_EXT_EXPORTED_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
#define VLK_EXT_PHYSICALDEVICE_FUNCTION(name) PFN_ ## name name ## _ = VLK_NULL;
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

#define VLK_GET_FUNCTION(name, message) name ## _ = (PFN_ ## name)VLK_DLSYM(handle_, #name);\
    if(VLK_NULL == name ## _){\
        PRINT1_ERR(message, #name);\
        return VK_ERROR_INITIALIZATION_FAILED;\
    }

#define VLK_GET_FUNCTION_WARN(name, message) name ## _ = (PFN_ ## name)VLK_DLSYM(handle_, #name);\
    if(VLK_NULL == name ## _){\
        PRINT1_WARN(message, #name);\
    }

#include "VkFunctions.inc"

#undef VLK_GET_FUNCTION
#undef VLK_GET_FUNCTION_WARN

        return VK_SUCCESS;
    }

    void Lib::terminate()
    {
#define VLK_EXPORTED_FUNCTION(name) name ## _ = VLK_NULL;
#define VLK_INSTANCE_FUNCTION(name) name ## _ = VLK_NULL;
#define VLK_DEVICE_FUNCTION(name) name ## _ = VLK_NULL;
#define VLK_PHYSICALDEVICE_FUNCTION(name) name ## _ = VLK_NULL;

#define VLK_EXT_EXPORTED_FUNCTION(name) name ## _ = VLK_NULL;
#include "VkFunctions.inc"

        if(VLK_NULL != handle_){
            VLK_DLCLOSE(handle_);
            handle_ = VLK_NULL;
        }
    }

    VkResult Lib::createInstance(Instance& instance, const VkInstanceCreateInfo* createInfo, const VkAllocationCallbacks* allocator)
    {
        if(VLK_NULL != instance.instance_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result = vkCreateInstance_(createInfo, allocator, &instance.instance_);
        if(VK_SUCCESS != result){
            return result;
        }

        result = instance.initialize();
        if(VK_SUCCESS != result){
            vkDestroyInstance_(instance.instance_, allocator);
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
        if(VLK_NULL != device.device_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkResult result = vkCreateDevice_(device_, createInfo, allocator, &device.device_);
        if(VK_SUCCESS != result){
            return result;
        }

        result = device.initialize();
        if(VK_SUCCESS != result){
            vkDestroyDevice_(device.device_, allocator);
            device.device_ = VLK_NULL;
            return result;
        }

        device.queueFamily_ = createInfo->pQueueCreateInfos->queueFamilyIndex;
        device.allocator_ = allocator;
        return result;
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    Instance::Instance()
        :instance_(VLK_NULL)
        ,allocator_(VLK_NULL)
#define VLK_EXT_INSTANCE_FUNCTION(name) ,name ## _(VLK_NULL)
#include "VkFunctions.inc"
    {
    }

    Instance::Instance(Instance&& rhs)
        :instance_(rhs.instance_)
        ,allocator_(rhs.allocator_)
#define VLK_EXT_INSTANCE_FUNCTION(name) ,name ## _(rhs.name ## _)
#include "VkFunctions.inc"
    {
        rhs.instance_ = VLK_NULL;
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
        if(VLK_NULL == instance_){
            return;
        }

#define VLK_EXT_INSTANCE_FUNCTION(name) name ## _ = VLK_NULL;
#include "VkFunctions.inc"

        vkDestroyInstance_(instance_, allocator_);
        instance_ = VLK_NULL;
        allocator_ = VLK_NULL;
    }

    Instance& Instance::operator=(Instance&& rhs)
    {
        if(this == &rhs){
            return *this;
        }
        instance_ = rhs.instance_;
        allocator_ = rhs.allocator_;
#define VLK_EXT_INSTANCE_FUNCTION(name) name ## _ = rhs.name ## _;
#include "VkFunctions.inc"

        rhs.instance_ = VLK_NULL;
        rhs.allocator_ = VLK_NULL;
#define VLK_EXT_INSTANCE_FUNCTION(name) rhs.name ## _ = VLK_NULL;
#include "VkFunctions.inc"
        return *this;
    }

    PhysicalDevices Instance::enumeratePhysicalDevices()
    {
        u32 deviceCount = PhysicalDevices::MaxDevices;
        VkPhysicalDevice devices[PhysicalDevices::MaxDevices];
        VkResult result = vkEnumeratePhysicalDevices_(instance_, &deviceCount, devices);
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

    VkResult Instance::initialize()
    {
        if(VLK_NULL == instance_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

#define VLK_EXT_INSTANCE_FUNCTION(name) if(VLK_NULL == name ## _) name ## _ = (PFN_ ## name)vkGetInstanceProcAddr_(instance_, #name);\
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
        ,queueFamily_(0)
        ,allocator_(VLK_NULL)
#define VLK_EXT_DEVICE_FUNCTION(name) ,name ## _(VLK_NULL)
#include "VkFunctions.inc"
    {
    }

    Device::Device(Device&& rhs)
        :device_(rhs.device_)
        ,queueFamily_(rhs.queueFamily_)
        ,allocator_(rhs.allocator_)
#define VLK_EXT_DEVICE_FUNCTION(name) ,name ## _(rhs.name ## _)
#include "VkFunctions.inc"
    {
        rhs.device_ = VLK_NULL;
        rhs.queueFamily_ = 0;
        rhs.allocator_ = VLK_NULL;
#define VLK_EXT_DEVICE_FUNCTION(name) rhs.name ## _ = VLK_NULL;
#include "VkFunctions.inc"
    }

    Device::~Device()
    {
        destroy();
    }

    void Device::destroy()
    {
        if(VLK_NULL == device_){
            return;
        }

#define VLK_EXT_DEVICE_FUNCTION(name) name ## _ = VLK_NULL;
#include "VkFunctions.inc"
        vkDestroyDevice_(device_, allocator_);

        device_ = VLK_NULL;
        queueFamily_ = 0;
        allocator_ = VLK_NULL;
    }

    Device& Device::operator=(Device&& rhs)
    {
        if(this == &rhs){
            return *this;
        }
        device_ = rhs.device_;
        queueFamily_ = rhs.queueFamily_;
        allocator_ = rhs.allocator_;
#define VLK_EXT_DEVICE_FUNCTION(name) name ## _ = rhs.name ## _;
#include "VkFunctions.inc"

        rhs.device_ = VLK_NULL;
        rhs.queueFamily_ = 0;
        rhs.allocator_ = VLK_NULL;
#define VLK_EXT_DEVICE_FUNCTION(name) rhs.name ## _ = VLK_NULL;
#include "VkFunctions.inc"
        return *this;
    }

    VkResult Device::initialize()
    {
        if(VLK_NULL == device_){
            return VK_ERROR_INITIALIZATION_FAILED;
        }

#define VLK_EXT_DEVICE_FUNCTION(name) if(VLK_NULL == name ## _) name ## _ = (PFN_ ## name)vkGetDeviceProcAddr_(device_, #name);\
    if(VLK_NULL == name ## _){\
        PRINT1_WARN("Warning: cannot get device function %s via vkGetDeviceProcAddr\n", #name);\
    }

#include "VkFunctions.inc"

        return VK_SUCCESS;
    }
}
