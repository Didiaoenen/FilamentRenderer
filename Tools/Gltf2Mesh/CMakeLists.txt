project(Gltf2Mesh CXX)

set(TARGET Gltf2Mesh)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_executable(${TARGET} ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

target_link_libraries(${TARGET} PRIVATE ozz_base ozz_animation ozz_options ozzmesh tinygltf)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

set_target_properties(${TARGET} PROPERTIES FOLDER "Tools")
