#include "RepresentationMap.h"

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


/**
 * Maps the chess pieces
 */
RepresentationMap::RepresentationMap() {
    map[-1] = "";
    map[-2] = "R";
    map[-3] = "N";
    map[-4] = "B";
    map[-5] = "Q";
    map[-6] = "K";

    map[1] = "";
    map[2] = "R";
    map[3] = "N";
    map[4] = "B";
    map[5] = "Q";
    map[6] = "K";
}

/**
 *  Gets the image for a chess piece
 *
 * @param key piece to get
 * @return image path of piece
 */
std::string RepresentationMap::getItem(int key) {
    return map[key];
}

