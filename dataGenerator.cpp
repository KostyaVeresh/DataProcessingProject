#include "dataGenerator.h"
#include <QDebug>

DataGenerator::DataGenerator()
{

}

DataGenerator::DataGenerator(double size, double firstXValue, double discreteStep)
{
    this->setGenerationParameters(size, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getDiscreteStepVector() {
    QVector<double> resultVec(size);
    for (size_t i = 0; i < size; ++i) {
        resultVec[i] = firstXValue + i * discreteStep;
    }
    return DiscreteData(resultVec, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getConstantVector(double value) {
    QVector<double> resultVec(size);
    for (int i = 0; i < size; ++i) {
        resultVec[i] = value;
    }
    return DiscreteData(resultVec, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getTrend(int multiply) {
    QVector<double> resultVec(size);
    for (int i = 0; i < size / 3; ++i) {
        double pointX = i * discreteStep;
        resultVec[i] = multiply * pointX;
    }
    for (int i = size / 3; i < 2 * size / 3; ++i) {
        double pointX = i * discreteStep;
        resultVec[i] = multiply * (- 2 * pointX / 5 + 7 * size * discreteStep / 15);
    }
    for (int i = 2 * size / 3; i < size; ++i) {
        double pointX = i * discreteStep;
        resultVec[i] = multiply * (9 * pointX / 10 - 2 * size * discreteStep / 5);
    }

    return DiscreteData(resultVec, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getHarmonicFunc(double frequency, double amplitude) {
    QVector<double> result(size);
    for (size_t i = 0; i < size; ++i) {
        double xPoint = i * discreteStep;
        result[i] = amplitude * qSin(2 * M_PI * frequency * xPoint);
    }
    return DiscreteData(result, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getDefaultRandomVector(unsigned int seed, double first, double second)
{
    QVector<double> randomVector(size);
    srand(seed);
    for (size_t i = 0; i < size; ++i) {
        double randValue = ((double)rand() / (double)RAND_MAX);
        randomVector[i] = randValue * (second - first) + first;
    }
    return DiscreteData(randomVector, firstXValue, discreteStep);
}

DiscreteData DataGenerator::getCustomRandomVector(unsigned int seed, double first, double second)
{
    QVector<double> randomVector(size);
    unsigned long int newNum = seed;
    for (size_t i = 0; i < size; ++i) {
        newNum = (419 * newNum + 6173) % 29282;
        randomVector[i] = takeNFirstDigits(newNum, 5) / 10000.0;
    }
    return DiscreteData(randomVector, firstXValue, discreteStep);
}

void DataGenerator::setGenerationParameters(double size, double firstXValue, double discreteStep)
{
    this->size = size;
    this->firstXValue = firstXValue;
    this->discreteStep = discreteStep;
}

int DataGenerator::takeNFirstDigits(int number, int n) {
    int digitNum = (int)log10(number);
    if (digitNum < n)
        return number % (int)pow(10, digitNum);
    number /= pow(10, digitNum - n);
    return number % n;
}

DiscreteData DataGenerator::lpf(int fcut) {
//fcut - частота, например 51; m =32 длина функции по иксу ; dt-частота дискретизации
    int m = this->size;
    double dt = this->discreteStep;
    double d1 = 0.35577019;
    double d2 = 0.2436983;
    double d3 = 0.07211497;
    double d4 = 0.00630165;
    double lpw[m + 1];
    double d[4];
    double arg, sumg, sum;
    d[0] = d1;
    d[1] = d2;
    d[2] = d3;
    d[3] = d4;
    arg = 2 * fcut * dt;
    lpw[0] = arg;
    arg = arg * M_PI;
    for (int i = 1; i <= m; i++) {
        lpw[i] = sin(arg * i) / (M_PI * i);
    }
    lpw[m] = lpw[m] / 2;
    sumg = lpw[0];
    for (int i = 1; i <= m; i++ ) {
        sum = d[0];
        arg = (M_PI * i) / m;
        for (int k = 1; k <= 3; k++) {
            sum = sum + 2 * d[k] * cos(arg * k);
        }
        lpw[i] = lpw[i] * sum;
        sumg = sumg + 2 * lpw[i];
    }
    for (int i = 0; i <= m; i++) {
        lpw[i] = lpw[i] / sumg;
    }
    /*for (int i = 0; i <= m; ++i) {
        lpw[i] = lpw[i] * m;
    }*/
    QVector<double> result(size * 2 + 1);
    for (int i = 0; i <= m; ++i) {
        result[i + m] = lpw[i];
        result[m - i] = lpw[i];
    }

    return DiscreteData(result, this->firstXValue, this->discreteStep);
}

DiscreteData DataGenerator::hpf(double fcut) {
    int m = this->size;
    double dt = this->discreteStep;
    double hpw[2 * m + 1];
    //double[] lpw[2 * m + 1];
    QVector<double> lp = lpf(fcut).getData();

    //lpw = lowPassFilter(fcut, m, dt);

    for (int k = 0; k < 2 * m + 1; k++) {
        if (k == m) {
            hpw[k] = 1 - lp[k];
        }
        else {
            hpw[k] = -lp[k];
        }
    }
    QVector<double> result(2 * m + 1);
    for (int i = 0; i < 2 * m + 1; ++i) {
        result[i] = hpw[i];
    }
    return DiscreteData(result, this->firstXValue, this->discreteStep);
}

DiscreteData DataGenerator::bpf(double fcut1, double fcut2) {
    int m = this->size;
    QVector<double> bpw(2 * m + 1);
    //double[] lpw1 = new double[2 * m + 1];
    //double[] lpw2 = new double[2 * m + 1];

    QVector<double> lpw1 = lpf(fcut1).getData();
    QVector<double> lpw2 = lpf(fcut2).getData();

    for (int k = 0; k < 2 * m + 1; k++) {
        bpw[k] = lpw2[k] - lpw1[k];
    }

    return DiscreteData(bpw, this->firstXValue, this->discreteStep);
}

DiscreteData DataGenerator::bsf(double fcut1, double fcut2) {
    int m = this->size;
    QVector<double> bsw(2 * m + 1);
    QVector<double> lpw1 = lpf(fcut1).getData();
    QVector<double> lpw2 = lpf(fcut2).getData();

    //lpw1 = lowPassFilter(fcut1, m, dt);
    //lpw2 = lowPassFilter(fcut2, m, dt);

    for (int k = 0; k < 2 * m + 1; k++) {
        if (k == m) {
            bsw[k] = 1 + lpw1[k] - lpw2[k];
        }
        else {
            bsw[k] = lpw1[k] - lpw2[k];
        }
    }

    return DiscreteData(bsw, this->firstXValue, this->discreteStep);
}

DiscreteData DataGenerator::getPart(DiscreteData data, double first, double last) {
    int fst = (int) ((first - data.getFirstXValue()) / data.getDiscreteStep());
    int lst = (int) ((last - data.getFirstXValue()) / data.getDiscreteStep());
    qDebug() << fst;
    qDebug() << lst;
    QVector<double> result(lst - fst + 1);
    for (int i = fst; i < lst; ++i) {
        result[i - fst] = data.getData()[i];
    }
    return DiscreteData(result, first, data.getDiscreteStep());
}

DiscreteData DataGenerator::covariation(DiscreteData data1, DiscreteData data2) {
    double e1 = 0;
    double e2 = 0;
    for (int i = 0; i < data1.getData().size(); ++i) {
        e1 += data1.getData()[i];
        e2 += data2.getData()[i];
    }
    e1 /= data1.getData().size();
    e2 /= data1.getData().size();
    QVector<double> cov(data1.getData().size());
    for (int i = 0; i < data1.getData().size(); ++i) {
        for (int k = 0; k < data1.getData().size() - i; ++k) {
            cov[i] += ((data1.getData()[k] - e1) * (data2.getData()[k + i] - e2));
        }
        cov[i] /= data1.getData().size();
    }
    return DiscreteData(cov, 0, 0.001);
}
