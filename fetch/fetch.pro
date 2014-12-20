TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += D:/libs/boost_1_56_0/

include(deployment.pri)
qtcAddDeployment()

