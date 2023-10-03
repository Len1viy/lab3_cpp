#include <iostream>

using namespace std;

namespace Input {

    struct Values {
        int y;
        int x;
        double value;
    };

    struct Matrix {
        int n;
        int m;
        int countOfValues;
        int *rowIndexes;
        Values *values;
    };


    template<class T>
    int getNum(T &a) {
        if (cin >> a && cin.good()) return 0;
        else {
            cin.clear();
            cin.sync();
            return 1;
        }
    }

    template<class T>
    int getTwoNum(T &a, T &b) {
        if (cin >> a >> b && cin.good()) return 0;
        else {
            cin.clear();
            cin.sync();
            return 1;
        }
    }



    template<class T>
    void createNewArray(T **array, int size) {
        *array = new T[size];
        for (int i = 0; i < size; i++) {
            (*array)[i] = 0;
        }
    }

    template<class T>
    void showArray(T &arr, int size) {
        if (size == 0) return;
        for (int i = 0; i < size; i++) {
            if (arr[i] != 0) {
                cout << "[" << i << "] = " << arr[i] << endl;
            }
        }
    }

    int createRowIndexes(Matrix &matrix);
    void help();
    int input(Matrix &matrix);
    void showMatrix(const Matrix &matrix);
    double *individualTask(const Matrix &matrix);
    void deleteMatrix(Matrix &matrix);
}

