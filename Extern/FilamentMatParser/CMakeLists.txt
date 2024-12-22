project(matparser CXX)

set(TARGET matparser)

set(OUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HDR_DIR ${OUR_DIR})
set(SRC_DIR ${OUR_DIR})

file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h ${HDR_DIR}/*.inl ${HDR_DIR}/matc/*.h ${HDR_DIR}/matc/*.inl)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp ${SRC_DIR}/matc/*.cpp)

add_library(${TARGET} STATIC ${HDRS} ${SRCS})

target_include_directories(${TARGET} PUBLIC ${HDR_DIR} ${HDR_DIR}/matc PRIVATE ${filamat_SOURCE_DIR}/src)

target_link_libraries(${TARGET} PRIVATE filament filamat getopt)

set_target_properties(${TARGET} PROPERTIES FOLDER "Third-party")

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")