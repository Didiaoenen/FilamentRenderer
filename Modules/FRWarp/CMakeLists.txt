project(FRWarp CXX)

find_package(glm CONFIG REQUIRED)

set(TARGET FRWarp)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl ${HDR_DIR}/enum/*.h ${HDR_DIR}/storage/*.h)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR} ${HDR_DIR}/enum ${HDR_DIR}/storage)

target_link_libraries(${TARGET} PRIVATE glm::glm filament dearimgui ozz_base FRTools)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

file(GLOB_RECURSE ENUM_HEAD ${HDR_DIR}/enum/*.h)
source_group("Header Files/enum" FILES ${ENUM_HEAD})

file(GLOB_RECURSE STORAGE_HEAD ${HDR_DIR}/storage/*.h)
source_group("Header Files/storage" FILES ${STORAGE_HEAD})