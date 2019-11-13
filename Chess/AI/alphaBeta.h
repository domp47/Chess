#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <Board/elPassant.h>
#include "evalMap.h"
#include "Controller/move.h"
#include <random>
#include "nn.h"

class Controller;

class AlphaBeta{

public:
    AlphaBeta(Controller* controller, int searchDepth, std::string graphPath, std::string checkpointPath);
    Move findMove(bool whiteTeam, int moveNumber);
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
    NeuralNetwork* nn;
    EvalMap map;
    std::random_device rd;
    std::mt19937 mt;
    int searchDepth;
};

#endif // ALPHABETA_H