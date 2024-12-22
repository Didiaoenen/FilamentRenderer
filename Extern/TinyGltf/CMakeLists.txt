
FetchContent_Declare(tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG release
)

FetchContent_MakeAvailable(tinygltf)

set_target_properties(
    tinygltf
    loader_example
    PROPERTIES FOLDER "Third-party/tinygltf"
)

set_target_properties(
    tinygltf
    loader_example
    PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)