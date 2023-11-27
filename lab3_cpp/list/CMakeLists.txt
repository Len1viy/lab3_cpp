cmake_minimum_required(VERSION 3.5)

project(list LANGUAGES CXX)


find_package(Catch2 2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_library(list_default INTERFACE include_default/List.h)
target_include_directories(list_default INTERFACE include_default)

add_library(list_union INTERFACE include_union/List.h)
target_include_directories(list_union INTERFACE include_union)

add_library(list_chars INTERFACE include_chars/List.h)
target_include_directories(list_chars INTERFACE include_chars)

add_library(list_allocator INTERFACE include_allocator/List.h)
target_include_directories(list_allocator INTERFACE include_allocator)


add_executable(list_tests_default test/ListTests.cpp)
target_link_libraries(list_tests_default list_default Catch2::Catch2)

add_executable(list_tests_union test/ListTests.cpp)
target_link_libraries(list_tests_union list_union Catch2::Catch2)

add_executable(list_tests_chars test/ListTests.cpp)
target_link_libraries(list_tests_chars list_chars Catch2::Catch2)

add_executable(list_tests_allocator test/ListTests.cpp)
target_link_libraries(list_tests_allocator list_allocator Catch2::Catch2)
