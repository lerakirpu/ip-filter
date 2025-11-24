cmake_minimum_required(VERSION 3.10)
project(lab2 VERSION 1.0.0)  

configure_file(version.h.in version.h)  

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
    ip_filter.cpp
    base/base.cpp
)

target_include_directories(lab2 PRIVATE head)