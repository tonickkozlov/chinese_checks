#include <QGridLayout>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <cassert>
#include "gamematrix.h"
#include "boardwidget.h"
#include "cellwidget.h"
#include "MouseClickStrategy.h"

namespace ChineseChess
{

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent)
{
    int nCells = CellsAtColumn*CellsAtRow;
    cells_.reserve(nCells);
    for(int i = 0; i < nCells; ++i)
    {
        CellWidget::ptr newCell(new CellWidget(i, this));
        cells_.push_back(newCell);
    }

    ItemDispencer<CellDrawStrategy> &cell_strategies = ItemDispencer<CellDrawStrategy>::Instance();
    // prepare all cell draw strategies:
    cell_strategies.Add("busy", CellDrawStrategy::ptr(new BusyCellDrawStrategy));
    cell_strategies.Add("empty", CellDrawStrategy::ptr(new EmptyCellDrawStrategy));
    cell_strategies.Add("free", CellDrawStrategy::ptr(new FreeCellDrawStrategy));
    // prepare all vavilable pixmaps
    ItemDispencer<QPixmap> &available_pixmaps = ItemDispencer<QPixmap>::Instance();
    typedef std::shared_ptr<QPixmap> QPixmap_ptr;
    available_pixmaps.Add("busy", QPixmap_ptr(new QPixmap(":/rc/busy.png")));
    available_pixmaps.Add("empty", QPixmap_ptr(new QPixmap(":/rc/closed.png")));
    available_pixmaps.Add("free", QPixmap_ptr(new QPixmap(":/rc/free.png")));
    // prepare all available click reporters:
    ItemDispencer<MouseClickStrategy> &mouse_strategies = ItemDispencer<MouseClickStrategy>::Instance();
    mouse_strategies.Add("ignore", MouseClickStrategy::ptr(new IgnoreMouseClick));
    mouse_strategies.Add("report", MouseClickStrategy::ptr(new ReportMouseClick));
}

//this function gets called by CellWidget
void BoardWidget::onClick(int cell_id)
{
    int cell_row = cell_id / CellsAtRow;
    int cell_col = cell_id % CellsAtColumn;
    qDebug() << "Click reported: " << cell_row << " " << cell_col;
    clicked_cells_.push(std::make_pair(cell_row, cell_col));
    if(clicked_cells_.size() > 1)
    {
        std::pair<int, int> from = clicked_cells_.front();
        std::pair<int, int> to = clicked_cells_.back();
        Command command(from, to);
        state_->make_move(command);
        // clean queue
        while(!clicked_cells_.empty())
            clicked_cells_.pop();
    }
}

void BoardWidget::paintEvent(QPaintEvent *)
{
}
void BoardWidget::Print(const Mat &matrix)
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
                MouseClickStrategy::ptr mouse_click_strategy;
                switch(matrix.at(i, j))
                {
                case Mat::state::BUSY:
                    cell_draw_strategy      = dispencer<CellDrawStrategy>().Get("busy");
                    mouse_click_strategy    = dispencer<MouseClickStrategy>().Get("report");
                    break;
                case Mat::state::FREE:
                    cell_draw_strategy      = dispencer<CellDrawStrategy>().Get("free");
                    mouse_click_strategy    = dispencer<MouseClickStrategy>().Get("report");
                    break;
                default:
                    cell_draw_strategy      = dispencer<CellDrawStrategy>().Get("empty");
                    mouse_click_strategy    = dispencer<MouseClickStrategy>().Get("ignore");
                    break;
                }
                current_cell->SetDrawStrategy(cell_draw_strategy);
                current_cell->SetMouseClickStrategy(mouse_click_strategy);
            }
        }
        repaint();
    }
    catch(std::out_of_range &)
    {
        QMessageBox(QMessageBox::NoIcon, "Error while updating display", "Game matrix is out of range").exec();
    }
    catch(ItemDispencer<CellDrawStrategy>::ItemDoesNotExist)
    {
        QMessageBox(QMessageBox::NoIcon, "Error while updating display", "Some of CellDrawStrategy does not exist").exec();
        this->close();
    }
    catch(ItemDispencer<MouseClickStrategy>::ItemDoesNotExist)
    {
        QMessageBox(QMessageBox::NoIcon, "Error while updating display", "Some of MouseClickStrategies does not exist").exec();
        this->close();
    }
}

void BoardWidget::resizeEvent(QResizeEvent *)
{
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

void BoardWidget::SetCommandExecutor(CommandExecutor *executor)
{
    if(executor != 0)
        state_ = executor;
}

BoardWidget::~BoardWidget()
{
}

}
