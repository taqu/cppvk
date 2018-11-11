#include <stdio.h>
#include "lgfx.h"
#include "Application.h"
#include "Window.h"
#include "Core.h"

#ifdef LGFX_VULKAN
void printPhysicalDevice(lgfx::PhysicalDevice device);

int main(int /*argc*/, char** /*argv*/)
{
    //---------------------------------------------------------------------
    lgfx::Window window;
    {
        HINSTANCE hInstance = LGFX_NULL;
        if(FALSE == GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &hInstance)){
            return EXIT_SUCCESS;
        }
        lgfx::Window::InitParam initParam = {
            hInstance,
            400,
            300,
            0,0,
            LGFX_NULL,
            "Tutorial",
            true,
        };
        if(!window.create(initParam)){
            return EXIT_SUCCESS;
        }
    }

    //---------------------------------------------------------------------
    {
        lgfx::BuilderVulkan builder;

        builder.instanceCreateInfo_ = {
            "Tutorial Vulkan", //application name
            VK_MAKE_VERSION(1,0,0), //application version
            "Tutorial Engine", //engine name
            VK_MAKE_VERSION(1,0,0), //engine version
            VK_API_VERSION_1_0, //api version

            0, //enabled layer count
            {LGFX_NULL}, //enabled layer names
            LGFX_NULL,
        };
        builder.deviceCreateInfo_ = {
            0,
            {true, true, true, false, false},
            0,
            {LGFX_NULL},
            LGFX_NULL,
        };

        builder.surfaceCreateInfo_ = {
            0,
            window.getInstance(),
            window.getHandle(),
        };

        lgfx::Window::Vector2 viewSize = window.getViewSize();
        builder.swapchainCreateInfo_ = {
            false,
            2,
            lgfx::PresentMode_MailBox,
            static_cast<lgfx::u32>(viewSize.x_),
            static_cast<lgfx::u32>(viewSize.y_),
        };

        if(!lgfx::System::initialize(builder, LGFX_NULL)){
            fprintf(stderr, "Fail to initialize\n");
            return EXIT_SUCCESS;
        }
        lgfx::System& system = lgfx::System::instance();

        // Enumerate Physical Devices
        //---------------------------------------------------------------------
        lgfx::PhysicalDevice physicalDevices[LGFX_MAX_PHYSICAL_DEVICES];
        lgfx::u32 numPycinalDevices = system.getInstance().enumeratePhysicalDevices(LGFX_MAX_PHYSICAL_DEVICES, physicalDevices);
        for(lgfx::u32 i=0; i<numPycinalDevices; ++i){
            printPhysicalDevice(physicalDevices[i]);
        }
    }
    lgfx::System::terminate();
    window.destroy();
    return EXIT_SUCCESS;
}

void printPhysicalDevice(lgfx::PhysicalDevice device)
{
    //--- VkPhysicalDeviceProperties
    //-----------------------------------------------------------------------
    {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        device.getPhysicalDeviceProperties(physicalDeviceProperties);

        //-------------------------------------------------
        const char* deviceType = "";
        switch(physicalDeviceProperties.deviceType){
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            deviceType = "other";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            deviceType = "integrated GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            deviceType = "discrete GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            deviceType = "virtual GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            deviceType = "CPU";
            break;
        }
        printf("device [%s]\n", physicalDeviceProperties.deviceName);
        printf("  vender id %d\n", physicalDeviceProperties.vendorID);
        printf("  api version %d\n", physicalDeviceProperties.apiVersion);
        printf("  driver version %d\n", physicalDeviceProperties.driverVersion);
        printf("  device type %s\n", deviceType);
        printf("  pipeline cache UUID ");
        for(lgfx::u32 j = 0; j<VK_UUID_SIZE; ++j){
            printf("%d", physicalDeviceProperties.pipelineCacheUUID[j]);
        }
        printf("\n");

        //-------------------------------------------------
        printf("  limits:\n");
        printf("    maxImageDimension1D %d\n", physicalDeviceProperties.limits.maxImageDimension1D);
        printf("    maxImageDimension2D %d\n", physicalDeviceProperties.limits.maxImageDimension2D);
        printf("    maxImageDimension3D %d\n", physicalDeviceProperties.limits.maxImageDimension3D);
        printf("    maxImageDimensionCube %d\n", physicalDeviceProperties.limits.maxImageDimensionCube);
        printf("    maxImageArrayLayers %d\n", physicalDeviceProperties.limits.maxImageArrayLayers);
        printf("    maxTexelBufferElements %d\n", physicalDeviceProperties.limits.maxTexelBufferElements);
        printf("    maxUniformBufferRange %d\n", physicalDeviceProperties.limits.maxUniformBufferRange);
        printf("    maxStorageBufferRange %d\n", physicalDeviceProperties.limits.maxStorageBufferRange);
        printf("    maxPushConstantsSize %d\n", physicalDeviceProperties.limits.maxPushConstantsSize);
        printf("    maxMemoryAllocationCount %d\n", physicalDeviceProperties.limits.maxMemoryAllocationCount);
        printf("    maxSamplerAllocationCount %d\n", physicalDeviceProperties.limits.maxSamplerAllocationCount);
        printf("    bufferImageGranularity %lld\n", physicalDeviceProperties.limits.bufferImageGranularity);
        printf("    sparseAddressSpaceSize %lld\n", physicalDeviceProperties.limits.sparseAddressSpaceSize);
        printf("    maxBoundDescriptorSets %d\n", physicalDeviceProperties.limits.maxBoundDescriptorSets);
        printf("    maxPerStageDescriptorSamplers %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorSamplers);
        printf("    maxPerStageDescriptorUniformBuffers %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorUniformBuffers);
        printf("    maxPerStageDescriptorStorageBuffers %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorStorageBuffers);
        printf("    maxPerStageDescriptorSampledImages %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorSampledImages);
        printf("    maxPerStageDescriptorStorageImages %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorStorageImages);
        printf("    maxPerStageDescriptorInputAttachments %d\n", physicalDeviceProperties.limits.maxPerStageDescriptorInputAttachments);
        printf("    maxPerStageResources %d\n", physicalDeviceProperties.limits.maxPerStageResources);
        printf("    maxDescriptorSetSamplers %d\n", physicalDeviceProperties.limits.maxDescriptorSetSamplers);
        printf("    maxDescriptorSetUniformBuffers %d\n", physicalDeviceProperties.limits.maxDescriptorSetUniformBuffers);
        printf("    maxDescriptorSetUniformBuffersDynamic %d\n", physicalDeviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
        printf("    maxDescriptorSetStorageBuffers %d\n", physicalDeviceProperties.limits.maxDescriptorSetStorageBuffers);
        printf("    maxDescriptorSetStorageBuffersDynamic %d\n", physicalDeviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
        printf("    maxDescriptorSetSampledImages %d\n", physicalDeviceProperties.limits.maxDescriptorSetSampledImages);
        printf("    maxDescriptorSetStorageImages %d\n", physicalDeviceProperties.limits.maxDescriptorSetStorageImages);
        printf("    maxDescriptorSetInputAttachments %d\n", physicalDeviceProperties.limits.maxDescriptorSetInputAttachments);
        printf("    maxVertexInputAttributes %d\n", physicalDeviceProperties.limits.maxVertexInputAttributes);
        printf("    maxVertexInputBindings %d\n", physicalDeviceProperties.limits.maxVertexInputBindings);
        printf("    maxVertexInputAttributeOffset %d\n", physicalDeviceProperties.limits.maxVertexInputAttributeOffset);
        printf("    maxVertexInputBindingStride %d\n", physicalDeviceProperties.limits.maxVertexInputBindingStride);
        printf("    maxVertexOutputComponents %d\n", physicalDeviceProperties.limits.maxVertexOutputComponents);
        printf("    maxTessellationGenerationLevel %d\n", physicalDeviceProperties.limits.maxTessellationGenerationLevel);
        printf("    maxTessellationPatchSize %d\n", physicalDeviceProperties.limits.maxTessellationPatchSize);
        printf("    maxTessellationControlPerVertexInputComponents %d\n", physicalDeviceProperties.limits.maxTessellationControlPerVertexInputComponents);
        printf("    maxTessellationControlPerVertexOutputComponents %d\n", physicalDeviceProperties.limits.maxTessellationControlPerVertexOutputComponents);
        printf("    maxTessellationControlPerPatchOutputComponents %d\n", physicalDeviceProperties.limits.maxTessellationControlPerPatchOutputComponents);
        printf("    maxTessellationControlTotalOutputComponents %d\n", physicalDeviceProperties.limits.maxTessellationControlTotalOutputComponents);
        printf("    maxTessellationEvaluationInputComponents %d\n", physicalDeviceProperties.limits.maxTessellationEvaluationInputComponents);
        printf("    maxTessellationEvaluationOutputComponents %d\n", physicalDeviceProperties.limits.maxTessellationEvaluationOutputComponents);
        printf("    maxGeometryShaderInvocations %d\n", physicalDeviceProperties.limits.maxGeometryShaderInvocations);
        printf("    maxGeometryInputComponents %d\n", physicalDeviceProperties.limits.maxGeometryInputComponents);
        printf("    maxGeometryOutputComponents %d\n", physicalDeviceProperties.limits.maxGeometryOutputComponents);
        printf("    maxGeometryOutputVertices %d\n", physicalDeviceProperties.limits.maxGeometryOutputVertices);
        printf("    maxGeometryTotalOutputComponents %d\n", physicalDeviceProperties.limits.maxGeometryTotalOutputComponents);
        printf("    maxFragmentInputComponents %d\n", physicalDeviceProperties.limits.maxFragmentInputComponents);
        printf("    maxFragmentOutputAttachments %d\n", physicalDeviceProperties.limits.maxFragmentOutputAttachments);
        printf("    maxFragmentDualSrcAttachments %d\n", physicalDeviceProperties.limits.maxFragmentDualSrcAttachments);
        printf("    maxFragmentCombinedOutputResources %d\n", physicalDeviceProperties.limits.maxFragmentCombinedOutputResources);
        printf("    maxComputeSharedMemorySize %d\n", physicalDeviceProperties.limits.maxComputeSharedMemorySize);
        printf("    maxComputeWorkGroupCount (%d %d %d)\n", physicalDeviceProperties.limits.maxComputeWorkGroupCount[0], physicalDeviceProperties.limits.maxComputeWorkGroupCount[1], physicalDeviceProperties.limits.maxComputeWorkGroupCount[2]);
        printf("    maxComputeWorkGroupInvocations %d\n", physicalDeviceProperties.limits.maxComputeWorkGroupInvocations);
        printf("    maxComputeWorkGroupSize (%d %d %d)\n", physicalDeviceProperties.limits.maxComputeWorkGroupSize[0], physicalDeviceProperties.limits.maxComputeWorkGroupSize[1], physicalDeviceProperties.limits.maxComputeWorkGroupSize[2]);
        printf("    subPixelPrecisionBits %d\n", physicalDeviceProperties.limits.subPixelPrecisionBits);
        printf("    subTexelPrecisionBits %d\n", physicalDeviceProperties.limits.subTexelPrecisionBits);
        printf("    maxDrawIndexedIndexValue %d\n", physicalDeviceProperties.limits.maxDrawIndexedIndexValue);
        printf("    maxDrawIndirectCount %d\n", physicalDeviceProperties.limits.maxDrawIndirectCount);
        printf("    maxSamplerLodBias %f\n", physicalDeviceProperties.limits.maxSamplerLodBias);
        printf("    maxSamplerAnisotropy %f\n", physicalDeviceProperties.limits.maxSamplerAnisotropy);
        printf("    maxViewports %d\n", physicalDeviceProperties.limits.maxViewports);
        printf("    maxViewportDimensions (%d %d)\n", physicalDeviceProperties.limits.maxViewportDimensions[0], physicalDeviceProperties.limits.maxViewportDimensions[1]);
        printf("    viewportBoundsRange (%f %f)\n", physicalDeviceProperties.limits.viewportBoundsRange[0], physicalDeviceProperties.limits.viewportBoundsRange[1]);
        printf("    viewportSubPixelBits %d\n", physicalDeviceProperties.limits.viewportSubPixelBits);
        printf("    minMemoryMapAlignment %zd\n", physicalDeviceProperties.limits.minMemoryMapAlignment);
        printf("    minTexelBufferOffsetAlignment %lld\n", physicalDeviceProperties.limits.minTexelBufferOffsetAlignment);
        printf("    minUniformBufferOffsetAlignment %lld\n", physicalDeviceProperties.limits.minUniformBufferOffsetAlignment);
        printf("    minStorageBufferOffsetAlignment %lld\n", physicalDeviceProperties.limits.minStorageBufferOffsetAlignment);
        printf("    minTexelOffset %d\n", physicalDeviceProperties.limits.minTexelOffset);
        printf("    maxTexelOffset %d\n", physicalDeviceProperties.limits.maxTexelOffset);
        printf("    minTexelGatherOffset %d\n", physicalDeviceProperties.limits.minTexelGatherOffset);
        printf("    maxTexelGatherOffset %d\n", physicalDeviceProperties.limits.maxTexelGatherOffset);
        printf("    minInterpolationOffset %f\n", physicalDeviceProperties.limits.minInterpolationOffset);
        printf("    maxInterpolationOffset %f\n", physicalDeviceProperties.limits.maxInterpolationOffset);
        printf("    subPixelInterpolationOffsetBits %d\n", physicalDeviceProperties.limits.subPixelInterpolationOffsetBits);
        printf("    maxFramebufferWidth %d\n", physicalDeviceProperties.limits.maxFramebufferWidth);
        printf("    maxFramebufferHeight %d\n", physicalDeviceProperties.limits.maxFramebufferHeight);
        printf("    maxFramebufferLayers %d\n", physicalDeviceProperties.limits.maxFramebufferLayers);
        printf("    framebufferColorSampleCounts %d\n", physicalDeviceProperties.limits.framebufferColorSampleCounts);
        printf("    framebufferDepthSampleCounts %d\n", physicalDeviceProperties.limits.framebufferDepthSampleCounts);
        printf("    framebufferStencilSampleCounts %d\n", physicalDeviceProperties.limits.framebufferStencilSampleCounts);
        printf("    framebufferNoAttachmentsSampleCounts %d\n", physicalDeviceProperties.limits.framebufferNoAttachmentsSampleCounts);
        printf("    maxColorAttachments %d\n", physicalDeviceProperties.limits.maxColorAttachments);
        printf("    sampledImageColorSampleCounts %d\n", physicalDeviceProperties.limits.sampledImageColorSampleCounts);
        printf("    sampledImageIntegerSampleCounts %d\n", physicalDeviceProperties.limits.sampledImageIntegerSampleCounts);
        printf("    sampledImageDepthSampleCounts %d\n", physicalDeviceProperties.limits.sampledImageDepthSampleCounts);
        printf("    sampledImageStencilSampleCounts %d\n", physicalDeviceProperties.limits.sampledImageStencilSampleCounts);
        printf("    storageImageSampleCounts %d\n", physicalDeviceProperties.limits.storageImageSampleCounts);
        printf("    maxSampleMaskWords %d\n", physicalDeviceProperties.limits.maxSampleMaskWords);
        printf("    timestampComputeAndGraphics %d\n", physicalDeviceProperties.limits.timestampComputeAndGraphics);
        printf("    timestampPeriod %f\n", physicalDeviceProperties.limits.timestampPeriod);
        printf("    maxClipDistances %d\n", physicalDeviceProperties.limits.maxClipDistances);
        printf("    maxCullDistances %d\n", physicalDeviceProperties.limits.maxCullDistances);
        printf("    maxCombinedClipAndCullDistances %d\n", physicalDeviceProperties.limits.maxCombinedClipAndCullDistances);
        printf("    discreteQueuePriorities %d\n", physicalDeviceProperties.limits.discreteQueuePriorities);
        printf("    pointSizeRange (%f %f)\n", physicalDeviceProperties.limits.pointSizeRange[0], physicalDeviceProperties.limits.pointSizeRange[1]);
        printf("    lineWidthRange (%f %f)\n", physicalDeviceProperties.limits.lineWidthRange[0], physicalDeviceProperties.limits.lineWidthRange[1]);
        printf("    pointSizeGranularity %f\n", physicalDeviceProperties.limits.pointSizeGranularity);
        printf("    lineWidthGranularity %f\n", physicalDeviceProperties.limits.lineWidthGranularity);
        printf("    strictLines %d\n", physicalDeviceProperties.limits.strictLines);
        printf("    standardSampleLocations %d\n", physicalDeviceProperties.limits.standardSampleLocations);
        printf("    optimalBufferCopyOffsetAlignment %lld\n", physicalDeviceProperties.limits.optimalBufferCopyOffsetAlignment);
        printf("    optimalBufferCopyRowPitchAlignment %lld\n", physicalDeviceProperties.limits.optimalBufferCopyRowPitchAlignment);
        printf("    nonCoherentAtomSize %lld\n", physicalDeviceProperties.limits.nonCoherentAtomSize);

        //-------------------------------------------------
        printf("  sparse properties:\n");
        printf("    residencyStandard2DBlockShape %d\n", physicalDeviceProperties.sparseProperties.residencyStandard2DBlockShape);
        printf("    residencyStandard2DMultisampleBlockShape %d\n", physicalDeviceProperties.sparseProperties.residencyStandard2DMultisampleBlockShape);
        printf("    residencyStandard3DBlockShape %d\n", physicalDeviceProperties.sparseProperties.residencyStandard3DBlockShape);
        printf("    residencyAlignedMipSize %d\n", physicalDeviceProperties.sparseProperties.residencyAlignedMipSize);
        printf("    residencyNonResidentStrict %d\n", physicalDeviceProperties.sparseProperties.residencyNonResidentStrict);
    }

    //--- VkPhysicalDeviceFeatures
    //-----------------------------------------------------------------------
    {
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        device.getPhysicalDeviceFeatures(physicalDeviceFeatures);
        printf("\n  features\n");
        printf("  robustBufferAccess %d\n", physicalDeviceFeatures.robustBufferAccess);
        printf("  fullDrawIndexUint32 %d\n", physicalDeviceFeatures.fullDrawIndexUint32);
        printf("  imageCubeArray %d\n", physicalDeviceFeatures.imageCubeArray);
        printf("  independentBlend %d\n", physicalDeviceFeatures.independentBlend);
        printf("  geometryShader %d\n", physicalDeviceFeatures.geometryShader);
        printf("  tessellationShader %d\n", physicalDeviceFeatures.tessellationShader);
        printf("  sampleRateShading %d\n", physicalDeviceFeatures.sampleRateShading);
        printf("  dualSrcBlend %d\n", physicalDeviceFeatures.dualSrcBlend);
        printf("  logicOp %d\n", physicalDeviceFeatures.logicOp);
        printf("  multiDrawIndirect %d\n", physicalDeviceFeatures.multiDrawIndirect);
        printf("  drawIndirectFirstInstance %d\n", physicalDeviceFeatures.drawIndirectFirstInstance);
        printf("  depthClamp %d\n", physicalDeviceFeatures.depthClamp);
        printf("  depthBiasClamp %d\n", physicalDeviceFeatures.depthBiasClamp);
        printf("  fillModeNonSolid %d\n", physicalDeviceFeatures.fillModeNonSolid);
        printf("  depthBounds %d\n", physicalDeviceFeatures.depthBounds);
        printf("  wideLines %d\n", physicalDeviceFeatures.wideLines);
        printf("  largePoints %d\n", physicalDeviceFeatures.largePoints);
        printf("  alphaToOne %d\n", physicalDeviceFeatures.alphaToOne);
        printf("  multiViewport %d\n", physicalDeviceFeatures.multiViewport);
        printf("  samplerAnisotropy %d\n", physicalDeviceFeatures.samplerAnisotropy);
        printf("  textureCompressionETC2 %d\n", physicalDeviceFeatures.textureCompressionETC2);
        printf("  textureCompressionASTC_LDR %d\n", physicalDeviceFeatures.textureCompressionASTC_LDR);
        printf("  textureCompressionBC %d\n", physicalDeviceFeatures.textureCompressionBC);
        printf("  occlusionQueryPrecise %d\n", physicalDeviceFeatures.occlusionQueryPrecise);
        printf("  pipelineStatisticsQuery %d\n", physicalDeviceFeatures.pipelineStatisticsQuery);
        printf("  vertexPipelineStoresAndAtomics %d\n", physicalDeviceFeatures.vertexPipelineStoresAndAtomics);
        printf("  fragmentStoresAndAtomics %d\n", physicalDeviceFeatures.fragmentStoresAndAtomics);
        printf("  shaderTessellationAndGeometryPointSize %d\n", physicalDeviceFeatures.shaderTessellationAndGeometryPointSize);
        printf("  shaderImageGatherExtended %d\n", physicalDeviceFeatures.shaderImageGatherExtended);
        printf("  shaderStorageImageExtendedFormats %d\n", physicalDeviceFeatures.shaderStorageImageExtendedFormats);
        printf("  shaderStorageImageMultisample %d\n", physicalDeviceFeatures.shaderStorageImageMultisample);
        printf("  shaderStorageImageReadWithoutFormat %d\n", physicalDeviceFeatures.shaderStorageImageReadWithoutFormat);
        printf("  shaderStorageImageWriteWithoutFormat %d\n", physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat);
        printf("  shaderUniformBufferArrayDynamicIndexing %d\n", physicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing);
        printf("  shaderSampledImageArrayDynamicIndexing %d\n", physicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing);
        printf("  shaderStorageBufferArrayDynamicIndexing %d\n", physicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing);
        printf("  shaderStorageImageArrayDynamicIndexing %d\n", physicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing);
        printf("  shaderClipDistance %d\n", physicalDeviceFeatures.shaderClipDistance);
        printf("  shaderCullDistance %d\n", physicalDeviceFeatures.shaderCullDistance);
        printf("  shaderFloat64 %d\n", physicalDeviceFeatures.shaderFloat64);
        printf("  shaderInt64 %d\n", physicalDeviceFeatures.shaderInt64);
        printf("  shaderInt16 %d\n", physicalDeviceFeatures.shaderInt16);
        printf("  shaderResourceResidency %d\n", physicalDeviceFeatures.shaderResourceResidency);
        printf("  shaderResourceMinLod %d\n", physicalDeviceFeatures.shaderResourceMinLod);
        printf("  sparseBinding %d\n", physicalDeviceFeatures.sparseBinding);
        printf("  sparseResidencyBuffer %d\n", physicalDeviceFeatures.sparseResidencyBuffer);
        printf("  sparseResidencyImage2D %d\n", physicalDeviceFeatures.sparseResidencyImage2D);
        printf("  sparseResidencyImage3D %d\n", physicalDeviceFeatures.sparseResidencyImage3D);
        printf("  sparseResidency2Samples %d\n", physicalDeviceFeatures.sparseResidency2Samples);
        printf("  sparseResidency4Samples %d\n", physicalDeviceFeatures.sparseResidency4Samples);
        printf("  sparseResidency8Samples %d\n", physicalDeviceFeatures.sparseResidency8Samples);
        printf("  sparseResidency16Samples %d\n", physicalDeviceFeatures.sparseResidency16Samples);
        printf("  sparseResidencyAliased %d\n", physicalDeviceFeatures.sparseResidencyAliased);
        printf("  variableMultisampleRate %d\n", physicalDeviceFeatures.variableMultisampleRate);
        printf("  inheritedQueries %d\n", physicalDeviceFeatures.inheritedQueries);
    }

    //--- VkPhysicalDeviceMemoryProperties
    //-----------------------------------------------------------------------
    {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
        device.getPhysicalDeviceMemoryProperties(physicalDeviceMemoryProperties);
        printf("\n memory properties\n");
        for(lgfx::u32 j = 0; j<physicalDeviceMemoryProperties.memoryTypeCount; ++j){
            printf("  memory %d index %d propety flags %d\n", j, physicalDeviceMemoryProperties.memoryTypes[j].heapIndex, physicalDeviceMemoryProperties.memoryTypes[j].propertyFlags);
        }
        for(lgfx::u32 j = 0; j<physicalDeviceMemoryProperties.memoryHeapCount; ++j){
            printf("  heap %d size %lld memory flags %d\n", j, physicalDeviceMemoryProperties.memoryHeaps[j].size, physicalDeviceMemoryProperties.memoryHeaps[j].flags);
        }
    }
}
#endif

#ifdef LGFX_DX12

class Sample00 : public lapp::Application
{
public:
    static const lgfx::s32 MaxBackCounts = 2;

    Sample00();
    ~Sample00();
    virtual bool initialize(lapp::InitParam& initParam);
    virtual void terminate();

    virtual bool update();

    virtual lgfx::Window& getWindow();

protected:
    struct Vertex
    {
        lapp::Vector3 position_;
        lapp::Vector4 color_;
    };

    bool populateCommandList();
    void waitForPreviousFrame();

    lgfx::Window window_;
    lgfx::f32 aspect_;
    lgfx::Viewport viewport_;
    lgfx::RectS32 scissor_;

    lgfx::Factory factory_;
    lgfx::Adapter adapter_;
    lgfx::Device device_;
    lgfx::CommandQueue commandQueue_;
    lgfx::SwapChain swapchain_;
    lgfx::DescriptorHeap rtvHeap_;
    lgfx::u32 rtvDescriptorSize_;

    lgfx::Resource backBuffers_[MaxBackCounts];

    lgfx::CommandAllocator commandAllocator_;
    lgfx::RootSignature rootSignature_;

    lgfx::PipelineState pipelineState_;
    lgfx::GraphicsCommandList graphicsCommandList_;

    lgfx::VertexBufferView vertexBufferView_;
    lgfx::VertexBuffer vertexBuffer_;

    lgfx::u32 frameIndex_;
    HANDLE fenceEvent_;
    lgfx::Fence fence_;
    lgfx::u64 fenceValue_;
};

Sample00::Sample00()
    :aspect_(1.0f)
    ,rtvDescriptorSize_(0)
    ,frameIndex_(0)
    ,fenceEvent_(LGFX_NULL)
    ,fenceValue_(0)
{}

Sample00::~Sample00()
{}

bool Sample00::initialize(lapp::InitParam& initParam)
{
    HINSTANCE hInstance = LGFX_NULL;
    if(FALSE == GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &hInstance)){
        return false;
    }
    initParam.windowParam_.instance_ = hInstance;
    if(!window_.create(initParam.windowParam_)){
        return false;
    }
    aspect_ = static_cast<lgfx::f32>(initParam.graphicsParam_.height_)/initParam.graphicsParam_.width_;
    viewport_ = {0.0f, 0.0f, static_cast<lgfx::f32>(initParam.graphicsParam_.width_), static_cast<lgfx::f32>(initParam.graphicsParam_.height_), lgfx::DefaultMinDepth, lgfx::DefaultMaxDepth};
    scissor_ = {0, 0, static_cast<lgfx::s32>(initParam.windowParam_.width_), static_cast<lgfx::s32>(initParam.windowParam_.height_)};

    //Load pipeline
    factory_ = lgfx::Factory::create();
    adapter_ = lgfx::Adapter::create(factory_, lgfx::FeatureLevel_11_0);
    device_ = lgfx::Device::create(adapter_, lgfx::FeatureLevel_11_0);
    commandQueue_ = lgfx::CommandQueue::create(device_, lgfx::CommandListType_Direct);
    swapchain_ = lgfx::SwapChain::create(factory_, commandQueue_, window_.getHandle(), MaxBackCounts, initParam.graphicsParam_.width_, initParam.graphicsParam_.height_, lgfx::Format_R8G8B8A8_UNORM, lgfx::Usage_RenderTargetOutput, lgfx::SwapEffect_FlipDiscard, 0, lgfx::MWA_NO_ALT_ENTER);
    rtvHeap_ = lgfx::DescriptorHeap::create(device_, lgfx::DescriptorHeapType_RTV, MaxBackCounts, lgfx::DescriptorHeapFlag_None);

    {//Create frame resources.
        rtvDescriptorSize_ = device_->GetDescriptorHandleIncrementSize(static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(lgfx::DescriptorHeapType_RTV));
        lgfx::CPUDesctiptorHandle cpuDescriptorHandle(rtvHeap_->GetCPUDescriptorHandleForHeapStart());

        ID3D12Resource* resources[MaxBackCounts];
        for(lgfx::u32 i=0; i<MaxBackCounts; ++i){
            if(FAILED(swapchain_->GetBuffer(i, IID_PPV_ARGS(&resources[i])))){
                return false;
            }
            device_->CreateRenderTargetView(resources[i], LGFX_NULL, cpuDescriptorHandle);
            cpuDescriptorHandle.offset(1, rtvDescriptorSize_);
            backBuffers_[i] = lgfx::move(lgfx::Resource(resources[i]));
        }
    }

    commandAllocator_ = lgfx::CommandAllocator::create(device_, lgfx::CommandListType_Direct);

    //Load resources
    lgfx::RootSignatureDesc rootSignatureDesc =
    {
        0,
        LGFX_NULL,
        0,
        LGFX_NULL,
        lgfx::RootSignatureFlags_AllowInputAssemblerInputLayout,
    };
    rootSignature_ = lgfx::RootSignature::create(device_, rootSignatureDesc);

    lgfx::Blob blobVS = lgfx::Blob::loadFileAll("../../assets/shader_vs_d.so");
    lgfx::Blob blobPS = lgfx::Blob::loadFileAll("../../assets/shader_ps_d.so");

    lgfx::PipelineState::stream_output_desc_type streamOutputDesc = lgfx::StreamOutputDesc::create();
    lgfx::PipelineState::blend_desc_type blendDesc = lgfx::BlendDesc::create();
    lgfx::PipelineState::rasterizer_desc_type rasterizerDesc = lgfx::RasterizerDesc::SolidCW;
    lgfx::PipelineState::depth_stencil_desc_type descStencilDesc = lgfx::DepthStencilDesc::Disable;//lgfx::DepthStencilDesc::Depth;
    lgfx::PipelineState::input_element_desc_type inputElementDescs[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };
    lgfx::PipelineState::input_layout_desc_type inputLayoutDesc ={
        inputElementDescs,
        2,
    };

    lgfx::RenderTargetFormat renderFormats = lgfx::RenderTargetFormat::create(lgfx::Format_R8G8B8A8_UNORM);
    lgfx::CachedPipelineState::desc_type cachedPipelineState = lgfx::CachedPipelineState::create();

    pipelineState_ = lgfx::PipelineState::create(
        device_,
        rootSignature_,
        &blobVS,
        &blobPS,
        LGFX_NULL,
        LGFX_NULL,
        LGFX_NULL,
        streamOutputDesc,
        blendDesc,
        0xFFFFFFFFU,
        rasterizerDesc,
        descStencilDesc,
        inputLayoutDesc,
        lgfx::IndexBufferStripCutValue_Disabled,
        lgfx::PrimitiveTopologyType_Triangle,
        1,
        renderFormats.formats_,
        lgfx::Format_UNKNOWN, //lgfx::Format_D24_UNORM_S8_UINT,
        {1, 0},
        0,
        cachedPipelineState,
        lgfx::PipelineStateFlag_None
    );

    graphicsCommandList_ = lgfx::GraphicsCommandList::create(device_, 0, lgfx::CommandListType_Direct, commandAllocator_, pipelineState_);
    //There is nothing to record into the command list. So close it now.
    graphicsCommandList_->Close();

    {
        Vertex vertices[] =
        {
            {{0.0f, 0.25f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.25f, -0.25f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{-0.25f, -0.25f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        };

        lapp::u32 size = sizeof(vertices);

        lgfx::HeapPropertiesDesc::desc_type heapPropDesc = lgfx::HeapPropertiesDesc::create(lgfx::HeapType_Upload);
        lgfx::ResourceDesc::desc_type resourceDesc = lgfx::ResourceDesc::buffer(size);
        if(!device_.createCommittedResource(
            &heapPropDesc,
            lgfx::HeapFlag_None,
            &resourceDesc,
            lgfx::ResourceState_GenericRead,
            LGFX_NULL,
            vertexBuffer_)){
            return false;
        }

        lgfx::u8* vertexData = LGFX_NULL;
        lgfx::Range range = {0, 0};
        if(!vertexBuffer_.map(0, &range, &vertexData)){
            return false;
        }
        memcpy(vertexData, vertices, size);
        vertexBuffer_.unmap(0, LGFX_NULL);

        vertexBufferView_.bufferLocation_ = vertexBuffer_->GetGPUVirtualAddress();
        vertexBufferView_.sizeInBytes_ = size;
        vertexBufferView_.strideInBytes_ = sizeof(Vertex);
    }

    //Create synchronization objects and wait until assets have been uploaded to the GPU.
    {
        fence_ = lgfx::Fence::create(device_, 0, lgfx::FenceFlag_None);
        fenceValue_ = 1;
        fenceEvent_ = CreateEvent(LGFX_NULL, FALSE, FALSE, LGFX_NULL);
        if(LGFX_NULL == fenceEvent_){
            return false;
        }
    }
    waitForPreviousFrame();
    return true;
}

void Sample00::terminate()
{
    waitForPreviousFrame();
    CloseHandle(fenceEvent_);
    fenceEvent_ = LGFX_NULL;
    window_.destroy();
}

bool Sample00::update()
{
    if(!window_.peekEvent()){
        return false;
    }
    // Record all the commands we need to render the scene into the command list.
    populateCommandList();

    // Execute the command list.
    ID3D12CommandList* ppCommandLists[] ={graphicsCommandList_};
    commandQueue_->ExecuteCommandLists(1, ppCommandLists);

    // Present the frame.
    swapchain_->Present(1, 0);

    waitForPreviousFrame();
    return true;
}

lgfx::Window& Sample00::getWindow()
{
    return window_;
}

bool Sample00::populateCommandList()
{
    // Command list allocators can only be reset when the associated 
    // command lists have finished execution on the GPU; apps should use 
    // fences to determine GPU execution progress.
    if(FAILED(commandAllocator_->Reset())){
        return false;
    }

    // However, when ExecuteCommandList() is called on a particular command 
    // list, that command list can then be reset at any time and must be before 
    // re-recording.
    if(FAILED(graphicsCommandList_->Reset(commandAllocator_, pipelineState_))){
        return false;
    }

    // Set necessary state.
    graphicsCommandList_->SetGraphicsRootSignature(rootSignature_);
    graphicsCommandList_->RSSetViewports(1, reinterpret_cast<const D3D12_VIEWPORT*>(&viewport_));
    graphicsCommandList_->RSSetScissorRects(1, reinterpret_cast<const D3D12_RECT*>(&scissor_));

    // Indicate that the back buffer will be used as a render target.
    lgfx::ResourceBarrier::desc_type resourceBarrierDesc = lgfx::ResourceBarrier::transition(backBuffers_[frameIndex_], lgfx::ResourceState_Present, lgfx::ResourceState_RenderTarget);
    graphicsCommandList_->ResourceBarrier(1, &resourceBarrierDesc);

    lgfx::CPUDesctiptorHandle rtvHandle = lgfx::CPUDesctiptorHandle(rtvHeap_->GetCPUDescriptorHandleForHeapStart(), frameIndex_, rtvDescriptorSize_);
    graphicsCommandList_->OMSetRenderTargets(1, &rtvHandle, FALSE, LGFX_NULL);

    // Record commands.
    const lgfx::f32 clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
    graphicsCommandList_->ClearRenderTargetView(rtvHandle, clearColor, 0, LGFX_NULL);
    graphicsCommandList_->IASetPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(lgfx::PrimitiveTopology_TriangleList));
    graphicsCommandList_->IASetVertexBuffers(0, 1, reinterpret_cast<const D3D12_VERTEX_BUFFER_VIEW*>(&vertexBufferView_));
    graphicsCommandList_->DrawInstanced(3, 1, 0, 0);

    // Indicate that the back buffer will now be used to present.
    resourceBarrierDesc = lgfx::ResourceBarrier::transition(backBuffers_[frameIndex_], lgfx::ResourceState_RenderTarget, lgfx::ResourceState_Present);
    graphicsCommandList_->ResourceBarrier(1, &resourceBarrierDesc);
    return SUCCEEDED(graphicsCommandList_->Close());
}

void Sample00::waitForPreviousFrame()
{
    // WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
    // This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
    // sample illustrates how to use fences for efficient resource usage and to
    // maximize GPU utilization.

    //Signal and increment the fence value
    const lgfx::u64 fenceValue = fenceValue_;
    if(FAILED(commandQueue_->Signal(fence_, fenceValue))){
        return;
    }
    ++fenceValue_;

    //Wait until the previous frame is finished.
    if(fence_->GetCompletedValue()<fenceValue){
        fence_->SetEventOnCompletion(fenceValue, fenceEvent_);
        WaitForSingleObject(fenceEvent_, INFINITE);
    }
    frameIndex_ = swapchain_->GetCurrentBackBufferIndex();
}

int main(int /*argc*/, char** /*argv*/)
{
    //---------------------------------------------------------------------
    const lgfx::s32 width = 400;
    const lgfx::s32 height = 300;
    const lgfx::s32 backCount = 2;

    {
        lapp::InitParam initParam;
        initParam.windowParam_ = {
            LGFX_NULL,
            width,
            height,
            0,0,
            LGFX_NULL,
            "Tutorial",
            true,
        };
        initParam.graphicsParam_ ={
            width,
            height,
        };

        if(!lapp::Core::initialize(initParam, LAPP_NEW Sample00)){
            return EXIT_FAILURE;
        }
    }

    lapp::Core::update();
    lapp::Core::terminate();
    return EXIT_SUCCESS;
}
#endif
