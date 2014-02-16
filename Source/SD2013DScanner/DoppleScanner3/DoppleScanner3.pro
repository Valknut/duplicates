#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T20:53:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoppleScanner3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sha1.cpp \
    TreeScanner.cpp \
    UserInterface.cpp

HEADERS  += mainwindow.h \
    sha1.h \
    TreeScanner.h \
    UserInterface.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp