#include <QGridLayout>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <cassert>
#include "gamematrix.h"
#include "boardwidget.h"
#include "cellwidget.h"

namespace ChineseChess
{

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent)
{
    int nCells = CellsAtColumn*CellsAtRow;
    cells_.reserve(nCells);
    for(int i = 0; i < nCells; ++i)
    {
        CellWidget::ptr newCell(new CellWidget(this));
        cells_.push_back(newCell);
    }
}

void BoardWidget::paintEvent(QPaintEvent *)
{

}
void BoardWidget::Draw(const Mat &matrix)
{
    const int nrows = matrix.get_n_rows();
    const int ncols = matrix.get_n_cols();
    assert(nrows * ncols == cells_.size());
    try
    {
        // synchronize matrix state and states of all columns
        for(int i = 0; i < nrows; ++i)
        {
            for(int j = 0; j < ncols; ++j)
            {
                CellWidget::ptr         current_cell = cells_[i * ncols + j];
                CellDrawStrategy::ptr   cell_draw_strategy;
                switch(matrix.at(i, j))
                {
                case Mat::state::BUSY:

                    cell_draw_strategy = CellStrategyCreator::BusyCellDrawStrategy();
                    break;
                case Mat::state::FREE:
                    cell_draw_strategy = CellStrategyCreator::FreeCellDrawStrategy();
                    break;
                default:
                    cell_draw_strategy = CellStrategyCreator::EmptyCellDrawStrategy();
                    break;
                }
                current_cell->SetDrawStrategy(cell_draw_strategy);
            }
        }
    }
    catch(std::out_of_range &)
    {
        QMessageBox(QMessageBox::NoIcon, "Error while updating display", "Game matrix is out of range").exec();
    }
}

void BoardWidget::resizeEvent(QResizeEvent *)
{
    qDebug() << "BoardWidget::resizeEvent";
    updateCellPositions();
}

void BoardWidget::moveEvent(QMoveEvent *)
{

}

void BoardWidget::updateCellPositions()
{
    // count new positions for inner widgets
    const QSize cellSize = geometry().size() / CellsAtRow ;
    for(int i = 0; i < CellsAtRow; ++i)
    {
        for(int j = 0; j < CellsAtColumn; ++j)
        {
            CellWidget::ptr cell = cells_[i * CellsAtRow + j];
            QRect newRect = QRect(j * cellSize.width(), i * cellSize.height(), cellSize.width(), cellSize.height());
            cell->setGeometry(newRect);
        }
    }
}

BoardWidget::~BoardWidget()
{
}

}
