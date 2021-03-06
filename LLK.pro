#-------------------------------------------------
#
# Project created by QtCreator 2019-07-09T18:58:13
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LLK
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        llk.cpp \
    logindialog.cpp \
    mylabel.cpp \
    connecttoserver.cpp \
    register.cpp \
    chatmessage.cpp \
    chatmainwindow.cpp \
    itemdelegate.cpp \
    tcpserver.cpp \
    settingdialog.cpp \
    signoutdialog.cpp \
    blockuserdialog.cpp

HEADERS += \
        llk.h \
    logindialog.h \
    mylabel.h \
    connecttoserver.h \
    register.h \
    chatmessage.h \
    chatmainwindow.h \
    itemdef.h \
    itemdelegate.h \
    tcpserver.h \
    settingdialog.h \
    signoutdialog.h \
    blockuserdialog.h

FORMS += \
        llk.ui \
    logindialog.ui \
    connecttoserver.ui \
    register.ui \
    chatmainwindow.ui \
    tcpserver.ui \
    settingdialog.ui \
    signoutdialog.ui \
    blockuserdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    qss.qrc
