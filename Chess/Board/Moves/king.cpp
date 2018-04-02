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
        if(!board->checkCheck(true)){// white kings not in check
            if(!board->getWLR()&&!board->getWKing()){//white long check if rook nd king havent been moved
                if(board->getPiece(1,7)==0 && board->getPiece(2,7)==0 && board->getPiece(3,7)==0){ //check if empty between the rook and king
                    //check if any of the two places the king is moving over or is moving to can be attacked
                    if(!board->checkForAttack(2,7, true) && !board->checkForAttack(3,7, true)){
                        board->setWhiteLongCastle(true);
                    }
                }
            }
            if(!board->getWRR() && board->getWKing()){
                if(board->getPiece(5,7)==0 && board->getPiece(6,7)==0){
                    if(!board->checkForAttack(5,7,true) && !board->checkForAttack(6,7,true)){
                        board->setWhiteCastle(true);
                    }
                }
            }
        }
    }else{
        if(!board->checkCheck(false)){
            if(!board->getBLR()&&!board->getBKing()){//white long check if rook nd king havent been moved
                if(board->getPiece(1,0)==0 && board->getPiece(2,0)==0 && board->getPiece(3,0)==0){ //check if empty between the rook and king
                    //check if any of the two places the king is moving over or is moving to can be attacked
                    if(!board->checkForAttack(2,0, false) && !board->checkForAttack(3,0, false)){
                        board->setBlackLongCastle(true);
                    }
                }
            }
            if(!board->getBRR() && board->getBKing()){
                if(board->getPiece(5,0)==0 && board->getPiece(6,0)==0){
                    if(!board->checkForAttack(5,0,false) && !board->checkForAttack(6,0,false)){
                        board->setBlackCastle(true);
                    }
                }
            }
        }
    }


    return moves;
}
