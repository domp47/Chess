#ifndef PAWN_H
#define PAWN_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <Controller/controller.h>

class Board;

namespace Pawn {
    QVector<Move> getMoves(int x, int y, std::array<std::array<int,8>,8> board, Controller* controller);
};

#endif //PAWN_H