project (service LANGUAGES CXX)

# Build static library as output; Create alias webservice::service for the same target
add_library(${PROJECT_NAME} STATIC)
add_library(webservice::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Determine paths
get_filename_component(SERVICE_DIR ${CMAKE_CURRENT_LIST_DIR} REALPATH)

# Add include directories to search and allow all targets depending on current to use them
target_include_directories(${PROJECT_NAME} PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Dependent module(s) include files
target_include_directories(${PROJECT_NAME} PRIVATE

    # Access to all includes from dependent modules (Only PUBLIC and INTERFACE include directories will be used)
    $<TARGET_PROPERTY:webservice::data,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:drogon,INCLUDE_DIRECTORIES>
)

# Sources
target_sources(
    ${PROJECT_NAME} PUBLIC

    ${SERVICE_DIR}/hello_world_api.cpp
    ${SERVICE_DIR}/hello_world_api.h
)

# <Diagnostics>
get_target_property(SERVICE_SOURCES ${PROJECT_NAME} SOURCES)
get_target_property(SERVICE_INCLUDES ${PROJECT_NAME} INCLUDE_DIRECTORIES)

message(STATUS "<Service diagnostics>")
message(STATUS "  PROJECT_NAME:          ${PROJECT_NAME}")
message(STATUS "  SERVICE_DIR:           ${SERVICE_DIR}")
message(STATUS "  SERVICE_SOURCES:       ${SERVICE_SOURCES}")
message(STATUS "  SERVICE_INCLUDES:      ${SERVICE_INCLUDES}")
message(STATUS "</Service diagnostics>")
# </Diagnostics>
