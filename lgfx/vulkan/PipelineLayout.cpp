/**
@file PipelineLayout.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- PipelineLayout
    //---
    //--------------------------------------------------------------
    PipelineLayout::PipelineLayout()
        :handle_(Handle::invalid())
    {
    }

    PipelineLayout::PipelineLayout(PipelineLayout& rhs)
        :handle_(rhs.handle_)
    {
        if(handle_.valid()){
            handle_.inc();
        }
    }

    PipelineLayout::PipelineLayout(PipelineLayout&& rhs)
        :handle_(rhs.handle_)
    {
        rhs.handle_ = Handle::invalid();
    }

    PipelineLayout::PipelineLayout(s32 device, VkPipelineLayout pipelineLayout)
        :handle_(Handle::allocate(device, pipelineLayout))
    {
        LGFX_ASSERT(LGFX_NULL != pipelineLayout);
    }

    PipelineLayout::~PipelineLayout()
    {
        destroy();
    }

    PipelineLayout& PipelineLayout::operator=(PipelineLayout& rhs)
    {
        destroy();
        handle_ = rhs.handle_;
        if(handle_.valid()){
            handle_.inc();
        }
        return *this;
    }

    PipelineLayout& PipelineLayout::operator=(PipelineLayout&& rhs)
    {
        if(this != &rhs){
            handle_ = rhs.handle_;
            rhs.handle_ = Handle::invalid();
        }
        return *this;
    }

    bool PipelineLayout::valid() const
    {
        return handle_.valid();
    }

    PipelineLayout::operator const VkPipelineLayout() const
    {
        return (const VkPipelineLayout)handle_;
    }

    PipelineLayout::operator VkPipelineLayout()
    {
        return (VkPipelineLayout)handle_;
    }

    void PipelineLayout::swap(PipelineLayout& rhs)
    {
        handle_.swap(rhs.handle_);
    }

    void PipelineLayout::destroy()
    {
        if(!handle_.valid()){
            return;
        }
        if(0!=handle_.dec()){
            return;
        }
        utils::destroy(handle_, vkDestroyPipelineLayout);
    }
}
