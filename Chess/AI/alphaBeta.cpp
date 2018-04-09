#include "alphaBeta.h"
#include <../Board/board.h>

AlphaBeta::AlphaBeta() {

}

int AlphaBeta::findMove(Board *board, bool whiteTeam, int move[4]) {
    return randomMove.getRandomMove(board, whiteTeam, move);
}
