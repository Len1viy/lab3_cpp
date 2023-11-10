cmake_minimum_required(VERSION 3.27)
project(lab3_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

#add_subdirectory(Interfaces)
#add_subdirectory(Inventory)
#add_subdirectory(Character)
#add_subdirectory(Level)
#
#add_executable(game main.cpp)
#
#target_link_libraries(game characters)
#target_link_libraries()

#add_library(matrix Matrix.h Matrix.cpp)

add_executable(Game main.cpp Matrix.h Matrix.cpp)

#target_link_libraries(Game matrix)