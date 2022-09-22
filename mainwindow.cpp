#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dataReader.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testUltrasonicDetection();
}

void MainWindow::testUltrasonicDetection() {
	UltrasonicFlawDetection detection(300);
    DiscreteData impulse = detection.getImpulse();
	double length = 0.030;
    double flawLength = 0.001;
	double flawBegin = 0.014;
    double speed1 = 5940;
    double speed2 = 330;//6320;
	speed1 = 330;
	speed2 = 600;
    double impedance2 = 0.00033;//17064;

    double impedance1 = 46629;
    double sumImpedance = impedance1 + impedance2;
    double rFirstToSecond = (impedance2 - impedance1) / sumImpedance;
    double dFirstToSecond = 2 * impedance2 / sumImpedance;
    double rSecondToFirst = (impedance1 - impedance2) / sumImpedance;
    double dSecondToFirst = 2 * impedance1 / sumImpedance;
    double timeLength = 2 * length / speed1;
    /*----------------------------------------------------------------------*/
	int size = int(timeLength / impulse.getDiscreteStep());
    DiscreteData wave_0 = detection.singleImpulse(size, 0, 1);
    DataProcessor result(wave_0);
    qDebug() << "Wave_0: Yes";
    double time_1 = 2 * flawBegin / speed1;
    int index_1 = int(time_1 / impulse.getDiscreteStep());
    if (index_1 < size) {
        DiscreteData wave_1 = detection.singleImpulse(size, index_1, rFirstToSecond);
        result.addAnotherFunction(wave_1);
        qDebug() << "Wave_1: Yes";
    } else {
        qDebug() << "Wave_1: No";
    }
    double time_2 = time_1 + 2 * flawLength / speed2;
    int index_2 = int(time_2 / impulse.getDiscreteStep());
    if (index_2 < size) {
        DiscreteData wave_2 = detection.singleImpulse(size, index_2, dFirstToSecond * rSecondToFirst * dSecondToFirst);
        result.addAnotherFunction(wave_2);
        qDebug() << "Wave_2: Yes";
    } else {
        qDebug() << "Wave_2: No";
    }
    double time_3 = time_2 + 2 * (length - flawBegin - flawLength) / speed1;
    int index_3 = int(time_3 / impulse.getDiscreteStep());
    if (index_3 < size) {
        DiscreteData wave_3 = detection.singleImpulse(size, index_3,
                                                      dFirstToSecond * dSecondToFirst * dFirstToSecond * dSecondToFirst);
        result.addAnotherFunction(wave_3);
        qDebug() << "Wave_3: Yes";
    } else {
        qDebug() << "Wave_3: No";
    }

    DataPlotter::plotFunction(ui->widget, result.getCurrentData());
    DataPlotter::plotFunction(ui->widget_2, DataProcessor(result.getCurrentData()).amplitudeSpectrum().getCurrentData());
	DataPlotter::plotFunction(ui->widget_3, impulse);
}

void MainWindow::testWav() {
    size_t filterSize = 500;
    DiscreteData filter = DataGenerator(filterSize, 0, 1.0 / 22050).hpf(500);
    DiscreteData wav = DataReader::readWavFile("C:\\Users\\kveresh\\Documents\\prog\\TestWav\\test.wav");
    DiscreteData oSound = DataGenerator().getPart(wav, 0.375, 0.52);
    DataProcessor pr1(oSound);
    pr1.convolution(filter);
    QVector<double> oRes(oSound.getData().size());
    for (int i = 0; i < oSound.getData().size(); ++i) {
        oRes[i] = 5 * pr1.getCurrentData().getData()[i + filter.getData().size() / 2];
    }
    DiscreteData oResData(oRes, oSound.getFirstXValue(), oSound.getDiscreteStep());
    DataPlotter::plotFunction(ui->widget, oResData);
    DataPlotter::plotFunction(ui->widget_2, DataProcessor(oResData).amplitudeSpectrum().getCurrentData());
    DiscreteData aSound = DataGenerator().getPart(wav, 0.68, 0.92);
    DataProcessor pr2(aSound);
    DataPlotter::plotFunction(ui->widget_3, pr2.getCurrentData());
    DataPlotter::plotFunction(ui->widget_4, pr2.amplitudeSpectrum().getCurrentData());
    DiscreteData iSound = DataGenerator().getPart(wav, 1.04, 1.25);
    DataProcessor pr3(iSound);
}

void MainWindow::test() {
    DataGenerator generator(500, 0, 0.01);
    DiscreteData filter = generator.lpf(8);
    DataProcessor processor(filter);
    DataPlotter::plotFunction(ui->widget, processor.getCurrentData());
    processor
            .amplitudeSpectrum()
            ;
    DataPlotter::plotFunction(ui->widget_2, processor.getCurrentData());

    DiscreteData harm = generator.getHarmonicFunc(1, 3);
    DiscreteData harm_2 = generator.getHarmonicFunc(2, 2);
    DiscreteData harm_3 = generator.getHarmonicFunc(5, 1);
    DiscreteData harm_4 = generator.getHarmonicFunc(12, 1);
    DiscreteData harm_5 = generator.getHarmonicFunc(15, 1);
    DataProcessor proc(harm);
    proc
            .addAnotherFunction(harm_2)
            .addAnotherFunction(harm_3)
            .addAnotherFunction(harm_4)
            .addAnotherFunction(harm_5)
            ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
