
project(imguiextern CXX)

set(TARGET imguiextern)

set(OUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HDR_DIR ${OUR_DIR})

set(HDRS
    ${HDR_DIR}/ImGuizmo.h
    ${HDR_DIR}/ImguiTextClipped.h
    ${HDR_DIR}/IconsMaterialDesignIcons.h
)

set(SRCS
    ${HDR_DIR}/ImGuizmo.cpp
    ${HDR_DIR}/ImguiTextClipped.cpp
)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

set_target_properties(${TARGET} PROPERTIES FOLDER "Third-party")

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(${TARGET} PRIVATE dearimgui)

