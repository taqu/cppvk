#ifndef INC_LGFX_VULKAN_H_
#define INC_LGFX_VULKAN_H_
/**
@file lgfx_vulkan.h
@author t-sakai
@date 2018/09/19 create

*/
#include "lgfx.h"

namespace lgfx
{
    typedef VkBool32 LGFX_BOOL;

#ifdef LGFX_VULKAN_IMPLEMENTATION
#   define LGFX_VK_EXPORTED_FUNCTION(name) PFN_ ## name name = LGFX_NULL;
#   include "VkFunctions.inc"
#else
#   define LGFX_VK_EXPORTED_FUNCTION(name) extern PFN_ ## name name = LGFX_NULL;
#   include "VkFunctions.inc"
#endif

    //--------------------------------------------------------------
    //---
    //--- Enumerations
    //---
    //--------------------------------------------------------------
    enum LGFX_RESULT : s32
    {
        LGFX_SUCCESS     = VK_SUCCESS,
        LGFX_NOT_READY   = VK_NOT_READY,
        LGFX_TIMEOUT     = VK_TIMEOUT,
        LGFX_EVENT_SET   = VK_EVENT_SET,
        LGFX_EVENT_RESET = VK_EVENT_RESET,
        LGFX_INCOMPLETE  = VK_INCOMPLETE,
        LGFX_ERROR_OUT_OF_HOST_MEMORY    = VK_ERROR_OUT_OF_HOST_MEMORY,
        LGFX_ERROR_OUT_OF_DEVICE_MEMORY  = VK_ERROR_OUT_OF_DEVICE_MEMORY,
        LGFX_ERROR_INITIALIZATION_FAILED = VK_ERROR_INITIALIZATION_FAILED,
        LGFX_ERROR_DEVICE_LOST           = VK_ERROR_DEVICE_LOST,
        LGFX_ERROR_MEMORY_MAP_FAILED     = VK_ERROR_MEMORY_MAP_FAILED,
        LGFX_ERROR_LAYER_NOT_PRESENT     = VK_ERROR_LAYER_NOT_PRESENT,
        LGFX_ERROR_EXTENSION_NOT_PRESENT = VK_ERROR_EXTENSION_NOT_PRESENT,
        LGFX_ERROR_FEATURE_NOT_PRESENT   = VK_ERROR_FEATURE_NOT_PRESENT,
        LGFX_ERROR_INCOMPATIBLE_DRIVER   = VK_ERROR_INCOMPATIBLE_DRIVER,
        LGFX_ERROR_TOO_MANY_OBJECTS      = VK_ERROR_TOO_MANY_OBJECTS,
        LGFX_ERROR_FORMAT_NOT_SUPPORTED  = VK_ERROR_FORMAT_NOT_SUPPORTED,
        LGFX_ERROR_FRAGMENTED_POOL       = VK_ERROR_FRAGMENTED_POOL,
        LGFX_ERROR_SURFACE_LOST_KHR      = VK_ERROR_SURFACE_LOST_KHR,
        LGFX_ERROR_NATIVE_WINDOW_IN_USE_KHR = VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,
        LGFX_SUBOPTIMAL_KHR              = VK_SUBOPTIMAL_KHR,
        LGFX_ERROR_OUT_OF_DATE_KHR       = VK_ERROR_OUT_OF_DATE_KHR,
        LGFX_ERROR_INCOMPATIBLE_DISPLAY_KHR = VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,
        LGFX_ERROR_VALIDATION_FAILED_EXT    = VK_ERROR_VALIDATION_FAILED_EXT,
        LGFX_ERROR_INVALID_SHADER_NV        = VK_ERROR_INVALID_SHADER_NV,
        LGFX_ERROR_OUT_OF_POOL_MEMORY_KHR   = VK_ERROR_OUT_OF_POOL_MEMORY_KHR,
        LGFX_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR,
    };

    #define LGFX_VK_TO_RESULT(result) static_cast<LGFX_RESULT>(result)

    enum PrimitiveTopology : s32
    {
        PrimitiveTopology_PointList     = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
        PrimitiveTopology_LineList      = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
        PrimitiveTopology_LineStrip     = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
        PrimitiveTopology_TriangleList  = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        PrimitiveTopology_TriangleStrip = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
        PrimitiveTopology_TriangleFan   = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
        PrimitiveTopology_PatchList     = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
    };

    enum PolygonMode : s32
    {
        PolygonMode_Fill  = VK_POLYGON_MODE_FILL,
        PolygonMode_Line  = VK_POLYGON_MODE_FILL,
        PolygonMode_Point = VK_POLYGON_MODE_POINT,
    };

    enum CullMode : s32
    {
        CullMode_None  = VK_CULL_MODE_NONE,
        CullMode_Front = VK_CULL_MODE_FRONT_BIT,
        CullMode_Back  = VK_CULL_MODE_BACK_BIT,
        CullMode_Both  = VK_CULL_MODE_FRONT_AND_BACK,
    };

    enum FrontFace : s32
    {
        FrontFace_CounterClockwise  = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        FrontFace_Clockwise         = VK_FRONT_FACE_CLOCKWISE,
    };

    enum SampleCount : s32
    {
        SampleCount_1 = VK_SAMPLE_COUNT_1_BIT,
        SampleCount_2 = VK_SAMPLE_COUNT_2_BIT,
        SampleCount_4 = VK_SAMPLE_COUNT_4_BIT,
        SampleCount_8 = VK_SAMPLE_COUNT_8_BIT,
        SampleCount_16 = VK_SAMPLE_COUNT_16_BIT,
        SampleCount_32 = VK_SAMPLE_COUNT_32_BIT,
        SampleCount_64 = VK_SAMPLE_COUNT_64_BIT,
    };

    enum BlendFactor : s32
    {
        BlendFactor_Zero = VK_BLEND_FACTOR_ZERO,
        BlendFactor_One = VK_BLEND_FACTOR_ONE,
        BlendFactor_SrcColor = VK_BLEND_FACTOR_SRC_COLOR,
        BlendFactor_OneMinusSrcColor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
        BlendFactor_DstColor = VK_BLEND_FACTOR_DST_COLOR,
        BlendFactor_OneMinusDstColor = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
        BlendFactor_SrcAlpha = VK_BLEND_FACTOR_SRC_ALPHA,
        BlendFactor_OneMinusSrcAlpha = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        BlendFactor_DstAlpha = VK_BLEND_FACTOR_DST_ALPHA,
        BlendFactor_OneMinusDstAlpha = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
        BlendFactor_ConstantColor = VK_BLEND_FACTOR_CONSTANT_COLOR,
        BlendFactor_OneMinusConstantColor = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
        BlendFactor_ConstantAlpha = VK_BLEND_FACTOR_CONSTANT_ALPHA,
        BlendFactor_OneMinusConstantAlpha = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
        BlendFactor_SrcAlphaSaturate = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
        BlendFactor_Src1Color = VK_BLEND_FACTOR_SRC1_COLOR,
        BlendFactor_OneMinusSrc1Color = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
        BlendFactor_Src1Alpha = VK_BLEND_FACTOR_SRC1_ALPHA,
        BlendFactor_OneMinusSrc1Alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
    };

    enum BlendOp : s32
    {
        BlendOp_Add = VK_BLEND_OP_ADD,
        BlendOp_Sub = VK_BLEND_OP_SUBTRACT,
        BlendOp_ReverseSub = VK_BLEND_OP_REVERSE_SUBTRACT,
        BlendOp_Min = VK_BLEND_OP_MIN,
        BlendOp_Max = VK_BLEND_OP_MAX,
    };

    enum LogicOp : s32
    {
        LogicOp_Clear = VK_LOGIC_OP_CLEAR,
        LogicOp_And = VK_LOGIC_OP_AND,
        LogicOp_AndReverse = VK_LOGIC_OP_AND_REVERSE,
        LogicOp_Copy = VK_LOGIC_OP_COPY,
        LogicOp_AndInverted = VK_LOGIC_OP_AND_INVERTED,
        LogicOp_Nop = VK_LOGIC_OP_NO_OP,
        LogicOp_Xor = VK_LOGIC_OP_XOR,
        LogicOp_Or = VK_LOGIC_OP_OR,
        LogicOp_Nor = VK_LOGIC_OP_NOR,
        LogicOp_Eq = VK_LOGIC_OP_EQUIVALENT,
        LogicOp_Invert = VK_LOGIC_OP_INVERT,
        LogicOp_Reverse = VK_LOGIC_OP_OR_REVERSE,
        LogicOp_CopyInverted = VK_LOGIC_OP_COPY_INVERTED,
        LogicOp_OrInverted = VK_LOGIC_OP_OR_INVERTED,
        LogicOp_Nand = VK_LOGIC_OP_NAND,
        LogicOp_Set = VK_LOGIC_OP_SET,
    };

    enum ColorComponent : s32
    {
        ColorComponent_R = VK_COLOR_COMPONENT_R_BIT,
        ColorComponent_G = VK_COLOR_COMPONENT_G_BIT,
        ColorComponent_B = VK_COLOR_COMPONENT_B_BIT,
        ColorComponent_A = VK_COLOR_COMPONENT_A_BIT,
    };

    enum ShaderType : s32
    {
        ShaderType_HS = 0,
        ShaderType_DS,
        ShaderType_VS,
        ShaderType_GS,
        ShaderType_PS,
        ShaderType_CS,
        ShaderType_Num,
    };

    enum ShaderStage : s32
    {
        ShaderStage_HS = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
        ShaderStage_DS = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
        ShaderStage_VS = VK_SHADER_STAGE_VERTEX_BIT,
        ShaderStage_GS = VK_SHADER_STAGE_GEOMETRY_BIT,
        ShaderStage_PS = VK_SHADER_STAGE_FRAGMENT_BIT,
        ShaderStage_CS = VK_SHADER_STAGE_COMPUTE_BIT,
    };

    extern const Char* ShaderEntryPoint;

    //--------------------------------------------------------------
    //---
    //---
    //---
    //--------------------------------------------------------------
    struct Rasterization
    {
        LGFX_BOOL depthClamp_;
        LGFX_BOOL rasterizerDiscard_;
        PolygonMode polygonMode_;
        CullMode cullMode_;
        FrontFace frontFace_;
        LGFX_BOOL depthBias_;
        f32 depthBiasConstantFactor_;
        f32 depthBiasClamp_;
        f32 depthBiasSlopeFactor_;
        f32 lineWidth_;
    };

    struct Multisample
    {
        SampleCount sampleCount_;
        LGFX_BOOL sampleShading_;
        f32 minSampleShading_;
        const u32* sampleMask_;
        LGFX_BOOL alphaToCoverage_;
        LGFX_BOOL alphaToOne_;
    };

    struct ColorBlendAttachment
    {
        LGFX_BOOL blend_;
        BlendFactor srcColorBlendFactor_;
        BlendFactor dstColorBlendFactor_;
        BlendOp colorBlendOp_;
        BlendFactor srcAlphaBlendFactor_;
        BlendFactor dstAlphaBlendFactor_;
        BlendOp alphaBlendOp_;
        u32 colorWriteMask_;
    };

    struct ColorBlendState
    {
        LGFX_BOOL logicOpEnable_;
        LogicOp logicOp_;
        f32 blendCostant_[4];
    };

#define LGFX_SETNULL(ARRAY, SIZE) \
    for(s32 i=0; i<(SIZE); ++i){\
        (ARRAY)[i] = LGFX_NULL;\
    }\

#define LGFX_DEVICE_DESTROY(ARRAY, SIZE, FUNC, DEVICE, ALLOCATOR) \
    for(s32 i=0; i<(SIZE); ++i){\
        if(LGFX_NULL == (ARRAY)[i]){\
            continue;\
        }\
        FUNC((DEVICE), (ARRAY)[i], ALLOCATOR);\
        (ARRAY)[i] = LGFX_NULL;\
    }\

#define LGFX_SWAP(ARRAY0, ARRAY1, SIZE) \
    for(s32 i=0; i<(SIZE); ++i){\
        lgfx::swap((ARRAY0)[i], (ARRAY1)[i]);\
    }\

    class Instance;
    class Device;
    class Swapchain;
    class CommandBuffer;

    //--------------------------------------------------------------
    namespace utils
    {
        template<class FuncT>
        void destroy(Handle& handle, FuncT destroyFunc)
        {
            System& system = System::instance();
            destroyFunc(system.getDevice(handle.device()), handle, system.getAllocator());
            Handle::release(handle);
        }
    }

    //--------------------------------------------------------------
    //---
    //--- Build functions
    //---
    //--------------------------------------------------------------
    typedef bool (*PFN_CheckSurfaceFormats)(
        VkSurfaceFormatKHR& dst,
        u32 size,
        const VkSurfaceFormatKHR* formats,
        bool supportHDR);

    typedef bool (*PFN_CheckSurfaceCapabilities)(
        VkImageUsageFlags& imageUsageFlags,
        VkSurfaceTransformFlagBitsKHR& preTransform,
        VkCompositeAlphaFlagBitsKHR& compsiteAlpha,
        const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

    typedef VkPresentModeKHR (*PFN_GetPresentMode)(
        u32 size,
        const VkPresentModeKHR* presentModes,
        VkPresentModeKHR request);


    typedef bool (*PFN_CheckInstanceExtension)(const VkExtensionProperties& properties);

    typedef void (*PFN_CheckQueueFamilies)(
        u32 queueFamilyIndices[QueueType_Max],
        u32 numQueueFamilies,
        VkQueueFamilyProperties* queueFamilyProperties,
        const bool* queueFamilyPresentationSupports,
        const bool* requests);

    typedef bool (*PFN_CheckDeviceExtension)(const VkExtensionProperties& properties);

    typedef bool (*PFN_CheckDeviceFeatures)(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);

    //--------------------------------------------------------------
    //---
    //--- SwapchainBuilderVulkan
    //---
    //--------------------------------------------------------------
    class SwapchainBuilderVulkan
    {
    public:
        static bool checkSurfaceFormats(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats, bool supportHDR);

        static bool checkSurfaceCapabilities(
            VkImageUsageFlags& imageUsageFlags,
            VkSurfaceTransformFlagBitsKHR& preTransform,
            VkCompositeAlphaFlagBitsKHR& compsiteAlpha,
            const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

        static VkPresentModeKHR getPresentMode(u32 size, const VkPresentModeKHR* presentModes, VkPresentModeKHR request);

        static bool defaultSupportedColorSpaceSDR(VkColorSpaceKHR colorSpace);
        static bool defaultSupportedColorSpaceHDR(VkColorSpaceKHR colorSpace);

        static bool defaultCheckSurfaceFormatSDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);
        static bool defaultCheckSurfaceFormatHDR(VkSurfaceFormatKHR& dst, u32 size, const VkSurfaceFormatKHR* formats);

        Instance* instance_;
        SwapchainCreateInfo swapchainCreateInfo_;

        PFN_CheckSurfaceFormats checkSurfaceFormats_;
        PFN_CheckSurfaceCapabilities checkSurfaceCapabilities_;
        PFN_GetPresentMode getPresentMode_;
    };

    //--------------------------------------------------------------
    //---
    //--- BuilderVulkan
    //---
    //--------------------------------------------------------------
    class BuilderVulkan : public Builder
    {
    public:
        virtual bool build(System& system);
        virtual bool buildInstance(System& system);
        virtual bool buildDevice(System& system);

        static bool checkInstanceExtension(const VkExtensionProperties& properties);

        static void checkQueueFamilies(
            u32 queueFamilyIndices[QueueType_Max],
            u32 numQueueFamilies,
            VkQueueFamilyProperties* queueFamilyProperties,
            const bool* queueFamilyPresentationSupports,
            const bool* requests);

        static bool checkDeviceExtension(const VkExtensionProperties& properties);

        static bool checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);

        BuilderVulkan()
            :checkInstanceExtension_(checkInstanceExtension)
            ,checkQueueFamilies_(checkQueueFamilies)
            ,checkDeviceExtension_(checkDeviceExtension)
            ,checkDeviceFeatures_(checkDeviceFeatures)

            ,checkSurfaceFormats_(SwapchainBuilderVulkan::checkSurfaceFormats)
            ,checkSurfaceCapabilities_(SwapchainBuilderVulkan::checkSurfaceCapabilities)
            ,getPresentMode_(SwapchainBuilderVulkan::getPresentMode)
        {}

        u32 getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName);

        SwapchainBuilderVulkan createSwapchainBuilder(Instance& instance);

        PFN_CheckInstanceExtension checkInstanceExtension_;
        PFN_CheckQueueFamilies checkQueueFamilies_;
        PFN_CheckDeviceExtension checkDeviceExtension_;
        PFN_CheckDeviceFeatures checkDeviceFeatures_;

        PFN_CheckSurfaceFormats checkSurfaceFormats_;
        PFN_CheckSurfaceCapabilities checkSurfaceCapabilities_;
        PFN_GetPresentMode getPresentMode_;
    };

    //--------------------------------------------------------------
    //---
    //--- Swapchain
    //---
    //--------------------------------------------------------------
    /**
    */
    class Swapchain
    {
    public:
        static const s32 MaxSwapchainImages = LGFX_MAX_SWAPCHAINMAX;

        static LGFX_RESULT create(Swapchain& swapchain, Device& device, SwapchainBuilderVulkan& builder);

        Swapchain();
        ~Swapchain();

        void destroy();

        inline bool valid() const;
        operator const VkSwapchainKHR() const;
        operator VkSwapchainKHR();
        void swap(Swapchain& rhs);

        inline u32 width() const;
        inline u32 height() const;
        inline VkFormat getFormat() const;
        inline s32 getNumImages() const;
        inline VkImage getImage(s32 index);
    private:
        Swapchain(const Swapchain&) = delete;
        Swapchain(Swapchain&&) = delete;
        Swapchain& operator=(const Swapchain&) = delete;
        Swapchain& operator=(Swapchain&&) = delete;

        Handle swapchain_;
        u32 width_;
        u32 height_;
        VkFormat format_;
        u32 numImages_;
        VkImage images_[MaxSwapchainImages];
    };

    inline bool Swapchain::valid() const
    {
        return swapchain_.valid();
    }

    inline u32 Swapchain::width() const
    {
        return width_;
    }

    inline u32 Swapchain::height() const
    {
        return height_;
    }

    inline VkFormat Swapchain::getFormat() const
    {
        return format_;
    }

    inline s32 Swapchain::getNumImages() const
    {
        return numImages_;
    }

    inline VkImage Swapchain::getImage(s32 index)
    {
        LGFX_ASSERT(0<=numImages_ && numImages_<MaxSwapchainImages);
        return images_[index];
    }

#if 0
    //--------------------------------------------------------------
    //---
    //--- CommandBuffer
    //---
    //--------------------------------------------------------------
    /**
    */
    class CommandBuffer
    {
    public:
        CommandBuffer();
        explicit CommandBuffer(VkCommandBuffer commandBuffer);
        ~CommandBuffer();

        inline bool valid() const;
        inline operator const VkCommandBuffer() const;
        inline operator VkCommandBuffer();

        void swap(CommandBuffer& rhs);

        inline LGFX_RESULT begin(const VkCommandBufferBeginInfo& beginInfo);
        inline LGFX_RESULT end();
        inline LGFX_RESULT reset(VkCommandBufferResetFlags flags);

        /**
        */
        inline void pipelineBarrier(
            VkPipelineStageFlags srcStageMask,
            VkPipelineStageFlags dstStageMask,
            VkDependencyFlags dependencyFlags,
            u32 numMemoryBarriers, const VkMemoryBarrier* memoryBarriers,
            u32 numBufferBarriers, const VkBufferMemoryBarrier* bufferBarriers,
            u32 numImageBarriers, const VkImageMemoryBarrier* imageBarriers);

        /**
        */
        inline void fillBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, u32 data);
        /**
        */
        inline void updateBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const u32* data);
        /**
        */
        inline void clearColorImage(VkImage image, VkImageLayout layout, const VkClearColorValue* color, u32 numRanges, const VkImageSubresourceRange* ranges);
        /**
        */
        inline void clearDepthStencilImage(VkImage image, VkImageLayout layout, const VkClearDepthStencilValue* depthStencil, u32 numRanges, const VkImageSubresourceRange* ranges);

        /**
        */
        inline void copy(VkBuffer src, VkBuffer dst, u32 numRegions, const VkBufferCopy* regions);
        /**
        */
        inline void copy(VkBuffer src, VkImage dst, VkImageLayout layout, u32 numRegions, const VkBufferImageCopy* regions);
        /**
        */
        inline void copy(VkImage src, VkImageLayout layout, VkBuffer dst, u32 numRegions, const VkBufferImageCopy* regions);
        /**
        */
        inline void copy(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageCopy* regions);

        /**
        */
        inline void blit(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageBlit* regions, VkFilter filter);

    private:
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer(CommandBuffer&&) = delete;
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        CommandBuffer& operator=(CommandBuffer&&) = delete;

        VkCommandBuffer commandBuffer_;
    };

    inline bool CommandBuffer::valid() const
    {
        return LGFX_NULL != commandBuffer_;
    }

    inline CommandBuffer::operator const VkCommandBuffer() const
    {
        return commandBuffer_;
    }

    inline CommandBuffer::operator VkCommandBuffer()
    {
        return commandBuffer_;
    }

    inline LGFX_RESULT CommandBuffer::begin(const VkCommandBufferBeginInfo& beginInfo)
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT(vkBeginCommandBuffer(commandBuffer_, &beginInfo));
    }

    inline LGFX_RESULT CommandBuffer::end()
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT(vkEndCommandBuffer(commandBuffer_));
    }

    inline LGFX_RESULT CommandBuffer::reset(VkCommandBufferResetFlags flags)
    {
        LGFX_ASSERT(valid());
        return LGFX_VK_TO_RESULT(vkResetCommandBuffer(commandBuffer_, flags));
    }

    inline void CommandBuffer::pipelineBarrier(
        VkPipelineStageFlags srcStageMask,
        VkPipelineStageFlags dstStageMask,
        VkDependencyFlags dependencyFlags,
        u32 numMemoryBarriers, const VkMemoryBarrier* memoryBarriers,
        u32 numBufferBarriers, const VkBufferMemoryBarrier* bufferBarriers,
        u32 numImageBarriers, const VkImageMemoryBarrier* imageBarriers)
    {
        LGFX_ASSERT(valid());
        vkCmdPipelineBarrier(commandBuffer_, srcStageMask, dstStageMask, dependencyFlags, numMemoryBarriers, memoryBarriers, numBufferBarriers, bufferBarriers, numImageBarriers, imageBarriers);
    }

    inline void CommandBuffer::fillBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, u32 data)
    {
        LGFX_ASSERT(valid());
        vkCmdFillBuffer(commandBuffer_, buffer, offset, size, data);
    }

    inline void CommandBuffer::updateBuffer(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const u32* data)
    {
        LGFX_ASSERT(valid());
        vkCmdUpdateBuffer(commandBuffer_, buffer, offset, size, data);
    }

    inline void CommandBuffer::clearColorImage(VkImage image, VkImageLayout layout, const VkClearColorValue* color, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        LGFX_ASSERT(valid());
        vkCmdClearColorImage(commandBuffer_, image, layout, color, numRanges, ranges);
    }

    inline void CommandBuffer::clearDepthStencilImage(VkImage image, VkImageLayout layout, const VkClearDepthStencilValue* depthStencil, u32 numRanges, const VkImageSubresourceRange* ranges)
    {
        LGFX_ASSERT(valid());
        vkCmdClearDepthStencilImage(commandBuffer_, image, layout, depthStencil, numRanges, ranges);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkBuffer dst, u32 numRegions, const VkBufferCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyBuffer(commandBuffer_, src, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkBuffer src, VkImage dst, VkImageLayout layout, u32 numRegions, const VkBufferImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyBufferToImage(commandBuffer_, src, dst, layout, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout layout, VkBuffer dst, u32 numRegions, const VkBufferImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyImageToBuffer(commandBuffer_, src, layout, dst, numRegions, regions);
    }

    inline void CommandBuffer::copy(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageCopy* regions)
    {
        LGFX_ASSERT(valid());
        vkCmdCopyImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions);
    }

    /**
    */
    inline void CommandBuffer::blit(VkImage src, VkImageLayout srcLayout, VkImage dst, VkImageLayout dstLayout, u32 numRegions, const VkImageBlit* regions, VkFilter filter)
    {
        LGFX_ASSERT(valid());
        vkCmdBlitImage(commandBuffer_, src, srcLayout, dst, dstLayout, numRegions, regions, filter);
    }
#endif

#if 0
    //--------------------------------------------------------------
    //---
    //--- CommandBuffer
    //---
    //--------------------------------------------------------------
    CommandBuffer::CommandBuffer()
        :commandBuffer_(LGFX_NULL)
    {}

    CommandBuffer::CommandBuffer(VkCommandBuffer commandBuffer)
        :commandBuffer_(commandBuffer)
    {}

    CommandBuffer::~CommandBuffer()
    {}

    void CommandBuffer::swap(CommandBuffer& rhs)
    {
        lgfx::swap(commandBuffer_, rhs.commandBuffer_);
    }
#endif


    //--------------------------------------------------------------
    //---
    //--- Shader
    //---
    //--------------------------------------------------------------
    class Shader
    {
    public:
        Shader();
        Shader(Shader& rhs);
        Shader(Shader&& rhs);
        Shader(s32 device, VkShaderModule shader);
        ~Shader();

        Shader& operator=(Shader& rhs);
        Shader& operator=(Shader&& rhs);

        bool valid() const;
        operator const VkShaderModule() const;
        operator VkShaderModule();
        void swap(Shader& rhs);
    private:
        void destroy();

        Handle handle_;
    };

    //--------------------------------------------------------------
    //---
    //--- PipelineLayout
    //---
    //--------------------------------------------------------------
    class PipelineLayout
    {
    public:
        PipelineLayout();
        PipelineLayout(PipelineLayout& rhs);
        PipelineLayout(PipelineLayout&& rhs);
        PipelineLayout(s32 device, VkPipelineLayout pipelineLayout);
        ~PipelineLayout();

        PipelineLayout& operator=(PipelineLayout& rhs);
        PipelineLayout& operator=(PipelineLayout&& rhs);

        bool valid() const;
        operator const VkPipelineLayout() const;
        operator VkPipelineLayout();
        void swap(PipelineLayout& rhs);
    private:
        void destroy();

        Handle handle_;
    };

    //--------------------------------------------------------------
    //---
    //--- PipelineState
    //---
    //--------------------------------------------------------------
    class PipelineState
    {
    public:
        static const ShaderStage ShaderStages[ShaderType_Num];

        PipelineState();

        void setShader(ShaderStage stage, Shader& shader);

        Shader shaders_[ShaderType_Num];
        Viewport viewport_;
        RectS32 scissor_;
        Rasterization rasterization_;
        Multisample multiSample_;
        ColorBlendAttachment colorBlendAttachment_;
        ColorBlendState colorBlendState_;
    };

    //--------------------------------------------------------------
    //---
    //--- Pipeline
    //---
    //--------------------------------------------------------------
    class Pipeline
    {
    public:
        static const ShaderStage ShaderStages[ShaderType_Num];
        static VkPipeline create(VkDevice device, VkRenderPass renderPass, const PipelineState& state, const VkAllocationCallbacks* allocator);

        Pipeline();
        Pipeline(Pipeline& rhs);
        Pipeline(Pipeline&& rhs);
        Pipeline(s32 device, VkPipeline pipeline);
        ~Pipeline();

        Pipeline& operator=(Pipeline& rhs);
        Pipeline& operator=(Pipeline&& rhs);

        bool valid() const;
        operator const VkPipeline() const;
        operator VkPipeline();
        void swap(Pipeline& rhs);

    private:
        void destroy();

        Handle handle_;
    };

    //--------------------------------------------------------------
    //---
    //--- Lib
    //---
    //--------------------------------------------------------------
    class Lib
    {
    public:
        Lib();
        ~Lib();

        inline bool valid() const;

        LGFX_RESULT initialize();
        void terminate();

        void swap(Lib& rhs);
    private:
        Lib(const Lib&) = delete;
        Lib(Lib&&) = delete;
        Lib& operator=(const Lib&) = delete;
        Lib& operator=(Lib&&) = delete;

        LGFX_DLHANDLE handle_;
    };

    inline bool Lib::valid() const
    {
        return LGFX_NULL != handle_;
    }

    //--------------------------------------------------------------
    //---
    //--- PhysicalDevice
    //---
    //--------------------------------------------------------------
    /**
    Pysical device wraps VkPhysicalDevice.
    */
    class PhysicalDevice
    {
    public:
        inline PhysicalDevice();
        explicit inline PhysicalDevice(VkPhysicalDevice device);

        inline bool valid() const;
        inline operator const VkPhysicalDevice() const;
        inline operator VkPhysicalDevice();

        inline void swap(PhysicalDevice& rhs);

        /**
        @brief
        */
        void getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& features);

        /**
        @brief
        */
        void getPhysicalDeviceProperties(VkPhysicalDeviceProperties& properties);

        /**
        @brief
        */
        void getPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties& formatProperties);

        /**
        @brief
        @return
        */
        LGFX_RESULT enumerateDeviceLayerProperties(u32* propertyCount, VkLayerProperties* properties);

        /**
        @brief
        @return
        */
        LGFX_RESULT getPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties& imageFormatProperties);

        /**
        @brief
        */
        void getPhysicalDeviceSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, u32* propertyCount, VkSparseImageFormatProperties* properties);

        /**
        @brief
        */
        void getPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProperties);

        /**
        @brief
        */
        u32 enumerateDeviceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName);

    private:
        VkPhysicalDevice device_;
    };

    inline PhysicalDevice::PhysicalDevice()
        :device_(LGFX_NULL)
    {}

    inline PhysicalDevice::PhysicalDevice(VkPhysicalDevice device)
        :device_(device)
    {}

    inline bool PhysicalDevice::valid() const
    {
        return LGFX_NULL != device_;
    }

    inline PhysicalDevice::operator const VkPhysicalDevice() const
    {
        return device_;
    }

    inline PhysicalDevice::operator VkPhysicalDevice()
    {
        return device_;
    }

    inline void PhysicalDevice::swap(PhysicalDevice& rhs)
    {
        lgfx::swap(device_, rhs.device_);
    }

    

    //--------------------------------------------------------------
    //---
    //--- Queue
    //---
    //--------------------------------------------------------------
    struct Queue
    {
        u32 familyIndex_;
        u32 index_;
        VkQueue handle_;
    };

    //--------------------------------------------------------------
    //---
    //--- Device
    //---
    //--------------------------------------------------------------
    /**
    */
    class Device
    {
    public:
        static LGFX_RESULT create(
            Device& device,
            PhysicalDevice& physicalDevice,
            const VkDeviceCreateInfo& deviceCreateInfo,
            const u32 queueFamilityIndices[QueueType_Max],
            SwapchainBuilderVulkan& swapchainBuilder);

        Device();
        ~Device();

        void destroy();

        inline s32 getID() const;
        void setID(s32 id);

        inline bool valid() const;
        inline operator const VkDevice() const;
        inline operator VkDevice();

        inline explicit operator VkPhysicalDevice();

        LGFX_RESULT waitIdle();
        bool onWindowSizeChanged();
        bool present();

        bool addRenderPass(s32 index);

        bool createShader(Shader& shader, u64 size, const u8* binary);
        bool createPipeline(Pipeline& pipeline, const PipelineState& state);

#define LGFX_VK_EXT_DEVICE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

    private:
        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) = delete;

        void initialize();
        VkResult createSemaphores();
        VkResult createCommandBuffers();

        void destroySemaphores();
        void destroyCommandBuffers();

        VkResult recordClearCommands();

        s32 id_;
        VkDevice device_;
        PhysicalDevice physicalDevice_;
        SwapchainBuilderVulkan swapchainBuilder_;
        Swapchain swapchain_;

        Queue queues_[QueueType_Max];
        VkSemaphore semaphoreImageAvailable_;
        VkSemaphore semaphoreRenderingFinished_;

        Array<VkCommandBuffer> presentCommandBuffers_;
        VkCommandPool presentCommandPool_;

        VkClearColorValue clearColor_;

        VkRenderPass renderPasses_[LGFX_MAX_RENDERPASSES];
        VkImageView imageViews_[Swapchain::MaxSwapchainImages];
        VkFramebuffer frameBuffers_[Swapchain::MaxSwapchainImages];
    };

    inline s32 Device::getID() const
    {
        return id_;
    }

    inline bool Device::valid() const
    {
        return LGFX_NULL != device_;
    }

    inline Device::operator const VkDevice() const
    {
        return device_;
    }

    inline Device::operator VkDevice()
    {
        return device_;
    }

    inline Device::operator VkPhysicalDevice()
    {
        return (VkPhysicalDevice)physicalDevice_;
    }

    //--------------------------------------------------------------
    //---
    //--- Instance
    //---
    //--------------------------------------------------------------
    class Instance
    {
    public:
        static LGFX_RESULT create(
            Instance& instance,
            const VkInstanceCreateInfo& instanceCreateInfo,
            const SurfaceCreateInfo& surfaceCreateInfo);

        static void destroy(Instance& instance);

        Instance();
        ~Instance();

        inline bool valid() const;
        inline operator const VkInstance() const;
        inline operator VkInstance();

        void swap(Instance& rhs);

        u32 enumeratePhysicalDevices(u32 maxDevices, PhysicalDevice* devices) const;
        inline VkSurfaceKHR getPresentationSurface();

#define LGFX_VK_EXT_INSTANCE_FUNCTION(name) PFN_ ## name name;
#include "VkFunctions.inc"

        /**
        @brief
        */
        bool getPhysicalDevicePresentationSurfaceSupport(PhysicalDevice physicalDevice, u32 queueFamilyIndex);

    private:
        Instance(const Instance&) = delete;
        Instance(Instance&&) = delete;
        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) = delete;

        void initialize();
        VkResult createPresentationSurface(const SurfaceCreateInfo& createInfo);

        VkInstance instance_;
        VkSurfaceKHR presentationSurface_;
    };

    inline bool Instance::valid() const
    {
        return LGFX_NULL != instance_;
    }

    inline Instance::operator const VkInstance() const
    {
        return instance_;
    }

    inline Instance::operator VkInstance()
    {
        return instance_;
    }

    inline VkSurfaceKHR Instance::getPresentationSurface()
    {
        return presentationSurface_;
    }

    //--------------------------------------------------------------
    //---
    //--- System
    //---
    //--------------------------------------------------------------
    /**
    */
    class System
    {
    public:
        static bool initialize(BuilderVulkan& builder, const VkAllocationCallbacks* allocator);
        static void terminate();
        static inline System& instance();

        inline const VkAllocationCallbacks* getAllocator();
        inline Instance& getInstance();
        inline Device& getDevice(s32 index);

    private:
        System(const System&) = delete;
        System(System&&) = delete;
        System& operator=(const System&) = delete;
        System& operator=(System&&) = delete;

        friend class BuilderVulkan;
        friend class Device;

        System();
        ~System();

        static System system_;

        u32 getInstanceExtensionProperties(u32 maxExtensions, VkExtensionProperties* extensionProperties, const Char* layerName);

        Lib lib_;
        Instance instance_;
        Device devices_[LGFX_MAX_PHYSICAL_DEVICES];

        const VkAllocationCallbacks* allocator_;
    };

    inline System& System::instance()
    {
        return system_;
    }

    inline const VkAllocationCallbacks* System::getAllocator()
    {
        return system_.allocator_;
    }

    inline Instance& System::getInstance()
    {
        return instance_;
    }

    inline Device& System::getDevice(s32 index)
    {
        LGFX_ASSERT(0<=index && index<LGFX_MAX_PHYSICAL_DEVICES);
        LGFX_ASSERT(LGFX_NULL != devices_[index]);
        return devices_[index];
    }
}
#endif //INC_LGFX_VULKAN_H_
