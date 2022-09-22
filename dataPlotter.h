#pragma once

#include "../qcustomplot/qcustomplot.h"
#include "discreteData.h"

class DataPlotter
{
public:
    DataPlotter();
    static void plotFunction(QCustomPlot *plotWidget, DiscreteData &data);
};
