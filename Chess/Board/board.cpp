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

    board[6][0] = 0; //change to 1
    board[6][1] = 1;
    board[6][2] = 1;
    board[6][3] = 1;
    board[6][4] = 1;
    board[6][5] = 1;
    board[6][6] = 1;
    board[6][7] = 1;
}

int Board::getPiece(int x, int y) {
    return board[y][x];
}

QVector<QPoint> Board::getMoves(int x, int y) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if(board[y][x] < 0)
        whiteTeam = false;

    if(board[y][x]==2||board[y][x]==-2){
        for (int i = y-1; i >= 0; i--) { //check above
            if(board[i][x]==0){
                moves.append(QPoint(x,i));
            }else{
                if(whiteTeam&&board[i][x]<0)
                    moves.append(QPoint(x,i));
                if(!whiteTeam&&board[i][x]>0)
                    moves.append(QPoint(x,i));
                break;
            }
        }
        for (int i = x + 1; i < 8; ++i) { //check right
            if(board[y][i]==0){
                moves.append(QPoint(i,y));
            }else{
                if(whiteTeam&&board[y][i]<0)
                    moves.append(QPoint(i,y));
                if(!whiteTeam&&board[y][i]>0)
                    moves.append(QPoint(i,y));
                break;
            }
        }
        for (int i = y + 1; i < 8; i++) { //check below
            if(board[i][x]==0){
                moves.append(QPoint(x,i));
            }else{
                if(whiteTeam&&board[i][x]<0)
                    moves.append(QPoint(x,i));
                if(!whiteTeam&&board[i][x]>0)
                    moves.append(QPoint(x,i));
                break;
            }
        }
        for (int i = x - 1; i >= 0; i--) { //check left
            if(board[y][i]==0){
                moves.append(QPoint(i,y));
            }else{
                if(whiteTeam&&board[y][i]<0)
                    moves.append(QPoint(i,y));
                if(!whiteTeam&&board[y][i]>0)
                    moves.append(QPoint(i,y));
                break;
            }
        }

    }

    return moves;
}

void Board::movePiece(int srcX, int srcY, int desX, int desY) {
    board[desY][desX] = board[srcY][srcX];
    board[srcY][srcX] = 0;
}


