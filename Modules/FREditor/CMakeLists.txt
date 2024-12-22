project(FREditor CXX)

find_package(glm CONFIG REQUIRED)
find_package(Tracy CONFIG REQUIRED)
# find_package(spdlog CONFIG REQUIRED)

set(TARGET FREditor)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS
${HDR_DIR}/*.h
${HDR_DIR}/*.inl
${HDR_DIR}/dialog/*.h
${HDR_DIR}/dialog/*.inl
${HDR_DIR}/enum/*.h
${HDR_DIR}/enum/*.inl
${HDR_DIR}/input/*.h
${HDR_DIR}/input/*.inl
${HDR_DIR}/panels/*.h
${HDR_DIR}/panels/*.inl
)

file(GLOB_RECURSE SRCS
${SRC_DIR}/*.cpp
${SRC_DIR}/dialog/*.cpp
${SRC_DIR}/input/*.cpp
${SRC_DIR}/panels/*.cpp
)

add_executable(${TARGET} ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC
${HDR_DIR}
${HDR_DIR}/dialog
${HDR_DIR}/enum
${HDR_DIR}/input
${HDR_DIR}/panels
)

target_link_libraries(${TARGET} PRIVATE glm::glm Tracy::TracyClient dearimgui imguiextern tinyxml2 filament filamat stb filaguiresources ozz_base ozz_animation sdl2 sdl2main spdlog matparser FRLog FRCore FRWarp FRGUI FRTools)

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

file(GLOB_RECURSE ENUM_HEAD ${HDR_DIR}/enum/*.h ${HDR_DIR}/enum/*.inl)
source_group("Header Files/enum" FILES ${ENUM_HEAD})

file(GLOB_RECURSE DIALOG_HEAD ${HDR_DIR}/dialog/*.h ${HDR_DIR}/dialog/*.inl)
file(GLOB_RECURSE DIALOG_SRC ${SRC_DIR}/dialog/*.cpp)
source_group("Header Files/dialog" FILES ${DIALOG_HEAD})
source_group("Source Files/dialog" FILES ${DIALOG_SRC})

file(GLOB_RECURSE INPUT_HEAD ${HDR_DIR}/input/*.h ${HDR_DIR}/input/*.inl)
file(GLOB_RECURSE INPUT_SRC ${SRC_DIR}/input/*.cpp)
source_group("Header Files/input" FILES ${INPUT_HEAD})
source_group("Source Files/input" FILES ${INPUT_SRC})

file(GLOB_RECURSE PANELS_HEAD ${HDR_DIR}/panels/*.h ${HDR_DIR}/panels/*.inl)
file(GLOB_RECURSE PANELS_SRC ${SRC_DIR}/panels/*.cpp)
source_group("Header Files/panels" FILES ${PANELS_HEAD})
source_group("Source Files/panels" FILES ${PANELS_SRC})
