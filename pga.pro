#-------------------------------------------------
#
# Project created by QtCreator 2015-04-10T17:50:12
#
#-------------------------------------------------

QT       += core gui

TARGET = pga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    mythread.h

FORMS    += mainwindow.ui

RESOURCES += \
    resfile.qrc
