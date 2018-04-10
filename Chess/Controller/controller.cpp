#include "controller.h"
#include "AI/alphaBeta.h"

Controller::Controller() {
    window = new Window(this);
    board = new Board(this);
    window->show();
    alphaBeta = new AlphaBeta();
}

Window *Controller::getWindow() {
    return window;
}

Board *Controller::getBoard() {
    return board;
}

int Controller::findMove(bool whiteTeam, int *move) {
    return alphaBeta->findMove(this,whiteTeam,move);
}
