#include "pawn.h"
#include "../board.h"

QVector<Move> Pawn::getMoves(int x, int y, std::array<std::array<int,8>,8> board, Controller* controller) {
    QVector<Move> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    if(whiteTeam){//if its white pawn
        if(y==6){//at starting position
            if(board[y-2][x]==0 && board[y-1][x]==0){//is something blocking it 2 spaces ahead
                moves.append(Move(QPoint(x,y),QPoint(x,y-2)));
            }
        }
        if(y-1 >= 0){//checking if it can move up without going off board
            if(board[y-1][x]==0){//check if the spot above is empty
                moves.append(Move(QPoint(x,y),QPoint(x,y-1)));
            }
            if(x-1 >= 0 && board[y-1][x-1]<0){//check if enemy on diagonal
                moves.append(Move(QPoint(x,y),QPoint(x-1,y-1)));
            }
            if(x+1 < 8 && board[y-1][x+1]<0){//check if enemy on diagonal
                moves.append(Move(QPoint(x,y),QPoint(x+1,y-1)));
            }
        }
        if(controller->getBoard()->getWhitePassant().getPresent()){
            if(controller->getBoard()->getWhitePassant().getAttacker1().x()==x && controller->getBoard()->getWhitePassant().getAttacker1().y()==y){
                moves.append(Move(QPoint(x,y),QPoint(controller->getBoard()->getWhitePassant().getVictim().x(),controller->getBoard()->getWhitePassant().getVictim().y()-1),1));
            }else if(controller->getBoard()->getWhitePassant().getAttacker2().x()==x && controller->getBoard()->getWhitePassant().getAttacker2().y()==y){
                moves.append(Move(QPoint(x,y),QPoint(controller->getBoard()->getWhitePassant().getVictim().x(),controller->getBoard()->getWhitePassant().getVictim().y()-1),1));
            }
        }

    }
    else{//black pawn
        if(y==1){//at starting pos
            if(board[y+2][x]==0 && board[y+1][x] == 0){
                moves.append(Move(QPoint(x,y),QPoint(x,y+2)));
            }
        }
        if(y+1 < 8){//can it move forward without going off board
            if(board[y+1][x]==0){
                moves.append(Move(QPoint(x,y),QPoint(x,y+1)));
            }
            if(x-1 >= 0 && board[y+1][x-1]>0){//check if enemy on diagonal
                moves.append(Move(QPoint(x,y),QPoint(x-1,y+1)));
            }
            if(x+1 < 8 && board[y+1][x+1]>0){//check if enemy on diagonal
                moves.append(Move(QPoint(x,y),QPoint(x+1,y+1)));
            }
        }
        if(controller->getBoard()->getBlackPassant().getPresent()){
            if(controller->getBoard()->getBlackPassant().getAttacker1().x()==x && controller->getBoard()->getBlackPassant().getAttacker1().y()==y){
                moves.append(Move(QPoint(x,y),QPoint(controller->getBoard()->getBlackPassant().getVictim().x(),controller->getBoard()->getBlackPassant().getVictim().y()+1),1));
            }else if(controller->getBoard()->getBlackPassant().getAttacker2().x()==x && controller->getBoard()->getBlackPassant().getAttacker2().y()==y){
                moves.append(Move(QPoint(x,y),QPoint(controller->getBoard()->getBlackPassant().getVictim().x(),controller->getBoard()->getBlackPassant().getVictim().y()+1),1));
            }
        }
    }

    return moves;
}
