#pragma once

#include "discreteData.h"

#include <QVector>

class UltrasonicFlawDetection
{
public:
    UltrasonicFlawDetection(int size);
    DiscreteData getImpulse();
    DiscreteData nonFlawExample(double length, double speed);
    DiscreteData flawExample(double length, double flawLength, double flawBegin
                             , double speed1, double speed2
                             , double impedance1, double impedance2);
    DiscreteData singleImpulse(int size, int index, double coeff);

private:
    DiscreteData impulse;
};
