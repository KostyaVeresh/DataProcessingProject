#pragma once

#include "discreteData.h"

class DataReader
{
public:
    DataReader();
    static DiscreteData readDatFile(const QString &file);
    static DiscreteData readWavFile(const QString &file);
    static void writeWavFile(DiscreteData data, const QString &file);
};
