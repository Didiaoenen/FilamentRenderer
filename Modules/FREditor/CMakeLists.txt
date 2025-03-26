project(FREditor CXX)

find_package(glm CONFIG REQUIRED)
find_package(Tracy CONFIG REQUIRED)
# find_package(spdlog CONFIG REQUIRED)

set(TARGET FREditor)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl)
file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_executable(${TARGET} ${HDRS} ${SRCS})

get_all_subdirs(ALL_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TARGET} PUBLIC ${ALL_DIRS})

target_link_libraries(${TARGET} PRIVATE glm::glm Tracy::TracyClient dearimgui imguiextern tinyxml2 filament filamat stb filaguiresources ozz_base ozz_animation sdl2 sdl2main spdlog matparser FRLog FRCore FRWarp FRGUI FRTools)

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HDRS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SRCS})