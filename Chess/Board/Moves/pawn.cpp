#include "pawn.h"
#include "../board.h"

QVector<QPoint> Pawn::getMoves(int x, int y, Board* board) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if (board->getPiece(x,y) < 0)
        whiteTeam = false;

    if(whiteTeam){
        if(y==6){
            if(board->getPiece(x,y-2)==0){
                moves.append(QPoint(x,y-2));
            }
        }
        if(y-1 >= 0){
            if(board->getPiece(x,y+1)==0){
                moves.append(QPoint(x,y-1));
            }
        }
    }
    else{
        if(y==1){
            if(board->getPiece(x,y+2)==0){
                moves.append(QPoint(x,y+2));
            }
        }
        if(y+1 < 8){
            if(board->getPiece(x,y+1)==0){
                moves.append(QPoint(x,y+1));
            }
        }
    }

    return moves;
}
