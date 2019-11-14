#include "king.h"

/**
 *  Gets all the possible moves the king at position x,y can make
 * 
 * @param x X location on board
 * @param y Y location on board
 * @param controller game controller
 * @return Vector of possible moves
 */
QVector<Move> King::getMoves(int x, int y, Controller* controller, Board* board) {
    QVector<Move> moves;

    std::array<std::array<int,8>,8> gameBoard = board->getBoard();

    bool whiteTeam = true;

    if (gameBoard[y][x] < 0)
        whiteTeam = false;

    if(x+1<8 && ((whiteTeam && gameBoard[y][x+1]<=0) || (!whiteTeam && gameBoard[y][x+1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x+1,y)));
    }
    if(x-1>=0 && ((whiteTeam && gameBoard[y][x-1]<=0) || (!whiteTeam && gameBoard[y][x-1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x-1,y)));
    }
    if(y+1<8 && ((whiteTeam && gameBoard[y+1][x]<=0) || (!whiteTeam && gameBoard[y+1][x]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x,y+1)));
    }
    if(y-1>=0 && ((whiteTeam && gameBoard[y-1][x]<=0) || (!whiteTeam && gameBoard[y-1][x]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x,y-1)));
    }

    if(x+1<8 && y+1<8 && ((whiteTeam && gameBoard[y+1][x+1]<=0) || (!whiteTeam && gameBoard[y+1][x+1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x+1,y+1)));
    }
    if(x-1>=0 && y+1<8 && ((whiteTeam && gameBoard[y+1][x-1]<=0) || (!whiteTeam && gameBoard[y+1][x-1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x-1,y+1)));
    }
    if(x+1<8 && y-1>=0 && ((whiteTeam && gameBoard[y-1][x+1]<=0) || (!whiteTeam && gameBoard[y-1][x+1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x+1,y-1)));
    }
    if(x-1>=0 && y-1>=0 && ((whiteTeam && gameBoard[y-1][x-1]<=0) || (!whiteTeam && gameBoard[y-1][x-1]>=0))){
        moves.append(Move(QPoint(x,y),QPoint(x-1,y-1)));
    }

    if(whiteTeam){
        if(!controller->checkCheck(board, true)){// white kings not in check
            if(!board->getWLR()&&!board->getWKing()){//white long check if rook nd king havent been moved
                if(board->getPiece(1,7)==0 && board->getPiece(2,7)==0 && board->getPiece(3,7)==0){ //check if empty between the rook and king
                    //check if any of the two places the king is moving over or is moving to can be attacked
                    if(!controller->checkForAttack(board, 2,7, true) && !controller->checkForAttack(board, 3,7, true)){
                        moves.append(Move(QPoint(4,7),QPoint(2,7),2));
                    }
                }
            }
            if(!board->getWRR() && !board->getWKing()){
                if(board->getPiece(5,7)==0 && board->getPiece(6,7)==0){
                    if(!controller->checkForAttack(board, 5,7,true) && !controller->checkForAttack(board, 6,7,true)){
                        moves.append(Move(QPoint(4,7),QPoint(6,7),3));
                    }
                }
            }
        }
    }else{
        if(!controller->checkCheck(board, false)){
            if(!board->getBLR()&&!board->getBKing()){//black long check if rook nd king havent been moved
                if(board->getPiece(1,0)==0 && board->getPiece(2,0)==0 && board->getPiece(3,0)==0){ //check if empty between the rook and king
                    //check if any of the two places the king is moving over or is moving to can be attacked
                    if(!controller->checkForAttack(board, 2,0, false) && !controller->checkForAttack(board, 3,0, false)){
                        moves.append(Move(QPoint(4,0),QPoint(2,0),2));
                    }
                }
            }
            if(!board->getBRR() && !board->getBKing()){
                if(board->getPiece(5,0)==0 && board->getPiece(6,0)==0){
                    if(!controller->checkForAttack(board, 5,0,false) && !controller->checkForAttack(board, 6,0,false)){
                        moves.append(Move(QPoint(4,0),QPoint(6,0),3));
                    }
                }
            }
        }
    }

    return moves;
}
