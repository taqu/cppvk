/**
@file lgfx_dx12.cpp
@author t-sakai
@date 2018/10/26 create
*/
#include "lgfx.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- RasterizerDesc
    //---
    //--------------------------------------------------------------
    const RasterizerDesc::desc_type RasterizerDesc::Solid ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::SolidMSAA ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_TRUE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::SolidCW ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_FALSE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::SolidCWMSAA ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_FALSE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_TRUE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::BothSided ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_None),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::BothSidedMSAA ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_None),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_TRUE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::Shadow ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_TRUE,
        -100,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        -1.5f,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::ShadowCW ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_FALSE,
        -100,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        -1.5f,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::ShadowBoth ={
        static_cast<D3D12_FILL_MODE>(FillMode_Solid),
        static_cast<D3D12_CULL_MODE>(CullMode_None),
        LGFX_TRUE,
        -100,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        -1.5f,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::Wire ={
        static_cast<D3D12_FILL_MODE>(FillMode_WireFrame),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::WireCW ={
        static_cast<D3D12_FILL_MODE>(FillMode_WireFrame),
        static_cast<D3D12_CULL_MODE>(CullMode_Back),
        LGFX_FALSE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    const RasterizerDesc::desc_type RasterizerDesc::WireBoth ={
        static_cast<D3D12_FILL_MODE>(FillMode_WireFrame),
        static_cast<D3D12_CULL_MODE>(CullMode_None),
        LGFX_TRUE,
        D3D12_DEFAULT_DEPTH_BIAS,
        D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        LGFX_TRUE,
        LGFX_FALSE,
        LGFX_FALSE,
        0,
        static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(ConservativeRasterizationMode_Off),
    };

    D3D12_RASTERIZER_DESC RasterizerDesc::create(
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
        ConservativeRasterizationMode conservativeRasterizationMode)
    {
        return {
            static_cast<D3D12_FILL_MODE>(fillMode),
            static_cast<D3D12_CULL_MODE>(cullMode),
            frontCounterClockwise,
            depthBias,
            depthBiasClamp,
            slopeScaledDepthBias,
            depthClipEnable,
            multisampleEnable,
            antialiasedLineEnable,
            forcedSampleCount,
            static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(conservativeRasterizationMode),
        };
    }

    //--------------------------------------------------------------
    //---
    //--- BlendDesc
    //---
    //--------------------------------------------------------------
    const BlendDesc::render_target_blend_desc_type BlendDesc::NoColorWrite ={
        LGFX_FALSE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(0),
    };

    const BlendDesc::render_target_blend_desc_type BlendDesc::Disable ={
        LGFX_FALSE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND>(Blend_Zero), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(ColorWriteEnable_All),
    };

    const BlendDesc::render_target_blend_desc_type BlendDesc::PreMultiplied ={
        LGFX_TRUE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(ColorWriteEnable_All),
    };

    const BlendDesc::render_target_blend_desc_type BlendDesc::Alpha ={
        LGFX_TRUE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_SrcAlpha), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(ColorWriteEnable_All),
    };

    const BlendDesc::render_target_blend_desc_type BlendDesc::Additive ={
        LGFX_TRUE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(ColorWriteEnable_All),
    };

    const BlendDesc::render_target_blend_desc_type BlendDesc::AlphaAdditive ={
        LGFX_TRUE,
        LGFX_FALSE,
        static_cast<D3D12_BLEND>(Blend_SrcAlpha), static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_BLEND>(Blend_One), static_cast<D3D12_BLEND>(Blend_InvSrcAlpha), static_cast<D3D12_BLEND_OP>(BlendOp_Add),
        static_cast<D3D12_LOGIC_OP>(LogicOp_Noop),
        static_cast<D3D12_COLOR_WRITE_ENABLE>(ColorWriteEnable_All),
    };

    BlendDesc::desc_type BlendDesc::create(
        bool alphaToCoverageEnable,
        bool independentBlendEnable,
        const render_target_blend_desc_type& target0,
        const render_target_blend_desc_type& target1,
        const render_target_blend_desc_type& target2,
        const render_target_blend_desc_type& target3,
        const render_target_blend_desc_type& target4,
        const render_target_blend_desc_type& target5,
        const render_target_blend_desc_type& target6,
        const render_target_blend_desc_type& target7)
    {
        return {
            alphaToCoverageEnable? LGFX_TRUE : LGFX_FALSE,
            independentBlendEnable? LGFX_TRUE : LGFX_FALSE,
            {target0, target1, target2, target3, target4, target5, target6, target7},
        };
    }

    BlendDesc::render_target_blend_desc_type BlendDesc::create(
        bool blendEnable,
        bool logicOpEnable,
        Blend srcColor,
        Blend dstColor,
        BlendOp colorOp,
        Blend srcAlpha,
        Blend dstAlpha,
        BlendOp alphaOp,
        LogicOp logicalOp,
        ColorWriteEnable colorWrite)
    {
        return {
            blendEnable? LGFX_TRUE : LGFX_FALSE,
            logicOpEnable? LGFX_TRUE : LGFX_FALSE,
            static_cast<D3D12_BLEND>(srcColor), static_cast<D3D12_BLEND>(dstColor), static_cast<D3D12_BLEND_OP>(colorOp),
            static_cast<D3D12_BLEND>(srcAlpha), static_cast<D3D12_BLEND>(dstAlpha), static_cast<D3D12_BLEND_OP>(alphaOp),
            static_cast<D3D12_LOGIC_OP>(logicalOp),
            static_cast<UINT8>(colorWrite),
        };
    }

    //--------------------------------------------------------------
    //---
    //--- DepthStencilOpDesc
    //---
    //--------------------------------------------------------------
    const DepthStencilOpDesc::desc_type DepthStencilOpDesc::None = {
        static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
        static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
        static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Never),
    };

    DepthStencilOpDesc::desc_type DepthStencilOpDesc::create(
        StencilOp stencilFailOp,
        StencilOp stencilDepthFailOp,
        StencilOp stencilPassOp,
        StencilOp stencilFunc)
    {
        return {
            static_cast<D3D12_STENCIL_OP>(stencilFailOp),
            static_cast<D3D12_STENCIL_OP>(stencilDepthFailOp),
            static_cast<D3D12_STENCIL_OP>(stencilPassOp),
            static_cast<D3D12_COMPARISON_FUNC>(stencilFunc),
        };
    }

    //--------------------------------------------------------------
    //---
    //--- DepthStencilDesc
    //---
    //--------------------------------------------------------------
    const DepthStencilDesc::desc_type DepthStencilDesc::Disable ={
        LGFX_FALSE,
        static_cast<D3D12_DEPTH_WRITE_MASK>(DepthWriteMask_Zero),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        LGFX_FALSE,
        D3D12_DEFAULT_STENCIL_READ_MASK,
        D3D12_DEFAULT_STENCIL_WRITE_MASK,
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
    };

    const DepthStencilDesc::desc_type DepthStencilDesc::Depth ={
        LGFX_TRUE,
        static_cast<D3D12_DEPTH_WRITE_MASK>(DepthWriteMask_All),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        LGFX_FALSE,
        D3D12_DEFAULT_STENCIL_READ_MASK,
        D3D12_DEFAULT_STENCIL_WRITE_MASK,
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        },
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
    };

    const DepthStencilDesc::desc_type DepthStencilDesc::DepthReadOnly ={
        LGFX_TRUE,
        static_cast<D3D12_DEPTH_WRITE_MASK>(DepthWriteMask_Zero),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        LGFX_FALSE,
        D3D12_DEFAULT_STENCIL_READ_MASK,
        D3D12_DEFAULT_STENCIL_WRITE_MASK,
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        },
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
    };

    const DepthStencilDesc::desc_type DepthStencilDesc::DepthReadOnlyReversed ={
        LGFX_TRUE,
        static_cast<D3D12_DEPTH_WRITE_MASK>(DepthWriteMask_Zero),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Less),
        LGFX_FALSE,
        D3D12_DEFAULT_STENCIL_READ_MASK,
        D3D12_DEFAULT_STENCIL_WRITE_MASK,
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        },
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
    };

    const DepthStencilDesc::desc_type DepthStencilDesc::DepthTestEqual ={
        LGFX_TRUE,
        static_cast<D3D12_DEPTH_WRITE_MASK>(DepthWriteMask_Zero),
        static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Equal),
        LGFX_FALSE,
        D3D12_DEFAULT_STENCIL_READ_MASK,
        D3D12_DEFAULT_STENCIL_WRITE_MASK,
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_GreaterEqual),
        },
        {
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_STENCIL_OP>(StencilOp_Keep),
            static_cast<D3D12_COMPARISON_FUNC>(ComparisonFunc_Always),
        },
    };

    DepthStencilDesc::desc_type DepthStencilDesc::create(
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
        ComparisonFunc backFunc)
    {
        return {
            enable? LGFX_TRUE : LGFX_FALSE,
            static_cast<D3D12_DEPTH_WRITE_MASK>(writeMask),
            static_cast<D3D12_COMPARISON_FUNC>(depthFunc),
            stencilEnable? LGFX_TRUE : LGFX_FALSE,
            stencilReadMask,
            stencilWriteMask,
            {
                static_cast<D3D12_STENCIL_OP>(frontFailOp),
                static_cast<D3D12_STENCIL_OP>(frontDepthFailOp),
                static_cast<D3D12_STENCIL_OP>(frontStencilPassOp),
                static_cast<D3D12_COMPARISON_FUNC>(frontFunc),
            },
            {
                static_cast<D3D12_STENCIL_OP>(backFailOp),
                static_cast<D3D12_STENCIL_OP>(backDepthFailOp),
                static_cast<D3D12_STENCIL_OP>(backStencilPassOp),
                static_cast<D3D12_COMPARISON_FUNC>(backFunc),
            },
        };
    }

    //--------------------------------------------------------------
    //---
    //--- StreamOutputDesc
    //---
    //--------------------------------------------------------------
    StreamOutputDesc::desc_type StreamOutputDesc::create()
    {
        return {
            {0},
            0,
            {0},
            0,
            0,
        };
    }

    //--------------------------------------------------------------
    //---
    //--- RenderTargetFormat
    //---
    //--------------------------------------------------------------
    RenderTargetFormat RenderTargetFormat::create(
        Format format0,
        Format format1,
        Format format2,
        Format format3,
        Format format4,
        Format format5,
        Format format6,
        Format format7)
    {
        return {
            format0, format1, format2, format3,
            format4, format5, format6, format7,
        };
    }

    //--------------------------------------------------------------
    //---
    //--- CachedPipelineState
    //---
    //--------------------------------------------------------------
    CachedPipelineState::desc_type CachedPipelineState::create(
        size_t blobSizeInBytes,
        const void* blob)
    {
        return {blob, blobSizeInBytes};
    }

    //--------------------------------------------------------------
    //---
    //--- HeapPropertiesDesc
    //---
    //--------------------------------------------------------------
    HeapPropertiesDesc::desc_type HeapPropertiesDesc::create(
        HeapType type,
        CPUPageProperty cpuPageProperty,
        MemoryPool memoryPool,
        u32 creationNodeMask,
        u32 visibleNodeMask)
    {
        return {static_cast<D3D12_HEAP_TYPE>(type), static_cast<D3D12_CPU_PAGE_PROPERTY>(cpuPageProperty), static_cast<D3D12_MEMORY_POOL>(memoryPool), creationNodeMask, visibleNodeMask};
    }

    HeapPropertiesDesc::desc_type HeapPropertiesDesc::create(
        HeapType type,
        u32 creationNodeMask,
        u32 visibleNodeMask)
    {
        return {static_cast<D3D12_HEAP_TYPE>(type), D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, creationNodeMask, visibleNodeMask};
    }

    HeapPropertiesDesc::desc_type HeapPropertiesDesc::create(
        CPUPageProperty cpuPageProperty,
        MemoryPool memoryPool,
        u32 creationNodeMask,
        u32 visibleNodeMask)
    {
        return {D3D12_HEAP_TYPE_CUSTOM, static_cast<D3D12_CPU_PAGE_PROPERTY>(cpuPageProperty), static_cast<D3D12_MEMORY_POOL>(memoryPool), creationNodeMask, visibleNodeMask};
    }

    //--------------------------------------------------------------
    //---
    //--- ResourceDesc
    //---
    //--------------------------------------------------------------
    ResourceDesc::desc_type ResourceDesc::create(
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
        ResourceFlag flags)
    {
        return {
            static_cast<D3D12_RESOURCE_DIMENSION>(dimension),
            alignment,
            width,
            height,
            depthOrArraySize,
            mipLevels,
            static_cast<DXGI_FORMAT>(format),
            sampleCount,
            sampleQuality,
            static_cast<D3D12_TEXTURE_LAYOUT>(layout),
            static_cast<D3D12_RESOURCE_FLAGS>(flags),
        };
    }

    ResourceDesc::desc_type ResourceDesc::buffer(
        u64 size,
        ResourceFlag flags,
        u64 alignment)
    {
        return {
            static_cast<D3D12_RESOURCE_DIMENSION>(D3D12_RESOURCE_DIMENSION_BUFFER),
            alignment,
            size,
            1,
            1,
            1,
            DXGI_FORMAT_UNKNOWN,
            1,
            0,
            D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
            static_cast<D3D12_RESOURCE_FLAGS>(flags),
        };
    }

    ResourceDesc::desc_type ResourceDesc::texture1D(
        Format format,
        u64 width,
        u16 arraySize,
        u16 mipLevels,
        ResourceFlag flags,
        TextureLayout layout,
        u64 alignment)
    {
        return {
            D3D12_RESOURCE_DIMENSION_TEXTURE1D,
            alignment,
            width,
            1,
            arraySize,
            mipLevels,
            static_cast<DXGI_FORMAT>(format),
            1,
            0,
            static_cast<D3D12_TEXTURE_LAYOUT>(layout),
            static_cast<D3D12_RESOURCE_FLAGS>(flags),
        };
    }

    ResourceDesc::desc_type ResourceDesc::texture2D(
        Format format,
        u64 width,
        u32 height,
        u16 arraySize,
        u16 mipLevels,
        u32 sampleCount,
        u32 sampleQuality,
        ResourceFlag flags,
        TextureLayout layout,
        u64 alignment)
    {
        return {
            D3D12_RESOURCE_DIMENSION_TEXTURE2D,
            alignment,
            width,
            height,
            arraySize,
            mipLevels,
            static_cast<DXGI_FORMAT>(format),
            sampleCount,
            sampleQuality,
            static_cast<D3D12_TEXTURE_LAYOUT>(layout),
            static_cast<D3D12_RESOURCE_FLAGS>(flags),
        };
    }

    ResourceDesc::desc_type ResourceDesc::texture3D(
        Format format,
        u64 width,
        u32 height,
        u16 depth,
        u16 mipLevels,
        ResourceFlag flags,
        TextureLayout layout,
        u64 alignment)
    {
        return {
            D3D12_RESOURCE_DIMENSION_TEXTURE3D,
            alignment,
            width,
            height,
            depth,
            mipLevels,
            static_cast<DXGI_FORMAT>(format),
            1,
            0,
            static_cast<D3D12_TEXTURE_LAYOUT>(layout),
            static_cast<D3D12_RESOURCE_FLAGS>(flags),
        };
    }

    //--------------------------------------------------------------
    //---
    //--- ResourceBarrier
    //---
    //--------------------------------------------------------------
    ResourceBarrier::desc_type ResourceBarrier::transition(
        ID3D12Resource* resource,
        ResourceState stateBefore,
        ResourceState stateAfter,
        u32 subresource,
        ResourceBarrierFlag flags)
    {
        desc_type result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        result.Flags = static_cast<D3D12_RESOURCE_BARRIER_FLAGS>(flags);
        result.Transition.pResource = resource;
        result.Transition.StateBefore = static_cast<D3D12_RESOURCE_STATES>(stateBefore);
        result.Transition.StateAfter = static_cast<D3D12_RESOURCE_STATES>(stateAfter);
        result.Transition.Subresource = subresource;
        return result;
    }

    ResourceBarrier::desc_type ResourceBarrier::aliasing(
        ID3D12Resource* resourceBefore,
        ID3D12Resource* resourceAfter)
    {
        desc_type result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_ALIASING;
        result.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        result.Aliasing.pResourceBefore = resourceBefore;
        result.Aliasing.pResourceAfter = resourceAfter;
        return result;
    }

    ResourceBarrier::desc_type ResourceBarrier::UAV(ID3D12Resource* resource)
    {
        desc_type result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
        result.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        result.UAV.pResource = resource;
        return result;
    }

    //--------------------------------------------------------------
    //---
    //--- IBlob
    //---
    //--------------------------------------------------------------
    IBlob::IBlob()
        :size_(0)
        ,pointer_(LGFX_NULL)
        ,referenceCount_(1)
    {}

    IBlob::IBlob(IBlob&& rhs)
        :size_(rhs.size_)
        ,pointer_(rhs.pointer_)
        ,referenceCount_(rhs.referenceCount_)
    {
        rhs.size_ = 0;
        rhs.pointer_ = LGFX_NULL;
        rhs.referenceCount_ = 0;
    }

    IBlob::IBlob(size_t size, pointer_type pointer)
        :size_(size)
        ,pointer_(pointer)
        ,referenceCount_(1)
    {}

    IBlob::~IBlob()
    {
        destroy();
    }

    bool IBlob::valid() const
    {
        return LGFX_NULL != pointer_;
    }

    void IBlob::destroy()
    {
        size_ = 0;
        LGFX_DELETE_ARRAY(pointer_);
    }

    IBlob& IBlob::operator=(IBlob&& rhs)
    {
        if(this != &rhs){
            LGFX_DELETE_ARRAY(pointer_);

            size_ = rhs.size_;
            pointer_ = rhs.pointer_;
            referenceCount_ = rhs.referenceCount_;

            rhs.size_ = 0;
            rhs.pointer_ = LGFX_NULL;
            rhs.referenceCount_ = 0;
        }
        return *this;
    }

    void IBlob::swap(IBlob& rhs)
    {
        lgfx::swap(size_, rhs.size_);
        lgfx::swap(pointer_, rhs.pointer_);
        lgfx::swap(referenceCount_, rhs.referenceCount_);
    }

    size_t IBlob::size() const
    {
        return size_;
    }

    const u8* IBlob::get() const
    {
        return pointer_;
    }

    u8* IBlob::get()
    {
        return pointer_;
    }

    const u8& IBlob::operator[](size_t index) const
    {
        LGFX_ASSERT(index<size_);
        return pointer_[index];
    }

    u8& IBlob::operator[](size_t index)
    {
        LGFX_ASSERT(index<size_);
        return pointer_[index];
    }

    void IBlob::AddRef()
    {
        ++referenceCount_;
    }

    void IBlob::Release()
    {
        --referenceCount_;
        if(0 == referenceCount_){
            LGFX_DELETE_RAW(this);
        }
    }

    IBlob* IBlob::create(size_t size, u8* pointer)
    {
        return LGFX_NEW IBlob(size, pointer);
    }
}
