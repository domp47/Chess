#ifndef KING_H
#define KING_H

#include <QtCore/QPoint>
#include <QVector>
#include <Board/board.h>

namespace King {
    QVector<QPoint> getMoves(int x, int y, Board* board);
};


#endif //KING_H
