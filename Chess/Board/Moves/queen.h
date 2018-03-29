#ifndef QUEEN_H
#define QUEEN_H

#include <QtCore/QPoint>
#include <QVector>

namespace Queen {
    QVector<QPoint> getMoves(int x, int y, int** board);
};


#endif //QUEEN_H
