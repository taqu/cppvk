/**
@file SwapChain.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    SwapChain SwapChain::create(
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
        MWA mwaFlags)
    {
        LGFX_ASSERT(0<=width);
        LGFX_ASSERT(0<=height);

        //struct DXGI_SWAP_CHAIN_FULLSCREEN_DESC
        //{
        //    DXGI_RATIONAL RefreshRate;
        //    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
        //    DXGI_MODE_SCALING Scaling;
        //    BOOL Windowed;
        //}

        //DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc =
        //{
        //};
        DXGI_SWAP_CHAIN_DESC1 desc =
        {
            static_cast<u32>(width),
            static_cast<u32>(height),
            static_cast<DXGI_FORMAT>(format),
            FALSE,
            {1, 0}, //DXGI_SAMPLE_DESC
            static_cast<DXGI_USAGE>(usage),
            count,
            static_cast<DXGI_SCALING>(Scaling_Stretch),
            static_cast<DXGI_SWAP_EFFECT>(swapEffect),
            static_cast<DXGI_ALPHA_MODE>(AlphaMode_Unspecified),
            flags,
        };

        handle_type swapChain = LGFX_NULL;
        IDXGISwapChain1* swapChain1 = LGFX_NULL;
        if(SUCCEEDED(factory->CreateSwapChainForHwnd(commandQueue, window, &desc, LGFX_NULL, LGFX_NULL, &swapChain1))){
            swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
            swapChain1->Release();
            if(LGFX_NULL != swapChain){
                factory->MakeWindowAssociation(window, mwaFlags);
                return lgfx::move(SwapChain(swapChain));
            }
        }
        return lgfx::move(SwapChain());
    }
}
