#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T16:54:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = andor-scmos-control
TEMPLATE = app

INCLUDEPATH += "C:\Program Files\Andor SDK3"
INCLUDEPATH += D:\home\xinhangliu\opencv-build\install\include
LIBS += -L"C:\Program Files\Andor SDK3" -latcorem -latutilitym
LIBS += -L"D:\home\xinhangliu\opencv-build\install\x64\mingw\lib" \
    -lopencv_core401 \
    -lopencv_highgui401 \
    -lopencv_imgcodecs401 \
    -lopencv_imgproc401 \
    -lopencv_features2d401 \
    -lopencv_calib3d401

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    propertybrowserdelegate.cpp \
    utils.cpp \
    server.cpp \
    graphicsscene.cpp \
    aboutwindow.cpp

HEADERS += \
        mainwindow.h \
    propertybrowserdelegate.h \
    utils.h \
    server.h \
    graphicsscene.h \
    aboutwindow.h

FORMS += \
        mainwindow.ui \
    serverwindow.ui \
    aboutwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

win32:RC_ICONS += "./assets/icon.ico"
