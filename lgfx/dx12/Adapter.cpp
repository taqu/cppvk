/**
@file Adapter.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    Adapter Adapter::create(Factory& factory, FeatureLevel featureLevel)
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
        IDXGIFactory6* factory6 = LGFX_NULL;
        factory->QueryInterface(IID_PPV_ARGS(&factory6));

        handle_type adapter = LGFX_NULL;
        if(LGFX_NULL != factory6){
            for(u32 i=0; DXGI_ERROR_NOT_FOUND != factory6->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)); ++i){
                DXGI_ADAPTER_DESC1 desc;
                adapter->GetDesc1(&desc);
                if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE){
                    continue;
                }
                //Check if the adapter supports Direct3D 12
                if(SUCCEEDED(D3D12CreateDevice(adapter, static_cast<D3D_FEATURE_LEVEL>(featureLevel), _uuidof(ID3D12Device), LGFX_NULL))){
                    break;
                }
                adapter->Release();
                adapter = LGFX_NULL;
            }

        }else{
            for(u32 i=0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(i, &adapter); ++i){
                DXGI_ADAPTER_DESC1 desc;
                adapter->GetDesc1(&desc);
                if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE){
                    continue;
                }
                //Check if the adapter supports Direct3D 12
                if(SUCCEEDED(D3D12CreateDevice(adapter, static_cast<D3D_FEATURE_LEVEL>(featureLevel), _uuidof(ID3D12Device), LGFX_NULL))){
                    break;
                }
                adapter->Release();
                adapter = LGFX_NULL;
            }
        }
        LGFX_SAFE_RELEASE(factory6);
        return lgfx::move(Adapter(adapter));
    }
}
