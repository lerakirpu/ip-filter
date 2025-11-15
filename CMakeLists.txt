cmake_minimum_required(VERSION 3.12)
project(IPFilter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdab60b14b31dbd6d83ad9.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(ip_filter main.cpp)

# Тесты
add_executable(test_ip_filter tests/test_main.cpp)
target_link_libraries(test_ip_filter GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_ip_filter)

# Для Windows
if(WIN32)
    target_compile_definitions(ip_filter PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(test_ip_filter PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

message(STATUS "Project configured successfully")