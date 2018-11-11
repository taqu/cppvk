/**
@file PipelineState.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
namespace
{
    D3D12_SHADER_BYTECODE getShaderByteCode(const Blob* shader)
    {
        D3D12_SHADER_BYTECODE bytecode = {LGFX_NULL, 0};
        if(LGFX_NULL != shader){
            bytecode.pShaderBytecode = (*shader)->get();
            bytecode.BytecodeLength = (*shader)->size();
        }
        return bytecode;
    }
}

    PipelineState PipelineState::create(
        Device& device,
        RootSignature& rootSignature,
        const Blob* vs,
        const Blob* ps,
        const Blob* ds,
        const Blob* hs,
        const Blob* gs,
        const stream_output_desc_type& streamOutputDesc,
        const blend_desc_type& blendDesc,
        u32 sampleMask,
        const rasterizer_desc_type& rasterizerDesc,
        const depth_stencil_desc_type& depthStencilDesc,
        const input_layout_desc_type& inputLayoutDesc,
        IndexBufferStripCutValue indexBufferStripCutValue,
        PrimitiveTopologyType primitiveTopology,
        u32 numRenderTargets,
        const Format rtvFormats[MaxRenderTargets],
        Format dsvFormat,
        sample_desc_type sampleDesc,
        u32 nodeMask,
        const cached_pipeline_state_type& cachedPipelineState,
        PipelineStateFlag pipelineStateFlags)
    {
        D3D12_SHADER_BYTECODE vsByteCode = getShaderByteCode(vs);
        D3D12_SHADER_BYTECODE psByteCode = getShaderByteCode(ps);
        D3D12_SHADER_BYTECODE dsByteCode = getShaderByteCode(ds);
        D3D12_SHADER_BYTECODE hsByteCode = getShaderByteCode(hs);
        D3D12_SHADER_BYTECODE gsByteCode = getShaderByteCode(gs);

        D3D12_STREAM_OUTPUT_DESC stream_output_desc = {
            streamOutputDesc.soDeclarations_,
            streamOutputDesc.numEntries_,
            streamOutputDesc.bufferStrides_,
            streamOutputDesc.numStrides_,
            streamOutputDesc.rasterizedStream_,
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc =
        {
            rootSignature,
            vsByteCode,
            psByteCode,
            dsByteCode,
            hsByteCode,
            gsByteCode,
            stream_output_desc,
            blendDesc,
            sampleMask,
            rasterizerDesc,
            depthStencilDesc,
            inputLayoutDesc,
            static_cast<D3D12_INDEX_BUFFER_STRIP_CUT_VALUE>(indexBufferStripCutValue),
            static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(primitiveTopology),
            numRenderTargets,
            {static_cast<DXGI_FORMAT>(rtvFormats[0]), static_cast<DXGI_FORMAT>(rtvFormats[1]), static_cast<DXGI_FORMAT>(rtvFormats[2]), static_cast<DXGI_FORMAT>(rtvFormats[3]),
             static_cast<DXGI_FORMAT>(rtvFormats[4]), static_cast<DXGI_FORMAT>(rtvFormats[5]), static_cast<DXGI_FORMAT>(rtvFormats[6]), static_cast<DXGI_FORMAT>(rtvFormats[7]),},
            static_cast<DXGI_FORMAT>(dsvFormat),
            sampleDesc,
            nodeMask,
            cachedPipelineState,
            static_cast<D3D12_PIPELINE_STATE_FLAGS>(pipelineStateFlags),
        };

        ID3D12PipelineState* pipelineState = LGFX_NULL;
        if(SUCCEEDED(device->CreateGraphicsPipelineState(&pipelineStateDesc, IID_PPV_ARGS(&pipelineState)))){
            return lgfx::move(PipelineState(pipelineState));
        }
        return lgfx::move(PipelineState());
    }
}
