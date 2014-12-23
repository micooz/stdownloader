TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += D:/libs/boost_1_56_0/
INCLUDEPATH += ../public/
INCLUDEPATH += ../libs/avhttp-2.9.9/include/
INCLUDEPATH += ../libs/jsoncpp-0.7.0/include/

LIBS += -L D:/libs/boost_1_56_0/stage/lib/ \
        -lboost_system-mgw48-mt-s-1_56 \
        -lboost_regex-mgw48-mt-s-1_56 \
        -lboost_filesystem-mgw48-mt-s-1_56 \
        -lboost_program_options-mgw48-mt-s-1_56

LIBS += "../jsoncpp-0.7.0-build/lib/libjsoncpp.a"

win32{
    DEFINES += WIN32
    LIBS    += -lws2_32
}

SOURCES += main.cpp \
    ../public/Configure.cpp \
    Downloader.cpp \
    MusicInfo.cpp \
    Sampler.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../public/Configure.h \
    Downloader.h \
    MusicInfo.h \
    Sampler.h

