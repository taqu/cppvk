
#ifndef VLK_EXPORTED_FUNCTION
#    define VLK_EXPORTED_FUNCTION(name)
#endif

#ifndef VLK_INSTANCE_FUNCTION
#    define VLK_INSTANCE_FUNCTION(name)
#endif

#ifndef VLK_DEVICE_FUNCTION
#    define VLK_DEVICE_FUNCTION(name)
#endif

#ifndef VLK_PHYSICALDEVICE_FUNCTION
#    define VLK_PHYSICALDEVICE_FUNCTION(name)
#endif

#ifndef VLK_EXT_EXPORTED_FUNCTION
#    define VLK_EXT_EXPORTED_FUNCTION(name)
#endif

#ifndef VLK_EXT_INSTANCE_FUNCTION
#    define VLK_EXT_INSTANCE_FUNCTION(name)
#endif

#ifndef VLK_EXT_DEVICE_FUNCTION
#    define VLK_EXT_DEVICE_FUNCTION(name)
#endif

#ifndef VLK_EXT_PHYSICALDEVICE_FUNCTION
#    define VLK_EXT_PHYSICALDEVICE_FUNCTION(name)
#endif

    VLK_EXPORTED_FUNCTION(vkCreateInstance)
    VLK_EXPORTED_FUNCTION(vkEnumerateInstanceLayerProperties)
    VLK_EXPORTED_FUNCTION(vkEnumerateInstanceExtensionProperties)
    VLK_EXPORTED_FUNCTION(vkQueueSubmit)
    VLK_EXPORTED_FUNCTION(vkQueueWaitIdle)
    VLK_EXPORTED_FUNCTION(vkQueueBindSparse)
    VLK_EXPORTED_FUNCTION(vkBeginCommandBuffer)
    VLK_EXPORTED_FUNCTION(vkEndCommandBuffer)
    VLK_EXPORTED_FUNCTION(vkResetCommandBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdBindPipeline)
    VLK_EXPORTED_FUNCTION(vkCmdSetViewport)
    VLK_EXPORTED_FUNCTION(vkCmdSetScissor)
    VLK_EXPORTED_FUNCTION(vkCmdSetLineWidth)
    VLK_EXPORTED_FUNCTION(vkCmdSetDepthBias)
    VLK_EXPORTED_FUNCTION(vkCmdSetBlendConstants)
    VLK_EXPORTED_FUNCTION(vkCmdSetDepthBounds)
    VLK_EXPORTED_FUNCTION(vkCmdSetStencilCompareMask)
    VLK_EXPORTED_FUNCTION(vkCmdSetStencilWriteMask)
    VLK_EXPORTED_FUNCTION(vkCmdSetStencilReference)
    VLK_EXPORTED_FUNCTION(vkCmdBindDescriptorSets)
    VLK_EXPORTED_FUNCTION(vkCmdBindIndexBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdBindVertexBuffers)
    VLK_EXPORTED_FUNCTION(vkCmdDraw)
    VLK_EXPORTED_FUNCTION(vkCmdDrawIndexed)
    VLK_EXPORTED_FUNCTION(vkCmdDrawIndirect)
    VLK_EXPORTED_FUNCTION(vkCmdDrawIndexedIndirect)
    VLK_EXPORTED_FUNCTION(vkCmdDispatch)
    VLK_EXPORTED_FUNCTION(vkCmdDispatchIndirect)
    VLK_EXPORTED_FUNCTION(vkCmdCopyBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdCopyImage)
    VLK_EXPORTED_FUNCTION(vkCmdBlitImage)
    VLK_EXPORTED_FUNCTION(vkCmdCopyBufferToImage)
    VLK_EXPORTED_FUNCTION(vkCmdCopyImageToBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdUpdateBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdFillBuffer)
    VLK_EXPORTED_FUNCTION(vkCmdClearColorImage)
    VLK_EXPORTED_FUNCTION(vkCmdClearDepthStencilImage)
    VLK_EXPORTED_FUNCTION(vkCmdClearAttachments)
    VLK_EXPORTED_FUNCTION(vkCmdResolveImage)
    VLK_EXPORTED_FUNCTION(vkCmdSetEvent)
    VLK_EXPORTED_FUNCTION(vkCmdResetEvent)
    VLK_EXPORTED_FUNCTION(vkCmdWaitEvents)
    VLK_EXPORTED_FUNCTION(vkCmdPipelineBarrier)
    VLK_EXPORTED_FUNCTION(vkCmdBeginQuery)
    VLK_EXPORTED_FUNCTION(vkCmdEndQuery)
    VLK_EXPORTED_FUNCTION(vkCmdResetQueryPool)
    VLK_EXPORTED_FUNCTION(vkCmdWriteTimestamp)
    VLK_EXPORTED_FUNCTION(vkCmdCopyQueryPoolResults)
    VLK_EXPORTED_FUNCTION(vkCmdPushConstants)
    VLK_EXPORTED_FUNCTION(vkCmdBeginRenderPass)
    VLK_EXPORTED_FUNCTION(vkCmdNextSubpass)
    VLK_EXPORTED_FUNCTION(vkCmdEndRenderPass)
    VLK_EXPORTED_FUNCTION(vkCmdExecuteCommands)
    VLK_EXT_DEVICE_FUNCTION(vkQueuePresentKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline VkResult VLK_EXT_DECL_EXPORTED_MEMBER(vkQueuePresentKHR)(VkQueue queue, const VkPresentInfoKHR* pPresentInfo){
        return VLK_EXT_IMPL_EXPORTED_MEMBER(vkQueuePresentKHR)(queue, pPresentInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDebugMarkerBeginEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDebugMarkerBeginEXT)(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDebugMarkerBeginEXT)(commandBuffer, pMarkerInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDebugMarkerEndEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDebugMarkerEndEXT)(VkCommandBuffer commandBuffer){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDebugMarkerEndEXT)(commandBuffer);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDebugMarkerInsertEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDebugMarkerInsertEXT)(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDebugMarkerInsertEXT)(commandBuffer, pMarkerInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDrawIndirectCountAMD)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDrawIndirectCountAMD)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDrawIndirectCountAMD)(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDrawIndexedIndirectCountAMD)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDrawIndexedIndirectCountAMD)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDrawIndexedIndirectCountAMD)(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdProcessCommandsNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdProcessCommandsNVX)(VkCommandBuffer commandBuffer, const VkCmdProcessCommandsInfoNVX* pProcessCommandsInfo){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdProcessCommandsNVX)(commandBuffer, pProcessCommandsInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdReserveSpaceForCommandsNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdReserveSpaceForCommandsNVX)(VkCommandBuffer commandBuffer, const VkCmdReserveSpaceForCommandsInfoNVX* pReserveSpaceInfo){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdReserveSpaceForCommandsNVX)(commandBuffer, pReserveSpaceInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdPushDescriptorSetKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdPushDescriptorSetKHR)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdPushDescriptorSetKHR)(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdSetDeviceMaskKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdSetDeviceMaskKHX)(VkCommandBuffer commandBuffer, uint32_t deviceMask){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdSetDeviceMaskKHX)(commandBuffer, deviceMask);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdDispatchBaseKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdDispatchBaseKHX)(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdDispatchBaseKHX)(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdPushDescriptorSetWithTemplateKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdPushDescriptorSetWithTemplateKHR)(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdPushDescriptorSetWithTemplateKHR)(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdSetViewportWScalingNV)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdSetViewportWScalingNV)(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdSetViewportWScalingNV)(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdSetDiscardRectangleEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdSetDiscardRectangleEXT)(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdSetDiscardRectangleEXT)(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCmdSetSampleLocationsEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)
    inline void VLK_EXT_DECL_EXPORTED_MEMBER(vkCmdSetSampleLocationsEXT)(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo){
        VLK_EXT_IMPL_EXPORTED_MEMBER(vkCmdSetSampleLocationsEXT)(commandBuffer, pSampleLocationsInfo);
    }
#   endif

    VLK_EXPORTED_FUNCTION(vkDestroyInstance)
    VLK_EXPORTED_FUNCTION(vkEnumeratePhysicalDevices)
    VLK_EXPORTED_FUNCTION(vkGetInstanceProcAddr)
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateAndroidSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateAndroidSurfaceKHR)(const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateAndroidSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateDisplayPlaneSurfaceKHR)(const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateDisplayPlaneSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif

#ifdef VK_USE_PLATFORM_MIR_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateMirSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateMirSurfaceKHR)(const VkMirSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateMirSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkDestroySurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline void VLK_EXT_DECL_INSTANCE_MEMBER(vkDestroySurfaceKHR)(VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_INSTANCE_MEMBER(vkDestroySurfaceKHR)(VLK_MEMBER_INSTANCE, surface, pAllocator);
    }
#   endif

#ifdef VK_USE_PLATFORM_VI_NN
    VLK_EXT_INSTANCE_FUNCTION(vkCreateViSurfaceNN)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateViSurfaceNN)(const VkViSurfaceCreateInfoNN* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateViSurfaceNN)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateWaylandSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateWaylandSurfaceKHR)(const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateWaylandSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateWin32SurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateWin32SurfaceKHR)(const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateWin32SurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateXlibSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateXlibSurfaceKHR)(const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateXlibSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkCreateXcbSurfaceKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateXcbSurfaceKHR)(const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateXcbSurfaceKHR)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkCreateDebugReportCallbackEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateDebugReportCallbackEXT)(const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateDebugReportCallbackEXT)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pCallback);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkDestroyDebugReportCallbackEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline void VLK_EXT_DECL_INSTANCE_MEMBER(vkDestroyDebugReportCallbackEXT)(VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_INSTANCE_MEMBER(vkDestroyDebugReportCallbackEXT)(VLK_MEMBER_INSTANCE, callback, pAllocator);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkDebugReportMessageEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline void VLK_EXT_DECL_INSTANCE_MEMBER(vkDebugReportMessageEXT)(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage){
        VLK_EXT_IMPL_INSTANCE_MEMBER(vkDebugReportMessageEXT)(VLK_MEMBER_INSTANCE, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkEnumeratePhysicalDeviceGroupsKHX)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkEnumeratePhysicalDeviceGroupsKHX)(uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHX* pPhysicalDeviceGroupProperties){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkEnumeratePhysicalDeviceGroupsKHX)(VLK_MEMBER_INSTANCE, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    }
#   endif

#ifdef VK_USE_PLATFORM_IOS_MVK
    VLK_EXT_INSTANCE_FUNCTION(vkCreateIOSSurfaceMVK)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateIOSSurfaceMVK)(const VkIOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateIOSSurfaceMVK)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
    VLK_EXT_INSTANCE_FUNCTION(vkCreateMacOSSurfaceMVK)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)
    inline VkResult VLK_EXT_DECL_INSTANCE_MEMBER(vkCreateMacOSSurfaceMVK)(const VkMacOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface){
        return VLK_EXT_IMPL_INSTANCE_MEMBER(vkCreateMacOSSurfaceMVK)(VLK_MEMBER_INSTANCE, pCreateInfo, pAllocator, pSurface);
    }
#   endif
#endif

    VLK_EXPORTED_FUNCTION(vkGetDeviceProcAddr)
    VLK_EXPORTED_FUNCTION(vkDestroyDevice)
    VLK_EXPORTED_FUNCTION(vkGetDeviceQueue)
    VLK_EXPORTED_FUNCTION(vkDeviceWaitIdle)
    VLK_EXPORTED_FUNCTION(vkAllocateMemory)
    VLK_EXPORTED_FUNCTION(vkFreeMemory)
    VLK_EXPORTED_FUNCTION(vkMapMemory)
    VLK_EXPORTED_FUNCTION(vkUnmapMemory)
    VLK_EXPORTED_FUNCTION(vkFlushMappedMemoryRanges)
    VLK_EXPORTED_FUNCTION(vkInvalidateMappedMemoryRanges)
    VLK_EXPORTED_FUNCTION(vkGetDeviceMemoryCommitment)
    VLK_EXPORTED_FUNCTION(vkGetBufferMemoryRequirements)
    VLK_EXPORTED_FUNCTION(vkBindBufferMemory)
    VLK_EXPORTED_FUNCTION(vkGetImageMemoryRequirements)
    VLK_EXPORTED_FUNCTION(vkBindImageMemory)
    VLK_EXPORTED_FUNCTION(vkGetImageSparseMemoryRequirements)
    VLK_EXPORTED_FUNCTION(vkCreateFence)
    VLK_EXPORTED_FUNCTION(vkDestroyFence)
    VLK_EXPORTED_FUNCTION(vkResetFences)
    VLK_EXPORTED_FUNCTION(vkGetFenceStatus)
    VLK_EXPORTED_FUNCTION(vkWaitForFences)
    VLK_EXPORTED_FUNCTION(vkCreateSemaphore)
    VLK_EXPORTED_FUNCTION(vkDestroySemaphore)
    VLK_EXPORTED_FUNCTION(vkCreateEvent)
    VLK_EXPORTED_FUNCTION(vkDestroyEvent)
    VLK_EXPORTED_FUNCTION(vkGetEventStatus)
    VLK_EXPORTED_FUNCTION(vkSetEvent)
    VLK_EXPORTED_FUNCTION(vkResetEvent)
    VLK_EXPORTED_FUNCTION(vkCreateQueryPool)
    VLK_EXPORTED_FUNCTION(vkDestroyQueryPool)
    VLK_EXPORTED_FUNCTION(vkGetQueryPoolResults)
    VLK_EXPORTED_FUNCTION(vkCreateBuffer)
    VLK_EXPORTED_FUNCTION(vkDestroyBuffer)
    VLK_EXPORTED_FUNCTION(vkCreateBufferView)
    VLK_EXPORTED_FUNCTION(vkDestroyBufferView)
    VLK_EXPORTED_FUNCTION(vkCreateImage)
    VLK_EXPORTED_FUNCTION(vkDestroyImage)
    VLK_EXPORTED_FUNCTION(vkGetImageSubresourceLayout)
    VLK_EXPORTED_FUNCTION(vkCreateImageView)
    VLK_EXPORTED_FUNCTION(vkDestroyImageView)
    VLK_EXPORTED_FUNCTION(vkCreateShaderModule)
    VLK_EXPORTED_FUNCTION(vkDestroyShaderModule)
    VLK_EXPORTED_FUNCTION(vkCreatePipelineCache)
    VLK_EXPORTED_FUNCTION(vkDestroyPipelineCache)
    VLK_EXPORTED_FUNCTION(vkGetPipelineCacheData)
    VLK_EXPORTED_FUNCTION(vkMergePipelineCaches)
    VLK_EXPORTED_FUNCTION(vkCreateGraphicsPipelines)
    VLK_EXPORTED_FUNCTION(vkCreateComputePipelines)
    VLK_EXPORTED_FUNCTION(vkDestroyPipeline)
    VLK_EXPORTED_FUNCTION(vkCreatePipelineLayout)
    VLK_EXPORTED_FUNCTION(vkDestroyPipelineLayout)
    VLK_EXPORTED_FUNCTION(vkCreateSampler)
    VLK_EXPORTED_FUNCTION(vkDestroySampler)
    VLK_EXPORTED_FUNCTION(vkCreateDescriptorSetLayout)
    VLK_EXPORTED_FUNCTION(vkDestroyDescriptorSetLayout)
    VLK_EXPORTED_FUNCTION(vkCreateDescriptorPool)
    VLK_EXPORTED_FUNCTION(vkDestroyDescriptorPool)
    VLK_EXPORTED_FUNCTION(vkResetDescriptorPool)
    VLK_EXPORTED_FUNCTION(vkAllocateDescriptorSets)
    VLK_EXPORTED_FUNCTION(vkFreeDescriptorSets)
    VLK_EXPORTED_FUNCTION(vkUpdateDescriptorSets)
    VLK_EXPORTED_FUNCTION(vkCreateFramebuffer)
    VLK_EXPORTED_FUNCTION(vkDestroyFramebuffer)
    VLK_EXPORTED_FUNCTION(vkCreateRenderPass)
    VLK_EXPORTED_FUNCTION(vkDestroyRenderPass)
    VLK_EXPORTED_FUNCTION(vkGetRenderAreaGranularity)
    VLK_EXPORTED_FUNCTION(vkCreateCommandPool)
    VLK_EXPORTED_FUNCTION(vkDestroyCommandPool)
    VLK_EXPORTED_FUNCTION(vkResetCommandPool)
    VLK_EXPORTED_FUNCTION(vkAllocateCommandBuffers)
    VLK_EXPORTED_FUNCTION(vkFreeCommandBuffers)
    VLK_EXT_DEVICE_FUNCTION(vkCreateSharedSwapchainsKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateSharedSwapchainsKHR)(uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateSharedSwapchainsKHR)(VLK_MEMBER_DEVICE, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateSwapchainKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateSwapchainKHR)(const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateSwapchainKHR)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pSwapchain);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroySwapchainKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroySwapchainKHR)(VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroySwapchainKHR)(VLK_MEMBER_DEVICE, swapchain, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetSwapchainImagesKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetSwapchainImagesKHR)(VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetSwapchainImagesKHR)(VLK_MEMBER_DEVICE, swapchain, pSwapchainImageCount, pSwapchainImages);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkAcquireNextImageKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkAcquireNextImageKHR)(VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkAcquireNextImageKHR)(VLK_MEMBER_DEVICE, swapchain, timeout, semaphore, fence, pImageIndex);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDebugMarkerSetObjectNameEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkDebugMarkerSetObjectNameEXT)(const VkDebugMarkerObjectNameInfoEXT* pNameInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkDebugMarkerSetObjectNameEXT)(VLK_MEMBER_DEVICE, pNameInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDebugMarkerSetObjectTagEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkDebugMarkerSetObjectTagEXT)(const VkDebugMarkerObjectTagInfoEXT* pTagInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkDebugMarkerSetObjectTagEXT)(VLK_MEMBER_DEVICE, pTagInfo);
    }
#   endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkGetMemoryWin32HandleNV)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetMemoryWin32HandleNV)(VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetMemoryWin32HandleNV)(VLK_MEMBER_DEVICE, memory, handleType, pHandle);
    }
#   endif
#endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateIndirectCommandsLayoutNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateIndirectCommandsLayoutNVX)(const VkIndirectCommandsLayoutCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNVX* pIndirectCommandsLayout){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateIndirectCommandsLayoutNVX)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pIndirectCommandsLayout);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroyIndirectCommandsLayoutNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroyIndirectCommandsLayoutNVX)(VkIndirectCommandsLayoutNVX indirectCommandsLayout, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroyIndirectCommandsLayoutNVX)(VLK_MEMBER_DEVICE, indirectCommandsLayout, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateObjectTableNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateObjectTableNVX)(const VkObjectTableCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkObjectTableNVX* pObjectTable){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateObjectTableNVX)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pObjectTable);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroyObjectTableNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroyObjectTableNVX)(VkObjectTableNVX objectTable, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroyObjectTableNVX)(VLK_MEMBER_DEVICE, objectTable, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkRegisterObjectsNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkRegisterObjectsNVX)(VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectTableEntryNVX* const*    ppObjectTableEntries, const uint32_t* pObjectIndices){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkRegisterObjectsNVX)(VLK_MEMBER_DEVICE, objectTable, objectCount, ppObjectTableEntries, pObjectIndices);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkUnregisterObjectsNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkUnregisterObjectsNVX)(VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectEntryTypeNVX* pObjectEntryTypes, const uint32_t* pObjectIndices){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkUnregisterObjectsNVX)(VLK_MEMBER_DEVICE, objectTable, objectCount, pObjectEntryTypes, pObjectIndices);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkTrimCommandPoolKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkTrimCommandPoolKHR)(VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkTrimCommandPoolKHR)(VLK_MEMBER_DEVICE, commandPool, flags);
    }
#   endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkGetMemoryWin32HandleKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetMemoryWin32HandleKHR)(const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetMemoryWin32HandleKHR)(VLK_MEMBER_DEVICE, pGetWin32HandleInfo, pHandle);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkGetMemoryWin32HandlePropertiesKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetMemoryWin32HandlePropertiesKHR)(VkExternalMemoryHandleTypeFlagBitsKHR handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetMemoryWin32HandlePropertiesKHR)(VLK_MEMBER_DEVICE, handleType, handle, pMemoryWin32HandleProperties);
    }
#   endif
#endif

    VLK_EXT_DEVICE_FUNCTION(vkGetMemoryFdKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetMemoryFdKHR)(const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetMemoryFdKHR)(VLK_MEMBER_DEVICE, pGetFdInfo, pFd);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetMemoryFdPropertiesKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetMemoryFdPropertiesKHR)(VkExternalMemoryHandleTypeFlagBitsKHR handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetMemoryFdPropertiesKHR)(VLK_MEMBER_DEVICE, handleType, fd, pMemoryFdProperties);
    }
#   endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkGetSemaphoreWin32HandleKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetSemaphoreWin32HandleKHR)(const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetSemaphoreWin32HandleKHR)(VLK_MEMBER_DEVICE, pGetWin32HandleInfo, pHandle);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkImportSemaphoreWin32HandleKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkImportSemaphoreWin32HandleKHR)(const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkImportSemaphoreWin32HandleKHR)(VLK_MEMBER_DEVICE, pImportSemaphoreWin32HandleInfo);
    }
#   endif
#endif

    VLK_EXT_DEVICE_FUNCTION(vkGetSemaphoreFdKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetSemaphoreFdKHR)(const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetSemaphoreFdKHR)(VLK_MEMBER_DEVICE, pGetFdInfo, pFd);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkImportSemaphoreFdKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkImportSemaphoreFdKHR)(const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkImportSemaphoreFdKHR)(VLK_MEMBER_DEVICE, pImportSemaphoreFdInfo);
    }
#   endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkGetFenceWin32HandleKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetFenceWin32HandleKHR)(const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetFenceWin32HandleKHR)(VLK_MEMBER_DEVICE, pGetWin32HandleInfo, pHandle);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_DEVICE_FUNCTION(vkImportFenceWin32HandleKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkImportFenceWin32HandleKHR)(const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkImportFenceWin32HandleKHR)(VLK_MEMBER_DEVICE, pImportFenceWin32HandleInfo);
    }
#   endif
#endif

    VLK_EXT_DEVICE_FUNCTION(vkGetFenceFdKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetFenceFdKHR)(const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetFenceFdKHR)(VLK_MEMBER_DEVICE, pGetFdInfo, pFd);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkImportFenceFdKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkImportFenceFdKHR)(const VkImportFenceFdInfoKHR* pImportFenceFdInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkImportFenceFdKHR)(VLK_MEMBER_DEVICE, pImportFenceFdInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDisplayPowerControlEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkDisplayPowerControlEXT)(VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkDisplayPowerControlEXT)(VLK_MEMBER_DEVICE, display, pDisplayPowerInfo);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkRegisterDeviceEventEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkRegisterDeviceEventEXT)(const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkRegisterDeviceEventEXT)(VLK_MEMBER_DEVICE, pDeviceEventInfo, pAllocator, pFence);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkRegisterDisplayEventEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkRegisterDisplayEventEXT)(VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkRegisterDisplayEventEXT)(VLK_MEMBER_DEVICE, display, pDisplayEventInfo, pAllocator, pFence);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetSwapchainCounterEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetSwapchainCounterEXT)(VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetSwapchainCounterEXT)(VLK_MEMBER_DEVICE, swapchain, counter, pCounterValue);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetDeviceGroupPeerMemoryFeaturesKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkGetDeviceGroupPeerMemoryFeaturesKHX)(uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHX* pPeerMemoryFeatures){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkGetDeviceGroupPeerMemoryFeaturesKHX)(VLK_MEMBER_DEVICE, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkBindBufferMemory2KHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkBindBufferMemory2KHR)(uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkBindBufferMemory2KHR)(VLK_MEMBER_DEVICE, bindInfoCount, pBindInfos);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkBindImageMemory2KHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkBindImageMemory2KHR)(uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkBindImageMemory2KHR)(VLK_MEMBER_DEVICE, bindInfoCount, pBindInfos);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetDeviceGroupPresentCapabilitiesKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetDeviceGroupPresentCapabilitiesKHX)(VkDeviceGroupPresentCapabilitiesKHX* pDeviceGroupPresentCapabilities){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetDeviceGroupPresentCapabilitiesKHX)(VLK_MEMBER_DEVICE, pDeviceGroupPresentCapabilities);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetDeviceGroupSurfacePresentModesKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetDeviceGroupSurfacePresentModesKHX)(VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHX* pModes){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetDeviceGroupSurfacePresentModesKHX)(VLK_MEMBER_DEVICE, surface, pModes);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkAcquireNextImage2KHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkAcquireNextImage2KHX)(const VkAcquireNextImageInfoKHX* pAcquireInfo, uint32_t* pImageIndex){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkAcquireNextImage2KHX)(VLK_MEMBER_DEVICE, pAcquireInfo, pImageIndex);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateDescriptorUpdateTemplateKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateDescriptorUpdateTemplateKHR)(const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateDescriptorUpdateTemplateKHR)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroyDescriptorUpdateTemplateKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroyDescriptorUpdateTemplateKHR)(VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroyDescriptorUpdateTemplateKHR)(VLK_MEMBER_DEVICE, descriptorUpdateTemplate, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkUpdateDescriptorSetWithTemplateKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkUpdateDescriptorSetWithTemplateKHR)(VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkUpdateDescriptorSetWithTemplateKHR)(VLK_MEMBER_DEVICE, descriptorSet, descriptorUpdateTemplate, pData);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkSetHdrMetadataEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkSetHdrMetadataEXT)(uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkSetHdrMetadataEXT)(VLK_MEMBER_DEVICE, swapchainCount, pSwapchains, pMetadata);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetSwapchainStatusKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetSwapchainStatusKHR)(VkSwapchainKHR swapchain){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetSwapchainStatusKHR)(VLK_MEMBER_DEVICE, swapchain);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetRefreshCycleDurationGOOGLE)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetRefreshCycleDurationGOOGLE)(VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetRefreshCycleDurationGOOGLE)(VLK_MEMBER_DEVICE, swapchain, pDisplayTimingProperties);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetPastPresentationTimingGOOGLE)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetPastPresentationTimingGOOGLE)(VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetPastPresentationTimingGOOGLE)(VLK_MEMBER_DEVICE, swapchain, pPresentationTimingCount, pPresentationTimings);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetBufferMemoryRequirements2KHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkGetBufferMemoryRequirements2KHR)(const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkGetBufferMemoryRequirements2KHR)(VLK_MEMBER_DEVICE, pInfo, pMemoryRequirements);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetImageMemoryRequirements2KHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkGetImageMemoryRequirements2KHR)(const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkGetImageMemoryRequirements2KHR)(VLK_MEMBER_DEVICE, pInfo, pMemoryRequirements);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetImageSparseMemoryRequirements2KHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkGetImageSparseMemoryRequirements2KHR)(const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkGetImageSparseMemoryRequirements2KHR)(VLK_MEMBER_DEVICE, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateSamplerYcbcrConversionKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateSamplerYcbcrConversionKHR)(const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateSamplerYcbcrConversionKHR)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pYcbcrConversion);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroySamplerYcbcrConversionKHR)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroySamplerYcbcrConversionKHR)(VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroySamplerYcbcrConversionKHR)(VLK_MEMBER_DEVICE, ycbcrConversion, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkCreateValidationCacheEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkCreateValidationCacheEXT)(const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkCreateValidationCacheEXT)(VLK_MEMBER_DEVICE, pCreateInfo, pAllocator, pValidationCache);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkDestroyValidationCacheEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline void VLK_EXT_DECL_DEVICE_MEMBER(vkDestroyValidationCacheEXT)(VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator){
        VLK_EXT_IMPL_DEVICE_MEMBER(vkDestroyValidationCacheEXT)(VLK_MEMBER_DEVICE, validationCache, pAllocator);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetValidationCacheDataEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkGetValidationCacheDataEXT)(VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkGetValidationCacheDataEXT)(VLK_MEMBER_DEVICE, validationCache, pDataSize, pData);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkMergeValidationCachesEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_DEVICE_MEMBER(vkMergeValidationCachesEXT)(VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches){
        return VLK_EXT_IMPL_DEVICE_MEMBER(vkMergeValidationCachesEXT)(VLK_MEMBER_DEVICE, dstCache, srcCacheCount, pSrcCaches);
    }
#   endif

    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceProperties)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceMemoryProperties)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceFeatures)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceFormatProperties)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceImageFormatProperties)
    VLK_EXPORTED_FUNCTION(vkCreateDevice)
    VLK_EXPORTED_FUNCTION(vkEnumerateDeviceLayerProperties)
    VLK_EXPORTED_FUNCTION(vkEnumerateDeviceExtensionProperties)
    VLK_EXPORTED_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties)
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceDisplayPropertiesKHR)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceDisplayPropertiesKHR)(physicalDevice, pPropertyCount, pProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceDisplayPlanePropertiesKHR)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceDisplayPlanePropertiesKHR)(physicalDevice, pPropertyCount, pProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetDisplayPlaneSupportedDisplaysKHR)(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetDisplayPlaneSupportedDisplaysKHR)(physicalDevice, planeIndex, pDisplayCount, pDisplays);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetDisplayModePropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetDisplayModePropertiesKHR)(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetDisplayModePropertiesKHR)(physicalDevice, display, pPropertyCount, pProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkCreateDisplayModeKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkCreateDisplayModeKHR)(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkCreateDisplayModeKHR)(physicalDevice, display, pCreateInfo, pAllocator, pMode);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetDisplayPlaneCapabilitiesKHR)(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetDisplayPlaneCapabilitiesKHR)(physicalDevice, mode, planeIndex, pCapabilities);
    }
#   endif

#ifdef VK_USE_PLATFORM_MIR_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceMirPresentationSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkBool32 VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMirPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, MirConnection* connection){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMirPresentationSupportKHR)(physicalDevice, queueFamilyIndex, connection);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceSupportKHR)(physicalDevice, queueFamilyIndex, surface, pSupported);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)(physicalDevice, surface, pSurfaceCapabilities);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceFormatsKHR)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceFormatsKHR)(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfacePresentModesKHR)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfacePresentModesKHR)(physicalDevice, surface, pPresentModeCount, pPresentModes);
    }
#   endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceWaylandPresentationSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkBool32 VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceWaylandPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceWaylandPresentationSupportKHR)(physicalDevice, queueFamilyIndex, display);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceWin32PresentationSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkBool32 VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceWin32PresentationSupportKHR)(physicalDevice, queueFamilyIndex);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceXlibPresentationSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkBool32 VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceXlibPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceXlibPresentationSupportKHR)(physicalDevice, queueFamilyIndex, dpy, visualID);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceXcbPresentationSupportKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkBool32 VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceXcbPresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceXcbPresentationSupportKHR)(physicalDevice, queueFamilyIndex, connection, visual_id);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalImageFormatPropertiesNV)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalImageFormatPropertiesNV)(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalImageFormatPropertiesNV)(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX)(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX* pFeatures, VkDeviceGeneratedCommandsLimitsNVX* pLimits){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX)(physicalDevice, pFeatures, pLimits);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceFeatures2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceFeatures2KHR)(physicalDevice, pFeatures);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceProperties2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceProperties2KHR)(physicalDevice, pProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceFormatProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceFormatProperties2KHR)(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceFormatProperties2KHR)(physicalDevice, format, pFormatProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceImageFormatProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceImageFormatProperties2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceImageFormatProperties2KHR)(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceQueueFamilyProperties2KHR)(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceQueueFamilyProperties2KHR)(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMemoryProperties2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMemoryProperties2KHR)(physicalDevice, pMemoryProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSparseImageFormatProperties2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSparseImageFormatProperties2KHR)(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalBufferPropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalBufferPropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalBufferPropertiesKHR)(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalFencePropertiesKHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalFencePropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceExternalFencePropertiesKHR)(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkReleaseDisplayEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkReleaseDisplayEXT)(VkPhysicalDevice physicalDevice, VkDisplayKHR display){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkReleaseDisplayEXT)(physicalDevice, display);
    }
#   endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
    VLK_EXT_INSTANCE_FUNCTION(vkAcquireXlibDisplayEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkAcquireXlibDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkAcquireXlibDisplayEXT)(physicalDevice, dpy, display);
    }
#   endif
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
    VLK_EXT_INSTANCE_FUNCTION(vkGetRandROutputDisplayEXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetRandROutputDisplayEXT)(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetRandROutputDisplayEXT)(physicalDevice, dpy, rrOutput, pDisplay);
    }
#   endif
#endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilities2EXT)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilities2EXT)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilities2EXT)(physicalDevice, surface, pSurfaceCapabilities);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetPhysicalDevicePresentRectanglesKHX)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDevicePresentRectanglesKHX)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDevicePresentRectanglesKHX)(physicalDevice, surface, pRectCount, pRects);
    }
#   endif

    VLK_EXT_DEVICE_FUNCTION(vkGetPhysicalDeviceMultisamplePropertiesEXT)
#   if defined(VLK_EXT_DEVICE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline void VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMultisamplePropertiesEXT)(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties){
        VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceMultisamplePropertiesEXT)(physicalDevice, samples, pMultisampleProperties);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilities2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilities2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceCapabilities2KHR)(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
    }
#   endif

    VLK_EXT_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormats2KHR)
#   if defined(VLK_EXT_INSTANCE_MEMBER) && defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)
    inline VkResult VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceFormats2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats){
        return VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(vkGetPhysicalDeviceSurfaceFormats2KHR)(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
    }
#   endif


#undef VLK_EXPORTED_FUNCTION
#undef VLK_INSTANCE_FUNCTION
#undef VLK_DEVICE_FUNCTION
#undef VLK_PHYSICALDEVICE_FUNCTION

#undef VLK_EXT_EXPORTED_FUNCTION
#undef VLK_EXT_INSTANCE_FUNCTION
#undef VLK_EXT_DEVICE_FUNCTION
#undef VLK_EXT_PHYSICALDEVICE_FUNCTION

#undef VLK_EXT_DECL_EXPORTED_MEMBER
#undef VLK_EXT_IMPL_EXPORTED_MEMBER

#undef VLK_EXT_DECL_INSTANCE_MEMBER
#undef VLK_EXT_IMPL_INSTANCE_MEMBER
#undef VLK_MEMBER_INSTANCE

#undef VLK_EXT_DECL_DEVICE_MEMBER
#undef VLK_EXT_IMPL_DEVICE_MEMBER
#undef VLK_MEMBER_DEVICE

#undef VLK_EXT_DECL_PHYSICALDEVICE_MEMBER
#undef VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER
#undef VLK_MEMBER_PHYSICALDEVICE

#undef VLK_EXT_EXPORTED_MEMBER
#undef VLK_EXT_INSTANCE_MEMBER
#undef VLK_EXT_DEVICE_MEMBER
#undef VLK_EXT_PHYSICALDEVICE_MEMBER

