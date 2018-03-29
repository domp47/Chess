#ifndef KING_H
#define KING_H

#include <QtCore/QPoint>
#include <QVector>

namespace King {
    QVector<QPoint> getMoves(int x, int y, int** board);
};


#endif //KING_H
