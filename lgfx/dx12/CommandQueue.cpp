/**
@file CommandQueue.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    CommandQueue CommandQueue::create(Device& device, CommandListType type)
    {
        handle_type commandQueue = LGFX_NULL;
        D3D12_COMMAND_QUEUE_DESC desc =
        {
            (D3D12_COMMAND_LIST_TYPE)type,
            D3D12_COMMAND_QUEUE_FLAG_NONE,
        };
        return SUCCEEDED(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)))
            ? lgfx::move(CommandQueue(commandQueue))
            : lgfx::move(CommandQueue());
    }
}
