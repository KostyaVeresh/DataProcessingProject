#pragma once

#include<QVector>

class DiscreteData
{
public:
    DiscreteData();

    /// Creates data vector for forward processing and plotting
    /// @param Sequence of Y values
    /// @param First point of absciss axis
    /// @param Discrete step for X values
    DiscreteData(QVector<double> vector, double firstXValue, double discreteStep);
    QVector<double> & getData();
    double getFirstXValue();
    double getDiscreteStep();

private:
    QVector<double> data;
    double firstXValue;
    double discreteStep;
};
