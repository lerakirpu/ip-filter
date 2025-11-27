cmake_minimum_required(VERSION 3.10.0)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(lab2 VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа))
add_executable(${PROJECT_NAME}
    ip_filter.cpp
    base/base.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE head)

install(TARGETS lab2 RUNTIME DESTINATION bin)

# Тесты
enable_testing()

# Проверяем существование файла тестов перед добавлением
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gtests.cpp")
    message(STATUS "Found gtests.cpp - configuring tests")
    
    find_package(GTest QUIET)
    
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
        message(STATUS "GoogleTest not found - skipping tests")
    endif()
else()
    message(STATUS "gtests.cpp not found - skipping tests")
endif()

message(STATUS "Build configuration complete")

set(CPACK_GENERATOR "DEB")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "lerakirpu@mail.ru")
set(CPACK_PACKAGE_NAME "lab2")
set(CPACK_PACKAGE_DESCRIPTION "IP Filter Application")

include(CPack)