# Individual task build
project(03-Functions LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compile commands for cppcheck

add_executable(${PROJECT_NAME} Functions.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    COMPILE_OPTIONS "-Wall;-Wextra" # Enable compiler warnings
)