#ifndef Controller_H
#define Controller_H

#include <GUI/window.h>
#include <Board/board.h>
//#include "AI/alphaBeta.h"

class AlphaBeta;

class Controller{
public:
    Controller();
    Window* getWindow();
    Board* getBoard();
    int findMove(bool whiteTeam, int move[4]);

private:
    Window* window;
    Board* board;
    AlphaBeta* alphaBeta;
};

#endif