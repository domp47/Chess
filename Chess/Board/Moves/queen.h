#ifndef QUEEN_H
#define QUEEN_H

#include <QtCore/QPoint>
#include <QVector>
#include <Controller/move.h>
#include <array>

namespace Queen {
    QVector<Move> getMoves(int x, int y, std::array<std::array<int,8>,8> board);
};


#endif //QUEEN_H
