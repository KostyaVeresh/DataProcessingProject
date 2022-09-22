#pragma once

#include "discreteData.h"

#include <qmath.h>

class DataGenerator
{
public:
    DataGenerator();

    /// Creates generator of discrete data with given parameters
    /// @param Size of returned discrete vector
    /// @param First point of absciss axis of generated data
    /// @param Discrete step for X values of generated data
    DataGenerator(double size, double firstXValue, double discreteStep);
    DiscreteData getDiscreteStepVector();
    DiscreteData getConstantVector(double value);
    DiscreteData getTrend(int multiply = 1);
    DiscreteData getDefaultRandomVector(unsigned int seed, double first = 0, double second = 1);
    DiscreteData getCustomRandomVector(unsigned int seed, double first = 0, double second = 1);
    DiscreteData getHarmonicFunc(double frequency, double amplitude);
    void setGenerationParameters(double size, double firstXValue, double discreteStep);
    DiscreteData lpf(int fcut);
    DiscreteData hpf(double fcut);
    DiscreteData bpf(double fcut1, double fcut2);
    DiscreteData bsf(double fcut1, double fcut2);
    DiscreteData getPart(DiscreteData data, double first, double last);
    DiscreteData covariation(DiscreteData data1, DiscreteData data2);

private:
    int takeNFirstDigits(int number, int n);

    double size;
    double firstXValue;
    double discreteStep;
};
