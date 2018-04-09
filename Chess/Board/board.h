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
#include <AI/alphaBeta.h>

class Board{
public:
    Board();
    void initBoard();
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
    int checkMateStalemate(bool whiteTeam);
    bool checkForAttack(int x, int y, bool whiteTeam);
    bool isBlackLongCastle() const;
    void setBlackLongCastle(bool blackLongCastle);
    bool isBlackCastle() const;
    void setBlackCastle(bool blackCastle);
    bool isWhiteLongCastle() const;
    void setWhiteLongCastle(bool whiteLongCastle);
    bool isWhiteCastle() const;
    void setWhiteCastle(bool whiteCastle);
    void findKing(bool whiteTeam, int cords[2]);
    QVector<QPoint> stripCheck(int x, int y, QVector<QPoint> moves);
    void setWindow(QWidget* window);
private:
    void nextMove();
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
    int gameMode;
    AlphaBeta alphaBeta;
    QWidget* window;
    bool windowSet;
};

#endif //BOARD_H