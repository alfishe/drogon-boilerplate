project (data LANGUAGES CXX)

# Build static library as output; Create alias webservice::data for the same target
add_library(${PROJECT_NAME} STATIC)
add_library(webservice::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Determine paths
get_filename_component(DATA_DIR ${CMAKE_CURRENT_LIST_DIR} REALPATH)

# Add include directories to search and allow all targets depending on current to use them
target_include_directories(
    ${PROJECT_NAME} PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Sources
set(DATA_SRC
    ${DATA_DIR}/data_access.cpp
    ${DATA_DIR}/data_access.h
)

target_sources(${PROJECT_NAME} PRIVATE

    ${DATA_SRC}
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

    # Allow to use pqxx headers
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${LIBPQXX_INCLUDE_DIRS}
    )

    #message(STATUS "LIBPQXX_LIBRARY_DIRS: ${LIBPQXX_LIBRARY_DIRS}")
    #message(STATUS "PQXX_LIB: ${PQXX_LIB}")
else ()
    message(FATAL_ERROR "Unable to find libpqxx package installed")
endif()


# <Diagnostics>
get_target_property(DATA_SOURCES ${PROJECT_NAME} SOURCES)
get_target_property(DATA_INCLUDES ${PROJECT_NAME} INCLUDE_DIRECTORIES)

message(STATUS "<Data diagnostics>")
message(STATUS "  PROJECT_NAME:          ${PROJECT_NAME}")
message(STATUS "  DATA_DIR:              ${DATA_DIR}")
message(STATUS "  DATA_SOURCES:          ${DATA_SOURCES}")
message(STATUS "  DATA_INCLUDES:         ${DATA_INCLUDES}")

message(STATUS "</Data diagnostics>")
# </Diagnostics>
