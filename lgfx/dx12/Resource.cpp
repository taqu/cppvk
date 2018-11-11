/**
@file Resource.cpp
@author t-sakai
@date 2018/10/21 create
*/
#include "lgfx.h"

namespace lgfx
{
    void VertexBuffer::unmap(u32 subresource, const Range* range)
    {
        handle_->Unmap(subresource, reinterpret_cast<const D3D12_RANGE*>(range));
    }
}
