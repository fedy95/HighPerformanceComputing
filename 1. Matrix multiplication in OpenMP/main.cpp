#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Matrix/Matrix.h"

using namespace std;


int main() {
    ofstream resultsAll("_results/all.csv");
    ofstream resultsWithoutOmp("_results/WithoutOmp.csv");
    ofstream resultsStatic("_results/Static.csv");
    ofstream resultsDynamic("_results/Dynamic.csv");
    ofstream resultsGuided("_results/Guided.csv");
    ofstream resultsRuntime("_results/Runtime.csv");

    if (resultsAll.is_open() && resultsWithoutOmp.is_open() && resultsStatic.is_open() && resultsDynamic.is_open() &&
            resultsGuided.is_open() && resultsRuntime.is_open()) {
        resultsAll << "method;N;M;threads;chunkSize;Executing time;" << endl;
        resultsWithoutOmp << "method;N;M;threads;chunkSize;Executing time;" << endl;
        resultsStatic << "method;N;M;threads;chunkSize;Executing time;" << endl;
        resultsDynamic << "method;N;M;threads;chunkSize;Executing time;" << endl;
        resultsGuided << "method;N;M;threads;chunkSize;Executing time;" << endl;
        resultsRuntime << "method;N;M;threads;chunkSize;Executing time;" << endl;

        for (size_t matrixSide = 10; matrixSide <= 500; matrixSide += 10) {
            auto *matrix = new Matrix(matrixSide, matrixSide);

            matrix->multiplyTwoMatricesWithoutOmp();
            resultsAll << "WithoutOmp" << ";" << matrixSide << ";" << matrixSide << ";" << "1" << ";"
                    << "not defined" << ";" << matrix->getExecutingTimeWithoutOmp() << ";" << endl;
            resultsWithoutOmp << "WithoutOmp" << ";" << matrixSide << ";" << matrixSide << ";" << "1" << ";"
                       << "not defined" << ";" << matrix->getExecutingTimeWithoutOmp() << ";" << endl;

            for (int numThreads = 1; numThreads <= 8; numThreads++) {
                for (size_t chunkSize = 1; chunkSize <= matrixSide; chunkSize += 10) {
                    matrix->multiplyTwoMatricesWithOmpStatic(numThreads, chunkSize);
                    resultsAll << "Static" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                           << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                    resultsStatic << "Static" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                               << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;

                    matrix->multiplyTwoMatricesWithOmpDynamic(numThreads, chunkSize);
                    resultsAll << "Dynamic" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                            << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                    resultsDynamic << "Dynamic" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                               << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;

                    matrix->multiplyTwoMatricesWithOmpGuided(numThreads, chunkSize);
                    resultsAll << "Guided" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                           << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                    resultsGuided << "Guided" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                               << chunkSize << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                }

                matrix->multiplyTwoMatricesWithOmpRuntime(numThreads);
                resultsAll << "Runtime" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                       << "not defined" << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                resultsRuntime << "Runtime" << ";" << matrixSide << ";" << matrixSide << ";" << numThreads << ";"
                           << "not defined" << ";" << matrix->getExecutingTimeWithOmp() << ";" << endl;
                cout << "matrixSide= " << matrixSide << " ; numThreads= " << numThreads << endl;
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
