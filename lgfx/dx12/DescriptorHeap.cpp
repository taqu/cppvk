/**
@file DescriptorHeap.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    DescriptorHeap DescriptorHeap::create(Device& device, DescriptorHeapType type, u32 count, DescriptorHeapFlag flags)
    {
        D3D12_DESCRIPTOR_HEAP_DESC desc =
        {
            static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(type),
            count,
            static_cast<D3D12_DESCRIPTOR_HEAP_FLAGS>(flags),
            0,
        };

        handle_type heap = LGFX_NULL;
        if(SUCCEEDED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap)))){
            return lgfx::move(DescriptorHeap(heap));
        }
        return lgfx::move(DescriptorHeap());
    }
}
