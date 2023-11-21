//
// Created by vadim on 21.10.2023.
//

#ifndef LAB3_CPP_MATRIX_H
#define LAB3_CPP_MATRIX_H

#include <vector>
#include <iostream>
#include <functional>


    template<typename T>
    class Matrix {
    private:
        int curRows;
        int curCols;
        T **data;
    public:

//        template<typename T3>
//        class MatrixSpecificIterator {
//        public:
//            MatrixSpecificIterator(Matrix<T> &matrix, int index, predicate) : matrix(matrix), index(index), predicate(predicate) {};
//        };


        template<typename T2>
        class MatrixIterator {
        public:

            MatrixIterator(Matrix<T> &matrix, int index) : matrix(matrix), index(index) {}

            MatrixIterator &operator++() {
                ++index;
                return *this;
            }

            MatrixIterator operator++(int) {
                MatrixIterator temp = *this;
                ++(*this);
                return temp;
            }

            MatrixIterator &operator+(int other) {
                index += other;
                return *this;
            }

            int getIndex() const { return index; }
            int getX() const {return index % matrix.getCols();}
            int getY() const {return (int)(index / matrix.getCols());}

            bool operator==(const MatrixIterator &other) const {
                return index == other.index;
            }

            bool operator!=(const MatrixIterator &other) const {
                return index != other.index;
            }

            T &operator*() {
                return matrix.data[(int) (index / matrix.curCols)][index % matrix.curCols];
            }

        private:
            Matrix<T> &matrix;
            int index;
//            Predicate func;
        };

        template<typename type>
        class Row {
        public:
            Row(type *nrow) : row(nrow) {};
            type *operator[](int index) {
                return &(row[index]);
            }
        private:
            type *row;
        };

        template<typename T2>
        class MatrixSpecialIterator {
        public:
            MatrixSpecialIterator(Matrix<T> &matrix, int index, std::function<bool(int index)> f1) : matrix(matrix), index(index) {
                check = f1;
            }

            MatrixSpecialIterator &operator++() {
                do {
                    ++index;
                } while (index < matrix.getSize() && !(check(index)));
                return *this;
            };


            bool operator==(MatrixSpecialIterator &other) {
                return index == other.index;
            }

            bool operator!=(MatrixSpecialIterator &other) {
                return index != other.index;
            }

            T &operator*(){
                return matrix.data[(int) (index / matrix.curCols)][index % matrix.curCols];
            };

            MatrixSpecialIterator &operator++(int) {
                MatrixSpecialIterator temp = *this;
                ++(*this);
                return temp;
            }

            [[nodiscard]] int getIndex() const {return index;}

        private:
            Matrix<T> &matrix;
            int index;
            std::function<bool(int index)> check;
        };

        MatrixIterator<Matrix> begin() {
            return MatrixIterator<Matrix>(*this, 0);
        }

        MatrixIterator<Matrix> end() {
            return MatrixIterator<Matrix>(*this, getSize());
        }

        MatrixSpecialIterator<Matrix> beginSpecial(std::function<bool (int index)> f) {
            return MatrixSpecialIterator<Matrix>(*this, 0, f);
        }

        MatrixSpecialIterator<Matrix> endSpecial(std::function<bool (int index)> f) {
            return MatrixSpecialIterator<Matrix>(*this, getSize(), f);
        }


        [[nodiscard]] int getRows() const { return curRows; }

        [[nodiscard]] int getCols() const { return curCols; }

        T getElement(int y, int x) {
            if (x > curCols || y > curRows) throw std::range_error("Index out of range");
            return data[y][x];
        };

        T *getElementByAdress(int y, int x) {
            if (x > curCols || y > curRows) throw std::range_error("Index out of range");
            return &(data[y][x]);
        }

        Matrix() : curRows(0), curCols(0) {};

//        ~Matrix() {
//        }

        Matrix(int r, int c) : curRows(r), curCols(c) {
            data = new T *[curRows];
            for (int i = 0; i < curRows; i++) {
                data[i] = new T[curCols];
            }
            for (int i = 0; i < curRows; i++) {
                for (int j = 0; j < curCols; j++) {
                    data[i][j] = T();
                }
            }
        }

        // копирующий конструктор
        Matrix(Matrix<T> &matr) {
            curRows = matr.curRows;
            curCols = matr.curCols;
            data = new T *[curRows];
            for (int i = 0; i < curRows; i++) {
                data[i] = new T[curCols];
            }

            for (int i = 0; i < matr.curRows; i++) {
                for (int j = 0; j < matr.curCols; j++) {
                    data[i][j] = matr.data[i][j];
                }
            }
        }

        // перемещающий конструктор
        Matrix(Matrix<T> &&matr) noexcept: curRows(matr.curRows), curCols(matr.curCols) {
            delete [] data;
            data = new T *[curRows];
            for (int i = 0; i < curRows; i++) {
                data[i] = new T[curCols];
            }
            for (int i = 0; i < curRows; i++) {
                for (int j = 0; j < curCols; j++) {
                    data[i][j] = matr.data[i][j];
                }
            }
            for (int i = 0; i < curRows; i++) {
                delete[] matr.data[i];
            }
            matr.curRows = 0;
            matr.curCols = 0;
            delete[] matr.data;
        }

        int getSize() {
            return curRows * curCols;
        }

        void resizeRow(int nsize) {
            if (nsize < curRows) throw std::runtime_error("New size is too small");
            T **new_matr = new T *[nsize];
            for (int i = 0; i < nsize; i++) {
                new_matr[i] = new T[curCols];
            }
            std::move(data, data + curRows, new_matr);
            curRows = nsize;
            delete[] data;
            data = new_matr;
        }

        void resizeColumn(int nsize) {
            if (nsize < curCols) throw std::runtime_error("New size is too small");
            T **new_matr = new T *[curRows];
            for (int i = 0; i < curRows; i++) {
                new_matr[i] = new T[nsize];
            }
            std::move(data, data + curRows, new_matr);
            curCols = nsize;
            delete[] data;
            data = new_matr;
        }

        Matrix<T> &pushBackRow(T &arr, int size) {
            resizeRow(curRows + 1);
            std::move(arr, arr + size, data[curRows]);
        }

        Matrix<T> &pushBackColumn(T &arr) {
        }

        T *getRow(int index) const {
            return data[index];
        }

        Row<T> operator[](int index) const {
            return Row<T>(data[index]);
        }

        int find(T value) {
            for (auto i = begin(); i != end(); i++) {
                if (*i == value) {
                    return i.getIndex();
                }
            }
            return -1;
        }

        Matrix<T> &setElement(int x, int y, T value) {
            if (x > curCols || y > curRows) return std::range_error("Index out of range!");
            data[y][x] = value;
            return *this;
        }


        T popFromRow(T **arr, int index) {
            T temp = (*arr)[index];
            for (int i = index; i < curCols - 1; i++) {
                (*arr)[i] = (*arr)[i + 1];
            }
            (*arr)[curCols - 1] = temp;
            return temp;

        }

//        void pushToArray(T **returned, T element, int indexRet) {
//            returned[indexRet] = element;
//        }

        Matrix<T> &popColumn(int index) {
//            T *returned = new T[curRows];
            if (index < 0 || index >= curCols) throw std::range_error("Index out of range!");
            int indexRet;
            for (auto i = begin(); i != end(); i++) {
                indexRet = (int) (i.getIndex() / curCols);
                if (i.getIndex() % curCols == index) {
//                    pushToArray(returned, popFromColumn(data[(int) (i.getIndex() / curCols)], indexRet));
                    popFromRow(&data[indexRet], indexRet);
                }
            }

            --curCols;
            return *this;
        }

        Matrix<T> &popRow(int index) {
            for (int i = index; i < curRows - 1; i++) {
                data[i] = data[i + 1];
            }
            curRows--;
            return *this;
        }

//        Matrix<T> pushStartColumn(T &arr) {
//        }
//
//        Matrix<T> pushStartRow(T &arr) {
//        }

        Matrix<T> &addRow(T &arr) {
            curRows++;
            data[curRows - 1] = arr;
            return *this;
        }


        template<typename T1>
        friend std::ostream &operator<<(std::ostream &c, Matrix<T1> &matr);


    };

    template<typename T1>
    std::ostream &operator<<(std::ostream &c, Matrix<T1> &matr) {
        if (matr.curRows == 0) return c << "MATRIX is clear";
        for (auto i = matr.begin(); i != matr.end(); i++) {
            if (i.getIndex() % matr.curCols == 0) c << "\n";
            c << *i << " ";
        }
        c << "\n";
        return c;
    }




#endif //LAB3_CPP_MATRIX_H
