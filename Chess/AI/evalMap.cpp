#include "evalMap.h"

/**
 *  -6 = BLK KING = -900
 *  -5 = BLK QUEEN = -90
 *  -4 = BLK BISHOP = -30
 *  -3 = BLK KNIGHT = -30
 *  -2 = BLK ROOK = -50
 *  -1 = BLK PAWN = -10
 *
 *   0 = NO PIECE
 *
 *   1 = WHT PAWN = 10
 *   2 = WHT ROOK = 50
 *   3 = WHT KNIGHT = 30
 *   4 = WHT BISHOP = 30
 *   5 = WHT QUEEN = 90
 *   6 = WHT KING = 900
 */


/**
 * Map with Piece Weights
 */
EvalMap::EvalMap() {

    map[-1] = -10;
    map[-2] = -50;
    map[-3] = -30;
    map[-4] = -30;
    map[-5] = -90;
    map[-6] = -900;

    map[1] = 10;
    map[2] = 50;
    map[3] = 30;
    map[4] = 30;
    map[5] = 90;
    map[6] = 900;
}

/**
 *  Returns the weight of the specified piece
 * 
 * @param key piece
 * @return weight of piece
 */
int EvalMap::getItem(int key) {
    return map[key];
}
