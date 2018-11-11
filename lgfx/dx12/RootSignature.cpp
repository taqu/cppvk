/**
@file RootSignature.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    RootSignature RootSignature::create(Device& device, const RootSignatureDesc& desc)
    {
        D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc =
        {
            desc.numParameters_,
            reinterpret_cast<const D3D12_ROOT_PARAMETER*>(desc.parameters_),
            desc.numStaticSamplers_,
            reinterpret_cast<const D3D12_STATIC_SAMPLER_DESC*>(desc.staticSamplers_),
            static_cast<D3D12_ROOT_SIGNATURE_FLAGS>(desc.flags_),
        };

        ID3DBlob* signature = LGFX_NULL;
        ID3DBlob* error = LGFX_NULL;
        if(FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &signature, &error))){
            LGFX_SAFE_RELEASE(error);
            LGFX_SAFE_RELEASE(signature);
            return lgfx::move(RootSignature());
        }

        ID3D12RootSignature* rootSignature = LGFX_NULL;
        if(SUCCEEDED(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)))){
            return lgfx::move(RootSignature(rootSignature));
        }
        return lgfx::move(RootSignature());
    }
}
