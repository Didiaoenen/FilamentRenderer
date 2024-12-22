
FetchContent_Declare(ozz-animation
    GIT_REPOSITORY https://github.com/guillaumeblanc/ozz-animation.git
    GIT_TAG master
)

# set(ozz_build_tools OFF CACHE BOOL "")
set(ozz_build_samples OFF CACHE BOOL "")
set(ozz_build_howtos OFF CACHE BOOL "")
set(ozz_build_tests OFF CACHE BOOL "")

set(FBX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk)

set(FBX_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/release/libfbxsdk-mt.lib)
set(FBX_LIB_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/debug/libfbxsdk-mt.lib)
set(XML_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/release/libxml2-mt.lib)
set(XML_LIB_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/debug/libxml2-mt.lib)
set(Z_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/release/zlib-mt.lib)
set(Z_LIB_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/debug/zlib-mt.lib)

set(FBX_SHARED_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/release/libfbxsdk.dll)
set(FBX_SHARED_LIB_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/Dependencies/fbxsdk/lib/x64/debug/libfbxsdk.dll)

FetchContent_MakeAvailable(ozz-animation)

set_target_properties(
    BUILD_FUSE_ozz_animation
    BUILD_FUSE_ozz_animation_fbx
    BUILD_FUSE_ozz_animation_offline
    BUILD_FUSE_ozz_animation_tools
    BUILD_FUSE_ozz_base
    BUILD_FUSE_ozz_geometry
    BUILD_FUSE_ozz_options
    BUILD_FUSE_ALL
    PROPERTIES FOLDER "Third-party/ozz/fuse"
)

set_target_properties(
    dump2ozz
    fbx2ozz
    gltf2ozz
    ozz_animation_tools
    PROPERTIES FOLDER "Third-party/ozz/tools"
)

set_target_properties(
    json
    PROPERTIES FOLDER "Third-party/ozz/extern"
)

set_target_properties(
    BUILD_DATA
    PROPERTIES FOLDER "CMakePredefinedTargets"
)

set_target_properties(
    ozz_base
    ozz_animation
    ozz_animation_fbx
    ozz_animation_offline
    ozz_geometry
    ozz_options
    PROPERTIES FOLDER "Third-party/ozz"
)

set_target_properties(
    ozz_base
    ozz_animation
    ozz_animation_fbx
    ozz_animation_offline
    ozz_geometry
    ozz_options

    dump2ozz
    fbx2ozz
    gltf2ozz
    ozz_animation_tools

    json

    PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)