#include "discreteData.h"

DiscreteData::DiscreteData()
{

}

DiscreteData::DiscreteData(QVector<double> vector, double firstXValue, double discreteStep)
    :data(vector), firstXValue(firstXValue), discreteStep(discreteStep)
{

}

QVector<double> &DiscreteData::getData() {
    return this->data;
}

double DiscreteData::getFirstXValue() {
    return this->firstXValue;
}

double DiscreteData::getDiscreteStep() {
    return this->discreteStep;
}
