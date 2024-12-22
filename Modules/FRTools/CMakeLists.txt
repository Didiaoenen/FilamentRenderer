project(FRTools CXX)

find_package(glm CONFIG REQUIRED)

set(TARGET FRTools)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS
${HDR_DIR}/*.h
${HDR_DIR}/*.inl
${HDR_DIR}/event/*.h
${HDR_DIR}/event/*.inl
${HDR_DIR}/geometry/*.h
${HDR_DIR}/geometry/*.inl
${HDR_DIR}/filesystem/*.h
${HDR_DIR}/filesystem/*.inl
${HDR_DIR}/message/*.h
${HDR_DIR}/message/*.inl
${HDR_DIR}/pathutils/*.h
${HDR_DIR}/pathutils/*.inl
${HDR_DIR}/platform/*.h
${HDR_DIR}/platform/*.inl
${HDR_DIR}/refvalue/*.h
${HDR_DIR}/refvalue/*.inl
${HDR_DIR}/service/*.h
${HDR_DIR}/service/*.inl
${HDR_DIR}/timer/*.h
${HDR_DIR}/timer/*.inl
)

file(GLOB_RECURSE SRCS
${SRC_DIR}/*.cpp
${SRC_DIR}/geometry/*.cpp
${SRC_DIR}/filesystem/*.cpp
${SRC_DIR}/pathutils/*.cpp
${SRC_DIR}/platform/*.cpp
${SRC_DIR}/timer/*.cpp
)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC
${HDR_DIR}
${HDR_DIR}/event
${HDR_DIR}/geometry
${HDR_DIR}/filesystem
${HDR_DIR}/message
${HDR_DIR}/pathutils
${HDR_DIR}/platform
${HDR_DIR}/refvalue
${HDR_DIR}/service
${HDR_DIR}/timer
)

target_link_libraries(${TARGET} PRIVATE glm::glm dearimgui filament spdlog ozz_base FRLog)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

file(GLOB_RECURSE EVENT_HEAD ${HDR_DIR}/event/*.h ${HDR_DIR}/event/*.inl)
file(GLOB_RECURSE EVENT_SRC ${SRC_DIR}/event/*.cpp)
source_group("Header Files/event" FILES ${EVENT_HEAD})
source_group("Source Files/event" FILES ${EVENT_SRC})

file(GLOB_RECURSE GEOMETRY_HEAD ${HDR_DIR}/geometry/*.h ${HDR_DIR}/geometry/*.inl)
file(GLOB_RECURSE GEOMETRY_SRC ${SRC_DIR}/geometry/*.cpp)
source_group("Header Files/geometry" FILES ${GEOMETRY_HEAD})
source_group("Source Files/geometry" FILES ${GEOMETRY_SRC})

file(GLOB_RECURSE FILESYSTEM_HEAD ${HDR_DIR}/filesystem/*.h ${HDR_DIR}/filesystem/*.inl)
file(GLOB_RECURSE FILESYSTEM_SRC ${SRC_DIR}/filesystem/*.cpp)
source_group("Header Files/filesystem" FILES ${FILESYSTEM_HEAD})
source_group("Source Files/filesystem" FILES ${FILESYSTEM_SRC})

file(GLOB_RECURSE MESSAGE_HEAD ${HDR_DIR}/message/*.h ${HDR_DIR}/message/*.inl)
file(GLOB_RECURSE MESSAGE_SRC ${SRC_DIR}/message/*.cpp)
source_group("Header Files/message" FILES ${MESSAGE_HEAD})
source_group("Source Files/message" FILES ${MESSAGE_SRC})

file(GLOB_RECURSE PATHUTILS_HEAD ${HDR_DIR}/pathutils/*.h ${HDR_DIR}/pathutils/*.inl)
file(GLOB_RECURSE PATHUTILS_SRC ${SRC_DIR}/pathutils/*.cpp)
source_group("Header Files/pathutils" FILES ${PATHUTILS_HEAD})
source_group("Source Files/pathutils" FILES ${PATHUTILS_SRC})

file(GLOB_RECURSE PLATFORM_HEAD ${HDR_DIR}/platform/*.h ${HDR_DIR}/platform/*.inl)
file(GLOB_RECURSE PLATFORM_SRC ${SRC_DIR}/platform/*.cpp)
source_group("Header Files/platform" FILES ${PLATFORM_HEAD})
source_group("Source Files/platform" FILES ${PLATFORM_SRC})

file(GLOB_RECURSE REFVALUE_HEAD ${HDR_DIR}/refvalue/*.h ${HDR_DIR}/refvalue/*.inl)
file(GLOB_RECURSE REFVALUE_SRC ${SRC_DIR}/refvalue/*.cpp)
source_group("Header Files/refvalue" FILES ${REFVALUE_HEAD})
source_group("Source Files/refvalue" FILES ${REFVALUE_SRC})

file(GLOB_RECURSE SERVICE_HEAD ${HDR_DIR}/service/*.h ${HDR_DIR}/service/*.inl)
source_group("Header Files/service" FILES ${SERVICE_HEAD})

file(GLOB_RECURSE TIMER_HEAD ${HDR_DIR}/timer/*.h ${HDR_DIR}/timer/*.inl)
file(GLOB_RECURSE TIMER_SRC ${SRC_DIR}/timer/*.cpp)
source_group("Header Files/timer" FILES ${TIMER_HEAD})
source_group("Source Files/timer" FILES ${TIMER_SRC})