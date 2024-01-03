QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet.cpp \
    Eagle.cpp \
    Enemy.cpp \
    Enemyhealth.cpp \
    Obstruction.cpp \
    Player.cpp \
    PowerUp.cpp \
    Scene.cpp \
    Score.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Bullet.h \
    Eagle.h \
    Enemy.h \
    Enemyhealth.h \
    Obstruction.h \
    Player.h \
    PowerUp.h \
    Scene.h \
    Score.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
