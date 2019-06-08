#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Matrix/Matrix.h"

using namespace std;


int main() {
    ofstream resultsAll("../_results/all.md");

    if (resultsAll) {
        resultsAll << "|method|N|M|threads|chunkSize|Executing time|" << endl;

        for (size_t matrixSide = 10; matrixSide <= 500; matrixSide += 10) {
            auto *matrix = new Matrix(matrixSide, matrixSide);

            matrix->multiplyTwoMatricesWithoutOmp();
            resultsAll << "|" << "WithoutOmp" << "|" << matrixSide << "|" << matrixSide << "|" << "1" << "|"
                    << "not defined" << "|" << matrix->getExecutingTimeWithoutOmp() << "|" << endl;

            for (int numThreads = 1; numThreads <= 8; numThreads++) {
                for (size_t chunkSize = 1; chunkSize <= matrixSide; chunkSize += 10) {
                    matrix->multiplyTwoMatricesWithOmpStatic(numThreads, chunkSize);
                    resultsAll << "|" << "Static" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                           << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;

                    matrix->multiplyTwoMatricesWithOmpDynamic(numThreads, chunkSize);
                    resultsAll << "|" << "Dynamic" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                            << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;

                    matrix->multiplyTwoMatricesWithOmpGuided(numThreads, chunkSize);
                    resultsAll << "|" << "Guided" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                           << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;
                }

                matrix->multiplyTwoMatricesWithOmpRuntime(numThreads);
                resultsAll << "|" << "Guided" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                       << "not defined" << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;
                cout << "matrixSide= " << matrixSide << " | numThreads= " << numThreads << endl;
            }
            delete matrix;
        }

        resultsAll.close();
        return 0;
    } else {
        cout << "Couldn't generate file" << endl;
        return 1;
    }
}
