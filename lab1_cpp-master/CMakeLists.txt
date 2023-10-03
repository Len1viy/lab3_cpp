cmake_minimum_required(VERSION 3.23)
project(lab1_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab1_cpp main.cpp matrix.h matrix.cpp)
add_executable(testing test.cpp)
