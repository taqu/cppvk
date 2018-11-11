/**
@file Lib.cpp
@author t-sakai
@date 2018/10/17 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    Lib::Lib()
        :handle_(LGFX_NULL)
    {}

    Lib::~Lib()
    {
        terminate();
    }

    LGFX_RESULT Lib::initialize()
    {
        if(LGFX_NULL != handle_){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }
        handle_ = LGFX_DLOPEN(LGFX_VULKANLIB);
        if(LGFX_NULL == handle_){
            return LGFX_ERROR_INITIALIZATION_FAILED;
        }

#define LGFX_VK_EXPORTED_FUNCTION(name) LGFX_VK_GET_FUNCTION(name, "Error: cannot get exported %s\n")

#define LGFX_VK_GET_FUNCTION(name, message) name = (PFN_ ## name)LGFX_DLSYM(handle_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_ERR(message, #name);\
        return LGFX_ERROR_INITIALIZATION_FAILED;\
    }

#define LGFX_VK_GET_FUNCTION_WARN(name, message) name = (PFN_ ## name)LGFX_DLSYM(handle_, #name);\
    if(LGFX_NULL == name){\
        PRINT1_WARN(message, #name);\
    }

#include "VkFunctions.inc"

        return LGFX_SUCCESS;
    }

    void Lib::terminate()
    {
        if(LGFX_NULL == handle_){
            return;
        }

#define LGFX_VK_EXPORTED_FUNCTION(name) name = LGFX_NULL;
#include "VkFunctions.inc"

        LGFX_DLCLOSE(handle_);
        handle_ = LGFX_NULL;
    }

    void Lib::swap(Lib& rhs)
    {
        lgfx::swap(handle_, rhs.handle_);
    }
}
