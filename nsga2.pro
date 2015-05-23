#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T00:10:21
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = nsga2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    individual.cpp \
    nsga2.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    individual.h \
    nsga2.h \
    exprtk.hpp \
    qcustomplot.h

FORMS    += mainwindow.ui
