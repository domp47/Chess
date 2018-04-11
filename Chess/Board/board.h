#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QPoint>
#include <QVector>
#include "elPassant.h"
#include <Board/Moves/rook.h>
#include <Board/Moves/bishop.h>
#include <Board/Moves/queen.h>
#include <Board/Moves/knight.h>
#include <Board/Moves/pawn.h>
#include <QtWidgets/QInputDialog>
#include <Board/Moves/king.h>
#include <QtWidgets/QMessageBox>
#include <QPushButton>
#include <QWidget>

class Controller;

class Board : public QObject{

    Q_OBJECT

public:
    Board(Controller* controller);
    void initBoard();
    int getPiece(int x, int y);
    void setPiece(int x, int y, int val);
    ElPassant getWhitePassant();
    ElPassant getBlackPassant();
    void setPassant(bool white, QPoint attacker, QPoint victim);
    void clearPassant(bool white);
    bool getWLR();
    bool getWRR();
    bool getBLR();
    bool getBRR();
    bool getWKing();
    bool getBKing();
    bool isBlackLongCastle() const;
    void setBlackLongCastle(bool blackLongCastle);
    bool isBlackCastle() const;
    void setBlackCastle(bool blackCastle);
    bool isWhiteLongCastle() const;
    void setWhiteLongCastle(bool whiteLongCastle);
    bool isWhiteCastle() const;
    void setWhiteCastle(bool whiteCastle);
    int** getBoard();
    void setWLR(bool val);
    void setWRR(bool val);
    void setBLR(bool val);
    void setBRR(bool val);
    void setWKing(bool val);
    void setBKing(bool val);
    void upgradePawn(int x, int y, char upgrade);
    void moveCastling(int type);
    void findKing(bool whiteTeam, int cords[2]);
private:
    int** board;
    ElPassant whitePassant;
    ElPassant blackPassant;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackLeftRookMoved;
    bool blackRightRookMoved;
    bool whiteKingMoved;
    bool blackKingMoved;
    bool blackLongCastle;
    bool blackCastle;
    bool whiteLongCastle;
    bool whiteCastle;
    Controller* controller;
};

#endif //BOARD_H