#-------------------------------------------------
#
# Project created by QtCreator 2013-12-09T16:51:34
#
#-------------------------------------------------

QT       += core gui
QT      += widgets

TARGET = china_chess
TEMPLATE = app


SOURCES += main.cpp\
    boardwidget.cpp \
    cellwidget.cpp \
    gamestate.cpp

HEADERS  += boardwidget.h \
    cellwidget.h \
    gamestate.h \
    gamematrix.h \
    chinese_chess.h \
    cell_draw_strategy.h \
    ConsolePrinter.h \
    ConsoleInput.h

#FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    resources.qrc
