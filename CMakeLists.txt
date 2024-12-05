cmake_minimum_required(VERSION 3.2)

if(CMAKE_CURRENT_LIST_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree build."
            " Building in-source is not supported!"
            " Please create a build directory outside the engine source"
            " code and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there.")
endif()

project(JSON_DSL_PROJECT 
        DESCRIPTION "A JSON processing DSL"
        LANGUAGES CXX)

# Creates a compiler_commands.json file for LSP 
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(
    json_dsl src/json_dsl.cpp
)

target_include_directories(
    json_dsl PRIVATE include
)

set_target_properties(
    json_dsl 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
)

# Create the bin directory if it does not exist
add_custom_target(
    build-time-make-directory
    ALL COMMAND 
    ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/bin
)
