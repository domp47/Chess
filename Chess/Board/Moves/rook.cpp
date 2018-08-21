#include "rook.h"

/**
 *  Gets all the possible moves the rook at position x,y can make
 * 
 * @param x X location on board
 * @param y Y location on board
 * @param board game board
 * @return Vector of possible moves
 */
QVector <Move> Rook::getMoves(int x, int y, std::array<std::array<int,8>,8> board) {
    QVector <Move> moves;

    bool whiteTeam = true;

    if (board[y][x] < 0)
        whiteTeam = false;

    for (int i = y - 1; i >= 0; i--) { //check above
        if (board[i][x] == 0) {
            moves.append(Move(QPoint(x,y),QPoint(x,i)));
        } else {
            if (whiteTeam && board[i][x] < 0)
                moves.append(Move(QPoint(x,y),QPoint(x,i)));
            if (!whiteTeam && board[i][x] > 0)
                moves.append(Move(QPoint(x,y),QPoint(x,i)));
            break;
        }
    }
    for (int i = x + 1; i < 8; ++i) { //check right
        if (board[y][i] == 0) {
            moves.append(Move(QPoint(x,y),QPoint(i,y)));
        } else {
            if (whiteTeam && board[y][i] < 0)
                moves.append(Move(QPoint(x,y),QPoint(i,y)));
            if (!whiteTeam && board[y][i] > 0)
                moves.append(Move(QPoint(x,y),QPoint(i,y)));
            break;
        }
    }
    for (int i = y + 1; i < 8; i++) { //check below
        if (board[i][x] == 0) {
            moves.append(Move(QPoint(x,y),QPoint(x,i)));
        } else {
            if (whiteTeam && board[i][x] < 0)
                moves.append(Move(QPoint(x,y),QPoint(x,i)));
            if (!whiteTeam && board[i][x] > 0)
                moves.append(Move(QPoint(x,y),QPoint(x,i)));
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) { //check left
        if (board[y][i] == 0) {
            moves.append(Move(QPoint(x,y),QPoint(i,y)));
        } else {
            if (whiteTeam && board[y][i] < 0)
                moves.append(Move(QPoint(x,y),QPoint(i,y)));
            if (!whiteTeam && board[y][i] > 0)
                moves.append(Move(QPoint(x,y),QPoint(i,y)));
            break;
        }
    }

    return moves;
}
