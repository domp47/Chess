#include "map.h"

/**
 *  -6 = BLK KING
 *  -5 = BLK QUEEN
 *  -4 = BLK BISHOP
 *  -3 = BLK KNIGHT
 *  -2 = BLK ROOK
 *  -1 = BLK PAWN
 *
 *   0 = NO PIECE
 *
 *   1 = WHT PAWN
 *   2 = WHT ROOK
 *   3 = WHT KNIGHT
 *   4 = WHT BISHOP
 *   5 = WHT QUEEN
 *   6 = WHT KING
 */



Map::Map() {

    map[-1] = "./Chess/Pieces/pd.png";
    map[-2] = "./Chess/Pieces/rd.png";
    map[-3] = "./Chess/Pieces/nd.png";
    map[-4] = "./Chess/Pieces/bd.png";
    map[-5] = "./Chess/Pieces/qd.png";
    map[-6] = "./Chess/Pieces/kd.png";

    map[1] = "./Chess/Pieces/pl.png";
    map[2] = "./Chess/Pieces/rl.png";
    map[3] = "./Chess/Pieces/nl.png";
    map[4] = "./Chess/Pieces/bl.png";
    map[5] = "./Chess/Pieces/ql.png";
    map[6] = "./Chess/Pieces/kl.png";
}

std::string Map::getItem(int key) {
    return map[key];
}
