cmake_minimum_required(VERSION 3.13)
project(2__Definite_integral_calculation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(2__Definite_integral_calculation main.cpp Integral/Integral.cpp Integral/Integral.h)