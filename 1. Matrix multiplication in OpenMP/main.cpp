#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <iostream>

#include "Matrix/Matrix.h"

using namespace std;

//void multiplexTwoMatrixWithOmp(double firstMatrix, double secondMatrix, double resultMatrix, int N, int M) {
//#pragma omp parallel
//    {
//        int i, j, k;
//        double element = 0;
//
//#pragma omp for
//        for (i = 0; i < N; i++) {
//            for (j = 0; j < M; j++) {
//                for (k = 0; k < N; k++) {
//                    element += firstMatrix[i * N + k] * secondMatrix[k * M + j];
//                }
//                resultMatrix[i * N + j] = element;
//                element = 0;
//            }
//        }
//    }
//}


int main() {

    auto *matrix = new Matrix(1000, 1000);

    matrix->multiplyTwoMatricesWithOmp();
    std::cout << std::endl;
    cout << matrix->getExecutingTimeWithOmp();

    matrix->multiplyTwoMatricesWithoutOmp();
    std::cout << std::endl;
    cout << matrix->getExecutingTimeWithoutOmp();
    delete matrix;
    cout << endl;
    cout << endl;
    cout << endl;

    return 0;
}