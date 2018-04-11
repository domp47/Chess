#ifndef KING_H
#define KING_H

#include <QtCore/QPoint>
#include <QVector>
#include <Board/board.h>
#include <Controller/controller.h>

namespace King {
    QVector<QPoint> getMoves(int x, int y, int** gameBoard);
};


#endif //KING_H
