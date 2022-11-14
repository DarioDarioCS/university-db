cmake_minimum_required(VERSION 3.11)
project(hello)

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

add_executable(hello  main.cpp university-db.cpp)

add_executable(gtests gtestCheck.cpp university-db.cpp)
target_link_libraries(gtests gtest_main gmock_main)
