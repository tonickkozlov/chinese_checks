#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <memory>
#include <utility>

#include "gamematrix.h"
#include "chinese_chess.h"

namespace ChineseChess {

class Printer
{
public:
    virtual void Print(const Mat &mat) = 0;
};
struct Command
{
    std::pair<int, int> from;
    std::pair<int, int> to;
    Command(){}
    Command(int from_first, int from_second, int to_first, int to_second)
    {
        from.first = from_first;
        from.second = from_second;
        to.first = to_first;
        to.second = to_second;
    }
    Command(std::pair<int, int> f, std::pair<int, int> t)
    {
        from.first = f.first;
        from.second = f.second;
        to.first = t.first;
        to.second = t.second;
    }
    bool operator == (Command com)
    {
        return(this->from == com.from &&
               this->to == com.to);
    }

    bool operator != (Command com)
    {
        return (!(com == *this));
    }
};
class GameState
{
public:
    enum class state_command
    {
        RIGHT,
        WRONG,
        RIGHT_WON,
        RIGHT_FAIL
    };
    GameState(Printer* print);
    void make_move(Command);

private:
    Mat matrix_;
    Printer* printer_;
    // initial game state
    // TODO: сделать фабрику? начальных состояний
    void fill_initial();
    bool validate(Command);

};

}
#endif // GAMESTATE_H
