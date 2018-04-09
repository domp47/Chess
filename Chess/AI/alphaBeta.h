#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "random.h"

class Board;

class AlphaBeta{

public:
    AlphaBeta();
    int findMove(Board* board, bool whiteTeam, int move[4]);

private:
    Random randomMove;

};

#endif // ALPHABETA_H