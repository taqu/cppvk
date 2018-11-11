/**
@file System.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- System
    //---
    //--------------------------------------------------------------
    System System::system_;

    System::System()
        :allocator_(LGFX_NULL)
    {
    }

    System::~System()
    {
        terminate();
    }

    bool System::initialize(BuilderVulkan& builder, const VkAllocationCallbacks* allocator)
    {
        ResourceTable::initialize();

        system_.allocator_ = allocator;
        for(s32 i=0; i<LGFX_MAX_PHYSICAL_DEVICES; ++i){
            system_.devices_[i].setID(i);
        }

        if(!builder.build(system_)){
            system_.allocator_ = LGFX_NULL;
            return false;
        }
        return true;
    }

    void System::terminate()
    {
        if(!system_.lib_.valid()){
            return;
        }
        for(s32 i=0; i<LGFX_MAX_PHYSICAL_DEVICES; ++i){
            system_.devices_[i].destroy();
        }
        Instance::destroy(system_.instance_);
        system_.lib_.terminate();
        system_.allocator_ = LGFX_NULL;

        ResourceTable::terminate();
    }

    u32 System::getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName)
    {
        vkEnumerateInstanceExtensionProperties(layerName, &maxExtensions, extensionProperties);
        return maxExtensions;
    }
}
