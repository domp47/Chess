#ifndef BISHOP_H
#define BISHOP_H


#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>

namespace Bishop {
    QVector<Move> getMoves(int x, int y, int** board);
};


#endif //BISHOP_H
