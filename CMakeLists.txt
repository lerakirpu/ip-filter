cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

# Просто соберем основную программу без тестов
add_executable(lab2
    ip_filter.cpp
    base/base.cpp
)

target_include_directories(lab2 PRIVATE head)

message(STATUS "=== CMake Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Source files: ip_filter.cpp, base/base.cpp")
message(STATUS "Include directories: head")