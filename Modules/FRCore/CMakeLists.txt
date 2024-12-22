project(FRCore CXX)

find_package(glm CONFIG REQUIRED)

set(TARGET FRCore)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDRS
${HDR_DIR}/*.h
${HDR_DIR}/*.inl
${HDR_DIR}/animation/*.h
${HDR_DIR}/animation/*.inl
${HDR_DIR}/assets/*.h
${HDR_DIR}/assets/*.inl
${HDR_DIR}/assetsmanager/*.h
${HDR_DIR}/assetsmanager/*.inl
${HDR_DIR}/component/*.h
${HDR_DIR}/component/*.inl
${HDR_DIR}/database/*.h
${HDR_DIR}/database/*.inl
${HDR_DIR}/enum/*.h
${HDR_DIR}/guidraw/*.h
${HDR_DIR}/guidraw/*.inl
${HDR_DIR}/renderer/*.h
${HDR_DIR}/renderer/*.inl
${HDR_DIR}/rendererfeature/*.h
${HDR_DIR}/rendererfeature/*.inl
${HDR_DIR}/scene/*.h
${HDR_DIR}/scene/*.inl
${HDR_DIR}/scenegraph/*.h
${HDR_DIR}/scenegraph/*.inl
${HDR_DIR}/serializer/*.h
${HDR_DIR}/serializer/*.inl
)

file(GLOB_RECURSE SRCS
${SRC_DIR}/*.cpp
${HDR_DIR}/animation/*.cpp
${HDR_DIR}/assets/*.cpp
${HDR_DIR}/assetsmanager/*.cpp
${HDR_DIR}/component/*.cpp
${HDR_DIR}/database/*.cpp
${HDR_DIR}/guidraw/*.cpp
${HDR_DIR}/renderer/*.cpp
${HDR_DIR}/rendererfeature/*.cpp
${HDR_DIR}/scene/*.cpp
${HDR_DIR}/scenegraph/*.cpp
${HDR_DIR}/serializer/*.cpp
)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC
${HDR_DIR}
${HDR_DIR}/animation
${HDR_DIR}/assets
${HDR_DIR}/assetsmanager
${HDR_DIR}/component
${HDR_DIR}/database
${HDR_DIR}/enum
${HDR_DIR}/guidraw
${HDR_DIR}/renderer
${HDR_DIR}/rendererfeature
${HDR_DIR}/scene
${HDR_DIR}/scenegraph
${HDR_DIR}/serializer
)

target_link_libraries(${TARGET} PRIVATE glm::glm ktxreader dearimgui imguiextern tinyxml2 filament filamat filament-iblprefilter assimp stb ozz_base ozzmesh sdl2 sdl2main matparser spdlog FRLog FRWarp FRGUI FRTools)

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

file(GLOB_RECURSE ANIMATION_HEAD ${HDR_DIR}/animation/*.h ${HDR_DIR}/animation/*.inl)
file(GLOB_RECURSE ANIMATION_SRC ${SRC_DIR}/animation/*.cpp)
source_group("Header Files/animation" FILES ${ANIMATION_HEAD})
source_group("Source Files/animation" FILES ${ANIMATION_SRC})

file(GLOB_RECURSE ASSETS_HEAD ${HDR_DIR}/assets/*.h ${HDR_DIR}/assets/*.inl)
file(GLOB_RECURSE ASSETS_SRC ${SRC_DIR}/assets/*.cpp)
source_group("Header Files/assets" FILES ${ASSETS_HEAD})
source_group("Source Files/assets" FILES ${ASSETS_SRC})

file(GLOB_RECURSE ASSETSMANAGER_HEAD ${HDR_DIR}/assetsmanager/*.h ${HDR_DIR}/assetsmanager/*.inl)
file(GLOB_RECURSE ASSETSMANAGER_SRC ${SRC_DIR}/assetsmanager/*.cpp)
source_group("Header Files/assetsmanager" FILES ${ASSETSMANAGER_HEAD})
source_group("Source Files/assetsmanager" FILES ${ASSETSMANAGER_SRC})

file(GLOB_RECURSE COMPONENT_HEAD ${HDR_DIR}/component/*.h ${HDR_DIR}/component/*.inl)
file(GLOB_RECURSE COMPONENT_SRC ${SRC_DIR}/component/*.cpp)
source_group("Header Files/component" FILES ${COMPONENT_HEAD})
source_group("Source Files/component" FILES ${COMPONENT_SRC})

file(GLOB_RECURSE DATABASE_HEAD ${HDR_DIR}/database/*.h ${HDR_DIR}/database/*.inl)
file(GLOB_RECURSE DATABASE_SRC ${SRC_DIR}/database/*.cpp)
source_group("Header Files/database" FILES ${DATABASE_HEAD})
source_group("Source Files/database" FILES ${DATABASE_SRC})

file(GLOB_RECURSE ENUM_HEAD ${HDR_DIR}/enum/*.h)
source_group("Header Files/enum" FILES ${ENUM_HEAD})

file(GLOB_RECURSE GUIDRAW_HEAD ${HDR_DIR}/guidraw/*.h ${HDR_DIR}/guidraw/*.inl)
file(GLOB_RECURSE GUIDRAW_SRC ${SRC_DIR}/guidraw/*.cpp)
source_group("Header Files/guidraw" FILES ${GUIDRAW_HEAD})
source_group("Source Files/guidraw" FILES ${GUIDRAW_SRC})

file(GLOB_RECURSE RENDER_HEAD ${HDR_DIR}/renderer/*.h ${HDR_DIR}/renderer/*.inl)
file(GLOB_RECURSE RENDER_SRC ${SRC_DIR}/renderer/*.cpp)
source_group("Header Files/renderer" FILES ${RENDER_HEAD})
source_group("Source Files/renderer" FILES ${RENDER_SRC})

file(GLOB_RECURSE RENDERFEATURE_HEAD ${HDR_DIR}/rendererfeature/*.h ${HDR_DIR}/rendererfeature/*.inl)
file(GLOB_RECURSE RENDERFEATURE_SRC ${SRC_DIR}/rendererfeature/*.cpp)
source_group("Header Files/rendererfeature" FILES ${RENDERFEATURE_HEAD})
source_group("Source Files/rendererfeature" FILES ${RENDERFEATURE_SRC})

file(GLOB_RECURSE SCENE_HEAD ${HDR_DIR}/scene/*.h ${HDR_DIR}/scene/*.inl)
file(GLOB_RECURSE SCENE_SRC ${SRC_DIR}/scene/*.cpp)
source_group("Header Files/scene" FILES ${SCENE_HEAD})
source_group("Source Files/scene" FILES ${SCENE_SRC})

file(GLOB_RECURSE SCENEGRAPH_HEAD ${HDR_DIR}/scenegraph/*.h ${HDR_DIR}/scenegraph/*.inl)
file(GLOB_RECURSE SCENEGRAPH_SRC ${SRC_DIR}/scenegraph/*.cpp)
source_group("Header Files/scenegraph" FILES ${SCENEGRAPH_HEAD})
source_group("Source Files/scenegraph" FILES ${SCENEGRAPH_SRC})

file(GLOB_RECURSE SERIALIZER_HEAD ${HDR_DIR}/serializer/*.h ${HDR_DIR}/serializer/*.inl)
file(GLOB_RECURSE SERIALIZER_SRC ${SRC_DIR}/serializer/*.cpp)
source_group("Header Files/serializer" FILES ${SERIALIZER_HEAD})
source_group("Source Files/serializer" FILES ${SERIALIZER_SRC})