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
    char findUpgrade(Move move);

private:
    QVector<Move> getAllMoves(bool whiteTeam);
    int evaluateBoard(std::array<std::array<int,8>,8> board);
    int minimax(int depth,int alpha, int beta, bool whiteTeam);
    Move minimaxRoot(int depth, bool whiteTeam);
    void doMove(Move move, int* temp, int* rook, int* king,int* undoType, ElPassant* whitePassant, ElPassant* blackPassant);
    void undoMove(Move move, int temp, int rook, int king, int undoType, ElPassant whitePassant, ElPassant blackPassant);
    int promotionRoot(Move move, int depth);

private:
    Controller* controller;
    EvalMap map;
    Random randomMove;

};

#endif // ALPHABETA_H