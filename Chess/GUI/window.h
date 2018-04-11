#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QMouseEvent>
#include "imageMap.h"
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
private:
    Controller* controller;
    ImageMap* map;

public slots:
    void showMessage(QString message);

signals:
    void sendClick(int x, int y);
};

#endif // WINDOW_H