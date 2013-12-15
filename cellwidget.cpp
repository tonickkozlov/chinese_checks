#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <algorithm>
#include <string>
#include "cellwidget.h"

namespace ChineseChess
{
QString Rc_path = "/home/tonick/Programming/Alenka/china_chess/rc/";

CellWidget::CellWidget(QWidget *parent) :
    QWidget(parent)

{
    draw_strategy_ = CellDrawStrategy::ptr(new EmptyCellDrawStrategy);
}

// PushButton event
void CellWidget::mouseReleaseEvent(QMouseEvent *)
{
    qDebug() << "Mouse pressed!";
}

void CellWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QSize self_size = geometry().size();
    draw_strategy_->draw(painter, self_size.width(), self_size.height());
}


void CellWidget::SetDrawStrategy(CellDrawStrategy::ptr strategy)
{
    draw_strategy_ = strategy;
}

CellWidget::~CellWidget()
{
}

}
