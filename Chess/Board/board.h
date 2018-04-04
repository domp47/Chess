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
    void moveCastling(int type);
    int getTurn();
    ElPassant getWhitePassant();
    ElPassant getBlackPassant();
    void upgradePawn(int x, int y, char upgrade);
    bool getWLR();
    bool getWRR();
    bool getBLR();
    bool getBRR();
    bool getWKing();
    bool getBKing();
    bool checkCheck(bool whiteTeam);
    bool checkCheckMate(bool whiteTeam);
    bool checkForAttack(int x, int y, bool whiteTeam);
    bool isBlackLongCastle() const;
    void setBlackLongCastle(bool blackLongCastle);
    bool isBlackCastle() const;
    void setBlackCastle(bool blackCastle);
    bool isWhiteLongCastle() const;
    void setWhiteLongCastle(bool whiteLongCastle);
    bool isWhiteCastle() const;
    void setWhiteCastle(bool whiteCastle);
private:
    int** board;
    int turn;
    ElPassant whitePassant;
    ElPassant blackPassant;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackLeftRookMoved;
    bool blackRightRookMoved;
    bool whiteKingMoved;
    bool blackKingMoved;

    bool blackLongCastle;

private:
    bool blackCastle;
    bool whiteLongCastle;
    bool whiteCastle;
};

#endif //BOARD_H