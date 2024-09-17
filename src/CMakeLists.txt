# add subdirectories
add_subdirectory(architecture)
add_subdirectory(parser)
add_subdirectory(stlHandler)

target_sources(${TARGET_NAME} INTERFACE ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})