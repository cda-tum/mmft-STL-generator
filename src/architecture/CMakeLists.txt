set(SOURCE_LIST
    pChannel.hh
    pNetwork.hh
    pNode.hh
)

set(HEADER_LIST
    pChannel.h
    pNetwork.h
    pNode.h
)

target_sources(${TARGET_NAME} INTERFACE ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})