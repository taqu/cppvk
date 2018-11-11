#ifndef INC_LGFX_DX12_H_
#define INC_LGFX_DX12_H_
/**
@file lgfx_dx12.h
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
#define LGFX_SAFE_RELEASE(ptr) if(LGFX_NULL != (ptr)) (ptr)->Release(); (ptr) = LGFX_NULL

    typedef u64 GPUVirtualAddress;
    static const u32 ResourceBarrierAllSubresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    //--------------------------------------------------------------
    //---
    //--- Enumerations
    //---
    //--------------------------------------------------------------
    enum CPUAccess : s32
    {
        CPUAccess_None = DXGI_CPU_ACCESS_NONE,
        CPUAccess_Dynamic = DXGI_CPU_ACCESS_DYNAMIC,
        CPUAccess_ReadWrite = DXGI_CPU_ACCESS_READ_WRITE,
        CPUAccess_Scratch = DXGI_CPU_ACCESS_SCRATCH,
        CPUAccess_Field = DXGI_CPU_ACCESS_FIELD,
    };

    enum Usage : u32
    {
        Usage_SharedInput = DXGI_USAGE_SHADER_INPUT,
        Usage_RenderTargetOutput = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        Usage_BackBuffer = DXGI_USAGE_BACK_BUFFER,
        Usage_Shared = DXGI_USAGE_SHARED,
        Usage_ReadOnly = DXGI_USAGE_READ_ONLY,
        Usage_DiscardOnPresent = DXGI_USAGE_DISCARD_ON_PRESENT,
        Usage_UnorderedAccess = DXGI_USAGE_UNORDERED_ACCESS,
    };

    enum Scaling : s32
    {
        Scaling_Stretch = DXGI_SCALING_STRETCH,
        Scaling_None = DXGI_SCALING_NONE,
        Scaling_AspectRatioStretch = DXGI_SCALING_ASPECT_RATIO_STRETCH,
    };

    enum AlphaMode : s32
    {
        AlphaMode_Unspecified = DXGI_ALPHA_MODE_UNSPECIFIED,
        AlphaMode_Premultiplied = DXGI_ALPHA_MODE_PREMULTIPLIED,
        AlphaMode_Straight = DXGI_ALPHA_MODE_STRAIGHT,
        AlphaMode_Ignore = DXGI_ALPHA_MODE_IGNORE,
    };

    enum SwapChainFlag : u32
    {
        SwapChainFlag_NonPrerotaed = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED,
        SwapChainFlag_AllowModeSwitch = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH,
        SwapChainFlag_GDICompatible = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE,
        SwapChainFlag_RestrictedContent = DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT,
        SwapChainFlag_RestrictSharedResourceDriver = DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER,
        SwapChainFlag_DisplayOnly = DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY,
        SwapChainFlag_FrameLatencyWaitableObject = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT,
        SwapChainFlag_ForegroundLayer = DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER,
        SwapChainFlag_FullscreenVideo = DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO,
        SwapChainFlag_YUVVideo = DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO,
        SwapChainFlag_HWProtected = DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED,
        SwapChainFlag_AllowTearing = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING,
        SwapChainFlag_RestrictedToAllHolographicDisplays = DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS,
    };

    enum SwapEffect : s32
    {
        SwapEffect_Discard  = DXGI_SWAP_EFFECT_DISCARD,
        SwapEffect_Sequential  = DXGI_SWAP_EFFECT_SEQUENTIAL,
        SwapEffect_FlipSequential  = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
        SwapEffect_FlipDiscard = DXGI_SWAP_EFFECT_FLIP_DISCARD,
    };

    enum MWA : u32
    {
        MWA_NO_WINDOW_CHANGES = DXGI_MWA_NO_WINDOW_CHANGES,
        MWA_NO_ALT_ENTER = DXGI_MWA_NO_ALT_ENTER,
        MWA_NO_PRINT_SCREEN = DXGI_MWA_NO_PRINT_SCREEN,
    };

    enum FeatureLevel : s32
    {
        FeatureLevel_9_1  = D3D_FEATURE_LEVEL_9_1,
        FeatureLevel_9_2  = D3D_FEATURE_LEVEL_9_2,
        FeatureLevel_9_3  = D3D_FEATURE_LEVEL_9_3,
        FeatureLevel_10_0 = D3D_FEATURE_LEVEL_10_0,
        FeatureLevel_10_1 = D3D_FEATURE_LEVEL_10_1,
        FeatureLevel_11_0 = D3D_FEATURE_LEVEL_11_0,
        FeatureLevel_11_1 = D3D_FEATURE_LEVEL_11_1,
        FeatureLevel_12_0 = D3D_FEATURE_LEVEL_12_0,
        FeatureLevel_12_1 = D3D_FEATURE_LEVEL_12_1,
    };

    enum CommandListType : s32
    {
        CommandListType_Direct  = D3D12_COMMAND_LIST_TYPE_DIRECT,
        CommandListType_Bundle  = D3D12_COMMAND_LIST_TYPE_BUNDLE,
        CommandListType_Compute  = D3D12_COMMAND_LIST_TYPE_COMPUTE,
        CommandListType_Copy = D3D12_COMMAND_LIST_TYPE_COPY,
        CommandListType_Decode = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,
        CommandListType_Process = D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS,
    };

    enum CommandQueuePriority : s32
    {
        CommandQueuePriority_Normal  = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
        CommandQueuePriority_High  = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
        CommandQueuePriority_GlobalRealtime  = D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME,
    };

    enum DescriptorHeapType : s32
    {
        DescriptorHeapType_CBV_SRV_UAV = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
        DescriptorHeapType_Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
        DescriptorHeapType_RTV = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
        DescriptorHeapType_DSV = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
    };

    enum DescriptorHeapFlag : s32
    {
        DescriptorHeapFlag_None = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
        DescriptorHeapFlag_ShaderVisible = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
    };

    enum RootParameterType : s32
    {
        RootParameterType_Descriptor = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
        RootParameterType_32BitConstants = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,
        RootParameterType_CBV = D3D12_ROOT_PARAMETER_TYPE_CBV,
        RootParameterType_SRV = D3D12_ROOT_PARAMETER_TYPE_SRV,
        RootParameterType_UAV = D3D12_ROOT_PARAMETER_TYPE_UAV,
    };

    enum DescriptorRangeType : s32 
    {
        DescriptorRangeType_SRV = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
        DescriptorRangeType_UAV = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
        DescriptorRangeType_CBV = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
        DescriptorRangeType_Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER,
    };

    enum ShaderVisibility
    {
        ShaderVisibility_All = D3D12_SHADER_VISIBILITY_ALL,
        ShaderVisibility_Vertex = D3D12_SHADER_VISIBILITY_VERTEX,
        ShaderVisibility_Hull = D3D12_SHADER_VISIBILITY_HULL,
        ShaderVisibility_Domain = D3D12_SHADER_VISIBILITY_DOMAIN,
        ShaderVisibility_Geometry = D3D12_SHADER_VISIBILITY_GEOMETRY,
        ShaderVisibility_Pixel = D3D12_SHADER_VISIBILITY_PIXEL
    };

    enum RootSignatureFlags
    {
        RootSignatureFlags_None = D3D12_ROOT_SIGNATURE_FLAG_NONE,
        RootSignatureFlags_AllowInputAssemblerInputLayout = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
        RootSignatureFlags_DenyVertexShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS,
        RootSignatureFlags_DenyHullShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS,
        RootSignatureFlags_DenyDomainShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS,
        RootSignatureFlags_DenyGeometryShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
        RootSignatureFlags_DenyPixelShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS,
        RootSignatureFlags_AllowStreamOutput = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT,
    };

    enum FillMode
    {
        FillMode_WireFrame = D3D12_FILL_MODE_WIREFRAME,
        FillMode_Solid = D3D12_FILL_MODE_SOLID,
    };

    enum CullMode
    {
        CullMode_None = D3D12_CULL_MODE_NONE,
        CullMode_Front = D3D12_CULL_MODE_FRONT,
        CullMode_Back = D3D12_CULL_MODE_BACK,
    };

    enum Format : s32
    {
        Format_UNKNOWN = DXGI_FORMAT_UNKNOWN,
        Format_R32G32B32A32_TYPELESS = DXGI_FORMAT_R32G32B32A32_TYPELESS,
        Format_R32G32B32A32_FLOAT = DXGI_FORMAT_R32G32B32A32_FLOAT,
        Format_R32G32B32A32_UINT = DXGI_FORMAT_R32G32B32A32_UINT,
        Format_R32G32B32A32_SINT = DXGI_FORMAT_R32G32B32A32_SINT,
        Format_R32G32B32_TYPELESS = DXGI_FORMAT_R32G32B32_TYPELESS,
        Format_R32G32B32_FLOAT = DXGI_FORMAT_R32G32B32_FLOAT,
        Format_R32G32B32_UINT = DXGI_FORMAT_R32G32B32_UINT,
        Format_R32G32B32_SINT = DXGI_FORMAT_R32G32B32_SINT,
        Format_R16G16B16A16_TYPELESS = DXGI_FORMAT_R16G16B16A16_TYPELESS,
        Format_R16G16B16A16_FLOAT = DXGI_FORMAT_R16G16B16A16_FLOAT,
        Format_R16G16B16A16_UNORM = DXGI_FORMAT_R16G16B16A16_UNORM,
        Format_R16G16B16A16_UINT = DXGI_FORMAT_R16G16B16A16_UINT,
        Format_R16G16B16A16_SNORM = DXGI_FORMAT_R16G16B16A16_SNORM,
        Format_R16G16B16A16_SINT = DXGI_FORMAT_R16G16B16A16_SINT,
        Format_R32G32_TYPELESS = DXGI_FORMAT_R32G32_TYPELESS,
        Format_R32G32_FLOAT = DXGI_FORMAT_R32G32_FLOAT,
        Format_R32G32_UINT = DXGI_FORMAT_R32G32_UINT,
        Format_R32G32_SINT = DXGI_FORMAT_R32G32_SINT,
        Format_R32G8X24_TYPELESS = DXGI_FORMAT_R32G8X24_TYPELESS,
        Format_D32_FLOAT_S8X24_UINT = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
        Format_R32_FLOAT_X8X24_TYPELESS = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
        Format_X32_TYPELESS_G8X24_UINT = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
        Format_R10G10B10A2_TYPELESS = DXGI_FORMAT_R10G10B10A2_TYPELESS,
        Format_R10G10B10A2_UNORM = DXGI_FORMAT_R10G10B10A2_UNORM ,
        Format_R10G10B10A2_UINT = DXGI_FORMAT_R10G10B10A2_UINT,
        Format_R11G11B10_FLOAT = DXGI_FORMAT_R11G11B10_FLOAT,
        Format_R8G8B8A8_TYPELESS = DXGI_FORMAT_R8G8B8A8_TYPELESS,
        Format_R8G8B8A8_UNORM = DXGI_FORMAT_R8G8B8A8_UNORM,
        Format_R8G8B8A8_UNORM_SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
        Format_R8G8B8A8_UINT = DXGI_FORMAT_R8G8B8A8_UINT,
        Format_R8G8B8A8_SNORM = DXGI_FORMAT_R8G8B8A8_SNORM,
        Format_R8G8B8A8_SINT = DXGI_FORMAT_R8G8B8A8_SINT,
        Format_R16G16_TYPELESS = DXGI_FORMAT_R16G16_TYPELESS,
        Format_R16G16_FLOAT = DXGI_FORMAT_R16G16_FLOAT,
        Format_R16G16_UNORM = DXGI_FORMAT_R16G16_UNORM,
        Format_R16G16_UINT = DXGI_FORMAT_R16G16_UINT ,
        Format_R16G16_SNORM = DXGI_FORMAT_R16G16_SNORM ,
        Format_R16G16_SINT = DXGI_FORMAT_R16G16_SINT,
        Format_R32_TYPELESS = DXGI_FORMAT_R32_TYPELESS,
        Format_D32_FLOAT = DXGI_FORMAT_D32_FLOAT,
        Format_R32_FLOAT = DXGI_FORMAT_R32_FLOAT,
        Format_R32_UINT = DXGI_FORMAT_R32_UINT,
        Format_R32_SINT = DXGI_FORMAT_R32_SINT,
        Format_R24G8_TYPELESS = DXGI_FORMAT_R24G8_TYPELESS,
        Format_D24_UNORM_S8_UINT = DXGI_FORMAT_D24_UNORM_S8_UINT,
        Format_R24_UNORM_X8_TYPELESS = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
        Format_X24_TYPELESS_G8_UINT = DXGI_FORMAT_X24_TYPELESS_G8_UINT,
        Format_R8G8_TYPELESS = DXGI_FORMAT_R8G8_TYPELESS,
        Format_R8G8_UNORM = DXGI_FORMAT_R8G8_UNORM,
        Format_R8G8_UINT = DXGI_FORMAT_R8G8_UINT,
        Format_R8G8_SNORM = DXGI_FORMAT_R8G8_SNORM,
        Format_R8G8_SINT = DXGI_FORMAT_R8G8_SINT,
        Format_R16_TYPELESS = DXGI_FORMAT_R16_TYPELESS,
        Format_R16_FLOAT = DXGI_FORMAT_R16_FLOAT,
        Format_D16_UNORM = DXGI_FORMAT_D16_UNORM,
        Format_R16_UNORM = DXGI_FORMAT_R16_UNORM,
        Format_R16_UINT = DXGI_FORMAT_R16_UINT,
        Format_R16_SNORM = DXGI_FORMAT_R16_SNORM,
        Format_R16_SINT = DXGI_FORMAT_R16_SINT,
        Format_R8_TYPELESS = DXGI_FORMAT_R8_TYPELESS,
        Format_R8_UNORM = DXGI_FORMAT_R8_UNORM,
        Format_R8_UINT = DXGI_FORMAT_R8_UINT,
        Format_R8_SNORM = DXGI_FORMAT_R8_SNORM,
        Format_R8_SINT = DXGI_FORMAT_R8_SINT,
        Format_A8_UNORM = DXGI_FORMAT_A8_UNORM,
        Format_R1_UNORM = DXGI_FORMAT_R1_UNORM,
        Format_R9G9B9E5_SHAREDEXP = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
        Format_R8G8_B8G8_UNORM = DXGI_FORMAT_R8G8_B8G8_UNORM,
        Format_G8R8_G8B8_UNORM = DXGI_FORMAT_G8R8_G8B8_UNORM,
        Format_BC1_TYPELESS = DXGI_FORMAT_BC1_TYPELESS,
        Format_BC1_UNORM = DXGI_FORMAT_BC1_UNORM,
        Format_BC1_UNORM_SRGB = DXGI_FORMAT_BC1_UNORM_SRGB,
        Format_BC2_TYPELESS = DXGI_FORMAT_BC2_TYPELESS,
        Format_BC2_UNORM = DXGI_FORMAT_BC2_UNORM,
        Format_BC2_UNORM_SRGB = DXGI_FORMAT_BC2_UNORM_SRGB,
        Format_BC3_TYPELESS = DXGI_FORMAT_BC3_TYPELESS,
        Format_BC3_UNORM = DXGI_FORMAT_BC3_UNORM,
        Format_BC3_UNORM_SRGB = DXGI_FORMAT_BC3_UNORM_SRGB,
        Format_BC4_TYPELESS = DXGI_FORMAT_BC4_TYPELESS,
        Format_BC4_UNORM = DXGI_FORMAT_BC4_UNORM,
        Format_BC4_SNORM = DXGI_FORMAT_BC4_SNORM,
        Format_BC5_TYPELESS = DXGI_FORMAT_BC5_TYPELESS,
        Format_BC5_UNORM = DXGI_FORMAT_BC5_UNORM,
        Format_BC5_SNORM = DXGI_FORMAT_BC5_SNORM,
        Format_B5G6R5_UNORM = DXGI_FORMAT_B5G6R5_UNORM,
        Format_B5G5R5A1_UNORM = DXGI_FORMAT_B5G5R5A1_UNORM,
        Format_B8G8R8A8_UNORM = DXGI_FORMAT_B8G8R8A8_UNORM,
        Format_B8G8R8X8_UNORM = DXGI_FORMAT_B8G8R8X8_UNORM,
        Format_R10G10B10_XR_BIAS_A2_UNORM = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
        Format_B8G8R8A8_TYPELESS = DXGI_FORMAT_B8G8R8A8_TYPELESS,
        Format_B8G8R8A8_UNORM_SRGB = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
        Format_B8G8R8X8_TYPELESS = DXGI_FORMAT_B8G8R8X8_TYPELESS,
        Format_B8G8R8X8_UNORM_SRGB = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
        Format_BC6H_TYPELESS = DXGI_FORMAT_BC6H_TYPELESS,
        Format_BC6H_UF16 = DXGI_FORMAT_BC6H_UF16,
        Format_BC6H_SF16 = DXGI_FORMAT_BC6H_SF16,
        Format_BC7_TYPELESS = DXGI_FORMAT_BC7_TYPELESS,
        Format_BC7_UNORM = DXGI_FORMAT_BC7_UNORM,
        Format_BC7_UNORM_SRGB = DXGI_FORMAT_BC7_UNORM_SRGB,
        Format_AYUV = DXGI_FORMAT_AYUV,
        Format_Y410 = DXGI_FORMAT_Y410,
        Format_Y416 = DXGI_FORMAT_Y416,
        Format_NV12 = DXGI_FORMAT_NV12,
        Format_P010 = DXGI_FORMAT_P010,
        Format_P016 = DXGI_FORMAT_P016,
        Format_420_OPAQUE = DXGI_FORMAT_420_OPAQUE,
        Format_YUV2 = DXGI_FORMAT_YUY2,
        Format_Y210 = DXGI_FORMAT_Y210,
        Format_Y216 = DXGI_FORMAT_Y216,
        Format_NV11 = DXGI_FORMAT_NV11,
        Format_AI44 = DXGI_FORMAT_AI44,
        Format_IA44 = DXGI_FORMAT_IA44,
        Format_P8 = DXGI_FORMAT_P8,
        Format_A8P8 = DXGI_FORMAT_A8P8,
        Format_B4G4R4A4_UNORM = DXGI_FORMAT_B4G4R4A4_UNORM,

        Format_P208 = DXGI_FORMAT_P208,
        Format_V208 = DXGI_FORMAT_V208,
        Format_V408 = DXGI_FORMAT_V408,
    };

    enum Filter : s32
    {
        Filter_MinMagMipPoint = D3D12_FILTER_MIN_MAG_MIP_POINT,
        Filter_MinMagPointMipLinear = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR,
        Filter_MinPointMagLinearMipPoint = D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
        Filter_MinPointMagMipLinear = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,
        Filter_MinLinearMagMipPoint = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT,
        Filter_MinLinearMagPointMipLinear = D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        Filter_MinMagLinearMipPoint = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
        Filter_MinMagMipLinear = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        Filter_Anisotropic = D3D12_FILTER_ANISOTROPIC,
        Filter_Comparison_MinMagMipPoint = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
        Filter_Comparison_MinMagPointMipLinear = D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
        Filter_Comparison_MinPointMagLinearMipPoint = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
        Filter_Comparison_MinPointMagMipLinear = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
        Filter_Comparison_MinLinearMagMipPoint = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
        Filter_Comparison_MinLinearMagPointMipLinear = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        Filter_Comparison_MinMagLinearMipPoint = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
        Filter_Comparison_MinMagMipLinear = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
        Filter_Comparison_Anisotropic = D3D12_FILTER_COMPARISON_ANISOTROPIC,
        Filter_Minumum_MinMagMipPoint = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT,
        Filter_Minumum_MinMagPointMipLinear = D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
        Filter_Minumum_MinPointMagLinearMipPoint = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
        Filter_Minumum_MinPointMagMipLinear = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
        Filter_Minumum_MinLinearMagMipPoint = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
        Filter_Minumum_MinLinearMagPointMipLinear = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        Filter_Minumum_MinMagLinearMipPoint = D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
        Filter_Minumum_MinMagMipLinear = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,
        Filter_Minumum_Anisotropic = D3D12_FILTER_MINIMUM_ANISOTROPIC,
        Filter_Maximum_MinMagMipPoint = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT,
        Filter_Maximum_MinMagPointMipLinear = D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
        Filter_Maximum_MinPointMagLinearMipPoint = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
        Filter_Maximum_MinPointMagMipLinear = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
        Filter_Maximum_MinLinearMagMipPoint = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
        Filter_Maximum_MinLinearMagPointMipLinear = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        Filter_Maximum_MinMagLinearMipPoint = D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
        Filter_Maximum_MinMagMipLinear = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,
        Filter_Maximum_Anisotropic = D3D12_FILTER_MAXIMUM_ANISOTROPIC,
    };

    enum TextureAddressMode : s32
    {
        TextureAddressMode_Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        TextureAddressMode_Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
        TextureAddressMode_Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        TextureAddressMode_Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
        TextureAddressMode_MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE,
    };

    enum ComparisonFunc : s32
    {
        ComparisonFunc_Never = D3D12_COMPARISON_FUNC_NEVER,
        ComparisonFunc_Less = D3D12_COMPARISON_FUNC_LESS,
        ComparisonFunc_Equal = D3D12_COMPARISON_FUNC_EQUAL,
        ComparisonFunc_LessEqual = D3D12_COMPARISON_FUNC_LESS_EQUAL,
        ComparisonFunc_Greater = D3D12_COMPARISON_FUNC_GREATER,
        ComparisonFunc_NotEqual = D3D12_COMPARISON_FUNC_NOT_EQUAL,
        ComparisonFunc_GreaterEqual = D3D12_COMPARISON_FUNC_GREATER_EQUAL,
        ComparisonFunc_Always = D3D12_COMPARISON_FUNC_ALWAYS,
    };

    enum Blend
    {
        Blend_Zero = D3D12_BLEND_ZERO,
        Blend_One = D3D12_BLEND_ONE,
        Blend_SrcColor = D3D12_BLEND_SRC_COLOR,
        Blend_InvSrcColor = D3D12_BLEND_INV_SRC_COLOR,
        Blend_SrcAlpha = D3D12_BLEND_SRC_ALPHA,
        Blend_InvSrcAlpha = D3D12_BLEND_INV_SRC_ALPHA,
        Blend_DstAlpha = D3D12_BLEND_DEST_ALPHA,
        Blend_InvDstAlpha = D3D12_BLEND_INV_DEST_ALPHA,
        Blend_DstColor = D3D12_BLEND_DEST_COLOR,
        Blend_InvDstColor = D3D12_BLEND_INV_DEST_COLOR,
        Blend_SrcAlphaSat = D3D12_BLEND_SRC_ALPHA_SAT,
        Blend_BlendFactor = D3D12_BLEND_BLEND_FACTOR,
        Blend_InvBlendFactor = D3D12_BLEND_INV_BLEND_FACTOR,
        Blend_Src1Color = D3D12_BLEND_SRC1_COLOR,
        Blend_InvSrc1Color = D3D12_BLEND_INV_SRC1_COLOR,
        Blend_Src1Alpha = D3D12_BLEND_SRC1_ALPHA,
        Blend_InvSrc1Alpha = D3D12_BLEND_INV_SRC1_ALPHA,
    };

    enum BlendOp
    {
        BlendOp_Add = D3D12_BLEND_OP_ADD,
        BlendOp_Subtract = D3D12_BLEND_OP_SUBTRACT,
        BlendOp_RevSubtract = D3D12_BLEND_OP_REV_SUBTRACT,
        BlendOp_Min = D3D12_BLEND_OP_MIN,
        BlendOp_Max = D3D12_BLEND_OP_MAX,
    };

    enum ColorWriteEnable
    {
        ColorWriteEnable_Red = D3D12_COLOR_WRITE_ENABLE_RED,
        ColorWriteEnable_Green = D3D12_COLOR_WRITE_ENABLE_GREEN,
        ColorWriteEnable_Blue = D3D12_COLOR_WRITE_ENABLE_BLUE,
        ColorWriteEnable_Alpha = D3D12_COLOR_WRITE_ENABLE_ALPHA,
        ColorWriteEnable_All = D3D12_COLOR_WRITE_ENABLE_ALL,
    };


    enum StencilOp
    {
        StencilOp_Keep = D3D12_STENCIL_OP_KEEP,
        StencilOp_Zero = D3D12_STENCIL_OP_ZERO,
        StencilOp_Replace = D3D12_STENCIL_OP_REPLACE,
        StencilOp_IncrSat = D3D12_STENCIL_OP_INCR_SAT,
        StencilOp_DecrSat = D3D12_STENCIL_OP_DECR_SAT,
        StencilOp_Invert = D3D12_STENCIL_OP_INVERT,
        StencilOp_Incr = D3D12_STENCIL_OP_INCR,
        StencilOp_Decr = D3D12_STENCIL_OP_DECR,
    };

    enum LogicOp
    {
        LogicOp_Clear = D3D12_LOGIC_OP_CLEAR,
        LogicOp_Set = D3D12_LOGIC_OP_SET,
        LogicOp_Copy = D3D12_LOGIC_OP_COPY,
        LogicOp_CopyInverted = D3D12_LOGIC_OP_COPY_INVERTED,
        LogicOp_Noop = D3D12_LOGIC_OP_NOOP,
        LogicOp_Invert = D3D12_LOGIC_OP_INVERT,
        LogicOp_And = D3D12_LOGIC_OP_AND,
        LogicOp_Nand = D3D12_LOGIC_OP_NAND,
        LogicOp_Or = D3D12_LOGIC_OP_OR,
        LogicOp_Nor = D3D12_LOGIC_OP_NOR,
        LogicOp_Xor = D3D12_LOGIC_OP_XOR,
        LogicOp_Equiv = D3D12_LOGIC_OP_EQUIV,
        LogicOp_AndReverse = D3D12_LOGIC_OP_AND_REVERSE,
        LogicOp_AndInverted = D3D12_LOGIC_OP_AND_INVERTED,
        LogicOp_OrReverse = D3D12_LOGIC_OP_OR_REVERSE,
        LogicOp_OrInverted = D3D12_LOGIC_OP_OR_INVERTED,
    };

    enum StaticBorderColor
    {
        StaticBorderColor_TransparentBlack = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,
        StaticBorderColor_OpaqueBlack = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,
        StaticBorderColor_OpaqueWhite = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE,
    };

    enum IndexBufferStripCutValue
    {
        IndexBufferStripCutValue_Disabled = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
        IndexBufferStripCutValue_0xFFFF = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF,
        IndexBufferStripCutValue_0xFFFFFFFF = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF,
    };

    enum PrimitiveTopologyType
    {
        PrimitiveTopologyType_Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
        PrimitiveTopologyType_Point = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
        PrimitiveTopologyType_Line = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
        PrimitiveTopologyType_Triangle = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
        PrimitiveTopologyType_Patch = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH,
    };

    enum PipelineStateFlag
    {
        PipelineStateFlag_None = D3D12_PIPELINE_STATE_FLAG_NONE,
        PipelineStateFlag_ToolDebug = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG,
    };

    enum InputClassification
    {
        InputClassification_PerVertex = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        InputClassification_PerInstance = D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,
    };

    enum ConservativeRasterizationMode
    {
        ConservativeRasterizationMode_Off = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
        ConservativeRasterizationMode_On = D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON,
    };

    enum DepthWriteMask
    {
        DepthWriteMask_Zero = D3D12_DEPTH_WRITE_MASK_ZERO,
        DepthWriteMask_All = D3D12_DEPTH_WRITE_MASK_ALL,
    };

    enum HeapType
    {
        HeapType_Default = D3D12_HEAP_TYPE_DEFAULT,
        HeapType_Upload = D3D12_HEAP_TYPE_UPLOAD,
        HeapType_Readback = D3D12_HEAP_TYPE_READBACK,
        HeapType_Custom = D3D12_HEAP_TYPE_CUSTOM,
    };

    enum CPUPageProperty
    {
        CPUPageProperty_Unknown = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
        CPUPageProperty_NotAvailable = D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE,
        CPUPageProperty_WriteCombine = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,
        CPUPageProperty_WriteBack = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
    };

    enum MemoryPool
    {
        MemoryPool_Unknown = D3D12_MEMORY_POOL_UNKNOWN,
        MemoryPool_L0 = D3D12_MEMORY_POOL_L0,
        MemoryPool_L1 = D3D12_MEMORY_POOL_L1,
    };

    enum HeapFlag
    {
        HeapFlag_None = D3D12_HEAP_FLAG_NONE,
        HeapFlag_Shared = D3D12_HEAP_FLAG_SHARED,
        HeapFlag_DenyBuffers = D3D12_HEAP_FLAG_DENY_BUFFERS,
        HeapFlag_AllowDisplay = D3D12_HEAP_FLAG_ALLOW_DISPLAY,
        HeapFlag_SharedCrossAdapter = D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER,
        HeapFlag_DenyRtDsTextures = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES	,
        HeapFlag_DenyNonRtDsTextures = D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES,
        HeapFlag_HardwareProtected = D3D12_HEAP_FLAG_HARDWARE_PROTECTED,
        HeapFlag_AllowWriteWatch = D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH,
        HeapFlag_AllowSharedAtomics = D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS,
        HeapFlag_AllowAllBuffersAndTextures = D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES,
        HeapFlag_AllowOnlyBuffers = D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS,
        HeapFlag_AllowOnlyNonRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES,
        HeapFlag_AllowOnlyRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES,
    };

    enum ResourceDimension
    {
        ResourceDimension_Unknown = D3D12_RESOURCE_DIMENSION_UNKNOWN,
        ResourceDimension_Buffer = D3D12_RESOURCE_DIMENSION_BUFFER,
        ResourceDimension_Texture1D = D3D12_RESOURCE_DIMENSION_TEXTURE1D,
        ResourceDimension_Texture2D = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        ResourceDimension_Texture3D = D3D12_RESOURCE_DIMENSION_TEXTURE3D,
    };

    enum TextureLayout
    {
        TextureLayout_Unknown = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        TextureLayout_RowMajor = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        TextureLayout_64KBUndefinedSwizzle = D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE,
        TextureLayout_64KBStandardSwizzle = D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE,
    };

    enum ResourceFlag : u32
    {
        ResourceFlag_None = D3D12_RESOURCE_FLAG_NONE,
        ResourceFlag_AllowRenderTarget = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,
        ResourceFlag_AllowDepthStencil = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
        ResourceFlag_AllowUnorderedAccess = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
        ResourceFlag_DenyShaderResource = D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE,
        ResourceFlag_AllowCrossAdapter = D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER,
        ResourceFlag_AllowSimultaneousAccess = D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS,
        ResourceFlag_VideoDecodeReferenceOnly = D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY,
    };

    enum ResourceState : u32
    {
        ResourceState_Common = D3D12_RESOURCE_STATE_COMMON,
        ResourceState_VertexAndConstantBuffer = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
        ResourceState_IndexBuffer = D3D12_RESOURCE_STATE_INDEX_BUFFER,
        ResourceState_RenderTarget = D3D12_RESOURCE_STATE_RENDER_TARGET,
        ResourceState_UnorderedAccess = D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
        ResourceState_DepthWrite = D3D12_RESOURCE_STATE_DEPTH_WRITE,
        ResourceState_DepthRead = D3D12_RESOURCE_STATE_DEPTH_READ,
        ResourceState_NonPixelShaderResource = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
        ResourceState_PixelShaderResource = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        ResourceState_StreamOut = D3D12_RESOURCE_STATE_STREAM_OUT,
        ResourceState_IndirectArgument = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT,
        ResourceState_CopyDest = D3D12_RESOURCE_STATE_COPY_DEST,
        ResourceState_CopySource = D3D12_RESOURCE_STATE_COPY_SOURCE,
        ResourceState_ResolveDest = D3D12_RESOURCE_STATE_RESOLVE_DEST,
        ResourceState_ResolveSource = D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
        ResourceState_GenericRead = D3D12_RESOURCE_STATE_GENERIC_READ,
        ResourceState_Present = D3D12_RESOURCE_STATE_PRESENT,
        ResourceState_Predication = D3D12_RESOURCE_STATE_PREDICATION,
        ResourceState_VideoDecodeRead = D3D12_RESOURCE_STATE_VIDEO_DECODE_READ,
        ResourceState_VideoDecodeWrite = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
        ResourceState_VideoProcessRead = D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ,
        ResourceState_VideoProcessWrite = D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE,
    };

    enum FenceFlag : u32
    {
        FenceFlag_None = D3D12_FENCE_FLAG_NONE,
        FenceFlag_Shared = D3D12_FENCE_FLAG_SHARED,
        FenceFlag_SharedCrossAdapter = D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER,
        FenceFlag_NonMonitored = D3D12_FENCE_FLAG_NON_MONITORED,
    };

    enum ResourceBarrierFlag
    {
        ResourceBarrierFlag_None = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        ResourceBarrierFlag_BeginOnly = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY,
        ResourceBarrierFlag_EndOnly = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY,
    };

    enum PrimitiveTopology
    {
        PrimitiveTopology_Undefined = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
        PrimitiveTopology_PointList = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
        PrimitiveTopology_LineList = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
        PrimitiveTopology_LineStrip = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
        PrimitiveTopology_TriangleList = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        PrimitiveTopology_TriangleStrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
        PrimitiveTopology_LineListADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
        PrimitiveTopology_LineStripADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
        PrimitiveTopology_TriangleListADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
        PrimitiveTopology_TriangleStripADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
        PrimitiveTopology_01ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_02ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_03ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_04ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_05ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_06ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_07ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_08ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_09ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_10ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_11ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_12ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_13ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_14ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_15ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_16ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_17ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_18ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_19ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_20ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_21ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_22ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_23ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_24ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_25ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_26ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_27ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_28ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_29ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_30ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_31ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
        PrimitiveTopology_32ControlPointPatchList = D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST,
    };

    //--------------------------------------------------------------
    //---
    //--- Structures
    //---
    //--------------------------------------------------------------
    struct GraphicsInitParam
    {
        u32 width_;
        u32 height_;
    };

    struct DescriptorRange
    {
        DescriptorRangeType type_;
        u32 numDescriptors_;
        u32 baseShaderRegister_;
        u32 registerSpace_;
        u32 offsetInDescriptorsFromTableStart_;
    };

    struct RootDescriptorTable
    {
        u32 numDescriptorRanges_;
        _Field_size_full_(numDescriptorRanges_)  const DescriptorRange *descriptorRanges_;
    };

    struct RootConstants
    {
        u32 shaderRegister_;
        u32 registerSpace_;
        u32 num32BitValues_;
    };

    struct RootDescriptor
    {
        u32 shaderRegister_;
        u32 registerSpace_;
    };

    struct RootParameter
    {
        RootParameterType type_;
        union
        {
            RootDescriptorTable descriptorTable_;
            RootConstants constants_;
            RootDescriptor descriptor_;
        };
        ShaderVisibility shaderVisibility_;
    };

    struct StaticSamplerDesc
    {
        Filter filter_;
        TextureAddressMode addressU_;
        TextureAddressMode addressV_;
        TextureAddressMode addressW_;
        f32 mipLODBias_;
        u32 maxAnisotropy_;
        ComparisonFunc comparisonFunc_;
        StaticBorderColor borderColor_;
        f32 minLOD_;
        f32 maxLOD_;
        u32 shaderRegister_;
        u32 registerSpace_;
        ShaderVisibility shaderVisibility_;
    };

    struct RootSignatureDesc
    {
        u32 numParameters_;
        const RootParameter* parameters_;
        u32 numStaticSamplers_;
        const StaticSamplerDesc* staticSamplers_;
        RootSignatureFlags flags_;
    };

    //--------------------------------------------------------------
    //---
    //--- RasterizerDesc
    //---
    //--------------------------------------------------------------
    struct RasterizerDesc
    {
        typedef D3D12_RASTERIZER_DESC desc_type;

        static const desc_type Solid;
        static const desc_type SolidMSAA;
        static const desc_type SolidCW;
        static const desc_type SolidCWMSAA;
        static const desc_type BothSided;
        static const desc_type BothSidedMSAA;
        static const desc_type Shadow;
        static const desc_type ShadowCW;
        static const desc_type ShadowBoth;
        static const desc_type Wire;
        static const desc_type WireCW;
        static const desc_type WireBoth;

        static D3D12_RASTERIZER_DESC create(
            FillMode fillMode,
            CullMode cullMode,
            BOOL frontCounterClockwise,
            s32 depthBias,
            f32 depthBiasClamp,
            f32 slopeScaledDepthBias,
            BOOL depthClipEnable,
            BOOL multisampleEnable,
            BOOL antialiasedLineEnable,
            u32 forcedSampleCount,
            ConservativeRasterizationMode conservativeRasterizationMode);
    };

    //--------------------------------------------------------------
    //---
    //--- BlendDesc
    //---
    //--------------------------------------------------------------
    struct BlendDesc
    {
        typedef D3D12_RENDER_TARGET_BLEND_DESC render_target_blend_desc_type;
        typedef D3D12_BLEND_DESC desc_type;

        static const render_target_blend_desc_type NoColorWrite;
        static const render_target_blend_desc_type Disable;
        static const render_target_blend_desc_type PreMultiplied;
        static const render_target_blend_desc_type Alpha;
        static const render_target_blend_desc_type Additive;
        static const render_target_blend_desc_type AlphaAdditive;

        static desc_type create(
            bool alphaToCoverageEnable=false,
            bool independentBlendEnable=false,
            const render_target_blend_desc_type& target0 = Disable,
            const render_target_blend_desc_type& target1 = Disable,
            const render_target_blend_desc_type& target2 = Disable,
            const render_target_blend_desc_type& target3 = Disable,
            const render_target_blend_desc_type& target4 = Disable,
            const render_target_blend_desc_type& target5 = Disable,
            const render_target_blend_desc_type& target6 = Disable,
            const render_target_blend_desc_type& target7 = Disable);

        static render_target_blend_desc_type create(
            bool blendEnable,
            bool logicOpEnable,
            Blend srcColor,
            Blend dstColor,
            BlendOp colorOp,
            Blend srcAlpha,
            Blend dstAlpha,
            BlendOp alphaOp,
            LogicOp logicalOp,
            ColorWriteEnable colorWrite);
    };

    //--------------------------------------------------------------
    //---
    //--- DepthStencilOpDesc
    //---
    //--------------------------------------------------------------
    struct DepthStencilOpDesc
    {
        typedef D3D12_DEPTH_STENCILOP_DESC desc_type;

        static const desc_type None;
        static desc_type create(
            StencilOp stencilFailOp,
            StencilOp stencilDepthFailOp,
            StencilOp stencilPassOp,
            StencilOp stencilFunc);
    };

    //--------------------------------------------------------------
    //---
    //--- DepthStencilDesc
    //---
    //--------------------------------------------------------------
    struct DepthStencilDesc
    {
        typedef D3D12_DEPTH_STENCIL_DESC desc_type;

        static const desc_type Disable;
        static const desc_type Depth;
        static const desc_type DepthReadOnly;
        static const desc_type DepthReadOnlyReversed;
        static const desc_type DepthTestEqual;

        static desc_type create(
            bool enable,
            DepthWriteMask writeMask,
            ComparisonFunc depthFunc,
            bool stencilEnable,
            u8 stencilReadMask,
            u8 stencilWriteMask,
            StencilOp frontFailOp,
            StencilOp frontDepthFailOp,
            StencilOp frontStencilPassOp,
            ComparisonFunc frontFunc,
            StencilOp backFailOp,
            StencilOp backDepthFailOp,
            StencilOp backStencilPassOp,
            ComparisonFunc backFunc);
    };

    //--------------------------------------------------------------
    //---
    //--- StreamOutputDesc
    //---
    //--------------------------------------------------------------
    struct StreamOutputDesc
    {
        typedef StreamOutputDesc desc_type;
        static const s32 MaxStreams = 4;

        D3D12_SO_DECLARATION_ENTRY soDeclarations_[MaxStreams];
        u32 numEntries_;
        u32 bufferStrides_[MaxStreams];
        u32 numStrides_;
        u32 rasterizedStream_;

        static desc_type create();
    };

    //--------------------------------------------------------------
    //---
    //--- RenderTargetFormat
    //---
    //--------------------------------------------------------------
    struct RenderTargetFormat
    {
        static const u32 MaxRenderTargets = 8;
        Format formats_[MaxRenderTargets];

        static RenderTargetFormat create(
            Format format0 = Format_UNKNOWN,
            Format format1 = Format_UNKNOWN,
            Format format2 = Format_UNKNOWN,
            Format format3 = Format_UNKNOWN,
            Format format4 = Format_UNKNOWN,
            Format format5 = Format_UNKNOWN,
            Format format6 = Format_UNKNOWN,
            Format format7 = Format_UNKNOWN);
    };

    //--------------------------------------------------------------
    //---
    //--- CachedPipelineState
    //---
    //--------------------------------------------------------------
    struct CachedPipelineState
    {
        typedef D3D12_CACHED_PIPELINE_STATE desc_type;
        static desc_type create(
            size_t blobSizeInBytes = 0,
            const void* blob = LGFX_NULL);
    };

    //--------------------------------------------------------------
    //---
    //--- HeapPropertiesDesc
    //---
    //--------------------------------------------------------------
    struct HeapPropertiesDesc
    {
        typedef D3D12_HEAP_PROPERTIES desc_type;

        static desc_type create(
            HeapType type,
            CPUPageProperty cpuPageProperty,
            MemoryPool memoryPool,
            u32 creationNodeMask=1,
            u32 visibleNodeMask =1);

        static desc_type create(
            HeapType type,
            u32 creationNodeMask=1,
            u32 visibleNodeMask =1);

        static desc_type create(
            CPUPageProperty cpuPageProperty,
            MemoryPool memoryPool,
            u32 creationNodeMask=1,
            u32 visibleNodeMask =1);
    };

    //--------------------------------------------------------------
    //---
    //--- ResourceDesc
    //---
    //--------------------------------------------------------------
    struct ResourceDesc
    {
        typedef D3D12_RESOURCE_DESC desc_type;

        static desc_type create(
            ResourceDimension dimension,
            u64 alignment,
            u64 width,
            u32 height,
            u16 depthOrArraySize,
            u16 mipLevels,
            Format format,
            u32 sampleCount,
            u32 sampleQuality,
            TextureLayout layout,
            ResourceFlag flags);

        static desc_type buffer(
            u64 size,
            ResourceFlag flags = ResourceFlag_None,
            u64 alignment = 0);

        static desc_type texture1D(
            Format format,
            u64 width,
            u16 arraySize = 1,
            u16 mipLevels = 0,
            ResourceFlag flags = ResourceFlag_None,
            TextureLayout layout = TextureLayout_Unknown,
            u64 alignment = 0);

        static desc_type texture2D(
            Format format,
            u64 width,
            u32 height,
            u16 arraySize = 1,
            u16 mipLevels = 0,
            u32 sampleCount = 0,
            u32 sampleQuality = 0,
            ResourceFlag flags = ResourceFlag_None,
            TextureLayout layout = TextureLayout_Unknown,
            u64 alignment = 0);

        static desc_type texture3D(
            Format format,
            u64 width,
            u32 height,
            u16 depth,
            u16 mipLevels = 0,
            ResourceFlag flags = ResourceFlag_None,
            TextureLayout layout = TextureLayout_Unknown,
            u64 alignment = 0);
    };

    //--------------------------------------------------------------
    //---
    //--- DepthStencil
    //---
    //--------------------------------------------------------------
    struct DepthStencil
    {
        f32 depth_;
        u8 stencil_;
    };

    //--------------------------------------------------------------
    //---
    //--- ClearValue
    //---
    //--------------------------------------------------------------
    struct ClearValue
    {
        Format format_;
        union
        {
            f32 color_[4];
            DepthStencil depthStencil_;
        };
    };

    //--------------------------------------------------------------
    //---
    //--- Range
    //---
    //--------------------------------------------------------------
    struct Range
    {
        size_t begin_;
        size_t end_;
    };

    //--------------------------------------------------------------
    //---
    //--- VertexBufferView
    //---
    //--------------------------------------------------------------
    struct VertexBufferView
    {
        GPUVirtualAddress bufferLocation_;
        u32 sizeInBytes_;
        u32 strideInBytes_;
    };

    //--------------------------------------------------------------
    //---
    //--- ResourceBarrier
    //---
    //--------------------------------------------------------------
    struct ResourceBarrier
    {
        typedef D3D12_RESOURCE_BARRIER desc_type;

        static desc_type transition(
            ID3D12Resource* resource,
            ResourceState stateBefore,
            ResourceState stateAfter,
            u32 subresource = ResourceBarrierAllSubresources,
            ResourceBarrierFlag flags = ResourceBarrierFlag_None);

        static desc_type aliasing(
            ID3D12Resource* resourceBefore,
            ID3D12Resource* resourceAfter);

        static desc_type UAV(ID3D12Resource* resource);
    };

    //--------------------------------------------------------------
    //---
    //--- Handle
    //---
    //--------------------------------------------------------------
    template<class Derived, class Type>
    class Handle
    {
    public:
        typedef Type* handle_type;
        typedef const Type* const_handle_type;

        Handle();
        Handle(const Handle& rhs);
        Handle(Handle&& rhs);
        explicit Handle(handle_type handle);
        ~Handle();

        inline bool valid() const;
        void destroy();

        Handle& operator=(const Handle& rhs);
        Handle& operator=(Handle&& rhs);

        void swap(Handle& rhs);

        const_handle_type operator->() const;
        handle_type operator->();
        operator const_handle_type() const;
        operator handle_type();

        template<class T>
        operator const T() const
        {
            return reinterpret_cast<const T>(handle_);
        }

        template<class T>
        operator T()
        {
            return reinterpret_cast<T>(handle_);
        }

        template<class T>
        Handle<Derived, T> as()
        {
            LGFX_ASSERT(valid());
            T* handle = LGFX_NULL;
            return SUCCEEDED(handle_->QueryInterface(IID_PPV_ARGS(&handle)))? Handle<Derived,T>(handle) : Handle<Derived,T>();
        }
    protected:
        handle_type handle_;
    };

    template<class Derived, class Type>
    Handle<Derived, Type>::Handle()
        :handle_(LGFX_NULL)
    {}

    template<class Derived, class Type>
    Handle<Derived, Type>::Handle(const Handle& rhs)
        :handle_(rhs.handle_)
    {
        if(LGFX_NULL != handle_){
            handle_->AddRef();
        }
    }

    template<class Derived, class Type>
    Handle<Derived, Type>::Handle(Handle&& rhs)
        :handle_(rhs.handle_)
    {
        rhs.handle_ = LGFX_NULL;
    }

    template<class Derived, class Type>
    Handle<Derived, Type>::Handle(handle_type handle)
        :handle_(handle)
    {}

    template<class Derived, class Type>
    Handle<Derived, Type>::~Handle()
    {
        if(LGFX_NULL != handle_){
            handle_->Release();
            handle_ = LGFX_NULL;
        }
    }

    template<class Derived, class Type>
    inline bool Handle<Derived, Type>::valid() const
    {
        return LGFX_NULL != handle_;
    }

    template<class Derived, class Type>
    void Handle<Derived, Type>::destroy()
    {
        if(LGFX_NULL != handle_){
            handle_->Release();
            handle_ = LGFX_NULL;
        }
    }

    template<class Derived, class Type>
    Handle<Derived, Type>& Handle<Derived, Type>::operator=(const Handle& rhs)
    {
        if(LGFX_NULL != handle_){
            handle_->Release();
        }
        handle_ = rhs.handle_;
        if(LGFX_NULL != handle_){
            handle_->AddRef();
        }
        return *this;
    }

    template<class Derived, class Type>
    Handle<Derived, Type>& Handle<Derived, Type>::operator=(Handle&& rhs)
    {
        if(this != &rhs){
            if(LGFX_NULL != handle_){
                handle_->Release();
            }
            handle_ = rhs.handle_;
            rhs.handle_ = LGFX_NULL;
        }
        return *this;
    }


    template<class Derived, class Type>
    void Handle<Derived, Type>::swap(Handle& rhs)
    {
        lgfx::swap(handle_, rhs.handle_);
    }

    template<class Derived, class Type>
    typename Handle<Derived, Type>::const_handle_type Handle<Derived, Type>::operator->() const
    {
        LGFX_ASSERT(LGFX_NULL != handle_);
        return handle_;
    }

    template<class Derived, class Type>
    typename Handle<Derived, Type>::handle_type Handle<Derived, Type>::operator->()
    {
        LGFX_ASSERT(LGFX_NULL != handle_);
        return handle_;
    }

    template<class Derived, class Type>
    Handle<Derived, Type>::operator const_handle_type() const
    {
        return handle_;
    }

    template<class Derived, class Type>
    Handle<Derived, Type>::operator handle_type()
    {
        return handle_;
    }

#define LGFX_DERIVED_HANDLE_TYPE(NAME, BASE)\
    typedef Handle<NAME, BASE> parent_type;\
    NAME(){}\
    NAME(const NAME& rhs)\
        :parent_type(rhs)\
    {}\
    NAME(NAME&& rhs)\
        :parent_type(lgfx::move(rhs))\
    {}\
    explicit NAME(handle_type handle)\
        :parent_type(handle)\
    {}\
    NAME& operator=(const NAME& rhs)\
    {\
        parent_type::operator=(rhs);\
        return *this;\
    }\
    NAME& operator=(NAME&& rhs)\
    {\
        parent_type::operator=(lgfx::move(rhs));\
        return *this;\
    }

    //--------------------------------------------------------------
    //---
    //--- DescriptorHandle
    //---
    //--------------------------------------------------------------
    template<class T>
    struct DescriptorHandle : public T
    {
        DescriptorHandle() = default;

        explicit DescriptorHandle(const T& rhs)
            :T(rhs)
        {}

        DescriptorHandle(const T& rhs, s32 offsetScaledByIncrementSize)
        {
            initOffsetted(rhs, offsetScaledByIncrementSize);
        }

        DescriptorHandle(const T &rhs, s32 offsetInDescriptors, u32 descriptorIncrementSize)
        {
            initOffsetted(rhs, offsetInDescriptors, descriptorIncrementSize);
        }
        DescriptorHandle& offset(s32 offsetInDescriptors, u32 descriptorIncrementSize)
        {
            ptr += static_cast<s64>(offsetInDescriptors) * static_cast<u64>(descriptorIncrementSize);
            return *this;
        }
        DescriptorHandle& offset(s32 offsetScaledByIncrementSize)
        {
            ptr += offsetScaledByIncrementSize;
            return *this;
        }
        bool operator==(const T& other) const
        {
            return (ptr == other.ptr);
        }
        bool operator!=(const T& other) const
        {
            return (ptr != other.ptr);
        }
        DescriptorHandle &operator=(const T &other)
        {
            ptr = other.ptr;
            return *this;
        }

        inline void initOffsetted(const T &base, s32 offsetScaledByIncrementSize)
        {
            initOffsetted(*this, base, offsetScaledByIncrementSize);
        }

        inline void initOffsetted(const T &base, s32 offsetInDescriptors, u32 descriptorIncrementSize)
        {
            initOffsetted(*this, base, offsetInDescriptors, descriptorIncrementSize);
        }

        static inline void initOffsetted(T &handle, const T &base, s32 offsetScaledByIncrementSize)
        {
            handle.ptr = base.ptr + offsetScaledByIncrementSize;
        }

        static inline void initOffsetted(T &handle, const T &base, s32 offsetInDescriptors, u32 descriptorIncrementSize)
        {
            handle.ptr = static_cast<u64>(base.ptr + static_cast<s64>(offsetInDescriptors) * static_cast<u64>(descriptorIncrementSize));
        }
    };

    typedef DescriptorHandle<D3D12_CPU_DESCRIPTOR_HANDLE> CPUDesctiptorHandle;

    //--------------------------------------------------------------
    class VertexBuffer;

    //--------------------------------------------------------------
    //---
    //--- Factory
    //---
    //--------------------------------------------------------------
    class Factory : public Handle<Factory, IDXGIFactory2>
    {
    public:
        static Factory create();

        LGFX_DERIVED_HANDLE_TYPE(Factory, IDXGIFactory2);
    };

    //--------------------------------------------------------------
    //---
    //--- Adapter
    //---
    //--------------------------------------------------------------
    class Adapter : public Handle<Adapter, IDXGIAdapter1>
    {
    public:
        static Adapter create(Factory& factory, FeatureLevel featureLevel);

        LGFX_DERIVED_HANDLE_TYPE(Adapter, IDXGIAdapter1);
    };

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    class Device : public Handle<Device, ID3D12Device>
    {
    public:
        static Device create(Adapter& adapter, FeatureLevel featureLevel);

        bool createCommittedResource(
            const HeapPropertiesDesc::desc_type* heapProperties,
            lgfx::HeapFlag heapFlags,
            const ResourceDesc::desc_type* resourceDesc,
            ResourceState initialResourceState,
            const ClearValue* optimizedClearValue,
            VertexBuffer& vertexBuffer);

        LGFX_DERIVED_HANDLE_TYPE(Device, ID3D12Device);
    };

    //--------------------------------------------------------------
    //---
    //--- CommandQueue
    //---
    //--------------------------------------------------------------
    class CommandQueue : public Handle<CommandQueue, ID3D12CommandQueue>
    {
    public:
        static CommandQueue create(Device& device, CommandListType type);

        LGFX_DERIVED_HANDLE_TYPE(CommandQueue, ID3D12CommandQueue);
    };

    //--------------------------------------------------------------
    //---
    //--- SwapChain
    //---
    //--------------------------------------------------------------
    class SwapChain : public Handle<SwapChain, IDXGISwapChain3>
    {
    public:
        static SwapChain create(
            Factory& factory,
            CommandQueue& commandQueue,
            HWND window,
            u32 count,
            s32 width,
            s32 height,
            Format format,
            Usage usage,
            SwapEffect swapEffect,
            u32 flags,
            MWA mwaFlags);

        LGFX_DERIVED_HANDLE_TYPE(SwapChain, IDXGISwapChain3);
    };

    //--------------------------------------------------------------
    //---
    //--- DescriptorHeap
    //---
    //--------------------------------------------------------------
    class DescriptorHeap : public Handle<DescriptorHeap, ID3D12DescriptorHeap>
    {
    public:
        static DescriptorHeap create(Device& device, DescriptorHeapType type, u32 count, DescriptorHeapFlag flags);

        LGFX_DERIVED_HANDLE_TYPE(DescriptorHeap, ID3D12DescriptorHeap);
    };

    //--------------------------------------------------------------
    //---
    //--- Resource
    //---
    //--------------------------------------------------------------
    class Resource : public Handle<Resource, ID3D12Resource>
    {
    public:
        LGFX_DERIVED_HANDLE_TYPE(Resource, ID3D12Resource);
    };

    //--------------------------------------------------------------
    //---
    //--- VertexBuffer
    //---
    //--------------------------------------------------------------
    class VertexBuffer : public Handle<VertexBuffer, ID3D12Resource>
    {
    public:
        LGFX_DERIVED_HANDLE_TYPE(VertexBuffer, ID3D12Resource);

        template<class T>
        bool map(u32 subresource, const Range* range, T** data)
        {
            return SUCCEEDED(handle_->Map(subresource, reinterpret_cast<const D3D12_RANGE*>(range), reinterpret_cast<void**>(data)));
        }

        void unmap(u32 subresource, const Range* range);
    };

    //--------------------------------------------------------------
    //---
    //--- IBlob
    //---
    //--------------------------------------------------------------
    class IBlob
    {
    public:
        typedef u8* pointer_type;
        typedef const u8* const_pointer_type;

        static IBlob* create(size_t size, u8* pointer);

        bool valid() const;
        void destroy();

        IBlob& operator=(IBlob&& rhs);

        void swap(IBlob& rhs);

        template<class T>
        operator const T() const
        {
            return reinterpret_cast<const T>(pointer_);
        }

        template<class T>
        operator T()
        {
            return reinterpret_cast<T>(pointer_);
        }

        size_t size() const;
        const u8* get() const;
        u8* get();
        const u8& operator[](size_t index) const;
        u8& operator[](size_t index);

        void AddRef();
        void Release();
    private:
        IBlob();
        IBlob(IBlob&& rhs);
        IBlob(size_t size, pointer_type pointer);
        ~IBlob();

        IBlob(const IBlob& rhs) = delete;
        IBlob& operator=(const IBlob& rhs) = delete;

        size_t size_;
        u8* pointer_;
        s64 referenceCount_;
    };

    //--------------------------------------------------------------
    //---
    //--- Blob
    //---
    //--------------------------------------------------------------
    class Blob : public Handle<Blob, IBlob>
    {
    public:
        static Blob loadFileAll(const Char* filepath);

        LGFX_DERIVED_HANDLE_TYPE(Blob, IBlob);
    };

    //--------------------------------------------------------------
    //---
    //--- Fence
    //---
    //--------------------------------------------------------------
    class Fence : public Handle<Fence, ID3D12Fence>
    {
    public:
        static Fence create(Device& device, u64 initialValue, FenceFlag flags);

        LGFX_DERIVED_HANDLE_TYPE(Fence, ID3D12Fence);
    };

    //--------------------------------------------------------------
    //---
    //--- RootSignature
    //---
    //--------------------------------------------------------------
    class RootSignature : public Handle<RootSignature, ID3D12RootSignature>
    {
    public:
        static RootSignature create(Device& device, const RootSignatureDesc& desc);

        LGFX_DERIVED_HANDLE_TYPE(RootSignature, ID3D12RootSignature);
    };

    //--------------------------------------------------------------
    //---
    //--- CommandAllocator
    //---
    //--------------------------------------------------------------
    class CommandAllocator : public Handle<CommandAllocator, ID3D12CommandAllocator>
    {
    public:
        static CommandAllocator create(Device& device, CommandListType type);

        LGFX_DERIVED_HANDLE_TYPE(CommandAllocator, ID3D12CommandAllocator);
    };

    //--------------------------------------------------------------
    //---
    //--- PipelineState
    //---
    //--------------------------------------------------------------
    class PipelineState : public Handle<PipelineState, ID3D12PipelineState>
    {
    public:
        typedef D3D12_INPUT_ELEMENT_DESC input_element_desc_type;
        typedef StreamOutputDesc stream_output_desc_type;
        typedef D3D12_BLEND_DESC blend_desc_type;
        typedef D3D12_RASTERIZER_DESC rasterizer_desc_type;
        typedef D3D12_DEPTH_STENCIL_DESC depth_stencil_desc_type;
        typedef D3D12_INPUT_LAYOUT_DESC input_layout_desc_type;
        typedef DXGI_SAMPLE_DESC sample_desc_type;
        typedef typename CachedPipelineState::desc_type cached_pipeline_state_type;
        static const u32 MaxRenderTargets = RenderTargetFormat::MaxRenderTargets;

        static PipelineState create(
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
            PipelineStateFlag pipelineStateFlags);

        LGFX_DERIVED_HANDLE_TYPE(PipelineState, ID3D12PipelineState);
    };

    //--------------------------------------------------------------
    //---
    //--- GraphicsCommandList
    //---
    //--------------------------------------------------------------
    class GraphicsCommandList : public Handle<GraphicsCommandList, ID3D12GraphicsCommandList>
    {
    public:
        static GraphicsCommandList create(Device& device, u32 nodeMask, CommandListType type, CommandAllocator& commandAllocator, PipelineState& pipelineState);

        LGFX_DERIVED_HANDLE_TYPE(GraphicsCommandList, ID3D12GraphicsCommandList);
    };
}
#endif //INC_LGFX_DX12_H_
