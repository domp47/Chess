#ifndef KNIGHT_H
#define KNIGHT_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>

namespace Knight {
    QVector<Move> getMoves(int x, int y, int** board);
    void addToVector(QVector<Move>* vector, int **board, int x, int y, bool whiteTeam, int initX, int initY);
};


#endif //KNIGHT_H
