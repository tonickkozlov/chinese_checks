#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <memory>
#include <utility>

#include "gamematrix.h"
#include "chinese_chess.h"

namespace ChineseChess {
/*!
    Эта структура описывает ход игрока как две пары значений: начальная позиция шашки(x,y) и позиция назначения,
    где окажется шашка после хода.
*/
struct Command // пара пар
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

/*!
  Класс Printer - абстрактный, содержит виртуальную функцию вывода матрицы на экран,
  которая реализуется в консольном выводе матрицы на экран и в реализации графического интерфейса
*/

class Printer
{
public:
    virtual void Print(const Mat &mat) = 0;
    virtual ~Printer() {}
};

struct CommandExecutor
{
    virtual void make_move(Command) =0;
};

/*!
    Этот класс описывает ходы игрока, изменяя матрицу состяния поля, а так же проверяет возможность сделать тот или иной ход.
    Класс GameState содержит объект класса Printer, которому GameState делигирует вывод начального состояния матрицы на экран,
    а также ее состояния после каждого корректного хода, проверенного методом validate(Command)
*/

class GameState: public CommandExecutor
{
public:
    GameState(Printer* print);
    void make_move(Command);
    int get_n_el();

private:
    Mat matrix_;
    Printer* printer_;
    int n_el;
    bool validate(Command);
    int n_elements();
};

}
#endif // GAMESTATE_H
