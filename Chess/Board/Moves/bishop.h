#ifndef BISHOP_H
#define BISHOP_H


#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <array>

namespace Bishop {
    QVector<Move> getMoves(int x, int y, std::array<std::array<int,8>,8> board);
};


#endif //BISHOP_H
