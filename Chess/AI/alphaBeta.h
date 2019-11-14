#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <Board/elPassant.h>
#include "evalMap.h"
#include "Controller/move.h"
#include "Board/board.h"
#include <random>
#include "nn.h"
#include <future>

class Controller;

class AlphaBeta{

public:
    AlphaBeta(Controller* controller, int searchDepth, std::string graphPath, std::string checkpointPath);
    Move findMove(bool whiteTeam, int moveNumber);
    char findUpgrade(Move move);

private:
    QVector<Move> getAllMoves(Board* board, bool whiteTeam);
    int evaluateBoard(std::array<std::array<int,8>,8> board);
    int minimax(Board* board, int depth,int alpha, int beta, bool whiteTeam);
    std::pair<int, int> minimaxRootSection(Board* board, int depth, bool whiteTeam, QVector<Move> moves, int start, int end);
    Move minimaxRoot(int depth, bool whiteTeam);
    void doMove(Move move, Board* board, int* temp, int* rook, int* king,int* undoType, ElPassant* whitePassant, ElPassant* blackPassant);
    void undoMove(Move move, Board* board, int temp, int rook, int king, int undoType, ElPassant whitePassant, ElPassant blackPassant);
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