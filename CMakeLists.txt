cmake_minimum_required(VERSION 3.20)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

message(STATUS "TOOLCHAIN: ${CMAKE_TOOLCHAIN_FILE}")

project(FREditor)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

add_subdirectory(Extern)
add_subdirectory(Modules)
add_subdirectory(Tools)