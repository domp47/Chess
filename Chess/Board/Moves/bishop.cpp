#include "bishop.h"

QVector<QPoint> Bishop::getMoves(int x, int y, int **board) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    int i = x+1;
    int ii = y-1;
    for (; i < 8 && ii >= 0; i++,ii--) {
        if(board[ii][i]==0){
            moves.append(QPoint(i,ii));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(QPoint(i,ii));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(QPoint(i,ii));
            }
            break;
        }
    }

    i = x+1;
    ii= y+1;
    for (; i < 8 && ii < 8 ; i++, ii++) {
        if(board[ii][i]==0){
            moves.append(QPoint(i,ii));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(QPoint(i,ii));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(QPoint(i,ii));
            }
            break;
        }
    }

    i = x-1;
    ii= y+1;
    for (; i >= 0 && ii < 8 ; i--, ii++) {
        if(board[ii][i]==0){
            moves.append(QPoint(i,ii));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(QPoint(i,ii));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(QPoint(i,ii));
            }
            break;
        }
    }

    i = x-1;
    ii= y-1;
    for (; i >= 0 && ii>= 0 ; i--,ii--) {
        if(board[ii][i]==0){
            moves.append(QPoint(i,ii));
        }else{
            if(whiteTeam && board[ii][i] < 0){
                moves.append(QPoint(i,ii));
            }
            if(!whiteTeam && board[ii][i] > 0){
                moves.append(QPoint(i,ii));
            }
            break;
        }
    }

    return moves;
}
