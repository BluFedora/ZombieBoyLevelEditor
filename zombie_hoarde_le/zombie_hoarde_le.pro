#-------------------------------------------------
#
# Project created by QtCreator 2018-02-17T17:18:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = zombie_horde_le
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    spritesetlist.cpp \
    graphicsview.cpp \
    assetio.cpp \
    zombiehordele.cpp \
    cmd/cmdnewgameobject.cpp \
    gameobject.cpp \
    meta/iclassproperty.cpp \
    meta/propertytreeitem.cpp

HEADERS += \
    spritesetlist.h \
    graphicsview.h \
    assetio.hpp \
    zombiehordele.h \
    cmd/cmdnewgameobject.hpp \
    gameobject.hpp \
    meta/iclassproperty.h \
    meta/propertytreeitem.hpp

INCLUDEPATH += \
    ../../norse_code/zombie_horde/zombie_horde_project/ \
    ../../norse_code/zombie_horde/zombie_horde_project/engine/ \

FORMS += \
    zombiehordele.ui

DISTFILES += \
    resources/changelog.txt

RESOURCES += \
    resources.qrc
