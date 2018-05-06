#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QMouseEvent>
#include "imageMap.h"
#include <iostream>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QPushButton>
#include <Controller/move.h>
#include "colors.h"

class Controller;

class Window : public QWidget
{
    Q_OBJECT
    const int STARTING_X = 40;
    const int STARTING_Y = 10;

public:
    Window(Controller *);
    void updateCahce(std::array<std::array<int,8>,8> board, QPoint highlight = QPoint(-1,-1), QVector<Move> possibleMoves= QVector<Move>());


private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    ImageMap* map;
    std::array<std::array<int,8>,8> boardCache;
    QPoint highlightedCache;
    QVector<Move> movesCache;

public slots:
    void showMessage(QString message);

signals:
    void sendClick(int x, int y);
};

#endif // WINDOW_H