set(SOURCE_LIST
    jsonReader.hh
    jsonParser.hh
)

set(HEADER_LIST
    jsonReader.h    
    jsonParser.h
)

target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})