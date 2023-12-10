QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Brick.cpp \
    Bullet.cpp \
    Ice.cpp \
    Obstruction.cpp \
    Player.cpp \
    Scene.cpp \
    Steel.cpp \
    Trees.cpp \
    Water.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Brick.h \
    Bullet.h \
    Ice.h \
    Obstruction.h \
    Player.h \
    Scene.h \
    Steel.h \
    Trees.h \
    Water.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
