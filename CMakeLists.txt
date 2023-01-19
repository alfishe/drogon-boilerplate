cmake_minimum_required (VERSION 3.10)

# Global options
#option(BUILD_TESTS "Build tests instead of webservice" OFF)

message(STATUS "<< top CMakeLists.txt")

project (drogon-boilerplate
    VERSION 1.0.0
    DESCRIPTION ""
    LANGUAGES CXX
)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths
get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
set(CMAKE_MODULE_PATH ${ROOT_DIR}/cmake)
message("CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")


if (BUILD_TESTS)
    message(STATUS "Tests will be built")
    add_subdirectory(test)
else ()
    add_subdirectory(src)
endif ()

# <Diagnostics>
message(STATUS "<Top diagnostics>")
message(STATUS "  PROJECT_NAME:        ${PROJECT_NAME}")
message(STATUS "  BUILD_TESTS:         ${BUILD_TESTS}")

message(STATUS "</Top diagnostics>")
# </Diagnostics>

message(STATUS "<< top CMakeLists.txt")

