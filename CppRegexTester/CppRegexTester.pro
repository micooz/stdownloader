#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T18:02:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CppRegexTester
TEMPLATE = app

INCLUDEPATH += D:\libs\boost_1_56_0
LIBS += -L D:\libs\boost_1_56_0\stage\lib
LIBS += -lboost_regex-mgw48-mt-d-1_56
LIBS += -lboost_regex-mgw48-mt-s-1_56

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
