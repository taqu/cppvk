/**
@file Fence.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    Fence Fence::create(Device& device, u64 initialValue, FenceFlag flags)
    {
        ID3D12Fence* fence = LGFX_NULL;
        return SUCCEEDED(device->CreateFence(initialValue, static_cast<D3D12_FENCE_FLAGS>(flags), IID_PPV_ARGS(&fence)))
            ? Fence(fence)
            : Fence();
    }
}
