/**
@file CommandAllocator.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    CommandAllocator CommandAllocator::create(Device& device, CommandListType type)
    {
        handle_type commandAllocator;
        if(SUCCEEDED(device->CreateCommandAllocator(static_cast<D3D12_COMMAND_LIST_TYPE>(type), IID_PPV_ARGS(&commandAllocator)))){
            return lgfx::move(CommandAllocator(commandAllocator));
        }
        return lgfx::move(CommandAllocator());
    }
}
