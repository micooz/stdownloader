TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += ../libs/jsoncpp-0.7.0/include/

LIBS += -L ../libs/jsoncpp-0.7.0/lib/
LIBS += -ljsoncpp

include(deployment.pri)
qtcAddDeployment()

