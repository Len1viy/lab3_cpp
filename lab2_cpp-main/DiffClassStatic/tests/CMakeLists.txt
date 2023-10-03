add_executable(tests_Static testing.cpp  ../../catch.hpp)

add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)