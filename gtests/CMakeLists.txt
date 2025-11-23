cmake_minimum_required(VERSION 3.15)

project(gtests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(COMMON_SRCS
    "../base/base.cpp"
)

include_directories(../head)

add_executable(gtests gtest.cpp ${COMMON_SRCS})
target_include_directories(gtests PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(gtests PUBLIC gtest gtest_main)