cmake_minimum_required(VERSION 3.11)
project(hello)

set(CMAKE_CXX_STANDARD 20)

# get JSON library
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


# Get Googletest

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

add_definitions(-Wno-unused-variable)
add_definitions(-Wno-unused-parameter)
add_definitions(-Wall -Werror -pedantic -Wextra)

add_executable(hello  main.cpp university-db.cpp Student.cpp)
add_executable(gtests gtestCheck.cpp university-db.cpp Student.cpp)
add_executable(json_experiments my_json_experiments.cpp)

target_link_libraries(hello PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(gtests PRIVATE gtest_main gmock_main nlohmann_json::nlohmann_json)
target_link_libraries(json_experiments PRIVATE nlohmann_json::nlohmann_json)
