#include <stdio.h>
#define LGFX_IMPLEMENTATION
#include "lgfx.h"

int main(int /*argc*/, char** /*argv*/)
{
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

        builder.instanceCreateInfo_ ={
            "Tutorial Vulkan", //application name
            VK_MAKE_VERSION(1,0,0), //application version
            "Tutorial Engine", //engine name
            VK_MAKE_VERSION(1,0,0), //engine version
            VK_API_VERSION_1_0, //api version

            0, //enabled layer count
            {LGFX_NULL}, //enabled layer names
            LGFX_NULL,
        };
        builder.deviceCreateInfo_ ={
            0,
            {true, true, true, false, false},
            0,
            {LGFX_NULL},
            LGFX_NULL,
        };

        builder.surfaceCreateInfo_ ={
            0,
            window.getInstance(),
            window.getHandle(),
        };

        lgfx::Window::Vector2 viewSize = window.getViewSize();
        builder.swapchainCreateInfo_ ={
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

        while(window.peekEvent()){
            Sleep(16);
        }
    }
    lgfx::System::terminate();
    window.destroy();
    return EXIT_SUCCESS;
}
