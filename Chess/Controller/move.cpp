#include "move.h"

/**
 * Creates a move with specified starting and end points and the type of move
 *
 * @param init starting point of move
 * @param end ending point of move
 * @param special 0 = nothing, 1 = passant, 2 = castling left, 3 = castling right, 4 = promotion
 */
Move::Move(QPoint init, QPoint end, int special) {
    this->init = init;
    this->end = end;
    this->special = special;
}

/**
 * Default constructor
 */
Move::Move() {
    this->init = QPoint(-1,-1);
    this->end = QPoint(-1,-1);
    this->special = -1;
}
