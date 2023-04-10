# Individual task build
project(01-FileIO LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compile commands for cppcheck

add_executable(${PROJECT_NAME} FileIO.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    COMPILE_OPTIONS "-Wall;-Wextra" # Enable compiler warnings
)

configure_file(input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)