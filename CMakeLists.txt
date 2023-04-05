project(Lab-C LANGUAGES CXX)

cmake_minimum_required(VERSION 3.16)

# Build all binaries to the /bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# Lab files
message(STATUS "Adding Exectables")
set(TASK_DIR "${CMAKE_SOURCE_DIR}/Tasks")

SUBDIRLIST(SUBDIRS ${TASK_DIR})
foreach(subdir ${SUBDIRS})
    message(${subdir})

    file(GLOB src_files "${TASK_DIR}/${subdir}/*.cpp")
    add_executable(${subdir} ${src_files})
endforeach()

option(BUILD_LABBOOK "Build the labbook" OFF)

# Lab Book using LaTeX
if(BUILD_LABBOOK)
    message(STATUS "Preparing for LaTeX")
    find_package(LATEX)
    set(LT_OUT_DIR "${CMAKE_BINARY_DIR}/tex")
    set(LT_WORKING_DIR "${CMAKE_SOURCE_DIR}/LabBook")
    set(MAIN_TEX "${LT_WORKING_DIR}/Lab-C.tex")

    if(LATEX_FOUND AND LATEX_PDFLATEX_FOUND)
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
        message(WARNING "LaTeX tools not found, unable to build tex files")
    endif()
endif()