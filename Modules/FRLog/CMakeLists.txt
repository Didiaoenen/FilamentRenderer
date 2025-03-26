project(FRLog CXX)

# find_package(spdlog CONFIG REQUIRED)

set(TARGET FRLog)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl)
file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

target_link_libraries(${TARGET} PRIVATE spdlog FRTools)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)