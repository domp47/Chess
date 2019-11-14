#ifndef KING_H
#define KING_H

#include <QtCore/QPoint>
#include <QVector>
#include <Board/board.h>
#include <Controller/controller.h>

namespace King {
    QVector<Move> getMoves(int x, int y, Controller* controller, Board* board);
};


#endif //KING_H
