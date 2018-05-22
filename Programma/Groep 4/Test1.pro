#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T16:44:37
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test1
TEMPLATE = app



INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    plotgraph.cpp \
    propagateinterface.cpp \
    batch.cpp \
    Layer.cpp \
    Network.cpp \
    Neuron.cpp \
    propagate.cpp \
    testimage.cpp \
    propagateRoot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    plotgraph.h \
    propagateinterface.h \
    batch.h \
    Layer.h \
    Network.h \
    Neuron.h \
    propagate.h \
    testimage.h \
    propagateRoot.h

FORMS    += mainwindow.ui

