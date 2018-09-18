cmake_minimum_required(VERSION 3.6)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

set(ProjectName lgfx)
project(${ProjectName})

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR})

set(OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

# Check using API
if(NOT (DEFINED LGFX_API))
    set(LGFX_API LGFX_VULKAN)
endif()

if(${LGFX_API} STREQUAL "LGFX_VULKAN")
    set(LGFX_VULKAN ON)
endif()

if(MSVC)
    set(DEFAULT_CXX_FLAGS "/DWIN32 /D_WINDOWS /D_MBCS /DCPPVK_USE_PLATFORM_WIN32_KHR /D${LGFX_API} /W4 /WX- /nologo /fp:precise /arch:AVX /Zc:wchar_t /TP /Gd")
    if("1800" VERSION_LESS MSVC_VERSION)
        set(DEFAULT_CXX_FLAGS "${DEFAULT_CXX_FLAGS} /EHsc")
    endif()

elseif(UNIX)
    find_package(XCB)
    find_package(XLIB)
    set(DEFAULT_CXX_FLAGS "-Wall -O2 -std=c++11 -march=native")
elseif(APPLE)
endif()

add_subdirectory(sample00)
add_subdirectory(sample01)
#add_subdirectory(sample02)
