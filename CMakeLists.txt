# ----------------------------------------------------------
# Project name
# ----------------------------------------------------------

project(OpenFuelCycle CXX)

# ----------------------------------------------------------
# Minimum Cmake version
# ----------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

# ----------------------------------------------------------
# Test CXX compiler and C++11 comptability
# ----------------------------------------------------------

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
IF(COMPILER_SUPPORTS_CXX11)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
ELSE()
  MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()

# Add directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

# ----------------------------------------------------------
# Variables definitions
# ----------------------------------------------------------

set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

# print all
MESSAGE( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY :" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# ----------------------------------------------------------
# Add Directories
# ----------------------------------------------------------

# Add source
ADD_SUBDIRECTORY(source)
