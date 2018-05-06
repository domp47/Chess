#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <Board/elPassant.h>
#include "random.h"
#include "evalMap.h"

class Controller;

class AlphaBeta{

public:
    AlphaBeta(Controller* controller);
    Move findMove(bool whiteTeam);
    char findUpgrade();

private:
    Random randomMove;
    QVector<Move> getAllMoves(bool whiteTeam);
    int evaluateBoard(std::array<std::array<int,8>,8> board);
    int minimax(int depth,int alpha, int beta, bool whiteTeam);
    Move minimaxRoot(int depth, bool whiteTeam);
    void doMove(Move move, int* temp, int* rook, int* king,int* undoType, ElPassant* whitePassant, ElPassant* blackPassant);
    void undoMove(Move move, int temp, int rook, int king, int undoType, ElPassant whitePassant, ElPassant blackPassant);

private:
    Controller* controller;
    EvalMap map;

};

#endif // ALPHABETA_H