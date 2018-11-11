/**
@file GraphicsCommandList.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    GraphicsCommandList GraphicsCommandList::create(Device& device, u32 nodeMask, CommandListType type, CommandAllocator& commandAllocator, PipelineState& pipelineState)
    {
        ID3D12GraphicsCommandList* commandList = LGFX_NULL;
        if(SUCCEEDED(device->CreateCommandList(nodeMask, static_cast<D3D12_COMMAND_LIST_TYPE>(type), commandAllocator, pipelineState, IID_PPV_ARGS(&commandList)))){
            return lgfx::move(GraphicsCommandList(commandList));
        }
        return lgfx::move(GraphicsCommandList());
    }
}
