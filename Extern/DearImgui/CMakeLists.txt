
project(dearimgui)

set(OUR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

set(TARGET dearimgui)

set(SRC_DIR             ${OUR_DIR})
set(PUBLIC_HDR_DIR      ${OUR_DIR})
set(PRIVATE_HDR_DIR     ${OUR_DIR})

set(PUBLIC_HDRS
    ${PUBLIC_HDR_DIR}/imgui.h
    ${PUBLIC_HDR_DIR}/imconfig.h

    ${PUBLIC_HDR_DIR}/backends/imgui_impl_sdl2.h
)

set(PRIVATE_HDRS
    ${PRIVATE_HDR_DIR}/imgui_internal.h
    ${PRIVATE_HDR_DIR}/imstb_rectpack.h
    ${PRIVATE_HDR_DIR}/imstb_textedit.h
    ${PRIVATE_HDR_DIR}/imstb_truetype.h
)

set(SRCS
    ${SRC_DIR}/imgui.cpp
    ${SRC_DIR}/imgui_demo.cpp
    ${SRC_DIR}/imgui_draw.cpp
    ${SRC_DIR}/imgui_tables.cpp
    ${SRC_DIR}/imgui_widgets.cpp

    ${SRC_DIR}/backends/imgui_impl_sdl2.cpp
)

add_library(${TARGET} STATIC ${PRIVATE_HDRS} ${PUBLIC_HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${PUBLIC_HDR_DIR} ${PRIVATE_HDR_DIR})

target_link_libraries(${TARGET} PRIVATE sdl2 sdl2main)

set_target_properties(${TARGET} PROPERTIES FOLDER "Third-party")

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")