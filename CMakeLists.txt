project(Lab-C LANGUAGES CXX)

cmake_minimum_required(VERSION 3.16)

# Build all binaries to the /bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin")

# Lab files
add_executable(FileIO ${CMAKE_SOURCE_DIR}/01-FileIO/FileIO.cpp)
configure_file(${CMAKE_SOURCE_DIR}/01-FileIO/input.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
add_executable(Copy ${CMAKE_SOURCE_DIR}/02-Copy/Copy.cpp)

option(BUILD_LABBOOK "Build the labbook" OFF)

# Lab Book using LaTeX
find_package(LATEX)
set(LT_OUT_DIR "${CMAKE_BINARY_DIR}/build/tex")
set(LT_WORKING_DIR "${CMAKE_SOURCE_DIR}/LabBook")
set(MAIN_TEX "${LT_WORKING_DIR}/Lab-C.tex")

if(LATEX_FOUND AND LATEX_PDFLATEX_FOUND AND BUILD_LABBOOK)
    file(MAKE_DIRECTORY ${LT_OUT_DIR})

    # First Pass
    add_custom_target( latex-prebuild
                        COMMAND ${PDFLATEX_COMPILER} -output-directory ${LT_OUT_DIR} -draftmode -shell-escape -interaction=nonstopmode ${MAIN_TEX}
                        COMMENT "Starting Prebuild..."
                        WORKING_DIRECTORY ${LT_WORKING_DIR}
                        DEPENDS ${MAIN_TEX}
                )

    # Second Pass, generating final pdf
    add_custom_target( latex-pdf
                        COMMAND ${PDFLATEX_COMPILER} -output-directory ${LT_OUT_DIR} -shell-escape ${MAIN_TEX}
                        COMMENT "Starting Final Build..."
                        WORKING_DIRECTORY ${LT_WORKING_DIR}
                        DEPENDS ${MAIN_TEX}
                )
    
    add_custom_target(all-formats ALL) # Entry point for execution
    add_dependencies(all-formats latex-pdf)
else()
    message("LaTeX tools not found, unable to build tex files")
endif()