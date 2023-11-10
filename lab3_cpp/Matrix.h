//
// Created by vadim on 21.10.2023.
//

#ifndef LAB3_CPP_MATRIX_H
#define LAB3_CPP_MATRIX_H
#include <vector>
namespace matrix {

    template <typename T>
    class Matrix {
    private:
        int curRows;
        int curCols;
        int rows;
        int cols;
        static const int QUOTA = 10;
        T **data;
        void resizeRow(int nsize);
        void resizeColumn(int nsize);
    public:
        Matrix(int r, int c);
        Matrix();
        // перемещающий конструктор
        Matrix(Matrix<T> &&matr) noexcept;
        // копирующий конструктор
        Matrix(Matrix <T> &matr);
        [[nodiscard]] int getRows() const {return curRows;}
        [[nodiscard]] int getCols() const {return curCols;}
        Matrix &addRow(T &arr);
        Matrix &pushBackRow(T &arr, int size);
        Matrix &pushBackColumn(T &arr);
        Matrix &pushStartRow(T &arr);
        Matrix &pushStartColumn(T &arr);
        Matrix &popRow(T &arr);
        Matrix &popColumn(T &arr);
        Matrix &setElement(int x, int y, T value);
        T &getElement(int x, int y) const;
        int find(T value);
        T getRow(int index) const;

        template<typename T1> friend std::ostream operator<<(std::ostream &, Matrix<T1> &);
    };



} // matrix



#endif //LAB3_CPP_MATRIX_H
