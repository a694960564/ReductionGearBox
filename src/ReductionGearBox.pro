#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T19:36:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReductionGearBox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += opengl

INCLUDEPATH += "D:\glm-0.9.7.3\glm"

CONFIG += c++11
LIBS += -lopengl32\
        -lglu32\
        -lglut32\
        -lglut
#LIBS += -L$$PWD/../lib/ -lglut
#LIBS += -L$$PWD/../lib/ -lglut32
SOURCES += \
        Controler.cpp \
        glWin/gl_win.cpp \
        main.cpp \
        mainwindow.cpp \
        object/GearBox.cpp \
        object/box/Box.cpp \
        object/model/Model.cpp

HEADERS += \
        Controler.h \
        common/stb_image.h \
        glWin/gl_win.h \
        mainwindow.h \
        object/GearBox.h \
        object/Object.h \
        object/box/Box.h \
        object/model/Model.h

FORMS += \
        Controler.ui \
        glWin/gl_win.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    object/box/fragmentshader.frag \
    object/box/vertexshader.vert \
    object/model/fragmentshader.frag \
    object/model/vertexshader.vert
