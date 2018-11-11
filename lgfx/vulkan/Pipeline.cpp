/**
@file Pipeline.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "../lgfx_vulkan.h"

namespace lgfx
{
    //--------------------------------------------------------------
    //---
    //--- PipelineState
    //---
    //--------------------------------------------------------------
    const ShaderStage PipelineState::ShaderStages[ShaderType_Num]
    {
        ShaderStage_HS,
        ShaderStage_DS,
        ShaderStage_VS,
        ShaderStage_GS,
        ShaderStage_PS,
        ShaderStage_CS,
    };

    PipelineState::PipelineState()
        :viewport_({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f})
        ,scissor_({0, 0, 0, 0})
        ,rasterization_({LGFX_FALSE, LGFX_FALSE, PolygonMode_Fill, CullMode_Back, FrontFace_CounterClockwise, LGFX_FALSE, 0.0f, 0.0f, 0.0f, 1.0f})
        ,multiSample_({SampleCount_1, LGFX_FALSE, 1.0f, LGFX_NULL, LGFX_FALSE, LGFX_FALSE})
        ,colorBlendAttachment_({LGFX_FALSE, BlendFactor_One, BlendFactor_Zero, BlendOp_Add, BlendFactor_One, BlendFactor_Zero, BlendOp_Add, ColorComponent_R|ColorComponent_G|ColorComponent_B|ColorComponent_A})
        ,colorBlendState_({LGFX_FALSE, LogicOp_Copy, {0.0f, 0.0f, 0.0f, 0.0f}})
    {}

    void PipelineState::setShader(ShaderStage stage, Shader& shader)
    {
        shaders_[stage] = shader;
    }

    //--------------------------------------------------------------
    //---
    //--- Pipeline
    //---
    //--------------------------------------------------------------
    VkPipeline Pipeline::create(VkDevice device, VkRenderPass renderPass, const PipelineState& state, const VkAllocationCallbacks* allocator)
    {
        VkPipelineLayoutCreateInfo layoutCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineLayoutCreateFlags
            0, //set layout count
            LGFX_NULL, //VkDescriptorSetLayout 
            0, //push constant range count
            LGFX_NULL, //VkPushConstantRange
        };
        VkPipelineLayout pipelineLayout = LGFX_NULL;
        if(VK_SUCCESS != vkCreatePipelineLayout(device, &layoutCreateInfo, allocator, &pipelineLayout)){
            return LGFX_NULL;
        }

        //Shader stages
        //--------------------------------------------------------------
        u32 numShaderStages = 0;
        VkPipelineShaderStageCreateInfo shaderStageCreateInfos[ShaderType_Num];
        if(state.shaders_[ShaderType_CS].valid()){
            shaderStageCreateInfos[numShaderStages++] =
            {
                VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, //structure type
                LGFX_NULL, //next
                0, //VkPipelineShaderStageCreateFlags
                VK_SHADER_STAGE_COMPUTE_BIT, //VkShaderStageFlagBits
                state.shaders_[ShaderType_CS], //VkShaderModule
                ShaderEntryPoint, //entry point
                LGFX_NULL, //VkSpecializationInfo
            };

        }else{
            for(s32 i=0; i<ShaderType_CS; ++i){
                if(!state.shaders_[i].valid()){
                    continue;
                }
                shaderStageCreateInfos[numShaderStages++] =
                {
                    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, //structure type
                    LGFX_NULL, //next
                    0, //VkPipelineShaderStageCreateFlags
                    static_cast<VkShaderStageFlagBits>(ShaderStages[i]), //VkShaderStageFlagBits
                    state.shaders_[i], //VkShaderModule
                    ShaderEntryPoint, //entry point
                    LGFX_NULL, //VkSpecializationInfo
                };
            }
        }

        //Vertex input
        //--------------------------------------------------------------
        VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineVertexInputStateCreateFlags
            0, //vertex input binding description count
            LGFX_NULL, //VkVertexInputBindingDescription
            0, //vertex input attribute description count
            LGFX_NULL,
        };

        //Input assembly
        //--------------------------------------------------------------
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineInputAssemblyStateCreateFlags
        };
        
        //Viewport
        //--------------------------------------------------------------
        VkPipelineViewportStateCreateInfo viewportStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineViewportStateCreateFlags
            1, //viewport count
            reinterpret_cast<const VkViewport*>(&state.viewport_), //viewports
            1, //scissor count
            reinterpret_cast<const VkRect2D*>(&state.scissor_), //scissors
        };

        //Rasterization
        //--------------------------------------------------------------
        VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineRasterizationStateCreateFlags
            state.rasterization_.depthClamp_,
            state.rasterization_.rasterizerDiscard_,
            static_cast<VkPolygonMode>(state.rasterization_.polygonMode_),
            state.rasterization_.cullMode_,
            static_cast<VkFrontFace>(state.rasterization_.frontFace_),
            state.rasterization_.depthBias_,
            state.rasterization_.depthBiasConstantFactor_,
            state.rasterization_.depthBiasClamp_,
            state.rasterization_.depthBiasSlopeFactor_,
            state.rasterization_.lineWidth_,
        };

        //Multisample
        //--------------------------------------------------------------
        VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineMultisampleStateCreateFlags
            static_cast<VkSampleCountFlagBits>(state.multiSample_.sampleCount_),
            state.multiSample_.sampleShading_,
            state.multiSample_.minSampleShading_,
            state.multiSample_.sampleMask_,
            state.multiSample_.alphaToCoverage_,
            state.multiSample_.alphaToOne_,
        };

        //Color blend
        //--------------------------------------------------------------
        VkPipelineColorBlendAttachmentState colorBlendAttachment =
        {
            state.colorBlendAttachment_.blend_,
            static_cast<VkBlendFactor>(state.colorBlendAttachment_.srcColorBlendFactor_),
            static_cast<VkBlendFactor>(state.colorBlendAttachment_.dstColorBlendFactor_),
            static_cast<VkBlendOp>(state.colorBlendAttachment_.colorBlendOp_),
            static_cast<VkBlendFactor>(state.colorBlendAttachment_.srcAlphaBlendFactor_),
            static_cast<VkBlendFactor>(state.colorBlendAttachment_.dstAlphaBlendFactor_),
            static_cast<VkBlendOp>(state.colorBlendAttachment_.alphaBlendOp_),
            state.colorBlendAttachment_.colorWriteMask_,
        };

        VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo =
        {
            VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineColorBlendStateCreateFlags
            state.colorBlendState_.logicOpEnable_,
            static_cast<VkLogicOp>(state.colorBlendState_.logicOp_),
            1,
            &colorBlendAttachment,
            {state.colorBlendState_.blendCostant_[0], state.colorBlendState_.blendCostant_[1], state.colorBlendState_.blendCostant_[2], state.colorBlendState_.blendCostant_[3]},
        };

        VkGraphicsPipelineCreateInfo pipelineCreateInfo =
        {
            VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO, //structure type
            LGFX_NULL, //next
            0, //VkPipelineCreateFlags
            numShaderStages, //shader stage count
            shaderStageCreateInfos,
            &vertexInputStateCreateInfo,
            &inputAssemblyStateCreateInfo,
            LGFX_NULL, //VkPipelineTessellationStateCreateInfo
            &viewportStateCreateInfo,
            &rasterizationStateCreateInfo,
            &multisampleStateCreateInfo,
            LGFX_NULL, //VkPipelineDepthStencilStateCreateInfo
            &colorBlendStateCreateInfo,
            LGFX_NULL, //VkPipelineDynamicStateCreateInfo
            pipelineLayout,
            renderPass,
            0, //subbpass
            LGFX_NULL, //VkPipeline basePipeline
            -1, //basePipeline index
        };

        VkPipeline pipeline = LGFX_NULL;
        vkCreateGraphicsPipelines(device, LGFX_NULL, 1, &pipelineCreateInfo, allocator, &pipeline);
        vkDestroyPipelineLayout(device, pipelineLayout, allocator);
        return pipeline;
    }

    void Pipeline::destroy()
    {
        if(!handle_.valid()){
            return;
        }
        if(0!=handle_.dec()){
            return;
        }
        utils::destroy(handle_, vkDestroyShaderModule);
    }
}
