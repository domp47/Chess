#include "queen.h"
#include "rook.h"
#include "bishop.h"

QVector<Move> Queen::getMoves(int x, int y, std::array<std::array<int,8>,8> board) {
    QVector<Move> moves;

    QVector<Move> rookMoves = Rook::getMoves(x,y,board);
    moves.append(rookMoves);

    QVector<Move> bishopMoves = Bishop::getMoves(x,y,board);
    moves.append(bishopMoves);

    return moves;
}
