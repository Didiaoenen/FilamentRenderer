project(FRGUI CXX)

find_package(glm CONFIG REQUIRED)

set(TARGET FRGUI)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS
${HDR_DIR}/*.h
${HDR_DIR}/*.inl
${HDR_DIR}/canvas/*.h
${HDR_DIR}/canvas/*.inl
${HDR_DIR}/enum/*.h
${HDR_DIR}/panel/*.h
${HDR_DIR}/panel/*.inl
${HDR_DIR}/plugin/*.h
${HDR_DIR}/plugin/*.inl
${HDR_DIR}/widget/*.h
${HDR_DIR}/widget/*.inl
)

file(GLOB_RECURSE SRCS
${SRC_DIR}/*.cpp
${SRC_DIR}/canvas/*.cpp
${SRC_DIR}/panel/*.cpp
${SRC_DIR}/plugin/*.cpp
${SRC_DIR}/widget/*.cpp
)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC
${HDR_DIR}
${HDR_DIR}/canvas
${HDR_DIR}/enum
${HDR_DIR}/panel
${HDR_DIR}/plugin
${HDR_DIR}/widget
)

target_link_libraries(${TARGET} PRIVATE glm::glm ozz_base dearimgui imguiextern filament sdl2 sdl2main FRCore FRWarp FRTools)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

file(GLOB_RECURSE CANVAS_HEAD ${HDR_DIR}/canvas/*.h ${HDR_DIR}/canvas/*.inl)
file(GLOB_RECURSE CANVAS_SRC ${SRC_DIR}/canvas/*.cpp)
source_group("Header Files/canvas" FILES ${CANVAS_HEAD})
source_group("Source Files/canvas" FILES ${CANVAS_SRC})

file(GLOB_RECURSE ENUM_HEAD ${HDR_DIR}/enum/*.h)
source_group("Header Files/enum" FILES ${ENUM_HEAD})

file(GLOB_RECURSE PANEL_HEAD ${HDR_DIR}/panel/*.h ${HDR_DIR}/panel/*.inl)
file(GLOB_RECURSE PANEL_SRC ${SRC_DIR}/panel/*.cpp)
source_group("Header Files/panel" FILES ${PANEL_HEAD})
source_group("Source Files/panel" FILES ${PANEL_SRC})

file(GLOB_RECURSE PLUGIN_HEAD ${HDR_DIR}/plugin/*.h ${HDR_DIR}/plugin/*.inl)
file(GLOB_RECURSE PLUGIN_SRC ${SRC_DIR}/plugin/*.cpp)
source_group("Header Files/plugin" FILES ${PLUGIN_HEAD})
source_group("Source Files/plugin" FILES ${PLUGIN_SRC})

file(GLOB_RECURSE WIDGET_HEAD ${HDR_DIR}/widget/*.h ${HDR_DIR}/widget/*.inl)
file(GLOB_RECURSE WIDGET_SRC ${SRC_DIR}/widget/*.cpp)
source_group("Header Files/widget" FILES ${WIDGET_HEAD})
source_group("Source Files/widget" FILES ${WIDGET_SRC})