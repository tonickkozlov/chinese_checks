#ifndef CELL_DRAW_STRATEGY_H
#define CELL_DRAW_STRATEGY_H

#include <memory>

#include <QPixmap>
#include <QPainter>

#include "chinese_chess.h"
#include "itemdispencer.h"

namespace ChineseChess
{

// a class to draw a single cell
struct CellDrawStrategy
{
    typedef  std::shared_ptr<CellDrawStrategy> ptr;
    virtual void draw(QPainter &painter, int width, int height) =0;
    virtual ~CellDrawStrategy() {}
};

struct EmptyCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        painter.drawPixmap(0, 0, width, height, *dispencer<QPixmap>().Get("empty"));
    }
};
/*
//typedef std::map<std::string, CellDrawStrategy::ptr> strategy_dispencer;
// init code:
///
class Singleton
{
public:
    static Singleton& ReturnInstance()
    {
        static Singleton instance_;
        return instance_;
    }
    CellDrawStrategy::ptr get_strategy(std::string key)
    {
        return dispencer_[key];
    }
    void put_strategy(std::string key, CellDrawStrategy::ptr strategy)
    {
        dispencer_[key] = strategy;
    }

private:
    std::map<std::string, CellDrawStrategy::ptr> dispencer_;
};

//init code
Singleton &sing = Singleton::ReturnInstance();
sing.put_strategy("busy", BusyCellDrawStrategy)
// use code

// singleton user:
#include "Singletone.h"
Singletone sing;
sing.GetIn..(); // wrong!
//
#include "Singletone.h"
Singletone::ReturnInstance().getInt();

*/
struct FreeCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        painter.drawPixmap(0, 0, width, height, *dispencer<QPixmap>().Get("free"));
    }
};

struct BusyCellDrawStrategy: CellDrawStrategy
{
    void draw(QPainter &painter, int width, int height)
    {
        painter.drawPixmap(0, 0, width, height, *dispencer<QPixmap>().Get("busy"));
    }
};

}

#endif // CELL_DRAW_STRATEGY_H
