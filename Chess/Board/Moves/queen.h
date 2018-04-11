#ifndef QUEEN_H
#define QUEEN_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>

namespace Queen {
    QVector<Move> getMoves(int x, int y, int** board);
};


#endif //QUEEN_H
