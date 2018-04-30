#ifndef KNIGHT_H
#define KNIGHT_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <array>

namespace Knight {
    QVector<Move> getMoves(int x, int y, std::array<std::array<int,8>,8> board);
    void addToVector(QVector<Move>* vector, std::array<std::array<int,8>,8> board, int x, int y, bool whiteTeam, int initX, int initY);
};


#endif //KNIGHT_H
