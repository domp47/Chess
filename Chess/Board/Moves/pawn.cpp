#include "pawn.h"
#include "../board.h"

QVector<QPoint> Pawn::getMoves(int x, int y, int** board) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    if(whiteTeam){//if its white pawn
        if(y==6){//at starting position
            if(board[y-2][x]==0){//is something blocking it 2 spaces ahead
                moves.append(QPoint(x,y-2));//add to list of spaces
            }
        }
        if(y-1 >= 0){//checking if it can move up without going off board
            if(board[y-1][x]==0){//check if the spot above is empty
                moves.append(QPoint(x,y-1));//add to list of spaces to move
            }
            if(x-1 >= 0 && board[y-1][x-1]<0){//check if enemy on diagonal
                moves.append(QPoint(x-1,y-1));
            }
            if(x+1 < 8 && board[y-1][x+1]<0){//check if enemy on diagonal
                moves.append(QPoint(x+1,y-1));
            }
        }
    }
    else{//black pawn
        if(y==1){//at starting pos
            if(board[y+2][x]==0){
                moves.append(QPoint(x,y+2));
            }
        }
        if(y+1 < 8){//can it move forward without going off board
            if(board[y+1][x]==0){
                moves.append(QPoint(x,y+1));
            }
            if(x-1 >= 0 && board[y+1][x-1]>0){//check if enemy on diagonal
                moves.append(QPoint(x-1,y+1));
            }
            if(x+1 < 8 && board[y+1][x+1]>0){//check if enemy on diagonal
                moves.append(QPoint(x+1,y+1));
            }
        }
    }

    return moves;
}
