#include "ultrasonicFlawDetection.h"
#include "dataProcessor.h"

#include <cmath>

UltrasonicFlawDetection::UltrasonicFlawDetection(int size) {
    double discreteStep = 0.000005 / size;
    QVector<double> waveData(size);
    for (int i = 0; i < waveData.size(); ++i) {
        waveData[i] = sin(2 * M_PI * 1000000 * i * discreteStep) * exp(-1100000 * i * discreteStep);
    }
    this->impulse = DiscreteData(waveData, 0, discreteStep);
}

DiscreteData UltrasonicFlawDetection::nonFlawExample(double length, double speed) {
    double timeLength = 2 * length / speed;
    QVector<double> data(int(timeLength / impulse.getDiscreteStep()));
    //data[0] = 1;
    data[data.size() - 1] = 1;
    QVector<double> dataEnd(int(timeLength / impulse.getDiscreteStep()));
    dataEnd[0] = 1;
    DiscreteData first(data, 0, impulse.getDiscreteStep());
    DiscreteData second(data, 0, impulse.getDiscreteStep());
    DataProcessor procFirst(first);
    DataProcessor procSecond(second);
    procFirst.convolution(this->impulse);
    procSecond.convolution(this->impulse);
    return procFirst.addAnotherFunction(procSecond.getCurrentData()).getCurrentData();
}

DiscreteData UltrasonicFlawDetection::singleImpulse(int size, int index, double coeff) {
    QVector<double> result(size);
    result[index] = coeff;
    DiscreteData res(result, 0, this->impulse.getDiscreteStep());
    return DataProcessor(res).convolution(this->impulse).getCurrentData();
}

DiscreteData UltrasonicFlawDetection::flawExample(double length, double flawLength, double flawBegin
                                                  , double speed1, double speed2
                                                  , double impedance1, double impedance2
                                                  ) {
    double sumImpedance = impedance1 + impedance2;
    double rFirstToSecond = (impedance2 - impedance1) / sumImpedance;
    double dFirstToSecond = 2 * impedance2 / sumImpedance;
    double rSecondToFirst = (impedance1 - impedance2) / sumImpedance;
    double dSecondToFirst = 2 * impedance1 / sumImpedance;

}

DiscreteData UltrasonicFlawDetection::getImpulse() {
    return this->impulse;
}
