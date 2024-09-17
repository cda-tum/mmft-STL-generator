set(SOURCE_LIST
    BaseSTL.hh
    NetworkSTL.hh
)

set(HEADER_LIST
    BaseSTL.h
    NetworkSTL.h
)

# add subdirectories
add_subdirectory(primitives)

target_sources(${TARGET_NAME} INTERFACE ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})