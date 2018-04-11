#ifndef PAWN_H
#define PAWN_H

#include <QtCore/QPoint>
#include <QVector>

class Board;

namespace Pawn {
    QVector<QPoint> getMoves(int x, int y, int** board);
};

#endif //PAWN_H