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
    void setPassant(bool white, ElPassant passant);
    void clearPassant(bool white);
    bool getWLR();
    bool getWRR();
    bool getBLR();
    bool getBRR();
    bool getWKing();
    bool getBKing();
    std::array<std::array<int,8>,8> getBoard();
    void setWLR(bool val);
    void setWRR(bool val);
    void setBLR(bool val);
    void setBRR(bool val);
    void setWKing(bool val);
    void setBKing(bool val);
    void upgradePawn(int x, int y, char upgrade);
    void findKing(bool whiteTeam, int cords[2]);
    void printBoard();
private:
    std::array<std::array<int,8>,8> board;
    ElPassant whitePassant;
    ElPassant blackPassant;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackLeftRookMoved;
    bool blackRightRookMoved;
    bool whiteKingMoved;
    bool blackKingMoved;
    Controller* controller;
};

#endif //BOARD_H