#include <iostream>
#include "Matrix.h"

int main() {
    matrix::Matrix<int> matr(10, 10);
    std::cout << matr;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
