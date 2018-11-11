/**
@file Shader.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- Shader
    //---
    //--------------------------------------------------------------
    Shader::Shader()
        :handle_(Handle::invalid())
    {
    }

    Shader::Shader(Shader& rhs)
        :handle_(rhs.handle_)
    {
        if(handle_.valid()){
            handle_.inc();
        }
    }

    Shader::Shader(Shader&& rhs)
        :handle_(rhs.handle_)
    {
        rhs.handle_ = Handle::invalid();
    }

    Shader::Shader(s32 device, VkShaderModule shader)
        :handle_(Handle::allocate(device, shader))
    {
        LGFX_ASSERT(LGFX_NULL != shader);
    }

    Shader::~Shader()
    {
        destroy();
    }

    Shader& Shader::operator=(Shader& rhs)
    {
        destroy();
        handle_ = rhs.handle_;
        if(handle_.valid()){
            handle_.inc();
        }
        return *this;
    }

    Shader& Shader::operator=(Shader&& rhs)
    {
        if(this != &rhs){
            handle_ = rhs.handle_;
            rhs.handle_ = Handle::invalid();
        }
        return *this;
    }

    bool Shader::valid() const
    {
        return handle_.valid();
    }

    Shader::operator const VkShaderModule() const
    {
        return (const VkShaderModule)handle_;
    }

    Shader::operator VkShaderModule()
    {
        return (VkShaderModule)handle_;
    }

    void Shader::swap(Shader& rhs)
    {
        handle_.swap(rhs.handle_);
    }

    void Shader::destroy()
    {
        if(!handle_.valid()){
            return;
        }
        if(0!=handle_.dec()){
            return;
        }
        utils::destroy(handle_, vkDestroyShaderModule);
    }
}
