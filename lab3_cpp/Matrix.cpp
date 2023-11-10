#include <iostream>
#include "Matrix.h"

namespace matrix {

    template <typename T>
    Matrix<T>::Matrix(int r, int c) : curRows(0), curCols(0), rows(r), cols(c) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
        for (int i = 0; i < curRows; i++) {
            for (int j = 0; j < curCols; j++) {
                data[i][j] = 0;
            }
        }
    }

    // копирующий конструктор
    template <typename T>
    Matrix<T>::Matrix(Matrix <T> &matr) {
        rows = matr.rows;
        cols = matr.cols;
        curRows = matr.curRows;
        curCols = matr.curCols;
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }

        for (int i = 0; i < matr.curRows; i++) {
            for (int j = 0; j < matr.curCols; j++) {
                data[i][j] = matr.data[i][j];
            }
        }
    }

    // перемещающий конструктор
    template <typename T>
    Matrix<T>::Matrix(Matrix<T> &&matr) noexcept: curRows(matr.curRows), curCols(matr.curCols), rows(matr.rows), cols(matr.cols), data(matr.data) {
        for (int i = 0; i < rows; i++) {
            delete [] matr.data[i];
        }
        matr.rows = 0;
        matr.cols = 0;
        matr.curRows = 0;
        matr.curCols = 0;
        delete [] matr.data;
    }

    template <typename T>
    void Matrix<T>::resizeRow(int nsize) {
        if (nsize < rows) throw std::runtime_error("New size is too small");
        T **new_matr = new T*[nsize];
        for (int i = 0; i < nsize; i++) {
            new_matr[i] = new T[cols];
        }
        std::move(data, data + curRows, new_matr);
        rows = nsize;
        delete [] data;
        data = new_matr;
    }

    template <typename T>
    void Matrix<T>::resizeColumn(int nsize) {
        if (nsize < cols) throw std::runtime_error("New size is too small");
        T **new_matr = new T*[rows];
        for (int i = 0; i < rows; i++) {
            new_matr[i] = new T[nsize];
        }
        std::move(data, data + curRows, new_matr);
        cols = nsize;
        delete [] data;
        data = new_matr;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::pushBackRow(T &arr, int size) {
        if (++curRows == rows) resizeRow(rows + QUOTA);
        std::move(arr, arr + size, data[curRows]);
    }

    template<typename T>
    Matrix<T> &Matrix<T>::pushBackColumn(T &arr) {
    }

    template<typename T>
    T Matrix<T>::getRow(int index) const {
        return nullptr;
    }

    template<typename T>
    int Matrix<T>::find(T value) {
        return 0;
    }

    template<typename T>
    T &Matrix<T>::getElement(int x, int y) const {
        if (x < curRows && y < curCols) return *data[x][y];
        return nullptr;
    }

    template<typename T>
    Matrix<T> &Matrix<T>::setElement(int x, int y, T value) {
    }

    template<typename T>
    Matrix<T> &Matrix<T>::popColumn(T &arr) {
    }

    template<typename T>
    Matrix<T> &Matrix<T>::popRow(T &arr) {
    }

    template<typename T>
    Matrix<T> &Matrix<T>::pushStartColumn(T &arr) {
    }

    template<typename T>
    Matrix<T> &Matrix<T>::pushStartRow(T &arr) {
    }

    template<typename T>
    Matrix<T> &Matrix<T>::addRow(T &arr) {
    }


    template<typename T>
    Matrix<T>::Matrix() : curRows(0), curCols(0), rows(QUOTA), cols(QUOTA) {
        T **data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &c, Matrix<T1> &matr) {
        if (matr.rows == 0) return c << "MATRIX is clear";
        for (int i = 0; i < matr.curRows; i++) {
            for (int j = 0; j < matr.curCols; j++) {
                c << matr.data[i][j] << " ";
            }
            c << std::endl;
        }
        return c;
    }



} // matrix