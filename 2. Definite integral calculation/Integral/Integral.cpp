#include <iostream>
#include <omp.h>
#include <ctime>
#include <cmath>

#include "Integral.h"

using namespace std;

Integral::Integral(double xStart, double xEnd, int numOfPoints) {
    setXStart(xStart);
    setXEnd(xEnd);
    setNumOfPoints(numOfPoints);
}

Integral::~Integral() = default;

void Integral::setXStart(double xStart) {
    this->xStart = xStart;
}

double Integral::getXStart() const {
    return this->xStart;
}

void Integral::setXEnd(double xEnd) {
    this->xEnd = xEnd;
}

double Integral::getXEnd() const {
    return this->xStart;
}

void Integral::setNumOfPoints(int numOfPoints) {
    this->numPoints = numOfPoints;
}

int Integral::getNumOfPoints() const {
    return this->xStart;
}

double Integral::calculateIntegralWithoutSpecialComputing() {
    double yEnd = (-1 / (2 * this->xEnd)) + 0.25 * sin(2. / this->xEnd);
    double yStart = (-1 / (2 * this->xStart)) + 0.25 * sin(2. / this->xStart);

    return yEnd - yStart;
}

double Integral::calculateWidthOfAreaByNumPoints() {
    return (this->xEnd - this->xEnd) / this->numPoints;
}

double Integral::calculateFunction(double x) {
    return (1. / (x * x)) * pow(sin(1. / x), 2);
}

double Integral::calculateAvgOfFunction() {
    return (calculateFunction(this->xEnd) + calculateFunction(this->xStart)) / 2.;
}

void Integral::setNumThreads(int numThreads) {
    omp_set_dynamic(0);
    omp_set_num_threads(numThreads);
    this->numThreads = numThreads;
}

int Integral::getNumPointForThread() {
    return ceil(this->numPoints * 1. / this->numThreads);
}

int Integral::getNumOperationsForComputing() {
    return min((this->numThreads + 1) * this->getNumPointForThread(), this->numPoints);
}

int Integral::getStartWidthForComputing() {
    return max(this->numThreads * this->getNumPointForThread(), 1);
}

double Integral::calculateIntegralWithAtomicComputing(int numThreads) {
    double widthOfArea = this->calculateWidthOfAreaByNumPoints();
    double resultForFunction = this->calculateAvgOfFunction();
    double localResult = 0.;

    setNumThreads(numThreads);

#pragma omp parallel
    {
        for (int deltaX = this->getStartWidthForComputing(); deltaX < this->getNumOperationsForComputing(); deltaX++) {
            double updateX = this->xStart + deltaX * widthOfArea;
            double updateFunction = this->calculateFunction(updateX);
            localResult += updateFunction;
        }

#pragma omp atomic
        resultForFunction += localResult;
    }

    return resultForFunction * widthOfArea;
}

double Integral::calculateIntegralWithCriticalComputing(int numThreads) {
    double widthOfArea = this->calculateWidthOfAreaByNumPoints();
    double resultForFunction = this->calculateAvgOfFunction();
    double localResult = 0.;

    setNumThreads(numThreads);

#pragma omp parallel
    {
        for (int deltaX = this->getStartWidthForComputing(); deltaX < this->getNumOperationsForComputing(); deltaX++) {
            double updateX = this->xStart + deltaX * widthOfArea;
            double updateFunction = this->calculateFunction(updateX);
            localResult += updateFunction;
        }

#pragma omp critical
        {
            resultForFunction += localResult;
        }
    }

    return resultForFunction * widthOfArea;
}

double Integral::calculateIntegralWithLockComputing(int numThreads) {
    double widthOfArea = this->calculateWidthOfAreaByNumPoints();

    omp_lock_t lock;
    omp_init_lock(&lock);

    double resultForFunction = this->calculateAvgOfFunction();
    double localResult = 0.;

    setNumThreads(numThreads);

#pragma omp parallel
    {
        for (int deltaX = this->getStartWidthForComputing(); deltaX < this->getNumOperationsForComputing(); deltaX++) {
            double updateX = this->xStart + deltaX * widthOfArea;
            double updateFunction = this->calculateFunction(updateX);
            localResult += updateFunction;
        }

        omp_set_lock(&lock);
        resultForFunction += localResult;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    return resultForFunction * widthOfArea;
}

double Integral::calculateIntegralWithReductionComputing() {
    double widthOfArea = this->calculateWidthOfAreaByNumPoints();
    double resultForFunction = this->calculateAvgOfFunction();
    double localResult = 0.;

#pragma omp parallel for reduction(+:resultForFunction)
    for (int points = 1; points < this->numPoints; points++) {
        double updateX = this->xStart + points * widthOfArea;
        double updateFunction = this->calculateFunction(updateX);
        localResult += updateFunction;
    }

    return resultForFunction * widthOfArea;
}
