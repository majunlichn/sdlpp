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

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SDLPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

if (NOT TARGET rad)
    add_subdirectory(imported/radcpp)
endif()

find_package(SDL3 CONFIG REQUIRED PATHS ${SDLPP_ROOT}/imported/installed/SDL)
find_package(SDL3_mixer CONFIG REQUIRED PATHS ${SDLPP_ROOT}/imported/installed/SDL_mixer)

add_subdirectory(imported/imgui)
add_subdirectory(sdlpp)

if (NOT ${SDLPP_SUBPROJECT})
    add_subdirectory(samples/WindowTest)
endif()
