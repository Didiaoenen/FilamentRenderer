
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
)

FetchContent_MakeAvailable(spdlog)

set_target_properties(
    spdlog
    PROPERTIES FOLDER "Third-party"
)

set_target_properties(
    spdlog
    PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)