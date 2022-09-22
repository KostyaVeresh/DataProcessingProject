#include "dataReader.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

#include "../aquila/source/WaveFile.h"

DataReader::DataReader()
{

}

DiscreteData DataReader::readWavFile(const QString &file) {
    Aquila::WaveFile wav(file.toStdString());
    QVector<double> result(wav.getSamplesCount());
    for (size_t i = 0; i < wav.getSamplesCount(); ++i) {
        result[i] = wav.sample(i);
    }
    return DiscreteData(result, 0, 1 / wav.getSampleFrequency());
}

void DataReader::writeWavFile(DiscreteData data, const QString &file) {
    Aquila::WaveFile::save(Aquila::SignalSource(data.getData().toStdVector(), 22050)
                           , file.toStdString());
}

DiscreteData DataReader::readDatFile(const QString &file) {
    QVector<double> res;
     QFile f(file);
     f.open(QIODevice::ReadOnly);
     QDataStream in(&f);
     in.setByteOrder(QDataStream::LittleEndian);
     in.setFloatingPointPrecision(QDataStream::SinglePrecision);
     while (!in.atEnd()) {
         float v;
         in >> v;
         //qDebug() << v;
         res.append(v);
     }
     return DiscreteData(res, 0, 0.001);
}
