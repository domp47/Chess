#ifndef KNIGHT_H
#define KNIGHT_H

#include <QtCore/QPoint>
#include <QVector>

namespace Knight {
    QVector<QPoint> getMoves(int x, int y, int** board);
    void addToVector(QVector<QPoint>* vector, int **board, int x, int y, bool whiteTeam);
};


#endif //KNIGHT_H
