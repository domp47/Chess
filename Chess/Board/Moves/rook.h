#ifndef ROOK_H
#define ROOK_H


#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>

namespace Rook {
    QVector<Move> getMoves(int x, int y, int** board);
};


#endif //ROOK_H
