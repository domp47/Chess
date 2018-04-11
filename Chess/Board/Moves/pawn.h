#ifndef PAWN_H
#define PAWN_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <Controller/controller.h>

class Board;

namespace Pawn {
    QVector<Move> getMoves(int x, int y, int** board, Controller* controller);
};

#endif //PAWN_H