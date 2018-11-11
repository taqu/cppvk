/**
@file Blob.cpp
@author t-sakai
@date 2018/10/26 create
*/
#include "lgfx.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#endif

namespace lgfx
{
    Blob Blob::loadFileAll(const Char* filepath)
    {
        LGFX_ASSERT(LGFX_NULL != filepath);

#ifdef _WIN32
        HANDLE file = CreateFile(
            filepath,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if(INVALID_HANDLE_VALUE == file){
            return lgfx::move(Blob());
        }
        LARGE_INTEGER size;
        if(!GetFileSizeEx(file, &size)){
            CloseHandle(file);
            return lgfx::move(Blob());
        }
        u8* buffer = LGFX_NEW u8[size.QuadPart];

        s64 total = 0;
        while(total<size.QuadPart){
            DWORD numBytesRead = 0;
            if(!ReadFile(file, buffer, size.LowPart, &numBytesRead, LGFX_NULL)){
                LGFX_DELETE_ARRAY(buffer);
                CloseHandle(file);
                return lgfx::move(Blob());
            }
            total += numBytesRead;
        }
        CloseHandle(file);
        LGFX_ASSERT(total == size.QuadPart);
        return lgfx::move(Blob(IBlob::create(size.QuadPart, buffer)));

#else
        FILE* file = fopen(filepath, "rb");
        if(LGFX_NULL == file){
            return lgfx::move(Blob());
        }
        fclose(file);

        s32 fd = fileno(file);
        stat64 size;
        if(fd<0 || fstat64(fd, &size)<0){
            fclose(file);
            return lgfx::move(Blob());
        }
        u8* buffer = LGFX_NEW u8[size.st_size];

        size_t total = fread(buffer, size.st_size, 1, file);
        if(total<=0){
            LGFX_DELETE_ARRAY(buffer);
            fclose(file);
            return lgfx::move(Blob());
        }
        fclose(file);
        return lgfx::move(Blob(IBlob::create(size.st_size, buffer)));
#endif
    }
}
