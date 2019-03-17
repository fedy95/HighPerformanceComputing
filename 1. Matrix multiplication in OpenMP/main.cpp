#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include <fstream>

#include "Matrix/Matrix.h"

using namespace std;


int main() {
    ofstream WithoutOmp("../_results/WithoutOmp.md");
    ofstream Static("../_results/Static.md");
    ofstream Dynamic("../_results/Dynamic.md");
    ofstream Guided("../_results/Guided.md");

    if (WithoutOmp && Static && Dynamic && Guided) {
        WithoutOmp << "|" << "method" << "|" << "N" << "|" << "M" << "|" << "threads" << "|" << "chunkSize" << "|"
                   << "Executing time" << "|" << endl;
        Static << "|" << "method" << "|" << "N" << "|" << "M" << "|" << "threads" << "|" << "chunkSize" << "|"
               << "Executing time" << "|" << endl;
        Dynamic << "|" << "method" << "|" << "N" << "|" << "M" << "|" << "threads" << "|" << "chunkSize" << "|"
                << "Executing time" << "|" << endl;
        Guided << "|" << "method" << "|" << "N" << "|" << "M" << "|" << "threads" << "|" << "chunkSize" << "|"
               << "Executing time" << "|" << endl;
        for (size_t matrixSide = 10; matrixSide < 500; matrixSide += 100) {
            auto *matrix = new Matrix(matrixSide, matrixSide);

            matrix->multiplyTwoMatricesWithoutOmp();
            WithoutOmp << "|" << "WithoutOmp" << "|" << matrixSide << "|" << matrixSide << "|" << "1" << "|" << "-"
                       << "|"
                       << matrix->getExecutingTimeWithoutOmp() << "|" << endl;

            for (int numThreads = 2; numThreads < 4; numThreads++) {
                for (size_t chunkSize = 1; chunkSize < matrixSide; chunkSize += 50) {
                    matrix->multiplyTwoMatricesWithOmpStatic(numThreads, chunkSize);
                    Static << "|" << "Static" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                           << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;

                    matrix->multiplyTwoMatricesWithOmpDynamic(numThreads, chunkSize);
                    Dynamic << "|" << "Dynamic" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                            << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;

                    matrix->multiplyTwoMatricesWithOmpGuided(numThreads, chunkSize);
                    Guided << "|" << "Guided" << "|" << matrixSide << "|" << matrixSide << "|" << numThreads << "|"
                           << chunkSize << "|" << matrix->getExecutingTimeWithOmp() << "|" << endl;
                }
            }
            delete matrix;
        }

        WithoutOmp.close();
        Static.close();
        Dynamic.close();
        Guided.close();
        return 0;
    } else {
        cout << "Couldn't generate file" << endl;
        return 1;
    }
}
