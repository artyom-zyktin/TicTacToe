TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        Field.cpp \
        GuiView.cpp \
        Player.cpp \
        View.cpp \
        main.cpp

HEADERS += \
    Driver.h \
    Field.h \
    GuiView.h \
    Player.h \
    View.h

QT += widgets
