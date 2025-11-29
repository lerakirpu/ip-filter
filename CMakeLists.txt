cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(lab2 VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
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
    
    # Автоматическая загрузка GoogleTest если не найден в системе
    if(NOT GTest_FOUND)
        message(STATUS "GoogleTest not found in system, fetching...")
        
        include(FetchContent)
        FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
        
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
        
        # Проверяем успешность загрузки
        if(TARGET gtest AND TARGET gtest_main)
            set(GTest_FOUND TRUE)
            message(STATUS "GoogleTest successfully fetched")
        else()
            message(WARNING "Failed to fetch GoogleTest")
        endif()
    else()
        message(STATUS "GoogleTest found in system")
    endif()
    
    if(GTest_FOUND)
        message(STATUS "Building tests")
        
        add_executable(ip_filter_test
            gtests.cpp          
            base/base.cpp     
        )

        # Универсальное подключение GTest
        if(TARGET GTest::gtest)
            # Для системного GTest (modern CMake targets)
            target_link_libraries(ip_filter_test GTest::gtest GTest::gtest_main)
        else()
            # Для загруженного через FetchContent
            target_link_libraries(ip_filter_test gtest gtest_main)
        endif()
        
        target_include_directories(ip_filter_test PRIVATE head)
        
        # Даем время на создание тестовых файлов
        add_custom_command(TARGET ip_filter_test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Tests compiled successfully"
        )
        
        include(GoogleTest)
        gtest_discover_tests(ip_filter_test)
        
        # Резервное добавление тестов если discovery не работает
        add_test(
            NAME IPFilterTests
            COMMAND ip_filter_test
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
        
    else()
        message(STATUS "GoogleTest not available - skipping tests")
    endif()
else()
    message(STATUS "gtests.cpp not found - skipping tests")
endif()

message(STATUS "Build configuration complete")

# Настройка пакетирования
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "lerakirpu@mail.ru")
set(CPACK_PACKAGE_NAME "lab2")
set(CPACK_PACKAGE_DESCRIPTION "IP Filter Application")

include(CPack)