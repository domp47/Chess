#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QPoint>
#include <QVector>
#include "elPassant.h"

class Board{
public:
    Board();
    int getPiece(int x, int y);
    QVector<QPoint> getMoves(int x, int y);
    void movePiece(int srcX, int srcY, int desX, int desY);
    int getTurn();

private:
    int** board;
    int turn;
    ElPassant whitePassant;
    ElPassant blackPassant;
};

#endif //BOARD_H