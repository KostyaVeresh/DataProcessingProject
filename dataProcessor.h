#pragma once

#include "discreteData.h"

class DataProcessor
{
public:
    DataProcessor(DiscreteData data);
    DiscreteData & getCurrentData();
    DataProcessor & addSpikeValues(int numberOfSpikes, int spikeOrder);
    DataProcessor & eliminateSpikeValues(double lowerBound, double upperBound);
    DataProcessor & addShift(double shift);
    DataProcessor & eliminateShift();
    DataProcessor & amplitudeSpectrum();
    DataProcessor & addAnotherFunction(const QVector<double> &toAdd);
    DataProcessor & addAnotherFunction(DiscreteData &data);
    DataProcessor & multiplyAnotherFunction(const QVector<double> &toMultiply);
    DataProcessor & multiplyAnotherFunction(DiscreteData &data);
    DataProcessor & convolution(const QVector<double> &toConvolute);
    DataProcessor & convolution(DiscreteData &data);
    DataProcessor & antitrend(int window);
    DataProcessor & multiply(double value);
private:
    DiscreteData currentData;
};
