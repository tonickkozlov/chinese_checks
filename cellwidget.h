#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <memory>

#include "chinese_chess.h"
#include "cell_draw_strategy.h"
#include "MouseClickStrategy.h"

namespace ChineseChess
{

class CellWidget : public QWidget
{
    Q_OBJECT
public:
    typedef std::shared_ptr<CellWidget> ptr;
    explicit CellWidget(int id, QWidget *parent = 0);
    void SetDrawStrategy(CellDrawStrategy::ptr strategy);
    void SetMouseClickStrategy(MouseClickStrategy::ptr strategy);
    ~CellWidget();
    
private:
    CellDrawStrategy::ptr draw_strategy_;
    MouseClickStrategy::ptr mouse_click_strategy_;

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    int id_;

};

}

#endif // CELLWIDGET_H
