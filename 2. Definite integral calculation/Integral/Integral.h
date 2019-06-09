#pragma once
#ifndef INC_1_MATRIXMATRIX_MULTIPLICATION_IN_OPENMP_MATRIX_H
#define INC_1_MATRIXMATRIX_MULTIPLICATION_IN_OPENMP_MATRIX_H

class Integral {

public:
    Integral(double xStart, double xEnd, int numOfPoints);

    ~Integral();

    double getXStart() const;
    double getXEnd() const;
    int getNumOfPoints() const;

    double calculateIntegralWithoutSpecialComputing();
    double calculateIntegralWithAtomicComputing(int numThreads);
    double calculateIntegralWithCriticalComputing(int numThreads);
    double calculateIntegralWithLockComputing(int numThreads);
    double calculateIntegralWithReductionComputing();

private:
    size_t precision;

    double xStart;
    void setXStart(double xStart);

    double xEnd;
    void setXEnd(double xEnd);

    int numPoints;
    void setNumOfPoints(int numPoints);

    double calculateWidthOfAreaByNumPoints();
    static double calculateFunction(double x);
    double calculateAvgOfFunction();

    int numThreads;
    void setNumThreads(int numThreads);

    int getNumPointForThread();
    int getNumOperationsForComputing();
    int getStartWidthForComputing();

};

#endif
