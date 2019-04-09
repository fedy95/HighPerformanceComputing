cmake_minimum_required(VERSION 3.10)
project(1__Matrix_multiplication_in_OpenMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(executeTests test/matrixTest.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread)

add_executable(1__Matrix_multiplication_in_OpenMP main.cpp Matrix/Matrix.cpp Matrix/Matrix.h test/matrixTest.cpp)