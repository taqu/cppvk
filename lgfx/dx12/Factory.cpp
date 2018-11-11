/**
@file Factory.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    Factory Factory::create()
    {
        u32 debugFlags = 0;
#ifdef _DEBUG
        ID3D12Debug* debug = LGFX_NULL;
        if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))){
            debug->EnableDebugLayer();
            debugFlags |= DXGI_CREATE_FACTORY_DEBUG;
            debug->Release();
        }
#endif
        handle_type factory = LGFX_NULL;
        return SUCCEEDED(CreateDXGIFactory2(debugFlags, IID_PPV_ARGS(&factory)))
            ? lgfx::move(Factory(factory))
            : lgfx::move(Factory());
    }
}
