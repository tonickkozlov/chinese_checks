#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <memory>
#include "chinese_chess.h"
namespace ChineseChess
{

class CellWidget : public QWidget
{
    Q_OBJECT
public:
    typedef std::shared_ptr<CellWidget> ptr;
    /* a cell can have 3 states
     * and draws itself based on
     * it's current state */
    enum state
    {
        CELL_CLOSED,
        CELL_BUSY,
        CELL_FREE
    };

    void setState(state new_state)
    {
        current_state_ = new_state;
    }

    explicit CellWidget(QWidget *parent = 0, state cell_state = CELL_CLOSED);
    ~CellWidget();
    
private:
    static std::shared_ptr<QPixmap> PixmapClosed, PixmapBusy, PixmapFree;
    static bool TexturesLoaded; // if textures are loaded into program memory (checked by every new cell)

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    state current_state_;



};

}

#endif // CELLWIDGET_H
