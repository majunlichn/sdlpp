cmake_minimum_required(VERSION 3.10)

if (DEFINED ENV{VCPKG_ROOT})
    list(APPEND CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()
message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

project(sdlpp)

option(SDLPP_BUILD_SAMPLES "Build samples." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SDLPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

if (NOT TARGET rad)
    add_subdirectory(imported/radcpp)
endif()
add_subdirectory(sdlpp)

if (SDLPP_BUILD_SAMPLES)
    add_subdirectory(samples/WindowTest)
endif()
