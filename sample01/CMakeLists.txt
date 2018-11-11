cmake_minimum_required(VERSION 3.12)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

set(ProjectName sample01)
project(${ProjectName})

expand_files(COMMON_HEADERS "${LGFX_SOURCE_DIR}/*.h")
expand_files(COMMON_SOURCES "${LGFX_SOURCE_DIR}/*.cpp")
source_group("lgfx\\include" FILES ${COMMON_HEADERS})
source_group("lgfx\\src" FILES ${COMMON_SOURCES})

expand_files(API_HEADERS "${LGFX_API_DIR}/*.h")
expand_files(API_SOURCES "${LGFX_API_DIR}/*.cpp")
source_group("lgfx\\include\\${LGFX_API_NAME}" FILES ${API_HEADERS})
source_group("lgfx\\src\\${LGFX_API_NAME}" FILES ${API_SOURCES})

set(SOURCES "sample01.cpp")
source_group("src" FILES ${SOURCES})

set(FILES ${COMMON_HEADERS} ${COMMON_SOURCES} ${API_HEADERS} ${API_SOURCES} ${SOURCES})
add_executable(${ProjectName} ${FILES})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${DEFAULT_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1 /Gy /GR- /GS /Gm-")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /GL /GR- /DNDEBUG")
    if("${LGFX_API}" STREQUAL "LGFX_DX12")
        target_link_libraries(${ProjectName} DX12 DXGI INPUTLIB IMMLIB)
    endif()

elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${DEFAULT_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")
elseif(APPLE)
endif()

set_target_properties(${ProjectName} PROPERTIES OUTPUT_NAME_DEBUG "${ProjectName}" OUTPUT_NAME_RELEASE "${ProjectName}")
