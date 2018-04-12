#ifndef MOVE_H
#define MOVE_H

#include <QPoint>

class Move {
public:
    Move();
    Move(QPoint init, QPoint end, int special=0);

public:
    QPoint init;
    QPoint end;
    int special;

};

#endif // MOVE_H