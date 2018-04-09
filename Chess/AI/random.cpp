#include "random.h"
#include "../Board/board.h"

Random::Random() {
    mt = std::mt19937(rd());
    dist = std::uniform_int_distribution<int>(0,8);
}

int Random::getRandomMove(Board *board, bool whiteTeam, int move[4]) {
    int col, row, nPiecesInRow;

    do{
        row = dist(mt);
        nPiecesInRow = piecesInRow(board,whiteTeam,row);
    }while(nPiecesInRow==0);

    if(nPiecesInRow==1){
        for (int x = 0; x < 8; ++x) {
            if(whiteTeam && board->getPiece(x,row) > 0){
                move[0] = x;
                move[1] = row;
                break;
            }else if(!whiteTeam && board->getPiece(x,row) < 0){
                move[0] = x;
                move[1] = row;
                break;
            }
        }
    }else if(nPiecesInRow > 1){
        do{
            col = dist(mt);
        }while(board->getPiece(col,row) == 0);
        move[0] = col;
        move[1] = row;
    }

    QVector<QPoint> posMoves = board->getMoves(move[0],move[1]);

    std::uniform_int_distribution<int> moveDist(0,posMoves.length());
    int loc = moveDist(mt);

    if(loc == 0){
        return 0;
    }else{
        move[2] = posMoves[loc].x();
        move[3] = posMoves[loc].y();
        return 1;
    }
}

int Random::piecesInRow(Board *board, bool whiteTeam, int row) {
    int nPieces = 0;

    for (int x = 0; x < 8; ++x) {
        if(whiteTeam && board->getPiece(x,row) > 0){
            nPieces++;
        }else if(!whiteTeam && board->getPiece(x,row) < 0){
            nPieces++;
        }
    }
}
