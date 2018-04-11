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
    QVector<QVector<int>> getAllMoves(int**, bool whiteTeam);
    int evaluateBoard(int** score);
    int minimax(int depth,int alpha, int beta, int** board, bool whiteTeam);
    QVector<int> minimaxRoot(int depth, int** board, bool whiteTeam);

private:
    Controller* controller;
    EvalMap map;

};

#endif // ALPHABETA_H