#pragma once
#ifndef INC_1_MATRIXMATRIX_MULTIPLICATION_IN_OPENMP_MATRIX_H
#define INC_1_MATRIXMATRIX_MULTIPLICATION_IN_OPENMP_MATRIX_H

class Matrix {

public:
    Matrix(size_t numRows, size_t numColumns);

    ~Matrix();

    size_t getNumRows() const;

    size_t getNumColumns() const;

    void showFirstMatrix(), showSecondMatrix(), showResultMatrix();

    double getExecutingTimeWithOmp(), getExecutingTimeWithoutOmp();

    void multiplyTwoMatricesWithOmp(), multiplyTwoMatricesWithoutOmp();

private:
    size_t numRows, numColumns;
    int **firstMatrix, **secondMatrix, **resultMatrix;

    void setNumRows(size_t numRows);

    void setNumColumns(size_t numColumns);

    void initFirstMatrix(), initSecondMatrix(), initResultMatrix();

    void setFirstMatrix(), setSecondMatrix();

    void initExecutingTimeWithOmp(), initExecutingTimeWithoutOmp();

    void setExecutingTimeWithOmp(), setExecutingTimeWithoutOmp();

    double executingTimeWithOmp, executingTimeWithoutOmp;
};

#endif
