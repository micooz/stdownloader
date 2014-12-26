TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += D:/libs/boost_1_56_0/
INCLUDEPATH += ../public/
INCLUDEPATH += ../libs/jsoncpp-0.7.0/include/

LIBS += -L D:/libs/boost_1_56_0/stage/lib/ \
        -lboost_regex-mgw48-mt-s-1_56 \
        -lboost_filesystem-mgw48-mt-s-1_56 \
        -lboost_system-mgw48-mt-s-1_56

LIBS += "../jsoncpp-0.7.0-build/lib/libjsoncpp.a"

SOURCES += main.cpp \
    ../public/Configure.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../public/Configure.h

