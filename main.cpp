#include <QApplication>
#include <QDialog>
#include <iostream>
#include "boardwidget.h"
#include "mainwindow.h"

#include "ConsolePrinter.h"
#include "gamestate.h"

int main(int argc, char *argv[])
{

    using namespace ChineseChess;
    /*
    QApplication a(argc, argv);
    BoardWidget *widget = new BoardWidget;

    widget->setGeometry(0, 0, 810, 810);
    widget->show();

    GameState state(widget);


    return a.exec();
    */
    ConsolePrinter* print = new ConsolePrinter;
    GameState start(print);

    return 0;
}
