cmake_minimum_required (VERSION 3.10)

project (drogon-boilerplate
    VERSION 1.0.0
    DESCRIPTION ""
    LANGUAGES CXX
)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set specific build options for Drogon framework (located in lib/drogon)
option(BUILD_CTL "Build drogon_ctl" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_ORM "Build orm" OFF)
option(COZ_PROFILING "Use coz for profiling" OFF)
option(BUILD_SHARED_LIBS "Build drogon as a shared lib" OFF)
option(BUILD_DOC "Build Doxygen documentation" OFF)
option(BUILD_BROTLI "Build Brotli" OFF)
add_subdirectory(lib/drogon)


add_executable(drogon-boilerplate
    src/main.cpp
    src/hello_world_api.cpp
    src/hello_world_api.h
)

target_include_directories(${PROJECT_NAME} PRIVATE JSONCPP_INCLUDE_DIRS)

target_link_libraries(${PROJECT_NAME} PRIVATE
    drogon
)