#include <QApplication>
#include <QDialog>
#include <iostream>
#include "boardwidget.h"
#include "mainwindow.h"

#include "ConsolePrinter.h"
#include "gamestate.h"
#include "ConsoleInput.h"

#include "gamematrix.h"


int main(int argc, char *argv[])
{

    using namespace ChineseChess;

    QApplication a(argc, argv);

    BoardWidget *widget = new BoardWidget;
    GameState state(widget);

    widget->SetCommandExecutor(&state);

    widget->setGeometry(0, 0, 810, 810);
    widget->show();




    return a.exec();


    /*ConsolePrinter* print = new ConsolePrinter;
    GameState state(print);
    ConsoleInput* input = new ConsoleInput(&state);
    input->Input();
    */


    return 0;
}
