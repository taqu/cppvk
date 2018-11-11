cmake_minimum_required(VERSION 3.12)

function(expand_files FILES SOURCE)
    file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE})
    set(${FILES} ${SOURCES} PARENT_SCOPE)
endfunction(expand_files)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

set(ProjectName lgfx)
project(${ProjectName})

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR})

set(LGFX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lgfx")
set(LAPP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lapp")
include_directories(AFTER ${LGFX_SOURCE_DIR})
include_directories(AFTER ${LAPP_SOURCE_DIR})

set(OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

add_library(WINMMLIB MODULE IMPORTED)
add_library(XINPUT MODULE IMPORTED)
add_library(DINPUTLIB MODULE IMPORTED)
add_library(IMMLIB MODULE IMPORTED)
set_target_properties(WINMMLIB PROPERTIES IMPORTED_LOCATION "winmm.lib")
set_target_properties(XINPUT PROPERTIES IMPORTED_LOCATION "xinput.lib")
set_target_properties(DINPUTLIB PROPERTIES IMPORTED_LOCATION "dinput8.lib")
set_target_properties(IMMLIB PROPERTIES IMPORTED_LOCATION "imm32.lib")

# Check using API
if(NOT (DEFINED LGFX_API))
    set(LGFX_API LGFX_DX12)
    #set(LGFX_API LGFX_VULKAN)
endif()

if("${LGFX_API}" STREQUAL "LGFX_DX12")
    set(LGFX_DX12 ON)
    set(LGFX_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lgfx/dx12")
    set(LGFX_API_NAME "dx12")
    add_library(DXGI MODULE IMPORTED)
    add_library(DX12 MODULE IMPORTED)
    set_target_properties(DXGI PROPERTIES IMPORTED_LOCATION_DEBUG "dxgi.lib" IMPORTED_LOCATION_RELEASE "dxgi.lib")
    set_target_properties(DX12 PROPERTIES IMPORTED_LOCATION_DEBUG "d3d12.lib" IMPORTED_LOCATION_RELEASE "d3d12.lib")

endif()

if("${LGFX_API}" STREQUAL "LGFX_VULKAN")
    set(LGFX_VULKAN ON)
    set(LGFX_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lgfx/vulkan")
    set(LGFX_API_NAME "vulkan")
endif()

if(MSVC)
    set(DEFAULT_CXX_FLAGS "/DWIN32 /D_WINDOWS /D_MBCS /DLGFX_USE_WIN32 /D${LGFX_API} /W4 /WX- /nologo /fp:precise /arch:AVX /Zc:wchar_t /TP /Gd")
    if("1800" VERSION_LESS MSVC_VERSION)
        set(DEFAULT_CXX_FLAGS "${DEFAULT_CXX_FLAGS} /EHsc")
    endif()

elseif(UNIX)
    find_package(XCB)
    find_package(XLIB)
    set(DEFAULT_CXX_FLAGS "-Wall -std=c++11 -march=native")
elseif(APPLE)
endif()

add_subdirectory(sample00)
add_subdirectory(sample01)
#add_subdirectory(sample02)
