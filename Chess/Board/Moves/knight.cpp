#include "knight.h"

QVector<Move> Knight::getMoves(int x, int y, int **board) {
    QVector<Move> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    if(y-1>=0){//up
        if(y-2 >= 0 && x-1 >= 0){//up - up - left
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
        if(y-2 >= 0 && x+1 < 8){//up - up - right
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
    }

    if(x+1 < 8){//right
        if(x+2 < 8 && y-1 >= 0){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
        if(x+2 < 8 && y+1 < 8){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
    }

    if(y+1 < 8){//down
        if(y+2 < 8 && x-1 >= 0){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
        if(y+2 < 8 && x+1 < 8){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
    }

    if(x-1 >= 0){//left
        if(x-2 >= 0 && y-1 >= 0){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
        if(x-2 >= 0 && y+1 < 8){
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
    }

    return moves;
}

void Knight::addToVector(QVector<Move>* vector, int** board, int x, int y, bool whiteTeam, int initX, int initY) {
    if (board[y][x] == 0) {
        vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
    } else {
        if (whiteTeam && board[y][x] < 0)
            vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
        if (!whiteTeam && board[y][x] > 0)
            vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
    }
}
