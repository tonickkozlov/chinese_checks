#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <QMessageBox>
#include <algorithm>
#include <string>
#include "cellwidget.h"
#include <cassert>

namespace ChineseChess
{
QString Rc_path = "/home/tonick/Programming/Alenka/china_chess/rc/";

CellWidget::CellWidget(int id, QWidget *parent) :
    QWidget(parent),
    id_(id)
{
    draw_strategy_ = CellDrawStrategy::ptr(new EmptyCellDrawStrategy);
}

// PushButton event
void CellWidget::mouseReleaseEvent(QMouseEvent *)
{
    MouseClickReporter *parent = dynamic_cast<MouseClickReporter *>(this->parent());
    assert(parent != 0);
    if(mouse_click_strategy_ != 0)
    {
        mouse_click_strategy_->onClick(parent, id_);
    }
}

void CellWidget::paintEvent(QPaintEvent *)
{
    if(draw_strategy_ != 0)
    {
        try
        {
            QPainter painter(this);
            QSize self_size = geometry().size();
            draw_strategy_->draw(painter, self_size.width(), self_size.height());
        }
        catch (ItemDispencer<QPixmap>::ItemDoesNotExist)
        {
            QMessageBox(QMessageBox::NoIcon, "Error while drawing cell", "Some of resource QPixmaps was not loaded").exec();
            exit(1);
        }
    }
}

void CellWidget::SetDrawStrategy(CellDrawStrategy::ptr strategy)
{
    draw_strategy_ = strategy;
}

void CellWidget::SetMouseClickStrategy(MouseClickStrategy::ptr strategy)
{
    mouse_click_strategy_ = strategy;
}

CellWidget::~CellWidget()
{
}

}
