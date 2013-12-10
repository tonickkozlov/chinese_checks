#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>

#include <vector>

#include "chinese_chess.h"
#include "gamestate.h"
#include "cellwidget.h"

namespace ChineseChess
{

class BoardWidget : public QWidget, public IOutput
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = 0);
    void Draw(const Mat &matrix);
    ~BoardWidget();
private:
    void updateCellPositions();
    void paintEvent(QPaintEvent *);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    std::vector<CellWidget::ptr> cells_;
    
signals:

public slots:
    
};

}

#endif // BOARDWIDGET_H
