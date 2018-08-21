#include "queen.h"
#include "rook.h"
#include "bishop.h"

/**
 *  Gets all the possible moves the Queen at position x,y can make
 * 
 * @param x X location on board
 * @param y Y location on board
 * @param board game board
 * @return Vector of possible moves
 */
QVector<Move> Queen::getMoves(int x, int y, std::array<std::array<int,8>,8> board) {
    QVector<Move> moves;

    QVector<Move> rookMoves = Rook::getMoves(x,y,board);
    moves.append(rookMoves);

    QVector<Move> bishopMoves = Bishop::getMoves(x,y,board);
    moves.append(bishopMoves);

    return moves;
}
