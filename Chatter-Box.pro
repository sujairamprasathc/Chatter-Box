QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets websockets

TARGET = Chatter-Box
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
    src/chatroomwindow.cpp \
    src/chatserver.cpp \
    src/chatserverexception.cpp \
    src/chatserverwindow.cpp \
    src/connecttoserverdialog.cpp \
    src/conversationmodel.cpp \
    src/englishtextlabels.cpp \
    src/gui.cpp \
    src/main.cpp \
    src/Message.cpp \
    src/messagemodel.cpp \
    src/network.cpp \
    src/User.cpp \
    src/welcomedialog.cpp

HEADERS += \
    include/chatroomwindow.h \
    include/chatserver.h \
    include/chatserverexception.h \
    include/chatserverwindow.h \
    include/connecttoserverdialog.h \
    include/conversationmodel.h \
    include/englishtextlabels.h \
    include/gui.h \
    include/Message.h \
    include/messagemodel.h \
    include/network.h \
    include/User.h \
    include/welcomedialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH = "./include"

# Build directory rules
MOC_DIR = build/moc
OBJECTS_DIR = build/objects
UI_DIR = build/ui
RCC_DIR = build
