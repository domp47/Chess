#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "random.h"
#include "evalMap.h"

class Controller;

class AlphaBeta{

public:
    AlphaBeta(Controller* controller);
    QVector<int> findMove(bool whiteTeam);
    char findUpgrade();

private:
    Random randomMove;
    QVector<QVector<int>> getAllMoves(bool whiteTeam);
    int evaluateBoard(int** board);
    int minimax(int depth,int alpha, int beta, bool whiteTeam);
    QVector<int> minimaxRoot(int depth, bool whiteTeam);

private:
    Controller* controller;
    EvalMap map;

};

#endif // ALPHABETA_H