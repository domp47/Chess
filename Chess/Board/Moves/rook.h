#ifndef ROOK_H
#define ROOK_H


#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <array>

namespace Rook {
    QVector<Move> getMoves(int x, int y, std::array<std::array<int,8>,8> board);
};


#endif //ROOK_H
