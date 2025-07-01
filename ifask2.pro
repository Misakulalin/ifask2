QT       += core gui network#添加网络功能

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets#所使用的qt版本

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatdialog.cpp \
    global.cpp \
    httpmgr.cpp \
    logindialog.cpp \
    main.cpp \
    ifask2.cpp \
    registdialog.cpp \
    singleton.cpp

HEADERS += \
    chatdialog.h \
    global.h \
    httpmgr.h \
    ifask2.h \
    logindialog.h \
    registdialog.h \
    singleton.h

FORMS += \
    chatdialog.ui \
    ifask2.ui \
    logindialog.ui \
    registdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
