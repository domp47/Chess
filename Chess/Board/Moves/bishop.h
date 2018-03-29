#ifndef BISHOP_H
#define BISHOP_H


#include <QtCore/QPoint>
#include <QVector>

namespace Bishop {
    QVector<QPoint> getMoves(int x, int y, int** board);
};


#endif //BISHOP_H
