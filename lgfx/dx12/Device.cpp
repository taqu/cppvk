/**
@file Device.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    Device Device::create(Adapter& adapter, FeatureLevel featureLevel)
    {
        handle_type device = LGFX_NULL;
        return SUCCEEDED(D3D12CreateDevice(adapter, static_cast<D3D_FEATURE_LEVEL>(featureLevel), IID_PPV_ARGS(&device)))
            ? lgfx::move(Device(device))
            : lgfx::move(Device());
    }

    bool Device::createCommittedResource(
        const HeapPropertiesDesc::desc_type* heapProperties,
        lgfx::HeapFlag heapFlags,
        const ResourceDesc::desc_type* resourceDesc,
        ResourceState initialResourceState,
        const ClearValue* optimizedClearValue,
        VertexBuffer& vertexBuffer)
    {
        ID3D12Resource* resource = LGFX_NULL;
        if(SUCCEEDED(handle_->CreateCommittedResource(
            heapProperties,
            static_cast<D3D12_HEAP_FLAGS>(heapFlags),
            resourceDesc,
            static_cast<D3D12_RESOURCE_STATES>(initialResourceState),
            reinterpret_cast<const D3D12_CLEAR_VALUE*>(optimizedClearValue),
            IID_PPV_ARGS(&resource)))){
            vertexBuffer = VertexBuffer(resource);
            return true;
        }
        return false;
    }
}
