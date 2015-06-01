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
    qcustomplot.cpp \
    muParser.cpp \
    muParserBase.cpp \
    muParserBytecode.cpp \
    muParserCallback.cpp \
    muParserError.cpp \
    muParserTokenReader.cpp

HEADERS  += mainwindow.h \
    individual.h \
    nsga2.h \
    qcustomplot.h \
    muParser.h \
    muParserBase.h \
    muParserBytecode.h \
    muParserCallback.h \
    muParserDef.h \
    muParserError.h \
    muParserFixes.h \
    muParserStack.h \
    muParserToken.h \
    muParserTokenReader.h

FORMS    += mainwindow.ui
