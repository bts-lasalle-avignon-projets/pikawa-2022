QT       += core gui widgets sql

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basededonnees.cpp \
    cafetiere.cpp \
    communication.cpp \
    main.cpp \
    ihm.cpp

HEADERS += \
    basededonnees.h \
    cafetiere.h \
    communication.h \
    ihm.h

FORMS += \
    ihm.ui

RESOURCES += \
    ressources.qrc

COPIES += bd
bd.files = pikawa.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
