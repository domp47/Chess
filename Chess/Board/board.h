#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QPoint>
#include <QVector>

class Board{
public:
    Board();
    int getPiece(int x, int y);
    QVector<QPoint> getMoves(int x, int y);

private:
    int** board;
};

#endif //BOARD_H