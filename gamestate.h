#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <memory>

#include "gamematrix.h"
#include "chinese_chess.h"

namespace ChineseChess {

class Printer
{
public:
    virtual void Print(const Mat &mat) = 0;
};

class GameState
{
public:
    GameState(Printer* print);

private:
    Mat matrix_;
    Printer* printer;
    // initial game state
    // TODO: сделать фабрику? начальных состояний
    void fill_initial();
};

}
#endif // GAMESTATE_H
