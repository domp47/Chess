#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QPoint>
#include <QVector>

class Board{
public:
    Board();
    int getPiece(int x, int y);
    QVector<QPoint> getMoves(int x, int y);
    void movePiece(int srcX, int srcY, int desX, int desY);

private:
    int** board;
};

#endif //BOARD_H