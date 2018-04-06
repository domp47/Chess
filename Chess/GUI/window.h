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
    void keyPressEvent(QKeyEvent *);
    bool isMovePossible(QPoint p);
public:
private:
    int highlightedCords[2];
    QVector<QPoint> possibleMoves;
    Map* map;
    Board* board;
    int lastKey;
};

#endif // WINDOW_H