cmake_minimum_required(VERSION 3.12)
project(IPFilter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(ip_filter main.cpp)

# Для Windows
if(WIN32)
    target_compile_definitions(ip_filter PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

enable_testing()

add_test(NAME CompilationTest COMMAND ip_filter)

message(STATUS "Project configured successfully")