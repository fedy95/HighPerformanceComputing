cmake_minimum_required(VERSION 3.13)
project(1__Matrix_multiplication_in_OpenMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(1__Matrix_multiplication_in_OpenMP main.cpp Matrix/Matrix.cpp Matrix/Matrix.h)