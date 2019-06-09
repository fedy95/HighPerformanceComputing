#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Integral/Integral.h"

using namespace std;


int main() {

    for (int numThreads = 1; numThreads <= 8; numThreads++) {
        for (int numPoints = 2000; numPoints <= 12000; numPoints += 1000) {
            auto *integral = new Integral(.1, 1., numPoints);

            integral->calculateIntegralWithoutSpecialComputing();
            integral->calculateIntegralWithAtomicComputing(numThreads);
            integral->calculateIntegralWithCriticalComputing(numThreads);
            integral->calculateIntegralWithLockComputing(numThreads);
            integral->calculateIntegralWithReductionComputing();

            delete integral;
        }
    }

    return 0;
}