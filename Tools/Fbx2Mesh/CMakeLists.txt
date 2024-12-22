project(Fbx2Mesh CXX)

set(TARGET Fbx2Mesh)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

file(GLOB_RECURSE LIBS
${HDR_DIR}/../Dependencies/fbxsdk/lib/x64/debug/alembic-mt.lib
${HDR_DIR}/../Dependencies/fbxsdk/lib/x64/debug/libfbxsdk-mt.lib
${HDR_DIR}/../Dependencies/fbxsdk/lib/x64/debug/libxml2-mt.lib
${HDR_DIR}/../Dependencies/fbxsdk/lib/x64/debug/zlib-mt.lib
)

add_executable(${TARGET} ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/fbxsdk/include)

target_link_libraries(${TARGET} PRIVATE ozz_base ozz_animation ozz_options ozz_animation_fbx ozz_animation_offline ozzmesh ${LIBS})

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=${HDR_DIR}/../Dependencies/fbxsdk/lib/x64/*.dll;${PATH}")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

set_target_properties(${TARGET} PROPERTIES FOLDER "Tools")

# --file=./xxx.fbx --skeleton=./xxx.ozz --mesh=xxx.ozz