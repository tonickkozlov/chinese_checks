#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H

#include "gamestate.h"
#include <iostream>
namespace ChineseChess
{
std::istream& operator >> (std::istream& p, Command& com) // оператор ввода команды
{
    p  >> com.from.first;
    p  >> com.from.second;
    p  >> com.to.first;
    p  >> com.to.second;
    return p;
}
/*!
    Класс ConsoleInput обеспечивает консольный ввод команд. Содержит объект класса GameState
*/
class ConsoleInput
{
public:
    ConsoleInput(GameState *g_state)
    {
        if(g_state == 0)
        {
            throw GamestateBadArgument();
        }
        gamestate_ = g_state;
    }

    void Input();
    struct GamestateBadArgument {};
private:
    GameState *gamestate_;
};

void ConsoleInput:: Input()
{
    Command com;
    Command StopCommand = Command(-1,-1,-1,-1); // стоповая команда для консольного ввода
    while(true)
    {
        std::cin >> com;
        gamestate_->make_move(com); // делаем ход
        if(com == StopCommand)
        {
            break;
        }
        if(gamestate_->get_n_el() == 1)
        {
            std::cout << "YOU WIN!" << std::endl;
            break;
        }
    }
}

}
#endif // CONSOLEINPUT_H
