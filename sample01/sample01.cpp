#include <stdio.h>
#include "cppvk.h"
#include "Window.h"

bool checkInstanceExtensions(const VkExtensionProperties& properties);
bool checkDeviceExtensions(const VkExtensionProperties& properties);
//void checkQueueFamilies(cppvk::u32 queueFamilyIndices[cppvk::QueueType_Max], cppvk::u32 numQueueFamilies, VkQueueFamilyProperties* queueFamilyProperties, const bool* queueFamilyPresentationSupports);
bool checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported);
//bool checkSurfaceFormats(VkSurfaceFormatKHR& dst, cppvk::u32 size, const VkSurfaceFormatKHR* formats);
bool checkSurfaceCapabilities(VkImageUsageFlags& imageUsageFlags, VkSurfaceTransformFlagBitsKHR& preTransform, VkCompositeAlphaFlagBitsKHR& compsiteAlpha, const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

int main(int /*argc*/, char** /*argv*/)
{
    lgfx::Window window;
    {
        HINSTANCE hInstance = CPPVK_NULL;
        if(FALSE == GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &hInstance)){
            return 0;
        }
        lgfx::Window::InitParam initParam = {
            hInstance,
            400,
            300,
            0,0,
            CPPVK_NULL,
            "Tutorial",
            true,
        };
        if(!window.create(initParam)){
            return 0;
        }
    }

    // Create instance
    //---------------------------------------------------------------------
    {
        //Load library
        cppvk::System system;
        if(!system.initialize()){
            fprintf(stderr, "Fail to initialize lib\n");
            return 0;
        }

        printf("Create Instance\n");
        cppvk::InstanceCreateInfo instanceCreateInfo = {
            "Tutorial Vulkan", //application name
            VK_MAKE_VERSION(1,0,0), //application version
            "Tutorial Engine", //engine name
            VK_MAKE_VERSION(1,0,0), //engine version
            VK_API_VERSION_1_0, //api version

            0, //enabled layer count
            {CPPVK_NULL}, //enabled layer names
            checkInstanceExtensions,
        };

        cppvk::SurfaceCreateInfo surfaceCreateInfo = {
            0,
            window.getInstance(),
            window.getHandle(),
        };

        if(!system.createInstance(instanceCreateInfo, surfaceCreateInfo, CPPVK_NULL, CPPVK_NULL)){
            fprintf(stderr, "Fail to create instance\n");
            return 0;
        }

        cppvk::DeviceCreateInfo deviceCreateInfo = {
            {true, true, true, false, false},
            0,
            {CPPVK_NULL},
            CPPVK_NULL,
            checkDeviceExtensions,
            checkDeviceFeatures,
        };

        cppvk::SwapchainCreateInfo swapchainCreateInfo = {
            true,
            2,
            VK_PRESENT_MODE_MAILBOX_KHR,
            {400, 300},
            CPPVK_NULL,
            CPPVK_NULL,
        };
        if(!system.createDevice(0, deviceCreateInfo, swapchainCreateInfo, CPPVK_NULL, CPPVK_NULL)){
            fprintf(stderr, "Fail to create device\n");
            return 0;
        }
        system.terminate();
    }

    return 0;
}

bool checkInstanceExtensions(const VkExtensionProperties& properties)
{
    printf(" %s\n", properties.extensionName);
    return true;
}

bool checkDeviceExtensions(const VkExtensionProperties& properties)
{
    printf(" %s\n", properties.extensionName);
    return true;
}

bool checkDeviceFeatures(VkPhysicalDeviceFeatures& dst, const VkPhysicalDeviceFeatures& supported)
{
    dst = supported;
    return true;
}

bool checkSurfaceCapabilities(VkImageUsageFlags& imageUsageFlags, VkSurfaceTransformFlagBitsKHR& preTransform, VkCompositeAlphaFlagBitsKHR& compsiteAlpha, const VkSurfaceCapabilitiesKHR& surfaceCapabilities)
{
    return true;
}
