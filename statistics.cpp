#include "statistics.h"

#include <cmath>

Statistics::Statistics()
{

}

double Statistics::assymetry(const QVector<double> &vec) {
    return nthCentralMoment(vec, 3);
}

double Statistics::dispertion(const QVector<double> &vec) {
    return nthCentralMoment(vec, 2);
}

double Statistics::curtosis(const QVector<double> &vec) {
    return nthCentralMoment(vec, 4);
}

double Statistics::expectation(const QVector<double> &vec) {
    double result = 0;
    for (double num : vec) {
        result += num;
    }
    return result / vec.size();
}

double Statistics::meanSquare(const QVector<double> &vec) {
    double result = 0;
    for (double num : vec) {
        result += num * num;
    }
    return result / vec.size();
}

double Statistics::meanSquareDeviation(const QVector<double> &vec) {
    return sqrt(meanSquare(vec));
}

double Statistics::standartDeviation(const QVector<double> &vec) {
    return sqrt(dispertion(vec));
}

double Statistics::nthCentralMoment(const QVector<double> &vec, int n) {
    double mean = expectation(vec);
    double result = 0;
    for (double num : vec) {
        result += pow(num - mean, n);
    }
    return result / vec.size();
}
