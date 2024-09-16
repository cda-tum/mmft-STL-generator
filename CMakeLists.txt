cmake_minimum_required(VERSION 3.21.0)

project(MMFT-STL-Generator
    DESCRIPTION "Generator of STL geometries for closed channel-based microfluidic networks."
    HOMEPAGE_URL "https://github.com/cda-tum/mmft-STL-generator.git"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-O3 -march=native")

# download external libraries
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# add library
set(TARGET_NAME stlLib)
add_library(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC nlohmann_json::nlohmann_json)

# add sources
add_subdirectory(src)
target_sources(${TARGET_NAME} PUBLIC src/main.cpp)

# main executable
add_executable(MMFTSTL)
target_link_libraries(MMFTSTL PUBLIC ${TARGET_NAME})
