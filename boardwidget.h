#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>

#include <vector>
#include <queue>

#include "chinese_chess.h"
#include "gamestate.h"
#include "cellwidget.h"
#include "itemdispencer.h"

namespace ChineseChess
{

class BoardWidget : public QWidget, public Printer, public MouseClickReporter
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = 0);
    void Print(const Mat &matrix);
    void SetCommandExecutor(CommandExecutor *executor);
    ~BoardWidget();
private:
    void updateCellPositions();
    void paintEvent(QPaintEvent *);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);

    void onClick(int cell_id);

    std::vector<CellWidget::ptr> cells_;
    CommandExecutor *state_;
    // нажатие ячейки помещает ее координаты в очередь.
    // когда нажаты 2 ячейки (в очереди 2 элемента)
    // из них формируется команда и отправляется в ядро игры.
    std::queue<std::pair<int, int>> clicked_cells_;
};

}

#endif // BOARDWIDGET_H
