cmake_minimum_required(VERSION 3.10)

# project name
project(SolvePDE VERSION 1.0)

#  C++ required version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# executable name and source code 
add_executable(solvePDE
    solvePDE.cpp
    gridPoints.cpp
)

# include directory for header files
target_include_directories(solvePDE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
