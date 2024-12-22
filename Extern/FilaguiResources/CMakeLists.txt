
project(filaguiresources)

set(TARGET filaguiresources)

set(OUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HDR_DIR ${OUR_DIR})
set(SRC_DIR ${OUR_DIR})

set(HDR
    ${HDR_DIR}/filagui_resources.h
)

set(SRCS
    ${SRC_DIR}/filagui_resources.c
)

add_library(${TARGET} STATIC ${HDR} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

set_target_properties(${TARGET} PROPERTIES FOLDER "Third-party")

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(${TARGET} PRIVATE ozz_base)