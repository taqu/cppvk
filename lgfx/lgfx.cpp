/**
@file lgfx.cpp
@author t-sakai
@date 2018/09/19 create
*/
#include "lgfx.h"

#define LGFX_WINDOW_IMPLEMENTATION
#include "Window.h"

#ifdef LGFX_VULKAN
#include "lgfx_vulkan.h"
#endif

namespace lgfx
{
#ifdef LGFX_VULKAN
    //--------------------------------------------------------------
    //---
    //--- Handle
    //---
    //--------------------------------------------------------------
    static_assert(lgfx::is_trivially_copyable<Handle>::value == true, "Handle must be trivially copyable");

    Handle Handle::allocate(s32 device, void* resource)
    {
        return ResourceTable::instance().pop(device, resource);
    }

    void Handle::release(Handle& handle)
    {
        ResourceTable::instance().push(handle);
        handle.handle_ = -1;
    }

    s32 Handle::count() const
    {
        return ResourceTable::instance()[handle_].count_;
    }

    s32 Handle::device() const
    {
        return ResourceTable::instance()[handle_].device_;
    }

    s32 Handle::inc()
    {
        s32& count = ResourceTable::instance()[handle_].count_;
        ++count;
        return count;
    }

    s32 Handle::dec()
    {
        s32& count = ResourceTable::instance()[handle_].count_;
        --count;
        return count;
    }

    void Handle::swap(Handle& rhs)
    {
        lgfx::swap(handle_, rhs.handle_);
    }

    //--------------------------------------------------------------
    //---
    //--- ResourceTable
    //---
    //--------------------------------------------------------------
    ResourceTable ResourceTable::instance_;

    void ResourceTable::initialize()
    {
    }

    void ResourceTable::terminate()
    {
        instance_.destroy();
    }

    ResourceTable::ResourceTable()
        :capacity_(0)
        , size_(0)
        , freeList_(-1)
        , entries_(LGFX_NULL)
    {}

    ResourceTable::~ResourceTable()
    {
        destroy();
    }

    void ResourceTable::destroy()
    {
        LGFX_FREE(entries_);
        freeList_ = -1;
        size_ = 0;
        capacity_ = 0;
    }

    Handle ResourceTable::pop(s32 device, void* resource)
    {
        LGFX_ASSERT(LGFX_NULL != resource);
        if(capacity_<=size_){
            //Expand the table
            LGFX_ASSERT(-1==freeList_);
            s32 newCapacity = capacity_ + ExpandSize;
            Entry* entries = reinterpret_cast<Entry*>(LGFX_MALLOC(sizeof(Entry)*newCapacity));
            memcpy(entries, entries_, sizeof(Entry)*capacity_);
            for(s32 i=capacity_; i<newCapacity; ++i){
                entries[i].next_ = i+1;
            }
            freeList_ = capacity_;
            entries[newCapacity-1].next_ = -1;
            LGFX_FREE(entries_);
            capacity_ = newCapacity;
            entries_ = entries;
        }

        LGFX_ASSERT(0<=freeList_ && freeList_<capacity_);
        ++size_;
        s32 index = freeList_;
        freeList_ = entries_[freeList_].next_;
        entries_[index].refCounted_.resource_ = resource;
        entries_[index].refCounted_.count_ = 1;
        entries_[index].refCounted_.device_ = device;
        return Handle::create(index);
    }

    void ResourceTable::push(Handle handle)
    {
        LGFX_ASSERT(0<size_ && size_<capacity_);
        LGFX_ASSERT(0<=handle.handle() && handle.handle()<size_);
        LGFX_ASSERT(LGFX_NULL != entries_[handle.handle()].refCounted_.resource_);
        s32 index = handle.handle();
        --size_;
        entries_[index].next_ = freeList_;
        freeList_ = index;
    }
#endif
}
