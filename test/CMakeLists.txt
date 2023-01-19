# This script is responsible for building googletest-based executable for unit testing purposes
cmake_minimum_required(VERSION 3.16)

message(STATUS ">> test CMakeLists.txt")

# This project is written on C++
project(webservice_test LANGUAGES CXX)

# Define paths
get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

# Source code dependencies
add_subdirectory(${ROOT_DIR}/src/data ${CMAKE_BINARY_DIR}/src/data)
add_subdirectory(${ROOT_DIR}/src/service ${CMAKE_BINARY_DIR}/src/service)
add_subdirectory(${ROOT_DIR}/lib/drogon ${CMAKE_BINARY_DIR}/drogon)
add_subdirectory(${ROOT_DIR}/lib/googletest ${CMAKE_BINARY_DIR}/googletest)

# All source files to be compiled
file(GLOB_RECURSE TEST_CPP_FILES *.cpp)            # Test sourcecode files

# Produce executable for 'webservice_test'
add_executable(${PROJECT_NAME} ${TEST_CPP_FILES})

# Include directories
target_include_directories(
    ${PROJECT_NAME} PRIVATE

    ${SRC_DIR}

    # Access to all includes from dependent modules (Only PUBLIC and INTERFACE include directories will be used)
    $<TARGET_PROPERTY:webservice::data,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:webservice::service,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:drogon,INCLUDE_DIRECTORIES>
)

# Sources to compile target from
target_sources(
    ${PROJECT_NAME} PRIVATE

    ${TEST_CPP_FILES}
)

# All dependencies to be linked
target_link_libraries(
    ${PROJECT_NAME} PRIVATE

    webservice::data          # Link data layer
    webservice::service       # All services
    drogon                    # Drogon framework
    ${PQXX_LIB}               # pqxx Postgres access library

    # Test frameworks
    gtest                       # Googletest framework
    gtest_main                  # Main stub from googletest
)

# <Diagnostics>
message(STATUS "<test diagnostics>")
message(STATUS "  PROJECT_NAME:        ${PROJECT_NAME}")
message(STATUS "  SRC_DIR:             ${SRC_DIR}")
message(STATUS "  LIB_DIR:             ${LIB_DIR}")
message(STATUS "  TEST_CPP_FILES:      ${TEST_CPP_FILES}")

message(STATUS "  INCLUDE_DIRECTORIES:")
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach (dir ${include_dirs})
    message(STATUS "                       ${dir}")
endforeach ()

message(STATUS "</test diagnostics>")
# </Diagnostics>

message(STATUS "<< test CMakeLists.txt")
