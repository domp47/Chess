#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QMouseEvent>
#include <Board/board.h>
#include "map.h"

class Window : public QWidget
{
    Q_OBJECT
    const int STARTING_X = 40;
    const int STARTING_Y = 10;

public:
    Window(Board*);

private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

public:
private:
    int highlightedCords[2];
    Map* map;
    Board* board;
};

#endif // WINDOW_H