#include "king.h"

QVector<QPoint> King::getMoves(int x, int y, int** gameBoard) {
    QVector<QPoint> moves;

    bool whiteTeam = true;

    if (gameBoard[y][x] < 0)
        whiteTeam = false;

    if(x+1<8 && ((whiteTeam && gameBoard[y][x+1]<=0) || (!whiteTeam && gameBoard[y][x+1]>=0))){
        moves.append(QPoint(x+1,y));
    }
    if(x-1>=0 && ((whiteTeam && gameBoard[y][x-1]<=0) || (!whiteTeam && gameBoard[y][x-1]>=0))){
        moves.append(QPoint(x-1,y));
    }
    if(y+1<8 && ((whiteTeam && gameBoard[y+1][x]<=0) || (!whiteTeam && gameBoard[y+1][x]>=0))){
        moves.append(QPoint(x,y+1));
    }
    if(y-1>=0 && ((whiteTeam && gameBoard[y-1][x]<=0) || (!whiteTeam && gameBoard[y-1][x]>=0))){
        moves.append(QPoint(x,y-1));
    }

    if(x+1<8 && y+1<8 && ((whiteTeam && gameBoard[y+1][x+1]<=0) || (!whiteTeam && gameBoard[y+1][x+1]>=0))){
        moves.append(QPoint(x+1,y+1));
    }
    if(x-1>=0 && y+1<8 && ((whiteTeam && gameBoard[y+1][x-1]<=0) || (!whiteTeam && gameBoard[y+1][x-1]>=0))){
        moves.append(QPoint(x-1,y+1));
    }
    if(x+1<8 && y-1>=0 && ((whiteTeam && gameBoard[y-1][x+1]<=0) || (!whiteTeam && gameBoard[y-1][x+1]>=0))){
        moves.append(QPoint(x+1,y-1));
    }
    if(x-1>=0 && y-1>=0 && ((whiteTeam && gameBoard[y-1][x-1]<=0) || (!whiteTeam && gameBoard[y-1][x-1]>=0))){
        moves.append(QPoint(x-1,y-1));
    }

//    if(whiteTeam){
//        if(!controller->checkCheck(true)){// white kings not in check
//            if(!board->getWLR()&&!board->getWKing()){//white long check if rook nd king havent been moved
//                if(board->getPiece(1,7)==0 && board->getPiece(2,7)==0 && board->getPiece(3,7)==0){ //check if empty between the rook and king
//                    //check if any of the two places the king is moving over or is moving to can be attacked
//                    if(!controller->checkForAttack(2,7, true) && !controller->checkForAttack(3,7, true)){
//                        board->setWhiteLongCastle(true);
//                    }
//                }
//            }
//            if(!board->getWRR() && !board->getWKing()){
//                if(board->getPiece(5,7)==0 && board->getPiece(6,7)==0){
//                    if(!controller->checkForAttack(5,7,true) && !controller->checkForAttack(6,7,true)){
//                        board->setWhiteCastle(true);
//                    }
//                }
//            }
//        }
//    }else{
//        if(!controller->checkCheck(false)){
//            if(!board->getBLR()&&!board->getBKing()){//white long check if rook nd king havent been moved
//                if(board->getPiece(1,0)==0 && board->getPiece(2,0)==0 && board->getPiece(3,0)==0){ //check if empty between the rook and king
//                    //check if any of the two places the king is moving over or is moving to can be attacked
//                    if(!controller->checkForAttack(2,0, false) && !controller->checkForAttack(3,0, false)){
//                        board->setBlackLongCastle(true);
//                    }
//                }
//            }
//            if(!board->getBRR() && !board->getBKing()){
//                if(board->getPiece(5,0)==0 && board->getPiece(6,0)==0){
//                    if(!controller->checkForAttack(5,0,false) && !controller->checkForAttack(6,0,false)){
//                        board->setBlackCastle(true);
//                    }
//                }
//            }
//        }
//    }


    return moves;
}
