#include "queen.h"
#include "rook.h"
#include "bishop.h"

QVector<QPoint> Queen::getMoves(int x, int y, int **board) {
    QVector<QPoint> moves;

    QVector<QPoint> rookMoves = Rook::getMoves(x,y,board);
    moves.append(rookMoves);

    QVector<QPoint> bishopMoves = Bishop::getMoves(x,y,board);
    moves.append(bishopMoves);

    return moves;
}
