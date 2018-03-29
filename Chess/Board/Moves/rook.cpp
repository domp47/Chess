#include "rook.h"

QVector <QPoint> Rook::getMoves(int x, int y, int **board) {
    QVector <QPoint> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    for (int i = y - 1; i >= 0; i--) { //check above
        if (board[i][x] == 0) {
            moves.append(QPoint(x, i));
        } else {
            if (whiteTeam && board[i][x] < 0)
                moves.append(QPoint(x, i));
            if (!whiteTeam && board[i][x] > 0)
                moves.append(QPoint(x, i));
            break;
        }
    }
    for (int i = x + 1; i < 8; ++i) { //check right
        if (board[y][i] == 0) {
            moves.append(QPoint(i, y));
        } else {
            if (whiteTeam && board[y][i] < 0)
                moves.append(QPoint(i, y));
            if (!whiteTeam && board[y][i] > 0)
                moves.append(QPoint(i, y));
            break;
        }
    }
    for (int i = y + 1; i < 8; i++) { //check below
        if (board[i][x] == 0) {
            moves.append(QPoint(x, i));
        } else {
            if (whiteTeam && board[i][x] < 0)
                moves.append(QPoint(x, i));
            if (!whiteTeam && board[i][x] > 0)
                moves.append(QPoint(x, i));
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) { //check left
        if (board[y][i] == 0) {
            moves.append(QPoint(i, y));
        } else {
            if (whiteTeam && board[y][i] < 0)
                moves.append(QPoint(i, y));
            if (!whiteTeam && board[y][i] > 0)
                moves.append(QPoint(i, y));
            break;
        }
    }

    return moves;
}
