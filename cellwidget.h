#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <memory>

#include "chinese_chess.h"
#include "cell_draw_strategy.h"

namespace ChineseChess
{

class CellWidget : public QWidget
{
    Q_OBJECT
public:

    typedef std::shared_ptr<CellWidget> ptr;
    explicit CellWidget(QWidget *parent = 0);
    void SetDrawStrategy(CellDrawStrategy::ptr strategy);
    ~CellWidget();
    
private:
    CellDrawStrategy::ptr draw_strategy_;

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);




};

}

#endif // CELLWIDGET_H
