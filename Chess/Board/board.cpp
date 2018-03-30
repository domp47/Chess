#include <Board/Moves/rook.h>
#include <Board/Moves/bishop.h>
#include <Board/Moves/queen.h>
#include <Board/Moves/knight.h>
#include <Board/Moves/pawn.h>
#include "board.h"

/**
 *  -6 = BLK KING
 *  -5 = BLK QUEEN
 *  -4 = BLK BISHOP
 *  -3 = BLK KNIGHT
 *  -2 = BLK ROOK
 *  -1 = BLK PAWN
 *
 *   0 = NO PIECE
 *
 *   1 = WHT PAWN
 *   2 = WHT ROOK
 *   3 = WHT KNIGHT
 *   4 = WHT BISHOP
 *   5 = WHT QUEEN
 *   6 = WHT KING
 */

Board::Board() {
    board = new int*[8];
    for (int i = 0; i < 8; ++i) {
        board[i] = new int[8];
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            board[y][x] = 0;
        }
    }

    board[0][0] = -2;
    board[0][1] = -3;
    board[0][2] = -4;
    board[0][3] = -5;
    board[0][4] = -6;
    board[0][5] = -4;
    board[0][6] = -3;
    board[0][7] = -2;

    board[1][0] = -1;
    board[1][1] = -1;
    board[1][2] = -1;
    board[1][3] = -1;
    board[1][4] = -1;
    board[1][5] = -1;
    board[1][6] = -1;
    board[1][7] = -1;

    board[7][0] = 2;
    board[7][1] = 3;
    board[7][2] = 4;
    board[7][3] = 5;
    board[7][4] = 6;
    board[7][5] = 4;
    board[7][6] = 3;
    board[7][7] = 2;

    board[6][0] = 1;
    board[6][1] = 1;
    board[6][2] = 1;
    board[6][3] = 1;
    board[6][4] = 1;
    board[6][5] = 1;
    board[6][6] = 1;
    board[6][7] = 1;

    turn = 0;
    whitePassant.clearElPassant();
    blackPassant.clearElPassant();
}

int Board::getPiece(int x, int y) {
    return board[y][x];
}

QVector<QPoint> Board::getMoves(int x, int y) {

    if(board[y][x]==1 || board[y][x]==-1){
        return Pawn::getMoves(x,y,this);
    }
    if(board[y][x]==2 || board[y][x]==-2){
        return Rook::getMoves(x,y,board);
    }
    if(board[y][x]==3 || board[y][x]==-3){
        return Knight::getMoves(x,y,board);
    }
    if(board[y][x]==4 || board[y][x] ==-4){
        return Bishop::getMoves(x,y,board);
    }
    if(board[y][x]==5 || board[y][x] ==-5){
        return Queen::getMoves(x,y,board);
    }

    return QVector<QPoint>();
}

void Board::movePiece(int srcX, int srcY, int desX, int desY) {
    whitePassant.clearElPassant();
    blackPassant.clearElPassant();

    if(board[srcY][srcX]==-1){//is black pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board[desY][desX-1]==1){//check left for white pawn
                whitePassant.setElPassant(QPoint(desX-1,desY),QPoint(desX,desY));
            }
            if(desX+1 < 8 && board[desY][desX+1]==1){//check right for white pawn
                whitePassant.setElPassant(QPoint(desX+1,desY),QPoint(desX,desY));
            }
        }
    }
    else if(board[srcY][srcX]==1){//is white pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board[desY][desX-1]==1){//check left for black pawn
                blackPassant.setElPassant(QPoint(desX-1,desY),QPoint(desX,desY));
            }
            if(desX+1 < 8 && board[desY][desX+1]==1){//check right for black pawn
                whitePassant.setElPassant(QPoint(desX+1,desY),QPoint(desX,desY));
            }
        }
    }
    board[desY][desX] = board[srcY][srcX];
    board[srcY][srcX] = 0;
    turn++;


    //TODO pawn upgrading stuff here
    //TODO pawn en passant
}

int Board::getTurn() {
    return turn;
}

ElPassant Board::getWhitePassant() {
    return whitePassant;
}

ElPassant Board::getBlackPassant() {
    return blackPassant;
}

void Board::movePassant(int srcX, int srcY, QPoint victim, bool whiteTeam) {
    board[victim.y()][victim.x()] = 0;
    if(whiteTeam){
        movePiece(srcX,srcY,victim.x(),victim.y()-1);
    }else{
        movePiece(srcX,srcY,victim.x(),victim.y()+1);
    }
}


