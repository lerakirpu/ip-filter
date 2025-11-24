cmake_minimum_required(VERSION 3.10)
project(lab2 VERSION 1.0.0)

configure_file(version.h.in version.h)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(lab2
    ip_filter.cpp
    base/base.cpp
)

target_include_directories(lab2 PRIVATE head)

enable_testing()

find_package(GTest)

if(GTest_FOUND)
    message(STATUS "GoogleTest found - building tests")
    
    add_executable(ip_filter_test
        gtests.cpp          
        base/base.cpp     
    )

    target_link_libraries(ip_filter_test GTest::gtest GTest::gtest_main)
    target_include_directories(ip_filter_test PRIVATE head)
    
    include(GoogleTest)
    gtest_discover_tests(ip_filter_test)
    
else()
    message(WARNING "GoogleTest not found - skipping tests")
endif()

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_CONTACT "lerakirpu@mail.ru")
set(CPACK_PACKAGE_NAME "lab2")
set(CPACK_PACKAGE_DESCRIPTION "IP Filter Application")

include(CPack)
