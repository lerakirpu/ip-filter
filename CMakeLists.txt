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

# Основное приложение
add_executable(ip_filter src/main.cpp)

# Тесты
add_executable(test_ip_filter tests/test_main.cpp)
target_link_libraries(test_ip_filter GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_ip_filter)

# Установка
install(TARGETS ip_filter DESTINATION bin)