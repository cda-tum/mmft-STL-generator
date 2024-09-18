set(SOURCE_LIST
    pjsonReader.hh
    pjsonParser.hh
)

set(HEADER_LIST
    pjsonReader.h    
    pjsonParser.h
)

target_sources(${TARGET_NAME} INTERFACE ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})