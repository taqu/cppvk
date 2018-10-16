#include <stdio.h>
#define LGFX_IMPLEMENTATION
#include "lgfx.h"

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
