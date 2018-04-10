#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QMouseEvent>
#include "map.h"
#include <iostream>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QPushButton>
#include "colors.h"

class Controller;

class Window : public QWidget
{
    Q_OBJECT
    const int STARTING_X = 40;
    const int STARTING_Y = 10;

public:
    Window(Controller *);


private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *);
    bool isMovePossible(QPoint p);
private:
    Controller* controller;
    int highlightedCords[2];
    QVector<QPoint> possibleMoves;
    Map* map;
    int lastKey;
};

#endif // WINDOW_H