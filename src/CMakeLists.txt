cmake_minimum_required (VERSION 3.10)

project (webservice
    VERSION 1.0.0
    DESCRIPTION ""
    LANGUAGES CXX
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths
get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)
set(CMAKE_MODULE_PATH ${ROOT_DIR}/cmake)

# Set specific build options for Drogon framework (located in lib/drogon)
option(BUILD_CTL "Build drogon_ctl" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_ORM "Build orm" OFF)
option(COZ_PROFILING "Use coz for profiling" OFF)
option(BUILD_SHARED_LIBS "Build drogon as a shared lib" OFF)
option(BUILD_DOC "Build Doxygen documentation" OFF)
option(BUILD_BROTLI "Build Brotli" OFF)
add_subdirectory(${ROOT_DIR}/lib/drogon ${CMAKE_BINARY_DIR}/drogon)

# Source code dependencies
add_subdirectory(data)
add_subdirectory(service)


add_executable(${PROJECT_NAME}
    main.cpp
)

# libpqxx
find_package(LibPQXX REQUIRED)
if (LIBPQXX_FOUND)
    # Resolve full name to pqxx dynamic library
    find_library(PQXX_LIB
        NAMES pqxx # what to look for
        HINTS "${LIBPQXX_LIBRARY_DIRS}" # where to look
        NO_DEFAULT_PATH # do not search system default paths
    )

    #message(STATUS "LIBPQXX_LIBRARY_DIRS: ${LIBPQXX_LIBRARY_DIRS}")
    #message(STATUS "PQXX_LIB: ${PQXX_LIB}")
endif()

# Dependent module(s) include files
target_include_directories(${PROJECT_NAME} PRIVATE
    ${JSONCPP_INCLUDE_DIRS}

    # Access to all includes from dependent modules (Only PUBLIC and INTERFACE include directories will be used)
    $<TARGET_PROPERTY:webservice::data,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:webservice::service,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:drogon,INCLUDE_DIRECTORIES>
)

# Link service executable with Drogon and pqxx (Postgres client)
target_link_libraries(${PROJECT_NAME} PRIVATE
    drogon
    ${PQXX_LIB}

    webservice::data
    webservice::service
)