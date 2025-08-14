##--------------------------------------------------------------------------##
## CMakeLists.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

cmake_minimum_required(VERSION 3.21)

# Define the project
project(IterTools
	VERSION 0.1
	DESCRIPTION "A library of iteration utilities"
	LANGUAGES CXX)

# Specify the C++ dialect
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add exportation of compile commands (needed by many IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##--------------------------------------------------------------------------##
## BUILD OPTIONS
##--------------------------------------------------------------------------##

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Type of build")
option(ITERTOOLS_DBC "Enable DBC checks" OFF)
option(ITERTOOLS_BUILD_DOC "Turn on/off Doxygen documentation" ON)
option(ITERTOOLS_ENABLE_TESTS "Turn on/off unit tests" OFF)

##--------------------------------------------------------------------------##
## BUILD DOXYGEN DOCUMENTATION
##--------------------------------------------------------------------------##
if (ITERTOOLS_BUILD_DIC)
  set(DOXYGEN_GENERATE_XML YES)
  set(DOXYGEN_EXCLUDE_PATTERNS "*/tests/*")
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doc)
  include(AddDoxygenTarget)
  add_doxygen_target(doxygen SOURCEDIR ${CMAKE_CURRENT_SOURCE_DIR})
else ()
  message(STATUS "Doxygen documentation disabled")
endif ()

##--------------------------------------------------------------------------##
## Setup Googletest
##--------------------------------------------------------------------------##
if (ITERTOOLS_ENABLE_TESTS)
  find_package(GTest REQUIRED)
  include(CTest)
  enable_testing()
else ()
  message(STATUS "Unit tests disabled")
endif ()

## Build the source
add_subdirectory(src)

##--------------------------------------------------------------------------##
## end of CMakeLists.txt
##--------------------------------------------------------------------------##

