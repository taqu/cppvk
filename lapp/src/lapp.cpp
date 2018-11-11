/**
@file lapp.cpp
@author t-sakai
@date 2018/10/30 create
*/
#include "lapp.h"
#include <stdarg.h>

namespace lapp
{
    void printDebug(const Char* format, ...)
    {
        va_list args;
        va_start(args, format);
        static const size_t Size = 256;
        Char buffer[Size];
#if _WIN32
        s32 len = vsnprintf_s(buffer, Size-1, format, args);
#else
        s32 len = vsnprintf(buffer, Size-1, format, args);
#endif
        va_end(args);
        if(len<=0){
            return;
        }
        buffer[len] = '\0';
#if _WIN32
        OutputDebugString(buffer);
#else
        puts(buffer);
#endif
    }
}
