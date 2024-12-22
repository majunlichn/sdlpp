cmake_minimum_required(VERSION 3.10)

if ((NOT DEFINED CMAKE_TOOLCHAIN_FILE) AND (DEFINED ENV{VCPKG_ROOT}))
    list(APPEND CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()
message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

project(sdlpp)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(SDLPP_SUBPROJECT OFF)
else()
    set(SDLPP_SUBPROJECT ON)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(USE_STATIC_CRT OFF CACHE BOOL "Link against the static runtime libraries." FORCE)
include(imported/radcpp/cmake/CompilerOptions.cmake)
include(imported/radcpp/cmake/Sanitizers.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SDLPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

if (NOT TARGET rad)
    add_subdirectory(imported/radcpp)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
        set(PLATFORM_NAME "x64-windows")
    endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(PLATFORM_NAME "x64-linux")
    endif()
endif()

set(SDL3_DIR "$ENV{RADSDK_ROOT}/${PLATFORM_NAME}/SDL/installed/cmake")
if (NOT (EXISTS ${SDL3_DIR}))
    set(SDL3_DIR "$ENV{RADSDK_ROOT}/${PLATFORM_NAME}/SDL/installed/lib/cmake/SDL3")
endif()
set(SDL3_mixer_DIR "$ENV{RADSDK_ROOT}/${PLATFORM_NAME}/SDL_mixer/installed/cmake")
if (NOT (EXISTS ${SDL3_mixer_DIR}))
    set(SDL3_mixer_DIR "$ENV{RADSDK_ROOT}/${PLATFORM_NAME}/SDL_mixer/installed/lib/cmake/SDL3_mixer")
endif()
message(SDL3_DIR=${SDL3_DIR})
message(SDL3_mixer_DIR=${SDL3_mixer_DIR})

find_package(SDL3 CONFIG REQUIRED PATHS "${SDL3_DIR}" NO_DEFAULT_PATH)
find_package(SDL3_mixer CONFIG REQUIRED PATHS "${SDL3_mixer_DIR}" NO_DEFAULT_PATH)

add_subdirectory(imported/imgui)
add_subdirectory(sdlpp)

if (NOT ${SDLPP_SUBPROJECT})
    add_subdirectory(samples/WindowTest)
endif()
