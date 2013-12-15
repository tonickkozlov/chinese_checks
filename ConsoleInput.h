#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H

#include "gamestate.h"
#include <iostream>
namespace ChineseChess
{
std::istream& operator >> (std::istream& p, Command& com)
{
    p  >> com.from.first;
    p  >> com.from.second;
    p  >> com.to.first;
    p  >> com.to.second;
    return p;
}

class ConsoleInput
{
public:
    ConsoleInput(GameState *g_state)
    {
        if(g_state == 0)
        {
            std::invalid_argument("b");
        }
        gamestate_ = g_state;
    }

    void Input();
private:
    GameState *gamestate_;
};

void ConsoleInput:: Input()
{
    Command com;
    Command StopCommand = Command(-1,-1,-1,-1);
    while(com != StopCommand)
    {
        std::cin >> com;
        gamestate_->make_move(com);
    }
}

}
#endif // CONSOLEINPUT_H
