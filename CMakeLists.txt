# © 2017 Joseph Cameron - All Rights Reserved
# Project: Hello Travis CI
# Created on 2017-12-7.

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
enable_testing()

set(JFC_CXX_COMPILER_FEATURE_REQUIREMENTS PRIVATE
    cxx_variadic_templates
    cxx_nullptr
    cxx_lambdas
)

if (NOT JFC_TARGET_PLATFORM)
    set(JFC_TARGET_PLATFORM ${CMAKE_HOST_SYSTEM_NAME}) #may need to follow project(). This works on 3.9.20170921-g46f7a, MacOS
endif()

include("cmake/HunterGate.cmake")

if(NOT EXISTS ${HUNTER_ENABLED})
    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.20.31.tar.gz"
        SHA1 "65c8f2292566aedb2fe10e08e09c74dda8e5d07a"
    )
endif()

# ================== TESTS ==================

project("Unit-Tests")
hunter_add_package(Catch)
find_package(Catch2 CONFIG REQUIRED)
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/tests/main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Catch2::Catch
)
target_compile_features(${PROJECT_NAME} ${JFC_CXX_COMPILER_FEATURE_REQUIREMENTS})
add_test(${PROJECT_NAME} ${PROJECT_NAME})

# ================== PROJECT ==================

project("Hunter-Reference" VERSION "0.0.1" DESCRIPTION "has no description!")
hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)
add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCE_DIR}/src/DemoGLWindow.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
)
target_link_libraries(${PROJECT_NAME} 
    glfw
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_features(${PROJECT_NAME} ${JFC_CXX_COMPILER_FEATURE_REQUIREMENTS})

# ================== GENERATED HEADER ==================

string(RANDOM LENGTH 15 JFC_RANDOM_128BITS)
string(TOUPPER ${JFC_TARGET_PLATFORM} JFC_TARGET_PLATFORM)

execute_process(COMMAND git rev-parse HEAD WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} OUTPUT_VARIABLE JFC_GIT_COMMIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND git log -1 --format=%cd --date=local HEAD WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} OUTPUT_VARIABLE JFC_GIT_COMMIT_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(${CMAKE_SOURCE_DIR}/src/cmake.h.in ${CMAKE_SOURCE_DIR}/src/cmake.h @ONLY)
