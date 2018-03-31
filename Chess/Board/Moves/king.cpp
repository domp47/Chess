#include "king.h"

QVector<QPoint> King::getMoves(int x, int y, Board* board) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if (board->getPiece(x,y) < 0)
        whiteTeam = false;

    if(x+1<8 && ((whiteTeam && board->getPiece(x+1,y)<=0) || (!whiteTeam && board->getPiece(x+1,y)>=0))){
        moves.append(QPoint(x+1,y));
    }
    if(x-1>=0 && ((whiteTeam && board->getPiece(x-1,y)<=0) || (!whiteTeam && board->getPiece(x-1,y)>=0))){
        moves.append(QPoint(x-1,y));
    }
    if(y+1<8 && ((whiteTeam && board->getPiece(x,y+1)<=0) || (!whiteTeam && board->getPiece(x,y+1)>=0))){
        moves.append(QPoint(x,y+1));
    }
    if(y-1>=0 && ((whiteTeam && board->getPiece(x,y-1)<=0) || (!whiteTeam && board->getPiece(x,y-1)>=0))){
        moves.append(QPoint(x,y-1));
    }

    if(x+1<8 && y+1<8 && ((whiteTeam && board->getPiece(x+1,y+1)<=0) || (!whiteTeam && board->getPiece(x+1,y+1)>=0))){
        moves.append(QPoint(x+1,y+1));
    }
    if(x-1>=0 && y+1<8 && ((whiteTeam && board->getPiece(x-1,y+1)<=0) || (!whiteTeam && board->getPiece(x-1,y+1)>=0))){
        moves.append(QPoint(x-1,y+1));
    }
    if(x+1<8 && y-1>=0 && ((whiteTeam && board->getPiece(x+1,y-1)<=0) || (!whiteTeam && board->getPiece(x+1,y-1)>=0))){
        moves.append(QPoint(x+1,y-1));
    }
    if(x-1>=0 && y-1>=0 && ((whiteTeam && board->getPiece(x-1,y-1)<=0) || (!whiteTeam && board->getPiece(x-1,y-1)>=0))){
        moves.append(QPoint(x-1,y-1));
    }

    if(whiteTeam){
        if(!board->checkCheck(true)){
            if(!board->getWLR()&&!board->getWKing()){//white long castling
                if(board->getPiece(1,7)==0 && board->getPiece(2,7)==0 && board->getPiece(3,7)==0){

                }
            }
        }
    }


    return moves;
}
