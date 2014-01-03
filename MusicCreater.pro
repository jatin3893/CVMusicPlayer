#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T11:25:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicCreater
TEMPLATE = app

LIBS += `pkg-config --libs opencv`  #OpenCV Libraries
LIBS += /usr/lib/libfmodex64.so     #FMOD libraries
LIBS += -lGL -lglut -lGLEW -lGLU -lSOIL   #OpenGL libraries

SOURCES += main.cpp\
        mainwindow.cpp \
    cvimagewidget.cpp \
    glmainwindow.cpp \
    fmodcontroller.cpp \
    glvisualiserwindow.cpp

HEADERS  += mainwindow.h \
    cvimagewidget.h \
    wincompat.h \
    glmainwindow.h \
    fmodcontroller.h \
    glvisualiserwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
