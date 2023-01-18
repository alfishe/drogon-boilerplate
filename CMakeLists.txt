cmake_minimum_required (VERSION 3.10)

project (drogon-boilerplate
    VERSION 1.0.0
    DESCRIPTION ""
    LANGUAGES CXX
)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
message("CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")

# Set specific build options for Drogon framework (located in lib/drogon)
option(BUILD_CTL "Build drogon_ctl" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_ORM "Build orm" OFF)
option(COZ_PROFILING "Use coz for profiling" OFF)
option(BUILD_SHARED_LIBS "Build drogon as a shared lib" OFF)
option(BUILD_DOC "Build Doxygen documentation" OFF)
option(BUILD_BROTLI "Build Brotli" OFF)
add_subdirectory(lib/drogon)


add_executable(${PROJECT_NAME}
    src/main.cpp
    src/hello_world_api.cpp
    src/hello_world_api.h
    src/data_access.cpp
    src/data_access.h
)

# libpqxx
find_package(LibPQXX REQUIRED)
if (LIBPQXX_FOUND)
    #target_link_directories(${PROJECT_NAME} PRIVATE ${LIBPQXX_LIBRARY_DIRS})

    # Resolve full name to pqxx dynamic library
    find_library(PQXX_LIB
        NAMES pqxx # what to look for
        HINTS "${LIBPQXX_LIBRARY_DIRS}" # where to look
        NO_DEFAULT_PATH # do not search system default paths
    )

    message("LIBPQXX_LIBRARY_DIRS: ${LIBPQXX_LIBRARY_DIRS}")
    message("PQXX_LIB: ${PQXX_LIB}")
endif()

# Allow compiler to find jsoncpp headers
target_include_directories(${PROJECT_NAME} PRIVATE JSONCPP_INCLUDE_DIRS)

# Link service executable with Drogon and pqxx (Postgres client)
target_link_libraries(${PROJECT_NAME} PRIVATE
    drogon
    ${PQXX_LIB}
)