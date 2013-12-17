#ifndef MOUSECLICKSTRATEGY_H
#define MOUSECLICKSTRATEGY_H

#include <memory>
#include "chinese_chess.h"

namespace ChineseChess
{

// абстрактный класс, которому можно "доложить" о клике
// (по-идее, если речь идет о клике на ячейку,
// этим классом должен быть виджет-родитель ячейки.
class MouseClickReporter
{
public:
    virtual void onClick(int cell_id) =0;
    virtual ~MouseClickReporter() {};
};

// исходная стратегия реакции на клик - игнорировать
struct MouseClickStrategy
{
    typedef std::shared_ptr<MouseClickStrategy> ptr;
    // прнимает указатель на класс, которому нужно сообщить о клике,
    // и id, который ему нужно передать (id ячейки)
    virtual void onClick(MouseClickReporter * =0, int id =0) =0;
    virtual ~MouseClickStrategy() {}
};

struct IgnoreMouseClick: MouseClickStrategy
{
    void onClick(MouseClickReporter * =0, int id =0) {}
};


struct ReportMouseClick: MouseClickStrategy
{
    void onClick(MouseClickReporter *reporter =0, int id =0)
    {
        if(reporter != 0)
            reporter->onClick(id);
    }
};

}

#endif // MOUSECLICKSTRATEGY_H
