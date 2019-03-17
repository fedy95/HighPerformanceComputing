#include <iostream>
#include <omp.h>
#include <ctime>

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


size_t Matrix::getNumRows() const {
    return numRows;
}

size_t Matrix::getNumColumns() const {
    return numColumns;
}

void Matrix::showFirstMatrix() {
    for (size_t i = 0; i < this->numColumns; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            cout << firstMatrix[i][j] << " ";
        }
        cout << endl;
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

void Matrix::showResultMatrix() {
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::setNumRows(size_t numRows) {
    this->numRows = numRows;
}

void Matrix::setNumColumns(size_t numColumns) {
    this->numColumns = numColumns;
}

void Matrix::initFirstMatrix() {
    this->firstMatrix = new int *[this->numRows];
    for (size_t i = 0; i < this->numColumns; i++) {
        this->firstMatrix[i] = new int[this->numRows];
    }
}

void Matrix::initSecondMatrix() {
    this->secondMatrix = new int *[this->numColumns];
    for (size_t i = 0; i < this->numRows; i++) {
        this->secondMatrix[i] = new int[this->numColumns];
    }
}

void Matrix::initResultMatrix() {
    this->resultMatrix = new int *[this->numColumns];
    for (size_t i = 0; i < this->numColumns; i++) {
        this->resultMatrix[i] = new int[this->numColumns];
    }
}

void Matrix::setFirstMatrix() {
    for (size_t i = 0; i < this->numColumns; i++) {
        for (size_t j = 0; j < this->numRows; j++) {
            this->firstMatrix[i][j] = rand();
        }
    }
}

void Matrix::setSecondMatrix() {
    for (size_t i = 0; i < this->numRows; i++) {
        for (size_t j = 0; j < this->numColumns; j++) {
            this->secondMatrix[i][j] = rand();
        }
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
    this->executingTimeWithoutOmp = (clock() - omp_get_wtime())/double(CLOCKS_PER_SEC);
}

double Matrix::getExecutingTimeWithoutOmp() {
    return this->executingTimeWithoutOmp;
}


void Matrix::multiplyTwoMatricesWithOmp() {
    initExecutingTimeWithOmp();
#pragma omp parallel
    {
#pragma omp for
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








