#include <iostream>
#include <omp.h>
#include <ctime>
#include <cmath>

#include "Matrix.h"

using namespace std;

Matrix::Matrix(size_t numRows, size_t numColumns) {
    setNumRows(numRows);
    setNumColumns(numColumns);

    initFirstMatrix();
    initSecondMatrix();
    initResultMatrix();

    setFirstMatrix();
    setSecondMatrix();
}

Matrix::~Matrix() = default;

void Matrix::setNumThreads(int numThreads) {
    omp_set_dynamic(0);
    omp_set_num_threads(numThreads);
    this->numThreads = numThreads;
}

void Matrix::setNumRows(size_t numRows) {
    this->numRows = numRows;
}

size_t Matrix::getNumRows() const {
    return numRows;
}

void Matrix::setNumColumns(size_t numColumns) {
    this->numColumns = numColumns;
}

size_t Matrix::getNumColumns() const {
    return numColumns;
}

void Matrix::initFirstMatrix() {
    this->firstMatrix = new int *[this->numRows];
    for (size_t i = 0; i < this->numColumns; i++) {
        this->firstMatrix[i] = new int[this->numRows];
    }
}

void Matrix::setFirstMatrix() {
    for (size_t i = 0; i < this->numColumns; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            this->firstMatrix[i][j] = rand();
        }
    }
}

void Matrix::showFirstMatrix() {
    for (size_t i = 0; i < this->numColumns; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            cout << firstMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::initSecondMatrix() {
    this->secondMatrix = new int *[this->numColumns];
    for (size_t i = 0; i < this->numRows; i++) {
        this->secondMatrix[i] = new int[this->numColumns];
    }
}

void Matrix::setSecondMatrix() {
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numColumns; j++) {
            this->secondMatrix[i][j] = rand();
        }
    }
}

void Matrix::showSecondMatrix() {
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numColumns; j++) {
            cout << secondMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::initResultMatrix() {
    this->resultMatrix = new int *[this->numColumns];
    for (size_t i = 0; i < this->numColumns; i++) {
        this->resultMatrix[i] = new int[this->numColumns];
    }
}

void Matrix::showResultMatrix() {
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void Matrix::initExecutingTimeWithOmp() {
    this->executingTimeWithOmp = omp_get_wtime();
}

void Matrix::setExecutingTimeWithOmp() {
    this->executingTimeWithOmp = omp_get_wtime() - this->executingTimeWithOmp;
}

double Matrix::getExecutingTimeWithOmp() {
    return this->executingTimeWithOmp;
}

void Matrix::initExecutingTimeWithoutOmp() {
    this->executingTimeWithoutOmp = clock();
}

void Matrix::setExecutingTimeWithoutOmp() {
    this->executingTimeWithoutOmp = (clock() - omp_get_wtime()) / double(CLOCKS_PER_SEC);
}

double Matrix::getExecutingTimeWithoutOmp() {
    return this->executingTimeWithoutOmp;
}

void Matrix::multiplyTwoMatricesWithOmpDefault() {
    initExecutingTimeWithOmp();
#pragma omp parallel
    {
        for (size_t i = 0; i < this->numRows; i++) {
            for (size_t j = 0; j < this->numColumns; j++) {
                for (size_t k = 0; k < this->numRows; k++) {
                    this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
                }
            }
        }
    }
    setExecutingTimeWithOmp();
}

void Matrix::multiplyTwoMatricesWithOmpStatic(int numThreads, size_t chunkSize) {
    setNumThreads(numThreads);
    initExecutingTimeWithOmp();
#pragma omp parallel
    {
#pragma omp for schedule(static, chunkSize)
        for (size_t i = 0; i < this->numRows; i++) {
            for (size_t j = 0; j < this->numColumns; j++) {
                for (size_t k = 0; k < this->numRows; k++) {
                    this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
                }
            }
        }
    }
    setExecutingTimeWithOmp();
}

void Matrix::multiplyTwoMatricesWithOmpDynamic(int numThreads, size_t chunkSize) {
    setNumThreads(numThreads);
    initExecutingTimeWithOmp();
#pragma omp parallel
    {
#pragma omp for schedule(dynamic, chunkSize)
        for (size_t i = 0; i < this->numRows; i++) {
            for (size_t j = 0; j < this->numColumns; j++) {
                for (size_t k = 0; k < this->numRows; k++) {
                    this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
                }
            }
        }
    }
    setExecutingTimeWithOmp();
}

void Matrix::multiplyTwoMatricesWithOmpGuided(int numThreads, size_t chunkSize) {
    setNumThreads(numThreads);
    initExecutingTimeWithOmp();
#pragma omp parallel
    {
#pragma omp for schedule(guided, chunkSize)
        for (size_t i = 0; i < this->numRows; i++) {
            for (size_t j = 0; j < this->numColumns; j++) {
                for (size_t k = 0; k < this->numRows; k++) {
                    this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
                }
            }
        }
    }
    setExecutingTimeWithOmp();
}

void Matrix::multiplyTwoMatricesWithOmpRuntime(int numThreads) {
    setNumThreads(numThreads);
    initExecutingTimeWithOmp();
    int rowsPerThread = ceil(this->numColumns * 1. / numThreads);
#pragma omp parallel
    {
        int threadNum = omp_get_thread_num();
        size_t rowBegin = threadNum * rowsPerThread;
        size_t rowEnd = rowBegin + rowsPerThread;

        for (size_t i = rowBegin; i < min(rowEnd, this->numRows); i++) {
            for (size_t j = 0; j < this->numColumns; j++) {
                for (size_t k = 0; k < this->numRows; k++) {
                    this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
                }
            }
        }
    }
    setExecutingTimeWithOmp();
}

void Matrix::multiplyTwoMatricesWithoutOmp() {
    initExecutingTimeWithoutOmp();
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numColumns; j++) {
            for (size_t k = 0; k < this->numRows; k++) {
                this->resultMatrix[i][j] += this->firstMatrix[i][k] * this->secondMatrix[k][j];
            }
        }
    }
    setExecutingTimeWithoutOmp();
}


