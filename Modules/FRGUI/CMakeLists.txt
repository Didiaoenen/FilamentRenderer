project(FRGUI CXX)

find_package(glm CONFIG REQUIRED)

set(TARGET FRGUI)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl)
file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

get_all_subdirs(ALL_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${TARGET} PUBLIC ${ALL_DIRS})

target_link_libraries(${TARGET} PRIVATE glm::glm ozz_base dearimgui imguiextern filament sdl2 sdl2main FRCore FRWarp FRTools)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HDRS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SRCS})