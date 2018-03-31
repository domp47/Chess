#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QPoint>
#include <QVector>
//#include <GUI/window.h>
#include "elPassant.h"

class Window;

class Board{
public:
    Board();
    int getPiece(int x, int y);
    QVector<QPoint> getMoves(int x, int y);
    void movePiece(int srcX, int srcY, int desX, int desY);
    void movePassant(int srcX, int srcY, QPoint victim, bool whiteTeam);
    int getTurn();
    ElPassant getWhitePassant();
    ElPassant getBlackPassant();
    void upgradePawn(int x, int y, char upgrade);

private:
    int** board;
    int turn;
    ElPassant whitePassant;
    ElPassant blackPassant;
};

#endif //BOARD_H