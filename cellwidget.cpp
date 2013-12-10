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

bool CellWidget::TexturesLoaded = false;
std::shared_ptr<QPixmap> CellWidget::PixmapBusy = 0;
std::shared_ptr<QPixmap> CellWidget::PixmapClosed = 0;
std::shared_ptr<QPixmap> CellWidget::PixmapFree = 0;

CellWidget::CellWidget(QWidget *parent, state cell_state) :
    QWidget(parent),
    current_state_(cell_state)
{
    if(!TexturesLoaded)
    {
        // load textures
        PixmapBusy      = std::shared_ptr<QPixmap>(new QPixmap(Rc_path + "busy.png"));
        PixmapClosed    = std::shared_ptr<QPixmap>(new QPixmap(Rc_path + "closed.png"));
        PixmapFree      = std::shared_ptr<QPixmap>(new QPixmap(Rc_path + "free.png"));
        if(PixmapBusy->isNull() || PixmapClosed->isNull() || PixmapFree->isNull())
        {
            qFatal("Could not load textures :(");
        }
        else
            TexturesLoaded = true;
    }
}

// PushButton event
void CellWidget::mouseReleaseEvent(QMouseEvent *)
{
    qDebug() << "Mouse pressed!";
}

void CellWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QSize currentSize = geometry().size();
    switch(current_state_)
    {
        case CELL_BUSY:
            painter.drawPixmap(0, 0, currentSize.width(), currentSize.height(), *PixmapBusy);
        break;
        case CELL_FREE:
            painter.drawPixmap(0, 0, currentSize.width(), currentSize.height(), *PixmapFree);
        break;
        default:
            painter.drawPixmap(0, 0, currentSize.width(), currentSize.height(), *PixmapClosed);
        break;

    }
}

CellWidget::~CellWidget()
{
}

}
