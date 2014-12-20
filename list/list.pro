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
        -lboost_filesystem-mgw48-mt-s-1_56

LIBS += "../libs/jsoncpp-0.7.0/lib/libjsoncpp.a"

win32{
    DEFINES += WIN32
    LIBS    += -lws2_32
}

SOURCES += \
    AlbumLister.cpp \
    AlbumListStruct.cpp \
    CategoryLister.cpp \
    CategoryListStruct.cpp \
    ILister.cpp \
    IListStruct.cpp \
    main.cpp \
    RecommendLister.cpp \
    RecommendListStruct.cpp \
    ../public/Configure.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    AlbumLister.h \
    AlbumListStruct.h \
    CategoryLister.h \
    CategoryListStruct.h \
    ILister.h \
    IListStruct.h \
    RecommendLister.h \
    RecommendListStruct.h \
    ../public/Configure.h

