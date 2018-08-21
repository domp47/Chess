#include "knight.h"

/**
 *  Gets all the possible moves the knight at position x,y can make
 * 
 * @param x X location on board
 * @param y Y location on board
 * @param board game board
 * @return Vector of possible moves
 */
QVector<Move> Knight::getMoves(int x, int y, std::array<std::array<int,8>,8> board) {
    QVector<Move> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    if(y-1>=0){//up
        if(y-2 >= 0 && x-1 >= 0){//up - up - left
            addToVector(&moves, board, x-1, y-2, whiteTeam,x ,y);
        }
        if(y-2 >= 0 && x+1 < 8){//up - up - right
            addToVector(&moves, board, x+1, y-2, whiteTeam,x ,y);
        }
    }

    if(x+1 < 8){//right
        if(x+2 < 8 && y-1 >= 0){
            addToVector(&moves, board, x+2, y-1, whiteTeam,x ,y);
        }
        if(x+2 < 8 && y+1 < 8){
            addToVector(&moves, board, x+2, y+1, whiteTeam,x ,y);
        }
    }

    if(y+1 < 8){//down
        if(y+2 < 8 && x-1 >= 0){
            addToVector(&moves, board, x-1, y+2, whiteTeam,x ,y);
        }
        if(y+2 < 8 && x+1 < 8){
            addToVector(&moves, board, x+1, y+2, whiteTeam,x ,y);
        }
    }

    if(x-1 >= 0){//left
        if(x-2 >= 0 && y-1 >= 0){
            addToVector(&moves, board, x-2, y-1, whiteTeam,x ,y);
        }
        if(x-2 >= 0 && y+1 < 8){
            addToVector(&moves, board, x-2, y+1, whiteTeam,x ,y);
        }
    }

    return moves;
}

/**
 *
 * @param vector
 * @param board
 * @param x
 * @param y
 * @param whiteTeam
 * @param initX
 * @param initY
 */
void Knight::addToVector(QVector<Move>* vector, std::array<std::array<int,8>,8> board, int x, int y, bool whiteTeam, int initX, int initY) {
    if (board[y][x] == 0) {
        vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
    } else {
        if (whiteTeam && board[y][x] < 0)
            vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
        if (!whiteTeam && board[y][x] > 0)
            vector->append(Move(QPoint(initX,initY),QPoint(x, y)));
    }
}
