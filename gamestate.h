#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <memory>

#include "gamematrix.h"
#include "chinese_chess.h"

namespace ChineseChess {

class IOutput
{
public:
    virtual void Draw(const Mat&) =0;
    virtual ~IOutput() {}
};

class GameState
{
public:
    GameState(IOutput *output);

private:
    GameMatrix<CellsAtRow, CellsAtColumn> matrix_;
    // initial game state
    void fill_initial();
    IOutput *output_;
};

}
#endif // GAMESTATE_H
