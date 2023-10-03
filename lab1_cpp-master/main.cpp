    #include <iostream>
    #include "matrix.h"

    using namespace Input;

    int main() {
        Matrix matrix = Matrix();
        int command = -1;
        int n = 0;
        help();
        try {
            while (command != 0 && n == 0) {
                std::cout << "Your command >>> ";
                n = getNum(command);
                if (command == 1) {
                    if (matrix.n != 0) deleteMatrix(matrix);
                    input(matrix);
                } else if (command == 2) {
                    showMatrix(matrix);
                    double *answer = individualTask(matrix);
                    std::cout << "ANSWER:" << std::endl;
                    showArray(answer, matrix.n);
                    delete[] answer;
                } else if (command == 3) {
                    showMatrix(matrix);
                } else if (command == 9) {
                    help();
                }
            }
        } catch (std::bad_alloc &ba) {
            std::cerr << "Not enough memory" << std::endl;
            deleteMatrix(matrix);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            deleteMatrix(matrix);
            return 1;
        }
        if (matrix.n != 0) deleteMatrix(matrix);

        return 0;
    }