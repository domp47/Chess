#include "alphaBeta.h"
#include "Controller/controller.h"

AlphaBeta::AlphaBeta() {

}

int AlphaBeta::findMove(Controller* controller, bool whiteTeam, int move[4]) {
    return randomMove.getRandomMove(controller, whiteTeam, move);
}
