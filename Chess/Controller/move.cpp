#include "move.h"

/**
 *
 * @param init
 * @param end
 * @param special 0 = nothing, 1 = passant, 2 = castling left, 3 = castling right, 4 = promotion
 */
Move::Move(QPoint init, QPoint end, int special) {
    this->init = init;
    this->end = end;
    this->special = special;
}
