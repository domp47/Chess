#include "queen.h"
#include "rook.h"
#include "bishop.h"

QVector<Move> Queen::getMoves(int x, int y, int **board) {
    QVector<Move> moves;

    QVector<Move> rookMoves = Rook::getMoves(x,y,board);
    moves.append(rookMoves);

    QVector<Move> bishopMoves = Bishop::getMoves(x,y,board);
    moves.append(bishopMoves);

    return moves;
}
