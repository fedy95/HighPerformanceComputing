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

    double getExecutingTimeWithOmp();

    double getExecutingTimeWithoutOmp();

    void multiplyTwoMatricesWithOmpDefault();

    void multiplyTwoMatricesWithoutOmp();

    void multiplyTwoMatricesWithOmpStatic(int numThreads, size_t chunkSize);

    void multiplyTwoMatricesWithOmpDynamic(int numThreads, size_t chunkSize);

    void multiplyTwoMatricesWithOmpGuided(int numThreads, size_t chunkSize);

    void multiplyTwoMatricesWithOmpRuntime(int numThreads, size_t chunkSize);

private:
    size_t numRows, numColumns;
    int numThreads;

    int **firstMatrix, **secondMatrix, **resultMatrix;
    double executingTimeWithOmp, executingTimeWithoutOmp;

    void setNumRows(size_t numRows);

    void setNumColumns(size_t numColumns);

    void initFirstMatrix(), initSecondMatrix(), initResultMatrix();

    void setFirstMatrix(), setSecondMatrix();

    void initExecutingTimeWithOmp();

    void initExecutingTimeWithoutOmp();

    void setExecutingTimeWithOmp();

    void setExecutingTimeWithoutOmp();

    void multiplyTwoMatrices();

    void setNumThreads(int numThreads);
};

#endif
