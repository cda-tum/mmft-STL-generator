set(SOURCE_LIST
    jsonParser.cpp
    jsonReader.hh
)

set(HEADER_LIST
    jsonParser.h
    jsonReader.h
)

target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})