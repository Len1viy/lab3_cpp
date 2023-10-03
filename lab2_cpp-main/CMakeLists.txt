# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(ooplab2)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# SIMPLE CLASS
add_subdirectory(SimpleClass/cards)
add_subdirectory(SimpleClass/input)
add_subdirectory(SimpleClass/tests)

add_executable(mainSimple SimpleClass/main.cpp)

target_link_libraries(mainSimple cards)
target_link_libraries(mainSimple input)

# DIFF CLASS

add_subdirectory(DiffClass/deck)
add_subdirectory(DiffClass/tests)

add_executable(mainDiff DiffClass/main.cpp)

target_link_libraries(mainDiff cards)
target_link_libraries(mainDiff input)
target_link_libraries(mainDiff deckDynamic)

# DIFF CLASS STATIC
add_subdirectory(DiffClassStatic/deck)
add_subdirectory(DiffClassStatic/tests)

add_executable(mainDiffStatic DiffClassStatic/main.cpp)

target_link_libraries(mainDiffStatic cards)
target_link_libraries(mainDiffStatic input)
target_link_libraries(mainDiffStatic deckStatic)



# для сборки из консоли:
#
# mkdir build   # создание директории для файлов сборки
# cd build      # переход в директорию сборки
# cmake ..      # генерация файлов сборки на основе CMakeLists.txt
# make          # сборка проекта
