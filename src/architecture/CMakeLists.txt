set(SOURCE_LIST
    Channel.hh
    Network.hh
    Node.hh
)

set(HEADER_LIST
    Channel.h
    Network.h
    Node.h
)

target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})