#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T10:22:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DataProcessingProject
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ../qcustomplot/qcustomplot.cpp \
    discreteData.cpp \
    dataGenerator.cpp \
    dataProcessor.cpp \
    dataPlotter.cpp \
    statistics.cpp \
    ../aquila/source/WaveFile.cpp \
    ../aquila/source/WaveFileHandler.cpp \
    dataReader.cpp \
    ultrasonicFlawDetection.cpp

HEADERS  += mainwindow.h \
    ../qcustomplot/qcustomplot.h \
    discreteData.h \
    dataGenerator.h \
    dataProcessor.h \
    dataPlotter.h \
    statistics.h \
    ../aquila/source/WaveFile.h \
    dataReader.h \
    ultrasonicFlawDetection.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3
