#include "bishop.h"

/**
 *  Gets all the possible moves the bishop at position x,y can make
 * 
 * @param x X location on board
 * @param y Y location on board
 * @param board game board
 * @return Vector of possible moves
 */
QVector<Move> Bishop::getMoves(int x, int y, std::array<std::array<int,8>,8> board) {
    QVector<Move> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    int i = x+1;
    int ii = y-1;
    for (; i < 8 && ii >= 0; i++,ii--) {
        if(board[ii][i]==0){
            moves.append(Move(QPoint(x,y),QPoint(i,ii)));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            break;
        }
    }

    i = x+1;
    ii= y+1;
    for (; i < 8 && ii < 8 ; i++, ii++) {
        if(board[ii][i]==0){
            moves.append(Move(QPoint(x,y),QPoint(i,ii)));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            break;
        }
    }

    i = x-1;
    ii= y+1;
    for (; i >= 0 && ii < 8 ; i--, ii++) {
        if(board[ii][i]==0){
            moves.append(Move(QPoint(x,y),QPoint(i,ii)));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            break;
        }
    }

    i = x-1;
    ii= y-1;
    for (; i >= 0 && ii>= 0 ; i--,ii--) {
        if(board[ii][i]==0){
            moves.append(Move(QPoint(x,y),QPoint(i,ii)));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(Move(QPoint(x,y),QPoint(i,ii)));
            }
            break;
        }
    }

    return moves;
}
