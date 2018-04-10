#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "random.h"

class Controller;

class AlphaBeta{

public:
    AlphaBeta();
    int findMove(Controller* controller, bool whiteTeam, int move[4]);

private:
    Random randomMove;

};

#endif // ALPHABETA_H