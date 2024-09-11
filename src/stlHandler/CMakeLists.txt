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

target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})