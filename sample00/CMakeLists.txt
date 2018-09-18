cmake_minimum_required(VERSION 3.6)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

set(ProjectName sample00)
project(${ProjectName})

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS "../vk_platform.h;../vulkan.h;../cppvk_config.h;../cppvk.h;../Window.h")
set(SOURCES "../cppvk.cpp;../Window.cpp;sample00.cpp")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

set(FILES ${HEADERS} ${SOURCES})

add_executable(${ProjectName} ${FILES})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${DEFAULT_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /DMU3_EXPORTS /MTd /Zi /Ob0 /Od /RTC1 /Gy /GR- /GS /Gm-")
    set(CMAKE_CXX_FLAGS_RELEASE "/DMU3_EXPORTS /MT /O2 /GL /GR- /DNDEBUG")

elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${DEFAULT_CXX_FLAGS}")
elseif(APPLE)
endif()

set_target_properties(${ProjectName} PROPERTIES OUTPUT_NAME_DEBUG "${ProjectName}" OUTPUT_NAME_RELEASE "${ProjectName}")
