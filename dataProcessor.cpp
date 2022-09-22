#include "dataProcessor.h"
#include "statistics.h"

#include <cmath>
#include <ctime>

DataProcessor::DataProcessor(DiscreteData data)
    :currentData(data) {

}

DiscreteData & DataProcessor::getCurrentData() {
    return this->currentData;
}

DataProcessor & DataProcessor::addAnotherFunction(const QVector<double> &toAdd) {
    QVector<double> &data = this->currentData.getData();
    for (int i = 0; i < data.size(); ++i) {
        data[i] += toAdd[i];
    }
    return *this;
}

DataProcessor & DataProcessor::addAnotherFunction(DiscreteData &data) {
    return addAnotherFunction(data.getData());
}

DataProcessor & DataProcessor::multiplyAnotherFunction(const QVector<double> &toMultiply) {
    QVector<double> &data = this->currentData.getData();
    for (int i = 0; i < data.size(); ++i) {
        data[i] *= toMultiply[i];
    }
    return *this;
}

DataProcessor & DataProcessor::multiplyAnotherFunction(DiscreteData &data) {
    return multiplyAnotherFunction(data.getData());
}

DataProcessor & DataProcessor::addSpikeValues(int numberOfSpikes, int spikeOrder)
{
    QVector<double> &data = this->currentData.getData();
    QVector<double> randomGen(data.size());

    for (int i = 0; i < randomGen.size(); ++i) {
        randomGen[i] = i;
    }

    double minValue = *std::min_element(data.begin(), data.end());
    double maxValue = *std::max_element(data.begin(), data.end());
    double range = (maxValue - minValue) / 2;
    double rangeMin = spikeOrder * range;
    double rangeMax = (spikeOrder + 2) * range;
    srand(time(NULL));

    for (int i = 0; i < numberOfSpikes; ++i) {
        int randIndex = rand() % randomGen.size();
        int index = randomGen[randIndex];
        double num =((double)rand() / (double)RAND_MAX);
        if (num >= 0.5) {
            data[index] = (num - 0.5) * 2 * range + rangeMin + maxValue;
        } else {
            data[index] =  - num * range - rangeMin + minValue;
        }
        //result[index] = num * 2 * range - range;
        randomGen[randIndex] = randomGen[randomGen.size() - 1];
        randomGen.removeLast();
    }

    return *this;
}

DataProcessor & DataProcessor::eliminateSpikeValues(double lowerBound, double upperBound) {
    QVector<double> result;
    for (double num : this->currentData.getData()) {
        if (num >= lowerBound && num <= upperBound) {
            result.append(num);
        }
    }
    this->currentData = DiscreteData(result
                                     , this->currentData.getFirstXValue()
                                     , this->currentData.getDiscreteStep());
    return *this;
}

DataProcessor & DataProcessor::addShift(double shift) {
    QVector<double> &data = this->currentData.getData();
    for (int i = 0; i < data.size(); ++i) {
        data[i] += shift;
    }
    return *this;
}

DataProcessor & DataProcessor::eliminateShift() {
    QVector<double> &data = this->currentData.getData();
    double shift = Statistics::expectation(data);
    for (int i = 0; i < data.size(); ++i) {
        data[i] -= shift;
    }
    return *this;
}

DataProcessor & DataProcessor::amplitudeSpectrum()
{
    QVector<double> &data = this->currentData.getData();
    int N = data.size();
    QVector<double> result(N / 2);
    for (int k = 0; k < N / 2; ++k) {
        double re = 0;
        double im = 0;
        for (int n = 0; n < N; ++n) {
            re += data[n] * cos(2 * M_PI * k * n / N);
            im += data[n] * sin(2 * M_PI * k * n / N);
        }
        re /= N;
        im /= N;
        result[k] = 2 * sqrt(im * im + re * re);
    }
    this->currentData = DiscreteData(result
                                     , this->currentData.getFirstXValue()
                                     , 1 / (N * this->currentData.getDiscreteStep()));
    return *this;
}

DataProcessor & DataProcessor::convolution(const QVector<double> &toConvolute) {
    QVector<double> &data = this->currentData.getData();
    int N = data.size();
    int M = toConvolute.size();
    QVector<double> result(M + N);
    for (int k = 0; k < M + N; ++k) {
        for (int i = 0; i < M; ++i) {
            if (k - i < 0 || k - i > N - 1)
                continue;
            result[k] += data[k - i] * toConvolute[i];
        }
    }
    this->currentData = DiscreteData(result
                                     , this->currentData.getFirstXValue()
                                     , this->currentData.getDiscreteStep());
    return *this;
}

DataProcessor & DataProcessor::convolution(DiscreteData &data) {
    return convolution(data.getData());
}

DataProcessor & DataProcessor::antitrend(int window) {
    int size = this->currentData.getData().size();
    QVector<double> res(size);
    for (int i = 0; i < window; ++i) {
        res[i] = currentData.getData()[i];

    }
    for (int i = window; i < size; ++i) {
        double w[window];
        double sum = 0;
        for (int j = 1; j <= window; ++j) {
            sum += currentData.getData()[i - j];
        }
        res[i] = sum / window;
    }
    currentData = DiscreteData(res, 0, this->currentData.getDiscreteStep());
    return *this;
}

DataProcessor & DataProcessor::multiply(double value) {
    QVector<double> res(currentData.getData().size());
    for (int i = 0; i < currentData.getData().size(); ++i) {
        res[i] = currentData.getData()[i] * value;
    }
    this->currentData = DiscreteData(res, 0 , currentData.getDiscreteStep());
    return *this;
}
