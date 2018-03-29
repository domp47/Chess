#ifndef ROOK_H
#define ROOK_H


#include <QtCore/QPoint>
#include <QVector>

namespace Rook {
    QVector<QPoint> getMoves(int x, int y, int** board);
};


#endif //ROOK_H
