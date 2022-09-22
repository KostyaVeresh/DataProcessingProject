#pragma once

#include <QVector>

class Statistics
{
public:
    Statistics();
    static double expectation(const QVector<double> &vec);
    static double meanSquare(const QVector<double> &vec);
    static double meanSquareDeviation(const QVector<double> &vec);
    static double dispertion(const QVector<double> &vec);
    static double standartDeviation(const QVector<double> &vec);
    static double assymetry(const QVector<double> &vec);
    static double curtosis(const QVector<double> &vec);
private:
    static double nthCentralMoment(const QVector<double> &vec, int n);
};
