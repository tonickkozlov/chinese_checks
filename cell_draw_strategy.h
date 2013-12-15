#ifndef CELL_DRAW_STRATEGY_H
#define CELL_DRAW_STRATEGY_H

#include <memory>

#include <QPixmap>
#include <QPainter>

#include "chinese_chess.h"

namespace ChineseChess
{

// a class to draw a single cell
struct CellDrawStrategy
{
    typedef  std::shared_ptr<CellDrawStrategy> ptr;
    virtual void draw(QPainter &painter, int width, int height) =0;
};

struct EmptyCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        QPixmap cell_pixmap(":/rc/closed.png");
        painter.drawPixmap(0, 0, width, height, cell_pixmap);
    }
};

struct FreeCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        QPixmap cell_pixmap(":/rc/free.png");
        painter.drawPixmap(0, 0, width, height, cell_pixmap);
    }
};

struct BusyCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        QPixmap cell_pixmap(":/rc/busy.png");
        painter.drawPixmap(0, 0, width, height, cell_pixmap);
    }
};

struct CellStrategyCreator
{
   /* static CellDrawStrategy::ptr EmptyCellDrawStrategy()
    {
        static CellDrawStrategy::ptr cell(new EmptyCellDrawStrategy);
        return cell;
    }
    static CellDrawStrategy::ptr BusyCellDrawStrategy()
    {
        static CellDrawStrategy::ptr cell(new BusyCellDrawStrategy);
        return cell;
    }
    static CellDrawStrategy::ptr FreeCellDrawStrategy()
    {
        static CellDrawStrategy::ptr cell(new FreeCellDrawStrategy);
        return cell;
    }
    */
};


}

#endif // CELL_DRAW_STRATEGY_H
