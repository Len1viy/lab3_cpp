#include <iostream>
#include "matrix.h"

// Сделать проверку на ввод элемента в уже занятую ячейку

namespace Input {

    void deleteMatrix(Matrix &matrix) {
        delete[] matrix.rowIndexes;
        delete[] matrix.values;
        matrix.n = 0;
        matrix.m = 0;
        matrix.countOfValues = 0;
        matrix.values = nullptr;
        matrix.rowIndexes = nullptr;
    }


    int comp(const Values *a, const Values *b) {
        return a->y - b->y;
    }


    int createRowIndexes(Matrix &matrix) {
        int curElements = 0;
        createNewArray(&matrix.rowIndexes, matrix.n + 1);
        matrix.rowIndexes[0] = 0;
        for (int i = 0; i < matrix.countOfValues; i++) {
            curElements++;
            for (int j = matrix.values[i].y + 1; j < matrix.n + 1; j++) {
                matrix.rowIndexes[j] = curElements;
            }
        }
        return 1;
    }

    int input(Matrix &matrix) {
        try {
            cout << "Input count of lines >>> ";
            int check = getNum(matrix.n);
            while (matrix.n <= 0 || check == 1) {
                cout << "ERROR WITH COUNT OF ROWS" << endl;
                cout << "Input count of lines >>> ";
                getNum(matrix.n);
            }
            cout << "Input count of columns >>> ";
            check = getNum(matrix.m);
            while (matrix.m <= 0 || check == 1) {
                cout << "ERROR WITH COUNT OF COLUMNS" << endl;
                cout << "Input count of columns >>> ";
                getNum(matrix.m);
            }
            cout << "Input count of not null elements >>> ";
            check = getNum(matrix.countOfValues);
            while (matrix.countOfValues <= 0 || check == 1 || matrix.countOfValues > matrix.n * matrix.m) {
                cout << "ERROR WITH COUNT" << endl;
                cout << "Input count of not null elements >>> ";
                check = getNum(matrix.countOfValues);
            }
            matrix.values = new Values[matrix.countOfValues];
            for (int i = 0; i < matrix.countOfValues; i++) {
                cout << "Input number of line and column for " << i + 1 << " value (line column) >>> ";
                check = getTwoNum(matrix.values[i].y, matrix.values[i].x);
                while (matrix.values[i].y < 0 || matrix.values[i].y >= matrix.n || matrix.values[i].x < 0 || matrix.values[i].x >= matrix.m || check == 1) {
                    cout << "ERROR WUTH INDEXES" << endl;
                    cout << "Input number of line and column for " << i + 1 << " value (line column) >>> ";
                    check = getTwoNum(matrix.values[i].y, matrix.values[i].x);
                }
                cout << "Input value for element [" << matrix.values[i].y << "][" << matrix.values[i].x << "] >>> ";
                check = getNum(matrix.values[i].value);
                while (check == 1) {
                    cout << "ERROR WITH VALUE" << endl;
                    cout << "Input value for element [" << matrix.values[i].y << "][" << matrix.values[i].x << "] >>> ";
                    check = getNum(matrix.values[i].value);
                }
            }
            qsort(matrix.values, matrix.countOfValues, sizeof(Values),
                  reinterpret_cast<int (*)(const void *,const void *)>(comp));
            createRowIndexes(matrix);
        } catch (...) {
            throw;
        }
        return 0;
    }


    void help() {
        std::cout << "COMMANDS:" << std::endl << "0 - Exit programm;" << std::endl << "1 - Initial matrix;" << std::endl
                  << "2 - Get answer;" << std::endl << "3 - Show matrix;" << std::endl << "9 - Instruction;"
                  << std::endl;
    }

    double *individualTask(const Matrix &matrix) {
        if (matrix.n == 0) {
            std::cout << "Matrix is free. Try to initial matrix and repeat this action." << std::endl;
            return nullptr;
        }
        double *answer;
        createNewArray(&answer, matrix.n);
        double sum;
        double *curLine;
        createNewArray(&curLine, matrix.m);
        double *prevLine;
        createNewArray(&prevLine, matrix.m);
        for (int i = 1; i < matrix.n + 1; i++) {
            sum = 0;
            int startInd = matrix.rowIndexes[i - 1];
            int endInd = matrix.rowIndexes[i];
            if (i == 1) {
                for (int j = startInd; j < endInd; j++) {
                    prevLine[matrix.values[j].x] = matrix.values[j].value;
                }
            } else {
                for (int j = startInd; j < endInd; j++) {
                    curLine[matrix.values[j].x] = matrix.values[j].value;
                }
                for (int j = 0; j < matrix.m; j++) {
                    if (curLine[j] > prevLine[j] && curLine[j] != 0) {
                        sum += curLine[j];
                    }
                    prevLine[j] = curLine[j];
                    curLine[j] = 0;
                }
                answer[i - 1] = sum;
            }
        }
        sum = 0;
        for (int j = 0; j < matrix.rowIndexes[1]; j++) {
            curLine[matrix.values[j].x] = matrix.values[j].value;
        }
        for (int j = 0; j < matrix.m; j++) {
            if (curLine[j] > prevLine[j] && curLine[j] != 0) {
                sum += curLine[j];
            }
        }
        answer[0] = sum;
        delete[] curLine;
        delete[] prevLine;
        return answer;
    }



    void showMatrix(const Matrix &matrix) {
        if (matrix.n == 0 || matrix.m == 0) {
            std::cout << "Matrix is free. Try to initial matrix and repeat this action." << std::endl;
            return;
        }
        std::cout << "MATRIX: " << std::endl;
        double *array;
        for (int i = 0; i < matrix.countOfValues; i++) {
            cout << "[" << matrix.values[i].y << "][" << matrix.values[i].x << "] = " << matrix.values[i].value << endl;
        }
//        createNewArray(&array, matrix.m);
//        for (int i = 0; i < matrix.n; i++) {
//            int startIndex = matrix.rowIndexes[i];
//            int endIndex = matrix.rowIndexes[i + 1];
//            for (int j = startIndex; j < endIndex; j++) {
//                array[matrix.values[j].x] = matrix.values[j].value;
//            }
//            std::cout << "[";
//            for (int element = 0; element < matrix.m; element++) {
//                if (element != matrix.m - 1) std::cout << array[element] << ", ";
//                else std::cout << array[element] << "]\n";
//                array[element] = 0;
//            }
//        }
//        delete[] array;
    }
}

