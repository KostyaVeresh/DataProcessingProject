#pragma once

#include "dataGenerator.h"
#include "dataProcessor.h"
#include "dataPlotter.h"
#include "ultrasonicFlawDetection.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void testUltrasonicDetection();
    void test();
    void testWav();
    Ui::MainWindow *ui;
};
