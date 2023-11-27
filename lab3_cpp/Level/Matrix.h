//
// Created by vadim on 21.10.2023.
//

#ifndef LAB3_CPP_MATRIX_H
#define LAB3_CPP_MATRIX_H

#include <vector>
#include <iostream>
#include <functional>

/**
* @brief template class matrix
*/
template<typename T>
class Matrix {
private:
    int curRows = 0;
    int curCols = 0;
    T **data;
public:

//        template<typename T3>
//        class MatrixSpecificIterator {
//        public:
//            MatrixSpecificIterator(Matrix<T> &matrix, int index, predicate) : matrix(matrix), index(index), predicate(predicate) {};
//        };

/**
 * @brief default matrix iterator
 * @tparam T2 type of items in the matrix
 */
    template<typename T2>
    class MatrixIterator {
    public:
        /**
         * Constructor
         * @param matrix matrix which we want to iterate
         * @param index index of iterator start
         */
        MatrixIterator(Matrix<T> &matrix, int index) : matrix(matrix), index(index) {}

/**
 * @brief overloaded prefix operator ++
 * @return the next element of the matrix
 */
        MatrixIterator &operator++() {
            ++index;
            return *this;
        }

/**
 * @brief overloaded postfix operator ++
 * @return iterator which describe previous element of matrix after moving to the pointer to the next element
 */
        MatrixIterator operator++(int) {
            MatrixIterator temp = *this;
            ++(*this);
            return temp;
        }

/**
 * @brief overloaded operator + which move the iterator on "other" steps
 * @param other count of elements which we want to skip
 * @return iterator which describe element after "other" elements from previous value
 */
        MatrixIterator &operator+(int other) {
            index += other;
            return *this;
        }

/**
 * @brief getter of index of element on which iterator indicates
 * @return index
 */
        int getIndex() const { return index; }

        /**
         * @brief getter of x component of element on which iterator indicate
         * @return x component
         */
        int getX() const { return index % matrix.getCols(); }

        /**
         * @brief getter of y component of element on which iterator indicate
         * @return y component
         */
        int getY() const { return (int) (index / matrix.getCols()); }

/// \brief overloaded operator == which compare two iterators
/// \param other the other iterator with which we want to compare
/// \return true if iterators are equal and false otherwise (indexes should be equal for true)
        bool operator==(const MatrixIterator &other) const {
            return index == other.index;
        }

/// \brief overloaded operator != which compare two iterators
/// \param other the other iterator with which we want to compare
/// \return true if iterators are not equal and false otherwise (indexes should be not equal for true)
        bool operator!=(const MatrixIterator &other) const {
            return index != other.index;
        }

/**
 * @brief overloaded pointer
 * @return pointer on element of matrix by index
 */
        T &operator*() {
            return matrix.data[(int) (index / matrix.curCols)][index % matrix.curCols];
        }

    private:
        Matrix<T> &matrix;
        int index;
//            Predicate func;
    };

/**
 * @brief special class for overload [][]
 * @tparam type type of row
 */
    template<typename type>
    class Row {
    public:
        /**
         * @brief constructor
         * @param nrow row from which we want to get element by adress
         */
        Row(type *nrow) : row(nrow) {};

        /**
         * @brief overloaded operator []
         * @param index index of element in the row which we want to get
         * @return element of row
         */
        type *operator[](int index) {
            return &(row[index]);
        }

    private:
        type *row;
    };

/**
 * @brief special iterator that works according to a special rule that we pass to the lambda function
 * @tparam T2 type of elements in the matrix
 */
    template<typename T2>
    class MatrixSpecialIterator {
    public:
        /**
         * @brief constructor
         * @param matrix - matrix which we want to iterate
         * @param index - iterator start index
         * @param f1 - the rule by which we will iterate over the elements
         */
        MatrixSpecialIterator(Matrix<T> &matrix, int index, std::function<bool(int index)> f1) : matrix(matrix),
                                                                                                 index(index) {
            check = f1;
        }

/**
 * @brief overloaded operator of prefix ++
 * @return iterator which indicates on the next element
 */
        MatrixSpecialIterator &operator++() {
            do {
                ++index;
            } while (index < matrix.getSize() && !(check(index)));
            return *this;
        };

/**
 * @brief overloaded operator ==
 * @param other - other iterator with which we want to compare
 * @return true if indexes are equal and false otherwise
 */
        bool operator==(const MatrixSpecialIterator &other) const {
            return index == other.index;
        }

/**
 * @brief overloaded operator !=
 * @param other - other iterator with which we want to compare
 * @return true if indexes are not equal and false otherwise
 */
        bool operator!=(const MatrixSpecialIterator &other) const {
            return index != other.index;
        }

/**
 * @brief overloaded pointer
 * @return element of matrix by index
 */
        T &operator*() {
            return matrix.data[(int) (index / matrix.curCols)][index % matrix.curCols];
        };

/**
 * @brief overloaded operator postfix ++
 * @return iterator which indicates on the next element without special rule (works like in usual iterator)
 */
        MatrixSpecialIterator &operator++(int) {
            MatrixSpecialIterator temp = *this;
            ++(*this);
            return temp;
        }

/**
 * @brief getter of the index
 * @return index of element in matrix on which iterator indicates
 */
        [[nodiscard]] int getIndex() const { return index; }

    private:
        Matrix<T> &matrix;
        int index;
        std::function<bool(int index)> check;
    };

    /**
     * @brief begin for usual iterator
     * @return iterator which indicates on the first element of matrix
     */
    MatrixIterator<Matrix> begin() {
        return MatrixIterator<Matrix>(*this, 0);
    }

/**
 * @brief end for usual iterator
 * @return iterator which indicates on the end of matrix (on one element further the last)
 */
    MatrixIterator<Matrix> end() {
        return MatrixIterator<Matrix>(*this, getSize());
    }

    /**
     * @brief begin for special iterator
     * @param f - special rule by which we want to iterate over elements
     * @return iterator which indicates on the first element of matrix which satisfies the transmitted rule
     */
    MatrixSpecialIterator<Matrix> beginSpecial(std::function<bool(int index)> f) {
        return MatrixSpecialIterator<Matrix>(*this, 0, f);
    }

/**
 * @brief end for special iterator
 * @param f - special rule by which we want to iterate over elements
 * @return iterator which indicates on the end of matrix (on one element further the last)
 */
    MatrixSpecialIterator<Matrix> endSpecial(std::function<bool(int index)> f) {
        return MatrixSpecialIterator<Matrix>(*this, getSize(), f);
    }

/**
 * @brief getter of count of rows in the matrix
 * @return count of rows in the matrix
 */
    [[nodiscard]] int getRows() const { return curRows; }

/**
 * @brief getter of count of columns in the matrix
 * @return count of columns in the matrix
 */
    [[nodiscard]] int getCols() const { return curCols; }

/**
 * @brief getter of element by coordinates
 * @param y y component of position element in the matrix
 * @param x x component of position element in the matrix
 * @return element of the matrix which locates on the (x, y) point
 */
    T getElement(int y, int x) {
        if (x > curCols || y > curRows) throw std::range_error("Index out of range");
        return data[y][x];
    };

/**
 * @brief getter of pointer to element by coordinates
 * @param y y component of position element in the matrix
 * @param x x component of position element in the matrix
 * @return pointer to element of the matrix which locates on the (x, y) point
 */
    T *getElementByAdress(int y, int x) {
        if (x > curCols || y > curRows) throw std::range_error("Index out of range");
        return &(data[y][x]);
    }

/**
 * @brief default constructor
 */
    Matrix() : curRows(0), curCols(0) {};

//        ~Matrix() {
//        }
/**
 * @brief constructor
 * @param r count of rows in the matrix which we want to create
 * @param c count of columns in the matrix which we want to create
 */
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
/**
 * @brief copy constructor of the matrix
 * @param matr the other matrix which we want to copy
 */
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
/**
 * @brief move constructor of the matrix
 * @param matr the other matrix which we want to move
 */
    // перемещающий конструктор
    Matrix(Matrix<T> &&matr) {
        if (curRows != 0 && curCols != 0) delete[] data;
        curRows = matr.curRows;
        curCols = matr.curCols;
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

/**
 * @brief getter of size of the matrix
 * @return size of the matrix
 */
    int getSize() {
        return curRows * curCols;
    }

/**
 * @brief function of resizing matrix by rows
 * @param nsize new count of rows which we want to have on our matrix
 */
    void resizeRow(int nsize) {
        if (nsize < curRows) throw std::runtime_error("New size is too small");
        T **new_matr = new T *[nsize];
        for (int i = 0; i < nsize; i++) {
            new_matr[i] = new T[curCols];
        }
        curRows = nsize;
        std::move(data, data + curRows, new_matr);

        delete[] data;
        data = new_matr;
    }

/**
 * @brief function of resizing matrix by columns
 * @param nsize new count of columns which we want to have on our matrix
 */
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

//        Matrix<T> &pushBackRow(T &arr, int size) {
//            resizeRow(curRows + 1);
//            std::move(arr, arr + size, data[curRows]);
//        }
//
//        Matrix<T> &pushBackColumn(T &arr) {
//        }
/**
 * @brief getter of row by index
 * @param index index of row which we want to get
 * @return row which we want to get
 */
    T *getRow(int index) const {
        return data[index];
    }

/**
 * @brief overloaded operator []
 * @param index index of row which we want to get
 * @return row which we want to get
 */
    Row<T> operator[](int index) const {
        return Row<T>(data[index]);
    }

/**
 * @brief find of element by value
 * @param value value which we want to find in the matrix
 * @return index of element
 */
    int find(T value) {
        for (auto i = begin(); i != end(); i++) {
            if (*i == value) {
                return i.getIndex();
            }
        }
        return -1;
    }

/**
 * @brief setter of element to point (x, y)
 * @param x - x component of element which we want to update
 * @param y - y component of element which we want to update
 * @param value - value of element which we want to set
 * @return changed matrix
 */
    Matrix<T> &setElement(int x, int y, T value) {
        if (x > curCols || y > curRows) return std::range_error("Index out of range!");
        data[y][x] = value;
        return *this;
    }

/**
 * @brief pop element from row
 * @param arr pointer to row from which we want to delete element
 * @param index index of element for deleting
 * @return deleted element
 */
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
/**
 * @brief delete the column from the matrix
 * @param index index of column which we want to delete
 * @return changed matrix
 */
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

/**
 * @brief delete the row from the matrix
 * @param index index of row which we want to delete
 * @return changed matrix
 */
    Matrix<T> &popRow(int index) {
        for (int i = index; i < curRows - 1; i++) {
            data[i] = data[i + 1];
        }
        curRows--;
        return *this;
    }

/**
 * @brief add the row to the matrix
 * @param arr row which we want to add
 * @return changed matrix
 */
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
